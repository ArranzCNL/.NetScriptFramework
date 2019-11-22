using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IFPV.Values
{
    internal sealed class StabilizeHistoryDuration : CameraValueSimple
    {
        internal StabilizeHistoryDuration(double value) : base(null, value, 5000.0) { }
    }

    internal sealed class StabilizeIgnorePositionX : CameraValueSimple
    {
        internal StabilizeIgnorePositionX(double value) : base(null, value, 5.0) { }
    }

    internal sealed class StabilizeIgnorePositionY : CameraValueSimple
    {
        internal StabilizeIgnorePositionY(double value) : base(null, value, 5.0) { }
    }

    internal sealed class StabilizeIgnorePositionZ : CameraValueSimple
    {
        internal StabilizeIgnorePositionZ(double value) : base(null, value, 5.0) { }
    }

    internal sealed class StabilizeIgnoreRotationX : CameraValueSimple
    {
        internal StabilizeIgnoreRotationX(double value) : base(null, value, 30.0) { }
    }

    internal sealed class StabilizeIgnoreRotationY : CameraValueSimple
    {
        internal StabilizeIgnoreRotationY(double value) : base(null, value, 30.0) { }
    }

    internal sealed class StabilizeIgnoreOffsetX : CameraValueSimple
    {
        internal StabilizeIgnoreOffsetX(double value) : base(null, value, 720.0)
        {
            this.Formula = TValue.TweenTypes.Decelerating;
        }
    }

    internal sealed class StabilizeIgnoreOffsetY : CameraValueSimple
    {
        internal StabilizeIgnoreOffsetY(double value) : base(null, value, 720.0)
        {
            this.Formula = TValue.TweenTypes.Decelerating;
        }
    }
}

namespace IFPV
{
    partial class CameraValueMap
    {
        internal readonly IFPV.Values.StabilizeHistoryDuration StabilizeHistoryDuration = new Values.StabilizeHistoryDuration(Settings.Instance.StabilizeHistoryDuration * 1000.0f);
        internal readonly IFPV.Values.StabilizeIgnorePositionX StabilizeIgnorePositionX = new Values.StabilizeIgnorePositionX(Settings.Instance.StabilizeIgnorePositionX);
        internal readonly IFPV.Values.StabilizeIgnorePositionY StabilizeIgnorePositionY = new Values.StabilizeIgnorePositionY(Settings.Instance.StabilizeIgnorePositionY);
        internal readonly IFPV.Values.StabilizeIgnorePositionZ StabilizeIgnorePositionZ = new Values.StabilizeIgnorePositionZ(Settings.Instance.StabilizeIgnorePositionZ);
        internal readonly IFPV.Values.StabilizeIgnoreRotationX StabilizeIgnoreRotationX = new Values.StabilizeIgnoreRotationX(Settings.Instance.StabilizeIgnoreRotationX);
        internal readonly IFPV.Values.StabilizeIgnoreRotationY StabilizeIgnoreRotationY = new Values.StabilizeIgnoreRotationY(Settings.Instance.StabilizeIgnoreRotationY);
        internal readonly IFPV.Values.StabilizeIgnoreOffsetX StabilizeIgnoreOffsetX = new Values.StabilizeIgnoreOffsetX(Settings.Instance.StabilizeIgnoreOffsetX);
        internal readonly IFPV.Values.StabilizeIgnoreOffsetY StabilizeIgnoreOffsetY = new Values.StabilizeIgnoreOffsetY(Settings.Instance.StabilizeIgnoreOffsetY);
    }
}
