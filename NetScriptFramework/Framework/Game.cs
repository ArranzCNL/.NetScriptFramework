using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace NetScriptFramework
{
    /// <summary>
    /// Contains header information about current game.
    /// </summary>
    public abstract class Game
    {
        #region Constructors

        /// <summary>
        /// Initializes a new instance of the <see cref="Game"/> class.
        /// </summary>
        public Game()
        {
            if (System.Threading.Interlocked.Exchange(ref Main.GameCreate, 0) != 1)
                throw new InvalidOperationException("Game header information can not be manually created! Use Main.Game property to fetch current game information.");

            this.RegisterType(IntPtr.Zero, "internal:MemoryObject", typeof(IMemoryObject), typeof(MemoryObject), 0, null);
            this.RegisterType(IntPtr.Zero, "internal:VirtualObject", typeof(IVirtualObject), typeof(VirtualObject), IntPtr.Size, null);
            this.RegisterType(IntPtr.Zero, "internal:PointerObject", typeof(IPointerObject), typeof(PointerObject), IntPtr.Size, null);
            this.RegisterType(IntPtr.Zero, "internal:PointerObject<>", typeof(IPointerObject<>), typeof(PointerObject<>), IntPtr.Size, null);
        }

        #endregion

        #region Game members

        /// <summary>
        /// Gets the short name of current game. For example "Skyrim".
        /// </summary>
        /// <value>
        /// The short name.
        /// </value>
        public abstract string ShortName
        {
            get;
        }

        /// <summary>
        /// Gets the full name of current game. For example "The Elder Scrolls V: Skyrim"
        /// </summary>
        /// <value>
        /// The full name.
        /// </value>
        public abstract string FullName
        {
            get;
        }

        /// <summary>
        /// Gets the name of the executable of current game including file extension. For example "TESV.exe".
        /// </summary>
        /// <value>
        /// The name of the executable.
        /// </value>
        public abstract string ExecutableName
        {
            get;
        }

        /// <summary>
        /// Gets the name of the target module. This is usually equal to ExecutableName but sometimes we may want to target a DLL inside the process instead in which case they would be different.
        /// </summary>
        /// <value>
        /// The name of the module.
        /// </value>
        public abstract string ModuleName
        {
            get;
        }

        /// <summary>
        /// Gets the version of current game. It is read from the executable. This is a list of four integers always.
        /// The first integer in the list is the most significant version number and last is the least significant.
        /// For example { 1, 9, 32, 0 }
        /// </summary>
        /// <value>
        /// The version of game.
        /// </value>
        public abstract IReadOnlyList<int> GameVersion
        {
            get;
        }

        /// <summary>
        /// Gets the library version. This is separate from game's version. Multiple library versions may exist for the same
        /// version of the game.
        /// </summary>
        /// <value>
        /// The library version.
        /// </value>
        public abstract int LibraryVersion
        {
            get;
        }

        /// <summary>
        /// Gets a value indicating whether currently loaded game version is a valid version supported by this library.
        /// This is only used during game header initialization. If it returns false the game will abort and display an error.
        /// </summary>
        /// <value>
        /// <c>true</c> if this instance is valid version; otherwise, <c>false</c>.
        /// </value>
        public abstract bool IsValidVersion
        {
            get;
        }

        /// <summary>
        /// Initializes the game library.
        /// </summary>
        protected virtual void Initialize()
        {

        }

        internal void _initialize()
        {
            this.Initialize();
        }

        /// <summary>
        /// The types cache.
        /// </summary>
        internal readonly TypeCache Types = new TypeCache();

        /// <summary>
        /// Parses the version.
        /// </summary>
        /// <param name="str">The string.</param>
        /// <param name="a">a.</param>
        /// <param name="b">b.</param>
        /// <param name="c">c.</param>
        /// <param name="d">d.</param>
        /// <returns></returns>
        protected int[] ParseVersion(string str, int a, int b, int c, int d)
        {
            if(!string.IsNullOrEmpty(str))
            {
                string[] spl = str.Split(new[] { "." }, StringSplitOptions.None);
                if (spl.Length > 4 || spl.Length == 0)
                    return null;

                int[] result = new int[4];
                for(int i = 0; i < result.Length; i++)
                {
                    int t = 0;
                    if (!int.TryParse(spl[i], out t) || t < 0 || t >= 65536)
                        return null;
                    result[i] = t;
                }
                if (IsBadVersion(result))
                    return null;
                return result;
            }

            {
                int[] result = new int[] { a, b, c, d };
                if (IsBadVersion(result))
                    return null;
                return result;
            }
        }

        /// <summary>
        /// Determines whether the version is bad or missing possibly.
        /// </summary>
        /// <param name="r">The version.</param>
        /// <returns></returns>
        private bool IsBadVersion(int[] r)
        {
            if (r.All(q => q == 0))
                return true;

            if(r[0] == 1)
            {
                bool yes = true;
                for(int i = 1; i < r.Length; i++)
                {
                    if(r[i] != 0)
                    {
                        yes = false;
                        break;
                    }
                }

                if (yes)
                    return true;
            }

            return false;
        }

        /// <summary>
        /// Registers the type to library. This must be done for all types.
        /// </summary>
        /// <param name="module">The module base address where this type is in. If zero then it's current process main module.</param>
        /// <param name="name">The name of type. This should be equal to the name of interface.</param>
        /// <param name="interfaceType">Type of the interface.</param>
        /// <param name="implementationType">Type of the implementation.</param>
        /// <param name="size">The total size of type. Negative if unknown.</param>
        /// <param name="rtti">The RTTI. This is null if unknown and empty if not available.</param>
        /// <param name="debugWriters">The debug writers.</param>
        /// <exception cref="System.ArgumentNullException">
        /// name
        /// or
        /// interfaceType
        /// or
        /// implementationType
        /// </exception>
        /// <exception cref="System.ArgumentOutOfRangeException">
        /// name;Name of type must not be empty and can't begin or end with whitespace!
        /// or
        /// offset;Offset can not be negative!
        /// </exception>
        /// <exception cref="System.ArgumentException">
        /// Interface type must be an interface!;interfaceType
        /// or
        /// Interface type must inherit from IMemoryObject interface!;interfaceType
        /// or
        /// Implementation type must inherit from MemoryObject!;implementationType
        /// or
        /// Implementation type must not be abstract!;implementationType
        /// or
        /// A type with this name \ + name + \ is already registered!
        /// or
        /// A type with specified interface \ + interfaceType.Name + \ is already registered!
        /// or
        /// A valid parameterless constructor was not found on type \ + implementationType.Name + \!
        /// </exception>
        protected void RegisterType(IntPtr module, string name, Type interfaceType, Type implementationType, int size, uint[] rtti, params Tools._Internal.TypeDebugWriter[] debugWriters)
        {
            if (module == IntPtr.Zero)
                module = Main.GetMainTargetedModule().BaseAddress;
            if (name == null)
                throw new ArgumentNullException("name");
            if (name.Length == 0 || name.Trim().Length != name.Length)
                throw new ArgumentOutOfRangeException("name", "Name of type must not be empty and can't begin or end with whitespace!");
            if (interfaceType == null)
                throw new ArgumentNullException("interfaceType");
            if (implementationType == null)
                throw new ArgumentNullException("implementationType");
            if (!interfaceType.IsInterface)
                throw new ArgumentException("Interface type must be an interface!", "interfaceType");
            if (interfaceType != typeof(IMemoryObject) && !typeof(IMemoryObject).IsAssignableFrom(interfaceType))
                throw new ArgumentException("Interface type must inherit from IMemoryObject interface!", "interfaceType");
            if (implementationType != typeof(MemoryObject) && !implementationType.IsSubclassOf(typeof(MemoryObject)))
                throw new ArgumentException("Implementation type must inherit from MemoryObject!", "implementationType");
            if (implementationType.IsAbstract)
                throw new ArgumentException("Implementation type must not be abstract!", "implementationType");

            TypeDescriptor t = null;
            if (this.Types.TypesByName.TryGetValue(name, out t))
                throw new ArgumentException("A type with this name \"" + name + "\" is already registered!");
            if (this.Types.TypesByInterface.TryGetValue(interfaceType, out t))
                throw new ArgumentException("A type with specified interface \"" + interfaceType.Name + "\" is already registered!");
            if (this.Types.TypesByImplementation.TryGetValue(implementationType, out t))
                throw new ArgumentException("A type with specified implementation \"" + implementationType.Name + "\" is already registered!");

            ConstructorInfo ci = null;
            if (!implementationType.IsGenericTypeDefinition)
            {
                var cis = implementationType.GetConstructors(BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance);
                foreach (var c in cis)
                {
                    if (!c.IsStatic && c.GetParameters().Length == 0)
                        ci = c;
                }
                if (ci == null)
                    throw new ArgumentException("A valid parameterless constructor was not found on type \"" + implementationType.Name + "\"!");
            }

            t = new TypeDescriptor();
            t.Name = name;
            t.InterfaceType = interfaceType;
            t.ImplementationType = implementationType;
            t.Size = size;
            t.RTTI = rtti;
            t.ConstructorNonGeneric = ci;
            t.IsGeneric = implementationType.IsGenericTypeDefinition;
            t.Module = module;
            var wr = debugWriters.Where(q => q != null).ToList();
            if (wr.Count != 0)
            {
                t.DebugWriters.AddRange(wr);
                this.Types.TypesWithDebugWriters.Add(t);
            }

            this.Types.TypesByInterface[t.InterfaceType] = t;
            this.Types.TypesByImplementation[t.ImplementationType] = t;
            this.Types.TypesByName[t.Name] = t;

            if (t.RTTI != null)
                Tools._Internal.RTTI.Register(t.InterfaceType, t.ImplementationType, t.RTTI, t.Module);
        }

        /// <summary>
        /// Registers the debug writer for the specified type. This will show up in NativeCrashLog.GetValueInfo method or in crash log to display more information
        /// about a specific type or any type inheriting from this type. This method may only be called during plugin initialization.
        /// </summary>
        /// <typeparam name="T">Type of object to write extra information about.</typeparam>
        /// <param name="parameterName">Name of the parameter. If another writer for this parameter is already registered it will be replaced!</param>
        /// <param name="writerFunc">The writer function. If this is null then the object's ToString method will be called instead.</param>
        /// <exception cref="System.InvalidOperationException">Debug writers can only be registered during initialization of plugins!</exception>
        /// <exception cref="System.ArgumentException">Type ` + t.Name + ` was not found in game library!;T</exception>
        public void RegisterDebugWriter<T>(string parameterName, Func<IVirtualObject, string> writerFunc) where T : IVirtualObject
        {
            if (Main._is_initializing_plugin != 2)
                throw new InvalidOperationException("Debug writers can only be registered during initialization of plugins!");

            parameterName = (parameterName ?? string.Empty).Trim();
            var t = typeof(T);
            TypeDescriptor descriptor = null;
            if (!this.Types.TypesByInterface.TryGetValue(t, out descriptor))
                throw new ArgumentException("Type `" + t.Name + "` was not found in game library!", "T");

            bool f = false;
            for(int i = 0; i < descriptor.DebugWriters.Count; i++)
            {
                var p = descriptor.DebugWriters[i];
                if(p.Name.Equals(parameterName, StringComparison.OrdinalIgnoreCase))
                {
                    f = true;
                    descriptor.DebugWriters[i] = new Tools._Internal.TypeDebugWriter(parameterName, writerFunc);
                }
            }

            if(!f)
            {
                descriptor.DebugWriters.Add(new Tools._Internal.TypeDebugWriter(parameterName, writerFunc));
                if (descriptor.DebugWriters.Count == 1)
                    this.Types.TypesWithDebugWriters.Add(descriptor);
            }
        }

        #endregion
    }

    #region TypeCache class

    /// <summary>
    /// The registered type cache for library.
    /// </summary>
    internal sealed class TypeCache
    {
        /// <summary>
        /// The registered types by name.
        /// </summary>
        internal readonly Dictionary<string, TypeDescriptor> TypesByName = new Dictionary<string, TypeDescriptor>();

        /// <summary>
        /// The registered types by interface.
        /// </summary>
        internal readonly Dictionary<Type, TypeDescriptor> TypesByInterface = new Dictionary<Type, TypeDescriptor>();

        /// <summary>
        /// The registered types by implementation.
        /// </summary>
        internal readonly Dictionary<Type, TypeDescriptor> TypesByImplementation = new Dictionary<Type, TypeDescriptor>();

        /// <summary>
        /// The types with debug writers list.
        /// </summary>
        internal readonly List<TypeDescriptor> TypesWithDebugWriters = new List<TypeDescriptor>();
    }

    #endregion

    #region TypeDescriptor class

    /// <summary>
    /// Implement registered type info.
    /// </summary>
    internal sealed class TypeDescriptor
    {
        /// <summary>
        /// The name of type.
        /// </summary>
        internal string Name;

        /// <summary>
        /// The interface type.
        /// </summary>
        internal Type InterfaceType;

        /// <summary>
        /// The implementation (internal) type.
        /// </summary>
        internal Type ImplementationType;

        /// <summary>
        /// The full size of type.
        /// </summary>
        internal int Size;

        /// <summary>
        /// The RTTI descriptor address. This is null if unknown and empty if not available.
        /// </summary>
        internal uint[] RTTI;

        /// <summary>
        /// The module base address where this type is in.
        /// </summary>
        internal IntPtr Module;

        /// <summary>
        /// The constructor for implementation.
        /// </summary>
        internal ConstructorInfo ConstructorNonGeneric;

        /// <summary>
        /// The constructor for implementation.
        /// </summary>
        private Dictionary<string, ConstructorInfo> ConstructorGeneric = new Dictionary<string, ConstructorInfo>();

        /// <summary>
        /// Is type generic.
        /// </summary>
        internal bool IsGeneric;

        /// <summary>
        /// The debug writers list.
        /// </summary>
        internal readonly List<Tools._Internal.TypeDebugWriter> DebugWriters = new List<Tools._Internal.TypeDebugWriter>();
        
        /// <summary>
        /// The generic constructor locker.
        /// </summary>
        private readonly object GenLocker = new object();

        /// <summary>
        /// Gets the generic constructor for specified type arguments.
        /// </summary>
        /// <param name="args">The arguments.</param>
        /// <returns></returns>
        internal ConstructorInfo GetGenericConstructor(Type[] args)
        {
            if (!this.IsGeneric)
                throw new InvalidOperationException();

            StringBuilder str = new StringBuilder();
            str.Append('<');
            for (int i = 0; i < args.Length; i++)
            {
                if (i > 0)
                    str.Append(",");
                str.Append(args[i].Name);
            }
            str.Append('>');

            string key = str.ToString();
            lock (this.GenLocker)
            {
                ConstructorInfo ci = null;
                if (this.ConstructorGeneric.TryGetValue(key, out ci))
                    return ci;

                var tgen = this.ImplementationType.MakeGenericType(args);
                var cis = tgen.GetConstructors(BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance);
                foreach (var c in cis)
                {
                    if (!c.IsStatic && c.GetParameters().Length == 0)
                    {
                        ci = c;
                        break;
                    }
                }

                this.ConstructorGeneric[key] = ci;
                return ci;
            }
        }
    }

    #endregion
}

namespace NetScriptFramework.Tools._Internal
{
    #region TypeDebugWriter class

    /// <summary>
    /// Information on what to write about a type when debugging.
    /// </summary>
    public sealed class TypeDebugWriter
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="TypeDebugWriter"/> class.
        /// </summary>
        /// <param name="paramName">Name of the parameter.</param>
        /// <param name="writeFunc">The write function.</param>
        public TypeDebugWriter(string paramName, Func<IVirtualObject, string> writeFunc)
        {
            this.Name = paramName;
            this.Func = writeFunc;
        }

        /// <summary>
        /// The name.
        /// </summary>
        internal readonly string Name;

        /// <summary>
        /// The function.
        /// </summary>
        internal readonly Func<IVirtualObject, string> Func;
    }

    #endregion
}
