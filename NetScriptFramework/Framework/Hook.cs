using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace NetScriptFramework.Tools._Internal
{
    /// <summary>
    /// Helper to create hooks.
    /// </summary>
    internal abstract class HookBase
    {
        #region Included code

        /// <summary>
        /// Writes the converted byte code to stream.
        /// </summary>
        /// <param name="code">The code.</param>
        /// <param name="ms">The ms.</param>
        /// <param name="hookSourceAddr">The hook source addr.</param>
        /// <param name="offset">The offset.</param>
        /// <param name="tempBack">The temporary back.</param>
        /// <exception cref="System.NotImplementedException"></exception>
        internal protected void WriteConvertedCode(byte[] code, BinaryWriter ms, IntPtr hookSourceAddr, int offset, List<KeyValuePair<long, long>> tempBack)
        {
            if (!Main.Is64Bit)
                throw new NotImplementedException();

            // Rel-call
            if (code.Length >= 5 && code[0] == 0xE8)
            {
                // Convert to absolute function call since the offset is changed.
                int realOffset = unchecked((int)(BitConverter.ToUInt32(code, 1) + 5 + (uint)offset));
                IntPtr goAddr = realOffset >= 0 ? (hookSourceAddr + realOffset) : (hookSourceAddr - Math.Abs(realOffset));

                ms.Write(new byte[] { 0x50 }); // push rax
                ms.Write(new byte[] { 0x50 }); // push rax
                ms.Write(new byte[] { 0x50 }); // push rax
                ms.Write(new byte[] { 0x48, 0xB8 }); ms.Write(goAddr.ToInt64()); // mov rax, funcAddr
                ms.Write(new byte[] { 0x48, 0x89, 0x44, 0x24, 0x08 }); // mov [rsp+8], rax
                ms.Write(new byte[] { 0x48, 0xB8 }); long tempBackPos = ms.BaseStream.Position; ms.Write((long)0); // mov rax, retAddr
                ms.Write(new byte[] { 0x48, 0x89, 0x44, 0x24, 0x10 }); // mov [rsp+0x10], rax
                ms.Write(new byte[] { 0x58 }); // pop rax
                ms.Write(new byte[] { 0xC3 }); // ret

                tempBack.Add(new KeyValuePair<long, long>(tempBackPos, ms.BaseStream.Position));
                code = code.Skip(5).ToArray();
                if (code.Length > 0)
                    WriteConvertedCode(code, ms, hookSourceAddr, offset + 5, tempBack);
                return;
            }
            
            // Regular code.
            ms.Write(code);
        }

        /// <summary>
        /// Includes the specified code when entering CLR and invoking action.
        /// </summary>
        /// <param name="code">The code.</param>
        /// <param name="hookSourceAddr">The source address where the included code begins.</param>
        /// <param name="target">Target where we jump after.</param>
        /// <returns></returns>
        internal protected IntPtr Include(byte[] code, IntPtr hookSourceAddr, IntPtr target)
        {
            if (target == IntPtr.Zero)
                throw new ArgumentOutOfRangeException("target");

            bool empty = code == null || code.Length == 0;
            if (empty && EmptyInclude != IntPtr.Zero)
                return EmptyInclude;

            // Used for temporary offsets.
            var tempBack = new List<KeyValuePair<long, long>>();

            using (MemoryStream stream = new MemoryStream(128))
            {
                using (BinaryWriter ms = new BinaryWriter(stream))
                {
                    // Original code.
                    if (code != null && code.Length > 0)
                        WriteConvertedCode(code, ms, hookSourceAddr, 0, tempBack);

                    if (Main.Is64Bit)
                    {
                        ms.Write(new byte[] { 0x51 }); // push rcx
                        ms.Write(new byte[] { 0x48, 0xB9 }); ms.Write(target.ToInt64()); // mov rcx, includeReturn
                        ms.Write(new byte[] { 0xFF, 0xE1 }); // jmp rcx
                    }
                    else
                        throw new NotImplementedException();
                }

                code = stream.ToArray();
            }

            var alloc = Memory.Allocate(code.Length + 0x10, 0, true);
            alloc.Pin();

            Memory.WriteBytes(alloc.Address, code);

            foreach (var x in tempBack)
            {
                if (Main.Is64Bit)
                {
                    IntPtr afterAddr = alloc.Address + (int)x.Value;
                    byte[] afterBytes = BitConverter.GetBytes(afterAddr.ToInt64());
                    Memory.WriteBytes(alloc.Address + (int)x.Key, afterBytes);
                }
                else
                    throw new NotImplementedException();
            }
            
            return alloc.Address;
        }

        /// <summary>
        /// The empty code cave.
        /// </summary>
        internal IntPtr EmptyInclude
        {
            get;
            set;
        } = IntPtr.Zero;

        #endregion
        
        #region Imports

        [DllImport("NetScriptFramework.Runtime.dll")]
        internal protected static extern int GetTLSIndex();

        [DllImport("NetScriptFramework.Runtime.dll")]
        internal protected static extern int GetHookMaxCalls();

        [DllImport("NetScriptFramework.Runtime.dll")]
        internal protected static extern int GetHookContextSize();

        [DllImport("NetScriptFramework.Runtime.dll")]
        internal protected static extern IntPtr GetHookIntegrityFailed();

        [DllImport("NetScriptFramework.Runtime.dll")]
        internal protected static extern IntPtr GetHookAllocateFail();

        [DllImport("NetScriptFramework.Runtime.dll")]
        internal protected static extern IntPtr GetDoActionAddress();

        [DllImport("NetScriptFramework.Runtime.dll")]
        internal protected static extern IntPtr GetRtlCaptureContextAddress();

        [DllImport("NetScriptFramework.Runtime.dll")]
        internal protected static extern IntPtr GetRtlRestoreContextAddress();

        [DllImport("NetScriptFramework.Runtime.dll")]
        internal protected static extern int GetMemoryInfo(IntPtr address, IntPtr resultBegin, IntPtr resultEnd, IntPtr moduleBase);

        #endregion
        
        /// <summary>
        /// Builds the hook.
        /// </summary>
        /// <param name="hookSourceBase">The hook source base.</param>
        /// <param name="hookReplaceLength">Length of the hook replace.</param>
        /// <param name="hookIncludeBase">The hook include base.</param>
        /// <param name="hookIncludeLength">Length of the hook include.</param>
        /// <param name="isLongJump">Is this long jump or short.</param>
        /// <param name="target">The target.</param>
        /// <param name="include1">The include1.</param>
        /// <param name="include2">The include2.</param>
        internal abstract void BuildHook(IntPtr hookSourceBase, int hookReplaceLength, IntPtr hookIncludeBase, int hookIncludeLength, bool isLongJump, ref IntPtr target, ref IntPtr include1, ref IntPtr include2);

        /// <summary>
        /// Contains information about a near jump setup.
        /// </summary>
        internal sealed class ModuleNearJumpHook
        {
            /// <summary>
            /// Initializes a new instance of the <see cref="ModuleNearJumpHook"/> class.
            /// </summary>
            /// <param name="moduleBase">The module base.</param>
            /// <param name="beginAddress">The begin address.</param>
            /// <param name="endAddress">The end address.</param>
            internal ModuleNearJumpHook(IntPtr moduleBase, IntPtr beginAddress, IntPtr endAddress)
            {
                this.ModuleBase = moduleBase;
                this.BeginAddress = beginAddress;
                this.EndAddress = endAddress;
            }

            /// <summary>
            /// The module base where this hook is in.
            /// </summary>
            internal readonly IntPtr ModuleBase;

            /// <summary>
            /// The begin address that can reach this jump.
            /// </summary>
            internal readonly IntPtr BeginAddress;

            /// <summary>
            /// The end address that can reach this jump.
            /// </summary>
            internal readonly IntPtr EndAddress;

            /// <summary>
            /// The target of what we must rel-call to use this jump.
            /// </summary>
            internal IntPtr Target;

            /// <summary>
            /// Determines whether this setup contains the specified address.
            /// </summary>
            /// <param name="address">The address.</param>
            /// <returns></returns>
            /// <exception cref="System.InvalidOperationException"></exception>
            internal bool Contains(IntPtr address)
            {
                if(Main.Is64Bit)
                {
                    ulong b = this.BeginAddress.ToUInt64();
                    ulong e = this.EndAddress.ToUInt64();
                    ulong v = address.ToUInt64();
                    return v >= b && v < e;
                }
                else
                {
                    throw new InvalidOperationException();
                }
            }
        }
    }

    /// <summary>
    /// Helper class for hooking before assembly code.
    /// </summary>
    /// <seealso cref="NetScriptFramework.Tools._Internal.HookBase" />
    internal sealed class HookBefore : HookBase
    {
        /// <summary>
        /// Prevents a default instance of the <see cref="HookBefore"/> class from being created.
        /// </summary>
        private HookBefore()
        {
            // Setup the entry point.
            {
                byte[] data = null;

                // [stack+0x08] = hook_source + (5/13)
                // [stack+0x00] = rcx
                if (Main.Is64Bit)
                {
                    using (MemoryStream stream = new MemoryStream())
                    {
                        using (BinaryWriter ms = new BinaryWriter(stream))
                        {
                            int psize = 8;

                            ms.Write(new byte[] { 0x50 }); // push rax
                            ms.Write(new byte[] { 0x52 }); // push rdx

                            int tls = GetTLSIndex();
                            ms.Write(new byte[] { 0x48, 0xB9 }); ms.Write((long)tls); // mov rcx, TlsIndex
                            if (tls < 0x40)
                                ms.Write(new byte[] { 0x65, 0x48, 0x8B, 0x04, 0xCD, 0x80, 0x14, 0x00, 0x00 }); // mov rax, gs:[rcx*8 + 0x1480]
                            else
                            {
                                ms.Write(new byte[] { 0x65, 0x48, 0x8B, 0x04, 0x25, 0x80, 0x17, 0x00, 0x00 }); // mov rax, gs:0x1780
                                ms.Write(new byte[] { 0x48, 0x8B, 0x84, 0xC8, 0x00, 0xFE, 0xFF, 0xFF }); // mov rax, [rax+rcx*8-0x200]
                            }

                            ms.Write(new byte[] { 0x9C }); // pushfq
                            {
                                ms.Write(new byte[] { 0x48, 0x89, 0xC1 }); // mov rcx, rax
                                ms.Write(new byte[] { 0x48, 0x8B, 0x01 }); // mov rax, [rcx]
                                ms.Write(new byte[] { 0x48, 0x3D }); ms.Write((int)GetHookMaxCalls()); // cmp rax, HOOK_MAX_CALLS
                                ms.Write(new byte[] { 0x7C, 0x14 }); // jl +14 (AllocateOk)
                                ms.Write(new byte[] { 0x48, 0x83, 0xE4, 0xF0 }); // and rsp, 0xFFFFFFFFFFFFFFF0
                                ms.Write(new byte[] { 0x48, 0x83, 0xEC, 0x20 }); // sub rsp, 0x20
                                ms.Write(new byte[] { 0x48, 0xB8 }); ms.Write((long)GetHookAllocateFail().ToInt64()); // mov rax, HookContextAllocateFail
                                ms.Write(new byte[] { 0xFF, 0xD0 }); // call rax
                                                                     // AllocateOk:
                                ms.Write(new byte[] { 0x48, 0xFF, 0x01 }); // inc qword ptr [rcx]
                                ms.Write(new byte[] { 0x48, 0x69, 0xC0 }); ms.Write((int)GetHookContextSize()); // imul rax, HOOK_CONTEXT_SIZE
                                ms.Write(new byte[] { 0x48, 0x8B, 0x49, 0x08 }); // mov rcx, [rcx+8]
                                ms.Write(new byte[] { 0x48, 0x01, 0xC1 }); // add rcx, rax
                            }
                            {
                                ms.Write(new byte[] { 0x48, 0x89, 0xC8 }); // mov rax, rcx
                                ms.Write(new byte[] { 0x48, 0x05 }); ms.Write((int)GetHookContextSize()); // add rax, HOOK_CONTEXT_SIZE
                                ms.Write(new byte[] { 0x48, 0x83, 0xE8, (byte)(psize * 2) }); // sub rax, p*2
                                ms.Write(new byte[] { 0x48, 0x8B, 0x54, 0x24, 0x20 }); // mov rdx, [rsp+0x20] (hook_source + x)
                                ms.Write(new byte[] { 0x48, 0x89, 0x10 }); // mov [rax], rdx
                                ms.Write(new byte[] { 0x48, 0x83, 0xE8, (byte)(psize * 2) }); // sub rax, p*2
                                ms.Write(new byte[] { 0x48, 0x8B, 0x54, 0x24, 0x18 }); // mov rdx, [rsp+0x18] (rcx)
                                ms.Write(new byte[] { 0x48, 0x89, 0x10 }); // mov [rax], rdx
                                ms.Write(new byte[] { 0x48, 0x83, 0xE8, (byte)(psize * 1) }); // sub rax, p*1
                                ms.Write(new byte[] { 0x48, 0x8B, 0x54, 0x24, 0x10 }); // mov rdx, [rsp+0x10] (rax)
                                ms.Write(new byte[] { 0x48, 0x89, 0x10 }); // mov [rax], rdx
                                ms.Write(new byte[] { 0x48, 0x83, 0xE8, (byte)(psize * 1) }); // sub rax, p*1
                                ms.Write(new byte[] { 0x48, 0x8B, 0x54, 0x24, 0x20 }); // mov rdx, [rsp+0x20] (hook_source + x)
                                ms.Write(new byte[] { 0x48, 0x89, 0x10 }); // mov [rax], rdx
                            }
                            ms.Write(new byte[] { 0x9D }); // popfq

                            ms.Write(new byte[] { 0x5A }); // pop rdx
                            ms.Write(new byte[] { 0x58 }); // pop rax
                            ms.Write(new byte[] { 0x58 }); // pop rax
                            ms.Write(new byte[] { 0x58 }); // pop rax

                            ms.Write(new byte[] { 0x48, 0xB8 }); ms.Write((long)GetRtlCaptureContextAddress().ToInt64()); // mov rax, RtlCaptureContext
                            ms.Write(new byte[] { 0xFF, 0xD0 }); // call rax
                            ms.Write(new byte[] { 0x48, 0x83, 0xE4, 0xF0 }); // and rsp, 0xFFFFFFFFFFFFFFF0
                            ms.Write(new byte[] { 0x48, 0x83, 0xEC, 0x20 }); // sub rsp, 0x20
                            ms.Write(new byte[] { 0x48, 0xB8 }); ms.Write((long)GetDoActionAddress().ToInt64()); // mov rax, NetHook
                            ms.Write(new byte[] { 0xB2, (byte)0 }); // mov dl, pass
                            ms.Write(new byte[] { 0xFF, 0xD0 }); // call rax
                            ms.Write(new byte[] { 0x48, 0x89, 0xC1 }); // mov rcx, rax
                            ms.Write(new byte[] { 0x48, 0x31, 0xD2 }); // xor rdx, rdx
                            ms.Write(new byte[] { 0x48, 0xB8 }); ms.Write((long)GetRtlRestoreContextAddress().ToInt64()); // mov rax, RtlRestoreContext
                            ms.Write(new byte[] { 0xFF, 0xD0 }); // call rax

                            data = stream.ToArray();
                        }
                    }
                }
                else
                    throw new NotImplementedException();

                var alloc_do = Memory.Allocate(data.Length + 0x10, 0, true);
                alloc_do.Pin();
                this._Address_EnterHook = alloc_do.Address;
                Memory.WriteBytes(this._Address_EnterHook, data);
            }

            // Setup what happens after included code.
            {
                byte[] data = null;

                // [stack+0x00] = rcx
                if (Main.Is64Bit)
                {
                    using (MemoryStream stream = new MemoryStream())
                    {
                        using (BinaryWriter ms = new BinaryWriter(stream))
                        {
                            int psize = 8;

                            ms.Write(new byte[] { 0x50 }); // push rax
                            ms.Write(new byte[] { 0x52 }); // push rdx

                            ms.Write(new byte[] { 0x9C }); // pushfq
                            {
                                int tls = GetTLSIndex();
                                ms.Write(new byte[] { 0x48, 0xB9 }); ms.Write((long)tls); // mov rcx, TlsIndex
                                if (tls < 0x40)
                                    ms.Write(new byte[] { 0x65, 0x48, 0x8B, 0x04, 0xCD, 0x80, 0x14, 0x00, 0x00 }); // mov rax, gs:[rcx*8 + 0x1480]
                                else
                                {
                                    ms.Write(new byte[] { 0x65, 0x48, 0x8B, 0x04, 0x25, 0x80, 0x17, 0x00, 0x00 }); // mov rax, gs:0x1780
                                    ms.Write(new byte[] { 0x48, 0x8B, 0x84, 0xC8, 0x00, 0xFE, 0xFF, 0xFF }); // mov rax, [rax+rcx*8-0x200]
                                }
                                ms.Write(new byte[] { 0x48, 0x89, 0xC1 }); // mov rcx, rax

                                ms.Write(new byte[] { 0x48, 0x8B, 0x01 }); // mov rax, [rcx]
                                ms.Write(new byte[] { 0x48, 0xFF, 0xC8 }); // dec rax
                                ms.Write(new byte[] { 0x48, 0x89, 0x01 }); // mov [rcx], rax
                                ms.Write(new byte[] { 0x48, 0x89, 0xC2 }); // mov rdx, rax
                                ms.Write(new byte[] { 0x48, 0x69, 0xD2 }); ms.Write((int)GetHookContextSize()); // imul rdx, HOOK_CONTEXT_SIZE
                                ms.Write(new byte[] { 0x48, 0x8B, 0x49, 0x08 }); // mov rcx, [rcx+8]
                                ms.Write(new byte[] { 0x48, 0x01, 0xD1 }); // add rcx, rdx
                                ms.Write(new byte[] { 0x48, 0x81, 0xC1 }); ms.Write((int)(GetHookContextSize() - psize * 1)); // add rcx, HOOK_CONTEXT_SIZE - p*1
                                ms.Write(new byte[] { 0x48, 0x8B, 0x11 }); // mov rdx, [rcx]
                                ms.Write(new byte[] { 0x48, 0x39, 0xC2 }); // cmp rdx, rax
                                ms.Write(new byte[] { 0x74, 0x14 }); // je +14 (PostHookVerifyPass)
                                ms.Write(new byte[] { 0x48, 0x83, 0xE4, 0xF0 }); // and rsp, 0xFFFFFFFFFFFFFFF0
                                ms.Write(new byte[] { 0x48, 0x83, 0xEC, 0x20 }); // sub rsp, 0x20
                                ms.Write(new byte[] { 0x48, 0xB8 }); ms.Write((long)GetHookIntegrityFailed().ToInt64()); // mov rax, PostHookVerifyFail
                                ms.Write(new byte[] { 0xFF, 0xD0 }); // call rax
                                                                     // PostHookVerifyPass:
                                ms.Write(new byte[] { 0x48, 0x83, 0xE9, (byte)(psize * 1) }); // sub rcx, 8
                                ms.Write(new byte[] { 0x48, 0x8B, 0x09 }); // mov rcx, [rcx]
                            }
                            ms.Write(new byte[] { 0x9D }); // popfq

                            ms.Write(new byte[] { 0x5A }); // pop rdx
                            ms.Write(new byte[] { 0x58 }); // pop rax

                            ms.Write(new byte[] { 0x48, 0x87, 0x0C, 0x24 }); // xchg [rsp], rcx
                            ms.Write(new byte[] { 0xC3 }); // ret

                            data = stream.ToArray();
                        }
                    }
                }
                else
                    throw new NotImplementedException();

                var alloc_do = Memory.Allocate(data.Length + 0x10, 0, true);
                alloc_do.Pin();
                this._Address_PostInclude = alloc_do.Address;
                Memory.WriteBytes(this._Address_PostInclude, data);
            }

            this.EmptyInclude = this.Include(null, IntPtr.Zero, this._Address_PostInclude);
        }

        /// <summary>
        /// Builds the hook.
        /// </summary>
        /// <param name="hookSourceBase">The hook source base.</param>
        /// <param name="hookReplaceLength">Length of the hook replace.</param>
        /// <param name="hookIncludeBase">The hook include base.</param>
        /// <param name="hookIncludeLength">Length of the hook include.</param>
        /// <param name="isLongJump">Is this long jump or short.</param>
        /// <param name="target">The target.</param>
        /// <param name="include1">The include1.</param>
        /// <param name="include2">The include2.</param>
        internal override void BuildHook(IntPtr hookSourceBase, int hookReplaceLength, IntPtr hookIncludeBase, int hookIncludeLength, bool isLongJump, ref IntPtr target, ref IntPtr include1, ref IntPtr include2)
        {
            if (isLongJump)
                target = this.GetFarHookAddress(hookSourceBase);
            else
                target = this.GetNearHookAddress(hookSourceBase);

            include1 = this.Include(hookIncludeLength > 0 ? Memory.ReadBytes(hookIncludeBase, hookIncludeLength) : null, hookIncludeBase, this._Address_PostInclude);
        }

        /// <summary>
        /// Compares the bytes.
        /// </summary>
        /// <param name="data">The data.</param>
        /// <param name="pattern">The pattern.</param>
        /// <param name="index">The index.</param>
        /// <returns></returns>
        private static bool CompareBytes(byte[] data, byte[] pattern, int index)
        {
            for (int i = 0; i < pattern.Length; i++, index++)
            {
                if (pattern[i] != data[index])
                    return false;
            }

            return true;
        }

        /// <summary>
        /// Gets the near hook address.
        /// </summary>
        /// <param name="hookAddress">The hook address (source).</param>
        /// <returns></returns>
        /// <exception cref="NetScriptFramework.MemoryAccessException"></exception>
        /// <exception cref="System.InvalidOperationException">
        /// Not a valid code page!
        /// or
        /// Not a valid module!
        /// or
        /// Code section was not found!
        /// or
        /// Unhandled error occurred ( + result + )!
        /// or
        /// Didn't find a code cave for near jump setup!
        /// </exception>
        private IntPtr GetNearHookAddress(IntPtr hookAddress)
        {
            if (!Main.Is64Bit)
                return GetFarHookAddress(hookAddress);

            var ls = this._Address_NearJumpSetup;
            for (int i = 0; i < ls.Count; i++)
            {
                var section = ls[i];
                if (section.Contains(hookAddress))
                    return section.Target;
            }

            ModuleNearJumpHook info = null;
            using (var alloc = Memory.Allocate(0x30))
            {
                int result = GetMemoryInfo(hookAddress, alloc.Address, alloc.Address + 0x10, alloc.Address + 0x20);
                if (result == 1)
                    throw new MemoryAccessException(hookAddress);

                if (result == 2)
                    throw new InvalidOperationException("Not a valid code page!");

                if (result == 3)
                    throw new InvalidOperationException("Not a valid module!");

                if (result == -1)
                    throw new InvalidOperationException("Code section was not found!");

                if (result != 0)
                    throw new InvalidOperationException("Unhandled error occurred (" + result + ")!");

                info = new ModuleNearJumpHook(Memory.ReadPointer(alloc.Address + 0x20), Memory.ReadPointer(alloc.Address), Memory.ReadPointer(alloc.Address + 0x10));
            }

            ulong begin = info.BeginAddress.ToUInt64();
            ulong end = info.EndAddress.ToUInt64();
            ulong ptr = begin;
            byte[] pattern = new byte[14] { 0xC3, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC };
            IntPtr found = IntPtr.Zero;
            bool stop = false;

            while (ptr < end && !stop)
            {
                ulong size = end - ptr;
                ulong maxSize = 4000 + (ulong)pattern.Length;
                if (size > maxSize)
                    size = maxSize;
                else
                    stop = true;

                IntPtr addr = new IntPtr(unchecked((long)ptr));
                byte[] chunk = Memory.ReadBytes(addr, (int)size);

                int highIndex = chunk.Length - pattern.Length;
                for (int i = 0; i < highIndex; i++)
                {
                    if (CompareBytes(chunk, pattern, i))
                    {
                        found = addr + i;
                        stop = true;
                        break;
                    }
                }

                if (!stop)
                    ptr += maxSize - (ulong)pattern.Length;
            }

            if (found == IntPtr.Zero)
                throw new InvalidOperationException("Didn't find a code cave for near jump setup!");

            // ret was part of the pattern so skip 1 byte to skip it.
            found = found + 1;

            // Bad.
            if (this._Address_EnterHook == IntPtr.Zero)
                throw new InvalidOperationException("Trying to get hook target without setting up the hook entry point!");

            // Set up preparation code.
            {
                byte[] data = null;
                using (MemoryStream stream = new MemoryStream())
                {
                    using (BinaryWriter ms = new BinaryWriter(stream))
                    {
                        ms.Write(new byte[] { 0x51 }); // push rcx
                        ms.Write(new byte[] { 0x48, 0xB9 }); ms.Write(this._Address_EnterHook.ToInt64()); // mov rcx, EnterHook
                        ms.Write(new byte[] { 0xFF, 0xE1 }); // jmp rcx

                        data = stream.ToArray();
                    }
                }

                if (data.Length > pattern.Length - 1)
                    throw new InvalidOperationException("Failed to write near jump code! Not enough memory in specified code cave.");

                Memory.WriteBytes(found, data, true);
            }

            info.Target = found;
            this._Address_NearJumpSetup.Add(info);
            return info.Target;
        }

        /// <summary>
        /// Gets the far hook address.
        /// </summary>
        /// <param name="hookAddress">The hook address (source).</param>
        /// <returns></returns>
        private IntPtr GetFarHookAddress(IntPtr hookAddress)
        {
            // Bad.
            if (this._Address_EnterHook == IntPtr.Zero)
                throw new InvalidOperationException("Trying to get hook target without setting up the hook entry point!");

            // Must setup.
            if (this._Address_FarJumpSetup == IntPtr.Zero)
            {
                byte[] data = null;

                if (Main.Is64Bit)
                {
                    using (MemoryStream stream = new MemoryStream())
                    {
                        using (BinaryWriter ms = new BinaryWriter(stream))
                        {
                            ms.Write(new byte[] { 0x59 }); // pop rcx
                            ms.Write(new byte[] { 0x48, 0x87, 0x0C, 0x24 }); // xchg [rsp], rcx
                            ms.Write(new byte[] { 0x51 }); // push rcx
                            ms.Write(new byte[] { 0x48, 0xB9 }); ms.Write(this._Address_EnterHook.ToInt64()); // mov rcx, EnterHook
                            ms.Write(new byte[] { 0xFF, 0xE1 }); // jmp rcx

                            data = stream.ToArray();
                        }
                    }
                }
                else
                    throw new NotImplementedException();

                var alloc_do = Memory.Allocate(data.Length + 0x10, 0, true);
                alloc_do.Pin();
                this._Address_FarJumpSetup = alloc_do.Address;
                Memory.WriteBytes(this._Address_FarJumpSetup, data);
            }

            return this._Address_FarJumpSetup;
        }

        /// <summary>
        /// The address for when we land from a far-jump.
        /// </summary>
        private IntPtr _Address_FarJumpSetup = IntPtr.Zero;

        /// <summary>
        /// The address for actually entering the hook.
        /// </summary>
        private IntPtr _Address_EnterHook = IntPtr.Zero;

        /// <summary>
        /// The address for what comes after included code has run.
        /// </summary>
        private IntPtr _Address_PostInclude = IntPtr.Zero;

        /// <summary>
        /// The addresses for near jump setups.
        /// </summary>
        private List<ModuleNearJumpHook> _Address_NearJumpSetup = new List<ModuleNearJumpHook>();

        /// <summary>
        /// The instance of this type of hook setup.
        /// </summary>
        internal static readonly HookBefore Instance = new HookBefore();
    }

    /// <summary>
    /// Helper class for hooking after assembly code.
    /// </summary>
    /// <seealso cref="NetScriptFramework.Tools._Internal.HookBase" />
    internal sealed class HookAfter : HookBase
    {
        /// <summary>
        /// Prevents a default instance of the <see cref="HookAfter"/> class from being created.
        /// </summary>
        private HookAfter()
        {
            // Setup what happens after included code.
            {
                byte[] data = null;

                // nothing on stack
                if (Main.Is64Bit)
                {
                    using (MemoryStream stream = new MemoryStream())
                    {
                        using (BinaryWriter ms = new BinaryWriter(stream))
                        {
                            int psize = 8;

                            ms.Write(new byte[] { 0x51 }); // push rcx

                            ms.Write(new byte[] { 0x50 }); // push rax
                            ms.Write(new byte[] { 0x52 }); // push rdx

                            ms.Write(new byte[] { 0x9C }); // pushfq
                            {
                                int tls = GetTLSIndex();
                                ms.Write(new byte[] { 0x48, 0xB9 }); ms.Write((long)tls); // mov rcx, TlsIndex
                                if (tls < 0x40)
                                    ms.Write(new byte[] { 0x65, 0x48, 0x8B, 0x04, 0xCD, 0x80, 0x14, 0x00, 0x00 }); // mov rax, gs:[rcx*8 + 0x1480]
                                else
                                {
                                    ms.Write(new byte[] { 0x65, 0x48, 0x8B, 0x04, 0x25, 0x80, 0x17, 0x00, 0x00 }); // mov rax, gs:0x1780
                                    ms.Write(new byte[] { 0x48, 0x8B, 0x84, 0xC8, 0x00, 0xFE, 0xFF, 0xFF }); // mov rax, [rax+rcx*8-0x200]
                                }
                                ms.Write(new byte[] { 0x48, 0x89, 0xC1 }); // mov rcx, rax

                                ms.Write(new byte[] { 0x48, 0x8B, 0x01 }); // mov rax, [rcx]
                                ms.Write(new byte[] { 0x48, 0xFF, 0xC8 }); // dec rax
                                ms.Write(new byte[] { 0x48, 0x89, 0x01 }); // mov [rcx], rax
                                ms.Write(new byte[] { 0x48, 0x89, 0xC2 }); // mov rdx, rax
                                ms.Write(new byte[] { 0x48, 0x69, 0xD2 }); ms.Write((int)GetHookContextSize()); // imul rdx, HOOK_CONTEXT_SIZE
                                ms.Write(new byte[] { 0x48, 0x8B, 0x49, 0x08 }); // mov rcx, [rcx+8]
                                ms.Write(new byte[] { 0x48, 0x01, 0xD1 }); // add rcx, rdx
                                ms.Write(new byte[] { 0x48, 0x81, 0xC1 }); ms.Write((int)(GetHookContextSize() - psize * 1)); // add rcx, HOOK_CONTEXT_SIZE - p*1
                                ms.Write(new byte[] { 0x48, 0x8B, 0x11 }); // mov rdx, [rcx]
                                ms.Write(new byte[] { 0x48, 0x39, 0xC2 }); // cmp rdx, rax
                                ms.Write(new byte[] { 0x74, 0x14 }); // je +14 (PostHookVerifyPass)
                                ms.Write(new byte[] { 0x48, 0x83, 0xE4, 0xF0 }); // and rsp, 0xFFFFFFFFFFFFFFF0
                                ms.Write(new byte[] { 0x48, 0x83, 0xEC, 0x20 }); // sub rsp, 0x20
                                ms.Write(new byte[] { 0x48, 0xB8 }); ms.Write((long)GetHookIntegrityFailed().ToInt64()); // mov rax, PostHookVerifyFail
                                ms.Write(new byte[] { 0xFF, 0xD0 }); // call rax
                                // PostHookVerifyPass:
                                ms.Write(new byte[] { 0x48, 0x83, 0xE9, (byte)(psize * 1) }); // sub rcx, p*1
                                ms.Write(new byte[] { 0x48, 0x8B, 0x09 }); // mov rcx, [rcx]
                            }
                            ms.Write(new byte[] { 0x9D }); // popfq

                            ms.Write(new byte[] { 0x5A }); // pop rdx
                            ms.Write(new byte[] { 0x58 }); // pop rax

                            ms.Write(new byte[] { 0x48, 0x87, 0x0C, 0x24 }); // xchg [rsp], rcx
                            ms.Write(new byte[] { 0xC3 }); // ret

                            data = stream.ToArray();
                        }
                    }
                }
                else
                    throw new NotImplementedException();

                var alloc_do = Memory.Allocate(data.Length + 0x10, 0, true);
                alloc_do.Pin();
                this._Address_PostInclude = alloc_do.Address;
                Memory.WriteBytes(this._Address_PostInclude, data);
            }
        }

        /// <summary>
        /// Builds the hook.
        /// </summary>
        /// <param name="hookSourceBase">The hook source base.</param>
        /// <param name="hookReplaceLength">Length of the hook replace.</param>
        /// <param name="hookIncludeBase">The hook include base.</param>
        /// <param name="hookIncludeLength">Length of the hook include.</param>
        /// <param name="isLongJump">Is this long jump or short.</param>
        /// <param name="target">The target.</param>
        /// <param name="include1">The include1.</param>
        /// <param name="include2">The include2.</param>
        /// <exception cref="System.NotImplementedException"></exception>
        internal override void BuildHook(IntPtr hookSourceBase, int hookReplaceLength, IntPtr hookIncludeBase, int hookIncludeLength, bool isLongJump, ref IntPtr target, ref IntPtr include1, ref IntPtr include2)
        {
            byte[] data = null;

            // Used for temporary offsets.
            var tempBack = new List<KeyValuePair<long, long>>();

            // [stack+0x08] = hook_source + (5/13)
            // [stack+0x00] = rcx
            if (Main.Is64Bit)
            {
                using (MemoryStream stream = new MemoryStream())
                {
                    using (BinaryWriter ms = new BinaryWriter(stream))
                    {
                        int psize = 8;

                        ms.Write(new byte[] { 0x50 }); // push rax
                        ms.Write(new byte[] { 0x52 }); // push rdx

                        int tls = GetTLSIndex();
                        ms.Write(new byte[] { 0x48, 0xB9 }); ms.Write((long)tls); // mov rcx, TlsIndex
                        if (tls < 0x40)
                            ms.Write(new byte[] { 0x65, 0x48, 0x8B, 0x04, 0xCD, 0x80, 0x14, 0x00, 0x00 }); // mov rax, gs:[rcx*8 + 0x1480]
                        else
                        {
                            ms.Write(new byte[] { 0x65, 0x48, 0x8B, 0x04, 0x25, 0x80, 0x17, 0x00, 0x00 }); // mov rax, gs:0x1780
                            ms.Write(new byte[] { 0x48, 0x8B, 0x84, 0xC8, 0x00, 0xFE, 0xFF, 0xFF }); // mov rax, [rax+rcx*8-0x200]
                        }

                        ms.Write(new byte[] { 0x9C }); // pushfq
                        {
                            ms.Write(new byte[] { 0x48, 0x89, 0xC1 }); // mov rcx, rax
                            ms.Write(new byte[] { 0x48, 0x8B, 0x01 }); // mov rax, [rcx]
                            ms.Write(new byte[] { 0x48, 0x3D }); ms.Write((int)GetHookMaxCalls()); // cmp rax, HOOK_MAX_CALLS
                            ms.Write(new byte[] { 0x7C, 0x14 }); // jl +14 (AllocateOk)
                            ms.Write(new byte[] { 0x48, 0x83, 0xE4, 0xF0 }); // and rsp, 0xFFFFFFFFFFFFFFF0
                            ms.Write(new byte[] { 0x48, 0x83, 0xEC, 0x20 }); // sub rsp, 0x20
                            ms.Write(new byte[] { 0x48, 0xB8 }); ms.Write((long)GetHookAllocateFail().ToInt64()); // mov rax, HookContextAllocateFail
                            ms.Write(new byte[] { 0xFF, 0xD0 }); // call rax
                                                                 // AllocateOk:
                            ms.Write(new byte[] { 0x48, 0xFF, 0x01 }); // inc qword ptr [rcx]
                            ms.Write(new byte[] { 0x48, 0x69, 0xC0 }); ms.Write((int)GetHookContextSize()); // imul rax, HOOK_CONTEXT_SIZE
                            ms.Write(new byte[] { 0x48, 0x8B, 0x49, 0x08 }); // mov rcx, [rcx+8]
                            ms.Write(new byte[] { 0x48, 0x01, 0xC1 }); // add rcx, rax
                        }
                        {
                            ms.Write(new byte[] { 0x48, 0x89, 0xC8 }); // mov rax, rcx
                            ms.Write(new byte[] { 0x48, 0x05 }); ms.Write((int)GetHookContextSize()); // add rax, HOOK_CONTEXT_SIZE
                            ms.Write(new byte[] { 0x48, 0x83, 0xE8, (byte)(psize * 2) }); // sub rax, p*2
                            ms.Write(new byte[] { 0x48, 0x8B, 0x54, 0x24, 0x20 }); // mov rdx, [rsp+0x20] (hook_source + x)
                            ms.Write(new byte[] { 0x48, 0x89, 0x10 }); // mov [rax], rdx
                            ms.Write(new byte[] { 0x48, 0x83, 0xE8, (byte)(psize * 4) }); // sub rax, p*4
                            ms.Write(new byte[] { 0x48, 0x89, 0x10 }); // mov [rax], rdx
                        }
                        ms.Write(new byte[] { 0x9D }); // popfq

                        ms.Write(new byte[] { 0x5A }); // pop rdx
                        ms.Write(new byte[] { 0x58 }); // pop rax
                        ms.Write(new byte[] { 0x59 }); // pop rcx
                        ms.Write(new byte[] { 0x48, 0x87, 0x0C, 0x24 }); // xchg [rsp], rcx
                        ms.Write(new byte[] { 0x59 }); // pop rcx

                        // Include
                        byte[] code = hookIncludeLength > 0 ? Memory.ReadBytes(hookIncludeBase, hookIncludeLength) : null;
                        if (code != null && code.Length != 0)
                            WriteConvertedCode(code, ms, hookIncludeBase, 0, tempBack);

                        ms.Write(new byte[] { 0x51 }); // push rcx
                        ms.Write(new byte[] { 0x51 }); // push rcx
                        ms.Write(new byte[] { 0x50 }); // push rax
                        ms.Write(new byte[] { 0x52 }); // push rdx

                        tls = GetTLSIndex();
                        ms.Write(new byte[] { 0x48, 0xB9 }); ms.Write((long)tls); // mov rcx, TlsIndex
                        if (tls < 0x40)
                            ms.Write(new byte[] { 0x65, 0x48, 0x8B, 0x04, 0xCD, 0x80, 0x14, 0x00, 0x00 }); // mov rax, gs:[rcx*8 + 0x1480]
                        else
                        {
                            ms.Write(new byte[] { 0x65, 0x48, 0x8B, 0x04, 0x25, 0x80, 0x17, 0x00, 0x00 }); // mov rax, gs:0x1780
                            ms.Write(new byte[] { 0x48, 0x8B, 0x84, 0xC8, 0x00, 0xFE, 0xFF, 0xFF }); // mov rax, [rax+rcx*8-0x200]
                        }

                        ms.Write(new byte[] { 0x9C }); // pushfq
                        {
                            ms.Write(new byte[] { 0x48, 0x89, 0xC1 }); // mov rcx, rax
                            ms.Write(new byte[] { 0x48, 0x8B, 0x01 }); // mov rax, [rcx]
                            ms.Write(new byte[] { 0x48, 0xFF, 0xC8 }); // dec rax
                            ms.Write(new byte[] { 0x48, 0x69, 0xC0 }); ms.Write((int)GetHookContextSize()); // imul rax, HOOK_CONTEXT_SIZE
                            ms.Write(new byte[] { 0x48, 0x8B, 0x49, 0x08 }); // mov rcx, [rcx+8]
                            ms.Write(new byte[] { 0x48, 0x01, 0xC1 }); // add rcx, rax
                        }
                        {
                            ms.Write(new byte[] { 0x48, 0x89, 0xC8 }); // mov rax, rcx
                            ms.Write(new byte[] { 0x48, 0x05 }); ms.Write((int)GetHookContextSize()); // add rax, HOOK_CONTEXT_SIZE
                            ms.Write(new byte[] { 0x48, 0x83, 0xE8, (byte)(psize * 4) }); // sub rax, p*4
                            ms.Write(new byte[] { 0x48, 0x8B, 0x54, 0x24, 0x18 }); // mov rdx, [rsp+0x18] (rcx)
                            ms.Write(new byte[] { 0x48, 0x89, 0x10 }); // mov [rax], rdx
                            ms.Write(new byte[] { 0x48, 0x83, 0xE8, (byte)(psize * 1) }); // sub rax, p*1
                            ms.Write(new byte[] { 0x48, 0x8B, 0x54, 0x24, 0x10 }); // mov rdx, [rsp+0x10] (rax)
                            ms.Write(new byte[] { 0x48, 0x89, 0x10 }); // mov [rax], rdx
                        }
                        ms.Write(new byte[] { 0x9D }); // popfq

                        ms.Write(new byte[] { 0x5A }); // pop rdx
                        ms.Write(new byte[] { 0x58 }); // pop rax
                        ms.Write(new byte[] { 0x58 }); // pop rax
                        ms.Write(new byte[] { 0x58 }); // pop rax

                        ms.Write(new byte[] { 0x48, 0xB8 }); ms.Write((long)GetRtlCaptureContextAddress().ToInt64()); // mov rax, RtlCaptureContext
                        ms.Write(new byte[] { 0xFF, 0xD0 }); // call rax
                        ms.Write(new byte[] { 0x48, 0x83, 0xE4, 0xF0 }); // and rsp, 0xFFFFFFFFFFFFFFF0
                        ms.Write(new byte[] { 0x48, 0x83, 0xEC, 0x20 }); // sub rsp, 0x20
                        ms.Write(new byte[] { 0x48, 0xB8 }); ms.Write((long)GetDoActionAddress().ToInt64()); // mov rax, NetHook
                        ms.Write(new byte[] { 0xB2, (byte)1 }); // mov dl, pass
                        ms.Write(new byte[] { 0xFF, 0xD0 }); // call rax
                        ms.Write(new byte[] { 0x48, 0x89, 0xC1 }); // mov rcx, rax
                        ms.Write(new byte[] { 0x48, 0x31, 0xD2 }); // xor rdx, rdx
                        ms.Write(new byte[] { 0x48, 0xB8 }); ms.Write((long)GetRtlRestoreContextAddress().ToInt64()); // mov rax, RtlRestoreContext
                        ms.Write(new byte[] { 0xFF, 0xD0 }); // call rax

                        data = stream.ToArray();
                    }
                }
            }
            else
                throw new NotImplementedException();

            var alloc_do = Memory.Allocate(data.Length + 0x10, 0, true);
            alloc_do.Pin();
            Memory.WriteBytes(alloc_do.Address, data);

            foreach (var x in tempBack)
            {
                if (Main.Is64Bit)
                {
                    IntPtr afterAddr = alloc_do.Address + (int)x.Value;
                    byte[] afterBytes = BitConverter.GetBytes(afterAddr.ToInt64());
                    Memory.WriteBytes(alloc_do.Address + (int)x.Key, afterBytes);
                }
                else
                    throw new NotImplementedException();
            }

            if (isLongJump)
                target = this.GetFarHookAddress(hookSourceBase, alloc_do.Address);
            else
                target = this.GetNearHookAddress(hookSourceBase, alloc_do.Address);
            include2 = this._Address_PostInclude;
        }

        /// <summary>
        /// Compares the bytes.
        /// </summary>
        /// <param name="data">The data.</param>
        /// <param name="pattern">The pattern.</param>
        /// <param name="index">The index.</param>
        /// <returns></returns>
        private static bool CompareBytes(byte[] data, byte[] pattern, int index)
        {
            for (int i = 0; i < pattern.Length; i++, index++)
            {
                if (pattern[i] != data[index])
                    return false;
            }

            return true;
        }

        /// <summary>
        /// Gets the near hook address.
        /// </summary>
        /// <param name="hookAddress">The hook address (source).</param>
        /// <param name="targetAddress">The target address.</param>
        /// <returns></returns>
        /// <exception cref="MemoryAccessException"></exception>
        /// <exception cref="System.InvalidOperationException">Not a valid code page!
        /// or
        /// Not a valid module!
        /// or
        /// Code section was not found!
        /// or
        /// Unhandled error occurred ( + result + )!
        /// or
        /// Didn't find a code cave for near jump setup!</exception>
        /// <exception cref="System.ArgumentOutOfRangeException"></exception>
        /// <exception cref="NetScriptFramework.MemoryAccessException"></exception>
        private IntPtr GetNearHookAddress(IntPtr hookAddress, IntPtr targetAddress)
        {
            if (!Main.Is64Bit)
                return this.GetFarHookAddress(hookAddress, targetAddress);

            ModuleNearJumpHook info = null;
            using (var alloc = Memory.Allocate(0x30))
            {
                int result = GetMemoryInfo(hookAddress, alloc.Address, alloc.Address + 0x10, alloc.Address + 0x20);
                if (result == 1)
                    throw new MemoryAccessException(hookAddress);

                if (result == 2)
                    throw new InvalidOperationException("Not a valid code page!");

                if (result == 3)
                    throw new InvalidOperationException("Not a valid module!");

                if (result == -1)
                    throw new InvalidOperationException("Code section was not found!");

                if (result != 0)
                    throw new InvalidOperationException("Unhandled error occurred (" + result + ")!");

                info = new ModuleNearJumpHook(Memory.ReadPointer(alloc.Address + 0x20), Memory.ReadPointer(alloc.Address), Memory.ReadPointer(alloc.Address + 0x10));
            }

            ulong begin = info.BeginAddress.ToUInt64();
            ulong end = info.EndAddress.ToUInt64();
            ulong ptr = begin;
            byte[] pattern = new byte[14] { 0xC3, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC };
            IntPtr found = IntPtr.Zero;
            bool stop = false;

            while (ptr < end && !stop)
            {
                ulong size = end - ptr;
                ulong maxSize = 4000 + (ulong)pattern.Length;
                if (size > maxSize)
                    size = maxSize;
                else
                    stop = true;

                IntPtr addr = new IntPtr(unchecked((long)ptr));
                byte[] chunk = Memory.ReadBytes(addr, (int)size);

                int highIndex = chunk.Length - pattern.Length;
                for (int i = 0; i < highIndex; i++)
                {
                    if (CompareBytes(chunk, pattern, i))
                    {
                        found = addr + i;
                        stop = true;
                        break;
                    }
                }

                if (!stop)
                    ptr += maxSize - (ulong)pattern.Length;
            }

            if (found == IntPtr.Zero)
                throw new InvalidOperationException("Didn't find a code cave for near jump setup!");

            // ret was part of the pattern so skip 1 byte to skip it.
            found = found + 1;

            // Bad.
            if (targetAddress == IntPtr.Zero)
                throw new ArgumentOutOfRangeException();

            // Set up preparation code.
            {
                byte[] data = null;
                using (MemoryStream stream = new MemoryStream())
                {
                    using (BinaryWriter ms = new BinaryWriter(stream))
                    {
                        ms.Write(new byte[] { 0x51 }); // push rcx
                        ms.Write(new byte[] { 0x48, 0xB9 }); ms.Write(targetAddress.ToInt64()); // mov rcx, target
                        ms.Write(new byte[] { 0xFF, 0xE1 }); // jmp rcx

                        data = stream.ToArray();
                    }
                }

                if (data.Length > pattern.Length - 1)
                    throw new InvalidOperationException("Failed to write near jump code! Not enough memory in specified code cave.");

                Memory.WriteBytes(found, data, true);
            }

            info.Target = found;
            return info.Target;
        }

        /// <summary>
        /// Gets the far hook address.
        /// </summary>
        /// <param name="hookAddress">The hook address (source).</param>
        /// <param name="targetAddress">The target address.</param>
        /// <returns></returns>
        private IntPtr GetFarHookAddress(IntPtr hookAddress, IntPtr targetAddress)
        {
            // Bad.
            if (targetAddress == IntPtr.Zero)
                throw new ArgumentOutOfRangeException();

            // Must setup.
            byte[] data = null;

            if (Main.Is64Bit)
            {
                using (MemoryStream stream = new MemoryStream())
                {
                    using (BinaryWriter ms = new BinaryWriter(stream))
                    {
                        ms.Write(new byte[] { 0x59 }); // pop rcx
                        ms.Write(new byte[] { 0x48, 0x87, 0x0C, 0x24 }); // xchg [rsp], rcx
                        ms.Write(new byte[] { 0x51 }); // push rcx
                        ms.Write(new byte[] { 0x48, 0xB9 }); ms.Write(targetAddress.ToInt64()); // mov rcx, target
                        ms.Write(new byte[] { 0xFF, 0xE1 }); // jmp rcx

                        data = stream.ToArray();
                    }
                }
            }
            else
                throw new NotImplementedException();

            var alloc_do = Memory.Allocate(data.Length + 0x10, 0, true);
            alloc_do.Pin();
            Memory.WriteBytes(alloc_do.Address, data);
            return alloc_do.Address;
        }

        /// <summary>
        /// The address for what comes after included code has run.
        /// </summary>
        private IntPtr _Address_PostInclude = IntPtr.Zero;

        /// <summary>
        /// The instance of this type of hook setup.
        /// </summary>
        internal static readonly HookAfter Instance = new HookAfter();
    }

    /// <summary>
    /// Helper class for hooking both before and after assembly code.
    /// </summary>
    /// <seealso cref="NetScriptFramework.Tools._Internal.HookBase" />
    internal sealed class HookBoth : HookBase
    {
        /// <summary>
        /// Prevents a default instance of the <see cref="HookBoth"/> class from being created.
        /// </summary>
        private HookBoth()
        {
            // Setup the entry point.
            {
                byte[] data = null;

                // [stack+0x08] = hook_source + (5/13)
                // [stack+0x00] = rcx
                if (Main.Is64Bit)
                {
                    using (MemoryStream stream = new MemoryStream())
                    {
                        using (BinaryWriter ms = new BinaryWriter(stream))
                        {
                            int psize = 8;

                            ms.Write(new byte[] { 0x50 }); // push rax
                            ms.Write(new byte[] { 0x52 }); // push rdx

                            int tls = GetTLSIndex();
                            ms.Write(new byte[] { 0x48, 0xB9 }); ms.Write((long)tls); // mov rcx, TlsIndex
                            if (tls < 0x40)
                                ms.Write(new byte[] { 0x65, 0x48, 0x8B, 0x04, 0xCD, 0x80, 0x14, 0x00, 0x00 }); // mov rax, gs:[rcx*8 + 0x1480]
                            else
                            {
                                ms.Write(new byte[] { 0x65, 0x48, 0x8B, 0x04, 0x25, 0x80, 0x17, 0x00, 0x00 }); // mov rax, gs:0x1780
                                ms.Write(new byte[] { 0x48, 0x8B, 0x84, 0xC8, 0x00, 0xFE, 0xFF, 0xFF }); // mov rax, [rax+rcx*8-0x200]
                            }

                            ms.Write(new byte[] { 0x9C }); // pushfq
                            {
                                ms.Write(new byte[] { 0x48, 0x89, 0xC1 }); // mov rcx, rax
                                ms.Write(new byte[] { 0x48, 0x8B, 0x01 }); // mov rax, [rcx]
                                ms.Write(new byte[] { 0x48, 0x3D }); ms.Write((int)GetHookMaxCalls()); // cmp rax, HOOK_MAX_CALLS
                                ms.Write(new byte[] { 0x7C, 0x14 }); // jl +14 (AllocateOk)
                                ms.Write(new byte[] { 0x48, 0x83, 0xE4, 0xF0 }); // and rsp, 0xFFFFFFFFFFFFFFF0
                                ms.Write(new byte[] { 0x48, 0x83, 0xEC, 0x20 }); // sub rsp, 0x20
                                ms.Write(new byte[] { 0x48, 0xB8 }); ms.Write((long)GetHookAllocateFail().ToInt64()); // mov rax, HookContextAllocateFail
                                ms.Write(new byte[] { 0xFF, 0xD0 }); // call rax
                                // AllocateOk:
                                ms.Write(new byte[] { 0x48, 0xFF, 0x01 }); // inc qword ptr [rcx]
                                ms.Write(new byte[] { 0x48, 0x69, 0xC0 }); ms.Write((int)GetHookContextSize()); // imul rax, HOOK_CONTEXT_SIZE
                                ms.Write(new byte[] { 0x48, 0x8B, 0x49, 0x08 }); // mov rcx, [rcx+8]
                                ms.Write(new byte[] { 0x48, 0x01, 0xC1 }); // add rcx, rax
                            }
                            {
                                ms.Write(new byte[] { 0x48, 0x89, 0xC8 }); // mov rax, rcx
                                ms.Write(new byte[] { 0x48, 0x05 }); ms.Write((int)GetHookContextSize()); // add rax, HOOK_CONTEXT_SIZE
                                ms.Write(new byte[] { 0x48, 0x83, 0xE8, (byte)(psize * 2) }); // sub rax, p*2
                                ms.Write(new byte[] { 0x48, 0x8B, 0x54, 0x24, 0x20 }); // mov rdx, [rsp+0x20] (hook_source + x)
                                ms.Write(new byte[] { 0x48, 0x89, 0x10 }); // mov [rax], rdx
                                ms.Write(new byte[] { 0x48, 0x83, 0xE8, (byte)(psize * 2) }); // sub rax, p*2
                                ms.Write(new byte[] { 0x48, 0x8B, 0x54, 0x24, 0x18 }); // mov rdx, [rsp+0x18] (rcx)
                                ms.Write(new byte[] { 0x48, 0x89, 0x10 }); // mov [rax], rdx
                                ms.Write(new byte[] { 0x48, 0x83, 0xE8, (byte)(psize * 1) }); // sub rax, p*1
                                ms.Write(new byte[] { 0x48, 0x8B, 0x54, 0x24, 0x10 }); // mov rdx, [rsp+0x10] (rax)
                                ms.Write(new byte[] { 0x48, 0x89, 0x10 }); // mov [rax], rdx
                                ms.Write(new byte[] { 0x48, 0x83, 0xE8, (byte)(psize * 1) }); // sub rax, p*1
                                ms.Write(new byte[] { 0x48, 0x8B, 0x54, 0x24, 0x20 }); // mov rdx, [rsp+0x20] (hook_source + x)
                                ms.Write(new byte[] { 0x48, 0x89, 0x10 }); // mov [rax], rdx
                            }
                            ms.Write(new byte[] { 0x9D }); // popfq

                            ms.Write(new byte[] { 0x5A }); // pop rdx
                            ms.Write(new byte[] { 0x58 }); // pop rax
                            ms.Write(new byte[] { 0x58 }); // pop rax
                            ms.Write(new byte[] { 0x58 }); // pop rax

                            ms.Write(new byte[] { 0x48, 0xB8 }); ms.Write((long)GetRtlCaptureContextAddress().ToInt64()); // mov rax, RtlCaptureContext
                            ms.Write(new byte[] { 0xFF, 0xD0 }); // call rax
                            ms.Write(new byte[] { 0x48, 0x83, 0xE4, 0xF0 }); // and rsp, 0xFFFFFFFFFFFFFFF0
                            ms.Write(new byte[] { 0x48, 0x83, 0xEC, 0x20 }); // sub rsp, 0x20
                            ms.Write(new byte[] { 0x48, 0xB8 }); ms.Write((long)GetDoActionAddress().ToInt64()); // mov rax, NetHook
                            ms.Write(new byte[] { 0xB2, (byte)0 }); // mov dl, pass
                            ms.Write(new byte[] { 0xFF, 0xD0 }); // call rax
                            ms.Write(new byte[] { 0x48, 0x89, 0xC1 }); // mov rcx, rax
                            ms.Write(new byte[] { 0x48, 0x31, 0xD2 }); // xor rdx, rdx
                            ms.Write(new byte[] { 0x48, 0xB8 }); ms.Write((long)GetRtlRestoreContextAddress().ToInt64()); // mov rax, RtlRestoreContext
                            ms.Write(new byte[] { 0xFF, 0xD0 }); // call rax

                            data = stream.ToArray();
                        }
                    }
                }
                else
                    throw new NotImplementedException();

                var alloc_do = Memory.Allocate(data.Length + 0x10, 0, true);
                alloc_do.Pin();
                this._Address_EnterHook = alloc_do.Address;
                Memory.WriteBytes(this._Address_EnterHook, data);
            }

            // Setup what happens after included code.
            {
                byte[] data = null;

                // [stack+0x00] = rcx
                if (Main.Is64Bit)
                {
                    using (MemoryStream stream = new MemoryStream())
                    {
                        using (BinaryWriter ms = new BinaryWriter(stream))
                        {
                            int psize = 8;

                            ms.Write(new byte[] { 0x48, 0x8B, 0x0C, 0x24 }); // mov rcx, [rsp]
                            ms.Write(new byte[] { 0x51 }); // push rcx
                            ms.Write(new byte[] { 0x50 }); // push rax
                            ms.Write(new byte[] { 0x52 }); // push rdx

                            ms.Write(new byte[] { 0x9C }); // pushfq
                            {
                                int tls = GetTLSIndex();
                                ms.Write(new byte[] { 0x48, 0xB9 }); ms.Write((long)tls); // mov rcx, TlsIndex
                                if (tls < 0x40)
                                    ms.Write(new byte[] { 0x65, 0x48, 0x8B, 0x04, 0xCD, 0x80, 0x14, 0x00, 0x00 }); // mov rax, gs:[rcx*8 + 0x1480]
                                else
                                {
                                    ms.Write(new byte[] { 0x65, 0x48, 0x8B, 0x04, 0x25, 0x80, 0x17, 0x00, 0x00 }); // mov rax, gs:0x1780
                                    ms.Write(new byte[] { 0x48, 0x8B, 0x84, 0xC8, 0x00, 0xFE, 0xFF, 0xFF }); // mov rax, [rax+rcx*8-0x200]
                                }
                                ms.Write(new byte[] { 0x48, 0x89, 0xC1 }); // mov rcx, rax

                                ms.Write(new byte[] { 0x48, 0x8B, 0x01 }); // mov rax, [rcx]
                                ms.Write(new byte[] { 0x48, 0xFF, 0xC8 }); // dec rax
                                ms.Write(new byte[] { 0x48, 0x89, 0xC2 }); // mov rdx, rax
                                ms.Write(new byte[] { 0x48, 0x69, 0xD2 }); ms.Write((int)GetHookContextSize()); // imul rdx, HOOK_CONTEXT_SIZE
                                ms.Write(new byte[] { 0x48, 0x8B, 0x49, 0x08 }); // mov rcx, [rcx+8]
                                ms.Write(new byte[] { 0x48, 0x01, 0xD1 }); // add rcx, rdx

                                ms.Write(new byte[] { 0x48, 0x89, 0xC8 }); // mov rax, rcx
                                ms.Write(new byte[] { 0x48, 0x05 }); ms.Write((int)GetHookContextSize()); // add rax, HOOK_CONTEXT_SIZE
                                ms.Write(new byte[] { 0x48, 0x83, 0xE8, (byte)(psize * 4) }); // sub rax, p*4
                                ms.Write(new byte[] { 0x48, 0x8B, 0x54, 0x24, 0x18 }); // mov rdx, [rsp+0x18] (rcx)
                                ms.Write(new byte[] { 0x48, 0x89, 0x10 }); // mov [rax], rdx
                                ms.Write(new byte[] { 0x48, 0x83, 0xE8, (byte)(psize * 1) }); // sub rax, p*1
                                ms.Write(new byte[] { 0x48, 0x8B, 0x54, 0x24, 0x10 }); // mov rdx, [rsp+0x10] (rax)
                                ms.Write(new byte[] { 0x48, 0x89, 0x10 }); // mov [rax], rdx
                            }
                            ms.Write(new byte[] { 0x9D }); // popfq

                            ms.Write(new byte[] { 0x5A }); // pop rdx
                            ms.Write(new byte[] { 0x58 }); // pop rax
                            ms.Write(new byte[] { 0x58 }); // pop rax
                            ms.Write(new byte[] { 0x58 }); // pop rax

                            ms.Write(new byte[] { 0x48, 0xB8 }); ms.Write((long)GetRtlCaptureContextAddress().ToInt64()); // mov rax, RtlCaptureContext
                            ms.Write(new byte[] { 0xFF, 0xD0 }); // call rax
                            ms.Write(new byte[] { 0x48, 0x83, 0xE4, 0xF0 }); // and rsp, 0xFFFFFFFFFFFFFFF0
                            ms.Write(new byte[] { 0x48, 0x83, 0xEC, 0x20 }); // sub rsp, 0x20
                            ms.Write(new byte[] { 0x48, 0xB8 }); ms.Write((long)GetDoActionAddress().ToInt64()); // mov rax, NetHook
                            ms.Write(new byte[] { 0xB2, (byte)1 }); // mov dl, pass
                            ms.Write(new byte[] { 0xFF, 0xD0 }); // call rax
                            ms.Write(new byte[] { 0x48, 0x89, 0xC1 }); // mov rcx, rax
                            ms.Write(new byte[] { 0x48, 0x31, 0xD2 }); // xor rdx, rdx
                            ms.Write(new byte[] { 0x48, 0xB8 }); ms.Write((long)GetRtlRestoreContextAddress().ToInt64()); // mov rax, RtlRestoreContext
                            ms.Write(new byte[] { 0xFF, 0xD0 }); // call rax

                            data = stream.ToArray();
                        }
                    }
                }
                else
                    throw new NotImplementedException();

                var alloc_do = Memory.Allocate(data.Length + 0x10, 0, true);
                alloc_do.Pin();
                this._Address_PostInclude = alloc_do.Address;
                Memory.WriteBytes(this._Address_PostInclude, data);
            }

            // Setup what happens after second code.
            {
                byte[] data = null;

                // nothing on stack
                if (Main.Is64Bit)
                {
                    using (MemoryStream stream = new MemoryStream())
                    {
                        using (BinaryWriter ms = new BinaryWriter(stream))
                        {
                            int psize = 8;

                            ms.Write(new byte[] { 0x51 }); // push rcx
                            ms.Write(new byte[] { 0x50 }); // push rax
                            ms.Write(new byte[] { 0x52 }); // push rdx

                            ms.Write(new byte[] { 0x9C }); // pushfq
                            {
                                int tls = GetTLSIndex();
                                ms.Write(new byte[] { 0x48, 0xB9 }); ms.Write((long)tls); // mov rcx, TlsIndex
                                if (tls < 0x40)
                                    ms.Write(new byte[] { 0x65, 0x48, 0x8B, 0x04, 0xCD, 0x80, 0x14, 0x00, 0x00 }); // mov rax, gs:[rcx*8 + 0x1480]
                                else
                                {
                                    ms.Write(new byte[] { 0x65, 0x48, 0x8B, 0x04, 0x25, 0x80, 0x17, 0x00, 0x00 }); // mov rax, gs:0x1780
                                    ms.Write(new byte[] { 0x48, 0x8B, 0x84, 0xC8, 0x00, 0xFE, 0xFF, 0xFF }); // mov rax, [rax+rcx*8-0x200]
                                }
                                ms.Write(new byte[] { 0x48, 0x89, 0xC1 }); // mov rcx, rax

                                ms.Write(new byte[] { 0x48, 0x8B, 0x01 }); // mov rax, [rcx]
                                ms.Write(new byte[] { 0x48, 0xFF, 0xC8 }); // dec rax
                                ms.Write(new byte[] { 0x48, 0x89, 0x01 }); // mov [rcx], rax
                                ms.Write(new byte[] { 0x48, 0x89, 0xC2 }); // mov rdx, rax
                                ms.Write(new byte[] { 0x48, 0x69, 0xD2 }); ms.Write((int)GetHookContextSize()); // imul rdx, HOOK_CONTEXT_SIZE
                                ms.Write(new byte[] { 0x48, 0x8B, 0x49, 0x08 }); // mov rcx, [rcx+8]
                                ms.Write(new byte[] { 0x48, 0x01, 0xD1 }); // add rcx, rdx
                                ms.Write(new byte[] { 0x48, 0x81, 0xC1 }); ms.Write((int)(GetHookContextSize() - psize * 1)); // add rcx, HOOK_CONTEXT_SIZE - p*1
                                ms.Write(new byte[] { 0x48, 0x8B, 0x11 }); // mov rdx, [rcx]
                                ms.Write(new byte[] { 0x48, 0x39, 0xC2 }); // cmp rdx, rax
                                ms.Write(new byte[] { 0x74, 0x14 }); // je +14 (PostHookVerifyPass)
                                ms.Write(new byte[] { 0x48, 0x83, 0xE4, 0xF0 }); // and rsp, 0xFFFFFFFFFFFFFFF0
                                ms.Write(new byte[] { 0x48, 0x83, 0xEC, 0x20 }); // sub rsp, 0x20
                                ms.Write(new byte[] { 0x48, 0xB8 }); ms.Write((long)GetHookIntegrityFailed().ToInt64()); // mov rax, PostHookVerifyFail
                                ms.Write(new byte[] { 0xFF, 0xD0 }); // call rax
                                                                     // PostHookVerifyPass:
                                ms.Write(new byte[] { 0x48, 0x83, 0xE9, (byte)(psize * 1) }); // sub rcx, 8
                                ms.Write(new byte[] { 0x48, 0x8B, 0x09 }); // mov rcx, [rcx]
                            }
                            ms.Write(new byte[] { 0x9D }); // popfq

                            ms.Write(new byte[] { 0x5A }); // pop rdx
                            ms.Write(new byte[] { 0x58 }); // pop rax

                            ms.Write(new byte[] { 0x48, 0x87, 0x0C, 0x24 }); // xchg [rsp], rcx
                            ms.Write(new byte[] { 0xC3 }); // ret

                            data = stream.ToArray();
                        }
                    }
                }
                else
                    throw new NotImplementedException();

                var alloc_do = Memory.Allocate(data.Length + 0x10, 0, true);
                alloc_do.Pin();
                this._Address_PostInclude2 = alloc_do.Address;
                Memory.WriteBytes(this._Address_PostInclude2, data);
            }

            this.EmptyInclude = this.Include(null, IntPtr.Zero, this._Address_PostInclude);
        }

        /// <summary>
        /// Builds the hook.
        /// </summary>
        /// <param name="hookSourceBase">The hook source base.</param>
        /// <param name="hookReplaceLength">Length of the hook replace.</param>
        /// <param name="hookIncludeBase">The hook include base.</param>
        /// <param name="hookIncludeLength">Length of the hook include.</param>
        /// <param name="isLongJump">Is this long jump or short.</param>
        /// <param name="target">The target.</param>
        /// <param name="include1">The include1.</param>
        /// <param name="include2">The include2.</param>
        internal override void BuildHook(IntPtr hookSourceBase, int hookReplaceLength, IntPtr hookIncludeBase, int hookIncludeLength, bool isLongJump, ref IntPtr target, ref IntPtr include1, ref IntPtr include2)
        {
            if (isLongJump)
                target = this.GetFarHookAddress(hookSourceBase);
            else
                target = this.GetNearHookAddress(hookSourceBase);

            include1 = this.Include(hookIncludeLength > 0 ? Memory.ReadBytes(hookIncludeBase, hookIncludeLength) : null, hookIncludeBase, this._Address_PostInclude);
            include2 = this._Address_PostInclude2;
        }

        /// <summary>
        /// Compares the bytes.
        /// </summary>
        /// <param name="data">The data.</param>
        /// <param name="pattern">The pattern.</param>
        /// <param name="index">The index.</param>
        /// <returns></returns>
        private static bool CompareBytes(byte[] data, byte[] pattern, int index)
        {
            for (int i = 0; i < pattern.Length; i++, index++)
            {
                if (pattern[i] != data[index])
                    return false;
            }

            return true;
        }

        /// <summary>
        /// Gets the near hook address.
        /// </summary>
        /// <param name="hookAddress">The hook address (source).</param>
        /// <returns></returns>
        /// <exception cref="NetScriptFramework.MemoryAccessException"></exception>
        /// <exception cref="System.InvalidOperationException">
        /// Not a valid code page!
        /// or
        /// Not a valid module!
        /// or
        /// Code section was not found!
        /// or
        /// Unhandled error occurred ( + result + )!
        /// or
        /// Didn't find a code cave for near jump setup!
        /// </exception>
        private IntPtr GetNearHookAddress(IntPtr hookAddress)
        {
            if (!Main.Is64Bit)
                return GetFarHookAddress(hookAddress);

            var ls = this._Address_NearJumpSetup;
            for (int i = 0; i < ls.Count; i++)
            {
                var section = ls[i];
                if (section.Contains(hookAddress))
                    return section.Target;
            }

            ModuleNearJumpHook info = null;
            using (var alloc = Memory.Allocate(0x30))
            {
                int result = GetMemoryInfo(hookAddress, alloc.Address, alloc.Address + 0x10, alloc.Address + 0x20);
                if (result == 1)
                    throw new MemoryAccessException(hookAddress);

                if (result == 2)
                    throw new InvalidOperationException("Not a valid code page!");

                if (result == 3)
                    throw new InvalidOperationException("Not a valid module!");

                if (result == -1)
                    throw new InvalidOperationException("Code section was not found!");

                if (result != 0)
                    throw new InvalidOperationException("Unhandled error occurred (" + result + ")!");

                info = new ModuleNearJumpHook(Memory.ReadPointer(alloc.Address + 0x20), Memory.ReadPointer(alloc.Address), Memory.ReadPointer(alloc.Address + 0x10));
            }

            ulong begin = info.BeginAddress.ToUInt64();
            ulong end = info.EndAddress.ToUInt64();
            ulong ptr = begin;
            byte[] pattern = new byte[14] { 0xC3, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC };
            IntPtr found = IntPtr.Zero;
            bool stop = false;

            while (ptr < end && !stop)
            {
                ulong size = end - ptr;
                ulong maxSize = 4000 + (ulong)pattern.Length;
                if (size > maxSize)
                    size = maxSize;
                else
                    stop = true;

                IntPtr addr = new IntPtr(unchecked((long)ptr));
                byte[] chunk = Memory.ReadBytes(addr, (int)size);

                int highIndex = chunk.Length - pattern.Length;
                for (int i = 0; i < highIndex; i++)
                {
                    if (CompareBytes(chunk, pattern, i))
                    {
                        found = addr + i;
                        stop = true;
                        break;
                    }
                }

                if (!stop)
                    ptr += maxSize - (ulong)pattern.Length;
            }

            if (found == IntPtr.Zero)
                throw new InvalidOperationException("Didn't find a code cave for near jump setup!");

            // ret was part of the pattern so skip 1 byte to skip it.
            found = found + 1;

            // Bad.
            if (this._Address_EnterHook == IntPtr.Zero)
                throw new InvalidOperationException("Trying to get hook target without setting up the hook entry point!");

            // Set up preparation code.
            {
                byte[] data = null;
                using (MemoryStream stream = new MemoryStream())
                {
                    using (BinaryWriter ms = new BinaryWriter(stream))
                    {
                        ms.Write(new byte[] { 0x51 }); // push rcx
                        ms.Write(new byte[] { 0x48, 0xB9 }); ms.Write(this._Address_EnterHook.ToInt64()); // mov rcx, EnterHook
                        ms.Write(new byte[] { 0xFF, 0xE1 }); // jmp rcx

                        data = stream.ToArray();
                    }
                }

                if (data.Length > pattern.Length - 1)
                    throw new InvalidOperationException("Failed to write near jump code! Not enough memory in specified code cave.");

                Memory.WriteBytes(found, data, true);
            }

            info.Target = found;
            this._Address_NearJumpSetup.Add(info);
            return info.Target;
        }

        /// <summary>
        /// Gets the far hook address.
        /// </summary>
        /// <param name="hookAddress">The hook address (source).</param>
        /// <returns></returns>
        private IntPtr GetFarHookAddress(IntPtr hookAddress)
        {
            // Bad.
            if (this._Address_EnterHook == IntPtr.Zero)
                throw new InvalidOperationException("Trying to get hook target without setting up the hook entry point!");

            // Must setup.
            if (this._Address_FarJumpSetup == IntPtr.Zero)
            {
                byte[] data = null;

                if (Main.Is64Bit)
                {
                    using (MemoryStream stream = new MemoryStream())
                    {
                        using (BinaryWriter ms = new BinaryWriter(stream))
                        {
                            ms.Write(new byte[] { 0x59 }); // pop rcx
                            ms.Write(new byte[] { 0x48, 0x87, 0x0C, 0x24 }); // xchg [rsp], rcx
                            ms.Write(new byte[] { 0x51 }); // push rcx
                            ms.Write(new byte[] { 0x48, 0xB9 }); ms.Write(this._Address_EnterHook.ToInt64()); // mov rcx, EnterHook
                            ms.Write(new byte[] { 0xFF, 0xE1 }); // jmp rcx

                            data = stream.ToArray();
                        }
                    }
                }
                else
                    throw new NotImplementedException();

                var alloc_do = Memory.Allocate(data.Length + 0x10, 0, true);
                alloc_do.Pin();
                this._Address_FarJumpSetup = alloc_do.Address;
                Memory.WriteBytes(this._Address_FarJumpSetup, data);
            }

            return this._Address_FarJumpSetup;
        }

        /// <summary>
        /// The address for when we land from a far-jump.
        /// </summary>
        private IntPtr _Address_FarJumpSetup = IntPtr.Zero;

        /// <summary>
        /// The address for actually entering the hook.
        /// </summary>
        private IntPtr _Address_EnterHook = IntPtr.Zero;

        /// <summary>
        /// The address for what comes after included code has run.
        /// </summary>
        private IntPtr _Address_PostInclude = IntPtr.Zero;

        /// <summary>
        /// The address for what comes after second code has run.
        /// </summary>
        private IntPtr _Address_PostInclude2 = IntPtr.Zero;

        /// <summary>
        /// The addresses for near jump setups.
        /// </summary>
        private List<ModuleNearJumpHook> _Address_NearJumpSetup = new List<ModuleNearJumpHook>();

        /// <summary>
        /// The instance of this type of hook setup.
        /// </summary>
        internal static readonly HookBoth Instance = new HookBoth();
    }

    /*/// <summary>
    /// Performance monitor hook.
    /// </summary>
    /// <seealso cref="NetScriptFramework.Tools._Internal.HookBase" />
    internal sealed class HookPerformance : HookBase
    {
        /// <summary>
        /// Prevents a default instance of the <see cref="HookPerformance"/> class from being created.
        /// </summary>
        private HookPerformance()
        {
            // Setup.
            {
                byte[] data = null;

                // [rsp+0] = called from return address
                if (Main.Is64Bit)
                {
                    using (MemoryStream stream = new MemoryStream())
                    {
                        using (BinaryWriter ms = new BinaryWriter(stream))
                        {
                            int psize = 8;

                            ms.Write(new byte[] { 0x51 }); // push rcx
                            ms.Write(new byte[] { 0x50 }); // push rax
                            ms.Write(new byte[] { 0x52 }); // push rdx

                            ms.Write(new byte[] { 0x9C }); // pushfq
                            {
                                int tls = GetTLSIndex();
                                ms.Write(new byte[] { 0x48, 0xB9 }); ms.Write((long)tls); // mov rcx, TlsIndex
                                if (tls < 0x40)
                                    ms.Write(new byte[] { 0x65, 0x48, 0x8B, 0x04, 0xCD, 0x80, 0x14, 0x00, 0x00 }); // mov rax, gs:[rcx*8 + 0x1480]
                                else
                                {
                                    ms.Write(new byte[] { 0x65, 0x48, 0x8B, 0x04, 0x25, 0x80, 0x17, 0x00, 0x00 }); // mov rax, gs:0x1780
                                    ms.Write(new byte[] { 0x48, 0x8B, 0x84, 0xC8, 0x00, 0xFE, 0xFF, 0xFF }); // mov rax, [rax+rcx*8-0x200]
                                }
                                ms.Write(new byte[] { 0x48, 0x89, 0xC1 }); // mov rcx, rax
                                ms.Write(new byte[] { 0x48, 0x8B, 0x49, (byte)(psize * 3) }); // mov rcx, [rcx+p*3]

                                // pmon base alloc is rcx
                                TODO();
                            }
                            ms.Write(new byte[] { 0x9D }); // popfq

                            ms.Write(new byte[] { 0x5A }); // pop rdx
                            ms.Write(new byte[] { 0x58 }); // pop rax

                            // get correct address to go to from return address, maybe also in TLS
                            TODO();

                            // change the return address to come back here instead of where we were
                            TODO();

                            // jump there without disturbing registers
                            TODO();

                            // get tls again and dec depth, if 0 then add up to total-inclusive, iterate upwards in stack and reduce total-exc for all by the diff, get real return from stack and jump back to continue execution

                            data = stream.ToArray();
                        }
                    }
                }
                else
                    throw new NotImplementedException();

                var alloc_do = Memory.Allocate(data.Length + 0x10, 0, true);
                alloc_do.Pin();
                this._Address_PostInclude2 = alloc_do.Address;
                Memory.WriteBytes(this._Address_PostInclude2, data);
            }
        }

        internal override void BuildHook(IntPtr hookSourceBase, int hookReplaceLength, IntPtr hookIncludeBase, int hookIncludeLength, bool isLongJump, ref IntPtr target, ref IntPtr include1, ref IntPtr include2)
        {
            if (hookReplaceLength != 5 || hookIncludeLength != 5 || isLongJump)
                throw new ArgumentOutOfRangeException();


        }

        /// <summary>
        /// The instance of this type of hook setup.
        /// </summary>
        internal static readonly HookPerformance Instance = new HookPerformance();
    }*/
}
