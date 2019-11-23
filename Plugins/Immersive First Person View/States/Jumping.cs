using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IFPV.States
{
    class Jumping : CameraState
    {
        internal override int Priority
        {
            get
            {
                return (int)Priorities.Jumping;
            }
        }

        internal override void OnEntering(CameraUpdate update)
        {
            base.OnEntering(update);

            update.Values.StabilizeIgnoreOffsetX.AddModifier(this, CameraValueModifier.ModifierTypes.SetIfPreviousIsLowerThanThis, 25.0, true, 500);
            update.Values.StabilizeIgnoreOffsetY.AddModifier(this, CameraValueModifier.ModifierTypes.SetIfPreviousIsLowerThanThis, 37.0, true, 700);
        }

        internal override bool Check(CameraUpdate update)
        {
            if (!update.CameraMain.IsEnabled)
                return false;

            var actor = update.Target.Actor;
            if (actor == null)
                return false;
            var state = actor.MovementState;
            return state == NetScriptFramework.SkyrimSE.bhkCharacterStateTypes.Jumping || state == NetScriptFramework.SkyrimSE.bhkCharacterStateTypes.InAir;
        }
    }
}
