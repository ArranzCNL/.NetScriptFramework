using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NetScriptFramework.Skyrim;

namespace IFPV.States
{
    class Crafting : Passenger
    {
        internal override int Priority
        {
            get
            {
                return (int)Priorities.Crafting;
            }
        }

        internal override void OnEntering(CameraUpdate update)
        {
            base.OnEntering(update);

            update.Values.Offset1PositionY.AddModifier(this, CameraValueModifier.ModifierTypes.Set, -5.0);
            update.Values.NearClip.AddModifier(this, CameraValueModifier.ModifierTypes.SetIfPreviousIsHigherThanThis, 1.0);
        }

        internal override bool Check(CameraUpdate update)
        {
            if (!update.CameraMain.IsEnabled)
                return false;
            
            var mm = MenuManager.Instance;
            if(mm != null)
            {
                if (mm.IsMenuOpen("Crafting Menu"))
                    return true;
            }

            return false;
        }
    }
}
