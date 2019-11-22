using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using IFPV.Values;
using NetScriptFramework.Skyrim;

namespace IFPV.Values
{
    internal sealed class InputRotationX : CameraValueBase
    {
        internal InputRotationX()
        {
            this.Flags |= CameraValueFlags.NoTween | CameraValueFlags.NoModifiers;
        }

        internal override string Name
        {
            get
            {
                return "input rotation x";
            }
        }

        internal override double ChangeSpeed
        {
            get
            {
                return 1.0;
            }
        }

        internal override double DefaultValue
        {
            get
            {
                return 0.0;
            }
        }

        internal override double CurrentValue
        {
            get
            {
                var pcam = PlayerCamera.Instance;
                if (pcam != null)
                {
                    var pstate = pcam.State;
                    if (pstate != null)
                    {
                        var pthird = pstate.As<ThirdPersonState>();
                        if (pthird != null)
                            return pthird.XRotationFromLastResetPoint;
                    }
                }

                return 0.0;
            }

            set
            {
                var pcam = PlayerCamera.Instance;
                if (pcam != null)
                {
                    var pstate = pcam.State;
                    if (pstate != null)
                    {
                        var pthird = pstate.As<ThirdPersonState>();
                        if (pthird != null)
                            pthird.XRotationFromLastResetPoint = (float)value;
                    }
                }
            }
        }
    }
}

namespace IFPV
{
    partial class CameraValueMap
    {
        internal readonly InputRotationX InputRotationX = new InputRotationX();
    }
}

namespace IFPV.Values
{
    internal sealed class InputRotationY : CameraValueBase
    {
        internal InputRotationY()
        {
            this.Flags |= CameraValueFlags.NoTween | CameraValueFlags.NoModifiers;
        }

        internal override string Name
        {
            get
            {
                return "input rotation y";
            }
        }

        internal override double ChangeSpeed
        {
            get
            {
                return 1.0;
            }
        }

        internal override double DefaultValue
        {
            get
            {
                return 0.0;
            }
        }

        internal override double CurrentValue
        {
            get
            {
                var pcam = PlayerCamera.Instance;
                if (pcam != null)
                {
                    var pstate = pcam.State;
                    if (pstate != null)
                    {
                        var pthird = pstate.As<ThirdPersonState>();
                        if (pthird != null)
                        {
                            uint refHandle = pcam.TargetRefHandle;
                            using (var objRefHolder = new ObjectRefHolder(refHandle))
                            {
                                float amount = 0.0f;
                                if (objRefHolder.IsValid)
                                    amount = -objRefHolder.Object.Rotation.X;
                                float offset = pthird.YRotationFromLastResetPoint;
                                return amount + offset;
                            }
                        }
                    }
                }

                return 0.0;
            }

            set
            {
                var pcam = PlayerCamera.Instance;
                if (pcam != null)
                {
                    var pstate = pcam.State;
                    if (pstate != null)
                    {
                        var pthird = pstate.As<ThirdPersonState>();
                        if (pthird != null)
                        {
                            uint refHandle = pcam.TargetRefHandle;
                            using (var objRefHolder = new ObjectRefHolder(refHandle))
                            {
                                float amount = 0.0f;
                                if (objRefHolder.IsValid)
                                    amount = -objRefHolder.Object.Rotation.X;
                                float offset = (float)(value - amount);
                                pthird.YRotationFromLastResetPoint = offset;
                            }
                        }
                    }
                }
            }
        }
    }
}

namespace IFPV
{
    partial class CameraValueMap
    {
        internal readonly InputRotationY InputRotationY = new InputRotationY();
    }
}

namespace IFPV.Values
{
    internal sealed class InputRotationXMultiplier : CameraValueSimple
    {
        internal InputRotationXMultiplier() : base(null, 1.0, 1.0) { }
    }
}

namespace IFPV
{
    partial class CameraValueMap
    {
        internal readonly InputRotationXMultiplier InputRotationXMultiplier = new InputRotationXMultiplier();
    }
}

namespace IFPV.Values
{
    internal sealed class InputRotationYMultiplier : CameraValueSimple
    {
        internal InputRotationYMultiplier() : base(null, 1.0, 1.0) { }
    }
}

namespace IFPV
{
    partial class CameraValueMap
    {
        internal readonly InputRotationYMultiplier InputRotationYMultiplier = new InputRotationYMultiplier();
    }
}

namespace IFPV.Values
{
    internal sealed class ExtraResponsiveControls : CameraValueBase
    {
        internal ExtraResponsiveControls()
        {
            this.Flags |= CameraValueFlags.NoTween | CameraValueFlags.DontUpdateIfDisabled;
        }

        internal override string Name
        {
            get
            {
                return "extra responsive controls";
            }
        }

        internal override double ChangeSpeed
        {
            get
            {
                return 1.0;
            }
        }

        internal override double DefaultValue
        {
            get
            {
                init();
                return _def_value;
            }
        }

        internal override double CurrentValue
        {
            get
            {
                init();

                if (_setting != null)
                    return _setting.GetBool() ? 0.0 : 1.0;

                return _def_value;
            }

            set
            {
                if (_setting != null)
                    _setting.SetBool(value >= 0.5 ? false : true);
            }
        }

        private static bool _init_d = false;
        private static Setting _setting = null;
        private static double _def_value = 0.0;

        private static void init()
        {
            if (_init_d)
                return;
            _init_d = true;

            _setting = Setting.FindSettingByName("bDampenPlayerControls:Controls", true, true);

            if(_setting != null)
                _def_value = _setting.GetBool() ? 0.0 : 1.0;
        }
    }
}

namespace IFPV
{
    partial class CameraValueMap
    {
        internal readonly ExtraResponsiveControls ExtraResponsiveControls = new ExtraResponsiveControls();
    }
}
