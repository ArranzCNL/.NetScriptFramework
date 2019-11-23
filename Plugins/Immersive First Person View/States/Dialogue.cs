using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NetScriptFramework.SkyrimSE;

namespace IFPV.States
{
    class Dialogue : CameraState
    {
        internal override int Priority
        {
            get
            {
                return (int)Priorities.Dialogue;
            }
        }

        internal override void OnEntering(CameraUpdate update)
        {
            base.OnEntering(update);

            //update.Values.FaceCamera.AddModifier(this, CameraValueModifier.ModifierTypes.Set, 0);
        }

        internal override bool Check(CameraUpdate update)
        {
            if (!update.CameraMain.IsEnabled)
                return false;

            var mm = MenuManager.Instance;
            if (mm == null)
                return false;

            return mm.IsMenuOpen("Dialogue Menu");
        }
    }
}
