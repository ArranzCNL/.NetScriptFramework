using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using IFPV.Values;

namespace IFPV.Values
{
    internal sealed class OffsetObjectPositionX : CameraValueSimple
    {
        internal OffsetObjectPositionX() : base(null, 0.0, 20.0) { }
    }

    internal sealed class OffsetObjectPositionY : CameraValueSimple
    {
        internal OffsetObjectPositionY() : base(null, 0.0, 20.0) { }
    }

    internal sealed class OffsetObjectPositionZ : CameraValueSimple
    {
        internal OffsetObjectPositionZ() : base(null, 0.0, 20.0) { }
    }
}

namespace IFPV
{
    partial class CameraValueMap
    {
        internal readonly OffsetObjectPositionX OffsetObjectPositionX = new OffsetObjectPositionX();
        internal readonly OffsetObjectPositionY OffsetObjectPositionY = new OffsetObjectPositionY();
        internal readonly OffsetObjectPositionZ OffsetObjectPositionZ = new OffsetObjectPositionZ();
    }
}
