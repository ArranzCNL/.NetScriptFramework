using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using IFPV.Values;

namespace IFPV.Values
{
    internal sealed class FaceCamera : CameraValueSimple
    {
        internal FaceCamera() : base(null, 0.0, 1.0)
        {
            this.Flags |= CameraValueFlags.NoTween;
        }
    }

    internal sealed class ActorTurnTime : CameraValueSimple
    {
        internal ActorTurnTime() : base(null, 0.0, 1.0)
        {
            this.Flags |= CameraValueFlags.NoTween;
        }
    }
}

namespace IFPV
{
    partial class CameraValueMap
    {
        internal readonly FaceCamera FaceCamera = new FaceCamera();
        internal readonly ActorTurnTime ActorTurnTime = new ActorTurnTime();
    }
}
