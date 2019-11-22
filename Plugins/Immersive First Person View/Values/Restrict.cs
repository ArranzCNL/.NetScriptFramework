using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using IFPV.Values;

namespace IFPV.Values
{
    internal sealed class RestrictLeft : CameraValueSimple
    {
        internal RestrictLeft() : base(null, Settings.Instance.MaximumLeftAngle, 90.0) { }
    }

    internal sealed class RestrictRight : CameraValueSimple
    {
        internal RestrictRight() : base(null, Settings.Instance.MaximumRightAngle, 90.0) { }
    }

    internal sealed class RestrictLeft2 : CameraValueSimple
    {
        internal RestrictLeft2() : base(null, Settings.Instance.MaximumLeftAngleRestricted, 90.0) { }
    }

    internal sealed class RestrictRight2 : CameraValueSimple
    {
        internal RestrictRight2() : base(null, Settings.Instance.MaximumRightAngleRestricted, 90.0) { }
    }

    internal sealed class RestrictUp : CameraValueSimple
    {
        internal RestrictUp() : base(null, Settings.Instance.MaximumUpAngle, 90.0) { }
    }

    internal sealed class RestrictDown : CameraValueSimple
    {
        internal RestrictDown() : base(null, Settings.Instance.MaximumDownAngle, 90.0) { }
    }

    internal sealed class RestrictSideDown : CameraValueSimple
    {
        internal RestrictSideDown() : base(null, Settings.Instance.RestrictSideAngleWhenLookingDown, 30.0) { }
    }
}

namespace IFPV
{
    partial class CameraValueMap
    {
        internal readonly RestrictLeft RestrictLeft = new RestrictLeft();
        internal readonly RestrictRight RestrictRight = new RestrictRight();
        internal readonly RestrictLeft2 RestrictLeft2 = new RestrictLeft2();
        internal readonly RestrictRight2 RestrictRight2 = new RestrictRight2();
        internal readonly RestrictUp RestrictUp = new RestrictUp();
        internal readonly RestrictDown RestrictDown = new RestrictDown();
        internal readonly RestrictSideDown RestrictSideDown = new RestrictSideDown();
    }
}
