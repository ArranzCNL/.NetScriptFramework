using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using IFPV.Values;

namespace IFPV.Values
{
    internal sealed class PositionFromHead : CameraValueSimple
    {
        internal PositionFromHead() : base(null, Settings.Instance.PositionFromHead, 2.0) { }
    }
}

namespace IFPV
{
    partial class CameraValueMap
    {
        internal readonly PositionFromHead PositionFromHead = new PositionFromHead();
    }
}
