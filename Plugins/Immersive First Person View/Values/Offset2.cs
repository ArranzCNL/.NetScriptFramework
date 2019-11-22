using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using IFPV.Values;

namespace IFPV.Values
{
    internal sealed class Offset2PositionX : CameraValueSimple
    {
        internal Offset2PositionX() : base(null, 0.0, 10.0) { }
    }
}

namespace IFPV
{
    partial class CameraValueMap
    {
        internal readonly Offset2PositionX Offset2PositionX = new Offset2PositionX();
    }
}

namespace IFPV.Values
{
    internal sealed class Offset2PositionY : CameraValueSimple
    {
        internal Offset2PositionY() : base(null, 0.0, 10.0) { }
    }
}

namespace IFPV
{
    partial class CameraValueMap
    {
        internal readonly Offset2PositionY Offset2PositionY = new Offset2PositionY();
    }
}

namespace IFPV.Values
{
    internal sealed class Offset2PositionZ : CameraValueSimple
    {
        internal Offset2PositionZ() : base(null, 0.0, 10.0) { }
    }
}

namespace IFPV
{
    partial class CameraValueMap
    {
        internal readonly Offset2PositionZ Offset2PositionZ = new Offset2PositionZ();
    }
}

namespace IFPV.Values
{
    internal sealed class Offset2RotationX : CameraValueSimple
    {
        internal Offset2RotationX() : base(null, 0.0, Math.PI * 0.5) { }
    }
}

namespace IFPV
{
    partial class CameraValueMap
    {
        internal readonly Offset2RotationX Offset2RotationX = new Offset2RotationX();
    }
}

namespace IFPV.Values
{
    internal sealed class Offset2RotationY : CameraValueSimple
    {
        internal Offset2RotationY() : base(null, 0.0, Math.PI * 0.5) { }
    }
}

namespace IFPV
{
    partial class CameraValueMap
    {
        internal readonly Offset2RotationY Offset2RotationY = new Offset2RotationY();
    }
}
