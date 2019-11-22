using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace NetScriptFramework
{
    /// <summary>
    /// Helper class for assembly loading.
    /// </summary>
    public static class Loader
    {
        /// <summary>
        /// Loads the specified file as assembly. This will throw exception if there are problems. It's possible that the assembly was loaded anyway.
        /// Loading a file with same name again will attempt to return same assembly even if the file versions are different.
        /// </summary>
        /// <param name="file">The file to load from.</param>
        /// <param name="result">The result is set here. Result may be set even when an exception is thrown.</param>
        public static void Load(FileInfo file, ref Assembly result)
        {
            lock(Locker)
            {
                AssemblyLoadResult r = Loaded.FirstOrDefault(q => q.FileName.Equals(file.Name, StringComparison.OrdinalIgnoreCase));
                if(r != null)
                {
                    result = r.Assembly;
                    if (r.Exception != null)
                        throw r.Exception;
                    return;
                }

                if (!file.Exists)
                    throw new FileNotFoundException("Specified assembly file was not found!", file.FullName);
                
                // Must use LoadFile instead of LoadFrom or the load context will not allow types to match up.
                Assembly a = Assembly.LoadFile(file.FullName);

                r = new AssemblyLoadResult();
                r.Assembly = a;
                r.FileName = file.Name;
                r.Exception = null;

                Loaded.Add(r);
                result = a;
            }
        }

        /// <summary>
        /// Tries the load assembly by its short name. For example TryLoadAssembly("NetScriptFramework") would try to load
        /// the core framework assembly.
        /// </summary>
        /// <param name="name">The name of assembly to load.</param>
        /// <returns></returns>
        public static Assembly TryLoadAssembly(string name)
        {
            if (name == Main.FrameworkName)
                return Assembly.GetExecutingAssembly();

            lock(Locker)
            {
                foreach(var a in Loaded)
                {
                    if (a.Assembly != null && a.Assembly.GetName().Name == name)
                        return a.Assembly;
                }

                string[] paths = new string[3];
                paths[0] = null;
                paths[1] = null;
                paths[2] = string.Empty;

                {
                    var plugin = Main.Config.GetValue(Main._Config_Plugin_Path);
                    if (plugin != null)
                        paths[0] = plugin.ToString();
                }

                {
                    var plugin = Main.Config.GetValue(Main._Config_Plugin_Lib_Path);
                    if (plugin != null)
                        paths[1] = plugin.ToString();
                }

                for (int i = 0; i < paths.Length; i++)
                {
                    string p = paths[i];
                    if (p == null)
                        continue;

                    string fileName = System.IO.Path.Combine(p, name + ".dll");
                    FileInfo fileInfo = new FileInfo(fileName);
                    if (!fileInfo.Exists)
                        continue;

                    Assembly a = null;
                    Load(fileInfo, ref a);

                    if (a != null)
                        return a;
                }
            }

            return null;
        }

        /// <summary>
        /// Called when trying to resolve an assembly.
        /// </summary>
        /// <param name="sender">The sender.</param>
        /// <param name="e">The <see cref="ResolveEventArgs"/> instance containing the event data.</param>
        /// <returns></returns>
        private static Assembly OnAssemblyResolve(object sender, ResolveEventArgs e)
        {
            // Get name for custom loading.
            string name = e.Name;
            if (name != null && name.Contains(","))
                name = name.Substring(0, name.IndexOf(","));

            // Try to use our method of loading.
            var result = TryLoadAssembly(name);
            if (result != null)
                return result;

            // Pass to regular loader if wasn't one of our assemblies.
            return Assembly.Load(e.Name);
        }

        /// <summary>
        /// Initializes the assembly loader.
        /// </summary>
        internal static void Initialize()
        {
            AppDomain.CurrentDomain.AssemblyResolve += OnAssemblyResolve;

            // Set up custom dependency path for plugins. When plugins use custom dependency with DllImport for example they
            // can store them in the appropriate path instead of having to put them in the main executable folder.
            var path = Main.Config.GetValue(Main._Config_Plugin_Lib_Path);
            if(path != null)
            {
                string pString = path.ToString();
                if (!string.IsNullOrEmpty(pString) && pString != ".")
                {
                    try
                    {
                        AddDLLSearchPath(pString);
                    }
                    catch(Exception ex)
                    {
                        if (Main.Log != null)
                        {
                            Main.Log.AppendLine("Failed to add \"" + pString + "\" to DLL path search!");
                            Main.Log.Append(ex);
                        }
                    }
                }
            }
        }

        private static void AddDLLSearchPath(string path)
        {
            if (string.IsNullOrEmpty(path) || path == ".")
                return;

            string fullPath = Path.GetFullPath(path);

            //SetDllDirectory(fullPath);

            if (!Path.IsPathRooted(path))
                path = Path.GetFullPath(path);

            string pathVar = Environment.GetEnvironmentVariable("PATH") ?? string.Empty;
            Environment.SetEnvironmentVariable("PATH", pathVar + ";" + path);
        }

        /// <summary>
        /// Sets the DLL directory. Internal API call.
        /// </summary>
        /// <param name="lpPathName">Path.</param>
        /// <returns></returns>
        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        private static extern bool SetDllDirectory(string lpPathName);

        /// <summary>
        /// The locker for loading.
        /// </summary>
        private static object Locker = new object();

        /// <summary>
        /// The loaded assembly list.
        /// </summary>
        private static readonly List<AssemblyLoadResult> Loaded = new List<AssemblyLoadResult>();
    }

    /// <summary>
    /// Internal class for storing loaded assembly info.
    /// </summary>
    internal sealed class AssemblyLoadResult
    {
        /// <summary>
        /// The file name.
        /// </summary>
        internal string FileName;

        /// <summary>
        /// The assembly that was loaded.
        /// </summary>
        internal Assembly Assembly;

        /// <summary>
        /// The exception if any was thrown.
        /// </summary>
        internal Exception Exception;
    }
}
