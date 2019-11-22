using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using IFPV.Values;

namespace IFPV.Values
{
    internal sealed class RotationFromHead : CameraValueSimple
    {
        internal RotationFromHead() : base(null, Settings.Instance.RotationFromHead, 1.0) { }
    }
}

namespace IFPV
{
    partial class CameraValueMap
    {
        internal readonly RotationFromHead RotationFromHead = new RotationFromHead();
    }
}
