using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IFPV.States
{
    class Bleedout : Passenger
    {
        internal override int Priority
        {
            get
            {
                return (int)Priorities.Bleedout;
            }
        }
        
        internal override bool Check(CameraUpdate update)
        {
            if (!update.CameraMain.IsEnabled)
                return false;

            return update.GameCameraState.Id == NetScriptFramework.SkyrimSE.TESCameraStates.Bleedout;
        }
    }
}
