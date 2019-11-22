using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetScriptFramework
{
    /// <summary>
    /// Implement pointer to another object. This can be used as address of X or double pointer for example.
    /// </summary>
    /// <seealso cref="NetScriptFramework.IPointerObject" />
    /// <seealso cref="NetScriptFramework.MemoryObject" />
    public class PointerObject : MemoryObject, IPointerObject
    {
        #region Members

        /// <summary>
        /// Gets the address where this pointer points to.
        /// </summary>
        /// <value>
        /// The target address.
        /// </value>
        public IntPtr Target
        {
            get
            {
                return Memory.ReadPointer(this.Address);
            }
        }

        #endregion
    }

    /// <summary>
    /// Implement pointer to another object. This can be used as address of X or double pointer for example.
    /// </summary>
    /// <typeparam name="T">Type of pointer.</typeparam>
    /// <seealso cref="NetScriptFramework.MemoryObject" />
    public class PointerObject<T> : MemoryObject, IPointerObject<T> where T : IMemoryObject
    {
        #region Members

        /// <summary>
        /// Gets the object where this pointer points to.
        /// </summary>
        /// <value>
        /// The target object.
        /// </value>
        public T Target
        {
            get
            {
                var p = Memory.ReadPointer(this.Address);
                if (p == IntPtr.Zero)
                    return default(T);

                return MemoryObject.FromAddress<T>(p);
            }
        }

        #endregion
    }

    /// <summary>
    /// Implement pointer to another object. This can be used as address of X or double pointer for example.
    /// </summary>
    /// <seealso cref="NetScriptFramework.IMemoryObject" />
    public interface IPointerObject : IMemoryObject
    {
        /// <summary>
        /// Gets the address where this pointer points to.
        /// </summary>
        /// <value>
        /// The target address.
        /// </value>
        IntPtr Target
        {
            get;
        }
    }

    /// <summary>
    /// Implement pointer to another object. This can be used as address of X or double pointer for example.
    /// </summary>
    /// <typeparam name="T">Type of pointer.</typeparam>
    /// <seealso cref="NetScriptFramework.IMemoryObject" />
    public interface IPointerObject<T> : IMemoryObject where T : IMemoryObject
    {
        /// <summary>
        /// Gets the address where this pointer points to.
        /// </summary>
        /// <value>
        /// The target address.
        /// </value>
        T Target
        {
            get;
        }
    }
}
