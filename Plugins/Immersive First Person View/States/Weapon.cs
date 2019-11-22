using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IFPV.States
{
    class Weapon : CameraState
    {
        internal override int Priority
        {
            get
            {
                return (int)Priorities.Weapon;
            }
        }

        internal override void OnEntering(CameraUpdate update)
        {
            base.OnEntering(update);

            if (Settings.Instance.ShowNormalFirstPersonArms)
            {
                update.Values.HideArms.AddModifier(this, CameraValueModifier.ModifierTypes.Set, 1.0);
                update.Values.Show1stPersonArms.AddModifier(this, CameraValueModifier.ModifierTypes.Set, 1.0);
            }

            update.Values.ThirdPersonArrowTilt.AddModifier(this, CameraValueModifier.ModifierTypes.Set, 1.5);
        }

        internal override bool Check(CameraUpdate update)
        {
            if (!update.CameraMain.IsEnabled)
                return false;

            var actor = update.Target.Actor;
            return actor != null && actor.IsWeaponDrawn;
        }
    }
}
