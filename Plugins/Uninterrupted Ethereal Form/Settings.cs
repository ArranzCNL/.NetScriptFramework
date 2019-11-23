using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NetScriptFramework.Tools;

namespace UninterruptedInvisibility
{
    public class Settings
    {
        [ConfigValue("DontRemove", "Remove mode", "Don't remove invisibility effect before expiring. 0 = disabled, 1 = don't remove if activating things, 2 = don't remove for any reason.")]
        public int DontRemove
        {
            get;
            set;
        } = 1;

        [ConfigValue("SuperInvisibility", "Super invisibility", "If this is enabled then you are completely undetectable while invisible even if you run into them or fight them.")]
        public bool SuperInvisibility
        {
            get;
            set;
        } = false;

        public void Load()
        {
            ConfigFile.LoadFrom(this, "UninterruptedInvisibility", true);
        }
    }
}
