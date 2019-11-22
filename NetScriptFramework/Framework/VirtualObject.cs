using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetScriptFramework
{
    /// <summary>
    /// Base implementation of a type that has a virtual table.
    /// </summary>
    /// <seealso cref="NetScriptFramework.IVirtualObject" />
    /// <seealso cref="NetScriptFramework.MemoryObject" />
    public class VirtualObject : MemoryObject, IVirtualObject
    {
        #region Members

        /// <summary>
        /// Gets the virtual table address of object at base. Object may have more than one virtual table!
        /// </summary>
        /// <value>
        /// The virtual table address.
        /// </value>
        public IntPtr VTable
        {
            get
            {
                return Memory.ReadPointer(this.Address);
            }
        }

        /// <summary>
        /// Returns true if memory object is valid and can be accessed for reading. It is possible for this to return true even if
        /// the object is not actually valid in case of bad pointers to valid memory regions, invalid cast or partially freed memory!
        /// </summary>
        /// <value>
        ///   <c>true</c> if this instance is valid; otherwise, <c>false</c>.
        /// </value>
        public override bool IsValid
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

                return this.Is(self);
            }
        }

        /// <summary>
        /// Determines whether this object is specified type.
        /// </summary>
        /// <typeparam name="T">Type to check.</typeparam>
        /// <returns></returns>
        public bool Is<T>() where T : IVirtualObject
        {
            return this.As<T>() != null;
        }

        /// <summary>
        /// Tries to cast this object into specified type.
        /// </summary>
        /// <typeparam name="T">Type to cast to.</typeparam>
        /// <returns></returns>
        public T As<T>() where T : IVirtualObject
        {
            return Tools._Internal.RTTI.DynamicCast<T>(this);
        }

        /// <summary>
        /// Tries to cast this object into specified type.
        /// </summary>
        /// <param name="t">Type to cast to.</param>
        /// <returns></returns>
        internal IVirtualObject As(Type t)
        {
            return Tools._Internal.RTTI.DynamicCast(this, t);
        }

        /// <summary>
        /// Determines whether this object is specified type.
        /// </summary>
        /// <param name="t">The type to check.</param>
        /// <returns></returns>
        internal bool Is(Type t)
        {
            if (t == null)
                throw new ArgumentNullException("t");

            return this.As(t) != null;
        }

        /// <summary>
        /// Invokes a "thiscall" native function from the virtual table of this object.
        /// </summary>
        /// <param name="vtblOffset">The offset of virtual function table in this object.</param>
        /// <param name="offset">The offset of function in the virtual table.</param>
        /// <param name="args">The arguments of function.</param>
        /// <returns></returns>
        public IntPtr InvokeVTableThisCall(int vtblOffset, int offset, params InvokeArgument[] args)
        {
            var vtable = Memory.ReadPointer(this.Address + vtblOffset);
            vtable += offset;
            var funcAddr = Memory.ReadPointer(vtable);
            return Memory.InvokeThisCall(this.Address + vtblOffset, funcAddr, args);
        }

        /// <summary>
        /// Invokes a "thiscall" native function that returns a floating point value from the virtual table of this object.
        /// </summary>
        /// <param name="vtblOffset">The offset of virtual function table in this object.</param>
        /// <param name="offset">The offset of function in the virtual table.</param>
        /// <param name="args">The arguments of function.</param>
        /// <returns></returns>
        public double InvokeVTableThisCallF(int vtblOffset, int offset, params InvokeArgument[] args)
        {
            var vtable = Memory.ReadPointer(this.Address + vtblOffset);
            vtable += offset;
            var funcAddr = Memory.ReadPointer(vtable);
            return Memory.InvokeThisCallF(this.Address + vtblOffset, funcAddr, args);
        }

        #endregion
    }

    #region IVirtualObject interface

    /// <summary>
    /// Base implementation of a type that has a virtual table.
    /// </summary>
    /// <seealso cref="NetScriptFramework.IMemoryObject" />
    public interface IVirtualObject : IMemoryObject
    {
        /// <summary>
        /// Gets the virtual table address of object at base. Object may have more than one virtual table!
        /// </summary>
        /// <value>
        /// The virtual table address.
        /// </value>
        IntPtr VTable
        {
            get;
        }

        /// <summary>
        /// Determines whether this object is specified type.
        /// </summary>
        /// <typeparam name="T">Type to check.</typeparam>
        /// <returns></returns>
        bool Is<T>() where T : IVirtualObject;

        /// <summary>
        /// Tries to cast this object into specified type.
        /// </summary>
        /// <typeparam name="T">Type to cast to.</typeparam>
        /// <returns></returns>
        T As<T>() where T : IVirtualObject;

        /// <summary>
        /// Invokes a "thiscall" native function from the virtual table of this object.
        /// </summary>
        /// <param name="vtblOffset">The offset of virtual function table in this object.</param>
        /// <param name="offset">The offset of function in the virtual table. This is not the index!</param>
        /// <param name="args">The arguments of function.</param>
        /// <returns></returns>
        IntPtr InvokeVTableThisCall(int vtblOffset, int offset, params InvokeArgument[] args);

        /// <summary>
        /// Invokes a "thiscall" native function that returns a floating point value from the virtual table of this object.
        /// </summary>
        /// <param name="vtblOffset">The offset of virtual function table in this object.</param>
        /// <param name="offset">The offset of function in the virtual table. This is not the index!</param>
        /// <param name="args">The arguments of function.</param>
        /// <returns></returns>
        double InvokeVTableThisCallF(int vtblOffset, int offset, params InvokeArgument[] args);
    }

    #endregion
}
