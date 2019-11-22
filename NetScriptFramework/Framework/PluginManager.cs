using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace NetScriptFramework
{
    #region PluginManager class

    /// <summary>
    /// This class will load, initialize and shutdown plugins when necessary. You can also query for a plugin or
    /// get a list of all loaded plugins.
    /// </summary>
    public static class PluginManager
    {
        #region PluginManager members

        /// <summary>
        /// Gets a plugin by its unique key. The key is not case sensitive. If the plugin was not found then
        /// it will return null.
        /// </summary>
        /// <param name="key">The unique key of plugin. This is not case sensitive.</param>
        /// <returns></returns>
        /// <exception cref="System.ArgumentNullException">key</exception>
        public static Plugin GetPlugin(string key)
        {
            if (key == null)
                throw new ArgumentNullException("key");
            return Plugins.FirstOrDefault(q => q.Key.Equals(key, StringComparison.OrdinalIgnoreCase)).Value;
        }

        /// <summary>
        /// Gets a plugin by type.
        /// </summary>
        /// <typeparam name="T">Type of plugin to get.</typeparam>
        /// <returns></returns>
        public static T GetPlugin<T>() where T : Plugin
        {
            var t = typeof(T);
            if (t.IsAbstract)
                throw new ArgumentException("Can't get an abstract type plugin!", "T");

            return Plugins.FirstOrDefault(q => q is T).Value as T;
        }

        /// <summary>
        /// Gets the plugin by its assembly.
        /// </summary>
        /// <param name="assembly">The assembly.</param>
        /// <returns></returns>
        internal static Plugin GetPlugin(System.Reflection.Assembly assembly)
        {
            if (assembly == null)
                return null;

            var pl = Plugins.Where(q => q.Value.Assembly == assembly).ToList();
            if (pl.Count == 1)
                return pl[0].Value;

            return null;
        }

        /// <summary>
        /// Gets a list of all the plugins.
        /// </summary>
        /// <returns></returns>
        public static List<Plugin> GetPlugins()
        {
            return Plugins.Select(q => q.Value).ToList();
        }

        #endregion

        #region Internal members

        /// <summary>
        /// Initializes this instance and all the plugins.
        /// </summary>
        internal static void Initialize()
        {
            Main.Log.AppendLine("Loading plugins.");

            string pluginPath = "";
            {
                var v = Main.Config.GetValue(Main._Config_Plugin_Path);
                if (v != null)
                    pluginPath = v.ToString();
            }

            Main.Log.AppendLine("Path to plugins: \"" + pluginPath + "\".");

            DirectoryInfo dir = new DirectoryInfo(pluginPath);
            if(!dir.Exists)
            {
                Main.Log.AppendLine("Directory \"" + pluginPath + "\" does not exist.");
            }
            else
            {
                Dictionary<string, Plugin> plugins = new Dictionary<string, Plugin>(StringComparer.OrdinalIgnoreCase);
                FileInfo[] files = dir.GetFiles("*.dll", SearchOption.TopDirectoryOnly);
                foreach(var f in files)
                {
                    // Process all files.
                    try
                    {
                        ProcessFile(f, plugins);
                    }
                    catch(Exception e)
                    {
                        Main.Log.Append(e);
                    }
                }

                List<KeyValuePair<string, Plugin>> loadedOrder = new List<KeyValuePair<string, Plugin>>();
                var processing = plugins.ToList();
                foreach (var x in plugins)
                    Plugins.Add(x);

                Main._is_initializing_plugin++;

                bool lastLoaded = true;
                while(processing.Count != 0)
                {
                    bool nowLoaded = false;
                    for(int i = 0; i < processing.Count;)
                    {
                        var p = processing[i];
                        int r;
                        Main._is_initializing_plugin++;
                        try
                        {
                            r = p.Value._initialize(lastLoaded) ? 1 : 0;
                        }
                        catch(Exception ex)
                        {
                            r = -1;
                            Main.Log.AppendLine("Exception occurred while trying to initialize plugin " + p.Value.GetInternalString() + ":");
                            Main.Log.Append(ex);
                            throw;
                        }
                        Main._is_initializing_plugin--;
                        if (r > 0)
                        {
                            processing.RemoveAt(i);
                            nowLoaded = true;
                            loadedOrder.Add(p);
                        }
                        else if(r < 0)
                        {
                            processing.RemoveAt(i);
                            nowLoaded = true;
                        }
                        else
                            i++;
                    }

                    if(!nowLoaded && !lastLoaded)
                    {
                        StringBuilder str = new StringBuilder();
                        for(int i = 0; i < processing.Count; i++)
                        {
                            if (i > 0)
                                str.Append(", ");
                            str.Append(processing[i].Value.GetInternalString());
                        }

                        if (processing.Count == 1)
                            throw new InvalidOperationException("The following plugin refused to initialize: " + str.ToString());
                        throw new InvalidOperationException("All the following plugins refused to initialize: " + str.ToString());
                    }

                    lastLoaded = nowLoaded;
                }

                Main._is_initializing_plugin--;

                Plugins.Clear();
                Plugins.AddRange(loadedOrder);
            }

            Main.Log.AppendLine("Finished loading " + Plugins.Count + " plugin" + (Plugins.Count == 1 ? "" : "s") + ".");
        }

        /// <summary>
        /// Processes the file for plugin loading.
        /// </summary>
        /// <param name="file">The file.</param>
        /// <param name="plugins">The plugins.</param>
        /// <returns></returns>
        /// <exception cref="System.InvalidOperationException"></exception>
        /// <exception cref="System.NotImplementedException"></exception>
        /// <exception cref="System.NullReferenceException"></exception>
        /// <exception cref="System.FormatException"></exception>
        private static void ProcessFile(FileInfo file, Dictionary<string, Plugin> plugins)
        {
            Main.Log.AppendLine("Checking file \"" + file.Name + "\"...");

            Assembly assembly = null;
            Loader.Load(file, ref assembly);
            if (assembly == null)
                throw new InvalidOperationException("Assembly failed to load and no exception was thrown!");
            
            var types = assembly.GetTypes();
            int totalFound = 0;
            List<Type>[] found = new List<Type>[7];
            List<ConstructorInfo> foundCis = new List<ConstructorInfo>();

            for (int i = 0; i < found.Length; i++)
                found[i] = new List<Type>();

            foreach (var t in types)
            {
                if (t == typeof(Plugin))
                {
                    totalFound++;
                    found[1].Add(t);
                    continue;
                }

                if (!t.IsSubclassOf(typeof(Plugin)))
                {
                    var qt = t.BaseType;
                    while (qt != null)
                    {
                        if (qt.Name == "Plugin")
                        {
                            totalFound++;
                            found[2].Add(t);
                            qt = null;
                            break;
                        }

                        qt = qt.BaseType;
                    }

                    continue;
                }

                if (t.IsAbstract)
                {
                    totalFound++;
                    found[3].Add(t);
                    continue;
                }

                if(t.BaseType != typeof(Plugin))
                {
                    totalFound++;
                    found[6].Add(t);
                    continue;
                }

                var constructors = t.GetConstructors(BindingFlags.Instance | BindingFlags.NonPublic | BindingFlags.Public);
                ConstructorInfo ci = null;
                foreach (var c in constructors)

                {
                    if (ci == null)
                        ci = c;
                    else if (c.GetParameters().Length == 0)
                        ci = c;
                }

                if (ci == null)
                {
                    totalFound++;
                    found[4].Add(t);
                    continue;
                }

                if (ci.GetParameters().Length != 0)
                {
                    totalFound++;
                    found[5].Add(t);
                    continue;
                }

                totalFound++;
                found[0].Add(t);
                foundCis.Add(ci);
            }

            if (totalFound == 0)
                throw new InvalidOperationException("Failed to load (" + file.Name + ")! Plugin header info type was missing. If this is a dependency then place it in the libraries folder.");

            if (found[0].Count > 1)
                throw new InvalidOperationException("Found more than one valid plugin header type!");

            if (found[0].Count == 0)
            {
                if (found[5].Count != 0)
                    throw new InvalidOperationException("Found plugin header type but invalid constructor arguments!");

                if (found[4].Count != 0)
                    throw new InvalidOperationException("Found plugin header type but no constructor!");

                if (found[3].Count != 0)
                    throw new InvalidOperationException("Found plugin header type but it's marked abstract!");

                if (found[2].Count != 0)
                    throw new InvalidOperationException("Found plugin header type but inherited from an incompatible type! If this is a plugin module then try recompiling plugin.");
                
                if (found[1].Count != 0)
                    throw new InvalidOperationException("Found plugin header type but it is not inherited from expected header type!");

                if (found[6].Count != 0)
                    throw new InvalidOperationException("Found plugin header type but it does not inherit directly from it!");

                throw new NotImplementedException();
            }

            CreatingPlugin = 1;
            Plugin pluginInstance = (Plugin)(foundCis[0].Invoke(new object[0]));
            pluginInstance.Assembly = assembly;

            string key = pluginInstance.InternalKey;
            int _vr = pluginInstance.InternalVersion; // Init these, if it throws exception we should abort now.
            string _nm = pluginInstance.InternalName;
            pluginInstance.InternalIndex = ++HighPluginIndex;

            if (key == null)
                throw new NullReferenceException("Plugin " + pluginInstance.GetInternalString() + " returned (null) as key!");

            if (key.Length == 0)
                throw new FormatException("Plugin \"" + pluginInstance.GetInternalString() + " returned empty key!");

            {
                Plugin d = null;
                if (plugins.TryGetValue(key, out d))
                {
                    string prev = d.GetInternalString();
                    string cur = pluginInstance.GetInternalString();
                    throw new InvalidOperationException("Plugin " + cur + " returned \"" + key + "\" as key! This is a duplicate of plugin " + prev + "! Multiple plugins with same key is not allowed.");
                }
            }

            plugins[key] = pluginInstance;

            Main.Log.AppendLine("Plugin found and loaded.");
        }

        /// <summary>
        /// The high plugin index.
        /// </summary>
        private static int HighPluginIndex = 0;

        /// <summary>
        /// Shutdowns this instance and all the plugins.
        /// </summary>
        internal static void Shutdown()
        {
            Main.Log.AppendLine("Shutting down plugins.");

            foreach(var x in Plugins)
            {
#if !DEBUG
                try
                {
#endif
                    x.Value._shutdown();
#if !DEBUG
                }
                catch (Exception e)
                {
                    Main.Log.AppendLine("Plugin " + x.Value.GetInternalString() + " threw an exception on shutdown!");
                    Main.Log.Append(e);
                }
#endif
            }
        }

        /// <summary>
        /// Detaches from the thread.
        /// </summary>
        internal static void DetachThread()
        {
            foreach (var x in Plugins)
                x.Value._onDetachThread();
        }

        /// <summary>
        /// Attaches to the thread.
        /// </summary>
        internal static void AttachThread()
        {
            foreach (var x in Plugins)
                x.Value._onAttachThread();
        }

        /// <summary>
        /// The plugins list.
        /// </summary>
        private static readonly List<KeyValuePair<string, Plugin>> Plugins = new List<KeyValuePair<string, Plugin>>();

        /// <summary>
        /// Allow creating plugin now.
        /// </summary>
        internal static int CreatingPlugin = 0;

        #endregion
    }

    #endregion
}
