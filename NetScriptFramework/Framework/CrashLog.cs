using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetScriptFramework
{
    /// <summary>
    /// Event arguments for a crash log event.
    /// </summary>
    /// <seealso cref="System.EventArgs" />
    public class CrashLogEventArgs : EventArgs
    {
        /// <summary>
        /// Gets the crash log instance.
        /// </summary>
        public CrashLog Log
        {
            get;
            internal set;
        }

        /// <summary>
        /// Gets the output. This is what will be written to file after all is finished.
        /// </summary>
        public StringBuilder Output
        {
            get;
            internal set;
        }

        /// <summary>
        /// Gets or sets a value indicating whether crash log should skip writing to file. If this is set to true
        /// then the file will not be written.
        /// </summary>
        public bool Skip
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets a value indicating whether the crash is handled and game should try to continue executing. Default
        /// is false meaning the game will close after writing the crash log. This is only used for native exceptions.
        /// </summary>
        public bool Handled
        {
            get;
            set;
        }
    }

    /// <summary>
    /// This is used to generate a crash log.
    /// </summary>
    public abstract class CrashLog
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="CrashLog"/> class.
        /// </summary>
        internal CrashLog()
        {
        }

        /// <summary>
        /// Occurs before writing the crash log.
        /// </summary>
        public static readonly Event<CrashLogEventArgs> OnBeforeWrite = new Event<CrashLogEventArgs>("OnBeforeWrite");

        /// <summary>
        /// Occurs after writing the crash log.
        /// </summary>
        public static readonly Event<CrashLogEventArgs> OnAfterWrite = new Event<CrashLogEventArgs>("OnAfterWrite");
        
        /// <summary>
        /// The debug info.
        /// </summary>
        public static DebugInfo Debug
        {
            get;
            internal set;
        }

        /// <summary>
        /// The debug file error.
        /// </summary>
        private static string DebugFileError = null;

        /// <summary>
        /// The file for debug information. This is set just before loading game library.
        /// </summary>
        internal static System.IO.FileInfo _FileForDebugInfo = null;

        /// <summary>
        /// Gets the modules collection.
        /// </summary>
        public System.Diagnostics.ProcessModuleCollection Modules
        {
            get;
            internal set;
        }

        /// <summary>
        /// Gets the main module of process.
        /// </summary>
        public System.Diagnostics.ProcessModule MainModule
        {
            get;
            internal set;
        }
        
        /// <summary>
        /// The culture to use for formatting.
        /// </summary>
        public System.Globalization.CultureInfo Culture
        {
            get;
            internal set;
        }

        /// <summary>
        /// Are we starting on a new line right now?
        /// </summary>
        private bool IsNewLine = true;

        /// <summary>
        /// The tab count to write.
        /// </summary>
        internal protected int TabCount = 0;

        /// <summary>
        /// The tab character.
        /// </summary>
        internal protected string TabCharacter = "  ";

        /// <summary>
        /// The builder.
        /// </summary>
        private readonly StringBuilder Builder = new StringBuilder(65536);

        /// <summary>
        /// Gets a value indicating whether this <see cref="CrashLog"/> is skipped.
        /// </summary>
        /// <value>
        ///   <c>true</c> if skipped; otherwise, <c>false</c>.
        /// </value>
        internal bool Skipped
        {
            get;
            private set;
        }

        /// <summary>
        /// Begins the group.
        /// </summary>
        /// <param name="name">The name.</param>
        internal protected void BeginGroup(string name)
        {
            if(!string.IsNullOrEmpty(name))
                this.WriteLine(name);
            this.WriteLine("{");
            this.TabCount++;
        }

        /// <summary>
        /// Ends the group.
        /// </summary>
        internal protected void EndGroup()
        {
            this.TabCount--;
            this.WriteLine("}");
        }

        /// <summary>
        /// Writes the crash log to file.
        /// </summary>
        internal int Write(bool allowToFile = true, string overwritePath = null, bool forceAppend = false)
        {
            bool writeToFile = false;

            if (allowToFile && Main.Config != null)
            {
                var vl = Main.Config.GetValue(Main._Config_Debug_CrashLog_Enabled);
                int enabled = 0;
                if (vl == null || !vl.TryToInt32(out enabled) || enabled <= 0)
                {

                }
                else
                    writeToFile = true;
            }
            
            DateTime now = DateTime.Now;
            string dirPath = null;
            string filePath = null;
            string fileBase = null;
            bool append = false;
            int stackCount = 128;

            if(writeToFile)
            {
                var vl = Main.Config.GetValue(Main._Config_Debug_CrashLog_Path);
                if (vl == null || string.IsNullOrEmpty(dirPath = vl.ToString()))
                    dirPath = System.IO.Path.Combine(Main.Config.Path, "Crash");
            }

            if(writeToFile)
            {
                var vl = Main.Config.GetValue(Main._Config_Debug_CrashLog_Append);
                int r = 0;
                if (vl == null || !vl.TryToInt32(out r))
                    r = 0;
                append = r > 0;

                if (append)
                    fileBase = "Crash";
                else
                    fileBase = "Crash_" + now.Year + "_" + now.Month + "_" + now.Day + "_" + now.Hour + "-" + now.Minute + "-" + now.Second;
            }

            if(this is NativeCrashLog)
            {
                var vl = Main.Config.GetValue(Main._Config_Debug_CrashLog_StackCount);
                if (vl != null && !vl.TryToInt32(out stackCount))
                    stackCount = 128;

                if (stackCount < 4)
                    stackCount = 4;
            }

            System.IO.FileInfo file = null;

            if (forceAppend)
                append = true;

            if (writeToFile)
            {
                if (!string.IsNullOrEmpty(overwritePath))
                {
                    file = new System.IO.FileInfo(overwritePath);
                    if (!file.Directory.Exists)
                        file.Directory.Create();
                }
                else
                {
                    System.IO.DirectoryInfo dir = new System.IO.DirectoryInfo(dirPath);
                    if (!dir.Exists)
                        dir.Create();

                    int tries = 0;
                    while (tries++ < 30)
                    {
                        string ext = ".txt";
                        if (tries > 1)
                            ext = "(" + tries + ")" + ext;
                        filePath = System.IO.Path.Combine(dir.FullName, fileBase + ext);
                        file = new System.IO.FileInfo(filePath);

                        if (append || !file.Exists)
                            break;
                    }
                }

                if (!append && file.Exists)
                    throw new InvalidOperationException("File for crash log already exists!");
            }
            
            this.Initialize(stackCount);
            
            int handled = 0;
            var args = OnBeforeWrite.Raise(() => new CrashLogEventArgs() { Log = this, Output = this.Builder, Skip = false, Handled = handled > 0 });
            if (args != null)
            {
                handled = args.Handled ? 1 : -1;
                if (args.Skip)
                {
                    this.Skipped = true;
                    return handled;
                }
            }
            
            this.DoWrite(now, append);
            
            args = OnAfterWrite.Raise(() => new CrashLogEventArgs() { Log = this, Output = this.Builder, Skip = false, Handled = handled > 0 });
            if (args != null)
            {
                handled = args.Handled ? 1 : -1;
                if (args.Skip)
                {
                    this.Skipped = true;
                    return handled;
                }
            }

            if (writeToFile && file != null)
            {
                using (var stream = append ? file.AppendText() : file.CreateText())
                {
                    stream.Write(this.Builder.ToString());
                }
            }
            
            return handled;
        }

        /// <summary>
        /// Does the write.
        /// </summary>
        /// <param name="now"></param>
        /// <param name="append"></param>
        private void DoWrite(DateTime now, bool append)
        {
            if (this is NativeCrashLog)
            {
                if (this.WriteInfo())
                    this.WriteDelimiter(false);
                if (this.WriteHeader(now))
                    this.WriteDelimiter(false);
                if (this.WriteCallStack())
                    this.WriteDelimiter(false);
                if (this.WriteRegisters())
                    this.WriteDelimiter(false);
                if (this.WriteFullStack())
                    this.WriteDelimiter(false);
                if (this.WriteModules())
                    this.WriteDelimiter(false);
                if (this.WritePlugins())
                    this.WriteDelimiter(false);
                this.WriteExtraInfo();

                if (append)
                    this.WriteDelimiter(true);
            }
            else
            {
                if (this.WriteInfo())
                    this.WriteDelimiter(false);
                if (this.WriteHeader(now))
                    this.WriteDelimiter(false);

                ManagedCrashLog mc = (ManagedCrashLog)this;
                List<Exception> exs = new List<Exception>();
                var e = mc.OriginalException;
                while (e != null)
                {
                    exs.Add(e);
                    e = e.InnerException;
                }
                exs.Reverse();

                for (int i = 0; i < exs.Count; i++)
                {
                    mc.CurrentException = exs[i];

                    if (i > 0)
                        this.WriteLine();

                    string header = (i == exs.Count - 1) ? "Exception" : "Inner Exception";
                    header += " (" + mc.CurrentException.GetType().Name + "): ";
                    int hlen = Math.Min(header.Length, PageWidth / 2);
                    var spl = Tools.ConfigEntry.Wrap(mc.CurrentException.Message, PageWidth - hlen, hlen);
                    this.Write(header);
                    foreach (var x in spl)
                        this.WriteLine(x);

                    this.BeginGroup(null);
                    {
                        this.WriteCallStack();
                    }
                    this.EndGroup();
                }

                if (exs.Count != 0)
                    this.WriteDelimiter(false);

                if (this.WriteModules())
                    this.WriteDelimiter(false);

                if (this.WritePlugins())
                    this.WriteDelimiter(false);

                this.WriteExtraInfo();

                if (append)
                    this.WriteDelimiter(true);
            }
        }

        /// <summary>
        /// Initializes this instance for log writing.
        /// </summary>
        /// <param name="stackCount">Stack pointer count.</param>
        internal protected virtual void Initialize(int stackCount)
        {
            this.Culture = System.Globalization.CultureInfo.InvariantCulture;
            this.MainModule = System.Diagnostics.Process.GetCurrentProcess().MainModule;
            this.Modules = System.Diagnostics.Process.GetCurrentProcess().Modules;

            // Try to load debug info.
            if (this is NativeCrashLog)
            {
                // Initialize debug info.
                InitializeDebug();
            }
            else
                DebugFileError = "Not loaded for managed exceptions";
        }

        /// <summary>
        /// Initializes the debug info.
        /// </summary>
        internal static void InitializeDebug()
        {
            if (Debug == null)
            {
                if (_FileForDebugInfo != null && _FileForDebugInfo.Exists)
                {
                    try
                    {
                        Debug = new DebugInfo();
                        Debug.ReadFromFile(_FileForDebugInfo);
                    }
                    catch (Exception ex)
                    {
                        Debug = null;
                        DebugFileError = "Exception when loading (" + ex.GetType().Name + "): " + ex.Message;
                    }
                }
                else if (_FileForDebugInfo != null)
                    DebugFileError = "File not found";
                else
                    DebugFileError = "No info";
            }
        }

        /// <summary>
        /// Writes the line of text to log.
        /// </summary>
        /// <param name="line">The line.</param>
        internal protected void WriteLine(string line = "")
        {
            this.Write(line);
            this.Builder.Append("\r\n");
            this.IsNewLine = true;
        }

        /// <summary>
        /// Writes the specified text to log without a newline.
        /// </summary>
        /// <param name="text">The text.</param>
        internal protected void Write(string text)
        {
            if (string.IsNullOrEmpty(text))
                return;

            text = text.Replace("\r\n", "\n").Replace("\r", "\n");
            if(!text.Contains('\n'))
            {
                if (text.Length == 0)
                    return;

                if(this.IsNewLine)
                {
                    for (int i = 0; i < this.TabCount; i++)
                        this.Builder.Append(this.TabCharacter);

                    this.IsNewLine = false;
                }

                this.Builder.Append(text);
                return;
            }

            var spl = text.Split(new[] { '\n' }, StringSplitOptions.None);
            if (spl.Length == 0)
                return;

            for (int i = 0; i < spl.Length - 1; i++)
                this.WriteLine(spl[i]);
            
            text = spl[spl.Length - 1];
            this.Write(text);
        }

        /// <summary>
        /// Gets the average maximum expected width of the line in log.
        /// </summary>
        /// <value>
        /// The width of the page.
        /// </value>
        internal protected virtual int PageWidth
        {
            get
            {
                return 140;
            }
        }

        /// <summary>
        /// Writes the delimiter to log.
        /// </summary>
        /// <param name="file">if set to <c>true</c> then delimit with another log, otherwise delimit section.</param>
        internal protected virtual void WriteDelimiter(bool file)
        {
            if (file)
            {
                this.WriteLine();
                this.WriteLine(new string('=', PageWidth));
                this.WriteLine();
            }
            else
                this.WriteLine();
        }

        /// <summary>
        /// Writes the information line of crash. This is the same line that goes to main log.
        /// </summary>
        /// <returns></returns>
        internal protected abstract bool WriteInfo();

        /// <summary>
        /// Writes the header information.
        /// </summary>
        /// <param name="now">Time of crash.</param>
        /// <returns></returns>
        internal protected virtual bool WriteHeader(DateTime now)
        {
            this.WriteLine("FrameworkName: " + Main.FrameworkName);
            this.WriteLine("FrameworkVersion: " + Main.FrameworkVersion);
            this.WriteLine("FrameworkArchitecture: " + (Main.Is64Bit ? "x64" : "x32"));
            this.WriteLine("GameLibrary: " + (Main.Game != null ? Main.Game.ShortName : "(null)"));
            this.WriteLine("GameLibraryVersion: " + (Main.Game != null ? Main.Game.LibraryVersion.ToString(this.Culture) : "-1"));
            {
                this.WriteLine("ApplicationName: " + System.IO.Path.GetFileName(this.MainModule.FileName));
                var appVer = Memory.GetMainModuleVersion();
                this.WriteLine("ApplicationVersion: " + appVer[0].ToString(this.Culture) + "." + appVer[1].ToString(this.Culture) + "." + appVer[2].ToString(this.Culture) + "." + appVer[3].ToString(this.Culture));

                if (Debug != null && (Debug.FileVersion[0] != appVer[0] || Debug.FileVersion[1] != appVer[1] || Debug.FileVersion[2] != appVer[2] || Debug.FileVersion[3] != appVer[3]))
                {
                    Debug = null;
                    DebugFileError = "Version mismatch";
                }
            }
            {
                if (Debug != null)
                    this.WriteLine("DebugInfo: Successfully loaded");
                else if (!string.IsNullOrEmpty(DebugFileError))
                    this.WriteLine("DebugInfo: " + DebugFileError);
                else
                    this.WriteLine("DebugInfo: Unknown error");
            }
            this.WriteLine("Time: " + Tools.DateTimeStringConverter.ToLogTimestampString(now));
            return true;
        }

        /// <summary>
        /// Writes the call stack.
        /// </summary>
        /// <returns></returns>
        internal protected abstract bool WriteCallStack();

        /// <summary>
        /// Writes the registers. This is only valid for native exception.
        /// </summary>
        /// <returns></returns>
        internal protected virtual bool WriteRegisters()
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Writes the full stack. This is only valid for native exception.
        /// </summary>
        /// <returns></returns>
        internal protected virtual bool WriteFullStack()
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Writes the modules list.
        /// </summary>
        /// <returns></returns>
        internal protected virtual bool WriteModules()
        {
            var vl = Main.Config.GetValue(Main._Config_Debug_CrashLog_Modules);
            bool inc = true;
            if (vl != null && vl.TryToBoolean(out inc) && !inc)
                return false;

            this.BeginGroup("Modules");
            {
                for (int i = 0; i < this.Modules.Count; i++)
                {
                    var m = this.Modules[i];

                    string mn = m.ModuleName ?? "UnknownModule";
                    mn += ":";
                    if (mn.Length < 50)
                        mn += new string(' ', 50 - mn.Length);

                    this.Write(mn);
                    this.WriteLine(m.BaseAddress.ToHexString());
                }
            }
            this.EndGroup();
            return true;
        }

        /// <summary>
        /// Writes the plugins list.
        /// </summary>
        /// <returns></returns>
        internal protected virtual bool WritePlugins()
        {
            var plugins = PluginManager.GetPlugins();

            this.BeginGroup("Plugins (" + plugins.Count + ")");
            {
                for(int i = 0; i < plugins.Count; i++)
                {
                    if (i > 0)
                        this.WriteLine();

                    var p = plugins[i];
                    this.BeginGroup(p.InternalKey);
                    {
                        this.Write("Name: ");
                        string n = p.InternalName;
                        if (n == null)
                            n = "(null)";
                        else
                            n = "\"" + n + "\"";
                        this.WriteLine(n);

                        this.Write("Version: ");
                        this.WriteLine(p.InternalVersion.ToString(this.Culture));

                        n = p.Author;
                        if(n != "Unknown" && !string.IsNullOrEmpty(n))
                            this.WriteLine("Author: \"" + n + "\"");

                        n = p.Website;
                        if (!string.IsNullOrEmpty(n))
                            this.WriteLine("Website: \"" + n + "\"");

                        this.Write("Assembly: ");
                        this.WriteLine(p.Assembly.ToString());
                    }
                    this.EndGroup();
                }
            }
            this.EndGroup();
            return true;
        }

        /// <summary>
        /// Writes extra information.
        /// </summary>
        /// <returns></returns>
        internal protected virtual bool WriteExtraInfo()
        {
            this.BeginGroup("Extra");
            {
                int count = 0;
                List<HookInfo> hooks = new List<HookInfo>();
                Memory.GetInProgressHooks(hooks, ref count);

                this.BeginGroup("Currently executing hooks (" + count + ")");
                {
                    for (int i = hooks.Count - 1; i >= 0; i--)
                    {
                        var hk = hooks[i];
                        this.BeginGroup(GetAddressInModule(hk.Address, this.Modules, ""));
                        {
                            this.Write("Installed from assembly: ");
                            if (hk.Assembly == null)
                                this.WriteLine("(null)");
                            else
                                this.WriteLine(hk.Assembly.ToString());

                            this.Write("Installed from plugin: ");
                            if (hk.Plugin == null)
                                this.WriteLine("(null)");
                            else
                                this.WriteLine(hk.Plugin.GetInternalString());

                            this.Write("Length: ");
                            this.WriteLine(hk.Length.ToString(this.Culture));

                            this.Write("Before: ");
                            if (hk.Before == null || hk.Before.Method == null)
                                this.WriteLine("(null)");
                            else
                                this.WriteLine(hk.Before.Method.ToString());

                            this.Write("After: ");
                            if (hk.After == null || hk.After.Method == null)
                                this.WriteLine("(null)");
                            else
                                this.WriteLine(hk.After.Method.ToString());
                        }
                        this.EndGroup();
                    }
                }
                this.EndGroup();
            }
            this.EndGroup();
            return true;
        }

        /// <summary>
        /// Gets the address in module.
        /// </summary>
        /// <param name="addr">The address.</param>
        /// <param name="modules">The modules.</param>
        /// <param name="prefix">Add this prefix if found.</param>
        /// <returns></returns>
        public static string GetAddressInModule(IntPtr addr, System.Diagnostics.ProcessModuleCollection modules, string prefix)
        {
            System.Diagnostics.ProcessModule m = null;
            int offset = 0;

            if (!TryGetCodeOffset(addr, modules, ref offset, ref m))
                return string.Empty;

            StringBuilder str = new StringBuilder();
            str.Append(prefix);
            str.Append("(");
            str.Append(m.ModuleName ?? "UnknownModule");
            str.Append("+");
            str.Append(offset.ToString("X"));
            str.Append(")");
            return str.ToString();
        }

        /// <summary>
        /// Tries the get module where address is in.
        /// </summary>
        /// <param name="addr">The address.</param>
        /// <param name="modules">The modules collection.</param>
        /// <param name="offset">The offset.</param>
        /// <param name="module">The module.</param>
        /// <returns></returns>
        private static bool TryGetCodeOffset(IntPtr addr, System.Diagnostics.ProcessModuleCollection modules, ref int offset, ref System.Diagnostics.ProcessModule module)
        {
            ulong a = addr.ToUInt64();
            for (int i = 0; i < modules.Count; i++)
            {
                var m = modules[i];

                ulong min = m.BaseAddress.ToUInt64();
                ulong max = min + (uint)m.ModuleMemorySize;

                if (a < min || a >= max)
                    continue;

                offset = (int)(a - min);
                module = m;
                return true;
            }

            return false;
        }
    }
    
    /// <summary>
    /// This is used to generate a crash log.
    /// </summary>
    public sealed class NativeCrashLog : CrashLog
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="NativeCrashLog"/> class.
        /// </summary>
        /// <param name="ctx">The context of thread that crashed.</param>
        internal NativeCrashLog(CPURegisters ctx) : base()
        {
            this.Context = ctx;
        }

        /// <summary>
        /// The context of thread that crashed.
        /// </summary>
        public readonly CPURegisters Context;

        /// <summary>
        /// The full stack.
        /// </summary>
        public IReadOnlyList<IntPtr> FullStack
        {
            get;
            private set;
        }

        /// <summary>
        /// The call stack.
        /// </summary>
        public IReadOnlyList<IntPtr> CallStack
        {
            get;
            private set;
        }

        /// <summary>
        /// Initializes this instance for log writing.
        /// </summary>
        /// <param name="stackCount">Stack pointer count.</param>
        protected internal override void Initialize(int stackCount)
        {
            base.Initialize(stackCount);

            // Prepare stack and call stack for writing.
            this.FullStack = GetStack(this.Context.SP, stackCount);
            var cs = this.FullStack.ToList();
            this.CallStack = cs;
            FilterCallStack(cs);
        }

        /// <summary>
        /// Writes the information line of crash. This is the same line that goes to main log.
        /// </summary>
        /// <returns></returns>
        protected internal override bool WriteInfo()
        {
            this.WriteLine("Unhandled native exception occurred at " + this.Context.IP.ToHexString() + GetAddressInModule(this.Context.IP, this.Modules, " ") + " on thread " + Memory.GetCurrentNativeThreadId() + "!");
            return true;
        }

        /// <summary>
        /// Writes the call stack.
        /// </summary>
        /// <returns></returns>
        protected internal override bool WriteCallStack()
        {
            this.BeginGroup("Probable callstack");
            this.WriteAddressCallStack("[0]", this.Context.IP);
            for (int i = 0; i < this.CallStack.Count; i++)
                this.WriteAddressCallStack("[" + (i + 1).ToString() + "]", this.CallStack[i]);
            this.EndGroup();
            return true;
        }

        /// <summary>
        /// Writes the registers. This is only valid for native exception.
        /// </summary>
        /// <returns></returns>
        protected internal override bool WriteRegisters()
        {
            this.BeginGroup("Registers");
            {
                this.WriteAddress("AX:", this.Context.AX, true);
                this.WriteAddress("BX:", this.Context.BX, true);
                this.WriteAddress("CX:", this.Context.CX, true);
                this.WriteAddress("DX:", this.Context.DX, true);
                this.WriteAddress("SI:", this.Context.SI, true);
                this.WriteAddress("DI:", this.Context.DI, true);
                this.WriteAddress("BP:", this.Context.BP, true);
                this.WriteAddress("SP:", this.Context.SP, true);
                this.WriteAddress("IP:", this.Context.IP, true);
                if (Main.Is64Bit)
                {
                    this.WriteAddress("R8:", this.Context.R8, true);
                    this.WriteAddress("R9:", this.Context.R9, true);
                    this.WriteAddress("R10:", this.Context.R10, true);
                    this.WriteAddress("R11:", this.Context.R11, true);
                    this.WriteAddress("R12:", this.Context.R12, true);
                    this.WriteAddress("R13:", this.Context.R13, true);
                    this.WriteAddress("R14:", this.Context.R14, true);
                    this.WriteAddress("R15:", this.Context.R15, true);
                }
                this.WriteAddress("Flags:", this.Context.FLAGS, false);
                // ST can't be printed because they are not in exception record info struct.
                /*int stc = this.Context.STCount;
                for(int i = 0; i < stc && i < 8; i++)
                {
                    stream.Write("ST" + i.ToString() + ":");
                    string st = null;
                    switch(i)
                    {
                        case 0: st = this.Context.ST0.ToString(this.Culture); break;
                        case 1: st = this.Context.ST1.ToString(this.Culture); break;
                        case 2: st = this.Context.ST2.ToString(this.Culture); break;
                        case 3: st = this.Context.ST3.ToString(this.Culture); break;
                        case 4: st = this.Context.ST4.ToString(this.Culture); break;
                        case 5: st = this.Context.ST5.ToString(this.Culture); break;
                        case 6: st = this.Context.ST6.ToString(this.Culture); break;
                        case 7: st = this.Context.ST7.ToString(this.Culture); break;
                    }
                    stream.WriteLine(string.Format(fmt, st));
                }*/
                this.WriteText("XMM0:", this.Context.XMM0.ToString(this.Culture));
                this.WriteText("XMM1:", this.Context.XMM1.ToString(this.Culture));
                this.WriteText("XMM2:", this.Context.XMM2.ToString(this.Culture));
                this.WriteText("XMM3:", this.Context.XMM3.ToString(this.Culture));
                this.WriteText("XMM4:", this.Context.XMM4.ToString(this.Culture));
                this.WriteText("XMM5:", this.Context.XMM5.ToString(this.Culture));
                this.WriteText("XMM6:", this.Context.XMM6.ToString(this.Culture));
                this.WriteText("XMM7:", this.Context.XMM7.ToString(this.Culture));
                if (Main.Is64Bit)
                {
                    this.WriteText("XMM8:", this.Context.XMM8.ToString(this.Culture));
                    this.WriteText("XMM9:", this.Context.XMM9.ToString(this.Culture));
                    this.WriteText("XMM10:", this.Context.XMM10.ToString(this.Culture));
                    this.WriteText("XMM11:", this.Context.XMM11.ToString(this.Culture));
                    this.WriteText("XMM12:", this.Context.XMM12.ToString(this.Culture));
                    this.WriteText("XMM13:", this.Context.XMM13.ToString(this.Culture));
                    this.WriteText("XMM14:", this.Context.XMM14.ToString(this.Culture));
                    this.WriteText("XMM15:", this.Context.XMM15.ToString(this.Culture));
                }
            }
            this.EndGroup();
            return true;
        }

        /// <summary>
        /// Writes the full stack. This is only valid for native exception.
        /// </summary>
        /// <returns></returns>
        protected internal override bool WriteFullStack()
        {
            this.BeginGroup("Stack");
            for (int i = 0; i < this.FullStack.Count; i++)
            {
                ulong offset = (ulong)i;
                offset *= (ulong)IntPtr.Size;

                this.WriteAddress("[SP+" + offset.ToString("X", this.Culture) + "]", this.FullStack[i], true);
            }
            this.EndGroup();
            return true;
        }
        
        /// <summary>
        /// The label size.
        /// </summary>
        private static int LabelSize = 10;

        /// <summary>
        /// Writes the address to stream.
        /// </summary>
        /// <param name="label">The label (optional).</param>
        /// <param name="value">The value.</param>
        /// <param name="evaluate">if set to <c>true</c> evaluate address to try and see what it is.</param>
        private void WriteAddress(string label, IntPtr value, bool evaluate)
        {
            if(!string.IsNullOrEmpty(label))
            {
                if (label.Length < LabelSize)
                    label = label + new string(' ', LabelSize - label.Length);

                this.Write(label);
            }

            this.Write(string.Format(Main.Is64Bit ? "{0,-18}" : "{0,-10}", value.ToHexString()) + GetAddressInModule(value, this.Modules, " "));
            if (!evaluate)
            {
                this.WriteLine();
                return;
            }
            
            string inf = GetValueInfo(value);
            if (!string.IsNullOrEmpty(inf))
                this.Write(" " + inf);
            this.WriteLine();
        }

        /// <summary>
        /// Writes the call stack address to stream.
        /// </summary>
        /// <param name="label">The label (optional).</param>
        /// <param name="value">The value.</param>
        private void WriteAddressCallStack(string label, IntPtr value)
        {
            if (!string.IsNullOrEmpty(label))
            {
                int lz = 6;
                if (label.Length < lz)
                    label = label + new string(' ', lz - label.Length);

                this.Write(label);
            }

            this.Write(string.Format(Main.Is64Bit ? "{0,-18}" : "{0,-10}", value.ToHexString()));
            this.Write(string.Format("{0,-32}", GetAddressInModule(value, this.Modules, " ")));

            if(Debug != null)
            {
                var fn = Debug.GetFunctionInfo(value, true);
                if(fn != null && !string.IsNullOrEmpty(fn.ShortName))
                {
                    string offset;
                    ulong addr = Main.Is64Bit ? value.ToUInt64() : value.ToUInt32();
                    if (addr >= Debug.BaseOffset)
                        addr -= Debug.BaseOffset;
                    else
                        addr = 0;
                    if (addr >= fn.Begin)
                        offset = "+" + (addr - fn.Begin).ToString("X");
                    else
                        offset = "+???";

                    this.Write(fn.ShortName + offset);
                }
            }

            this.WriteLine();
        }

        /// <summary>
        /// Gets the function address information.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <param name="full">Get full info, if false then only get the shortest best info we can.</param>
        /// <returns></returns>
        public static string GetFunctionAddressInfo(IntPtr value, bool full)
        {
            string info1 = string.Format(Main.Is64Bit ? "{0,-18}" : "{0,-10}", value.ToHexString());
            string info2 = string.Format("{0,-32}", GetAddressInModule(value, System.Diagnostics.Process.GetCurrentProcess().Modules, " "));
            string info3 = "";

            if (Debug != null)
            {
                var fn = Debug.GetFunctionInfo(value, true);
                if (fn != null && !string.IsNullOrEmpty(fn.ShortName))
                {
                    string offset;
                    ulong addr = Main.Is64Bit ? value.ToUInt64() : value.ToUInt32();
                    if (addr >= Debug.BaseOffset)
                        addr -= Debug.BaseOffset;
                    else
                        addr = 0;
                    if (addr >= fn.Begin)
                        offset = "+" + (addr - fn.Begin).ToString("X");
                    else
                        offset = "+???";

                    info3 = fn.ShortName + offset;
                }
            }

            if (full)
                return info1 + info2 + info3;

            if (!string.IsNullOrEmpty(info3))
                return info3;
            if (!string.IsNullOrEmpty(info2))
                return info2;
            return info1;
        }

        /// <summary>
        /// Guesses the value types.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <param name="type">The type.</param>
        /// <param name="simple">The simple type.</param>
        public static void GuessValueTypes(IntPtr value, ref DebugInfo.DebugTypeInfo type, ref string simple)
        {
            if(value == IntPtr.Zero)
            {
                simple = "null";
                return;
            }

            IntPtr target = IntPtr.Zero;

            if (Memory.TryReadPointer(value, ref target))
            {
                if(Debug != null)
                {
                    var ot = Debug.GetTypeInfo(target, true);
                    if (ot != null)
                    {
                        type = ot;
                        return;
                    }
                }

                string rs = Memory.ReadStringIfItsString(value, true);
                if (rs != null)
                {
                    simple = "string";
                    return;
                }
                else
                {
                    rs = Memory.ReadStringIfItsString(target, true);
                    if (rs != null)
                    {
                        simple = "pstring";
                        return;
                    }
                }

                simple = "ptr";
                return;
            }

            string types = GuessValueTypes(value);
            if (types.Contains('4'))
            {
                if (types.Contains('i'))
                    simple = "long";
                else
                    simple = "ulong";
            }
            else if (types.Contains('2'))
            {
                if (types.Contains('i'))
                    simple = "int";
                else
                    simple = "uint";
            }
            else if (types.Contains('6'))
            {
                simple = "ushort";
            }
            else if (types.Contains('8'))
            {
                simple = "byte";
            }

            if (types.Contains('d'))
            {
                if (string.IsNullOrEmpty(simple))
                    simple = "double";
                else
                    simple = simple + " double";
            }
            if (types.Contains('f'))
            {
                if (string.IsNullOrEmpty(simple))
                    simple = "float";
                else
                    simple = simple + " float";
            }
        }

        /// <summary>
        /// Gets the value information.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <returns></returns>
        public static string GetValueInfo(IntPtr value)
        {
            if (value == IntPtr.Zero)
                return "(NULL)";

            //Memory.IncIgnoreException();
            //try
            {
                StringBuilder str = new StringBuilder();
                bool isMemory = false;
                IntPtr target = IntPtr.Zero;

                if (Memory.TryReadPointer(value, ref target))
                    isMemory = true;

                if (!isMemory)
                {
                    string types = GuessValueTypes(value);
                    int prev = str.Length;
                    if (types.Contains('4'))
                    {
                        if (types.Contains('i'))
                            str.Append("(i64):[" + value.ToInt64().ToString() + "] ");
                        else
                            str.Append("(u64):[" + unchecked((ulong)value.ToInt64()).ToString() + "] ");
                    }
                    else if (types.Contains('2'))
                    {
                        if (types.Contains('i'))
                        {
                            if (Main.Is64Bit)
                                str.Append("(i32):[" + value.ToInt64().ToString() + "] ");
                            else
                                str.Append("(i32):[" + value.ToInt32().ToString() + "] ");
                        }
                        else
                            str.Append("(u32):[" + unchecked((ulong)value.ToInt64()).ToString() + "] ");
                    }
                    else if (types.Contains('6'))
                    {
                        str.Append("(u16):[" + unchecked((ulong)value.ToInt64()).ToString() + "] ");
                    }
                    else if (types.Contains('8'))
                    {
                        str.Append("(u8):[" + unchecked((ulong)value.ToInt64()).ToString() + "] ");
                    }

                    if (types.Contains('d'))
                        str.Append("(f64):[" + value.ToDouble().ToString(System.Globalization.CultureInfo.InvariantCulture) + "] ");
                    if (types.Contains('f'))
                        str.Append("(f32):[" + value.ToSingle().ToString(System.Globalization.CultureInfo.InvariantCulture) + "] ");

                    if (prev != str.Length)
                        str.Remove(str.Length - 1, 1);

                    return str.ToString();
                }

                bool wroteTypeName = false;
                if (Debug != null)
                {
                    IntPtr tg = target;
                    for (int level = 1; level <= 2; level++)
                    {
                        if(level >= 2)
                        {
                            if (!Memory.TryReadPointer(tg, ref tg))
                                break;
                        }

                        var knownType = Debug.GetTypeInfo(tg, true);
                        if (knownType != null)
                        {
                            str.Append("(");
                            str.Append(knownType.Name ?? "unknown");
                            str.Append(new string('*', level));
                            str.Append(")");
                            wroteTypeName = true;

                            if (Main.Game != null)
                            {
                                foreach (var dt in Main.Game.Types.TypesWithDebugWriters)
                                {
                                    try
                                    {
                                        Type dtt = dt.InterfaceType;
                                        if (dtt.IsGenericTypeDefinition)
                                            dtt = dtt.MakeGenericType(typeof(object));

                                        var conv = MemoryObject.FromAddressSafeCast(dtt, value);
                                        if (conv != null)
                                        {
                                            foreach (var x in dt.DebugWriters)
                                            {
                                                bool isSelf = string.IsNullOrEmpty(x.Name);
                                                if (isSelf)
                                                {
                                                    str.Append(" [");
                                                    string cs = conv.ToString();
                                                    if (!string.IsNullOrEmpty(cs))
                                                        str.Append(cs);
                                                    str.Append("]");
                                                }
                                                else
                                                {
                                                    if (x.Func == null)
                                                        continue;

                                                    str.Append(" (" + x.Name + "):[");
                                                    try
                                                    {
                                                        var y = x.Func(conv);
                                                        if (!string.IsNullOrEmpty(y))
                                                            str.Append(y);
                                                    }
                                                    catch//(Exception ex)
                                                    {
                                                        //Main.Log.Append(ex);
                                                    }
                                                    str.Append("]");
                                                }
                                            }
                                        }
                                    }
                                    catch
                                    {

                                    }
                                }
                            }
                        }
                    }
                }

                if (!wroteTypeName)
                {
                    string rs = Memory.ReadStringIfItsString(value, true);
                    if (rs != null)
                    {
                        str.Append("(char*) \"" + rs + "\"");
                        wroteTypeName = true;
                    }
                    else
                    {
                        rs = Memory.ReadStringIfItsString(target, true);
                        if (rs != null)
                        {
                            str.Append("(char**) \"" + rs + "\"");
                            wroteTypeName = true;
                        }
                    }

                    if (!wroteTypeName)
                        str.Append("(void*)");
                }

                return str.ToString();
            }
            /*finally
            {
                Memory.DecIgnoreException();
            }*/
        }

        /// <summary>
        /// Guesses the value types.
        /// </summary>
        /// <param name="ptr">The value.</param>
        /// <returns></returns>
        private static string GuessValueTypes(IntPtr ptr)
        {
            var str = new StringBuilder(8);

            if(Main.Is64Bit)
            {
                ulong r = unchecked((ulong)ptr.ToInt64());
                if ((r & 0xFF) == r)
                    str.Append('8');
                else if ((r & 0xFFFF) == r)
                    str.Append('6');
                else if ((r & 0xFFFFFFFF) == r)
                    str.Append('2');
                else
                    str.Append('4');

                if ((r & 0x8000000000000000) != 0)
                    str.Append('i');

                // Check float.
                {
                    uint x = (uint)(r & 0xFFFFFFFF);
                    if((x & 0x80000000) != 0)
                    {
                        if (x >= 0xb8d1b717 && x <= 0xc8742400) // between -0.0001 and -250000.0
                            str.Append('f');
                    }
                    else
                    {
                        if (x >= 0x38d1b717 && x <= 0x48742400) // between 0.0001 and 250000.0
                            str.Append('f');
                    }
                }

                // Check double.
                {
                    if((r & 0x8000000000000000) != 0)
                    {
                        if (r >= 0xbee4f8b588e368f1 && r <= 0xc12e848000000000) // between -0.00001 and -1000000.0
                            str.Append('d');
                    }
                    else
                    {
                        if (r >= 0x3ee4f8b588e368f1 && r <= 0x412e848000000000) // between 0.00001 and 1000000.0
                            str.Append('d');
                    }
                }
            }
            else
            {
                uint r = unchecked((uint)ptr.ToInt32());
                if ((r & 0xFF) == r)
                    str.Append('8');
                else if ((r & 0xFFFF) == r)
                    str.Append('6');
                else
                    str.Append('2');

                if ((r & 0x80000000) != 0)
                    str.Append('i');

                // Check float.
                {
                    if ((r & 0x80000000) != 0)
                    {
                        if (r >= 0xb8d1b717 && r <= 0xc8742400) // between -0.0001 and -250000.0
                            str.Append('f');
                    }
                    else
                    {
                        if (r >= 0x38d1b717 && r <= 0x48742400) // between 0.0001 and 250000.0
                            str.Append('f');
                    }
                }
            }

            return str.ToString();
        }

        /// <summary>
        /// Writes the text to stream.
        /// </summary>
        /// <param name="label">The label (optional).</param>
        /// <param name="value">The value.</param>
        private void WriteText(string label, string value)
        {
            if (!string.IsNullOrEmpty(label))
            {
                if (label.Length < LabelSize)
                    label = label + new string(' ', LabelSize - label.Length);

                this.Write(label);
            }

            if (!string.IsNullOrEmpty(value))
                this.WriteLine(value);
            else
                this.WriteLine();
        }

        /// <summary>
        /// Gets the stack memory values.
        /// </summary>
        /// <param name="start">The start of stack address.</param>
        /// <param name="count">The count of values to get.</param>
        /// <returns></returns>
        private static List<IntPtr> GetStack(IntPtr start, int count)
        {
            List<IntPtr> result = new List<IntPtr>();
            while (count-- > 0)
            {
                IntPtr ptr = IntPtr.Zero;
                if (!Memory.TryReadPointer(start, ref ptr))
                    return result;
                result.Add(ptr);
                start += IntPtr.Size;
            }

            return result;
        }

        /// <summary>
        /// Filters the stack and leaves only addresses with function calls.
        /// </summary>
        /// <param name="stack">The stack.</param>
        private static void FilterCallStack(List<IntPtr> stack)
        {
            for(int i = stack.Count - 1; i >= 0; i--)
            {
                if (!IsFunctionCallReturnAddress(stack[i]))
                    stack.RemoveAt(i);
            }
        }

        /// <summary>
        /// Determines whether the specified address is function call return address - meaning it has a function call before it.
        /// </summary>
        /// <param name="ptr">The address.</param>
        /// <returns></returns>
        /// <exception cref="System.NotImplementedException"></exception>
        private static bool IsFunctionCallReturnAddress(IntPtr ptr)
        {
            if (!Main.Is64Bit)
                throw new NotImplementedException();

            int sz = 8;
            uint oldFlags = 0;

            // Get memory protection flags. If this fails it's likely not a valid memory region.
            {
                uint _tFlags = 0;
                if (!VirtualProtect(ptr - sz, (uint)sz, 0x40, out oldFlags))
                    return false;
                VirtualProtect(ptr - sz, (uint)sz, oldFlags, out _tFlags);
            }

            // If no execute flag then it's not code region.
            if (oldFlags != 0x10 && // PAGE_EXECUTE
                oldFlags != 0x20 && // PAGE_EXECUTE_READ
                oldFlags != 0x40) // PAGE_EXECUTE_READWRITE
                return false;

            // It's still possible that the region is not code if someone else manually changed the protection flags.

            // Read bytes.
            byte[] data = null;
            if (!Memory.TryReadBytes(ptr - sz, sz, ref data))
                return false;

            string[] valid = new[]
            {
                "E8 ? ? ? ?", // Rel-call
                "FF D0", // call rax
                "FF D3", // call rbx
                "FF D1", // call rcx
                "FF D2", // call rdx
                "FF D6", // call rsi
                "FF D7", // call rdi
                "FF D5", // call rbp
                "41 FF D0", // call r8
                "41 FF D1", // call r9
                "41 FF D2", // call r10
                "41 FF D3", // call r11
                "41 FF D4", // call r12
                "41 FF D5", // call r13
                "41 FF D6", // call r14
                "41 FF D7", // call r15
                "FF 14 25 ? ? ? ?", // call qword ptr[...]
                "FF 10", // call [rax]
                "FF 13", // call [rbx]
                "FF 11", // call [rcx]
                "FF 12", // call [rdx]
                "FF 16", // call [rsi]
                "FF 17", // call [rdi]
                "FF 15", // call [rbp]
                "41 FF 10", // call [r8]
                "41 FF 11", // call [r9]
                "41 FF 12", // call [r10]
                "41 FF 13", // call [r11]
                "41 FF 14", // call [r12]
                "41 FF 15", // call [r13]
                "41 FF 16", // call [r14]
                "41 FF 17", // call [r15]
                "2E FF 14 25 ? ? ? ?", // call cs:[...]
                "FF 15 ? ? ? ?", // call [rip+...]
                "FF 50 ?", // call [rax+...]
                "FF 53 ?", // call [rbx+...]
                "FF 51 ?", // call [rcx+...]
                "FF 52 ?", // call [rdx+...]
                "FF 56 ?", // call [rsi+...]
                "FF 57 ?", // call [rdi+...]
                "FF 55 ?", // call [rbp+...]
                "41 FF 50 ?", // call [r8+...]
                "41 FF 51 ?", // call [r9+...]
                "41 FF 52 ?", // call [r10+...]
                "41 FF 53 ?", // call [r11+...]
                "41 FF 54 24 ?", // call [r12+...]
                "41 FF 55 ?", // call [r13+...]
                "41 FF 56 ?", // call [r14+...]
                "41 FF 57 ?", // call [r15+...]
                "FF 90 ? ? ? ?", // call [rax+...]
                "FF 93 ? ? ? ?", // call [rbx+...]
                "FF 91 ? ? ? ?", // call [rcx+...]
                "FF 92 ? ? ? ?", // call [rdx+...]
                "FF 96 ? ? ? ?", // call [rsi+...]
                "FF 97 ? ? ? ?", // call [rdi+...]
                "FF 95 ? ? ? ?", // call [rbp+...]
                "41 FF 90 ? ? ? ?", // call [r8+...]
                "41 FF 91 ? ? ? ?", // call [r9+...]
                "41 FF 92 ? ? ? ?", // call [r10+...]
                "41 FF 93 ? ? ? ?", // call [r11+...]
                "41 FF 94 24 ? ? ? ?", // call [r12+...]
                "41 FF 95 ? ? ? ?", // call [r13+...]
                "41 FF 96 ? ? ? ?", // call [r14+...]
                "41 FF 97 ? ? ? ?", // call [r15+...]
            };

            if (valid.Any(q => Test(q, data)))
                return true;

            return false;
        }

        /// <summary>
        /// Tests the specified memory for bytes.
        /// </summary>
        /// <param name="fmt">The format.</param>
        /// <param name="data">The data.</param>
        /// <returns></returns>
        private static bool Test(string fmt, byte[] data)
        {
            string[] spl = fmt.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
            if (spl.Length > data.Length)
                throw new InvalidOperationException();

            for(int i = spl.Length - 1, j = data.Length - 1; i >= 0; i--, j--)
            {
                if (spl[i][0] == '?' || spl[i][0] == '*')
                    continue;

                byte hx = byte.Parse(spl[i], System.Globalization.NumberStyles.AllowHexSpecifier, System.Globalization.CultureInfo.InvariantCulture);
                if (data[j] != hx)
                    return false;
            }

            return true;
        }

        [System.Runtime.InteropServices.DllImport("kernel32.dll")]
        private static extern bool VirtualProtect(IntPtr lpAddress, uint dwSize, uint flNewProtect, out uint lpflOldProtect);
    }

    /// <summary>
    /// This is used to generate a crash log.
    /// </summary>
    /// <seealso cref="NetScriptFramework.CrashLog" />
    public sealed class ManagedCrashLog : CrashLog
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="ManagedCrashLog"/> class.
        /// </summary>
        /// <param name="exception">The exception.</param>
        internal ManagedCrashLog(Exception exception) : base()
        {
            this.OriginalException = exception;
        }

        /// <summary>
        /// The original exception.
        /// </summary>
        public readonly Exception OriginalException;

        /// <summary>
        /// The current exception.
        /// </summary>
        internal Exception CurrentException = null;

        /// <summary>
        /// Writes the information line of crash. This is the same line that goes to main log.
        /// </summary>
        /// <returns></returns>
        protected internal override bool WriteInfo()
        {
            string at = this.OriginalException.TargetSite != null ? this.OriginalException.TargetSite.ToString() : "(null)";
            this.WriteLine("Unhandled managed exception (" + this.OriginalException.GetType().Name + ") occurred at " + at + "!");
            return true;
        }

        /// <summary>
        /// Writes the call stack.
        /// </summary>
        /// <returns></returns>
        protected internal override bool WriteCallStack()
        {
            this.BeginGroup("Callstack");
            {
                var spl = this.CurrentException.StackTrace.Replace("\r\n", "\n").Replace("\r", "\n").Split(new[] { '\n' }, StringSplitOptions.RemoveEmptyEntries);
                for (int i = 0; i < spl.Length; i++)
                    spl[i] = spl[i].Trim();

                foreach (var x in spl)
                    this.WriteLine(x);
            }
            this.EndGroup();
            return true;
        }
    }
}
