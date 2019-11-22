using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NetScriptFramework.Example
{
    /// <summary>
    /// Example plugin header.
    /// </summary>
    /// <seealso cref="NetScriptFramework.Plugin" />
    public sealed class ExamplePlugin : Plugin
    {
        /// <summary>
        /// Gets the unique keyword of plugin.<para></para><para></para>For developers: Other plugins may query plugin
        /// manager for your plugin using this keyword. This is not case sensitive! It is advisable to keep this short
        /// and simple phrase but unique enough that other plugin authors would not choose it.
        /// </summary>
        /// <value>
        /// The unique key of plugin.
        /// </value>
        public override string Key
        {
            get
            {
                return "example";
            }
        }

        /// <summary>
        /// Gets the name of plugin.<para></para><para></para>For developers: This is what will be shown to user and in
        /// the log files. This does not have to be unique but it should be informative enough to let user know what mod
        /// this is from.
        /// </summary>
        /// <value>
        /// The name of plugin.
        /// </value>
        public override string Name
        {
            get
            {
                return "Example plugin";
            }
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
        public override int Version
        {
            get
            {
                return 1;
            }
        }
        
        /// <summary>
        /// Initializes the plugin instance. Perform your plugin initialization here. If you return false then
        /// you will let plugin manager know that other plugins should be initialized first. The plugin manager will
        /// return to your plugin (and any others that returned false this pass) in the next pass. If no plugins were
        /// loaded in a pass then the argument "loadedAny" will be false. If all plugins in a pass still return false
        /// then the plugin manager will fail to load and an error will be displayed to user, forcing the game to exit.
        /// If you don't need to perform any initialization for your plugin then you can skip overriding this method
        /// or simply return <c>true</c>.
        /// </summary>
        /// <param name="loadedAny">If set to <c>true</c> then we did load at least one plugin last pass. It is safe
        /// to return false now and try again next pass. If this is set to <c>false</c> then all plugins in the last pass
        /// also returned false and if that happens again the game will close with an error.</param>
        /// <returns></returns>
        protected override bool Initialize(bool loadedAny)
        {
            return true;
        }
    }
}
