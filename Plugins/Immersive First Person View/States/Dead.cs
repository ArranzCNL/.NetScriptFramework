using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IFPV.States
{
    class Dead : Passenger
    {
        internal override int Priority
        {
            get
            {
                return (int)Priorities.Dead;
            }
        }

        internal override bool Check(CameraUpdate update)
        {
            if (!update.CameraMain.IsEnabled)
                return false;

            var actor = update.Target.Actor;
            if (actor == null)
                return false;

            return actor.IsDead;
        }
    }
}
