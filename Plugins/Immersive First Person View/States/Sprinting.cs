using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IFPV.States
{
    class Sprinting : CameraState
    {
        internal override int Priority
        {
            get
            {
                return (int)Priorities.Sprinting;
            }
        }

        internal override void OnEntering(CameraUpdate update)
        {
            base.OnEntering(update);

            update.Values.StabilizeIgnoreOffsetY.AddModifier(this, CameraValueModifier.ModifierTypes.SetIfPreviousIsLowerThanThis, 34.0, true, 200);
            this.AddHeadBobModifier(update, false, true);
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

            if (actor.IsSneaking)
                return false;

            uint flags = NetScriptFramework.Memory.ReadUInt32(actor.Address + 0xC0) & 0x3FFF;
            return (flags & 0x100) != 0;
        }
    }
}
