using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NetScriptFramework;
using NetScriptFramework.SkyrimSE;

namespace IFPV.States
{
    class Grabbing : CameraState
    {
        internal override int Priority
        {
            get
            {
                return (int)Priorities.Grabbing;
            }
        }

        internal override void OnEntering(CameraUpdate update)
        {
            base.OnEntering(update);

            update.Values.FaceCamera.AddModifier(this, CameraValueModifier.ModifierTypes.Set, 1);
        }

        internal override bool Check(CameraUpdate update)
        {
            if (!update.CameraMain.IsEnabled)
                return false;

            var plr = PlayerCharacter.Instance;
            if (plr == null)
                return false;

            uint refHandle = Memory.ReadUInt32(plr.Address + 0x8C8);
            if (refHandle == 0)
                return false;

            using (var objRef = new ObjectRefHolder(refHandle))
            {
                return objRef.IsValid;
            }
        }
    }
}
