using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IFPV.States
{
    class Walking : CameraState
    {
        internal override int Priority
        {
            get
            {
                return (int)Priorities.Walking;
            }
        }

        internal override void OnEntering(CameraUpdate update)
        {
            base.OnEntering(update);

            this.AddHeadBobModifier(update);
        }

        internal override bool Check(CameraUpdate update)
        {
            if (!update.CameraMain.IsEnabled)
                return false;

            if (update.CachedMounted)
                return false;

            var actor = update.Target.Actor;
            if (actor == null)
                return false;

            uint flags = NetScriptFramework.Memory.ReadUInt32(actor.Address + 0xC0) & 0x3FFF;
            return (flags & 0x1C0) == 0x40;
        }
    }
}
