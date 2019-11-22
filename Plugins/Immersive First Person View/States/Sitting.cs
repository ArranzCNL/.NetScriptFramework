using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IFPV.States
{
    class Sitting : CameraState
    {
        internal override int Priority
        {
            get
            {
                return (int)Priorities.Sitting;
            }
        }

        internal override void OnEntering(CameraUpdate update)
        {
            base.OnEntering(update);

            update.Values.FaceCamera.AddModifier(this, CameraValueModifier.ModifierTypes.Set, 0);
            Default.CantAutoTurnCounter++;
        }

        internal override void OnLeaving(CameraUpdate update)
        {
            base.OnLeaving(update);

            Default.CantAutoTurnCounter--;
        }

        internal override bool Check(CameraUpdate update)
        {
            if (!update.CameraMain.IsEnabled)
                return false;

            if (update.CachedMounted)
                return false;

            // Also triggers on some crafting benches but it should be fine

            var actor = update.Target.Actor;
            if (actor == null)
                return false;

            if (actor.SitState == NetScriptFramework.Skyrim.ActorActionStates.NotAction)
                return false;
            
            return true;
        }
    }
}
