using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetScriptFramework.Tools
{
    /// <summary>
    /// Helper class to deal with generic types in memory.
    /// </summary>
    public static class GenericMemoryHelper
    {
        /// <summary>
        /// The null pointer bytes.
        /// </summary>
        private static readonly byte[] Null = Main.Is64Bit ? new byte[8] : new byte[4];

        /// <summary>
        /// Convert byte array to pointer.
        /// </summary>
        /// <param name="data">The data.</param>
        /// <returns></returns>
        private static IntPtr BytesToPtr(byte[] data)
        {
            if (Main.Is64Bit)
                return new IntPtr(BitConverter.ToInt64(data, 0));
            return new IntPtr(BitConverter.ToInt32(data, 0));
        }

        private static readonly Dictionary<Type, Func<object, bool, byte[]>> ConvertToBytes = new Dictionary<Type, Func<object, bool, byte[]>>()
        {
            { typeof(int), (q, f) => BitConverter.GetBytes((int)q) },
            { typeof(uint), (q, f) => BitConverter.GetBytes((uint)q) },
            { typeof(long), (q, f) => BitConverter.GetBytes((long)q) },
            { typeof(ulong), (q, f) => BitConverter.GetBytes((ulong)q) },
            { typeof(byte), (q, f) => BitConverter.GetBytes((byte)q) },
            { typeof(sbyte), (q, f) => BitConverter.GetBytes((sbyte)q) },
            { typeof(char), (q, f) => new[] { unchecked((byte)q) } },
            { typeof(bool), (q, f) => BitConverter.GetBytes((bool)q) },
            { typeof(float), (q, f) => BitConverter.GetBytes((float)q) },
            { typeof(double), (q, f) => BitConverter.GetBytes((double)q) },
            { typeof(short), (q, f) => BitConverter.GetBytes((short)q) },
            { typeof(ushort), (q, f) => BitConverter.GetBytes((ushort)q) },

            { typeof(string),
                (q, f) =>
                {
                    if(f)
                    {
                    if(object.ReferenceEquals(q, null))
                        return null;
                    return Encoding.ASCII.GetBytes(q as string);
                    }
                    if(object.ReferenceEquals(q, null))
                        return Null;
                    throw new InvalidOperationException("Unable to get pointer to string!");
                }
            },
        };

        private static readonly Dictionary<Type, Func<byte[], bool, object>> ConvertToObject = new Dictionary<Type, Func<byte[], bool, object>>()
        {
            { typeof(int), (q, f) => BitConverter.ToInt32(q, 0) },
            { typeof(uint), (q, f) => BitConverter.ToUInt32(q, 0) },
            { typeof(long), (q, f) => BitConverter.ToInt64(q, 0) },
            { typeof(ulong), (q, f) => BitConverter.ToUInt64(q, 0) },
            { typeof(byte), (q, f) => q[0] },
            { typeof(sbyte), (q, f) => unchecked((sbyte)q[0]) },
            { typeof(char), (q, f) => unchecked((char)q[0]) },
            { typeof(bool), (q, f) => q[0] != 0 },
            { typeof(float), (q, f) => BitConverter.ToSingle(q, 0) },
            { typeof(double), (q, f) => BitConverter.ToDouble(q, 0) },
            { typeof(short), (q, f) => BitConverter.ToInt16(q, 0) },
            { typeof(ushort), (q, f) => BitConverter.ToUInt16(q, 0) },

            { typeof(string),
                (q, f) =>
                {
                    if(f)
                        return Encoding.ASCII.GetString(q);

                    var ptr = BytesToPtr(q);
                    return Memory.ReadString(ptr, false);
                }
            },
        };

        private static readonly Dictionary<Type, Func<bool, int>> SizeOfType = new Dictionary<Type, Func<bool, int>>()
        {
            { typeof(int), q => 4 },
            { typeof(uint), q => 4 },
            { typeof(long), q => 8 },
            { typeof(ulong), q => 8 },
            { typeof(byte), q => 1 },
            { typeof(sbyte), q => 1 },
            { typeof(char), q => 1 },
            { typeof(bool), q => 1 },
            { typeof(float), q => 4 },
            { typeof(double), q => 8 },
            { typeof(short), q => 2 },
            { typeof(ushort), q => 2 },

            { typeof(string),
                q =>
                {
                    if(q)
                        throw new InvalidOperationException();

                    return Main.Is64Bit ? 8 : 4;
                }
            },
        };

        /// <summary>
        /// Convert value to byte array.
        /// </summary>
        /// <typeparam name="T">Type of value.</typeparam>
        /// <param name="value">The value.</param>
        /// <param name="forceStruct">If set to <c>true</c> then force handling type as structure instead of pointer, otherwise decide based on type.</param>
        /// <returns></returns>
        public static byte[] ToBytes<T>(T value, bool forceStruct)
        {
            var t = typeof(T);
            var a = t;
            object o = value;

            // Enum is special case, get underlying type instead.
            if(t.IsEnum)
                a = t.UnderlyingSystemType;

            // Have registered handler.
            {
                Func<object, bool, byte[]> func = null;
                if (ConvertToBytes.TryGetValue(a, out func))
                    return func(o, forceStruct);
            }

            // Maybe it's memory type.
            if(typeof(IMemoryObject).IsAssignableFrom(t))
            {
                var obj = value as IMemoryObject;

                // Memory types are always by pointer unless we specifically ask otherwise.
                if (!forceStruct)
                {
                    if (object.ReferenceEquals(obj, null))
                        return Null;
                    return Main.Is64Bit ? BitConverter.GetBytes(obj.Address.ToInt64()) : BitConverter.GetBytes(obj.Address.ToInt32());
                }

                if (object.ReferenceEquals(obj, null))
                    throw new ArgumentOutOfRangeException("value", "Unable to get struct bytes from null pointer!");

                var size = MemoryObject.SizeOf(t);
                return size == 0 ? new byte[0] : Memory.ReadBytes(obj.Address, size);
            }

            // Type does not have a handler.
            throw new ArgumentException("Specified type does not have a generic handler!", "T");
        }

        /// <summary>
        /// Convert value from byte array.
        /// </summary>
        /// <typeparam name="T">Type of value.</typeparam>
        /// <param name="data">The byte array.</param>
        /// <param name="forceStruct">If set to <c>true</c> then force handling type as structure instead of pointer, otherwise decide based on type.</param>
        /// <returns></returns>
        public static T FromBytes<T>(byte[] data, bool forceStruct)
        {
            var t = typeof(T);
            var a = t;

            // Enum is special case, get underlying type instead.
            if (t.IsEnum)
                a = t.UnderlyingSystemType;

            // Have registered handler.
            {
                Func<byte[], bool, object> func = null;
                if (ConvertToObject.TryGetValue(a, out func))
                    return (T)func(data, forceStruct);
            }

            // Maybe it's memory type.
            if (typeof(IMemoryObject).IsAssignableFrom(t))
            {
                // Memory types are always by pointer unless we specifically ask otherwise.
                if (!forceStruct)
                {
                    var ptr = BytesToPtr(data);
                    return (T)MemoryObject.FromAddress(t, ptr);
                }

                //var size = MemoryObject.SizeOf(t);

                // This must be handled differently. We could create a new object, read the memory into it but it would cause a memory leak and if we automatically
                // free later then it may cause bad pointers if this object is stored somewhere in game.
                throw new NotImplementedException("Unable to get structure!");
            }

            // Type does not have a handler.
            throw new ArgumentException("Specified type does not have a generic handler!", "T");
        }

        /// <summary>
        /// Calculate size of type.
        /// </summary>
        /// <typeparam name="T">Type of value.</typeparam>
        /// <param name="forceStruct">If set to <c>true</c> then force handling type as structure instead of pointer, otherwise decide based on type.</param>
        /// <returns></returns>
        public static int SizeOf<T>(bool forceStruct)
        {
            var t = typeof(T);
            var a = t;

            // Enum is special case, get underlying type instead.
            if (t.IsEnum)
                a = t.UnderlyingSystemType;

            // Have registered handler.
            {
                Func<bool, int> func = null;
                if (SizeOfType.TryGetValue(a, out func))
                    return func(forceStruct);
            }

            // Maybe it's memory type.
            if (typeof(IMemoryObject).IsAssignableFrom(t))
            {
                // Memory types are always by pointer unless we specifically ask otherwise.
                if (!forceStruct)
                    return Main.Is64Bit ? 8 : 4;

                return MemoryObject.SizeOf(t);
            }

            // Type does not have a handler.
            throw new ArgumentException("Specified type does not have a generic handler!", "T");
        }
    }
}
