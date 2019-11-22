using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetScriptFramework
{
    #region MemoryObject class

    /// <summary>
    /// Base implementation of a wrapper for an object that exists in memory. Use the Equals methods to check
    /// equality with another object rather than equality operator.
    /// </summary>
    /// <seealso cref="NetScriptFramework.IMemoryObject" />
    /// <seealso cref="NetScriptFramework.Tools.IArgument" />
    public class MemoryObject : IMemoryObject, Tools.IArgument
    {
        #region Constructors

        #endregion

        #region MemoryObject members

        /// <summary>
        /// Gets the base address of the object in memory.
        /// </summary>
        /// <value>
        /// The base address of object in memory.
        /// </value>
        public IntPtr Address
        {
            get;
            internal set;
        } = IntPtr.Zero;

        /// <summary>
        /// Returns true if memory object is valid and can be accessed for reading. It is possible for this to return true even if
        /// the object is not actually valid in case of bad pointers to valid memory regions, invalid cast or partially freed memory!
        /// </summary>
        /// <value>
        ///   <c>true</c> if this instance is valid; otherwise, <c>false</c>.
        /// </value>
        public virtual bool IsValid
        {
            get
            {
                if (this.Address == IntPtr.Zero)
                    return false;

                Type self = null;
                try
                {
                    self = this.GetInterfaceType();
                }
                catch (NotSupportedException)
                {
                    return false;
                }

                int size = SizeOf(self);
                return Memory.IsValidRegion(this.Address, size, true, false, false);
            }
        }

        /// <summary>
        /// Gets the full size of type in memory.
        /// </summary>
        /// <typeparam name="T">Type to check.</typeparam>
        /// <returns></returns>
        /// <exception cref="System.NotImplementedException">Size of type T is not specified!</exception>
        /// <exception cref="System.InvalidOperationException">
        /// Type T is not registered in game library!
        /// or
        /// Unable to get size for type T - game library is not loaded!
        /// </exception>
        public static int SizeOf<T>() where T : IMemoryObject
        {
            var s = typeof(T);
            if (s.IsGenericType && !s.IsGenericTypeDefinition)
                s = s.GetGenericTypeDefinition();

            return SizeOf(s);
        }

        /// <summary>
        /// Get size of type.
        /// </summary>
        /// <param name="s">The type.</param>
        /// <returns></returns>
        internal static int SizeOf(Type s)
        {
            if (Main.Game != null)
            {
                TypeDescriptor t = null;
                if (Main.Game.Types.TypesByInterface.TryGetValue(s, out t))
                {
                    if (t.Size >= 0)
                        return t.Size;
                    throw new NotImplementedException("Size of type \"" + s.Name + "\" is not specified!");
                }

                throw new InvalidOperationException("Type \"" + s.Name + "\" is not registered in game library!");
            }

            {
                if (s == typeof(IMemoryObject))
                    return 0;
                if (s == typeof(IVirtualObject) || IsPointerObjectInterfaceType(s))
                    return Main.Is64Bit ? 8 : 4;

                throw new InvalidOperationException("Unable to get size for type \"" + s.Name + "\" - game library is not loaded!");
            }
        }

        /// <summary>
        /// Copies all data from another object.
        /// </summary>
        /// <typeparam name="T">Type of object to copy from. Both this and the other object must have this type!</typeparam>
        /// <param name="obj">The object.</param>
        public void CopyFrom<T>(T obj) where T : IMemoryObject
        {
            int size = SizeOf<T>();
            if(size > 0)
            {
                var bytes = Memory.ReadBytes(obj.Address, size);
                Memory.WriteBytes(this.Address, bytes);
            }
        }
        
        /// <summary>
        /// Get an object in memory from specified base address.
        /// </summary>
        /// <typeparam name="T">Type of object to get.</typeparam>
        /// <param name="address">The base address of object.</param>
        /// <returns></returns>
        public static T FromAddress<T>(IntPtr address) where T : IMemoryObject
        {
            if (address == IntPtr.Zero)
                return default(T);

            TypeDescriptor t = null;
            if(Main.Game != null)
            {
                if (!Main.Game.Types.TypesByInterface.TryGetValue(typeof(T), out t))
                {
                    t = null;

                    var t3 = typeof(T);
                    if (t3.IsGenericType && !t3.IsGenericTypeDefinition)
                    {
                        var t2 = t3.GetGenericTypeDefinition();
                        if (!Main.Game.Types.TypesByInterface.TryGetValue(t2, out t))
                            t = null;
                    }
                }
            }

            if (t == null)
                throw new ArgumentException("Type \"" + typeof(T).Name + "\" is not registered with game library!");

            MemoryObject mo = null;
            if (t.IsGeneric)
            {
                var ci = t.GetGenericConstructor(typeof(T).GenericTypeArguments);
                mo = (MemoryObject)ci.Invoke(new object[0]);
            }
            else
                mo = (MemoryObject)t.ConstructorNonGeneric.Invoke(new object[0]);

            mo.Address = address;
            object result = mo;
            return (T)result;
        }

        /// <summary>
        /// Get an object in memory from specified base address. This will try to use runtime dynamic cast to ensure object is valid type.
        /// It will return null if object could not be cast, type is not registered or memory could not be read properly. The base address
        /// of returned object may or may not equal specified address.
        /// </summary>
        /// <typeparam name="T">Type of object to get.</typeparam>
        /// <param name="address">The base address of object. If an object is returned the base address of object may be different!</param>
        /// <returns></returns>
        public static T FromAddressSafeCast<T>(IntPtr address) where T : IVirtualObject
        {
            if (address == IntPtr.Zero)
                return default(T);

            TypeDescriptor t = null;
            if (Main.Game != null)
            {
                if (!Main.Game.Types.TypesByInterface.TryGetValue(typeof(T), out t))
                {
                    t = null;

                    var t3 = typeof(T);
                    if (t3.IsGenericType && !t3.IsGenericTypeDefinition)
                    {
                        var t2 = t3.GetGenericTypeDefinition();
                        if (!Main.Game.Types.TypesByInterface.TryGetValue(t2, out t))
                            t = null;
                    }
                }
            }

            if (t == null)
                return default(T);

            T mo;
            try
            {
                mo = MemoryObject.FromAddress<T>(address);
            }
            catch(ArgumentException)
            {
                return default(T);
            }

            try
            {
                var result = mo.As<T>();
                return result;
            }
            catch(NotSupportedException)
            {

            }

            return default(T);
        }

        /// <summary>
        /// Get an object in memory from specified base address.
        /// </summary>
        /// <param name="t">The type of object.</param>
        /// <param name="address">The address.</param>
        /// <returns></returns>
        /// <exception cref="System.ArgumentNullException">t</exception>
        /// <exception cref="System.ArgumentException">
        /// Type can not be abstract!
        /// or
        /// Type must inherit from MemoryObject!
        /// </exception>
        public static IMemoryObject FromAddress(Type t, IntPtr address)
        {
            if (t == null)
                throw new ArgumentNullException("t");
            if (!t.IsInterface)
                throw new ArgumentException("Type must be interface!");
            if (t != typeof(IMemoryObject) && !typeof(IMemoryObject).IsAssignableFrom(t))
                throw new ArgumentException("Type must inherit from IMemoryObject!");

            if (address == IntPtr.Zero)
                return null;

            TypeDescriptor td = null;
            if (Main.Game != null)
            {
                if (!Main.Game.Types.TypesByInterface.TryGetValue(t, out td))
                {
                    td = null;

                    if(t.IsGenericType && !t.IsGenericTypeDefinition)
                    {
                        var t2 = t.GetGenericTypeDefinition();
                        if (!Main.Game.Types.TypesByInterface.TryGetValue(t2, out td))
                            td = null;
                    }
                }
            }

            if (td == null)
                throw new ArgumentException("Type \"" + t.Name + "\" is not registered with game library!");

            MemoryObject mo = null;
            if (td.IsGeneric)
            {
                var ci = td.GetGenericConstructor(t.GenericTypeArguments);
                mo = (MemoryObject)ci.Invoke(new object[0]);
            }
            else
                mo = (MemoryObject)td.ConstructorNonGeneric.Invoke(new object[0]);

            mo.Address = address;
            return mo;
        }

        /// <summary>
        /// Get an object in memory from specified base address.
        /// </summary>
        /// <param name="t">The type of object.</param>
        /// <param name="address">The address.</param>
        /// <returns></returns>
        /// <exception cref="System.ArgumentNullException">t</exception>
        /// <exception cref="System.ArgumentException">
        /// Type can not be abstract!
        /// or
        /// Type must inherit from VirtualObject!
        /// </exception>
        public static IVirtualObject FromAddressSafeCast(Type t, IntPtr address)
        {
            if (t == null)
                throw new ArgumentNullException("t");
            if (!t.IsInterface)
                throw new ArgumentException("Type must be interface!");
            if (t != typeof(IVirtualObject) && !typeof(IVirtualObject).IsAssignableFrom(t))
                throw new ArgumentException("Type must inherit from IVirtualObject!");

            if (address == IntPtr.Zero)
                return null;

            TypeDescriptor td = null;
            if (Main.Game != null)
            {
                if (!Main.Game.Types.TypesByInterface.TryGetValue(t, out td))
                {
                    td = null;

                    if (t.IsGenericType && !t.IsGenericTypeDefinition)
                    {
                        var t2 = t.GetGenericTypeDefinition();
                        if (!Main.Game.Types.TypesByInterface.TryGetValue(t2, out td))
                            td = null;
                    }
                }
            }

            if (td == null)
                return null;

            VirtualObject mo = null;
            if (td.IsGeneric)
            {
                var ci = td.GetGenericConstructor(t.GenericTypeArguments);
                mo = (VirtualObject)ci.Invoke(new object[0]);
            }
            else
                mo = (VirtualObject)td.ConstructorNonGeneric.Invoke(new object[0]);

            mo.Address = address;

            try
            {
                return mo.As(t);
            }
            catch(NotSupportedException)
            {
            }

            return null;
        }

        /// <summary>
        /// Get an object in memory from specified pointer.
        /// </summary>
        /// <typeparam name="T">Type of object to get.</typeparam>
        /// <param name="address">The pointer address of object.</param>
        /// <returns></returns>
        public static T FromPointer<T>(IntPtr address) where T : IMemoryObject
        {
            return MemoryObject.FromAddress<T>(Memory.ReadPointer(address));
        }

        /// <summary>
        /// Get an object in memory from specified pointer.
        /// </summary>
        /// <param name="t">The type of object to get.</param>
        /// <param name="address">The pointer address.</param>
        /// <returns></returns>
        /// <exception cref="System.ArgumentNullException">t</exception>
        /// <exception cref="System.ArgumentException">
        /// Type can not be abstract!
        /// or
        /// Type must inherit from MemoryObject!
        /// </exception>
        public static IMemoryObject FromPointer(Type t, IntPtr address)
        {
            return MemoryObject.FromAddress(t, Memory.ReadPointer(address));
        }

        /// <summary>
        /// Gets the interface type of the current memory object wrapper.
        /// </summary>
        /// <returns></returns>
        /// <exception cref="System.NotSupportedException"></exception>
        public Type GetInterfaceType()
        {
            Type result = null;
            var impl = this.GetImplementationType();
            Type[] gen = null;
            if(impl.IsGenericType && !impl.IsGenericTypeDefinition)
            {
                gen = impl.GetGenericArguments();
                impl = impl.GetGenericTypeDefinition();
            }

            if (impl == typeof(MemoryObject))
                result = typeof(IMemoryObject);
            else if (impl == typeof(VirtualObject))
                result = typeof(IVirtualObject);
            else
            {
                var game = Main.Game;
                if (game != null)
                {
                    TypeDescriptor descriptor = null;
                    if (!game.Types.TypesByImplementation.TryGetValue(impl, out descriptor))
                        throw new NotSupportedException();

                    result = descriptor.InterfaceType;
                }
                else
                    throw new NotSupportedException();
            }

            if(gen != null && result.IsGenericType && result.IsGenericTypeDefinition)
                result = result.MakeGenericType(gen);

            return result;
        }

        /// <summary>
        /// Gets the implementation type of the current memory object wrapper.
        /// </summary>
        /// <returns></returns>
        public Type GetImplementationType()
        {
            return this.GetType();
        }

        #endregion

        #region Internal members

        /// <summary>
        /// Determines whether the specified type is pointer object interface type.
        /// </summary>
        /// <param name="t">The type.</param>
        /// <returns></returns>
        private static bool IsPointerObjectInterfaceType(Type t)
        {
            if (t == null || !t.IsInterface)
                return false;

            if (t == typeof(IPointerObject))
                return true;

            if (t.IsGenericTypeDefinition)
            {
                if(t == typeof(IPointerObject<>))
                    return true;
            }
            else
            {
                t = t.GetGenericTypeDefinition();
                if (t == typeof(IPointerObject<>))
                    return true;
            }

            return false;
        }

        #endregion

        #region Object members

        /// <summary>
        /// Returns a hash code for this instance.
        /// </summary>
        /// <returns>
        /// A hash code for this instance, suitable for use in hashing algorithms and data structures like a hash table. 
        /// </returns>
        public override int GetHashCode()
        {
            return this.Address.GetHashCode();
        }

        /// <summary>
        /// Determines whether the specified <see cref="System.Object" />, is equal to this instance. If the specified object
        /// is not a <see cref="MemoryObject" /> or is null then this method will return false!
        /// </summary>
        /// <param name="obj">The <see cref="System.Object" /> to compare with this instance.</param>
        /// <returns>
        ///   <c>true</c> if the specified <see cref="System.Object" /> is equal to this instance; otherwise, <c>false</c>.
        /// </returns>
        public override bool Equals(object obj)
        {
            var mo = obj as MemoryObject;
            if (mo != null)
                return this.Address == mo.Address;
            return false;
        }

        /// <summary>
        /// Determines whether the specified <see cref="NetScriptFramework.IMemoryObject" />, is equal to this instance. If the specified object
        /// is not a <see cref="NetScriptFramework.IMemoryObject" /> or is null then this method will return false!
        /// </summary>
        /// <param name="obj">The <see cref="NetScriptFramework.IMemoryObject" /> to compare with this instance.</param>
        /// <returns>
        ///   <c>true</c> if the specified <see cref="NetScriptFramework.IMemoryObject" /> is equal to this instance; otherwise, <c>false</c>.
        /// </returns>
        public bool Equals(IMemoryObject obj)
        {
            var mo = obj as MemoryObject;
            if (mo != null)
                return this.Address == mo.Address;
            return false;
        }
        
        /// <summary>
        /// Returns a <see cref="System.String" /> that represents this instance.
        /// </summary>
        /// <returns>
        /// A <see cref="System.String" /> that represents this instance.
        /// </returns>
        public override string ToString()
        {
            return string.Format("{0}:[{1}]", this.GetType().Name, this.Address == IntPtr.Zero ? "NULL" : ("0x" + this.Address.ToInt64().ToString("X")));
        }

        #endregion

        #region IArgument members

        /// <summary>
        /// Parse an argument from this object.
        /// </summary>
        /// <param name="key">Keyword for argument.</param>
        /// <param name="message">Message to parse for.</param>
        /// <param name="parser">Parser that is currently processing message.</param>
        /// <returns></returns>
        public Tools.IArgument ParseArgument(string key, Tools.Message message, Tools.Parser parser)
        {
            var prop = this._GetProperty(key);
            if (prop == null || prop.GetMethod == null)
                return null;

            object instance = prop.GetMethod.IsStatic ? null : this;
            return prop.GetMethod.Invoke(instance, new object[0]) as Tools.IArgument;
        }

        /// <summary>
        /// Parse a variable from this object.
        /// </summary>
        /// <param name="key">Keyword for variable.</param>
        /// <param name="message">Message to parse for.</param>
        /// <param name="parser">Parser that is currently processing message.</param>
        /// <returns></returns>
        public string ParseVariable(string key, Tools.Message message, Tools.Parser parser)
        {
            var prop = this._GetProperty(key);
            if (prop == null || prop.GetMethod == null)
                return null;

            object instance = prop.GetMethod.IsStatic ? null : this;
            object result = prop.GetMethod.Invoke(instance, new object[0]);
            if (object.ReferenceEquals(result, null))
                return null;
            if (result is float)
                return ((float)result).ToString(System.Globalization.CultureInfo.InvariantCulture);
            if (result is double)
                return ((double)result).ToString(System.Globalization.CultureInfo.InvariantCulture);
            if (result is IntPtr)
                return ((IntPtr)result).ToHexString();
            return result.ToString();
        }

        /// <summary>
        /// Parse a function from this object.
        /// </summary>
        /// <param name="key">Keyword for function.</param>
        /// <param name="args">Arguments for function.</param>
        /// <param name="message">Message to parse for.</param>
        /// <param name="parser">Parser that is currently processing message.</param>
        /// <returns></returns>
        public string ParseFunction(string key, string[] args, Tools.Message message, Tools.Parser parser)
        {
            return null;
        }

        /// <summary>
        /// Get a property of this object by its name.
        /// </summary>
        /// <param name="name">The name of property.</param>
        /// <returns></returns>
        private System.Reflection.PropertyInfo _GetProperty(string name)
        {
            if (string.IsNullOrEmpty(name))
                return null;

            var t = this.GetType();
            while(t != null)
            {
                try
                {
                    var prop = t.GetProperty(name, System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.NonPublic | System.Reflection.BindingFlags.Instance | System.Reflection.BindingFlags.Static | System.Reflection.BindingFlags.DeclaredOnly);
                    if (prop != null)
                        return prop;
                }
                catch(System.Reflection.AmbiguousMatchException)
                {

                }

                t = t.BaseType;
            }

            return null;
        }

        #endregion
    }

    #endregion

    #region IMemoryObject interface

    /// <summary>
    /// Base implementation of a wrapper for an object that exists in memory. Use the Equals methods to check
    /// equality with another object rather than equality operator.
    /// </summary>
    /// <seealso cref="System.IEquatable{NetScriptFramework.IMemoryObject}" />
    public interface IMemoryObject : IEquatable<IMemoryObject>
    {
        /// <summary>
        /// Gets the base address of the object in memory.
        /// </summary>
        /// <value>
        /// The base address of object in memory.
        /// </value>
        IntPtr Address
        {
            get;
        }

        /// <summary>
        /// Returns true if memory object is valid and can be accessed. It is possible for this to return true even if
        /// the object is not actually valid in case of bad pointers or freed memory!
        /// </summary>
        /// <value>
        ///   <c>true</c> if this instance is valid; otherwise, <c>false</c>.
        /// </value>
        bool IsValid
        {
            get;
        }

        /// <summary>
        /// Copies all data (shallow copy) from another object.
        /// </summary>
        /// <typeparam name="T">Type of object to copy from. Both this and the other object must have this type!</typeparam>
        /// <param name="obj">The object.</param>
        void CopyFrom<T>(T obj) where T : IMemoryObject;
    }

    #endregion
}
