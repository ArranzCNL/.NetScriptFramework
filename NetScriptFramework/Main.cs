using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace NetScriptFramework
{
    #region Main class

    /// <summary>
    /// Implement framework runtime methods. This will deal with initialization and shutdown.
    /// </summary>
    public static class Main
    {
        #region Constructors

        #endregion

        #region Main members

        /// <summary>
        /// The name of running framework.
        /// </summary>
        public static readonly string FrameworkName = "NetScriptFramework";

        /// <summary>
        /// The version of running framework.
        /// </summary>
        public static readonly int FrameworkVersion = 7;

        /// <summary>
        /// The required runtime version.
        /// </summary>
        private static readonly int RequiredRuntimeVersion = 4;

        /// <summary>
        /// Gets the framework assembly.
        /// </summary>
        internal static System.Reflection.Assembly FrameworkAssembly
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the currently loaded game library information. If no valid game library is found this will be null, plugins may
        /// still be loaded into an unknown game process.
        /// </summary>
        /// <value>
        /// The game information or null.
        /// </value>
        public static Game Game
        {
            get;
            private set;
        }
        
        /// <summary>
        /// Gets a value indicating whether this process is currently running in 64 bit mode.
        /// </summary>
        /// <value>
        ///   <c>true</c> if this is 64 bit process; otherwise, <c>false</c>.
        /// </value>
        public static bool Is64Bit
        {
            get
            {
                int result = EnvironmentType;
                if(result == 0)
                {
                    result = IntPtr.Size == 4 ? -1 : 1;
                    EnvironmentType = result;
                }
                return result > 0;
            }
        }

        /// <summary>
        /// Gets the main framework configuration file.
        /// </summary>
        /// <value>
        /// The main framework configuration.
        /// </value>
        public static Tools.ConfigFile Config
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets the main framework log file.
        /// </summary>
        /// <value>
        /// The main framework log.
        /// </value>
        public static Tools.LogFile Log
        {
            get;
            private set;
        }

        /// <summary>
        /// Gets a pointer to a valid memory region, usable for any purpose. Size is 1 KB. Not thread safe!
        /// </summary>
        /// <value>
        /// The trash memory.
        /// </value>
        public static IntPtr TrashMemory
        {
            get;
            private set;
        }

        /// <summary>
        /// Stops the application, displays an error message box and exits after user has clicked Ok.
        /// </summary>
        /// <param name="e">The exception to display.</param>
        /// <param name="kill">Should we kill the process or exit normally.</param>
        public static void CriticalException(Exception e, bool kill)
        {
            StringBuilder message = new StringBuilder();
            message.AppendLine("A critical or unhandled managed exception has occurred!");
            if (e != null)
            {
                message.AppendLine();
                var lines = Tools.LogFile.GetExceptionText(e);
                foreach (var x in lines)
                    message.AppendLine(x);
            }
            
            CriticalException(message.ToString(), kill);
        }

        /// <summary>
        /// Stops the application, displays an error message box and exits after user has clicked Ok.
        /// </summary>
        /// <param name="message">The message to display.</param>
        /// <param name="kill">Should we kill the process or exit normally.</param>
        public static void CriticalException(string message, bool kill)
        {
            if(Log != null)
            {
                string[] spl = message.Replace("\r\n", "\n").Replace("\r", "\n").Split(new[] { "\n" }, StringSplitOptions.None);
                foreach (var x in spl)
                    Log.AppendLine(x);
            }

            Tools._Internal.RTHandler.SuspendAllThreadsInCurrentProcess();

            System.Windows.Forms.MessageBox.Show(message, "Error", System.Windows.Forms.MessageBoxButtons.OK, System.Windows.Forms.MessageBoxIcon.Error);

            Tools._Internal.RTHandler.ExitProcess(!kill);
        }

        internal static void _CriticalException_NoLog(string message, bool kill)
        {
            Tools._Internal.RTHandler.SuspendAllThreadsInCurrentProcess();

            System.Windows.Forms.MessageBox.Show(message, "Error", System.Windows.Forms.MessageBoxButtons.OK, System.Windows.Forms.MessageBoxIcon.Error);

            Tools._Internal.RTHandler.ExitProcess(!kill);
        }

        /// <summary>
        /// Generates a unique identifier.
        /// </summary>
        /// <returns></returns>
        public static long GenerateGuid()
        {
            return IDGenerator.Generate();
        }

        /// <summary>
        /// Gets the runtime version.
        /// </summary>
        /// <returns></returns>
        [System.Runtime.InteropServices.DllImport("NetScriptFramework.Runtime.dll")]
        private static extern int GetRuntimeVersion();
        
        /// <summary>
        /// Initializes the framework.
        /// </summary>
        internal static string Initialize()
        {
            try
            {
                // Make sure state is correct.
                if (Interlocked.CompareExchange(ref Status, 1, 0) != 0)
                    throw new InvalidOperationException("Trying to initialize the framework more than once!");

                if (GetRuntimeVersion() < RequiredRuntimeVersion)
                    throw new InvalidOperationException("The runtime DLL version is too old! Make sure NetScriptFramework.Runtime.dll is updated.");

                // This is needed later so we can cache this call.
                FrameworkAssembly = System.Reflection.Assembly.GetExecutingAssembly();

                // Initialize ID generator.
                IDGenerator = new Tools.UIDGenerator();

                // Allocate trash memory.
                {
                    var alloc = Memory.Allocate(1024);
                    alloc.Pin();
                    TrashMemory = alloc.Address;
                }

                // Prepare and load configuration file.
                bool loadedConfiguration = PrepareAndLoadConfiguration();

                // Initialize log file.
                InitializeLog();

                // Setup managed unhandled exception filter.
                AppDomain.CurrentDomain.UnhandledException += CurrentDomain_UnhandledException;

                // Setup exit handler.
                AppDomain.CurrentDomain.ProcessExit += CurrentDomain_ProcessExit;

                // Write startup info.
                Log.AppendLine("Initializing framework version " + FrameworkVersion + ".");
                if (!loadedConfiguration)
                    Log.AppendLine("Warning: failed to load configuration file! Attempting to create a new default one.");
                else
                    Log.AppendLine("Loaded configuration file.");

                // Prepare code for .NET hooking.
                Memory.PrepareNETHook();

                // Initialize assembly loader for plugin loading.
                Loader.Initialize();

                // Prepare game info before loading plugins.
                LoadGameInfo();

                // Load plugins.
                PluginManager.Initialize();

                // Write startup info.
                Log.AppendLine("Finished framework initialization.");
            }
            catch(Exception ex)
            {
                if (Log != null)
                    Log.Append(ex);

                return ex.GetType().Name + "(" + (ex.Message ?? string.Empty) + ")";
            }

            return null;
        }

        /// <summary>
        /// Gets a value indicating whether this instance is shutdown.
        /// </summary>
        /// <value>
        /// <c>true</c> if this instance is shutdown; otherwise, <c>false</c>.
        /// </value>
        public static bool IsShutdown
        {
            get
            {
                return Interlocked.CompareExchange(ref Status, 0, 0) == 2;
            }
        }

        /// <summary>
        /// Shuts the framework down.
        /// </summary>
        internal static void Shutdown()
        {
            // Make sure state is correct but don't throw because it is theoretically possible to shut down framework before initialize.
            if (Interlocked.CompareExchange(ref Status, 2, 1) != 1)
                return;

            // Write info to log.
            Log.AppendLine("Shutting down framework.");

            // Shutdown plugins.
            PluginManager.Shutdown();

            // Write info to log.
            Log.AppendLine("Shutdown complete.");

            // Close all log files last.
            Tools.LogFile.CloseAll();
        }

        /// <summary>
        /// Handles the ProcessExit event of the CurrentDomain control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="EventArgs"/> instance containing the event data.</param>
        private static void CurrentDomain_ProcessExit(object sender, EventArgs e)
        {
            Shutdown();
        }

        /// <summary>
        /// Called when detached thread.
        /// </summary>
        private static void OnDetachThread()
        {
            PluginManager.DetachThread();
        }

        /// <summary>
        /// Called when attached thread.
        /// </summary>
        private static void OnAttachThread()
        {
            PluginManager.AttachThread();
        }

        /// <summary>
        /// Handles the UnhandledException event of the CurrentDomain control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="UnhandledExceptionEventArgs"/> instance containing the event data.</param>
        private static void CurrentDomain_UnhandledException(object sender, UnhandledExceptionEventArgs e)
        {
            ProcessManagedUnhandledException(e.ExceptionObject as Exception);
        }

        /// <summary>
        /// Processes the managed unhandled exception.
        /// </summary>
        /// <param name="ex">The exception object.</param>
        internal static void ProcessManagedUnhandledException(Exception ex)
        {
            if (ex != null)
            {
                try
                {
                    var cl = new ManagedCrashLog(ex);
                    cl.Write();
                }
                catch(Exception ex2)
                {
                    Log.Append(ex2);
                }
            }

            CriticalException(ex, true);
        }

        /// <summary>
        /// Unhandled exception filter.
        /// </summary>
        /// <param name="cpu">The cpu context.</param>
        /// <returns></returns>
        internal static bool UnhandledExceptionFilter(CPURegisters cpu)
        {
            int handled = 0;
            string logmsg = "Unhandled native exception occurred at " + cpu.IP.ToHexString() + CrashLog.GetAddressInModule(cpu.IP, System.Diagnostics.Process.GetCurrentProcess().Modules, " ") + " on thread " + Memory.GetCurrentNativeThreadId() + "!";

            try
            {
                var cl = new NativeCrashLog(cpu);
                handled = cl.Write(true);

                if (cl.Skipped)
                    logmsg = null;
            }
            catch(Exception ex2)
            {
                Main.Log.Append(ex2);
            }

            if (logmsg != null)
                Log.AppendLine(logmsg);

            return handled > 0;
        }

        /// <summary>
        /// Writes the native crash log for specified context. It does not actually treat this as a crash, it just writes out to file as if this was a crash.
        /// Warning: plugins may still treat this as a crash and modify registers or perform functions that would happen on crash!
        /// </summary>
        /// <param name="cpu">The cpu context.</param>
        /// <param name="nativeThreadId">The native thread identifier. Set int.MinValue for current thread.</param>
        /// <param name="filePath">The file path to write to (including file name). If file exists it will append.</param>
        /// <exception cref="System.ArgumentNullException">cpu</exception>
        public static bool WriteNativeCrashLog(CPURegisters cpu, int nativeThreadId, string filePath)
        {
            if (cpu == null)
                throw new ArgumentNullException("cpu");

            if (string.IsNullOrEmpty(filePath))
                throw new ArgumentOutOfRangeException("filePath");

            if (nativeThreadId == int.MinValue)
                nativeThreadId = Memory.GetCurrentNativeThreadId();

            int handled = 0;
            try
            {
                var cl = new NativeCrashLog(cpu);
                handled = cl.Write(true, filePath, true);
            }
            catch (Exception ex2)
            {
                Main.Log.Append(ex2);
            }
            return handled > 0;
        }

        /// <summary>
        /// Gets a value indicating whether plugins are being initialized right now.
        /// </summary>
        /// <value>
        /// <c>true</c> if plugins are initializing; otherwise, <c>false</c>.
        /// </value>
        public static bool IsInitializing
        {
            get
            {
                return _is_initializing_plugin > 0;
            }
        }

        /// <summary>
        /// Gets or sets the internal value of plugin initialize state.
        /// </summary>
        internal static int _is_initializing_plugin
        {
            get;
            set;
        } = 0;

        /// <summary>
        /// Gets the main targeted module.
        /// </summary>
        /// <returns></returns>
        /// <exception cref="System.IO.FileNotFoundException">Main targeted module was not found in process!</exception>
        public static System.Diagnostics.ProcessModule GetMainTargetedModule()
        {
            var proc = System.Diagnostics.Process.GetCurrentProcess();
            if (Game == null)
                return proc.MainModule;

            string want = Game.ModuleName ?? string.Empty;
            if (want.Length == 0)
                return proc.MainModule;

            var modules = proc.Modules;
            foreach(System.Diagnostics.ProcessModule m in modules)
            {
                if (!want.Equals(m.ModuleName, StringComparison.OrdinalIgnoreCase))
                    continue;

                return m;
            }

            throw new FileNotFoundException("Main targeted module was not found in process!");
        }
        
        #endregion

        #region Internal members

        /// <summary>
        /// The status of framework.
        /// </summary>
        private static int Status = 0;

        /// <summary>
        /// The environment type.
        /// </summary>
        private static int EnvironmentType = 0;

        /// <summary>
        /// Value saying whether game info creation is allowed now.
        /// </summary>
        internal static int GameCreate = 0;

        /// <summary>
        /// The identifier generator.
        /// </summary>
        private static Tools.UIDGenerator IDGenerator = null;

        /// <summary>
        /// Initializes the log file.
        /// </summary>
        private static void InitializeLog()
        {
            Log = new Tools.LogFile();
        }

        /// <summary>
        /// Prepares the configuration instance. This doesn't load from file automatically!
        /// </summary>
        private static void PrepareConfiguration()
        {
            Config = new Tools.ConfigFile();
            Config.AddSetting(Main._Config_Plugin_Path, System.IO.Path.Combine(Config.Path, "Plugins"), "Path to plugins", "Relative or absolute path to plugin files.");
            Config.AddSetting(Main._Config_Plugin_Lib_Path, System.IO.Path.Combine(Config.Path, "Plugins", "Lib"), "Path to plugin libraries", "Relative or absolute path to plugin dependency libraries. You can place any additional DLL files your plugin requires here. These DLL files will not attempt to automatically load as plugins, you can also use DllImport attribute and it will search for the DLL's in this path. Any .NET libraries referenced by your plugin project will also search for them here.");
            Config.AddSetting(Main._Config_Debug_CrashLog_Enabled, new Tools.Value((int)1), "Enable crash logs", "Enable writing crash logs when the game crashes.");
            Config.AddSetting(Main._Config_Debug_CrashLog_Path, System.IO.Path.Combine(Config.Path, "Crash"), "Path to crash logs", "The path where to write crash logs if enabled.");
            Config.AddSetting(Main._Config_Debug_CrashLog_Append, new Tools.Value((int)0), "Append crash logs", "Append all crash logs to same file or create a separate file for each crash.");
            Config.AddSetting(Main._Config_Debug_CrashLog_StackCount, new Tools.Value((int)512), "Stack count", "How many values to print from stack.");
            Config.AddSetting(Main._Config_Debug_CrashLog_Modules, new Tools.Value(true), "Modules", "Write loaded modules of process to crash log?");
        }

        /// <summary>
        /// Loads the game information.
        /// </summary>
        private static void LoadGameInfo()
        {
            Main.Log.AppendLine("Loading game library.");
            List<FileInfo> found = new List<FileInfo>();
            DirectoryInfo dir = new DirectoryInfo("Data\\NetScriptFramework");
            var files = dir.GetFiles();
            foreach(var x in files)
            {
                string fileName = x.Name;
                if (!fileName.EndsWith(".dll", StringComparison.OrdinalIgnoreCase) || !fileName.StartsWith(Main.FrameworkName + ".", StringComparison.OrdinalIgnoreCase) || fileName.Equals(Main.FrameworkName + ".dll", StringComparison.OrdinalIgnoreCase))
                    continue;

                fileName = fileName.Substring(Main.FrameworkName.Length + 1);
                fileName = fileName.Substring(0, fileName.Length - 4);

                if (fileName.Length == 0 || fileName.Equals("Runtime", StringComparison.OrdinalIgnoreCase))
                    continue;

                found.Add(x);
            }

            if(found.Count == 0)
            {
                Main.Log.AppendLine("No game library found! Game definitions will not be loaded but plugins may still load.");
                return;
            }

            if(found.Count > 1)
            {
                string fstr = string.Join(", ", found.Select(q => q.Name));
                throw new InvalidOperationException("Found more than one game library DLL! Only one game library may be active at a time. [" + fstr + "]");
            }

            {
                var debugFile = found[0];
                string debugFileName = debugFile.Name;
                int ptIdx = debugFileName.LastIndexOf('.');
                if (ptIdx >= 0)
                {
                    debugFileName = debugFileName.Substring(0, ptIdx) + ".bin";
                    debugFile = new FileInfo(System.IO.Path.Combine(debugFile.DirectoryName, debugFileName));
                    CrashLog._FileForDebugInfo = debugFile;
                    CrashLog.InitializeDebug();
                }
            }

            System.Reflection.Assembly assembly = null;
            Loader.Load(found[0], ref assembly);
            if (assembly == null)
                throw new InvalidOperationException();

            var types = assembly.GetTypes();
            Type valid = null;
            foreach(var t in types)
            {
                if (!t.IsSubclassOf(typeof(Game)))
                    continue;

                if (t.IsAbstract)
                    continue;

                if (t.BaseType != typeof(Game))
                    continue;

                if (valid != null)
                    throw new InvalidOperationException("Found more than one valid game header type!");

                valid = t;
            }

            if (valid == null)
                throw new InvalidOperationException("Found game library but no valid game header type!");

            GameCreate = 1;
            Main._is_initializing_plugin += 2;
            try
            {
                Game result = (Game)Activator.CreateInstance(valid);
                string print = "`" + result.FullName + "` (" + result.LibraryVersion + ")";
                Main.Log.AppendLine("Loaded game library for " + print + ".");
                Main.Log.AppendLine("Running game version is " + string.Join(".", result.GameVersion));
                string supportedExecutable = result.ExecutableName;
                string haveExecutable = System.Diagnostics.Process.GetCurrentProcess().MainModule.ModuleName;
                if (!haveExecutable.Equals(supportedExecutable, StringComparison.OrdinalIgnoreCase))
                    throw new InvalidOperationException("Game library " + print + " expected game executable `" + supportedExecutable + "` but have `" + haveExecutable + "`!");
                if (!result.IsValidVersion)
                    throw new InvalidOperationException("Game library " + print + " does not support game version " + string.Join(".", result.GameVersion) + "!");
                Main.Game = result;
                result._initialize();
            }
            finally
            {
                Main._is_initializing_plugin -= 2;
            }
        }

        #region Setting names

        /// <summary>
        /// The plugin files path.
        /// </summary>
        internal const string _Config_Plugin_Path = "Plugin.Path";

        /// <summary>
        /// The plugin depdency files path.
        /// </summary>
        internal const string _Config_Plugin_Lib_Path = "Plugin.LibPath";

        /// <summary>
        /// Value saying whether to write crash log or not.
        /// </summary>
        internal const string _Config_Debug_CrashLog_Enabled = "Debug.CrashLog.Enabled";

        /// <summary>
        /// The path where to write crash logs.
        /// </summary>
        internal const string _Config_Debug_CrashLog_Path = "Debug.CrashLog.Path";

        /// <summary>
        /// Value saying whether to append all crash logs to same file or create separate files.
        /// </summary>
        internal const string _Config_Debug_CrashLog_Append = "Debug.CrashLog.Append";

        /// <summary>
        /// How many values to print from stack.
        /// </summary>
        internal const string _Config_Debug_CrashLog_StackCount = "Debug.CrashLog.StackCount";

        /// <summary>
        /// Print modules or not.
        /// </summary>
        internal const string _Config_Debug_CrashLog_Modules = "Debug.CrashLog.Modules";

        #endregion

        /// <summary>
        /// Prepares and loads configuration file. If file failed to load it will attempt to create.
        /// </summary>
        /// <returns></returns>
        private static bool PrepareAndLoadConfiguration()
        {
            PrepareConfiguration();
            bool loadedConfiguration = false;
#if !DEBUG
            try
            {
#endif
                loadedConfiguration = Config.Load();
#if !DEBUG
            }
            catch
            {

            }
#endif
            if (!loadedConfiguration)
            {
#if !DEBUG
                try
                {
#endif
                    Config.Save();
#if !DEBUG
                }
                catch
                {

                }
#endif
            }

            return loadedConfiguration;
        }

        #endregion
    }

    #endregion
}
