using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IFPV.States
{
    class MountedProcess : CameraState
    {
        internal override int Priority
        {
            get
            {
                return (int)Priorities.MountedProcess;
            }
        }

        internal override void OnEntering(CameraUpdate update)
        {
            base.OnEntering(update);

            update.Values.RestrictLeft.AddModifier(this, CameraValueModifier.ModifierTypes.SetIfPreviousIsHigherThanThis, 10.0);
        }
        
        internal override bool Check(CameraUpdate update)
        {
            if (!update.CameraMain.IsEnabled)
                return false;

            if (!update.CachedMounted)
                return false;

            var actor = update.Target.Actor;
            if (actor == null)
                return false;

            switch (actor.SitState)
            {
                case NetScriptFramework.SkyrimSE.ActorActionStates.NotAction:
                case NetScriptFramework.SkyrimSE.ActorActionStates.InProgress:
                    return false;
            }

            return true;
        }
    }
}
