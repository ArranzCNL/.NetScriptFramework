using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace NetScriptFramework
{
    /// <summary>
    /// Implement helper functions for reading and writing from memory.
    /// </summary>
    public static class Memory
    {
        #region Native functions

        /// <summary>
        /// Invokes a "thiscall" native function.
        /// </summary>
        /// <param name="thisAddress">The address of object instance.</param>
        /// <param name="funcAddress">The function address.</param>
        /// <param name="args">The arguments of function.</param>
        /// <returns></returns>
        public static IntPtr InvokeThisCall(IntPtr thisAddress, IntPtr funcAddress, params InvokeArgument[] args)
        {
            int count = 0;
            IntPtr[] prepared = null;
            if (Main.Is64Bit)
            {
                prepared = PrepareArguments(0, args, thisAddress, ref count);
                return InvokeCdecl(funcAddress, new IntPtr(count), prepared);
            }
            prepared = PrepareArguments(0, args, null, ref count);
            return InvokeThisCall(thisAddress, funcAddress, new IntPtr(count), prepared);
        }

        /// <summary>
        /// Invokes a "thiscall" native function that returns a floating point value.
        /// </summary>
        /// <param name="thisAddress">The address of object instance.</param>
        /// <param name="funcAddress">The function address.</param>
        /// <param name="args">The arguments of function.</param>
        /// <returns></returns>
        public static float InvokeThisCallF(IntPtr thisAddress, IntPtr funcAddress, params InvokeArgument[] args)
        {
            int count = 0;
            IntPtr[] prepared = null;
            IntPtr result;
            byte[] converted = null;
            if (Main.Is64Bit)
            {
                prepared = PrepareArguments(1, args, thisAddress, ref count);
                result = InvokeCdeclF(funcAddress, new IntPtr(count), prepared);
                converted = BitConverter.GetBytes(result.ToInt64());
                return BitConverter.ToSingle(converted, 0);
            }
            prepared = PrepareArguments(1, args, null, ref count);
            result = InvokeThisCallF(thisAddress, funcAddress, new IntPtr(count), prepared);
            converted = BitConverter.GetBytes(result.ToInt32());
            return BitConverter.ToSingle(converted, 0);
        }

        /// <summary>
        /// Invokes a "thiscall" native function that returns a double value.
        /// </summary>
        /// <param name="thisAddress">The address of object instance.</param>
        /// <param name="funcAddress">The function address.</param>
        /// <param name="args">The arguments of function.</param>
        /// <returns></returns>
        public static double InvokeThisCallD(IntPtr thisAddress, IntPtr funcAddress, params InvokeArgument[] args)
        {
            int count = 0;
            IntPtr[] prepared = null;
            IntPtr result;
            byte[] converted = null;
            if (Main.Is64Bit)
            {
                prepared = PrepareArguments(2, args, thisAddress, ref count);
                result = InvokeCdeclD(funcAddress, new IntPtr(count), prepared);
                converted = BitConverter.GetBytes(result.ToInt64());
                return BitConverter.ToDouble(converted, 0);
            }
            prepared = PrepareArguments(2, args, null, ref count);
            result = InvokeThisCallD(thisAddress, funcAddress, new IntPtr(count), prepared);
            converted = BitConverter.GetBytes(result.ToInt32());
            return BitConverter.ToSingle(converted, 0);
        }

        /// <summary>
        /// Invokes a "stdcall" native function.
        /// </summary>
        /// <param name="funcAddress">The function address.</param>
        /// <param name="args">The arguments of function.</param>
        /// <returns></returns>
        public static IntPtr InvokeStdCall(IntPtr funcAddress, params InvokeArgument[] args)
        {
            if (Main.Is64Bit)
                return InvokeCdecl(funcAddress, args);
            int count = 0;
            var prepared = PrepareArguments(0, args, null, ref count);
            return InvokeStdCall(funcAddress, new IntPtr(count), prepared);
        }

        /// <summary>
        /// Invokes a "stdcall" native function that returns a floating point value.
        /// </summary>
        /// <param name="funcAddress">The function address.</param>
        /// <param name="args">The arguments of function.</param>
        /// <returns></returns>
        public static float InvokeStdCallF(IntPtr funcAddress, params InvokeArgument[] args)
        {
            if (Main.Is64Bit)
                return InvokeCdeclF(funcAddress, args);
            int count = 0;
            var prepared = PrepareArguments(1, args, null, ref count);
            var result = InvokeStdCallF(funcAddress, new IntPtr(count), prepared);
            byte[] converted = BitConverter.GetBytes(result.ToInt32());
            return BitConverter.ToSingle(converted, 0);
        }

        /// <summary>
        /// Invokes a "stdcall" native function that returns a floating point value.
        /// </summary>
        /// <param name="funcAddress">The function address.</param>
        /// <param name="args">The arguments of function.</param>
        /// <returns></returns>
        public static double InvokeStdCallD(IntPtr funcAddress, params InvokeArgument[] args)
        {
            if (Main.Is64Bit)
                return InvokeCdeclD(funcAddress, args);
            int count = 0;
            var prepared = PrepareArguments(2, args, null, ref count);
            var result = InvokeStdCallD(funcAddress, new IntPtr(count), prepared);
            byte[] converted = BitConverter.GetBytes(result.ToInt32());
            return BitConverter.ToSingle(converted, 0);
        }

        /// <summary>
        /// Invokes a "cdecl" native function. For x64 this is also used for "fastcall".
        /// </summary>
        /// <param name="funcAddress">The function address.</param>
        /// <param name="args">The arguments of function.</param>
        /// <returns></returns>
        public static IntPtr InvokeCdecl(IntPtr funcAddress, params InvokeArgument[] args)
        {
            int count = 0;
            var prepared = PrepareArguments(0, args, null, ref count);
            return InvokeCdecl(funcAddress, new IntPtr(count), prepared);
        }

        /// <summary>
        /// Invokes a "cdecl" native function that returns a floating point value. For x64 this is also used for "fastcall".
        /// </summary>
        /// <param name="funcAddress">The function address.</param>
        /// <param name="args">The arguments of function.</param>
        /// <returns></returns>
        public static float InvokeCdeclF(IntPtr funcAddress, params InvokeArgument[] args)
        {
            int count = 0;
            var prepared = PrepareArguments(1, args, null, ref count);
            var result = InvokeCdeclF(funcAddress, new IntPtr(count), prepared);
            if (Main.Is64Bit)
            {
                byte[] converted = BitConverter.GetBytes(result.ToInt64());
                return BitConverter.ToSingle(converted, 0);
            }
            else
            {
                byte[] converted = BitConverter.GetBytes(result.ToInt32());
                return BitConverter.ToSingle(converted, 0);
            }
        }

        /// <summary>
        /// Invokes a "cdecl" native function that returns a floating point value. For x64 this is also used for "fastcall".
        /// </summary>
        /// <param name="funcAddress">The function address.</param>
        /// <param name="args">The arguments of function.</param>
        /// <returns></returns>
        public static double InvokeCdeclD(IntPtr funcAddress, params InvokeArgument[] args)
        {
            int count = 0;
            var prepared = PrepareArguments(2, args, null, ref count);
            var result = InvokeCdeclD(funcAddress, new IntPtr(count), prepared);
            if (Main.Is64Bit)
            {
                byte[] converted = BitConverter.GetBytes(result.ToInt64());
                return BitConverter.ToDouble(converted, 0);
            }
            else
            {
                byte[] converted = BitConverter.GetBytes(result.ToInt32());
                return BitConverter.ToSingle(converted, 0);
            }
        }

        [DllImport("NetScriptFramework.Runtime.dll")]
        internal static extern void IncIgnoreException();

        [DllImport("NetScriptFramework.Runtime.dll")]
        internal static extern void DecIgnoreException();

        [DllImport("NetScriptFramework.Runtime.dll")]
        private static extern IntPtr InvokeThisCall(IntPtr thisAddress, IntPtr funcAddress, IntPtr argCount, IntPtr[] argData);

        [DllImport("NetScriptFramework.Runtime.dll")]
        private static extern IntPtr InvokeStdCall(IntPtr funcAddress, IntPtr argCount, IntPtr[] argData);

        [DllImport("NetScriptFramework.Runtime.dll")]
        private static extern IntPtr InvokeCdecl(IntPtr funcAddress, IntPtr argCount, IntPtr[] argData);

        [DllImport("NetScriptFramework.Runtime.dll")]
        private static extern IntPtr InvokeCdecl_addr();

        [DllImport("NetScriptFramework.Runtime.dll")]
        private static extern IntPtr InvokeThisCallF(IntPtr thisAddress, IntPtr funcAddress, IntPtr argCount, IntPtr[] argData);

        [DllImport("NetScriptFramework.Runtime.dll")]
        private static extern IntPtr InvokeStdCallF(IntPtr funcAddress, IntPtr argCount, IntPtr[] argData);

        [DllImport("NetScriptFramework.Runtime.dll")]
        private static extern IntPtr InvokeThisCallD(IntPtr thisAddress, IntPtr funcAddress, IntPtr argCount, IntPtr[] argData);

        [DllImport("NetScriptFramework.Runtime.dll")]
        private static extern IntPtr InvokeStdCallD(IntPtr funcAddress, IntPtr argCount, IntPtr[] argData);

        [DllImport("NetScriptFramework.Runtime.dll")]
        private static extern IntPtr InvokeCdeclF(IntPtr funcAddress, IntPtr argCount, IntPtr[] argData);

        [DllImport("NetScriptFramework.Runtime.dll")]
        private static extern IntPtr InvokeCdeclF_addr();

        [DllImport("NetScriptFramework.Runtime.dll")]
        private static extern IntPtr InvokeCdeclD(IntPtr funcAddress, IntPtr argCount, IntPtr[] argData);

        [DllImport("NetScriptFramework.Runtime.dll")]
        private static extern IntPtr InvokeCdeclD_addr();

        [DllImport("NetScriptFramework.Runtime.dll")]
        internal static extern void ReadDQFrom(byte[] source, byte[] dest);

        [DllImport("NetScriptFramework.Runtime.dll")]
        internal static extern void WriteDQTo(byte[] source, byte[] dest);

        [DllImport("NetScriptFramework.Runtime.dll")]
        internal static extern void ReadFQFrom(byte[] source, byte[] dest);

        [DllImport("NetScriptFramework.Runtime.dll")]
        internal static extern void WriteFQTo(byte[] source, byte[] dest);

        private static IntPtr _Invoke_Cdecl_address = IntPtr.Zero;
        private static IntPtr _Invoke_CdeclF_address = IntPtr.Zero;
        private static IntPtr _Invoke_CdeclD_address = IntPtr.Zero;

        private static IntPtr[] _Argument_Jmp_Address = null;

        /// <summary>
        /// Prepares the arguments for a native function call.
        /// </summary>
        /// <param name="funcReturnType">The function return value type.</param>
        /// <param name="args">The arguments.</param>
        /// <param name="thisPtr">This pointer if it's thiscall.</param>
        /// <param name="count">Argument count to pass.</param>
        /// <returns></returns>
        /// <exception cref="System.NotImplementedException"></exception>
        private static IntPtr[] PrepareArguments(int funcReturnType, InvokeArgument[] args, IntPtr? thisPtr, ref int count)
        {
            if (args == null)
                args = new InvokeArgument[0];

            // Stack size can't support more.
            if (args.Length >= 32)
                throw new ArgumentOutOfRangeException("Invoke argument count can't exceed 31!"); // Actually can be 32 if thisPtr is not set.

            if (!Main.Is64Bit)
            {
                throw new NotImplementedException();
                /*IntPtr[] result = new IntPtr[args.Length];
                for (int i = 0, j = args.Length - 1; i < args.Length; i++, j--)
                    result[j] = args[i].ValueOther;
                count = args.Length;
                return result;*/
            }
            else if (!thisPtr.HasValue)
            {
                IntPtr[] result = new IntPtr[args.Length * 2];
                for (int i = 0; i < args.Length; i++)
                {
                    var a = args[i];
                    int type = a.ValueType;
                    result[i * 2] = _Argument_Jmp_Address[funcReturnType * 15 + Math.Min(4, i) * 3 + type];
                    switch(type)
                    {
                        case 0: result[i * 2 + 1] = a.ValueOther; break;
                        case 1:
                            {
                                byte[] converted = BitConverter.GetBytes(a.ValueFloat);
                                long converted2 = BitConverter.ToUInt32(converted, 0);
                                result[i * 2 + 1] = new IntPtr(converted2);
                            }
                            break;
                        case 2:
                            {
                                byte[] converted = BitConverter.GetBytes(a.ValueDouble);
                                long converted2 = BitConverter.ToUInt32(converted, 0);
                                result[i * 2 + 1] = new IntPtr(converted2);
                            }
                            break;
                        default: throw new NotImplementedException();
                    }
                }
                count = args.Length;
                return result;
            }
            else
            {
                IntPtr[] result = new IntPtr[(args.Length + 1) * 2];
                result[0] = _Argument_Jmp_Address[funcReturnType * 15];
                result[1] = thisPtr.Value;
                for (int j = 0; j < args.Length; j++)
                {
                    var a = args[j];
                    int type = a.ValueType;
                    int i = j + 1;
                    result[i * 2] = _Argument_Jmp_Address[funcReturnType * 15 + Math.Min(4, i) * 3 + type];
                    switch (type)
                    {
                        case 0: result[i * 2 + 1] = a.ValueOther; break;
                        case 1:
                            {
                                byte[] converted = BitConverter.GetBytes(a.ValueFloat);
                                long converted2 = BitConverter.ToUInt32(converted, 0);
                                result[i * 2 + 1] = new IntPtr(converted2);
                            }
                            break;
                        case 2:
                            {
                                byte[] converted = BitConverter.GetBytes(a.ValueDouble);
                                long converted2 = BitConverter.ToUInt32(converted, 0);
                                result[i * 2 + 1] = new IntPtr(converted2);
                            }
                            break;
                        default: throw new NotImplementedException();
                    }
                }
                count = args.Length + 1;
                return result;
            }
        }

        #endregion

        #region Allocation

        /// <summary>
        /// Allocates memory in current process. Returned value contains information about the allocation, including the base address. If
        /// returned instance is disposed the underlying memory will be freed! Use Pin method on the returned value to avoid the memory
        /// from being freed automatically.
        /// </summary>
        /// <param name="size">The size of memory to allocate.</param>
        /// <param name="align">The alignment of memory. This is ignored if execute parameter is <c>true</c>.</param>
        /// <param name="execute">If set to <c>true</c> then returned memory has read + write + execute access, otherwise it will have only read + write access.
        /// This should be <c>false</c> always unless you plan to execute assembly code in that memory.</param>
        /// <returns></returns>
        /// <exception cref="System.ArgumentOutOfRangeException">
        /// size;Size can't be zero or negative!
        /// or
        /// align;Alignment can't be negative!
        /// or
        /// size
        /// </exception>
        /// <exception cref="System.OutOfMemoryException">Failed to allocate memory using C allocator! Requested size was ...</exception>
        public static MemoryAllocation Allocate(int size, int align = 0, bool execute = false)
        {
            if (size <= 0)
                throw new ArgumentOutOfRangeException("size", "Size can't be zero or negative!");
            if (align < 0)
                throw new ArgumentOutOfRangeException("align", "Alignment can't be negative!");

            if (execute)
            {
                if (size > 1024 * 1024)
                    throw new ArgumentOutOfRangeException("size");

                if (_codePageDefault < 0)
                {
                    //SYSTEM_INFO si;
                    //GetSystemInfo(&si);
                    //_codePageDefault = Math.Max(65536, si.dwAllocationGranularity);
                    _codePageDefault = 65536;
                }

                MemoryAllocation result = null;
                lock (_codePageLocker)
                {
                    for (int i = 0; i < _codePageList.Count; i++)
                    {
                        result = _codePageList[i].Get(size);
                        if (result != null)
                            return result;
                    }

                    CodePageAllocator allocator = new CodePageAllocator(Math.Max(size, _codePageDefault));
                    _codePageList.Add(allocator);

                    result = allocator.Get(size);
                    return result;
                }
            }
            else
            {
                var result = AllocateC(size, align);
                if (result == IntPtr.Zero)
                    throw new OutOfMemoryException("Failed to allocate memory using C allocator! Requested size was " + size + ".");

                return new MemoryAllocation(result, size, align, MemoryAllocation.MemoryAllocationTypes.Heap, null);
            }
        }

        /// <summary>
        /// Allocates a structure. Default values will be zero. Use indexer for easy modification.
        /// </summary>
        /// <param name="size">The size of structure.</param>
        /// <returns></returns>
        /// <exception cref="System.ArgumentOutOfRangeException">size</exception>
        public static Tools.MemoryStruct AllocateStruct(int size)
        {
            if (size < 0)
                throw new ArgumentOutOfRangeException("size");

            var alloc = Memory.Allocate(Math.Max(0x10, size), 0x10);
            var mem = new Tools.MemoryStruct();
            mem.Allocation = alloc;
            mem.Size = size;
            mem.Fields = new ulong[size];
            return mem;
        }

        /// <summary>
        /// Allocates a string into the process memory that can be used by native code. Returned value is the allocation information
        /// including the address. If returned value is disposed the underlying memory is automatically freed! Use Pin method on the return
        /// value to avoid automatically freeing the memory when reference is lost.
        /// </summary>
        /// <param name="text">The text to allocate.</param>
        /// <param name="wide">If set to <c>true</c> then allocate as Unicode (2 bytes per character), otherwise allocate as ANSI (1 byte per character).</param>
        /// <returns></returns>
        /// <exception cref="System.ArgumentNullException">text</exception>
        /// <exception cref="System.InvalidOperationException"></exception>
        public static MemoryAllocation AllocateString(string text, bool wide)
        {
            if (text == null)
                throw new ArgumentNullException("text");

            IntPtr result = wide ? Marshal.StringToHGlobalUni(text) : Marshal.StringToHGlobalAnsi(text);
            if (result == IntPtr.Zero)
                throw new InvalidOperationException();

            return new MemoryAllocation(result, (wide ? 2 : 1) * (text.Length + 1), 0, MemoryAllocation.MemoryAllocationTypes.String, null);
        }

        /// <summary>
        /// Frees the previously allocated string.
        /// </summary>
        /// <param name="address">The address.</param>
        internal static void FreeString(IntPtr address)
        {
            Marshal.FreeHGlobal(address);
        }

        /// <summary>
        /// Frees previously allocated code.
        /// </summary>
        /// <param name="address">The address.</param>
        /// <param name="size">The size.</param>
        /// <param name="page">The page.</param>
        internal static void FreeCode(IntPtr address, int size, CodePageAllocator page)
        {
            lock (_codePageLocker)
            {
                page.Free(address, size);
            }
        }

        [DllImport("NetScriptFramework.Runtime.dll")]
        internal static extern IntPtr AllocateC(int size, int align);

        [DllImport("NetScriptFramework.Runtime.dll")]
        internal static extern void FreeC(IntPtr buf, bool align);

        private static readonly object _codePageLocker = new object();
        private static readonly List<CodePageAllocator> _codePageList = new List<CodePageAllocator>();
        private static int _codePageDefault = -1;

        #endregion

        #region Query

        [DllImport("kernel32.dll")]
        private static extern int VirtualQuery(IntPtr lpAddress, out MEMORY_BASIC_INFORMATION lpBuffer, int dwLength);

        [StructLayout(LayoutKind.Sequential)]
        private struct MEMORY_BASIC_INFORMATION
        {
            public IntPtr BaseAddress;
            public IntPtr AllocationBase;
            public uint AllocationProtect;
            public IntPtr RegionSize;
            public uint State;
            public uint Protect;
            public uint Type;
        }

        /// <summary>
        /// Memory allocation protection flags.
        /// </summary>
        [Flags]
        public enum AllocationProtectFlags : uint
        {
            None = 0,
            PAGE_EXECUTE = 0x00000010,
            PAGE_EXECUTE_READ = 0x00000020,
            PAGE_EXECUTE_READWRITE = 0x00000040,
            PAGE_EXECUTE_WRITECOPY = 0x00000080,
            PAGE_NOACCESS = 0x00000001,
            PAGE_READONLY = 0x00000002,
            PAGE_READWRITE = 0x00000004,
            PAGE_WRITECOPY = 0x00000008,
            PAGE_GUARD = 0x00000100,
            PAGE_NOCACHE = 0x00000200,
            PAGE_WRITECOMBINE = 0x00000400
        }

        /// <summary>
        /// Gets the memory region information at specified address. The address does not have to be the base address of the region. Returns false if this is not a valid
        /// memory region or VirtualQuery failed for some other reason.
        /// </summary>
        /// <param name="address">The address.</param>
        /// <param name="baseAddress">The base address of the region.</param>
        /// <param name="size">The size of the region in bytes starting from base address.</param>
        /// <param name="flags">The protection flags.</param>
        /// <returns></returns>
        public static bool GetRegionInfo(IntPtr address, ref IntPtr baseAddress, ref long size, ref AllocationProtectFlags flags)
        {
            MEMORY_BASIC_INFORMATION result;
            int ok = VirtualQuery(address, out result, Marshal.SizeOf(typeof(MEMORY_BASIC_INFORMATION)));
            if (ok == 0)
                return false;

            baseAddress = result.BaseAddress;
            if (Main.Is64Bit)
                size = result.RegionSize.ToInt64();
            else
                size = result.RegionSize.ToInt32();
            flags = (AllocationProtectFlags)result.AllocationProtect;
            
            return true;
        }

        /// <summary>
        /// Determines whether the memory region at the specified address is valid.
        /// </summary>
        /// <param name="address">The address we wish to check.</param>
        /// <param name="size">The size in bytes of how much memory must be valid.</param>
        /// <param name="read">If set to <c>true</c> then we must have read access to this region.</param>
        /// <param name="write">If set to <c>true</c> then we must have write access to this region.</param>
        /// <param name="executable">If set to <c>true</c> then we must have code execution access to this region.</param>
        /// <returns></returns>
        public static bool IsValidRegion(IntPtr address, int size, bool read, bool write, bool executable)
        {
            IntPtr alloc_base = IntPtr.Zero;
            long alloc_size = 0;
            AllocationProtectFlags alloc_flags = AllocationProtectFlags.None;

            if (!GetRegionInfo(address, ref alloc_base, ref alloc_size, ref alloc_flags))
                return false;

            if (read && (alloc_flags & (AllocationProtectFlags.PAGE_EXECUTE_READ | AllocationProtectFlags.PAGE_EXECUTE_READWRITE | AllocationProtectFlags.PAGE_READONLY | AllocationProtectFlags.PAGE_READWRITE)) == AllocationProtectFlags.None)
                return false;
            if (write && (alloc_flags & (AllocationProtectFlags.PAGE_EXECUTE_READWRITE | AllocationProtectFlags.PAGE_EXECUTE_WRITECOPY | AllocationProtectFlags.PAGE_READWRITE | AllocationProtectFlags.PAGE_WRITECOMBINE | AllocationProtectFlags.PAGE_WRITECOPY)) == AllocationProtectFlags.None)
                return false;
            if (executable && (alloc_flags & (AllocationProtectFlags.PAGE_EXECUTE | AllocationProtectFlags.PAGE_EXECUTE_READ | AllocationProtectFlags.PAGE_EXECUTE_READWRITE | AllocationProtectFlags.PAGE_EXECUTE_WRITECOPY)) == AllocationProtectFlags.None)
                return false;

            ulong b = (Main.Is64Bit ? alloc_base.ToUInt64() : alloc_base.ToUInt32());
            ulong begin = Main.Is64Bit ? address.ToUInt64() : address.ToUInt32();
            ulong end = b + unchecked((ulong)alloc_size);

            if (begin >= end || begin < b)
                return false;

            if (size <= 0)
                return true;

            ulong available = end - begin;
            ulong want = (ulong)size;
            return want <= available;
        }

        #endregion

        #region Reading

        /// <summary>
        /// Reads value from specified memory address.
        /// </summary>
        /// <param name="address">The address to read from.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before reading and return after.
        /// Only set this true if you are sure you don't have read permissions!</param>
        /// <returns></returns>
        public static byte ReadUInt8(IntPtr address, bool protect = false)
        {
            var r = new byte[1];
            Read(address, r, r.Length, protect);
            return r[0];
        }

        /// <summary>
        /// Reads value from specified memory address.
        /// </summary>
        /// <param name="address">The address to read from.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before reading and return after.
        /// Only set this true if you are sure you don't have read permissions!</param>
        /// <returns></returns>
        public static sbyte ReadInt8(IntPtr address, bool protect = false)
        {
            var r = new byte[1];
            Read(address, r, r.Length, protect);
            return unchecked((sbyte)r[0]);
        }

        /// <summary>
        /// Reads value from specified memory address.
        /// </summary>
        /// <param name="address">The address to read from.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before reading and return after.
        /// Only set this true if you are sure you don't have read permissions!</param>
        /// <returns></returns>
        public static char ReadChar(IntPtr address, bool protect = false)
        {
            var r = new byte[2];
            Read(address, r, r.Length, protect);
            return BitConverter.ToChar(r, 0);
        }

        /// <summary>
        /// Reads value from specified memory address.
        /// </summary>
        /// <param name="address">The address to read from.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before reading and return after.
        /// Only set this true if you are sure you don't have read permissions!</param>
        /// <returns></returns>
        public static short ReadInt16(IntPtr address, bool protect = false)
        {
            var r = new byte[2];
            Read(address, r, r.Length, protect);
            return BitConverter.ToInt16(r, 0);
        }

        /// <summary>
        /// Reads value from specified memory address.
        /// </summary>
        /// <param name="address">The address to read from.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before reading and return after.
        /// Only set this true if you are sure you don't have read permissions!</param>
        /// <returns></returns>
        public static ushort ReadUInt16(IntPtr address, bool protect = false)
        {
            var r = new byte[2];
            Read(address, r, r.Length, protect);
            return BitConverter.ToUInt16(r, 0);
        }

        /// <summary>
        /// Reads value from specified memory address.
        /// </summary>
        /// <param name="address">The address to read from.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before reading and return after.
        /// Only set this true if you are sure you don't have read permissions!</param>
        /// <returns></returns>
        public static int ReadInt32(IntPtr address, bool protect = false)
        {
            var r = new byte[4];
            Read(address, r, r.Length, protect);
            return BitConverter.ToInt32(r, 0);
        }

        /// <summary>
        /// Reads value from specified memory address.
        /// </summary>
        /// <param name="address">The address to read from.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before reading and return after.
        /// Only set this true if you are sure you don't have read permissions!</param>
        /// <returns></returns>
        public static int ReadInterlockedInt32(IntPtr address, bool protect = false)
        {
            var r = new byte[4];
            Read(address, r, r.Length, protect, 1);
            return BitConverter.ToInt32(r, 0);
        }

        /// <summary>
        /// Reads value from specified memory address.
        /// </summary>
        /// <param name="address">The address to read from.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before reading and return after.
        /// Only set this true if you are sure you don't have read permissions!</param>
        /// <returns></returns>
        public static uint ReadUInt32(IntPtr address, bool protect = false)
        {
            var r = new byte[4];
            Read(address, r, r.Length, protect);
            return BitConverter.ToUInt32(r, 0);
        }

        /// <summary>
        /// Reads value from specified memory address.
        /// </summary>
        /// <param name="address">The address to read from.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before reading and return after.
        /// Only set this true if you are sure you don't have read permissions!</param>
        /// <returns></returns>
        public static uint ReadInterlockedUInt32(IntPtr address, bool protect = false)
        {
            var r = new byte[4];
            Read(address, r, r.Length, protect, 1);
            return BitConverter.ToUInt32(r, 0);
        }

        /// <summary>
        /// Reads value from specified memory address.
        /// </summary>
        /// <param name="address">The address to read from.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before reading and return after.
        /// Only set this true if you are sure you don't have read permissions!</param>
        /// <returns></returns>
        public static long ReadInt64(IntPtr address, bool protect = false)
        {
            var r = new byte[8];
            Read(address, r, r.Length, protect);
            return BitConverter.ToInt64(r, 0);
        }

        /// <summary>
        /// Reads value from specified memory address.
        /// </summary>
        /// <param name="address">The address to read from.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before reading and return after.
        /// Only set this true if you are sure you don't have read permissions!</param>
        /// <returns></returns>
        public static long ReadInterlockedInt64(IntPtr address, bool protect = false)
        {
            var r = new byte[8];
            Read(address, r, r.Length, protect, 2);
            return BitConverter.ToInt64(r, 0);
        }

        /// <summary>
        /// Reads value from specified memory address.
        /// </summary>
        /// <param name="address">The address to read from.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before reading and return after.
        /// Only set this true if you are sure you don't have read permissions!</param>
        /// <returns></returns>
        public static ulong ReadUInt64(IntPtr address, bool protect = false)
        {
            var r = new byte[8];
            Read(address, r, r.Length, protect);
            return BitConverter.ToUInt64(r, 0);
        }

        /// <summary>
        /// Reads value from specified memory address.
        /// </summary>
        /// <param name="address">The address to read from.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before reading and return after.
        /// Only set this true if you are sure you don't have read permissions!</param>
        /// <returns></returns>
        public static ulong ReadInterlockedUInt64(IntPtr address, bool protect = false)
        {
            var r = new byte[8];
            Read(address, r, r.Length, protect, 2);
            return BitConverter.ToUInt64(r, 0);
        }

        /// <summary>
        /// Reads value from specified memory address.
        /// </summary>
        /// <param name="address">The address to read from.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before reading and return after.
        /// Only set this true if you are sure you don't have read permissions!</param>
        /// <returns></returns>
        public static float ReadFloat(IntPtr address, bool protect = false)
        {
            var r = new byte[4];
            Read(address, r, r.Length, protect);
            return BitConverter.ToSingle(r, 0);
        }

        /// <summary>
        /// Reads value from specified memory address.
        /// </summary>
        /// <param name="address">The address to read from.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before reading and return after.
        /// Only set this true if you are sure you don't have read permissions!</param>
        /// <returns></returns>
        public static double ReadDouble(IntPtr address, bool protect = false)
        {
            var r = new byte[8];
            Read(address, r, r.Length, protect);
            return BitConverter.ToDouble(r, 0);
        }

        /// <summary>
        /// Reads value from specified memory address.
        /// </summary>
        /// <param name="address">The address to read from.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before reading and return after.
        /// Only set this true if you are sure you don't have read permissions!</param>
        /// <returns></returns>
        public static double ReadDouble128(IntPtr address, bool protect = false)
        {
            var r = new byte[16];
            var a = new byte[8];
            Read(address, r, r.Length, protect);
            ReadDQFrom(r, a);
            return BitConverter.ToDouble(a, 0);
        }

        /// <summary>
        /// Reads value from specified memory address.
        /// </summary>
        /// <param name="address">The address to read from.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before reading and return after.
        /// Only set this true if you are sure you don't have read permissions!</param>
        /// <returns></returns>
        public static float ReadFloat128(IntPtr address, bool protect = false)
        {
            var r = new byte[16];
            var a = new byte[4];
            Read(address, r, r.Length, protect);
            ReadFQFrom(r, a);
            return BitConverter.ToSingle(a, 0);
        }

        /// <summary>
        /// Reads value from specified memory address.
        /// </summary>
        /// <param name="address">The address to read from.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before reading and return after.
        /// Only set this true if you are sure you don't have read permissions!</param>
        /// <returns></returns>
        public static IntPtr ReadPointer(IntPtr address, bool protect = false)
        {
            var r = new byte[IntPtr.Size];
            Read(address, r, r.Length, protect);
            return Main.Is64Bit ? new IntPtr(BitConverter.ToInt64(r, 0)) : new IntPtr(BitConverter.ToInt32(r, 0));
        }

        /// <summary>
        /// Tries to read pointer and instead of throwing exception returns false if failed.
        /// </summary>
        /// <param name="address">The address.</param>
        /// <param name="result">The result.</param>
        /// <param name="protect">if set to <c>true</c> [protect].</param>
        /// <returns></returns>
        public static bool TryReadPointer(IntPtr address, ref IntPtr result, bool protect = false)
        {
            var r = new byte[IntPtr.Size];
            if (!TryRead(address, r, r.Length, protect))
                return false;
            result = Main.Is64Bit ? new IntPtr(BitConverter.ToInt64(r, 0)) : new IntPtr(BitConverter.ToInt32(r, 0));
            return true;
        }

        /// <summary>
        /// Reads value from specified memory address.
        /// </summary>
        /// <param name="address">The address to read from.</param>
        /// <param name="wide">If set to <c>true</c> then string is unicode (2 bytes per character).</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before reading and return after.
        /// Only set this true if you are sure you don't have read permissions!</param>
        /// <returns></returns>
        public static string ReadString(IntPtr address, bool wide, bool protect = false)
        {
            using (System.IO.MemoryStream ms = new System.IO.MemoryStream(128))
            {
                byte[] r = new byte[wide ? 2 : 1];
                while (true)
                {
                    Read(address, r, r.Length, protect);
                    if ((wide && BitConverter.ToChar(r, 0) == '\0') || (!wide && r[0] == 0))
                        break;
                    address += r.Length;
                    ms.Write(r, 0, r.Length);
                }

                r = ms.ToArray();
                return (wide ? Encoding.Unicode : Encoding.ASCII).GetString(r);
            }
        }

        /// <summary>
        /// Reads string from specified memory address but only if it's probably a string.
        /// </summary>
        /// <param name="address">The address to read from.</param>
        /// <param name="escapeChars">Escape some characters like newline.</param>
        /// <returns></returns>
        internal static string ReadStringIfItsString(IntPtr address, bool escapeChars)
        {
            int countGood = 0;
            int countBad = 0;
            int countOk = 0;

            using (System.IO.MemoryStream ms = new System.IO.MemoryStream(128))
            {
                byte[] r = new byte[1];
                while (true)
                {
                    if (!TryRead(address, r, r.Length, false))
                        break;
                    if (r[0] == 0)
                        break;
                    address += r.Length;
                    ms.Write(r, 0, r.Length);

                    bool did = false;
                    switch(r[0])
                    {
                        case 9: // \t
                        case 0xD: // \r
                            countOk++;
                            did = true;
                            break;

                        case 0xA: // \n
                            countGood++;
                            did = true;
                            break;
                    }

                    if (!did && r[0] < 0x20)
                    {
                        countBad++;
                        did = true;
                    }
                    else if(!did && r[0] < 0x7F)
                    {
                        countGood++;
                        did = true;
                    }
                    else if(!did && r[0] < 176)
                    {
                        countOk++;
                        did = true;
                    }
                    else if(!did)
                    {
                        countBad++;
                        did = true;
                    }
                }

                int total = countGood + countOk + countBad;
                if (total <= 0)
                    return null;

                int score = countBad * -20 + countOk * 1 + countGood * 4;
                if (score < 0)
                    return null;

                r = ms.ToArray();
                string rs = Encoding.ASCII.GetString(r);
                if(escapeChars)
                {
                    rs = rs.Replace("\n", "\\n");
                    rs = rs.Replace("\r", "\\r");
                    rs = rs.Replace("\t", "\\t");
                }
                return rs;
            }
        }

        /// <summary>
        /// Reads value from specified memory address.
        /// </summary>
        /// <param name="address">The address to read from.</param>
        /// <param name="length">Amount of bytes to read.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before reading and return after.
        /// Only set this true if you are sure you don't have read permissions!</param>
        /// <returns></returns>
        public static byte[] ReadBytes(IntPtr address, int length, bool protect = false)
        {
            if (length < 0)
                throw new ArgumentOutOfRangeException("length");
            byte[] result = new byte[length];
            if (length > 0)
                Read(address, result, length, protect);
            return result;
        }

        /// <summary>
        /// Verifies the bytes at address. If the bytes match then returns true. Use ? symbol for wildcard so a wild byte would be ?? but you can also
        /// check 7? to allow 70-7F and so on. Any space or dash in the hex string will be ignored.
        /// </summary>
        /// <param name="address">The address.</param>
        /// <param name="hex">The hexadecimal byte array.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before reading and return after.
        /// Only set this true if you are sure you don't have read permissions!</param>
        /// <returns></returns>
        public static bool VerifyBytes(IntPtr address, string hex, bool protect = false)
        {
            if (hex == null)
                throw new ArgumentNullException("hex");

            if (hex.Length == 0)
                return true;

            var bld = new StringBuilder(hex.Length);
            int index = 0;
            int len = hex.Length;
            while(index < len)
            {
                char c = hex[index];
                
                switch(c)
                {
                    case ' ':
                    case '-':
                        {
                            index++;
                            continue;
                        }

                    case '*':
                    case '?':
                    case '.':
                        {
                            bld.Append('?');
                            index++;
                            continue;
                        }

                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                    case 'a':
                    case 'b':
                    case 'c':
                    case 'd':
                    case 'e':
                    case 'f':
                        {
                            bld.Append(c);
                            index++;
                            continue;
                        }

                    case 'A':
                    case 'B':
                    case 'C':
                    case 'D':
                    case 'E':
                    case 'F':
                        {
                            bld.Append(char.ToLowerInvariant(c));
                            index++;
                            continue;
                        }

                    default:
                        throw new FormatException("Unknown symbol in hex string: '" + c.ToString() + "'!");
                }
            }

            string hex2 = bld.ToString();
            if ((hex2.Length % 2) != 0)
                throw new FormatException("Hex string length must be divisible by 2!");

            var bytes = Memory.ReadBytes(address, hex2.Length / 2, protect);
            for(int i = 0; i < bytes.Length; i++)
            {
                char c1 = hex2[i * 2];
                char c2 = hex2[i * 2 + 1];

                if (c1 == '?' && c2 == '?')
                    continue;

                if(c1 == '?')
                {
                    byte b = byte.Parse(c2.ToString(), System.Globalization.NumberStyles.HexNumber, null);
                    if (b != (bytes[i] & 0xF))
                        return false;
                }
                else if(c2 == '?')
                {
                    byte b = byte.Parse(c1.ToString(), System.Globalization.NumberStyles.HexNumber, null);
                    if (b != (bytes[i] >> 4))
                        return false;
                }
                else
                {
                    byte b = byte.Parse(hex2.Substring(i * 2, 2), System.Globalization.NumberStyles.HexNumber, null);
                    if (b != bytes[i])
                        return false;
                }
            }

            return true;
        }

        /// <summary>
        /// Tries to read bytes but instead of exception it will return false on fail.
        /// </summary>
        /// <param name="address">The address to read from.</param>
        /// <param name="length">The length of bytes to read.</param>
        /// <param name="result">The result. This should be a null value because a new byte array will be allocated during this method if it succeeds.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before reading and return after.
        /// Only set this true if you are sure you don't have read permissions!</param>
        /// <returns></returns>
        public static bool TryReadBytes(IntPtr address, int length, ref byte[] result, bool protect = false)
        {
            if (length < 0)
                throw new ArgumentOutOfRangeException("length");
            byte[] r = new byte[length];
            if (length > 0)
            {
                if (!TryRead(address, r, length, protect))
                    return false;
            }
            result = r;
            return true;
        }

        #endregion

        #region Writing

        /// <summary>
        /// Writes value to specified memory address.
        /// </summary>
        /// <param name="address">The address to write to.</param>
        /// <param name="value">The value to write.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before writing and return after.
        /// Only set this true if you are sure you don't have write permissions!</param>
        public static void WriteInt8(IntPtr address, sbyte value, bool protect = false)
        {
            var r = new byte[] { unchecked((byte)value) };
            Write(address, r, 0, r.Length, protect);
        }

        /// <summary>
        /// Writes value to specified memory address.
        /// </summary>
        /// <param name="address">The address to write to.</param>
        /// <param name="value">The value to write.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before writing and return after.
        /// Only set this true if you are sure you don't have write permissions!</param>
        public static void WriteUInt8(IntPtr address, byte value, bool protect = false)
        {
            var r = new byte[] { value };
            Write(address, r, 0, r.Length, protect);
        }

        /// <summary>
        /// Writes value to specified memory address.
        /// </summary>
        /// <param name="address">The address to write to.</param>
        /// <param name="value">The value to write.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before writing and return after.
        /// Only set this true if you are sure you don't have write permissions!</param>
        public static void WriteInt16(IntPtr address, short value, bool protect = false)
        {
            var r = BitConverter.GetBytes(value);
            Write(address, r, 0, r.Length, protect);
        }

        /// <summary>
        /// Writes value to specified memory address.
        /// </summary>
        /// <param name="address">The address to write to.</param>
        /// <param name="value">The value to write.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before writing and return after.
        /// Only set this true if you are sure you don't have write permissions!</param>
        public static void WriteUInt16(IntPtr address, ushort value, bool protect = false)
        {
            var r = BitConverter.GetBytes(value);
            Write(address, r, 0, r.Length, protect);
        }

        /// <summary>
        /// Writes value to specified memory address.
        /// </summary>
        /// <param name="address">The address to write to.</param>
        /// <param name="value">The value to write.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before writing and return after.
        /// Only set this true if you are sure you don't have write permissions!</param>
        public static void WriteInt32(IntPtr address, int value, bool protect = false)
        {
            var r = BitConverter.GetBytes(value);
            Write(address, r, 0, r.Length, protect);
        }

        /// <summary>
        /// Writes value to specified memory address.
        /// </summary>
        /// <param name="address">The address to write to.</param>
        /// <param name="value">The value to write.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before writing and return after.
        /// Only set this true if you are sure you don't have write permissions!</param>
        public static int WriteInterlockedInt32(IntPtr address, int value, bool protect = false)
        {
            var r = BitConverter.GetBytes(value);
            Write(address, r, 0, r.Length, protect, 1);
            return BitConverter.ToInt32(r, 0);
        }

        /// <summary>
        /// Writes value to specified memory address.
        /// </summary>
        /// <param name="address">The address to write to.</param>
        /// <param name="value">The value to write.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before writing and return after.
        /// Only set this true if you are sure you don't have write permissions!</param>
        public static void WriteUInt32(IntPtr address, uint value, bool protect = false)
        {
            var r = BitConverter.GetBytes(value);
            Write(address, r, 0, r.Length, protect);
        }

        /// <summary>
        /// Writes value to specified memory address.
        /// </summary>
        /// <param name="address">The address to write to.</param>
        /// <param name="value">The value to write.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before writing and return after.
        /// Only set this true if you are sure you don't have write permissions!</param>
        public static uint WriteInterlockedUInt32(IntPtr address, uint value, bool protect = false)
        {
            var r = BitConverter.GetBytes(value);
            Write(address, r, 0, r.Length, protect, 1);
            return BitConverter.ToUInt32(r, 0);
        }

        /// <summary>
        /// Writes value to specified memory address.
        /// </summary>
        /// <param name="address">The address to write to.</param>
        /// <param name="value">The value to write.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before writing and return after.
        /// Only set this true if you are sure you don't have write permissions!</param>
        public static void WriteInt64(IntPtr address, long value, bool protect = false)
        {
            var r = BitConverter.GetBytes(value);
            Write(address, r, 0, r.Length, protect);
        }

        /// <summary>
        /// Writes value to specified memory address.
        /// </summary>
        /// <param name="address">The address to write to.</param>
        /// <param name="value">The value to write.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before writing and return after.
        /// Only set this true if you are sure you don't have write permissions!</param>
        public static long WriteInterlockedInt64(IntPtr address, long value, bool protect = false)
        {
            var r = BitConverter.GetBytes(value);
            Write(address, r, 0, r.Length, protect, 2);
            return BitConverter.ToInt64(r, 0);
        }

        /// <summary>
        /// Writes value to specified memory address.
        /// </summary>
        /// <param name="address">The address to write to.</param>
        /// <param name="value">The value to write.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before writing and return after.
        /// Only set this true if you are sure you don't have write permissions!</param>
        public static void WriteUInt64(IntPtr address, ulong value, bool protect = false)
        {
            var r = BitConverter.GetBytes(value);
            Write(address, r, 0, r.Length, protect);
        }

        /// <summary>
        /// Writes value to specified memory address.
        /// </summary>
        /// <param name="address">The address to write to.</param>
        /// <param name="value">The value to write.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before writing and return after.
        /// Only set this true if you are sure you don't have write permissions!</param>
        public static ulong WriteInterlockedUInt64(IntPtr address, ulong value, bool protect = false)
        {
            var r = BitConverter.GetBytes(value);
            Write(address, r, 0, r.Length, protect, 2);
            return BitConverter.ToUInt64(r, 0);
        }

        /// <summary>
        /// Writes value to specified memory address.
        /// </summary>
        /// <param name="address">The address to write to.</param>
        /// <param name="value">The value to write.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before writing and return after.
        /// Only set this true if you are sure you don't have write permissions!</param>
        public static void WriteFloat(IntPtr address, float value, bool protect = false)
        {
            var r = BitConverter.GetBytes(value);
            Write(address, r, 0, r.Length, protect);
        }

        /// <summary>
        /// Writes value to specified memory address.
        /// </summary>
        /// <param name="address">The address to write to.</param>
        /// <param name="value">The value to write.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before writing and return after.
        /// Only set this true if you are sure you don't have write permissions!</param>
        public static void WriteDouble(IntPtr address, double value, bool protect = false)
        {
            var r = BitConverter.GetBytes(value);
            Write(address, r, 0, r.Length, protect);
        }

        /// <summary>
        /// Writes value to specified memory address.
        /// </summary>
        /// <param name="address">The address to write to.</param>
        /// <param name="value">The value to write.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before writing and return after.
        /// Only set this true if you are sure you don't have write permissions!</param>
        public static void WriteDouble128(IntPtr address, double value, bool protect = false)
        {
            var a = BitConverter.GetBytes(value);
            var r = new byte[16];
            WriteDQTo(a, r);
            Write(address, r, 0, r.Length, protect);
        }

        /// <summary>
        /// Writes value to specified memory address.
        /// </summary>
        /// <param name="address">The address to write to.</param>
        /// <param name="value">The value to write.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before writing and return after.
        /// Only set this true if you are sure you don't have write permissions!</param>
        public static void WriteFloat128(IntPtr address, float value, bool protect = false)
        {
            var a = BitConverter.GetBytes(value);
            var r = new byte[16];
            WriteFQTo(a, r);
            Write(address, r, 0, r.Length, protect);
        }

        /// <summary>
        /// Writes value to specified memory address.
        /// </summary>
        /// <param name="address">The address to write to.</param>
        /// <param name="value">The value to write.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before writing and return after.
        /// Only set this true if you are sure you don't have write permissions!</param>
        public static void WritePointer(IntPtr address, IntPtr value, bool protect = false)
        {
            var r = Main.Is64Bit ? BitConverter.GetBytes(value.ToInt64()) : BitConverter.GetBytes(value.ToInt32());
            Write(address, r, 0, r.Length, protect);
        }

        /// <summary>
        /// Writes value to specified memory address.
        /// </summary>
        /// <param name="address">The address to write to.</param>
        /// <param name="value">The value to write.</param>
        /// <param name="wide">Write as wide (2 byte) string or regular (1 byte) string.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before writing and return after.
        /// Only set this true if you are sure you don't have write permissions!</param>
        /// <exception cref="System.ArgumentNullException">value</exception>
        public static void WriteString(IntPtr address, string value, bool wide, bool protect = false)
        {
            if (value == null)
                throw new ArgumentNullException("value");

            var r = wide ? Encoding.Unicode.GetBytes(value) : Encoding.ASCII.GetBytes(value);
            Write(address, r, 0, r.Length, protect);
        }

        /// <summary>
        /// Writes value to specified memory address.
        /// </summary>
        /// <param name="address">The address to write to.</param>
        /// <param name="value">The value to write.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before writing and return after.
        /// Only set this true if you are sure you don't have write permissions!</param>
        public static void WriteBytes(IntPtr address, byte[] value, bool protect = false)
        {
            Write(address, value, 0, value.Length, protect);
        }

        /// <summary>
        /// Writes value to specified memory address.
        /// </summary>
        /// <param name="address">The address to write to.</param>
        /// <param name="value">The value to write.</param>
        /// <param name="index">The index in array when to start writing.</param>
        /// <param name="length">The amount of bytes to write starting at index.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before writing and return after.
        /// Only set this true if you are sure you don't have write permissions!</param>
        public static void WriteBytes(IntPtr address, byte[] value, int index, int length, bool protect = false)
        {
            Write(address, value, index, length, protect);
        }

        /// <summary>
        /// Writes zero bytes to specified memory address.
        /// </summary>
        /// <param name="address">The address to write to.</param>
        /// <param name="size">The amount of bytes to write.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before writing and return after.
        /// Only set this true if you are sure you don't have write permissions!</param>
        public static void WriteZero(IntPtr address, int size, bool protect = false)
        {
            if (size < 0)
                throw new ArgumentOutOfRangeException("size", "Size must not be negative!");

            if (size <= ZeroBytes.Length)
                WriteBytes(address, ZeroBytes, 0, size, protect);
            else
            {
                for(int i = 0; i < size; i += ZeroBytes.Length)
                {
                    int len = Math.Min(ZeroBytes.Length, (size - i));
                    WriteBytes(address, ZeroBytes, 0, len, protect);
                }
            }
        }

        /// <summary>
        /// The zero bytes array.
        /// </summary>
        private static readonly byte[] ZeroBytes = new byte[4096];

        /// <summary>
        /// Changes value at specified memory address and returns the modified value.
        /// </summary>
        /// <param name="address">The address to change.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before writing and return after.
        /// Only set this true if you are sure you don't have write permissions!</param>
        /// <returns></returns>
        public static int InterlockedIncrement32(IntPtr address, bool protect = false)
        {
            byte[] data = new byte[4];
            Write(address, data, 0, data.Length, protect, 3);
            return BitConverter.ToInt32(data, 0);
        }

        /// <summary>
        /// Changes value at specified memory address and returns the modified value.
        /// </summary>
        /// <param name="address">The address to change.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before writing and return after.
        /// Only set this true if you are sure you don't have write permissions!</param>
        /// <returns></returns>
        public static int InterlockedDecrement32(IntPtr address, bool protect = false)
        {
            byte[] data = new byte[4];
            Write(address, data, 0, data.Length, protect, 4);
            return BitConverter.ToInt32(data, 0);
        }

        /// <summary>
        /// Changes value at specified memory address and returns the modified value.
        /// </summary>
        /// <param name="address">The address to change.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before writing and return after.
        /// Only set this true if you are sure you don't have write permissions!</param>
        /// <returns></returns>
        public static long InterlockedIncrement64(IntPtr address, bool protect = false)
        {
            byte[] data = new byte[8];
            Write(address, data, 0, data.Length, protect, 5);
            return BitConverter.ToInt64(data, 0);
        }

        /// <summary>
        /// Changes value at specified memory address and returns the modified value.
        /// </summary>
        /// <param name="address">The address to change.</param>
        /// <param name="protect">If set to <c>true</c> then change protection flags of memory page before writing and return after.
        /// Only set this true if you are sure you don't have write permissions!</param>
        /// <returns></returns>
        public static long InterlockedDecrement64(IntPtr address, bool protect = false)
        {
            byte[] data = new byte[8];
            Write(address, data, 0, data.Length, protect, 6);
            return BitConverter.ToInt64(data, 0);
        }

        #endregion

        #region Internal methods

        /// <summary>
        /// Converts the specified pointer to a unsigned long value.
        /// </summary>
        /// <param name="ptr">The pointer.</param>
        /// <returns></returns>
        internal static ulong Convert(IntPtr ptr)
        {
            if (Main.Is64Bit)
                return unchecked((ulong)ptr.ToInt64());
            return unchecked((uint)ptr.ToInt32());
        }

        /// <summary>
        /// Converts the specified unsigned long to a pointer value.
        /// </summary>
        /// <param name="ptr">The value.</param>
        /// <returns></returns>
        internal static IntPtr Convert(ulong ptr)
        {
            if (Main.Is64Bit)
                return new IntPtr(unchecked((long)ptr));
            ptr &= 0xFFFFFFFF;
            return new IntPtr(unchecked((int)((uint)ptr)));
        }

        /// <summary>
        /// Reads memory internally from the specified address.
        /// </summary>
        /// <param name="address">The address.</param>
        /// <param name="buffer">The buffer.</param>
        /// <param name="length">The length.</param>
        /// <param name="protect">if set to <c>true</c> [protect].</param>
        /// <param name="intl">Interlocked type.</param>
        /// <exception cref="NetScriptFramework.MemoryAccessException"></exception>
        private static void Read(IntPtr address, byte[] buffer, int length, bool protect, int intl = 0)
        {
            if (!protect)
            {
                if (intl == 0)
                {
                    if (MemoryCopy(address, 0, buffer, 0, length) != length)
                        throw new MemoryAccessException(address, length, false);
                }
                else
                {
                    switch(intl)
                    {
                        case 1:
                            if (MemoryReadInterlocked32(address, buffer) == 0)
                                throw new MemoryAccessException(address, 4, false);
                            break;

                        case 2:
                            if (MemoryReadInterlocked64(address, buffer) == 0)
                                throw new MemoryAccessException(address, 8, false);
                            break;

                        default:
                            throw new InvalidOperationException();
                    }
                }
                return;
            }

            lock (ProtectedMemoryLocker)
            {
                uint oldProtect = 0;
                if (!VirtualProtect(address, (uint)length, 0x40, out oldProtect))
                    throw new MemoryAccessException(address, length, 1);

                try
                {
                    if (intl == 0)
                    {
                        Marshal.Copy(address, buffer, 0, length);
                    }
                    else
                    {
                        switch(intl)
                        {
                            case 1:
                                if (MemoryReadInterlocked32(address, buffer) == 0)
                                    throw new MemoryAccessException(address, 4, false);
                                break;

                            case 2:
                                if (MemoryReadInterlocked64(address, buffer) == 0)
                                    throw new MemoryAccessException(address, 8, false);
                                break;

                            default:
                                throw new InvalidOperationException();
                        }
                    }
                }
                finally
                {
                    VirtualProtect(address, (uint)length, oldProtect, out oldProtect);
                }
            }
        }

        /// <summary>
        /// Reads memory internally from the specified address.
        /// </summary>
        /// <param name="address">The address.</param>
        /// <param name="buffer">The buffer.</param>
        /// <param name="length">The length.</param>
        /// <param name="protect">if set to <c>true</c> [protect].</param>
        /// <param name="intl">Interlocked type.</param>
        /// <exception cref="NetScriptFramework.MemoryAccessException"></exception>
        private static bool TryRead(IntPtr address, byte[] buffer, int length, bool protect, int intl = 0)
        {
            if (!protect)
            {
                if (intl == 0)
                {
                    if (MemoryCopy(address, 0, buffer, 0, length) != length)
                        return false;
                }
                else
                {
                    switch (intl)
                    {
                        case 1:
                            if (MemoryReadInterlocked32(address, buffer) == 0)
                                return false;
                            break;

                        case 2:
                            if (MemoryReadInterlocked64(address, buffer) == 0)
                                return false;
                            break;

                        default:
                            throw new InvalidOperationException();
                    }
                }
                return true;
            }

            lock (ProtectedMemoryLocker)
            {
                uint oldProtect = 0;
                if (!VirtualProtect(address, (uint)length, 0x40, out oldProtect))
                    return false;

                try
                {
                    if (intl == 0)
                    {
                        Marshal.Copy(address, buffer, 0, length);
                    }
                    else
                    {
                        switch (intl)
                        {
                            case 1:
                                if (MemoryReadInterlocked32(address, buffer) == 0)
                                    return false;
                                break;

                            case 2:
                                if (MemoryReadInterlocked64(address, buffer) == 0)
                                    return false;
                                break;

                            default:
                                throw new InvalidOperationException();
                        }
                    }
                }
                finally
                {
                    VirtualProtect(address, (uint)length, oldProtect, out oldProtect);
                }
            }

            return true;
        }

        /// <summary>
        /// Writes memory internally to the specified address.
        /// </summary>
        /// <param name="address">The address.</param>
        /// <param name="buffer">The buffer.</param>
        /// <param name="index">The index.</param>
        /// <param name="length">The length.</param>
        /// <param name="protect">if set to <c>true</c> [protect].</param>
        /// <param name="intl">Interlocked type.</param>
        /// <exception cref="NetScriptFramework.MemoryAccessException">
        /// </exception>
        private static void Write(IntPtr address, byte[] buffer, int index, int length, bool protect, int intl = 0)
        {
            if (!protect)
            {
                if (intl == 0)
                {
                    if (MemoryCopy(buffer, index, address, 0, length) != length)
                        throw new MemoryAccessException(address, length, true);
                }
                else
                {
                    switch(intl)
                    {
                        case 1:
                            if (MemoryWriteInterlocked32(buffer, address) == 0)
                                throw new MemoryAccessException(address, 4, true);
                            break;

                        case 2:
                            if (MemoryWriteInterlocked64(buffer, address) == 0)
                                throw new MemoryAccessException(address, 8, true);
                            break;

                        case 3:
                            if(MemoryIncrementInterlocked32(buffer, address) == 0)
                                throw new MemoryAccessException(address, 4, true);
                            break;

                        case 4:
                            if (MemoryDecrementInterlocked32(buffer, address) == 0)
                                throw new MemoryAccessException(address, 4, true);
                            break;

                        case 5:
                            if (MemoryIncrementInterlocked64(buffer, address) == 0)
                                throw new MemoryAccessException(address, 8, true);
                            break;

                        case 6:
                            if (MemoryDecrementInterlocked64(buffer, address) == 0)
                                throw new MemoryAccessException(address, 8, true);
                            break;

                        default:
                            throw new NotImplementedException();
                    }
                }
                return;
            }

            lock (ProtectedMemoryLocker)
            {
                uint oldProtect = 0;
                if (!VirtualProtect(address, (uint)length, 0x40, out oldProtect))
                    throw new MemoryAccessException(address, length, -1);

                try
                {
                    if (intl == 0)
                    {
                        Marshal.Copy(buffer, index, address, length);
                    }
                    else
                    {
                        switch (intl)
                        {
                            case 1:
                                if (MemoryWriteInterlocked32(buffer, address) == 0)
                                    throw new MemoryAccessException(address, 4, true);
                                break;

                            case 2:
                                if (MemoryWriteInterlocked64(buffer, address) == 0)
                                    throw new MemoryAccessException(address, 8, true);
                                break;

                            case 3:
                                if (MemoryIncrementInterlocked32(buffer, address) == 0)
                                    throw new MemoryAccessException(address, 4, true);
                                break;

                            case 4:
                                if (MemoryDecrementInterlocked32(buffer, address) == 0)
                                    throw new MemoryAccessException(address, 4, true);
                                break;

                            case 5:
                                if (MemoryIncrementInterlocked64(buffer, address) == 0)
                                    throw new MemoryAccessException(address, 8, true);
                                break;

                            case 6:
                                if (MemoryDecrementInterlocked64(buffer, address) == 0)
                                    throw new MemoryAccessException(address, 8, true);
                                break;

                            default:
                                throw new NotImplementedException();
                        }
                    }
                }
                finally
                {
                    VirtualProtect(address, (uint)length, oldProtect, out oldProtect);
                }
            }
        }

        /// <summary>
        /// Gets the main module version.
        /// </summary>
        /// <returns></returns>
        public static int[] GetMainModuleVersion()
        {
            int[] result = new int[4];
            result[0] = 1;
            var module = System.Diagnostics.Process.GetCurrentProcess().MainModule;
            if(module.FileVersionInfo != null)
            {
                string ver = module.FileVersionInfo.FileVersion;
                if (ver == "1.0.0.0" || ver == "0.0.0.0")
                    ver = module.FileVersionInfo.ProductVersion;

                var spl = ver.Split(new[] { '.' }, StringSplitOptions.None).ToList();
                int i = 0;
                foreach(var x in spl)
                {
                    string y = x.Trim();
                    if (y.Length == 0)
                        continue;

                    int t = 0;
                    if (!int.TryParse(y, out t) || t < 0)
                        continue;

                    result[i++] = t;
                    if (i >= result.Length)
                        break;
                }
            }

            return result;
        }

        /// <summary>
        /// The protected memory locker. This is used to make sure memory protection flags are returned correctly if reading or writing from multiple threads.
        /// </summary>
        private static readonly object ProtectedMemoryLocker = new object();

        [DllImport("kernel32.dll")]
        private static extern bool VirtualProtect(IntPtr lpAddress, uint dwSize, uint flNewProtect, out uint lpflOldProtect);

        [DllImport("NetScriptFramework.Runtime.dll")]
        private static extern int MemoryCopy(IntPtr source, int sourceIndex, byte[] destination, int destinationIndex, int length);

        [DllImport("NetScriptFramework.Runtime.dll")]
        private static extern int MemoryCopy(byte[] source, int sourceIndex, IntPtr destination, int destinationIndex, int length);

        [DllImport("NetScriptFramework.Runtime.dll")]
        private static extern int MemoryReadInterlocked32(IntPtr address, byte[] result);

        [DllImport("NetScriptFramework.Runtime.dll")]
        private static extern int MemoryReadInterlocked64(IntPtr address, byte[] result);

        [DllImport("NetScriptFramework.Runtime.dll")]
        private static extern int MemoryWriteInterlocked32(byte[] result, IntPtr address);

        [DllImport("NetScriptFramework.Runtime.dll")]
        private static extern int MemoryWriteInterlocked64(byte[] result, IntPtr address);

        [DllImport("NetScriptFramework.Runtime.dll")]
        private static extern int MemoryIncrementInterlocked64(byte[] result, IntPtr address);

        [DllImport("NetScriptFramework.Runtime.dll")]
        private static extern int MemoryDecrementInterlocked64(byte[] result, IntPtr address);

        [DllImport("NetScriptFramework.Runtime.dll")]
        private static extern int MemoryIncrementInterlocked32(byte[] result, IntPtr address);

        [DllImport("NetScriptFramework.Runtime.dll")]
        private static extern int MemoryDecrementInterlocked32(byte[] result, IntPtr address);

        [DllImport("NetScriptFramework.Runtime.dll")]
        private static extern void Explore_RTTI(IntPtr obj, IntPtr baseObj, IntPtr data, int dataMaxCount, IntPtr moduleBase);

        #endregion

        /// <summary>
        /// Explores the rtti data of object. Returns false if failed for any reason.
        /// </summary>
        /// <param name="obj">The object pointer.</param>
        /// <param name="baseObj">The base object pointer will be set here. May or may not equal the object pointer.</param>
        /// <param name="typeDescriptors">The type descriptors and their offsets from base object.</param>
        /// <returns></returns>
        public static bool ExploreRTTI(IntPtr obj, ref IntPtr baseObj, ref List<Tuple<IntPtr, int>> typeDescriptors)
        {
            int ptrSize = IntPtr.Size;
            int maxInheritCount = 0x80;
            var ls = new List<Tuple<IntPtr, int>>();
            using (var alloc = Memory.Allocate((maxInheritCount + 2) * ptrSize))
            {
                IntPtr addrOfBase = alloc.Address - ptrSize * 2;
                Memory.WritePointer(addrOfBase, IntPtr.Zero);
                Explore_RTTI(obj, addrOfBase, alloc.Address, maxInheritCount, Main.GetMainTargetedModule().BaseAddress);

                IntPtr _base = Memory.ReadPointer(addrOfBase);
                if (_base == IntPtr.Zero)
                    return false;

                for(int i = 0; i < maxInheritCount; i += 2)
                {
                    var objTypeId = Memory.ReadPointer(alloc.Address + i * ptrSize);
                    var objOffset = Memory.ReadInt32(alloc.Address + (i + 1) * ptrSize);
                    ls.Add(new Tuple<IntPtr, int>(objTypeId, objOffset));
                }
                baseObj = _base;
                typeDescriptors = ls;
            }

            return true;
        }

        /// <summary>
        /// Gets the current native thread identifier.
        /// </summary>
        /// <returns></returns>
        public static int GetCurrentNativeThreadId()
        {
            return Tools._Internal.RTHandler.GetCurrentThreadId();
        }

        #region Injection

        /// <summary>
        /// Writes the assembly NOP opcodes to address. This will use safe writing so we can write on code pages as well.
        /// </summary>
        /// <param name="address">The address.</param>
        /// <param name="count">The count.</param>
        public static void WriteNop(IntPtr address, int count)
        {
            if (count <= 0)
                return;

            byte[] data = new byte[count];
            for (int i = 0; i < data.Length; i++)
                data[i] = 0x90;

            WriteBytes(address, data, true);
        }

        /*/// <summary>
        /// Writes the virtual table hook.
        /// </summary>
        /// <param name="parameters">The parameters.</param>
        /// <exception cref="System.ArgumentNullException">
        /// parameters
        /// or
        /// parameters.Address
        /// or
        /// parameters.Before && parameters.After
        /// </exception>
        /// <exception cref="System.InvalidOperationException">Writing code hooks is only allowed during plugin initialization!</exception>
        public static void WriteVTableHook(VTableHookParameters parameters)
        {
            if (parameters == null)
                throw new ArgumentNullException("parameters");

            if (parameters.Address == IntPtr.Zero)
                throw new ArgumentNullException("parameters.Address");

            if (parameters.Before == null && parameters.After == null)
                throw new ArgumentNullException("parameters.Before && parameters.After");

            if (Main._is_initializing_plugin != 2)
                throw new InvalidOperationException("Writing code hooks is only allowed during plugin initialization!");

            byte[] data = null;
            int offset_before = -1;
            int offset_after = -1;

            using (var stream = new System.IO.MemoryStream())
            {
                using (var ms = new System.IO.BinaryWriter(stream))
                {
                    if (Main.Is64Bit)
                    {
                        if(parameters.Before != null)
                        {
                            offset_before = (int)ms.BaseStream.Position;
                            ms.Write(new byte[13]);
                        }

                        // This can't work because some arguments may be on stack and we must also align stack to 16 without losing the original return address, using TLS would make it possible
                        throw new NotImplementedException();

                        if(!parameters.SkipDefaultImplementation)
                        {
                            var original = Memory.ReadPointer(parameters.Address);
                            ms.Write(new byte[] { 0x48, 0x83, 0xEC, 0x08 }); // sub rsp, 8
                            ms.Write(new byte[] { 0x48, 0xB8 }); ms.Write(original.ToInt64()); // mov rax, original
                            ms.Write(new byte[] { 0xFF, 0xD0 }); // call rax
                            ms.Write(new byte[] { 0x48, 0x83, 0xC4, 0x08 }); // add rsp, 8
                        }

                        if(parameters.After != null)
                        {
                            offset_after = (int)ms.BaseStream.Position;
                            ms.Write(new byte[13]);
                        }

                        ms.Write(new byte[] { 0xC3 }); // ret
                    }
                    else
                        throw new NotImplementedException();

                    data = stream.ToArray();
                }
            }

            var alloc = Memory.Allocate(data.Length + 0x10, 0, true);
            alloc.Pin();
            Memory.WriteBytes(alloc.Address, data, true);

            if (parameters.Before != null)
                Memory.WriteHook(new HookParameters()
                {
                    Address = alloc.Address + offset_before,
                    IncludeLength = 0,
                    ReplaceLength = Main.Is64Bit ? 13 : 5,
                    ForceLongJump = Main.Is64Bit,
                    Before = parameters.Before,
                });

            if (parameters.After != null)
                Memory.WriteHook(new HookParameters()
                {
                    Address = alloc.Address + offset_after,
                    IncludeLength = 0,
                    ReplaceLength = Main.Is64Bit ? 13 : 5,
                    ForceLongJump = Main.Is64Bit,
                    Before = parameters.After,
                });

            Memory.WritePointer(parameters.Address, alloc.Address, true);
        }*/

        /// <summary>
        /// Write a .NET code hook into a specific memory address.
        /// </summary>
        /// <param name="parameters">The parameters.</param>
        /// <exception cref="System.ArgumentNullException">parameters
        /// or
        /// parameters.Address
        /// or
        /// parameters.Action</exception>
        /// <exception cref="System.InvalidOperationException">Unable to place .NET hook at address 0x + Convert(parameters.Address).ToString(X) +  - 0x + (Convert(parameters.Address) + (uint)parameters.ReplaceLength) +  because there is another hook already in place that would overlap! Previous hook was placed by  + placedBy
        /// or</exception>
        /// <exception cref="System.ArgumentException">parameters.ReplaceLength;Replace length must be at least  + requiredLength +  bytes when  + (isLongHook ? far jump : near jump) +  is used!</exception>
        /// <exception cref="System.ArgumentOutOfRangeException">parameters.IncludeLength;Include length can't be a negative value!</exception>
        /// <exception cref="System.NotImplementedException"></exception>
        public static void WriteHook(HookParameters parameters)
        {
            if (parameters == null)
                throw new ArgumentNullException("parameters");

            if (parameters.Address == IntPtr.Zero)
                throw new ArgumentNullException("parameters.Address");

            if (parameters.Before == null && parameters.After == null)
                throw new ArgumentNullException("parameters.Before && parameters.After");

            if (Main._is_initializing_plugin != 2)
                throw new InvalidOperationException("Writing code hooks is only allowed during plugin initialization!");

            Tools._Internal.HookBase handler = null;
            if (parameters.Before != null && parameters.After != null)
                handler = Tools._Internal.HookBoth.Instance;
            else if (parameters.Before != null)
                handler = Tools._Internal.HookBefore.Instance;
            else if (parameters.After != null)
                handler = Tools._Internal.HookAfter.Instance;

            bool isLongHook = false;
            IntPtr target = IntPtr.Zero;
            IntPtr include1 = IntPtr.Zero;
            IntPtr include2 = IntPtr.Zero;

            if (Main.Is64Bit && (parameters.ForceLongJump || parameters.ReplaceLength >= 13))
                isLongHook = true;

            handler.BuildHook(parameters.Address, parameters.ReplaceLength, parameters.Address, parameters.IncludeLength, isLongHook, ref target, ref include1, ref include2);
            if(!isLongHook && Main.Is64Bit)
            {
                long addr_s = parameters.Address.ToInt64();
                long addr_t = target.ToInt64() - 5;

                if (addr_t > addr_s)
                {
                    if (addr_t - addr_s <= int.MaxValue)
                    {

                    }
                    else
                        throw new InvalidOperationException();
                }
                else
                {
                    if (addr_t - addr_s >= int.MinValue)
                    {

                    }
                    else
                        throw new InvalidOperationException();
                }
            }
            
            int requiredLength = isLongHook ? 13 : 5;
            if (parameters.ReplaceLength < requiredLength)
                throw new ArgumentException("parameters.ReplaceLength", "Replace length must be at least " + requiredLength + " bytes when " + (isLongHook ? "far jump" : "near jump") + " is used!");

            if (parameters.IncludeLength < 0)
                throw new ArgumentOutOfRangeException("parameters.IncludeLength", "Include length can't be a negative value!");

            var assembly = System.Reflection.Assembly.GetCallingAssembly();
            var plugin = PluginManager.GetPlugins().FirstOrDefault(q => q.Assembly == assembly);

            HookInfo info = new HookInfo();
            info.Address = parameters.Address;
            info.Length = parameters.ReplaceLength;
            info.Assembly = assembly;
            info.Plugin = plugin;
            info.Before = parameters.Before;
            info.After = parameters.After;
            info.IsFarJump = isLongHook;
            info.Include = include1;
            info.Include2 = include2;

            HookInfo conflict = null;
            if ((conflict = AddHookIfNoOverlap(info, info.Address, info.Length)) != null)
            {
                string placedBy = (conflict.Plugin != null ? conflict.Plugin.GetInternalString() : (conflict.Assembly != null ? conflict.Assembly.GetName().FullName : "(null)")) ?? string.Empty;
                throw new InvalidOperationException("Unable to place .NET hook at address 0x" + Convert(parameters.Address).ToString("X") + " - 0x" + (Convert(parameters.Address) + (uint)parameters.ReplaceLength).ToString("X") + " because there is another hook already in place that would overlap! Previous hook was placed by " + placedBy);
            }
            HookRealMap[info.Address.ToInt64()] = info;
            HookMap[info.Address.ToInt64() + (isLongHook ? 13 : 5)] = info;
            
            byte[] source = null;

            if (!Main.Is64Bit)
                throw new NotImplementedException();
            else
                source = isLongHook ? GetHookBytesSource64_Far(parameters.Address, target) : GetHookBytesSource64_Near(parameters.Address, target);

            if (source == null || source.Length > parameters.ReplaceLength)
                throw new InvalidOperationException();

            WriteBytes(parameters.Address, source, true);
            if (parameters.ReplaceLength > requiredLength)
            {
                byte[] nops = new byte[parameters.ReplaceLength - requiredLength];
                for (int i = 0; i < nops.Length; i++)
                    nops[i] = 0x90;
                WriteBytes(parameters.Address + requiredLength, nops, true);
            }
        }
        
        /// <summary>
        /// Prepares the .NET hooking code.
        /// </summary>
        internal static void PrepareNETHook()
        {
            Main.Log.AppendLine("Preparing .NET code hooking.");

            _Invoke_Cdecl_address = InvokeCdecl_addr();
            _Invoke_CdeclF_address = InvokeCdeclF_addr();
            _Invoke_CdeclD_address = InvokeCdeclD_addr();
            
            _Argument_Jmp_Address = new IntPtr[]
            {
                _Invoke_Cdecl_address + 0x63, // arg0 type0
                _Invoke_Cdecl_address + 0x68, // arg0 type1
                _Invoke_Cdecl_address + 0x71, // arg0 type2
                _Invoke_Cdecl_address + 0x7A, // arg1 type0
                _Invoke_Cdecl_address + 0x7F, // arg1 type1
                _Invoke_Cdecl_address + 0x88, // arg1 type2
                _Invoke_Cdecl_address + 0x91, // arg2 type0
                _Invoke_Cdecl_address + 0x96, // arg2 type1
                _Invoke_Cdecl_address + 0x9F, // arg2 type2
                _Invoke_Cdecl_address + 0xA8, // arg3 type0
                _Invoke_Cdecl_address + 0xAD, // arg3 type1
                _Invoke_Cdecl_address + 0xB6, // arg3 type2
                _Invoke_Cdecl_address + 0xBF, // arg4 type0
                _Invoke_Cdecl_address + 0xBF, // arg4 type1
                _Invoke_Cdecl_address + 0xBF, // arg4 type2

                _Invoke_CdeclF_address + 0x63, // arg0 type0
                _Invoke_CdeclF_address + 0x68, // arg0 type1
                _Invoke_CdeclF_address + 0x71, // arg0 type2
                _Invoke_CdeclF_address + 0x7A, // arg1 type0
                _Invoke_CdeclF_address + 0x7F, // arg1 type1
                _Invoke_CdeclF_address + 0x88, // arg1 type2
                _Invoke_CdeclF_address + 0x91, // arg2 type0
                _Invoke_CdeclF_address + 0x96, // arg2 type1
                _Invoke_CdeclF_address + 0x9F, // arg2 type2
                _Invoke_CdeclF_address + 0xA8, // arg3 type0
                _Invoke_CdeclF_address + 0xAD, // arg3 type1
                _Invoke_CdeclF_address + 0xB6, // arg3 type2
                _Invoke_CdeclF_address + 0xBF, // arg4 type0
                _Invoke_CdeclF_address + 0xBF, // arg4 type1
                _Invoke_CdeclF_address + 0xBF, // arg4 type2

                _Invoke_CdeclD_address + 0x63, // arg0 type0
                _Invoke_CdeclD_address + 0x68, // arg0 type1
                _Invoke_CdeclD_address + 0x71, // arg0 type2
                _Invoke_CdeclD_address + 0x7A, // arg1 type0
                _Invoke_CdeclD_address + 0x7F, // arg1 type1
                _Invoke_CdeclD_address + 0x88, // arg1 type2
                _Invoke_CdeclD_address + 0x91, // arg2 type0
                _Invoke_CdeclD_address + 0x96, // arg2 type1
                _Invoke_CdeclD_address + 0x9F, // arg2 type2
                _Invoke_CdeclD_address + 0xA8, // arg3 type0
                _Invoke_CdeclD_address + 0xAD, // arg3 type1
                _Invoke_CdeclD_address + 0xB6, // arg3 type2
                _Invoke_CdeclD_address + 0xBF, // arg4 type0
                _Invoke_CdeclD_address + 0xBF, // arg4 type1
                _Invoke_CdeclD_address + 0xBF, // arg4 type2
            };

            _unmanagedDoAction = GetDoActionAddress();
            CPURegisters.Offsets = new CPURegisters.CPUOffsets();
        }

        /// <summary>
        /// Gets the in progress executing hooks.
        /// </summary>
        /// <param name="hooks">The hooks.</param>
        /// <param name="count">The count.</param>
        internal static void GetInProgressHooks(List<HookInfo> hooks, ref int count)
        {
            var tlsBase = GetCurrentTLSValue();
            if (tlsBase == IntPtr.Zero)
                return;

            count = Memory.ReadInt32(tlsBase);
            if (count == 0)
                return;

            IntPtr ptr = Memory.ReadPointer(tlsBase + (Main.Is64Bit ? 8 : 4));
            int size = GetHookContextSize();
            for(int i = 0; i < count; i++)
            {
                var addr = Memory.ReadPointer(ptr + (size - 0x18));
                var info = GetHookReal(addr);
                if (info != null)
                    hooks.Add(info);

                ptr = ptr + size;
            }
        }

        [DllImport("NetScriptFramework.Runtime.dll")]
        private static extern IntPtr GetDoActionAddress();

        [DllImport("NetScriptFramework.Runtime.dll")]
        private static extern IntPtr GetCurrentTLSValue();

        [DllImport("NetScriptFramework.Runtime.dll")]
        private static extern int GetHookContextSize();

        /// <summary>
        /// Gets the byte code for hooking at source address in 64 bit process.
        /// </summary>
        /// <param name="source">The source address.</param>
        /// <param name="target">The target where to jump.</param>
        /// <returns></returns>
        private static byte[] GetHookBytesSource64_Far(IntPtr source, IntPtr target)
        {
            // push rcx
            // mov rcx, 1234
            // call rcx
            var result = new byte[] { 0x51, 0x48, 0xB9 }.Concat(BitConverter.GetBytes(target.ToInt64())).Concat(new byte[] { 0xFF, 0xD1 }).ToArray();
#if DEBUG
            if(result.Length != 13)
                throw new InvalidOperationException();
#endif
            return result;
        }

        /// <summary>
        /// Gets the byte code for hooking at source address in 64 bit process.
        /// </summary>
        /// <param name="source">The source address.</param>
        /// <param name="target">The target where to jump.</param>
        /// <returns></returns>
        private static byte[] GetHookBytesSource64_Near(IntPtr source, IntPtr target)
        {
            // call 1234
            int value = (int)((target.ToInt64() - 5) - source.ToInt64());
            var result = new byte[] { 0xE8 }.Concat(BitConverter.GetBytes(value)).ToArray();
#if DEBUG
            if(result.Length != 5)
                throw new InvalidOperationException();
#endif
            return result;
        }
        
        internal static IntPtr _unmanagedDoAction = IntPtr.Zero;
        private static readonly Dictionary<long, HookInfo> HookMap = new Dictionary<long, HookInfo>();
        private static readonly Dictionary<long, HookInfo> HookRealMap = new Dictionary<long, HookInfo>();
        private static readonly List<Tuple<ulong, ulong, HookInfo>> HookOverlapList = new List<Tuple<ulong, ulong, HookInfo>>();

        /// <summary>
        /// Adds the hook if no overlap with other hooks.
        /// </summary>
        /// <param name="self">The self.</param>
        /// <param name="begin">The begin.</param>
        /// <param name="size">The size.</param>
        /// <returns></returns>
        private static HookInfo AddHookIfNoOverlap(HookInfo self, IntPtr begin, int size)
        {
            ulong min = Memory.Convert(begin);
            ulong max = min + (uint)size;

            var ls = HookOverlapList;
            for(int i = 0; i < ls.Count; i++)
            {
                var t = ls[i];
                ulong min_t = t.Item1;
                ulong max_t = t.Item2;

                if(min <= min_t)
                {
                    if (max > min_t)
                        return t.Item3;

                    ls.Insert(i, new Tuple<ulong, ulong, HookInfo>(min, max, self));
                    return null;
                }

                if (max_t > min)
                    return t.Item3;
            }

            ls.Add(new Tuple<ulong, ulong, HookInfo>(min, max, self));
            return null;
        }
        
        /// <summary>
        /// Gets the hook.
        /// </summary>
        /// <param name="addr">The addr.</param>
        /// <returns></returns>
        private static HookInfo GetHook(IntPtr addr)
        {
            HookInfo result = null;
            if (HookMap.TryGetValue(addr.ToInt64(), out result))
                return result;
            return null;
        }

        /// <summary>
        /// Gets the hook.
        /// </summary>
        /// <param name="addr">The addr.</param>
        /// <returns></returns>
        private static HookInfo GetHookReal(IntPtr addr)
        {
            HookInfo result = null;
            if (HookRealMap.TryGetValue(addr.ToInt64(), out result))
                return result;
            return null;
        }

        /// <summary>
        /// Invoke previously registered action. This is called from unmanaged code.
        /// </summary>
        /// <param name="cpu_address">The address to CPU register info.</param>
        /// <param name="pass">The pass.</param>
        /// <returns></returns>
        /// <exception cref="System.InvalidOperationException">Trying to invoke missing action (actionId)!</exception>
        internal static void DoAction(IntPtr cpu_address, int pass)
        {
            try
            {
                /*if (Main.IsShutdown)
                    return;*/

                // Read the hook info.
                int sz = GetHookContextSize();

                // The hooked address. This is not the actual address yet!
                var hookAddr = Memory.ReadPointer(cpu_address + sz - IntPtr.Size * 6);

                // Get action.
                var hook = GetHook(hookAddr);
                if (hook == null)
                    throw new InvalidOperationException("Trying to invoke missing hook (0x" + hookAddr.ToInt64().ToString("X") + ")!");

                // Decide handler type.
                Tools._Internal.HookBase handler = null;
                if (hook.Before == null)
                {
                    if (hook.After != null)
                        handler = Tools._Internal.HookAfter.Instance;
                    else
                        throw new InvalidOperationException("Trying to invoke hook with no handlers!");
                }
                else if (hook.After != null)
                    handler = Tools._Internal.HookBoth.Instance;
                else
                    handler = Tools._Internal.HookBefore.Instance;

                // Create CPU register info.
                var cpu = new CPURegisters(cpu_address, handler);
                
                // Fix some things according to hook.
                cpu.IP = hook.Address + hook.Length;
                cpu.Include = pass == 0 ? hook.Include : hook.Include2;
                cpu.Hook = hook.Address;
                cpu.AllowSkip = pass == 0;

                // Perform action.
                var ac = pass == 0 ? hook.Before : hook.After;
                if(ac != null)
                    ac(cpu);
            }
            catch (Exception ex)
            {
                // We can't rely on AppDomain.CurrentDomain.UnhandledException event here because if it happens in main thread the native exception handler is invoked before managed.
                Main.ProcessManagedUnhandledException(ex);
            }
        }
        
        #endregion
    }

    /// <summary>
    /// Information about a .NET code hook.
    /// </summary>
    internal sealed class HookInfo
    {
        /// <summary>
        /// The base address of hook.
        /// </summary>
        internal IntPtr Address;

        /// <summary>
        /// The length of hook.
        /// </summary>
        internal int Length;

        /// <summary>
        /// The assembly that installed the hook.
        /// </summary>
        internal System.Reflection.Assembly Assembly;

        /// <summary>
        /// The plugin associated with assembly.
        /// </summary>
        internal Plugin Plugin;

        /// <summary>
        /// The action.
        /// </summary>
        internal Action<CPURegisters> Before;

        /// <summary>
        /// The action.
        /// </summary>
        internal Action<CPURegisters> After;

        /// <summary>
        /// Is this using far jump or near?
        /// </summary>
        internal bool IsFarJump;

        /// <summary>
        /// The pointer to included code cave.
        /// </summary>
        internal IntPtr Include;

        /// <summary>
        /// The pointer to after.
        /// </summary>
        internal IntPtr Include2;
    }

    /// <summary>
    /// Contains information about a memory allocation. Also implements a disposable pattern to free the underlying memory, use
    /// Pin or Unpin methods to prevent memory from being freed even after this allocation instance reference is lost.
    /// </summary>
    /// <seealso cref="NetScriptFramework.TemporaryObject" />
    public sealed class MemoryAllocation : TemporaryObject
    {
        #region Constructors

        /// <summary>
        /// Initializes a new instance of the <see cref="MemoryAllocation"/> class.
        /// </summary>
        /// <param name="address">The address.</param>
        /// <param name="size">The size.</param>
        /// <param name="align">The align.</param>
        /// <param name="type">The type.</param>
        /// <param name="page">The page.</param>
        internal MemoryAllocation(IntPtr address, int size, int align, MemoryAllocationTypes type, CodePageAllocator page)
        {
            this.Address = address;
            this.Size = size;
            this.Align = align;
            this.Type = type;
            this.CodePage = page;
        }

        #endregion

        #region MemoryAllocation members

        /// <summary>
        /// The code page if it is code.
        /// </summary>
        private readonly CodePageAllocator CodePage;

        /// <summary>
        /// The base address of memory allocation location.
        /// </summary>
        public readonly IntPtr Address;

        /// <summary>
        /// The safe size of allocation.
        /// </summary>
        public readonly int Size;

        /// <summary>
        /// The alignment of allocation.
        /// </summary>
        public readonly int Align;

        /// <summary>
        /// The type of allocation.
        /// </summary>
        public readonly MemoryAllocationTypes Type;
        
        /// <summary>
        /// List of memory allocation types.
        /// </summary>
        public enum MemoryAllocationTypes : int
        {
            /// <summary>
            /// The memory is allocated on heap and has read + write access.
            /// </summary>
            Heap = 0,

            /// <summary>
            /// The memory is allocated in a memory page for code execution and has read + write + execute access.
            /// </summary>
            Code = 1,

            /// <summary>
            /// The memory is allocated for ANSI or Unicode string.
            /// </summary>
            String = 2,
        }

        /// <summary>
        /// Frees resources.
        /// </summary>
        /// <exception cref="System.InvalidOperationException"></exception>
        protected override void Free()
        {
            switch (this.Type)
            {
                case MemoryAllocationTypes.Heap:
                    Memory.FreeC(this.Address, this.Align != 0);
                    break;

                case MemoryAllocationTypes.Code:
                    Memory.FreeCode(this.Address, this.Size, this.CodePage);
                    break;

                case MemoryAllocationTypes.String:
                    Memory.FreeString(this.Address);
                    break;

                default:
                    throw new InvalidOperationException();
            }
        }

        #endregion
    }

    /// <summary>
    /// Implement invoke argument for native calls.
    /// </summary>
    public sealed class InvokeArgument
    {
        #region Internal members

        /// <summary>
        /// Initializes a new instance of the <see cref="InvokeArgument"/> class.
        /// </summary>
        private InvokeArgument()
        {

        }

        /// <summary>
        /// The value if it's not floating point.
        /// </summary>
        internal IntPtr ValueOther;

        /// <summary>
        /// The value if it is floating point.
        /// </summary>
        internal double ValueDouble;

        /// <summary>
        /// The value if it is floating point.
        /// </summary>
        internal float ValueFloat;

        /// <summary>
        /// The value type.
        /// </summary>
        internal int ValueType = -1;

        #endregion

        #region InvokeArgument members

        /// <summary>
        /// Performs an implicit conversion from <see cref="IntPtr"/> to <see cref="InvokeArgument"/>.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <returns>
        /// The result of the conversion.
        /// </returns>
        public static implicit operator InvokeArgument(IntPtr value)
        {
            return new InvokeArgument() { ValueOther = value, ValueType = 0 };
        }

        /// <summary>
        /// Performs an implicit conversion from <see cref="Int32"/> to <see cref="InvokeArgument"/>.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <returns>
        /// The result of the conversion.
        /// </returns>
        public static implicit operator InvokeArgument(int value)
        {
            return new InvokeArgument() { ValueOther = new IntPtr(value), ValueType = 0 };
        }

        /// <summary>
        /// Performs an implicit conversion from <see cref="System.Int64"/> to <see cref="InvokeArgument"/>.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <returns>
        /// The result of the conversion.
        /// </returns>
        public static implicit operator InvokeArgument(long value)
        {
            return new InvokeArgument() { ValueOther = new IntPtr(value), ValueType = 0 };
        }

        /// <summary>
        /// Performs an implicit conversion from <see cref="System.UInt32"/> to <see cref="InvokeArgument"/>.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <returns>
        /// The result of the conversion.
        /// </returns>
        public static implicit operator InvokeArgument(uint value)
        {
            return new InvokeArgument() { ValueOther = new IntPtr(unchecked((int)value)), ValueType = 0 };
        }

        /// <summary>
        /// Performs an implicit conversion from <see cref="System.UInt64"/> to <see cref="InvokeArgument"/>.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <returns>
        /// The result of the conversion.
        /// </returns>
        public static implicit operator InvokeArgument(ulong value)
        {
            return new InvokeArgument() { ValueOther = new IntPtr(unchecked((long)value)), ValueType = 0 };
        }

        /// <summary>
        /// Performs an implicit conversion from <see cref="System.Int16"/> to <see cref="InvokeArgument"/>.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <returns>
        /// The result of the conversion.
        /// </returns>
        public static implicit operator InvokeArgument(short value)
        {
            return new InvokeArgument() { ValueOther = new IntPtr(unchecked((ushort)value)), ValueType = 0 };
        }

        /// <summary>
        /// Performs an implicit conversion from <see cref="System.UInt16"/> to <see cref="InvokeArgument"/>.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <returns>
        /// The result of the conversion.
        /// </returns>
        public static implicit operator InvokeArgument(ushort value)
        {
            return new InvokeArgument() { ValueOther = new IntPtr(value), ValueType = 0 };
        }

        /// <summary>
        /// Performs an implicit conversion from <see cref="System.Byte"/> to <see cref="InvokeArgument"/>.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <returns>
        /// The result of the conversion.
        /// </returns>
        public static implicit operator InvokeArgument(byte value)
        {
            return new InvokeArgument() { ValueOther = new IntPtr(value), ValueType = 0 };
        }

        /// <summary>
        /// Performs an implicit conversion from <see cref="System.SByte"/> to <see cref="InvokeArgument"/>.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <returns>
        /// The result of the conversion.
        /// </returns>
        public static implicit operator InvokeArgument(sbyte value)
        {
            return new InvokeArgument() { ValueOther = new IntPtr(unchecked((byte)value)), ValueType = 0 };
        }

        /// <summary>
        /// Performs an implicit conversion from <see cref="System.Boolean"/> to <see cref="InvokeArgument"/>.
        /// </summary>
        /// <param name="value">if set to <c>true</c> [value].</param>
        /// <returns>
        /// The result of the conversion.
        /// </returns>
        public static implicit operator InvokeArgument(bool value)
        {
            return new InvokeArgument() { ValueOther = new IntPtr(value ? (int)1 : (int)0), ValueType = 0 };
        }

        /// <summary>
        /// Performs an implicit conversion from <see cref="System.Double"/> to <see cref="InvokeArgument"/>.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <returns>
        /// The result of the conversion.
        /// </returns>
        public static implicit operator InvokeArgument(double value)
        {
            if (!Main.Is64Bit)
            {
                // This is correct.
                byte[] converted = BitConverter.GetBytes((float)value);
                return new InvokeArgument() { ValueOther = new IntPtr(BitConverter.ToInt32(converted, 0)), ValueType = 0 };
            }
            return new InvokeArgument() { ValueDouble = value, ValueType = 2 };
        }

        /// <summary>
        /// Performs an implicit conversion from <see cref="System.Single"/> to <see cref="InvokeArgument"/>.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <returns>
        /// The result of the conversion.
        /// </returns>
        public static implicit operator InvokeArgument(float value)
        {
            if (!Main.Is64Bit)
            {
                // This is correct.
                byte[] converted = BitConverter.GetBytes(value);
                return new InvokeArgument() { ValueOther = new IntPtr(BitConverter.ToInt32(converted, 0)), ValueType = 0 };
            }
            return new InvokeArgument() { ValueFloat = value, ValueType = 1 };
        }

        #endregion
    }

    /// <summary>
    /// Hook parameters for vtable entry.
    /// </summary>
    public sealed class VTableHookParameters
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="VTableHookParameters"/> class.
        /// </summary>
        public VTableHookParameters()
        {

        }

        /// <summary>
        /// Gets or sets the address of the entry in vtable.
        /// </summary>
        /// <value>
        /// The address.
        /// </value>
        public IntPtr Address
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets a value indicating whether to skip default implementation and not call what was in the vtable before this.
        /// </summary>
        /// <value>
        /// <c>true</c> if [skip default implementation]; otherwise, <c>false</c>.
        /// </value>
        public bool SkipDefaultImplementation
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the action to run when hooked code is triggered. This action will run before included code and may read or write CPU registers.
        /// </summary>
        /// <value>
        /// The action.
        /// </value>
        public Action<CPURegisters> Before
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the action to run when hooked code is triggered. This action will run after included code and may read or write CPU registers.
        /// </summary>
        /// <value>
        /// The action.
        /// </value>
        public Action<CPURegisters> After
        {
            get;
            set;
        }
    }
    
    /// <summary>
    /// Parameters for creating a hook.
    /// </summary>
    public sealed class HookParameters
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="HookParameters"/> class.
        /// </summary>
        public HookParameters()
        {

        }

        /// <summary>
        /// Gets or sets the start address of hook.
        /// </summary>
        /// <value>
        /// The address.
        /// </value>
        public IntPtr Address
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the length of the replaced code in bytes. The code is replaced due to placing a hook there. Must be at least 5 bytes in 32-bit process and 13 bytes in 64-bit process. If near jump
        /// hooking is enabled in the module then it may be 5 bytes also in 64-bit process. Execution of code after hook will resume at "Address + ReplaceLength" unless the "IP" register is modified in
        /// hook action.
        /// </summary>
        /// <value>
        /// The length of the replaced code.
        /// </value>
        public int ReplaceLength
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the length of the included code in bytes. This code will be included automatically and be run after the hook action if set. Be careful not to include any location-specific code
        /// or it will most likely crash the process.
        /// </summary>
        /// <value>
        /// The length of the included code.
        /// </value>
        public int IncludeLength
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the action to run when hooked code is triggered. This action will run before included code and may read or write CPU registers.
        /// </summary>
        /// <value>
        /// The action.
        /// </value>
        public Action<CPURegisters> Before
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the action to run when hooked code is triggered. This action will run after included code and may read or write CPU registers.
        /// </summary>
        /// <value>
        /// The action.
        /// </value>
        public Action<CPURegisters> After
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets a value indicating whether to force long jump that uses 13 bytes instead of the 5 byte one. This only has any effect in 64 bit mode.
        /// </summary>
        /// <value>
        ///   <c>true</c> if [force long jump]; otherwise, <c>false</c>.
        /// </value>
        public bool ForceLongJump
        {
            get;
            set;
        } = false;
    }

    /// <summary>
	/// Use this for code allocations. VirtualAlloc is used to allocate whole page of memory and is very wasteful for this reason.
	/// So we use our own backend allocator to use same code page for multiple allocations to save memory.
	/// </summary>
	internal sealed class CodePageAllocator : IDisposable
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="CodePageAllocator"/> class.
        /// </summary>
        /// <param name="size">The full size of code page.</param>
        internal CodePageAllocator(int size)
        {
            if (size <= 0)
                throw new ArgumentOutOfRangeException("size", "Size must be positive!");

            Size = size;
            Available = new SortedDictionary<ulong, int>();
            Begin = VirtualAlloc(IntPtr.Zero, new IntPtr(size), 0x3000, 0x40);
            if (Begin == IntPtr.Zero)
                throw new OutOfMemoryException("Failed to allocate memory for code page!");
            End = Begin + size;
            Available[Memory.Convert(Begin)] = size;
        }

        /// <summary>
        /// The size of code page.
        /// </summary>
        internal readonly int Size;

        /// <summary>
        /// Gets allocated memory from page with specified size. If the allocation is not possible in this code page this
        /// function returns null.
        /// </summary>
        /// <param name="size">The size of allocation.</param>
        /// <returns></returns>
        internal MemoryAllocation Get(int size)
        {
            if (Available.Count == 0)
                return null;

            ulong found = 0;
            int foundTotal = 0;
            foreach (var x in Available)

            {
                if (x.Value >= size)
                {
                    found = x.Key;
                    foundTotal = x.Value;
                    break;
                }
            }

            if (found == 0)
                return null;

            Available.Remove(found);
            if (foundTotal > size)
                Available[found + (uint)size] = foundTotal - size;

            return new MemoryAllocation(Memory.Convert(found), size, 0, MemoryAllocation.MemoryAllocationTypes.Code, this);
        }

        /// <summary>
        /// Frees previously allocated memory from this code page.
        /// </summary>
        /// <param name="addr">The base address of allocation.</param>
        /// <param name="size">The size of allocation.</param>
        internal void Free(IntPtr addr, int size)
        {
            ulong addr_u = Memory.Convert(addr);
            ulong keyFound = 0;
            int valueFound = 0;
            int found = 0;
            foreach (var x in Available)

            {
                if (x.Key + (uint)x.Value == addr_u)
                {
                    keyFound = x.Key;
                    valueFound = x.Value;
                    found = 1;
                    break;
                }
                else if (addr_u + (uint)size == x.Key)
                {
                    keyFound = x.Key;
                    valueFound = x.Value;
                    found = 2;
                    break;
                }
            }

            if (found == 0)
                Available[addr_u] = size;
            else if (found == 1)
                Available[keyFound] = valueFound + size;
            else if (found == 2)
            {
                Available.Remove(keyFound);
                Available[addr_u] = valueFound + size;
            }
            else
                throw new NotImplementedException();
        }

        /// <summary>
        /// The begin pointer of memory page.
        /// </summary>
        private IntPtr Begin = IntPtr.Zero;

        /// <summary>
        /// The end pointer of memory page.
        /// </summary>
        private IntPtr End = IntPtr.Zero;

        /// <summary>
        /// The available memory ranges.
        /// </summary>
        private readonly SortedDictionary<ulong, int> Available = null;

        #region Api calls

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern IntPtr VirtualAlloc(IntPtr lpAddress, IntPtr dwSize, uint lAllocationType, uint flProtect);

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern bool VirtualFree(IntPtr lpAddress, IntPtr dwSize, uint dwFreeType);

        #endregion

        #region IDisposable interface

        /// <summary>
        /// The disposed value to avoid redundant calls.
        /// </summary>
        private bool disposedValue = false;

        /// <summary>
        /// Releases unmanaged and - optionally - managed resources.
        /// </summary>
        /// <param name="disposing"><c>true</c> to release both managed and unmanaged resources; <c>false</c> to release only unmanaged resources.</param>
        private void Dispose(bool disposing)
        {
            if (!disposedValue)
            {
                //if (disposing) { }

                if (Begin != IntPtr.Zero)
                {
                    VirtualFree(Begin, IntPtr.Zero, 0x8000);
                    Begin = IntPtr.Zero;
                }

                disposedValue = true;
            }
        }

        /// <summary>
        /// Finalizes an instance of the <see cref="CodePageAllocator"/> class.
        /// </summary>
        ~CodePageAllocator()
        {
            Dispose(false);
        }

        /// <summary>
        /// Performs application-defined tasks associated with freeing, releasing, or resetting unmanaged resources.
        /// </summary>
        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        #endregion
    };

    /// <summary>
    /// Contains information about CPU registers at a specific location in hooked code.
    /// </summary>
    public sealed class CPURegisters
    {
        #region Constructors

        /// <summary>
        /// Initializes a new instance of the <see cref="CPURegisters"/> class.
        /// </summary>
        /// <param name="address">The address.</param>
        /// <param name="isFromHook">Is this from hook?</param>
        internal CPURegisters(IntPtr address, Tools._Internal.HookBase isFromHook)
        {
            this.Address = address;
            this.IsFromHook = isFromHook;

            var handler = this.IsFromHook;
            if(handler != null)
            {
                this.AX = Memory.ReadPointer(this.Address + VerifyOffset(Offsets.Hook_AX, "Reading Hook AX register"));
                this.CX = Memory.ReadPointer(this.Address + VerifyOffset(Offsets.Hook_CX, "Reading Hook CX register"));
            }
        }

        #endregion

        /// <summary>
        /// Is from hook?
        /// </summary>
        private readonly Tools._Internal.HookBase IsFromHook;

        #region CPURegisters members

        /// <summary>
        /// Verifies the offset.
        /// </summary>
        /// <param name="offset">The offset.</param>
        /// <param name="name">The name.</param>
        /// <returns></returns>
        /// <exception cref="System.NotSupportedException"></exception>
        private static int VerifyOffset(int offset, string name)
        {
            if (offset < 0)
                throw new NotSupportedException(name + " is not supported!");
            return offset;
        }
        
        /// <summary>
        /// Gets or sets the value in AX register.
        /// </summary>
        /// <value>
        /// The value in AX register.
        /// </value>
        public IntPtr AX
        {
            get
            {
                return Memory.ReadPointer(this.Address + VerifyOffset(Offsets.AX, "Reading AX register"));
            }
            set
            {
                Memory.WritePointer(this.Address + VerifyOffset(Offsets.AX, "Writing AX register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in BX register.
        /// </summary>
        /// <value>
        /// The value in BX register.
        /// </value>
        public IntPtr BX
        {
            get
            {
                return Memory.ReadPointer(this.Address + VerifyOffset(Offsets.BX, "Reading BX register"));
            }
            set
            {
                Memory.WritePointer(this.Address + VerifyOffset(Offsets.BX, "Writing BX register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in CX register.
        /// </summary>
        /// <value>
        /// The value in CX register.
        /// </value>
        public IntPtr CX
        {
            get
            {
                return Memory.ReadPointer(this.Address + VerifyOffset(Offsets.CX, "Reading CX register"));
            }
            set
            {
                Memory.WritePointer(this.Address + VerifyOffset(Offsets.CX, "Writing CX register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in DX register.
        /// </summary>
        /// <value>
        /// The value in DX register.
        /// </value>
        public IntPtr DX
        {
            get
            {
                return Memory.ReadPointer(this.Address + VerifyOffset(Offsets.DX, "Reading DX register"));
            }
            set
            {
                Memory.WritePointer(this.Address + VerifyOffset(Offsets.DX, "Writing DX register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in DI register.
        /// </summary>
        /// <value>
        /// The value in DI register.
        /// </value>
        public IntPtr DI
        {
            get
            {
                return Memory.ReadPointer(this.Address + VerifyOffset(Offsets.DI, "Reading DI register"));
            }
            set
            {
                Memory.WritePointer(this.Address + VerifyOffset(Offsets.DI, "Writing DI register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in SI register.
        /// </summary>
        /// <value>
        /// The value in SI register.
        /// </value>
        public IntPtr SI
        {
            get
            {
                return Memory.ReadPointer(this.Address + VerifyOffset(Offsets.SI, "Reading SI register"));
            }
            set
            {
                Memory.WritePointer(this.Address + VerifyOffset(Offsets.SI, "Writing SI register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in BP register.
        /// </summary>
        /// <value>
        /// The value in BP register.
        /// </value>
        public IntPtr BP
        {
            get
            {
                return Memory.ReadPointer(this.Address + VerifyOffset(Offsets.BP, "Reading BP register"));
            }
            set
            {
                Memory.WritePointer(this.Address + VerifyOffset(Offsets.BP, "Writing BP register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in SP register.
        /// </summary>
        /// <value>
        /// The value in SP register.
        /// </value>
        public IntPtr SP
        {
            get
            {
                return Memory.ReadPointer(this.Address + VerifyOffset(Offsets.SP, "Reading SP register"));
            }
            set
            {
                Memory.WritePointer(this.Address + VerifyOffset(Offsets.SP, "Writing SP register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in FLAGS register.
        /// </summary>
        /// <value>
        /// The value in FLAGS register.
        /// </value>
        public IntPtr FLAGS
        {
            get
            {
                return Memory.ReadPointer(this.Address + VerifyOffset(Offsets.FLAGS, "Reading FLAGS register"));
            }
            set
            {
                Memory.WritePointer(this.Address + VerifyOffset(Offsets.FLAGS, "Writing FLAGS register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the IP value. In this context the value means the address where execution of native code will
        /// continue. Changing this will work like an absolute jump.
        /// </summary>
        /// <value>
        /// The IP value.
        /// </value>
        public IntPtr IP
        {
            get
            {
                int offset = this.IsFromHook != null ? Offsets.ReturnAfter : Offsets.IP;
                offset = VerifyOffset(offset, "Reading IP register");
                return Memory.ReadPointer(this.Address + offset);
            }
            set
            {
                int offset = this.IsFromHook != null ? Offsets.ReturnAfter : Offsets.IP;
                offset = VerifyOffset(offset, "Writing IP register");
                Memory.WritePointer(this.Address + offset, value);
            }
        }

        /// <summary>
        /// Gets the hooked address. This is the base address where the .NET hook was placed. Returns zero if this is not a hooked call.
        /// </summary>
        /// <value>
        /// The hooked address.
        /// </value>
        public IntPtr Hook
        {
            get
            {
                if (this.IsFromHook == null)
                    return IntPtr.Zero;
                return Memory.ReadPointer(this.Address + VerifyOffset(Offsets.Hook, "Reading hook address"));
            }
            internal set
            {
                if (this.IsFromHook == null)
                    throw new InvalidOperationException();
                Memory.WritePointer(this.Address + VerifyOffset(Offsets.Hook, "Writing hook address"), value);
            }
        }

        /// <summary>
        /// Gets or sets the original hook.
        /// </summary>
        /// <value>
        /// The original hook.
        /// </value>
        internal IntPtr OriginalHook
        {
            get
            {
                if (this.IsFromHook == null)
                    return IntPtr.Zero;
                return Memory.ReadPointer(this.Address + VerifyOffset(Offsets.Hook_OrigReturnAfter, "Reading original hook address"));
            }
            set
            {
                if (this.IsFromHook == null)
                    throw new InvalidOperationException();
                Memory.WritePointer(this.Address + VerifyOffset(Offsets.Hook_OrigReturnAfter, "Writing original hook address"), value);
            }
        }

        /// <summary>
        /// Skip executing the included assembly code after this hook call.
        /// </summary>
        public void Skip()
        {
            if (this.IsFromHook == null)
                throw new InvalidOperationException("This is only available when executing a hook!");

            if(this.AllowSkip)
                this.Include = this.IsFromHook.EmptyInclude;
        }

        /// <summary>
        /// Gets the depth of hooked call on current thread. Returns negative value if this is not a hooked call.
        /// </summary>
        /// <value>
        /// The depth.
        /// </value>
        /// <exception cref="System.NotSupportedException">Depth checking is not supported!</exception>
        public int Depth
        {
            get
            {
                if (this.IsFromHook == null)
                    return -1;
                return Memory.ReadInt32(this.Address + VerifyOffset(Offsets.Depth, "Depth checking"));
            }
        }

        /// <summary>
        /// Gets or sets the include code pointer.
        /// </summary>
        /// <value>
        /// The include.
        /// </value>
        internal IntPtr Include
        {
            get
            {
                return Memory.ReadPointer(this.Address + Offsets.IP);
            }
            set
            {
                Memory.WritePointer(this.Address + Offsets.IP, value);
            }
        }

        /// <summary>
        /// Gets or sets a value indicating whether to allow skip.
        /// </summary>
        /// <value>
        ///   <c>true</c> if [allow skip]; otherwise, <c>false</c>.
        /// </value>
        internal bool AllowSkip
        {
            get;
            set;
        } = false;
        
        /// <summary>
        /// Gets or sets the value in XMM0 register.
        /// </summary>
        /// <value>
        /// The value in XMM0 register.
        /// </value>
        public double XMM0
        {
            get
            {
                return Memory.ReadDouble128(this.Address + VerifyOffset(Offsets.XMM0, "Reading XMM0 register"));
            }
            set
            {
                Memory.WriteDouble128(this.Address + VerifyOffset(Offsets.XMM0, "Writing XMM0 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM1 register.
        /// </summary>
        /// <value>
        /// The value in XMM1 register.
        /// </value>
        public double XMM1
        {
            get
            {
                return Memory.ReadDouble128(this.Address + VerifyOffset(Offsets.XMM1, "Reading XMM1 register"));
            }
            set
            {
                Memory.WriteDouble128(this.Address + VerifyOffset(Offsets.XMM1, "Writing XMM1 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM2 register.
        /// </summary>
        /// <value>
        /// The value in XMM2 register.
        /// </value>
        public double XMM2
        {
            get
            {
                return Memory.ReadDouble128(this.Address + VerifyOffset(Offsets.XMM2, "Reading XMM2 register"));
            }
            set
            {
                Memory.WriteDouble128(this.Address + VerifyOffset(Offsets.XMM2, "Writing XMM2 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM3 register.
        /// </summary>
        /// <value>
        /// The value in XMM3 register.
        /// </value>
        public double XMM3
        {
            get
            {
                return Memory.ReadDouble128(this.Address + VerifyOffset(Offsets.XMM3, "Reading XMM3 register"));
            }
            set
            {
                Memory.WriteDouble128(this.Address + VerifyOffset(Offsets.XMM3, "Writing XMM3 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM4 register.
        /// </summary>
        /// <value>
        /// The value in XMM4 register.
        /// </value>
        public double XMM4
        {
            get
            {
                return Memory.ReadDouble128(this.Address + VerifyOffset(Offsets.XMM4, "Reading XMM4 register"));
            }
            set
            {
                Memory.WriteDouble128(this.Address + VerifyOffset(Offsets.XMM4, "Writing XMM4 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM5 register.
        /// </summary>
        /// <value>
        /// The value in XMM5 register.
        /// </value>
        public double XMM5
        {
            get
            {
                return Memory.ReadDouble128(this.Address + VerifyOffset(Offsets.XMM5, "Reading XMM5 register"));
            }
            set
            {
                Memory.WriteDouble128(this.Address + VerifyOffset(Offsets.XMM5, "Writing XMM5 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM6 register.
        /// </summary>
        /// <value>
        /// The value in XMM6 register.
        /// </value>
        public double XMM6
        {
            get
            {
                return Memory.ReadDouble128(this.Address + VerifyOffset(Offsets.XMM6, "Reading XMM6 register"));
            }
            set
            {
                Memory.WriteDouble128(this.Address + VerifyOffset(Offsets.XMM6, "Writing XMM6 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM7 register.
        /// </summary>
        /// <value>
        /// The value in XMM7 register.
        /// </value>
        public double XMM7
        {
            get
            {
                return Memory.ReadDouble128(this.Address + VerifyOffset(Offsets.XMM7, "Reading XMM7 register"));
            }
            set
            {
                Memory.WriteDouble128(this.Address + VerifyOffset(Offsets.XMM7, "Writing XMM7 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM8 register. This is not available in 32 bit environment and will throw an
        /// exception!
        /// </summary>
        /// <value>
        /// The value in XMM8 register.
        /// </value>
        public double XMM8
        {
            get
            {
                return Memory.ReadDouble128(this.Address + VerifyOffset(Offsets.XMM8, "Reading XMM8 register"));
            }
            set
            {
                Memory.WriteDouble128(this.Address + VerifyOffset(Offsets.XMM8, "Writing XMM8 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM9 register. This is not available in 32 bit environment and will throw an
        /// exception!
        /// </summary>
        /// <value>
        /// The value in XMM9 register.
        /// </value>
        public double XMM9
        {
            get
            {
                return Memory.ReadDouble128(this.Address + VerifyOffset(Offsets.XMM9, "Reading XMM9 register"));
            }
            set
            {
                Memory.WriteDouble128(this.Address + VerifyOffset(Offsets.XMM9, "Writing XMM9 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM10 register. This is not available in 32 bit environment and will throw an
        /// exception!
        /// </summary>
        /// <value>
        /// The value in XMM10 register.
        /// </value>
        public double XMM10
        {
            get
            {
                return Memory.ReadDouble128(this.Address + VerifyOffset(Offsets.XMM10, "Reading XMM10 register"));
            }
            set
            {
                Memory.WriteDouble128(this.Address + VerifyOffset(Offsets.XMM10, "Writing XMM10 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM11 register. This is not available in 32 bit environment and will throw an
        /// exception!
        /// </summary>
        /// <value>
        /// The value in XMM11 register.
        /// </value>
        public double XMM11
        {
            get
            {
                return Memory.ReadDouble128(this.Address + VerifyOffset(Offsets.XMM11, "Reading XMM11 register"));
            }
            set
            {
                Memory.WriteDouble128(this.Address + VerifyOffset(Offsets.XMM11, "Writing XMM11 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM12 register. This is not available in 32 bit environment and will throw an
        /// exception!
        /// </summary>
        /// <value>
        /// The value in XMM12 register.
        /// </value>
        public double XMM12
        {
            get
            {
                return Memory.ReadDouble128(this.Address + VerifyOffset(Offsets.XMM12, "Reading XMM12 register"));
            }
            set
            {
                Memory.WriteDouble128(this.Address + VerifyOffset(Offsets.XMM12, "Writing XMM12 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM13 register. This is not available in 32 bit environment and will throw an
        /// exception!
        /// </summary>
        /// <value>
        /// The value in XMM13 register.
        /// </value>
        public double XMM13
        {
            get
            {
                return Memory.ReadDouble128(this.Address + VerifyOffset(Offsets.XMM13, "Reading XMM13 register"));
            }
            set
            {
                Memory.WriteDouble128(this.Address + VerifyOffset(Offsets.XMM13, "Writing XMM13 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM14 register. This is not available in 32 bit environment and will throw an
        /// exception!
        /// </summary>
        /// <value>
        /// The value in XMM14 register.
        /// </value>
        public double XMM14
        {
            get
            {
                return Memory.ReadDouble128(this.Address + VerifyOffset(Offsets.XMM14, "Reading XMM14 register"));
            }
            set
            {
                Memory.WriteDouble128(this.Address + VerifyOffset(Offsets.XMM14, "Writing XMM14 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM15 register. This is not available in 32 bit environment and will throw an
        /// exception!
        /// </summary>
        /// <value>
        /// The value in XMM15 register.
        /// </value>
        public double XMM15
        {
            get
            {
                return Memory.ReadDouble128(this.Address + VerifyOffset(Offsets.XMM15, "Reading XMM15 register"));
            }
            set
            {
                Memory.WriteDouble128(this.Address + VerifyOffset(Offsets.XMM15, "Writing XMM15 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM0 register.
        /// </summary>
        /// <value>
        /// The value in XMM0 register.
        /// </value>
        public float XMM0f
        {
            get
            {
                return Memory.ReadFloat128(this.Address + VerifyOffset(Offsets.XMM0, "Reading XMM0 register"));
            }
            set
            {
                Memory.WriteFloat128(this.Address + VerifyOffset(Offsets.XMM0, "Writing XMM0 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM1 register.
        /// </summary>
        /// <value>
        /// The value in XMM1 register.
        /// </value>
        public float XMM1f
        {
            get
            {
                return Memory.ReadFloat128(this.Address + VerifyOffset(Offsets.XMM1, "Reading XMM1 register"));
            }
            set
            {
                Memory.WriteFloat128(this.Address + VerifyOffset(Offsets.XMM1, "Writing XMM1 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM2 register.
        /// </summary>
        /// <value>
        /// The value in XMM2 register.
        /// </value>
        public float XMM2f
        {
            get
            {
                return Memory.ReadFloat128(this.Address + VerifyOffset(Offsets.XMM2, "Reading XMM2 register"));
            }
            set
            {
                Memory.WriteFloat128(this.Address + VerifyOffset(Offsets.XMM2, "Writing XMM2 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM3 register.
        /// </summary>
        /// <value>
        /// The value in XMM3 register.
        /// </value>
        public float XMM3f
        {
            get
            {
                return Memory.ReadFloat128(this.Address + VerifyOffset(Offsets.XMM3, "Reading XMM3 register"));
            }
            set
            {
                Memory.WriteFloat128(this.Address + VerifyOffset(Offsets.XMM3, "Writing XMM3 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM4 register.
        /// </summary>
        /// <value>
        /// The value in XMM4 register.
        /// </value>
        public float XMM4f
        {
            get
            {
                return Memory.ReadFloat128(this.Address + VerifyOffset(Offsets.XMM4, "Reading XMM4 register"));
            }
            set
            {
                Memory.WriteFloat128(this.Address + VerifyOffset(Offsets.XMM4, "Writing XMM4 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM5 register.
        /// </summary>
        /// <value>
        /// The value in XMM5 register.
        /// </value>
        public float XMM5f
        {
            get
            {
                return Memory.ReadFloat128(this.Address + VerifyOffset(Offsets.XMM5, "Reading XMM5 register"));
            }
            set
            {
                Memory.WriteFloat128(this.Address + VerifyOffset(Offsets.XMM5, "Writing XMM5 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM6 register.
        /// </summary>
        /// <value>
        /// The value in XMM6 register.
        /// </value>
        public float XMM6f
        {
            get
            {
                return Memory.ReadFloat128(this.Address + VerifyOffset(Offsets.XMM6, "Reading XMM6 register"));
            }
            set
            {
                Memory.WriteFloat128(this.Address + VerifyOffset(Offsets.XMM6, "Writing XMM6 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM7 register.
        /// </summary>
        /// <value>
        /// The value in XMM7 register.
        /// </value>
        public float XMM7f
        {
            get
            {
                return Memory.ReadFloat128(this.Address + VerifyOffset(Offsets.XMM7, "Reading XMM7 register"));
            }
            set
            {
                Memory.WriteFloat128(this.Address + VerifyOffset(Offsets.XMM7, "Writing XMM7 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM8 register. This is not available in 32 bit environment and will throw an
        /// exception!
        /// </summary>
        /// <value>
        /// The value in XMM8 register.
        /// </value>
        public float XMM8f
        {
            get
            {
                return Memory.ReadFloat128(this.Address + VerifyOffset(Offsets.XMM8, "Reading XMM8 register"));
            }
            set
            {
                Memory.WriteFloat128(this.Address + VerifyOffset(Offsets.XMM8, "Writing XMM8 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM9 register. This is not available in 32 bit environment and will throw an
        /// exception!
        /// </summary>
        /// <value>
        /// The value in XMM9 register.
        /// </value>
        public float XMM9f
        {
            get
            {
                return Memory.ReadFloat128(this.Address + VerifyOffset(Offsets.XMM9, "Reading XMM9 register"));
            }
            set
            {
                Memory.WriteFloat128(this.Address + VerifyOffset(Offsets.XMM9, "Writing XMM9 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM10 register. This is not available in 32 bit environment and will throw an
        /// exception!
        /// </summary>
        /// <value>
        /// The value in XMM10 register.
        /// </value>
        public float XMM10f
        {
            get
            {
                return Memory.ReadFloat128(this.Address + VerifyOffset(Offsets.XMM10, "Reading XMM10 register"));
            }
            set
            {
                Memory.WriteFloat128(this.Address + VerifyOffset(Offsets.XMM10, "Writing XMM10 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM11 register. This is not available in 32 bit environment and will throw an
        /// exception!
        /// </summary>
        /// <value>
        /// The value in XMM11 register.
        /// </value>
        public float XMM11f
        {
            get
            {
                return Memory.ReadFloat128(this.Address + VerifyOffset(Offsets.XMM11, "Reading XMM11 register"));
            }
            set
            {
                Memory.WriteFloat128(this.Address + VerifyOffset(Offsets.XMM11, "Writing XMM11 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM12 register. This is not available in 32 bit environment and will throw an
        /// exception!
        /// </summary>
        /// <value>
        /// The value in XMM12 register.
        /// </value>
        public float XMM12f
        {
            get
            {
                return Memory.ReadFloat128(this.Address + VerifyOffset(Offsets.XMM12, "Reading XMM12 register"));
            }
            set
            {
                Memory.WriteFloat128(this.Address + VerifyOffset(Offsets.XMM12, "Writing XMM12 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM13 register. This is not available in 32 bit environment and will throw an
        /// exception!
        /// </summary>
        /// <value>
        /// The value in XMM13 register.
        /// </value>
        public float XMM13f
        {
            get
            {
                return Memory.ReadFloat128(this.Address + VerifyOffset(Offsets.XMM13, "Reading XMM13 register"));
            }
            set
            {
                Memory.WriteFloat128(this.Address + VerifyOffset(Offsets.XMM13, "Writing XMM13 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM14 register. This is not available in 32 bit environment and will throw an
        /// exception!
        /// </summary>
        /// <value>
        /// The value in XMM14 register.
        /// </value>
        public float XMM14f
        {
            get
            {
                return Memory.ReadFloat128(this.Address + VerifyOffset(Offsets.XMM14, "Reading XMM14 register"));
            }
            set
            {
                Memory.WriteFloat128(this.Address + VerifyOffset(Offsets.XMM14, "Writing XMM14 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in XMM15 register. This is not available in 32 bit environment and will throw an
        /// exception!
        /// </summary>
        /// <value>
        /// The value in XMM15 register.
        /// </value>
        public float XMM15f
        {
            get
            {
                return Memory.ReadFloat128(this.Address + VerifyOffset(Offsets.XMM15, "Reading XMM15 register"));
            }
            set
            {
                Memory.WriteFloat128(this.Address + VerifyOffset(Offsets.XMM15, "Writing XMM15 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in R8 register. This is not available in 32 bit environment and will throw an
        /// exception!
        /// </summary>
        /// <value>
        /// The value in R8 register.
        /// </value>
        public IntPtr R8
        {
            get
            {
                return Memory.ReadPointer(this.Address + VerifyOffset(Offsets.R8, "Reading R8 register"));
            }
            set
            {
                Memory.WritePointer(this.Address + VerifyOffset(Offsets.R8, "Writing R8 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in R9 register. This is not available in 32 bit environment and will throw an
        /// exception!
        /// </summary>
        /// <value>
        /// The value in R9 register.
        /// </value>
        public IntPtr R9
        {
            get
            {
                return Memory.ReadPointer(this.Address + VerifyOffset(Offsets.R9, "Reading R9 register"));
            }
            set
            {
                Memory.WritePointer(this.Address + VerifyOffset(Offsets.R9, "Writing R9 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in R10 register. This is not available in 32 bit environment and will throw an
        /// exception!
        /// </summary>
        /// <value>
        /// The value in R10 register.
        /// </value>
        public IntPtr R10
        {
            get
            {
                return Memory.ReadPointer(this.Address + VerifyOffset(Offsets.R10, "Reading R10 register"));
            }
            set
            {
                Memory.WritePointer(this.Address + VerifyOffset(Offsets.R10, "Writing R10 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in R11 register. This is not available in 32 bit environment and will throw an
        /// exception!
        /// </summary>
        /// <value>
        /// The value in R11 register.
        /// </value>
        public IntPtr R11
        {
            get
            {
                return Memory.ReadPointer(this.Address + VerifyOffset(Offsets.R11, "Reading R11 register"));
            }
            set
            {
                Memory.WritePointer(this.Address + VerifyOffset(Offsets.R11, "Writing R11 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in R12 register. This is not available in 32 bit environment and will throw an
        /// exception!
        /// </summary>
        /// <value>
        /// The value in R12 register.
        /// </value>
        public IntPtr R12
        {
            get
            {
                return Memory.ReadPointer(this.Address + VerifyOffset(Offsets.R12, "Reading R12 register"));
            }
            set
            {
                Memory.WritePointer(this.Address + VerifyOffset(Offsets.R12, "Writing R12 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in R13 register. This is not available in 32 bit environment and will throw an
        /// exception!
        /// </summary>
        /// <value>
        /// The value in R13 register.
        /// </value>
        public IntPtr R13
        {
            get
            {
                return Memory.ReadPointer(this.Address + VerifyOffset(Offsets.R13, "Reading R13 register"));
            }
            set
            {
                Memory.WritePointer(this.Address + VerifyOffset(Offsets.R13, "Writing R13 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in R14 register. This is not available in 32 bit environment and will throw an
        /// exception!
        /// </summary>
        /// <value>
        /// The value in R14 register.
        /// </value>
        public IntPtr R14
        {
            get
            {
                return Memory.ReadPointer(this.Address + VerifyOffset(Offsets.R14, "Reading R14 register"));
            }
            set
            {
                Memory.WritePointer(this.Address + VerifyOffset(Offsets.R14, "Writing R14 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in R15 register. This is not available in 32 bit environment and will throw an
        /// exception!
        /// </summary>
        /// <value>
        /// The value in R15 register.
        /// </value>
        public IntPtr R15
        {
            get
            {
                return Memory.ReadPointer(this.Address + VerifyOffset(Offsets.R15, "Reading R15 register"));
            }
            set
            {
                Memory.WritePointer(this.Address + VerifyOffset(Offsets.R15, "Writing R15 register"), value);
            }
        }

        /// <summary>
        /// Gets or sets the value in ST0 register. If STCount is less or equal to the number at index then this will
        /// throw an exception! This is only available in 32-bit at the moment.
        /// </summary>
        /// <value>
        /// The value in ST0 register.
        /// </value>
        public double ST0
        {
            get
            {
                int o = VerifyOffset(Offsets.ST0, "Reading ST0 register");
                if (this.STCount <= 0)
                    throw new IndexOutOfRangeException("This register is empty and can't be accessed!");
                return Memory.ReadDouble(this.Address + o);
            }
            set
            {
                int o = VerifyOffset(Offsets.ST0, "Writing ST0 register");
                if (this.STCount <= 0)
                    throw new IndexOutOfRangeException("This register is empty and can't be accessed!");
                Memory.WriteDouble(this.Address + o, value);
            }
        }

        /// <summary>
        /// Gets or sets the value in ST1 register. If STCount is less or equal to the number at index then this will
        /// throw an exception! This is only available in 32-bit at the moment.
        /// </summary>
        /// <value>
        /// The value in ST1 register.
        /// </value>
        public double ST1
        {
            get
            {
                int o = VerifyOffset(Offsets.ST1, "Reading ST1 register");
                if (this.STCount <= 1)
                    throw new IndexOutOfRangeException("This register is empty and can't be accessed!");
                return Memory.ReadDouble(this.Address + o);
            }
            set
            {
                int o = VerifyOffset(Offsets.ST1, "Writing ST1 register");
                if (this.STCount <= 1)
                    throw new IndexOutOfRangeException("This register is empty and can't be accessed!");
                Memory.WriteDouble(this.Address + o, value);
            }
        }

        /// <summary>
        /// Gets or sets the value in ST2 register. If STCount is less or equal to the number at index then this will
        /// throw an exception! This is only available in 32-bit at the moment.
        /// </summary>
        /// <value>
        /// The value in ST2 register.
        /// </value>
        public double ST2
        {
            get
            {
                int o = VerifyOffset(Offsets.ST2, "Reading ST2 register");
                if (this.STCount <= 2)
                    throw new IndexOutOfRangeException("This register is empty and can't be accessed!");
                return Memory.ReadDouble(this.Address + o);
            }
            set
            {
                int o = VerifyOffset(Offsets.ST2, "Writing ST2 register");
                if (this.STCount <= 2)
                    throw new IndexOutOfRangeException("This register is empty and can't be accessed!");
                Memory.WriteDouble(this.Address + o, value);
            }
        }

        /// <summary>
        /// Gets or sets the value in ST3 register. If STCount is less or equal to the number at index then this will
        /// throw an exception! This is only available in 32-bit at the moment.
        /// </summary>
        /// <value>
        /// The value in ST3 register.
        /// </value>
        public double ST3
        {
            get
            {
                int o = VerifyOffset(Offsets.ST3, "Reading ST3 register");
                if (this.STCount <= 3)
                    throw new IndexOutOfRangeException("This register is empty and can't be accessed!");
                return Memory.ReadDouble(this.Address + o);
            }
            set
            {
                int o = VerifyOffset(Offsets.ST3, "Writing ST3 register");
                if (this.STCount <= 3)
                    throw new IndexOutOfRangeException("This register is empty and can't be accessed!");
                Memory.WriteDouble(this.Address + o, value);
            }
        }

        /// <summary>
        /// Gets or sets the value in ST4 register. If STCount is less or equal to the number at index then this will
        /// throw an exception! This is only available in 32-bit at the moment.
        /// </summary>
        /// <value>
        /// The value in ST4 register.
        /// </value>
        public double ST4
        {
            get
            {
                int o = VerifyOffset(Offsets.ST4, "Reading ST4 register");
                if (this.STCount <= 4)
                    throw new IndexOutOfRangeException("This register is empty and can't be accessed!");
                return Memory.ReadDouble(this.Address + o);
            }
            set
            {
                int o = VerifyOffset(Offsets.ST4, "Writing ST4 register");
                if (this.STCount <= 4)
                    throw new IndexOutOfRangeException("This register is empty and can't be accessed!");
                Memory.WriteDouble(this.Address + o, value);
            }
        }

        /// <summary>
        /// Gets or sets the value in ST5 register. If STCount is less or equal to the number at index then this will
        /// throw an exception! This is only available in 32-bit at the moment.
        /// </summary>
        /// <value>
        /// The value in ST5 register.
        /// </value>
        public double ST5
        {
            get
            {
                int o = VerifyOffset(Offsets.ST5, "Reading ST5 register");
                if (this.STCount <= 5)
                    throw new IndexOutOfRangeException("This register is empty and can't be accessed!");
                return Memory.ReadDouble(this.Address + o);
            }
            set
            {
                int o = VerifyOffset(Offsets.ST5, "Writing ST5 register");
                if (this.STCount <= 5)
                    throw new IndexOutOfRangeException("This register is empty and can't be accessed!");
                Memory.WriteDouble(this.Address + o, value);
            }
        }

        /// <summary>
        /// Gets or sets the value in ST6 register. If STCount is less or equal to the number at index then this will
        /// throw an exception! This is only available in 32-bit at the moment.
        /// </summary>
        /// <value>
        /// The value in ST6 register.
        /// </value>
        public double ST6
        {
            get
            {
                int o = VerifyOffset(Offsets.ST6, "Reading ST6 register");
                if (this.STCount <= 6)
                    throw new IndexOutOfRangeException("This register is empty and can't be accessed!");
                return Memory.ReadDouble(this.Address + o);
            }
            set
            {
                int o = VerifyOffset(Offsets.ST6, "Writing ST6 register");
                if (this.STCount <= 6)
                    throw new IndexOutOfRangeException("This register is empty and can't be accessed!");
                Memory.WriteDouble(this.Address + o, value);
            }
        }

        /// <summary>
        /// Gets or sets the value in ST7 register. If STCount is less or equal to the number at index then this will
        /// throw an exception! This is only available in 32-bit at the moment.
        /// </summary>
        /// <value>
        /// The value in ST7 register.
        /// </value>
        public double ST7
        {
            get
            {
                int o = VerifyOffset(Offsets.ST7, "Reading ST7 register");
                if (this.STCount <= 7)
                    throw new IndexOutOfRangeException("This register is empty and can't be accessed!");
                return Memory.ReadDouble(this.Address + o);
            }
            set
            {
                int o = VerifyOffset(Offsets.ST7, "Writing ST7 register");
                if (this.STCount <= 7)
                    throw new IndexOutOfRangeException("This register is empty and can't be accessed!");
                Memory.WriteDouble(this.Address + o, value);
            }
        }

        /// <summary>
        /// Gets the count of values in x87 FPU stack. This is only available in 32-bit at the moment.
        /// </summary>
        /// <value>
        /// The count of x87 FPU stack.
        /// </value>
        public int STCount
        {
            get
            {
                int o = VerifyOffset(Offsets.STCount, "Reading STCount");
                var r = Memory.ReadPointer(this.Address + o).ToInt64();
                return (int)r;
            }
        }
        
        #endregion

        #region Internal members

        /// <summary>
        /// Writes debug info to log.
        /// </summary>
        internal void WriteToLog()
        {
            Main.Log.AppendLine("--------------------------------------------------------------------------------");
            Main.Log.AppendLine("CPURegisters(0x" + Memory.Convert(this.Address).ToString("X") + "):");
            Main.Log.AppendLine("AX: 0x" + Memory.Convert(this.AX).ToString("X"));
            Main.Log.AppendLine("BX: 0x" + Memory.Convert(this.BX).ToString("X"));
            Main.Log.AppendLine("CX: 0x" + Memory.Convert(this.CX).ToString("X"));
            Main.Log.AppendLine("DX: 0x" + Memory.Convert(this.DX).ToString("X"));
            Main.Log.AppendLine("DI: 0x" + Memory.Convert(this.DI).ToString("X"));
            Main.Log.AppendLine("SI: 0x" + Memory.Convert(this.SI).ToString("X"));
            Main.Log.AppendLine("BP: 0x" + Memory.Convert(this.BP).ToString("X"));
            Main.Log.AppendLine("SP: 0x" + Memory.Convert(this.SP).ToString("X"));
            Main.Log.AppendLine("FLAGS: 0x" + Memory.Convert(this.FLAGS).ToString("X"));
            Main.Log.AppendLine("IP: 0x" + Memory.Convert(this.IP).ToString("X"));
            if (this.IsFromHook != null)
            {
                Main.Log.AppendLine("Hook: 0x" + Memory.Convert(this.Hook).ToString("X"));
                Main.Log.AppendLine("Include: 0x" + this.Include.ToString("X"));
            }
            Main.Log.AppendLine("XMM0: " + this.XMM0);
            Main.Log.AppendLine("XMM1: " + this.XMM1);
            Main.Log.AppendLine("XMM2: " + this.XMM2);
            Main.Log.AppendLine("XMM3: " + this.XMM3);
            Main.Log.AppendLine("XMM4: " + this.XMM4);
            Main.Log.AppendLine("XMM5: " + this.XMM5);
            Main.Log.AppendLine("XMM6: " + this.XMM6);
            Main.Log.AppendLine("XMM7: " + this.XMM7);
            if (Main.Is64Bit)
            {
                Main.Log.AppendLine("XMM8: " + this.XMM8);
                Main.Log.AppendLine("XMM9: " + this.XMM9);
                Main.Log.AppendLine("XMM10: " + this.XMM10);
                Main.Log.AppendLine("XMM11: " + this.XMM11);
                Main.Log.AppendLine("XMM12: " + this.XMM12);
                Main.Log.AppendLine("XMM13: " + this.XMM13);
                Main.Log.AppendLine("XMM14: " + this.XMM14);
                Main.Log.AppendLine("XMM15: " + this.XMM15);
                Main.Log.AppendLine("R8: 0x" + Memory.Convert(this.R8).ToString("X"));
                Main.Log.AppendLine("R9: 0x" + Memory.Convert(this.R9).ToString("X"));
                Main.Log.AppendLine("R10: 0x" + Memory.Convert(this.R10).ToString("X"));
                Main.Log.AppendLine("R11: 0x" + Memory.Convert(this.R11).ToString("X"));
                Main.Log.AppendLine("R12: 0x" + Memory.Convert(this.R12).ToString("X"));
                Main.Log.AppendLine("R13: 0x" + Memory.Convert(this.R13).ToString("X"));
                Main.Log.AppendLine("R14: 0x" + Memory.Convert(this.R14).ToString("X"));
                Main.Log.AppendLine("R15: 0x" + Memory.Convert(this.R15).ToString("X"));
            }
            else
            {
                int stc = this.STCount;
                Main.Log.AppendLine("STCount: " + stc);
                if (stc > 0)
                    Main.Log.AppendLine("ST0: " + this.ST0);
                if (stc > 1)
                    Main.Log.AppendLine("ST1: " + this.ST1);
                if (stc > 2)
                    Main.Log.AppendLine("ST2: " + this.ST2);
                if (stc > 3)
                    Main.Log.AppendLine("ST3: " + this.ST3);
                if (stc > 4)
                    Main.Log.AppendLine("ST4: " + this.ST4);
                if (stc > 5)
                    Main.Log.AppendLine("ST5: " + this.ST5);
                if (stc > 6)
                    Main.Log.AppendLine("ST6: " + this.ST6);
                if (stc > 7)
                    Main.Log.AppendLine("ST7: " + this.ST7);
            }
            Main.Log.AppendLine("--------------------------------------------------------------------------------");
        }

        /// <summary>
        /// The base address of allocation.
        /// </summary>
        internal readonly IntPtr Address;

        /// <summary>
        /// The offsets of unmanaged memory.
        /// </summary>
        internal static CPUOffsets Offsets = null;

        /// <summary>
        /// Gets the size of CPU registers struct.
        /// </summary>
        /// <value>
        /// The size of.
        /// </value>
        internal static int SizeOf
        {
            get
            {
                return Offsets.Size;
            }
        }

        /// <summary>
        /// Container for offsets in the unmanaged memory.
        /// </summary>
        internal class CPUOffsets
        {
            /// <summary>
            /// Initializes a new instance of the <see cref="CPUOffsets"/> class.
            /// </summary>
            internal CPUOffsets()
            {
                this.Size = GetContextOffset(0);
                this.AX = GetContextOffset(1);
                this.BX = GetContextOffset(2);
                this.CX = GetContextOffset(3);
                this.DX = GetContextOffset(4);
                this.SI = GetContextOffset(5);
                this.DI = GetContextOffset(6);
                this.SP = GetContextOffset(7);
                this.IP = GetContextOffset(8);
                this.FLAGS = GetContextOffset(9);
                this.R8 = GetContextOffset(10);
                this.R9 = GetContextOffset(11);
                this.R10 = GetContextOffset(12);
                this.R11 = GetContextOffset(13);
                this.R12 = GetContextOffset(14);
                this.R13 = GetContextOffset(15);
                this.R14 = GetContextOffset(16);
                this.R15 = GetContextOffset(17);
                this.XMM0 = GetContextOffset(18);
                this.XMM1 = GetContextOffset(19);
                this.XMM2 = GetContextOffset(20);
                this.XMM3 = GetContextOffset(21);
                this.XMM4 = GetContextOffset(22);
                this.XMM5 = GetContextOffset(23);
                this.XMM6 = GetContextOffset(24);
                this.XMM7 = GetContextOffset(25);
                this.XMM8 = GetContextOffset(26);
                this.XMM9 = GetContextOffset(27);
                this.XMM10 = GetContextOffset(28);
                this.XMM11 = GetContextOffset(29);
                this.XMM12 = GetContextOffset(30);
                this.XMM13 = GetContextOffset(31);
                this.XMM14 = GetContextOffset(32);
                this.XMM15 = GetContextOffset(33);
                this.Depth = GetContextOffset(34);
                this.ReturnAfter = GetContextOffset(35);
                this.Hook = GetContextOffset(36);
                this.BP = GetContextOffset(37);
                this.Hook_CX = GetContextOffset(38);
                this.Hook_AX = GetContextOffset(39);
                this.Hook_OrigReturnAfter = GetContextOffset(40);
            }

            [DllImport("NetScriptFramework.Runtime.dll")]
            private static extern int GetContextOffset(int index);

            internal int AX = -1;
            internal int BX = -1;
            internal int CX = -1;
            internal int DX = -1;
            internal int DI = -1;
            internal int SI = -1;
            internal int BP = -1;
            internal int SP = -1;
            internal int FLAGS = -1;
            internal int IP = -1;
            internal int Hook = -1;
            internal int XMM0 = -1;
            internal int XMM1 = -1;
            internal int XMM2 = -1;
            internal int XMM3 = -1;
            internal int XMM4 = -1;
            internal int XMM5 = -1;
            internal int XMM6 = -1;
            internal int XMM7 = -1;
            internal int XMM8 = -1;
            internal int XMM9 = -1;
            internal int XMM10 = -1;
            internal int XMM11 = -1;
            internal int XMM12 = -1;
            internal int XMM13 = -1;
            internal int XMM14 = -1;
            internal int XMM15 = -1;
            internal int ST0 = -1;
            internal int ST1 = -1;
            internal int ST2 = -1;
            internal int ST3 = -1;
            internal int ST4 = -1;
            internal int ST5 = -1;
            internal int ST6 = -1;
            internal int ST7 = -1;
            internal int STCount = -1;
            internal int R8 = -1;
            internal int R9 = -1;
            internal int R10 = -1;
            internal int R11 = -1;
            internal int R12 = -1;
            internal int R13 = -1;
            internal int R14 = -1;
            internal int R15 = -1;
            internal int Size = -1;
            internal int Depth = -1;
            internal int ReturnAfter = -1;
            internal int Hook_AX = -1;
            internal int Hook_CX = -1;
            internal int Hook_OrigReturnAfter = -1;
        }

        #endregion
    }

    /// <summary>
    /// Extension helper functions for IntPtr class.
    /// </summary>
    public static class _IntPtrExtensions
    {
        /// <summary>
        /// Convert pointer to hex string (including prefix).
        /// </summary>
        /// <param name="value">The value to convert.</param>
        /// <returns></returns>
        public static string ToHexString(this IntPtr value)
        {
            return "0x" + value.ToInt64().ToString("X", System.Globalization.CultureInfo.InvariantCulture);
        }

        /// <summary>
        /// Converts the value of this instance to a boolean.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <returns></returns>
        public static bool ToBool(this IntPtr value)
        {
            var q = ToInternal32(value);
            return (q & 0xFF) != 0;
        }

        /// <summary>
        /// Converts the value of this instance to a 8-bit unsigned integer.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <returns></returns>
        public static byte ToUInt8(this IntPtr value)
        {
            var q = ToInternal32(value);
            return (byte)(q & 0xFF);
        }

        /// <summary>
        /// Converts the value of this instance to a 8-bit signed integer.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <returns></returns>
        public static sbyte ToInt8(this IntPtr value)
        {
            return unchecked((sbyte)value.ToUInt8());
        }

        /// <summary>
        /// Converts the value of this instance to a 16-bit unicode character.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <returns></returns>
        public static char ToChar(this IntPtr value)
        {
            byte[] bt = BitConverter.GetBytes(value.ToUInt16());
            return BitConverter.ToChar(bt, 0);
        }

        /// <summary>
        /// Converts the value of this instance to a 16-bit signed integer.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <returns></returns>
        public static short ToInt16(this IntPtr value)
        {
            return unchecked((short)value.ToUInt16());
        }

        /// <summary>
        /// Converts the value of this instance to a 16-bit unsigned integer.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <returns></returns>
        public static ushort ToUInt16(this IntPtr value)
        {
            var q = ToInternal32(value);
            return (ushort)(q & 0xFFFF);
        }

        /// <summary>
        /// Converts the value of this instance to a 32-bit unsigned integer.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <returns></returns>
        public static uint ToUInt32(this IntPtr value)
        {
            var q = ToInternal32(value);
            return (uint)(q & 0xFFFFFFFF);
        }

        /// <summary>
        /// Converts the value of this instance to a 64-bit unsigned integer.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <returns></returns>
        /// <exception cref="System.InvalidCastException">Unable to cast a pointer to a 64-bit unsigned integer!</exception>
        public static ulong ToUInt64(this IntPtr value)
        {
            if (!Main.Is64Bit)
                throw new InvalidCastException("Unable to cast a pointer to a 64-bit unsigned integer!");
            return unchecked((ulong)value.ToInt64());
        }

        /// <summary>
        /// Converts the value of this instance to a 32-bit floating point value.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <returns></returns>
        public static float ToSingle(this IntPtr value)
        {
            var bt = BitConverter.GetBytes(value.ToUInt32());
            return BitConverter.ToSingle(bt, 0);
        }

        /// <summary>
        /// Converts the value of this instance to a 64-bit floating point value.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <returns></returns>
        /// <exception cref="System.InvalidCastException">Unable to cast a pointer to a 64-bit floating point value!</exception>
        public static double ToDouble(this IntPtr value)
        {
            if (!Main.Is64Bit)
                throw new InvalidCastException("Unable to cast a pointer to a 64-bit floating point value!");
            var bt = BitConverter.GetBytes(value.ToUInt64());
            return BitConverter.ToDouble(bt, 0);
        }

        /// <summary>
        /// Get internal value that we can convert from.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <returns></returns>
        private static ulong ToInternal32(IntPtr value)
        {
            if (Main.Is64Bit)
                return value.ToUInt64();
            return unchecked((uint)value.ToInt32());
        }

        /// <summary>
        /// Compares a pointer with another.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <param name="other">The other.</param>
        /// <returns></returns>
        public static int CompareTo(this IntPtr value, IntPtr other)
        {
            if (value == other)
                return 0;

            if(Main.Is64Bit)
            {
                ulong a = value.ToUInt64();
                ulong b = other.ToUInt64();
                return a.CompareTo(b);
            }
            else
            {
                uint a = value.ToUInt32();
                uint b = other.ToUInt32();
                return a.CompareTo(b);
            }
        }
    }

    /// <summary>
    /// Custom class for handling memory access exceptions.
    /// </summary>
    /// <seealso cref="System.Exception" />
    public class MemoryAccessException : Exception
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="MemoryAccessException"/> class.
        /// </summary>
        public MemoryAccessException() : base("Trying to access protected or unallocated memory!")
        {

        }

        /// <summary>
        /// Initializes a new instance of the <see cref="MemoryAccessException"/> class.
        /// </summary>
        /// <param name="address">The address.</param>
        /// <param name="length">The length.</param>
        /// <param name="protectForRead">The protect for read.</param>
        internal MemoryAccessException(IntPtr address, int length, int protectForRead) : base("Failed to modify memory protection flags for " + (protectForRead > 0 ? "reading" : "writing") + " at address " + address.ToHexString() + " to " + (address + length).ToHexString() + "!")
        {

        }

        /// <summary>
        /// Initializes a new instance of the <see cref="MemoryAccessException"/> class.
        /// </summary>
        /// <param name="address">The address.</param>
        public MemoryAccessException(IntPtr address) : base("Trying to access protected or unallocated memory at address " + address.ToHexString() + "!")
        {

        }

        /// <summary>
        /// Initializes a new instance of the <see cref="MemoryAccessException"/> class.
        /// </summary>
        /// <param name="address">The address.</param>
        /// <param name="length">The length.</param>
        public MemoryAccessException(IntPtr address, int length) : base("Trying to access protected or unallocated memory at address " + address.ToHexString() + " to " + (address + length).ToHexString() + "!")
        {

        }

        /// <summary>
        /// Initializes a new instance of the <see cref="MemoryAccessException"/> class.
        /// </summary>
        /// <param name="address">The address.</param>
        /// <param name="length">The length.</param>
        /// <param name="write">if set to <c>true</c> [write].</param>
        public MemoryAccessException(IntPtr address, int length, bool write) : base("Trying to " + (write ? "write to" : "read from") + " protected or unallocated memory at address " + address.ToHexString() + " to " + (address + length).ToHexString() + "!")
        {

        }

        /// <summary>
        /// Initializes a new instance of the <see cref="MemoryAccessException"/> class.
        /// </summary>
        /// <param name="address">The address.</param>
        /// <param name="write">if set to <c>true</c> [write].</param>
        public MemoryAccessException(IntPtr address, bool write) : base("Trying to " + (write ? "write to" : "read from") + " protected or unallocated memory at address " + address.ToHexString() + "!")
        {

        }
    }
}
