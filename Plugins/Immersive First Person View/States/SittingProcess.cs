using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IFPV.States
{
    class SittingProcess : CameraState
    {
        internal override int Priority
        {
            get
            {
                return (int)Priorities.SittingProcess;
            }
        }

        internal override void OnEntering(CameraUpdate update)
        {
            base.OnEntering(update);

            update.Values.RotationFromHead.AddModifier(this, CameraValueModifier.ModifierTypes.SetIfPreviousIsLowerThanThis, 0.2);
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

            switch(actor.SitState)
            {
                case NetScriptFramework.SkyrimSE.ActorActionStates.NotAction:
                case NetScriptFramework.SkyrimSE.ActorActionStates.InProgress:
                    return false;
            }
            
            return true;
        }
    }
}
