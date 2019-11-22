using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IFPV.States
{
    class Killmove : Passenger
    {
        internal override int Priority
        {
            get
            {
                return (int)Priorities.Killmove;
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
            return actor != null && actor.IsInKillmove;
        }
    }
}
