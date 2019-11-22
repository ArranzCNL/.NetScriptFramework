using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetScriptFramework
{
    #region Plugin class

    /// <summary>
    /// Implement base plugin class. All loaded plugins must inherit from this and provide plugin header information.
    /// </summary>
    public abstract class Plugin
    {
        #region Constructors

        /// <summary>
        /// Initializes a new instance of the <see cref="Plugin"/> class. Don't put any initialization code in constructor! If you
        /// need to initialize your plugin then override the Initialize method instead.
        /// </summary>
        public Plugin()
        {
            if (System.Threading.Interlocked.Exchange(ref PluginManager.CreatingPlugin, 0) != 1)
                throw new InvalidOperationException("Plugin's can not be manually created! Only PluginManager will create the plugins.");
        }

        #endregion

        #region Plugin members

        /// <summary>
        /// Gets the unique keyword of plugin.<para></para><para></para>For developers: Other plugins may query plugin
        /// manager for your plugin using this keyword. This is not case sensitive! It is advisable to keep this short
        /// and simple phrase but unique enough that other plugin authors would not choose it.
        /// </summary>
        /// <value>
        /// The unique key of plugin.
        /// </value>
        public abstract string Key
        {
            get;
        }

        /// <summary>
        /// Gets the name of plugin.<para></para><para></para>For developers: This is what will be shown to user and in
        /// the log files. This does not have to be unique but it should be informative enough to let user know what mod
        /// this is from.
        /// </summary>
        /// <value>
        /// The name of plugin.
        /// </value>
        public abstract string Name
        {
            get;
        }

        /// <summary>
        /// Gets the version of plugin.<para></para><para></para>For developers: Current version of your plugin. It is
        /// advisable to start with "1" and increment as your plugin's version is increased. You can also use a custom
        /// versioning scheme as long as it fits in the integer. You should at least make your scheme comparable, so that
        /// new version number is always greater than older version when sorted or compared.
        /// </summary>
        /// <value>
        /// The version.
        /// </value>
        public abstract int Version
        {
            get;
        }

        /// <summary>
        /// Gets the author's name of plugin.<para></para><para></para>For developers: Set author's name or nickname here.
        /// It is optional, the default value will return "Unknown" if not overrided.
        /// </summary>
        /// <value>
        /// The author.
        /// </value>
        public virtual string Author
        {
            get
            {
                return "Unknown";
            }
        }

        /// <summary>
        /// Gets the website of plugin.<para></para><para></para>For developers: Set website of your plugin here. This is where
        /// users could check for newer versions or get support in case of issues. It is optional and the default value will return
        /// empty string if not overrided.
        /// </summary>
        /// <value>
        /// The website of plugin.
        /// </value>
        public virtual string Website
        {
            get
            {
                return string.Empty;
            }
        }

        /// <summary>
        /// Gets a value indicating whether Initialize has been called successfully on this plugin instance.
        /// </summary>
        /// <value>
        /// <c>true</c> if this instance is initialized; otherwise, <c>false</c>.
        /// </value>
        public bool IsInitialized
        {
            get;
            private set;
        } = false;

        /// <summary>
        /// Gets the assembly associated with this plugin. This is the assembly where the plugin type header was found.
        /// </summary>
        /// <value>
        /// The assembly.
        /// </value>
        public System.Reflection.Assembly Assembly
        {
            get;
            internal set;
        }

        internal bool _initialize(bool loadedAny)
        {
            if(this.Initialize(loadedAny))
            {
                this.IsInitialized = true;
                return true;
            }

            return false;
        }

        /// <summary>
        /// Initializes the plugin instance. Perform your plugin initialization here. If you return false then
        /// you will let plugin manager know that other plugins should be initialized first. The plugin manager will
        /// return to your plugin (and any others that returned false this pass) in the next pass. If no plugins were
        /// loaded in a pass then the argument "loadedAny" will be false. If all plugins in a pass still return false
        /// then the plugin manager will fail to load and an error will be displayed to user, forcing the game to exit.
        /// If you don't need to perform any initialization for your plugin then you can skip overriding this method
        /// or simply return <c>true</c>. Plugins are initialized before static initialization occurs in the application!
        /// </summary>
        /// <param name="loadedAny">If set to <c>true</c> then we did load at least one plugin last pass. It is safe
        /// to return false now and try again next pass. If this is set to <c>false</c> then all plugins in the last pass
        /// also returned false and if that happens again the game will close with an error.</param>
        /// <returns></returns>
        protected virtual bool Initialize(bool loadedAny)
        {
            return true;
        }

        internal void _shutdown()
        {
            if (this.IsInitialized)
                this.Shutdown();
        }

        /// <summary>
        /// Shutdowns this plugin instance. Perform any cleanup you need to do here. At this point the application is
        /// about to exit, it is not necessary to release resources unless you have pending buffers. It is also not
        /// necessary to close log files inheriting from <see cref="NetScriptFramework.Tools.LogFile"/> as this is
        /// done automatically a little while later. This method is not guaranteed to be called in every scenario!
        /// If the application crashes or doesn't have a exit hook in place then this method will not be called.
        /// This method is also not called if the initialization of plugin has not completed successfully.
        /// </summary>
        protected virtual void Shutdown()
        {

        }

        /// <summary>
        /// Called when detaching from thread. This is used mostly only to clean up stuff from memory if you used thread-local storage.
        /// </summary>
        protected virtual void OnDetachThread()
        {

        }

        /*/// <summary>
        /// Called when attaching to thread.
        /// </summary>
        protected virtual void OnAttachThread()
        {

        }*/

        internal void _onAttachThread()
        {
            //this.OnAttachThread();
        }

        internal void _onDetachThread()
        {
            this.OnDetachThread();
        }

        /*/// <summary>
        /// Gets the value stored in current thread's thread-local storage for this plugin.
        /// </summary>
        /// <returns></returns>
        public IntPtr GetTLSValue()
        {
            using (var mem = Memory.Allocate(0x10))
            {
                Memory.WritePointer(mem.Address, IntPtr.Zero);
                if (!Memory.GetInternalTLS(this.InternalIndex, mem.Address))
                    throw new InvalidOperationException("Failed to read TLS for plugin " + this.ToString() + ", internal index was " + this.InternalIndex + "!");
                return Memory.ReadPointer(mem.Address);
            }
        }

        /// <summary>
        /// Sets the value stored in current thread's thread-local storage for this plugin.
        /// </summary>
        /// <param name="value">The value to set.</param>
        public void SetTLSValue(IntPtr value)
        {
            if(!Memory.SetInternalTLS(this.InternalIndex, value))
                throw new InvalidOperationException("Failed to write TLS for plugin " + this.ToString() + ", internal index was " + this.InternalIndex + "!");
        }*/

        #endregion

        #region Internal members

        /// <summary>
        /// Gets the internal string to display in log about the plugin.
        /// </summary>
        /// <returns></returns>
        internal string GetInternalString()
        {
            try
            {
                string name = this.InternalName;
                string key = this.InternalKey ?? string.Empty;
                int version = this.InternalVersion;
                return "\"" + name + "\" [" + key + "] (" + version + ")";
            }
            catch
            {
                return "ERROR<" + this.GetType().Name + ">";
            }
        }

        /// <summary>
        /// Gets the name of plugin for internal use.
        /// </summary>
        internal string InternalName
        {
            get
            {
                if (!_in)
                {
                    _in = true;
                    this._internalName = this.Name ?? string.Empty;
                }
                return this._internalName;
            }
        }
        private string _internalName = null;
        private bool _in = false;

        /// <summary>
        /// Gets the version of plugin for internal use.
        /// </summary>
        internal int InternalVersion
        {
            get
            {
                if(!_iv)
                {
                    _iv = true;
                    this._internalVersion = this.Version;
                }
                return this._internalVersion;
            }
        }
        private int _internalVersion = 0;
        private bool _iv = false;

        /// <summary>
        /// Gets the key of plugin for internal use.
        /// </summary>
        internal string InternalKey
        {
            get
            {
                if (!_ik)
                {
                    _ik = true;
                    this._internalKey = this.Key;
                }
                return this._internalKey;
            }
        }
        private string _internalKey = null;
        private bool _ik = false;

        /// <summary>
        /// Gets or sets the internal plugin index.
        /// </summary>
        /// <value>
        /// The internal index of plugin.
        /// </value>
        internal int InternalIndex
        {
            get;
            set;
        }
        
        #endregion
    }

    #endregion
}
