using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NetScriptFramework.Tools;

namespace UninterruptedEtherealForm
{
    public sealed class Settings
    {
        [ConfigValue("DontRemove", "Remove mode", "Don't remove ethereal form effect before expiring. 0 = disabled, 1 = don't remove if activating things, 2 = don't remove for any reason.")]
        public int DontRemove
        {
            get;
            set;
        } = 1;

        [ConfigValue("SuperInvisibility", "Super invisibility", "If this is enabled then you are completely undetectable while ethereal even if you run into others or fight them.")]
        public bool SuperInvisibility
        {
            get;
            set;
        } = false;

        public void Load()
        {
            ConfigFile.LoadFrom(this, "UninterruptedEtherealForm", true);
        }
    }
}
