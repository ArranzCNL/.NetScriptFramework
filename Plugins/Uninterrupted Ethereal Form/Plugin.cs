using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NetScriptFramework;
using NetScriptFramework.SkyrimSE;

namespace UninterruptedEtherealForm
{
    public sealed class UninterruptedEtherealFormPlugin : Plugin
    {
        public override string Key
        {
            get
            {
                return "un_ethereal";
            }
        }

        public override string Name
        {
            get
            {
                return "Uninterrupted Ethereal Form";
            }
        }

        public override int Version
        {
            get
            {
                return 2;
            }
        }

        public override string Author
        {
            get
            {
                return "meh321";
            }
        }

        public Settings Settings
        {
            get;
            private set;
        }

        protected override bool Initialize(bool loadedAny)
        {
            var game = NetScriptFramework.Main.Game;
            if (game == null || game.LibraryVersion < 10)
                throw new InvalidOperationException(this.Name + " requires a newer version of .NET Script Framework. You must update the framework to use this plugin.");

            this._Initialize();

            return true;
        }

        private void _Initialize()
        {
            this.Settings = new Settings();
            this.Settings.Load();

            if (this.Settings.SuperInvisibility)
            {
                Events.OnCalculateDetection.Register(e =>
                {
                    Actor actor = e.TargetActor;
                    if (actor != null && actor.FindFirstEffectWithArchetype(Archetypes.Etherealize, false) != null)
                        e.ResultValue = -1000;
                }, 1);
            }

            if (this.Settings.DontRemove > 0)
            {
                int mode = this.Settings.DontRemove;
                if (mode == 1)
                    Events.OnRemoveMagicEffectsWithArchetype.Register(e =>
                    {
                        if (e.Archetype != Archetypes.Etherealize || e.Reason != MagicEffectRemovalReasons.Activation)
                            return;

                        e.Skip = true;
                    });
                else if (mode == 2)
                    Events.OnRemoveMagicEffectsWithArchetype.Register(e =>
                    {
                        if (e.Archetype != Archetypes.Etherealize || e.Reason == MagicEffectRemovalReasons.Expired)
                            return;

                        e.Skip = true;
                    });
            }
        }
    }
}
