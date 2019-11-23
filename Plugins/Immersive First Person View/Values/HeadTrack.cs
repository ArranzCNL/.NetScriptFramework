using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using IFPV.Values;

namespace IFPV.Values
{
    internal sealed class HeadTrackEnabled : CameraValueBase
    {
        internal HeadTrackEnabled()
        {
            this.Flags |= CameraValueFlags.NoTween | CameraValueFlags.DontUpdateIfDisabled;
        }

        internal override double DefaultValue
        {
            get
            {
                return 0.0;
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
                return "head tracking enabled";
            }
        }

        internal override double CurrentValue
        {
            get
            {
                var plr = NetScriptFramework.SkyrimSE.PlayerCharacter.Instance;
                if (plr != null)
                    return plr.IsHeadTrackingEnabled ? 1 : 0;
                return 0;
            }

            set
            {
                var plr = NetScriptFramework.SkyrimSE.PlayerCharacter.Instance;
                if (plr != null)
                    plr.IsHeadTrackingEnabled = value > 0.0;
            }
        }
    }
}

namespace IFPV
{
    partial class CameraValueMap
    {
        internal readonly HeadTrackEnabled HeadTrackEnabled = new HeadTrackEnabled();
    }
}
