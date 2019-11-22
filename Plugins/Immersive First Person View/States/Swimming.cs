using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IFPV.States
{
    class Swimming : CameraState
    {
        internal override int Priority
        {
            get
            {
                return (int)Priorities.Swimming;
            }
        }

        internal override void OnEntering(CameraUpdate update)
        {
            base.OnEntering(update);
        }

        internal override bool Check(CameraUpdate update)
        {
            if (!update.CameraMain.IsEnabled)
                return false;

            var actor = update.Target.Actor;
            if (actor == null)
                return false;

            uint flags = NetScriptFramework.Memory.ReadUInt32(actor.Address + 0xC0) & 0x3FFF;
            return (flags & 0x400) != 0;
        }
    }
}
