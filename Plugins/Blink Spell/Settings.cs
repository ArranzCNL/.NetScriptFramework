using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NetScriptFramework.Tools;

namespace BlinkSpell
{
    public sealed class Settings
    {
        [ConfigValue("MaxDistance", "Max distance", "The maximum distance to teleport. Absolute maximum is 8000 and will be capped to it.")]
        public float MaxDistance
        {
            get;
            set;
        } = 3000.0f;

        [ConfigValue("MarkerNif", "Marker NIF", "The NIF file to display as marker object while aiming.")]
        public string MarkerNif
        {
            get;
            set;
        } = "Magic\\MAGINVGenericSpellArt.nif";

        [ConfigValue("MarkerScale", "Marker scale", "The scale of the marker object.")]
        public float MarkerScale
        {
            get;
            set;
        } = 1.5f;

        [ConfigValue("TeleportSpeed", "Teleport speed", "The speed at which you move during teleport (this many units per second). Set 0 for instant teleport instead of moving there.")]
        public float TeleportSpeed
        {
            get;
            set;
        } = 10000.0f;

        [ConfigValue("TeleportIncrementalCheck", "Incremental check distance", "If the teleport spot is not valid go back this many units and check for next valid teleport position. This only happens if the spot does not have enough space for the player.")]
        public float TeleportIncrementalCheck
        {
            get;
            set;
        } = 50.0f;

        [ConfigValue("PlayerRadius", "Player radius", "The radius of the player. We can't teleport the player inside a wall so we must push the teleport point away from it, this is the amount to do so.")]
        public float PlayerRadius
        {
            get;
            set;
        } = 60.0f;

        [ConfigValue("AutoLearnSpell", "Auto learn", "Automatically learn the spell if player does not have it.")]
        public bool AutoLearnSpell
        {
            get;
            set;
        } = true;

        [ConfigValue("ScreenDistortion", "Screen distortion", "Apply screen distortion effect while teleporting. This is a multiplier amount. 0 disables, 2 doubles, 0.5 halves, negative is ok too to reverse the effect.")]
        public float ScreenDistortion
        {
            get;
            set;
        } = 1.0f;
        
        public NetScriptFramework.SkyrimSE.SpellItem SpellForm
        {
            get
            {
                var sp = this._spell;
                if(sp == null)
                {
                    sp = NetScriptFramework.SkyrimSE.TESForm.LookupFormFromFile<NetScriptFramework.SkyrimSE.SpellItem>(this.SpellFormId, this.SpellFormFile);
                    this._spell = sp;
                }
                return sp;
            }
            set
            {
                this._spell = value;
            }
        }
        private NetScriptFramework.SkyrimSE.SpellItem _spell = null;

        [ConfigValue("SpellFormId", "Spell form ID", "The form ID of the spell to use.", ConfigEntryFlags.PreferHex)]
        internal uint SpellFormId
        {
            get;
            set;
        } = 0xD63;

        [ConfigValue("SpellFormFile", "Spell form file", "The file where spell is from.")]
        internal string SpellFormFile
        {
            get;
            set;
        } = "BlinkSpell.esp";

        [ConfigValue("MaxSnapToGroundDistance", "Max snap distance", "The teleport will try to put the target location on the ground if it's within this distance (height) from it. Any further and the teleport location will be in the air.")]
        public float MaxSnapToGroundDistance
        {
            get;
            set;
        } = 150.0f;

        [ConfigValue("MaxWallClimbHeight", "Max wall climb height", "If you aim at a wall (steep enough angle) it will try to place the teleport point on top of the wall. This is the maximum units you can climb this way. Set 0 to disable this behavior.")]
        public float MaxWallClimbHeight
        {
            get;
            set;
        } = 300.0f;

        [ConfigValue("WallClimbWidth", "Wall climb width", "Used to calculate how much space is needed horizontally to wall climb.")]
        public float WallClimbWidth
        {
            get;
            set;
        } = 200.0f;

        [ConfigValue("Hotkey", "Hotkey", "If this is set (not 0) then aiming and teleporting also happens by holding this virtual key. Spell is not necessary. See https://docs.microsoft.com/en-us/windows/desktop/inputdev/virtual-key-codes for a list.", ConfigEntryFlags.PreferHex)]
        public int Hotkey
        {
            get;
            set;
        } = 0;

        [ConfigValue("AbortHotkey", "Abort hotkey", "If we are using hotkey to aim and teleport but we want to abort during aiming instead of teleporting then this key will do so.", ConfigEntryFlags.PreferHex)]
        public int AbortHotkey
        {
            get;
            set;
        } = 0;

        [ConfigValue("SoundFormId", "Sound form id", "The sound to play when teleporting.", ConfigEntryFlags.PreferHex)]
        internal uint SoundFormId
        {
            get;
            set;
        } = 0x3F37C; // 3F37D

        [ConfigValue("SoundFormFile", "Sound form file", "The file where the sound effect is from.")]
        internal string SoundFormFile
        {
            get;
            set;
        } = "Skyrim.esm";

        public NetScriptFramework.SkyrimSE.TESForm SoundForm
        {
            get
            {
                var so = this._sound;
                if (so == null)
                {
                    so = NetScriptFramework.SkyrimSE.TESForm.LookupFormFromFile(this.SoundFormId, this.SoundFormFile);
                    if (so == null || so.FormType == NetScriptFramework.SkyrimSE.FormTypes.SoundDescriptor)
                        this._sound = so;
                    else
                        so = null;
                }
                return so;
            }
            set
            {
                if (value == null || value.FormType == NetScriptFramework.SkyrimSE.FormTypes.SoundDescriptor)
                    this._sound = value;
            }
        }
        private NetScriptFramework.SkyrimSE.TESForm _sound = null;

        [ConfigValue("IModFormId", "Image space modifier form id", "The image space modifier to apply when teleporting.", ConfigEntryFlags.PreferHex)]
        internal uint IModFormId
        {
            get;
            set;
        } = 0x800;

        [ConfigValue("IModFormFile", "Image space modifier form file", "The file where the image space modifier is from.")]
        internal string IModFormFile
        {
            get;
            set;
        } = "BlinkSpell.esp";

        public NetScriptFramework.SkyrimSE.TESForm IModForm
        {
            get
            {
                var so = this._imod;
                if (so == null)
                {
                    so = NetScriptFramework.SkyrimSE.TESForm.LookupFormFromFile(this.IModFormId, this.IModFormFile);
                    if (so == null || so.FormType == NetScriptFramework.SkyrimSE.FormTypes.ImageSpaceMod)
                        this._imod = so;
                    else
                        so = null;
                }
                return so;
            }
            set
            {
                if (value == null || value.FormType == NetScriptFramework.SkyrimSE.FormTypes.ImageSpaceMod)
                    this._imod = value;
            }
        }
        private NetScriptFramework.SkyrimSE.TESForm _imod = null;

        [ConfigValue("MagickaCost", "Magicka cost", "Teleportation takes this much magicka.")]
        public float MagickaCost
        {
            get;
            set;
        } = 0.0f;

        [ConfigValue("StaminaCost", "Stamina cost", "Teleportation takes this much stamina.")]
        public float StaminaCost
        {
            get;
            set;
        } = 0.0f;

        [ConfigValue("AllowLedgeClimbNPC", "Ledge climb NPC", "Allow ledge/wall climb mode when aiming at NPC?")]
        public bool AllowLedgeClimbNPC
        {
            get;
            set;
        } = false;

        internal void Load()
        {
            ConfigFile.LoadFrom<Settings>(this, "BlinkSpell", true);
        }
    }
}
