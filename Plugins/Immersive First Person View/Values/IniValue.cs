using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IFPV.Values
{
    internal abstract class IniValue : CameraValueBase
    {
        internal IniValue(string name) : base()
        {
            this._name = name;
            this.Flags |= CameraValueFlags.NoTween;
        }

        private readonly string _name;

        internal override string Name
        {
            get
            {
                return this._name ?? "unk_ini_value";
            }
        }

        internal override double DefaultValue
        {
            get
            {
                return this._def;
            }
        }

        internal override double ChangeSpeed
        {
            get
            {
                return 1;
            }
        }

        internal override double CurrentValue
        {
            get
            {
                this.init();
                if (this._setting == null)
                    return 0;

                switch(this._setting.Type)
                {
                    case NetScriptFramework.SkyrimSE.SettingTypes.Float: return this._setting.GetFloat();
                    case NetScriptFramework.SkyrimSE.SettingTypes.Int:
                    case NetScriptFramework.SkyrimSE.SettingTypes.UInt: return this._setting.GetInt();
                }

                return 0;
            }

            set
            {
                this.init();
                if (this._setting == null)
                    return;

                switch(this._setting.Type)
                {
                    case NetScriptFramework.SkyrimSE.SettingTypes.Float: this._setting.SetFloat((float)value); break;
                    case NetScriptFramework.SkyrimSE.SettingTypes.Int:
                    case NetScriptFramework.SkyrimSE.SettingTypes.UInt: this._setting.SetInt((int)value); break;
                }
            }
        }

        private NetScriptFramework.SkyrimSE.Setting _setting = null;
        private double _def = 0;
        private bool _tried = false;

        private void init()
        {
            if (this._tried)
                return;

            this._tried = true;
            this._setting = NetScriptFramework.SkyrimSE.Setting.FindSettingByName(this.Name, true, true);

            if (this._setting != null)
                _def = this.CurrentValue;
        }
    }
}
