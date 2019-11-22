using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IFPV.States
{
    /// <summary>
    /// This profile is used when player has no control and should just see what the character is doing.
    /// </summary>
    /// <seealso cref="IFPV.CameraState" />
    abstract class Passenger : CameraState
    {
        internal override void OnEntering(CameraUpdate update)
        {
            base.OnEntering(update);

            update.Values.InputRotationXMultiplier.AddModifier(this, CameraValueModifier.ModifierTypes.Set, 0);
            update.Values.InputRotationYMultiplier.AddModifier(this, CameraValueModifier.ModifierTypes.Set, 0);
            update.Values.PositionFromHead.AddModifier(this, CameraValueModifier.ModifierTypes.Set, 1);
            update.Values.RotationFromHead.AddModifier(this, CameraValueModifier.ModifierTypes.Set, 1);
            update.Values.HeadTrackEnabled.AddModifier(this, CameraValueModifier.ModifierTypes.Set, 0);
            update.Values.Show1stPersonArms.AddModifier(this, CameraValueModifier.ModifierTypes.Set, 0);
            update.Values.HideArms.AddModifier(this, CameraValueModifier.ModifierTypes.Set, 0);
            update.Values.FaceCamera.AddModifier(this, CameraValueModifier.ModifierTypes.Set, 0);
            update.Values.SkeletonMode.AddModifier(this, CameraValueModifier.ModifierTypes.Set, 0.0);
            Default.CantAutoTurnCounter++;
        }

        internal override void OnLeaving(CameraUpdate update)
        {
            base.OnLeaving(update);

            Default.CantAutoTurnCounter--;
        }
    }
}
