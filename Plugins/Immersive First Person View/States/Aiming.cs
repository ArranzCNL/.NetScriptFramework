using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NetScriptFramework;
using NetScriptFramework.Skyrim;

namespace IFPV.States
{
    class Aiming : CameraState
    {
        internal override int Priority
        {
            get
            {
                return (int)Priorities.Aiming;
            }
        }

        internal override void OnEntering(CameraUpdate update)
        {
            base.OnEntering(update);

            update.Values.FirstPersonSkeletonRotateYMultiplier.AddModifier(this, CameraValueModifier.ModifierTypes.Set, 1.0);
            update.Values.FaceCamera.AddModifier(this, CameraValueModifier.ModifierTypes.Set, 1.0);
            update.Values.RestrictDown.AddModifier(this, CameraValueModifier.ModifierTypes.Add, -10.0);
            update.Values.HeadTrackEnabled.AddModifier(this, CameraValueModifier.ModifierTypes.Set, 0.0);
        }

        internal override bool Check(CameraUpdate update)
        {
            if (!update.CameraMain.IsEnabled)
                return false;

            var actor = update.Target.Actor;
            if (actor == null)
                return false;

            // Aiming bow or crossbow.
            uint flags = Memory.ReadUInt32(actor.Address + 0xC0) >> 28;
            if (flags == 0xA)
                return true;
            
            for(int i = 0; i < 3; i++)
            {
                var caster = actor.GetMagicCaster((EquippedSpellSlots)i);
                if (caster == null)
                    continue;

                var state = caster.State;
                switch(state)
                {
                    case MagicCastingStates.Charged:
                    case MagicCastingStates.Charging:
                    case MagicCastingStates.Concentrating:
                        return true;
                }
            }

            return false;
        }
    }
}
