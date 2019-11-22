using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetScriptFramework.Tools._Internal
{
    /// <summary>
    /// Helper class that contains information for runtime dynamic cast.
    /// </summary>
    public static class RTTI
    {
        /// <summary>
        /// Registers the specified type to RTTI map.
        /// </summary>
        /// <param name="intType">The interface type.</param>
        /// <param name="implType">The implementation type.</param>
        /// <param name="address">The addresses.</param>
        /// <param name="moduleBase">Current module base address.</param>
        internal static void Register(Type intType, Type implType, uint[] address, IntPtr moduleBase)
        {
            if (intType == null)
                throw new ArgumentNullException("intType");
            if (implType == null)
                throw new ArgumentNullException("implType");
            if (address == null)
                throw new ArgumentNullException("address");
            if (moduleBase == null)
                throw new ArgumentNullException("moduleBase");

            if (MapInterface.ContainsKey(intType))
                throw new InvalidOperationException("RTTI for \"" + intType.Name + "\" already exists!");
            if (MapImplementation.ContainsKey(implType))
                throw new InvalidOperationException("RTTI for \"" + implType.Name + "\" already exists!");
            
            address = address.ToArray();

            MapInterface[intType] = new Tuple<Type, uint[], IntPtr>(implType, address, moduleBase);
            MapImplementation[implType] = new Tuple<Type, uint[], IntPtr>(intType, address, moduleBase);
        }
        
        /// <summary>
        /// Attempt to perform a dynamic cast on an object. This will throw an exception if source or target type is unsupported
        /// or if the RTTI cast function has not been set up!
        /// </summary>
        /// <param name="obj">The object.</param>
        /// <param name="target">Type of object to cast to.</param>
        /// <returns></returns>
        internal static IVirtualObject DynamicCast(IVirtualObject obj, Type target)
        {
            if (obj == null || obj.Address == IntPtr.Zero)
                return null;

            if (target == typeof(IVirtualObject))
                return obj;

            // Get target RTTI. There may be more than one if we combined types.
            Tuple<Type, uint[], IntPtr> targetInfo;
            {
                if (!MapInterface.TryGetValue(target, out targetInfo))
                    throw new NotSupportedException("Missing RTTI type descriptor for target \"" + target.Name + "\"!");
            }
            
            // Try multiple RTTI addresses.
            foreach (var ip in targetInfo.Item2)
            {
                var result = Custom_RTTI_Cast(obj.Address, ip, targetInfo.Item3);
                if (result != IntPtr.Zero)
                    return (IVirtualObject)MemoryObject.FromAddress(target, result);
            }

            // None matched or didn't have any in the list.
            return null;
        }

        /// <summary>
        /// Attempt to perform a dynamic cast on an object. This will throw an exception if source or target type is unsupported
        /// or if the RTTI cast function has not been set up!
        /// </summary>
        /// <typeparam name="T">Type of object to cast to.</typeparam>
        /// <param name="obj">The object.</param>
        /// <returns></returns>
        internal static T DynamicCast<T>(IVirtualObject obj) where T : IVirtualObject
        {
            if (obj == null || obj.Address == IntPtr.Zero)
                return default(T);
            
            var target = typeof(T);
            if (target == typeof(IVirtualObject))
                return (T)obj;
            
            // Get target RTTI. There may be more than one if we combined types.
            Tuple<Type, uint[], IntPtr> targetInfo;
            {
                if (!MapInterface.TryGetValue(target, out targetInfo))
                    throw new NotSupportedException("Missing RTTI type descriptor for target \"" + target.Name + "\"!");
            }

            // Try multiple RTTI addresses.
            foreach (var ip in targetInfo.Item2)
            {
                var result = Custom_RTTI_Cast(obj.Address, ip, targetInfo.Item3);
                if (result != IntPtr.Zero)
                    return (T)MemoryObject.FromAddress(target, result);
            }
            
            // None matched or didn't have any in the list.
            return default(T);
        }

        /// <summary>
        /// Custom RTTI cast implementation.
        /// </summary>
        /// <param name="obj">The object.</param>
        /// <param name="target">The target.</param>
        /// <param name="moduleBase">The module base.</param>
        /// <returns></returns>
        [System.Runtime.InteropServices.DllImport("NetScriptFramework.Runtime.dll")]
        private static extern IntPtr Custom_RTTI_Cast(IntPtr obj, uint target, IntPtr moduleBase);

        /// <summary>
        /// The info for dynamic cast.
        /// </summary>
        private static readonly Dictionary<Type, Tuple<Type, uint[], IntPtr>> MapInterface = new Dictionary<Type, Tuple<Type, uint[], IntPtr>>();

        /// <summary>
        /// The info for dynamic cast.
        /// </summary>
        private static readonly Dictionary<Type, Tuple<Type, uint[], IntPtr>> MapImplementation = new Dictionary<Type, Tuple<Type, uint[], IntPtr>>();
    }
}
