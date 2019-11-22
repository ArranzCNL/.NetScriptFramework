using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IFPV.States
{
    class SneakRoll : CameraState
    {
        internal override int Priority
        {
            get
            {
                return (int)Priorities.SneakRoll;
            }
        }

        internal override void OnEntering(CameraUpdate update)
        {
            base.OnEntering(update);

            //update.Values.StabilizeHistoryDuration.AddModifier(this, CameraValueModifier.ModifierTypes.SetIfPreviousIsHigherThanThis, 100.0);
            update.Values.RotationFromHead.AddModifier(this, CameraValueModifier.ModifierTypes.Set, 1.0);
            update.Values.PositionFromHead.AddModifier(this, CameraValueModifier.ModifierTypes.Set, 1.0);
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

            if (!actor.IsSneaking)
                return false;

            uint flags = NetScriptFramework.Memory.ReadUInt32(actor.Address + 0xC0) & 0x3FFF;
            return (flags & 0x100) != 0;
        }
    }
}
