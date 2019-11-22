using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using IFPV.Values;

namespace IFPV.Values
{
    internal sealed class ThirdPersonArrowTilt : IniValue
    {
        internal ThirdPersonArrowTilt() : base("f3PArrowTiltUpAngle:Combat") { }
    }
}

namespace IFPV
{
    partial class CameraValueMap
    {
        internal readonly ThirdPersonArrowTilt ThirdPersonArrowTilt = new ThirdPersonArrowTilt();
    }
}
