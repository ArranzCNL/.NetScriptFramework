using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NetScriptFramework.Skyrim;

namespace IFPV.States
{
    class Lich : CameraState
    {
        internal override int Priority
        {
            get
            {
                return (int)Priorities.Lich;
            }
        }

        internal override int Group
        {
            get
            {
                return (int)Groups.Beast;
            }
        }

        internal override void OnEntering(CameraUpdate update)
        {
            base.OnEntering(update);

            if (Settings.Instance.HideHead)
                update.Values.HideHead2.AddModifier(this, CameraValueModifier.ModifierTypes.Set, 1.0);
            update.Values.HideHead.AddModifier(this, CameraValueModifier.ModifierTypes.Set, 0.0);
            update.Values.HideArms.AddModifier(this, CameraValueModifier.ModifierTypes.Set, 0.0);
            update.Values.HideHelmet.AddModifier(this, CameraValueModifier.ModifierTypes.Set, 0.0);
            update.Values.Show1stPersonArms.AddModifier(this, CameraValueModifier.ModifierTypes.Set, 0.0);
        }

        internal override bool Check(CameraUpdate update)
        {
            if (!update.CameraMain.IsEnabled)
                return false;

            var actor = update.Target.Actor;
            if (actor == null)
                return false;

            string want = Settings.Instance.LichRaceName;
            if (string.IsNullOrEmpty(want))
                return false;

            var race = actor.Race;
            if (race == null)
                return false;

            string name = race.Name;
            string id = race.EditorId;

            return (!string.IsNullOrEmpty(name) && name.IndexOf(want, StringComparison.OrdinalIgnoreCase) >= 0) ||
                (!string.IsNullOrEmpty(id) && id.IndexOf(want, StringComparison.OrdinalIgnoreCase) >= 0);
        }
    }

    class LichTransform : CameraState
    {
        internal override int Priority
        {
            get
            {
                return (int)Priorities.LichTransform;
            }
        }

        internal override int Group
        {
            get
            {
                return (int)Groups.Beast;
            }
        }

        internal override void OnEntering(CameraUpdate update)
        {
            base.OnEntering(update);

            update.Values.Offset1PositionY.AddModifier(this, CameraValueModifier.ModifierTypes.Add, 5.0);
            update.Values.Offset1PositionZ.AddModifier(this, CameraValueModifier.ModifierTypes.Add, 2.0);
        }

        private void init()
        {
            if (_t_init)
                return;
            _t_init = true;

            uint id = Settings.Instance.LichTransformationEffectId;
            string file = Settings.Instance.LichTransformationEffectFile;

            if (id == 0 || string.IsNullOrEmpty(file))
                return;

            _effect = TESForm.LookupFormFromFile<EffectSetting>(id, file);
        }

        private bool _t_init = false;
        private EffectSetting _effect = null;

        internal override bool Check(CameraUpdate update)
        {
            this.init();

            if (_effect == null)
                return false;

            var actor = update.Target.Actor;
            if (actor == null)
                return false;

            return actor.HasMagicEffect(this._effect);
        }
    }
}
