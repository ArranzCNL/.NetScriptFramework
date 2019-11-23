using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NetScriptFramework;
using NetScriptFramework.Tools;
using NetScriptFramework.SkyrimSE;

namespace IFPV
{
    /// <summary>
    /// Settings loaded from configuration file.
    /// </summary>
    public sealed class Settings
    {
        #region Activation
        
        [ConfigValue("ReplaceDefaultCamera", "Replace default camera", "This says if we should completely replace the regular first person view. If you try to zoom in or toggle into first person view it will instead toggle into this mod's view. This is recommended to enable unless you plan to use only the custom hotkey or there will be weird stuff.")]
        public bool ReplaceDefaultCamera
        {
            get;
            set;
        } = true;
        
        [ConfigValue("ToggleHotkey", "Hotkey", "The hotkey to enable or disable IFPV. See https://docs.microsoft.com/en-us/windows/desktop/inputdev/virtual-key-codes for a list of all keycodes. For example 0x61 is numpad 1. This is optional and setting 0 disables the hotkey.", ConfigEntryFlags.PreferHex)]
        public int ToggleHotkey
        {
            get;
            set;
        } = 0;

        [ConfigValue("FixLookSensitivity", "Fix look sensitivity", "This will fix look sensitivity so the horizontal look sensitivity is not tied to framerate. Set 0 for vanilla mode where it is tied to framerate, 1 to fix always and 2 to fix only when IFPV view is enabled.")]
        public int FixLookSensitivity
        {
            get;
            set;
        } = 0;

        #endregion

        #region Base rotation and offset

        [ConfigValue("PositionFromHead", "Head position multiplier", "Set the amount of position that comes from player's actual head position.")]
        public float PositionFromHead
        {
            get;
            set;
        } = 0.0f;

        [ConfigValue("RotationFromHead", "Head rotation multiplier", "Set the amount of rotation that comes from player's actual head position.")]
        public float RotationFromHead
        {
            get;
            set;
        } = 0.0f;
        
        [ConfigValue("BaseOffsetX", "Base offset X", "This is the base position offset from head. +X is right, -X is left.")]
        public float BaseOffsetX
        {
            get;
            set;
        } = 0.0f;

        [ConfigValue("BaseOffsetY", "Base offset Y", "This is the base position offset from head. +Y is forward, -Y is backward.")]
        public float BaseOffsetY
        {
            get;
            set;
        } = 10.0f;

        [ConfigValue("BaseOffsetZ", "Base offset Z", "This is the base position offset from head. +Z is up, -Z is down.")]
        public float BaseOffsetZ
        {
            get;
            set;
        } = 0.0f;

        [ConfigValue("DownOffsetX", "Down offset X", "Move camera left/right when looking down past a certain angle.")]
        public float DownOffsetX
        {
            get;
            set;
        } = 0.0f;

        [ConfigValue("DownOffsetY", "Down offset Y", "Move camera back/forward when looking down past a certain angle.")]
        public float DownOffsetY
        {
            get;
            set;
        } = 10.0f;

        [ConfigValue("DownOffsetZ", "Down offset Z", "Move camera down/up when looking down past a certain angle.")]
        public float DownOffsetZ
        {
            get;
            set;
        } = 0.0f;

        [ConfigValue("DownOffsetBeginAngle", "Down offset angle", "Move camera when looking down past a certain angle. This is the angle where we start moving the camera. Set 360 to disable this. Set 50 for example to start moving when looking past 50 degrees down.")]
        public float DownOffsetBeginAngle
        {
            get;
            set;
        } = 360.0f;

        #endregion

        #region Look angle restriction

        [ConfigValue("MaximumLeftAngle", "Maximum left angle", "The maximum horizontal angle that you can look at. This is in degrees.")]
        public float MaximumLeftAngle
        {
            get;
            set;
        } = 100.0f;

        [ConfigValue("MaximumRightAngle", "Maximum right angle", "The maximum horizontal angle that you can look at. This is in degrees.")]
        public float MaximumRightAngle
        {
            get;
            set;
        } = 100.0f;

        [ConfigValue("MaximumUpAngle", "Maximum up angle", "The maximum vertical angle you can look at (up). This is in degrees.")]
        public float MaximumUpAngle
        {
            get;
            set;
        } = 80.0f;

        [ConfigValue("MaximumDownAngle", "Maximum down angle", "The maximum vertical angle you can look at (down). This is in degrees.")]
        public float MaximumDownAngle
        {
            get;
            set;
        } = 80.0f;

        [ConfigValue("MaximumDownAngleCollided", "Maximum down angle on collide", "The maximum vertical angle you can look at (down) right after colliding with something. This is in degrees.")]
        public float MaximumDownAngleCollided
        {
            get;
            set;
        } = 30.0f;

        [ConfigValue("RestrictSideAngleWhenLookingDown", "Restrict side angle when looking down", "If greater than zero then restrict the side angle when looking down a lot. This is to prevent weird angle. The amount here is when to begin restricting (MaximumDownAngle - this_value).")]
        public float RestrictSideAngleWhenLookingDown
        {
            get;
            set;
        } = 40.0f;

        [ConfigValue("MaximumLeftAngleRestricted", "Maximum left angle when restricted", "The maximum horizontal angle that you can look at when restricted by looking down a lot. This is in degrees.")]
        public float MaximumLeftAngleRestricted
        {
            get;
            set;
        } = 10.0f;

        [ConfigValue("MaximumRightAngleRestricted", "Maximum right angle when restricted", "The maximum horizontal angle that you can look at when restricted by looking down a lot. This is in degrees.")]
        public float MaximumRightAngleRestricted
        {
            get;
            set;
        } = 10.0f;

        #endregion

        #region Look sensitivity

        [ConfigValue("LookSensitivity", "Look sensitivity", "The global look sensitivity multiplier while IFPV is active.")]
        public float LookSensitivity
        {
            get;
            set;
        } = 1.0f;

        [ConfigValue("LookSensitivityHorizontal", "Horizontal look sensitivity", "Additional horizontal look sensitivity multiplier (left and right) while IFPV is active.")]
        public float LookSensitivityHorizontal
        {
            get;
            set;
        } = 1.0f;

        [ConfigValue("LookSensitivityVertical", "Vertical look sensitivity", "Additional vertical look sensitivity multiplier (down and up) while IFPV is active.")]
        public float LookSensitivityVertical
        {
            get;
            set;
        } = 1.0f;

        #endregion

        #region Camera stabilization

        [ConfigValue("StabilizeHistoryDuration", "Stabilizer history duration", "How many seconds to keep node offsets in history for stabilizing the camera.")]
        public float StabilizeHistoryDuration
        {
            get;
            set;
        } = 0.3f;

        [ConfigValue("StabilizeIgnorePositionX", "Stabilizer position ignore X", "How much to ignore X axis movement (left/right) when stabilizing camera.")]
        public float StabilizeIgnorePositionX
        {
            get;
            set;
        } = 3.0f;

        [ConfigValue("StabilizeIgnorePositionY", "Stabilizer position ignore Y", "How much to ignore Y axis movement (back/forward) when stabilizing camera.")]
        public float StabilizeIgnorePositionY
        {
            get;
            set;
        } = 2.5f;

        [ConfigValue("StabilizeIgnorePositionZ", "Stabilizer position ignore Z", "How much to ignore Z axis movement (up/down) when stabilizing camera.")]
        public float StabilizeIgnorePositionZ
        {
            get;
            set;
        } = 2.0f;

        [ConfigValue("StabilizeIgnoreRotationX", "Stabilizer rotation ignore X", "How much to ignore left/right rotation when stabilizing camera. This is in degrees.")]
        public float StabilizeIgnoreRotationX
        {
            get;
            set;
        } = 0.0f;

        [ConfigValue("StabilizeIgnoreRotationY", "Stabilizer rotation ignore Y", "How much to ignore up/down rotation when stabilizing camera. This is in degrees.")]
        public float StabilizeIgnoreRotationY
        {
            get;
            set;
        } = 0.0f;

        [ConfigValue("StabilizeIgnoreOffsetX", "Stabilizer rotation offset ignore X", "How much to ignore left/right rotation offset when stabilizing camera.")]
        public float StabilizeIgnoreOffsetX
        {
            get;
            set;
        } = 90.0f;

        [ConfigValue("StabilizeIgnoreOffsetY", "Stabilizer rotation offset ignore Y", "How much to ignore up/down rotation offset when stabilizing camera.")]
        public float StabilizeIgnoreOffsetY
        {
            get;
            set;
        } = 90.0f;

        #endregion

        #region Near clip

        [ConfigValue("NearClipExteriorDefault", "Near clip in exterior", "Set the near clip value when in first person mode. Lower value means objects don't disappear when too near but can also cause flickering issues with distant objects.")]
        public float NearClipExteriorDefault
        {
            get;
            set;
        } = 10.0f;

        [ConfigValue("NearClipExteriorDown", "Near clip in exterior 2", "Set near clip value when looking down significantly.")]
        public float NearClipExteriorDown
        {
            get;
            set;
        } = 3.0f;

        [ConfigValue("NearClipInteriorDefault", "Near clip in interior", "Set the near clip value when in first person mode. Lower value means objects don't disappear when too near but can also cause flickering issues with distant objects.")]
        public float NearClipInteriorDefault
        {
            get;
            set;
        } = 3.0f;

        [ConfigValue("NearClipInteriorDown", "Near clip in interior 2", "Set near clip value when looking down significantly.")]
        public float NearClipInteriorDown
        {
            get;
            set;
        } = 3.0f;

        #endregion

        #region Other stuff

        [ConfigValue("HeadTrackEnable", "Enable head tracking", "Enable head tracking while in the mod's first person view? This will make your character turn their head where you are aiming. This setting can't be used together with camera stabilizer unless you set very high values for IgnoreOffsetX/Y (90+). This setting will reduce chance of clipping when looking down at your character due to your character leaning forward when looking down. It is disabled by default because it adds some movement to camera and some people find it distracting for gameplay.")]
        public bool HeadTrackEnable
        {
            get;
            set;
        } = false;

        [ConfigValue("Enable360WalkAnimationCompatibilityMode", "Enable 360 animation compatibility", "This will allow you to move backwards with 360 compatibility animations without too much weirdness, hopefully.")]
        public bool Enable360WalkAnimationCompatibilityMode
        {
            get;
            set;
        } = false;

        [ConfigValue("My360WalkAnimationActivatesWithSneakToo", "Sneak 360 animations", "Enable this if your 360 walk animations also apply to sneak mode.")]
        public bool My360WalkAnimationActivatesWithSneakToo
        {
            get;
            set;
        } = false;

        [ConfigValue("My360WalkAnimationActivatesWithSwimToo", "Swim 360 animations", "Enable this if your 360 walk animations also apply to swim mode.")]
        public bool My360WalkAnimationActivatesWithSwimToo
        {
            get;
            set;
        } = true;

        [ConfigValue("TryFixLeftRightMovementClipping", "Try fix clipping on move", "When moving left or right the character shoulder will clip badly. This will attempt to fix that by moving the camera forward more when moving left or right and looking down.")]
        public float TryFixLeftRightMovementClipping
        {
            get;
            set;
        } = 15.0f;

        [ConfigValue("HidePlayerWhenColliding", "Hide player when colliding", "When you run into a wall and collide hide player? This will set the hide mode. 0 means disabled, 1 means hide normally as if you zoom very close, 2 means hide instantly.")]
        public int HidePlayerWhenColliding
        {
            get;
            set;
        } = 2;

        [ConfigValue("CameraCollisionSafety", "Camera collision safety", "Extra safety distance to add to camera collision in order for walls not to be clipped.")]
        public float CameraCollisionSafety
        {
            get;
            set;
        } = 20.0f;

        [ConfigValue("ExtraResponsiveControls", "Extra responsive controls", "Set movement controls to be extra responsive while in IFPV mode. This may feel better if you don't like the 'swaying' movement effect but it also adds some camera jerking especially when you start or stop moving.")]
        public bool ExtraResponsiveControls
        {
            get;
            set;
        } = true;

        [ConfigValue("SeparateShadowCulling", "Separate shadow culling", "Separate shadow culling from regular culling thread so that we can hide head of player but not hide the shadow of it. May have performance impact on older PCs but if you set this to false then the shadow of head will not be drawn.")]
        public bool SeparateShadowCulling
        {
            get;
            set;
        } = true;

        [ConfigValue("DisableDuringKillmove", "Disable during killmove", "Disable the IFPV camera during killmoves.")]
        public bool DisableDuringKillmove
        {
            get;
            set;
        } = false;

        [ConfigValue("WerewolfRaceName", "Werewolf race name", "Set partial name of the werewolf race. If the player race's name or editor ID has this word in it then it will activate the werewolf profile. Set empty to disable.")]
        public string WerewolfRaceName
        {
            get;
            set;
        } = "werewolf";

        [ConfigValue("WerewolfTransformationEffectId", "Effect id", "Form ID for the transformation magic effect.", ConfigEntryFlags.PreferHex)]
        public uint WerewolfTransformationEffectId
        {
            get;
            set;
        } = 0x92C45;

        [ConfigValue("WerewolfTransformationEffectFile", "Effect file", "File name for the transformation magic effect.")]
        public string WerewolfTransformationEffectFile
        {
            get;
            set;
        } = "Skyrim.esm";

        [ConfigValue("VampireLordRaceName", "Vampire lord race name", "Set partial name of the vampire lord race. If the player race's name or editor ID has this word in it then it will activate the vampire lord profile. Set empty to disable.")]
        public string VampireLordRaceName
        {
            get;
            set;
        } = "vampirebeast";

        [ConfigValue("VampireLordTransformationEffectId", "Effect id", "Form ID for the transformation magic effect.", ConfigEntryFlags.PreferHex)]
        public uint VampireLordTransformationEffectId
        {
            get;
            set;
        } = 0x283C;

        [ConfigValue("VampireLordTransformationEffectFile", "Effect file", "File name for the transformation magic effect.")]
        public string VampireLordTransformationEffectFile
        {
            get;
            set;
        } = "Dawnguard.esm";

        [ConfigValue("LichRaceName", "Lich race name", "Set partial name of the lich race. If the player race's name or editor ID has this word in it then it will activate the lich profile. Set empty to disable.")]
        public string LichRaceName
        {
            get;
            set;
        } = "lich???";

        [ConfigValue("LichTransformationEffectId", "Effect id", "Form ID for the transformation magic effect.", ConfigEntryFlags.PreferHex)]
        public uint LichTransformationEffectId
        {
            get;
            set;
        } = 0x0;

        [ConfigValue("LichTransformationEffectFile", "Effect file", "File name for the transformation magic effect.")]
        public string LichTransformationEffectFile
        {
            get;
            set;
        } = "???";

        [ConfigValue("HeadBob", "Head bob", "Add a small amount of head movement when running or walking otherwise the camera is completely stable and gliding along the ground.")]
        public bool HeadBob
        {
            get;
            set;
        } = true;

        [ConfigValue("HeadBobAmount", "Head bob amount", "If head bob is enabled there will be this much of it. Higher means more significant head bob.")]
        public float HeadBobAmount
        {
            get;
            set;
        } = 1.0f;

        #endregion

        #region Custom profile

        [ConfigValue("CustomPassengerKeyword", "Custom profile keyword", "Activate custom profile where camera position and rotation is equal to character's head. Profile is only activated if character has this keyword on them. If empty then disabled.")]
        public string CustomPassengerKeyword
        {
            get;
            set;
        } = "";

        [ConfigValue("CustomPassengerMagicKeyword", "Custom profile magic effect keyword", "Activate custom profile where camera position and rotation is equal to character's head. Profile is only activated if character has magic effect with this keyword on them. If empty then disabled.")]
        public string CustomPassengerMagicKeyword
        {
            get;
            set;
        } = "";

        [ConfigValue("CustomPassengerPositionFromHead", "Custom profile position from head", "Position from head setting while this profile is active.")]
        public float CustomPassengerPositionFromHead
        {
            get;
            set;
        } = 1.0f;

        [ConfigValue("CustomPassengerRotationFromHead", "Custom profile rotation from head", "Rotation from head setting while this profile is active.")]
        public float CustomPassengerRotationFromHead
        {
            get;
            set;
        } = 1.0f;

        [ConfigValue("CustomPassengerStabilizeHistoryDuration", "Stabilizer history duration", "How many seconds to keep node offsets in history for stabilizing the camera.")]
        public float CustomPassengerStabilizeHistoryDuration
        {
            get;
            set;
        } = 0.3f;

        [ConfigValue("CustomPassengerStabilizeIgnorePositionX", "Stabilizer position ignore X", "How much to ignore X axis movement (left/right) when stabilizing camera.")]
        public float CustomPassengerStabilizeIgnorePositionX
        {
            get;
            set;
        } = 3.0f;

        [ConfigValue("CustomPassengerStabilizeIgnorePositionY", "Stabilizer position ignore Y", "How much to ignore Y axis movement (back/forward) when stabilizing camera.")]
        public float CustomPassengerStabilizeIgnorePositionY
        {
            get;
            set;
        } = 2.5f;

        [ConfigValue("CustomPassengerStabilizeIgnorePositionZ", "Stabilizer position ignore Z", "How much to ignore Z axis movement (up/down) when stabilizing camera.")]
        public float CustomPassengerStabilizeIgnorePositionZ
        {
            get;
            set;
        } = 2.0f;

        [ConfigValue("CustomPassengerStabilizeIgnoreRotationX", "Stabilizer rotation ignore X", "How much to ignore left/right rotation when stabilizing camera. This is in degrees.")]
        public float CustomPassengerStabilizeIgnoreRotationX
        {
            get;
            set;
        } = 0.0f;

        [ConfigValue("CustomPassengerStabilizeIgnoreRotationY", "Stabilizer rotation ignore Y", "How much to ignore up/down rotation when stabilizing camera. This is in degrees.")]
        public float CustomPassengerStabilizeIgnoreRotationY
        {
            get;
            set;
        } = 0.0f;

        [ConfigValue("CustomPassengerStabilizeIgnoreOffsetX", "Stabilizer rotation offset ignore X", "How much to ignore left/right rotation offset when stabilizing camera.")]
        public float CustomPassengerStabilizeIgnoreOffsetX
        {
            get;
            set;
        } = 90.0f;

        [ConfigValue("CustomPassengerStabilizeIgnoreOffsetY", "Stabilizer rotation offset ignore Y", "How much to ignore up/down rotation offset when stabilizing camera.")]
        public float CustomPassengerStabilizeIgnoreOffsetY
        {
            get;
            set;
        } = 90.0f;

        #endregion

        #region Hiding

        [ConfigValue("HideHead", "Hide head", "Hide head when in IFPV? This should be enabled otherwise we will get strange clipping.")]
        public bool HideHead
        {
            get;
            set;
        } = true;

        [ConfigValue("HideHelmet", "Hide helmet", "Hide helmet when in IFPV? This should be enabled otherwise we will get strange clipping unless camera stabilizer is disabled.")]
        public bool HideHelmet
        {
            get;
            set;
        } = true;

        [ConfigValue("HideArms", "Hide arms", "Hide arms when in IFPV? Hide 3rd person arms even when weapon is not out?")]
        public bool HideArms
        {
            get;
            set;
        } = false;

        [ConfigValue("ShowNormalFirstPersonArms", "Show normal first person arms", "Hide 3rd person arms and show regular first person arms when in IFPV and weapon is out? This will allow you to see your hands when using weapon in IFPV.")]
        public bool ShowNormalFirstPersonArms
        {
            get;
            set;
        } = true;

        [ConfigValue("NormalFirstPersonArmsRotateRatio", "Normal first person arms rotate ratio", "This controls the multiplier of how much normal first person arms rotate when you look up and down. For example if it's 0.5 and you look 90 degrees down then your first person arms will only rotate 45 degrees down. Setting too low value may end up clipping in some cases, setting too high will look weird when you look down or up.")]
        public float NormalFirstPersonArmsRotateRatio
        {
            get;
            set;
        } = 0.8f;

        #endregion

        #region Auto turn

        [ConfigValue("AlwaysForceAutoTurn", "Always force auto turn", "Always force actor to face where you are looking.")]
        public bool AlwaysForceAutoTurn
        {
            get;
            set;
        } = false;

        [ConfigValue("ForceAutoTurnOnAngle", "Force auto turn on angle", "Force actor to face where you are looking if the angle is greater than this amount. Set 360 to disable. It can cause camera to jerk slightly.")]
        public float ForceAutoTurnOnAngle
        {
            get;
            set;
        } = 80.0f;

        [ConfigValue("ActorTurnTime", "Actor turn time", "The time it takes in seconds for an actor to do a full 360 turn when turning towards camera. Zero means instant turn. This setting does not work at the moment and should be 0 always.")]
        public float ActorTurnTime
        {
            get;
            set;
        } = 0.0f;

        [ConfigValue("ActorTurnStabilizeTime", "Actor turn stabilize time", "Add extra stabilization to camera position when suddenly turning for this many seconds. This can be helpful to get rid of the sudden jerking effect when making a large turn. Set zero to disable.")]
        public float ActorTurnStabilizeTime
        {
            get;
            set;
        } = 0.2f;

        #endregion

        #region Magic fire offsets

        [ConfigValue("MagicLeftOffsetX", "Magic offset", "The magic projectile source offset.")]
        public float MagicLeftOffsetX
        {
            get;
            set;
        } = -7.0f;

        [ConfigValue("MagicLeftOffsetY", "Magic offset", "The magic projectile source offset.")]
        public float MagicLeftOffsetY
        {
            get;
            set;
        } = 20.0f;

        [ConfigValue("MagicLeftOffsetZ", "Magic offset", "The magic projectile source offset.")]
        public float MagicLeftOffsetZ
        {
            get;
            set;
        } = -2.0f;

        [ConfigValue("MagicRightOffsetX", "Magic offset", "The magic projectile source offset.")]
        public float MagicRightOffsetX
        {
            get;
            set;
        } = 7.0f;

        [ConfigValue("MagicRightOffsetY", "Magic offset", "The magic projectile source offset.")]
        public float MagicRightOffsetY
        {
            get;
            set;
        } = 20.0f;

        [ConfigValue("MagicRightOffsetZ", "Magic offset", "The magic projectile source offset.")]
        public float MagicRightOffsetZ
        {
            get;
            set;
        } = -2.0f;

        [ConfigValue("MagicVoiceOffsetX", "Magic offset", "The magic projectile source offset.")]
        public float MagicVoiceOffsetX
        {
            get;
            set;
        } = 0.0f;

        [ConfigValue("MagicVoiceOffsetY", "Magic offset", "The magic projectile source offset.")]
        public float MagicVoiceOffsetY
        {
            get;
            set;
        } = 20.0f;

        [ConfigValue("MagicVoiceOffsetZ", "Magic offset", "The magic projectile source offset.")]
        public float MagicVoiceOffsetZ
        {
            get;
            set;
        } = -5.0f;

        #endregion

        internal static Settings Instance
        {
            get;
            private set;
        }

        /// <summary>
        /// (Re)loads this instance.
        /// </summary>
        public void Load()
        {
            ConfigFile.LoadFrom(this, "IFPV", true);
            Instance = this;
        }
    }
}
