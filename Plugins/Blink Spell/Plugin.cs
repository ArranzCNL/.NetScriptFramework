using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NetScriptFramework;
using NetScriptFramework.Skyrim;

namespace BlinkSpell
{
    public sealed class BlinkSpellPlugin : Plugin
    {
        public override string Key
        {
            get
            {
                return "blinkspell";
            }
        }

        public override string Name
        {
            get
            {
                return "Blink Spell";
            }
        }

        public override string Author
        {
            get
            {
                return "meh321";
            }
        }

        public override int Version
        {
            get
            {
                return 3;
            }
        }

        public override string Website
        {
            get
            {
                return "https://www.nexusmods.com/skyrimspecialedition/mods/21606";
            }
        }

        private BlinkState State = null;
        private NetScriptFramework.Tools.Timer Timer = null;
        private long? LastUpdateTime = null;
        
        public Settings Settings
        {
            get;
            private set;
        }
        
        protected override bool Initialize(bool loadedAny)
        {
            var game = NetScriptFramework.Main.Game;
            if (game == null || game.LibraryVersion < 5)
                throw new InvalidOperationException(this.Name + " requires newer version of .NET script framework! Go update.");

            this._Initialize();

            return true;
        }

        private void _Initialize()
        {
            this.Settings = new Settings();
            this.Settings.Load();

            this.Timer = new NetScriptFramework.Tools.Timer();
            this.Timer.Start();

            Events.OnFrame.Register(e =>
            {
                long now = this.Timer.Time;
                long diff = 0;
                if (this.LastUpdateTime.HasValue)
                    diff = now - this.LastUpdateTime.Value;
                this.LastUpdateTime = now;

                if (this.State != null)
                    this.State.Update((float)diff / 1000.0f, (float)now / 1000.0f);
            });

            Events.OnMainMenu.Register(e =>
            {
                this.State = new BlinkState(this);
                this.State.Initialize();
            });

            Events.OnMagicCasterFire.Register(e =>
            {
                if (this.State == null)
                    return;

                var item = e.Item;
                var spell = this.Settings.SpellForm;
                if (item == null || spell == null || !spell.Equals(item))
                    return;

                var casterBase = e.Caster;
                if (casterBase == null)
                    return;

                var casterActor = casterBase.As<ActorMagicCaster>();
                Actor owner = null;
                if (casterActor == null || (owner = casterActor.Owner) == null || !owner.IsPlayer)
                    return;

                this.State.Fire(true);
            });

            Events.OnUpdateCamera.Register(e =>
            {
                if (this.State == null)
                    return;

                float amt = this.State.GetDistortionEffect();
                if (amt == 0.0f)
                    return;

                var cameraBase = e.Camera;
                if (cameraBase == null)
                    return;

                var playerCamera = cameraBase.As<PlayerCamera>();
                if (playerCamera == null)
                    return;

                var node = playerCamera.Node;
                if (node == null)
                    return;

                if (amt > 0.0f)
                    node.LocalTransform.Rotation[2, 2] *= 1.0f + amt;
                else
                    node.LocalTransform.Rotation[2, 2] /= 1.0f - amt;
                node.Update(0.0f);
            }, 100000);
        }
    }
}
