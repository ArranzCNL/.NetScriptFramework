using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using IFPV.Values;
using NetScriptFramework.Skyrim;

namespace IFPV.Values
{
    internal sealed class HideHead : CameraValueSimple
    {
        internal HideHead() : base(null, 0.0, 1.0)
        {
            this.Flags |= CameraValueFlags.NoTween;
        }
    }

    internal sealed class HideHelmet : CameraValueSimple
    {
        internal HideHelmet() : base(null, 0.0, 1.0)
        {
            this.Flags |= CameraValueFlags.NoTween;
        }
    }

    internal sealed class HideHead2 : CameraValueSimple
    {
        internal HideHead2() : base(null, 0.0, 1.0)
        {
            this.Flags |= CameraValueFlags.NoTween;
        }
    }
    
    /*internal sealed class HideWeapon : CameraValueSimple
    {
        internal HideWeapon() : base(null, 0.0, 1.0)
        {
            this.Flags |= CameraValueFlags.NoTween;
        }
    }*/

    internal sealed class HideArms : CameraValueSimple
    {
        internal HideArms() : base(null, 0.0, 1.0)
        {
            this.Flags |= CameraValueFlags.NoTween;
        }
    }

    internal sealed class Show1stPersonArms : CameraValueSimple
    {
        internal Show1stPersonArms() : base(null, 0.0, 1.0)
        {
            this.Flags |= CameraValueFlags.NoTween;
        }
    }

    internal sealed class FirstPersonSkeletonRotateYMultiplier : CameraValueSimple
    {
        internal FirstPersonSkeletonRotateYMultiplier() : base(null, Settings.Instance.NormalFirstPersonArmsRotateRatio, 1.0) { }
    }

    internal sealed class BlockPlayerFadeOut : CameraValueSimple
    {
        internal BlockPlayerFadeOut() : base(null, 0.0, 1.0)
        {
            this.Flags |= CameraValueFlags.NoTween;
        }
    }

    internal sealed class SkeletonMode : CameraValueSimple
    {
        internal SkeletonMode() : base(null, -1.0, 1.0)
        {
            this.Flags |= CameraValueFlags.NoTween;
        }
    }
}

namespace IFPV
{
    partial class CameraValueMap
    {
        internal readonly HideHead HideHead = new HideHead();
        internal readonly HideHelmet HideHelmet = new HideHelmet();
        internal readonly HideHead2 HideHead2 = new HideHead2();
        internal readonly HideArms HideArms = new HideArms();
        internal readonly Show1stPersonArms Show1stPersonArms = new Show1stPersonArms();
        internal readonly FirstPersonSkeletonRotateYMultiplier FirstPersonSkeletonRotateYMultiplier = new FirstPersonSkeletonRotateYMultiplier();
        internal readonly BlockPlayerFadeOut BlockPlayerFadeOut = new BlockPlayerFadeOut();
        internal readonly SkeletonMode SkeletonMode = new SkeletonMode();
    }
}
