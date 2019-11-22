using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using IFPV.Values;

namespace IFPV.Values
{
    internal sealed class WantEnabled : CameraValueSimple
    {
        internal WantEnabled() : base(null, 0.0, 1.0)
        {
            this.Flags |= CameraValueFlags.NoTween;
        }
    }

    internal sealed class WantDisabled : CameraValueSimple
    {
        internal WantDisabled() : base(null, 0.0, 1.0)
        {
            this.Flags |= CameraValueFlags.NoTween;
        }
    }
}

namespace IFPV
{
    partial class CameraValueMap
    {
        internal readonly WantEnabled WantEnabled = new WantEnabled();
        internal readonly WantDisabled WantDisabled = new WantDisabled();
    }
}
