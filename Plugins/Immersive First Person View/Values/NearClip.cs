using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using IFPV.Values;

namespace IFPV.Values
{
    internal sealed class NearClip : CameraValueBase
    {
        internal NearClip()
        {
            this.Flags |= CameraValueFlags.NoTween;
        }

        internal override double DefaultValue
        {
            get
            {
                this.UpdateDefaultValue();
                return this._defaultValue.Value;
            }
        }

        private double? _defaultValue = null;
        private static NetScriptFramework.SkyrimSE.Setting _setting = null;

        private void UpdateDefaultValue()
        {
            if (this._defaultValue.HasValue)
                return;

            _setting = NetScriptFramework.SkyrimSE.Setting.FindSettingByName("fNearDistance:Display", true, true);
            if (_setting == null)
                throw new InvalidOperationException("Failed to find fNearDistance setting!");

            this._defaultValue = _setting.GetFloat();
        }

        internal override double CurrentValue
        {
            get
            {
                this.UpdateDefaultValue();
                return _setting.GetFloat();
            }

            set
            {
                this.UpdateDefaultValue();
                _setting.SetFloat((float)value);
            }
        }

        internal override double ChangeSpeed
        {
            get
            {
                return 1.0;
            }
        }

        internal override string Name
        {
            get
            {
                return "Near clip";
            }
        }
    }
}

namespace IFPV
{
    partial class CameraValueMap
    {
        internal readonly NearClip NearClip = new NearClip();
    }
}
