using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetScriptFramework
{
    /// <summary>
    /// Contains custom debug information about the application so we can write more info from registers and stack.
    /// </summary>
    public sealed class DebugInfo
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="DebugInfo"/> class.
        /// </summary>
        internal DebugInfo()
        {
            var mainModule = Main.GetMainTargetedModule();
            this.BaseOffset = mainModule.BaseAddress.ToUInt64();
        }

        /// <summary>
        /// The types.
        /// </summary>
        internal readonly Dictionary<ulong, DebugTypeInfo> Types = new Dictionary<ulong, DebugTypeInfo>();

        /// <summary>
        /// The functions.
        /// </summary>
        internal readonly List<DebugFunctionInfo> Functions = new List<DebugFunctionInfo>();

        /// <summary>
        /// The file version.
        /// </summary>
        internal int[] FileVersion = null;

        /// <summary>
        /// The base offset.
        /// </summary>
        public readonly ulong BaseOffset;

        /// <summary>
        /// Gets all the registered types.
        /// </summary>
        /// <returns></returns>
        public List<DebugTypeInfo> GetTypes()
        {
            return this.Types.Values.ToList();
        }

        /// <summary>
        /// Gets all the functions.
        /// </summary>
        /// <returns></returns>
        public List<DebugFunctionInfo> GetFunctions()
        {
            return this.Functions.ToList();
        }

        /// <summary>
        /// Gets the type from vtable address.
        /// </summary>
        /// <param name="vtable">The vtable address.</param>
        /// <param name="withBaseOffset">Does the address include base offset of module?</param>
        /// <returns></returns>
        public DebugTypeInfo GetTypeInfo(IntPtr vtable, bool withBaseOffset)
        {
            ulong v = Main.Is64Bit ? vtable.ToUInt64() : vtable.ToUInt32();
            if(withBaseOffset)
                v = unchecked(v - this.BaseOffset);

            DebugTypeInfo result = null;
            if (this.Types.TryGetValue(v, out result))
                return result;
            return null;
        }

        /// <summary>
        /// Gets the function information.
        /// </summary>
        /// <param name="address">The address.</param>
        /// <param name="withBaseOffset">Does the address include base offset of module?</param>
        /// <returns></returns>
        public DebugFunctionInfo GetFunctionInfo(IntPtr address, bool withBaseOffset)
        {
            ulong v = Main.Is64Bit ? address.ToUInt64() : address.ToUInt32();
            if(withBaseOffset)
                v = unchecked(v - this.BaseOffset);

            foreach (var f in this.Functions)
            {
                if (v >= f.Begin && v < f.End)
                    return f;
            }

            return null;
        }

        /// <summary>
        /// Gets the function information.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <returns></returns>
        public DebugFunctionInfo GetFunctionInfo(ulong id)
        {
            if(id != 0)
                return this.Functions.FirstOrDefault(q => q.Id == id);
            return null;
        }

        /// <summary>
        /// Adds the type information.
        /// </summary>
        /// <param name="vtable">The vtable.</param>
        /// <param name="name">The name.</param>
        internal void AddTypeInfo(ulong vtable, string name)
        {
            DebugTypeInfo dt = new DebugTypeInfo();
            dt.Name = name;
            dt.VTable = vtable;

            this.Types[dt.VTable] = dt;
        }

        /// <summary>
        /// Adds the function information.
        /// </summary>
        /// <param name="offsetBegin">The offset begin.</param>
        /// <param name="offsetEnd">The offset end.</param>
        /// <param name="shortName">The short name.</param>
        /// <param name="fullName">The full name.</param>
        /// <param name="id">The unique ID.</param>
        internal void AddFunctionInfo(ulong offsetBegin, ulong offsetEnd, string shortName, string fullName, ulong id)
        {
            var fi = new DebugFunctionInfo();
            fi.Id = id;
            fi.Begin = offsetBegin;
            fi.End = offsetEnd;
            fi.ShortName = shortName;
            fi.FullName = fullName;

            this.Functions.Add(fi);
        }

        /// <summary>
        /// Reads from specified file. This will clear previous debug info.
        /// </summary>
        /// <param name="file">The file.</param>
        /// <exception cref="System.IO.FileNotFoundException"></exception>
        internal void ReadFromFile(System.IO.FileInfo file)
        {
            this.Types.Clear();

            if (!file.Exists)
                throw new System.IO.FileNotFoundException();

            using (var stream = file.OpenRead())
            {
                using (var reader = new System.IO.BinaryReader(stream))
                {
                    this.ReadFromStream(reader);
                }
            }
        }

        /// <summary>
        /// Writes to specified file. This will replace the file if it already exists.
        /// </summary>
        /// <param name="file">The file.</param>
        internal void WriteToFile(System.IO.FileInfo file)
        {
            using (var stream = file.Create())
            {
                using (var writer = new System.IO.BinaryWriter(stream))
                {
                    this.WriteToStream(writer);
                }
            }
        }

        /// <summary>
        /// The stream version.
        /// </summary>
        private const int StreamVersion = 1;

        /// <summary>
        /// Reads from stream.
        /// </summary>
        /// <param name="stream">The stream.</param>
        /// <exception cref="System.IO.InvalidDataException">Version of object is not supported!</exception>
        private void ReadFromStream(System.IO.BinaryReader stream)
        {
            int version = stream.ReadInt32();
            if (version <= 0 || version > StreamVersion)
                throw new System.IO.InvalidDataException("Version of object is not supported!");

            this.FileVersion = new int[4];
            for (int i = 0; i < 4; i++)
                this.FileVersion[i] = stream.ReadInt32();

            {
                int count = stream.ReadInt32();
                for (int i = 0; i < count; i++)
                {
                    DebugTypeInfo dt = new DebugTypeInfo();
                    dt.ReadFromStream(stream);
                    this.Types[dt.VTable] = dt;
                }
            }

            {
                int count = stream.ReadInt32();
                for (int i = 0; i < count; i++)
                {
                    var fi = new DebugFunctionInfo();
                    fi.ReadFromStream(stream);
                    this.Functions.Add(fi);
                }
            }
        }

        /// <summary>
        /// Writes to stream.
        /// </summary>
        /// <param name="stream">The stream.</param>
        private void WriteToStream(System.IO.BinaryWriter stream)
        {
            stream.Write(StreamVersion);

            for (int i = 0; i < 4; i++)
                stream.Write(this.FileVersion[i]);

            {
                stream.Write(this.Types.Count);
                foreach (var x in this.Types)
                    x.Value.WriteToStream(stream);
            }

            {
                stream.Write(this.Functions.Count);
                foreach (var x in this.Functions)
                    x.WriteToStream(stream);
            }
        }

        /// <summary>
        /// Debug info for a type.
        /// </summary>
        public sealed class DebugTypeInfo
        {
            /// <summary>
            /// Initializes a new instance of the <see cref="DebugTypeInfo"/> class.
            /// </summary>
            internal DebugTypeInfo()
            {

            }

            /// <summary>
            /// The virtual function table address offset.
            /// </summary>
            public ulong VTable
            {
                get;
                internal set;
            }

            /// <summary>
            /// The name of type to display.
            /// </summary>
            public string Name
            {
                get;
                internal set;
            } = "(null)";

            /// <summary>
            /// Gets the size of type. This is null if unknown.
            /// </summary>
            /// <value>
            /// The size.
            /// </value>
            public int? Size
            {
                get;
                internal set;
            } = null;

            /// <summary>
            /// Gets the rtti type descriptor.
            /// </summary>
            /// <value>
            /// The rtti.
            /// </value>
            public ulong RTTI
            {
                get;
                internal set;
            }

            /// <summary>
            /// The stream version.
            /// </summary>
            private const int StreamVersion = 2;

            /// <summary>
            /// Reads from stream.
            /// </summary>
            /// <param name="stream">The stream.</param>
            /// <exception cref="System.IO.InvalidDataException">Version of object is not supported!</exception>
            internal void ReadFromStream(System.IO.BinaryReader stream)
            {
                int version = stream.ReadInt32();
                if (version <= 0 || version > StreamVersion)
                    throw new System.IO.InvalidDataException("Version of object is not supported!");

                this.VTable = stream.ReadUInt64();
                this.Name = stream.ReadString();
                if(version >= 2)
                {
                    byte b = stream.ReadByte();
                    if (b != 0)
                        this.Size = stream.ReadInt32();

                    this.RTTI = stream.ReadUInt64();
                }
            }

            /// <summary>
            /// Writes to stream.
            /// </summary>
            /// <param name="stream">The stream.</param>
            internal void WriteToStream(System.IO.BinaryWriter stream)
            {
                stream.Write(StreamVersion);

                stream.Write(this.VTable);
                stream.Write(this.Name);
                if (this.Size.HasValue)
                {
                    stream.Write((byte)1);
                    stream.Write(this.Size.Value);
                }
                else
                    stream.Write((byte)0);
                stream.Write(this.RTTI);
            }
        }

        /// <summary>
        /// Debug info for a function.
        /// </summary>
        public sealed class DebugFunctionInfo
        {
            /// <summary>
            /// Initializes a new instance of the <see cref="DebugFunctionInfo"/> class.
            /// </summary>
            internal DebugFunctionInfo()
            {

            }

            /// <summary>
            /// The identifier of the function. This is version independent.
            /// </summary>
            public ulong Id
            {
                get;
                internal set;
            }

            /// <summary>
            /// The begin offset.
            /// </summary>
            public ulong Begin
            {
                get;
                internal set;
            }

            /// <summary>
            /// The end offset.
            /// </summary>
            public ulong End
            {
                get;
                internal set;
            }

            /// <summary>
            /// The short name of function.
            /// </summary>
            public string ShortName
            {
                get;
                internal set;
            }

            /// <summary>
            /// The full name of function.
            /// </summary>
            public string FullName
            {
                get;
                internal set;
            }

            /// <summary>
            /// The stream version.
            /// </summary>
            private const int StreamVersion = 2;

            /// <summary>
            /// Reads from stream.
            /// </summary>
            /// <param name="stream">The stream.</param>
            /// <exception cref="System.IO.InvalidDataException">Version of object is not supported!</exception>
            internal void ReadFromStream(System.IO.BinaryReader stream)
            {
                int version = stream.ReadInt32();
                if (version <= 0 || version > StreamVersion)
                    throw new System.IO.InvalidDataException("Version of object is not supported!");

                this.Begin = stream.ReadUInt64();
                this.End = stream.ReadUInt64();
                if (stream.ReadByte() != 0)
                    this.ShortName = stream.ReadString();
                else
                    this.ShortName = null;
                if (stream.ReadByte() != 0)
                    this.FullName = stream.ReadString();
                else
                    this.FullName = null;

                if (version >= 2)
                    this.Id = stream.ReadUInt64();
            }

            /// <summary>
            /// Writes to stream.
            /// </summary>
            /// <param name="stream">The stream.</param>
            internal void WriteToStream(System.IO.BinaryWriter stream)
            {
                stream.Write(StreamVersion);

                stream.Write(this.Begin);
                stream.Write(this.End);
                if (this.ShortName != null)
                {
                    stream.Write((byte)1);
                    stream.Write(this.ShortName);
                }
                else
                    stream.Write((byte)0);
                if (this.FullName != null)
                {
                    stream.Write((byte)1);
                    stream.Write(this.FullName);
                }
                else
                    stream.Write((byte)0);
                stream.Write(this.Id);
            }
        }
    }
}
