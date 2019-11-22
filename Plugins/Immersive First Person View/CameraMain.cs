using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NetScriptFramework;
using NetScriptFramework.Skyrim;

namespace IFPV
{
    internal sealed class CameraMain
    {
        internal CameraMain(IFPVPlugin plugin)
        {
            if (plugin == null)
                throw new ArgumentNullException("plugin");

            this.Plugin = plugin;
        }

        internal readonly IFPVPlugin Plugin;

        internal CameraStack Stack
        {
            get;
            private set;
        }

        internal CameraValueMap Values
        {
            get;
            private set;
        }

        internal CameraStabilize Stabilize
        {
            get;
            private set;
        }

        internal CameraCull Cull
        {
            get;
            private set;
        }

        internal CameraHideHelper Hide
        {
            get;
            private set;
        }

        internal bool IsInitialized
        {
            get;
            private set;
        }

        internal bool IsEnabled
        {
            get;
            private set;
        }

        private CameraResult BaseHead
        {
            get;
            set;
        }

        private CameraResult BaseRoot
        {
            get;
            set;
        }

        private CameraResult BaseResult
        {
            get;
            set;
        }

        private CameraResult Offset1Result
        {
            get;
            set;
        }

        private CameraResult InputResult
        {
            get;
            set;
        }

        private CameraResult Offset2Result
        {
            get;
            set;
        }

        private CameraResult FinalResult
        {
            get;
            set;
        }

        internal CameraResult TempResult
        {
            get;
            set;
        }

        internal float LastActorTurnX
        {
            get;
            set;
        }

        internal float LastActorTurnY
        {
            get;
            set;
        }

        internal int LastActorTurnFrames
        {
            get;
            set;
        }

        internal bool WasUsingFirstPersonArms
        {
            get;
            private set;
        }

        private bool HadKey = false;
        private bool LastActorWasPlayer = false;
        private uint LastTargetFormId = 0;
        private WantStates LastWantState = WantStates.None;
        private CameraValueModifier WantMod = null;

        internal enum WantStates : int
        {
            None,

            EnabledFromTogglePOV,
            DisabledFromTogglePOV,
            EnabledFromHotkey,
            DisabledFromHotkey,
            EnabledFromZoom,
            DisabledFromZoom,
        }

        internal bool AlreadyHasWantState()
        {
            return this.GetWantFromState(this.LastWantState) > 0;
        }
        
        internal void SetWantState(WantStates state)
        {
            int curState = this.GetWantFromState(state);
            if (curState == 0)
                return;

            if (this.WantMod != null)
            {
                this.WantMod.Remove();
                this.WantMod = null;
            }
            
            int lastState = this.GetWantFromState(this.LastWantState);
            var prev = this.LastWantState;
            this.LastWantState = state;

            if (curState > 0)
                this.WantMod = this.Values.WantEnabled.AddModifier(null, CameraValueModifier.ModifierTypes.Add, 1.0, false);
            else
                this.WantMod = this.Values.WantDisabled.AddModifier(null, CameraValueModifier.ModifierTypes.Add, 1.0, false);
        }
        
        private Setting _min_zoom = null;
        private Setting _inc_zoom = null;
        private bool _init_zoom = false;

        private void _init_z()
        {
            if (this._init_zoom)
                return;
            this._init_zoom = true;

            this._min_zoom = Setting.FindSettingByName("fMinCurrentZoom:Camera", true, true);
            this._inc_zoom = Setting.FindSettingByName("fMouseWheelZoomIncrement:Camera", true, true);
        }

        private int GetWantFromState(WantStates state)
        {
            switch(state)
            {
                case WantStates.None: return 0;

                case WantStates.EnabledFromHotkey:
                    return 1;

                case WantStates.EnabledFromTogglePOV:
                case WantStates.EnabledFromZoom:
                    return Settings.Instance.ReplaceDefaultCamera ? 1 : 0;

                case WantStates.DisabledFromHotkey:
                    return -1;

                case WantStates.DisabledFromTogglePOV:
                case WantStates.DisabledFromZoom:
                    return Settings.Instance.ReplaceDefaultCamera ? -1 : 0;

                default: throw new NotImplementedException();
            }
        }

        internal long _LastTurnIsFromAutoTurn = 0;

        internal void OnMakeTurn()
        {
            if (this.Stabilize == null)
                return;

            double ftime = Settings.Instance.ActorTurnStabilizeTime;
            if (ftime <= 0.0)
                return;

            long now = this.Plugin.Time;
            if (now < this._LastTurnIsFromAutoTurn)
                ftime *= 1.5;

            var pcam = PlayerCamera.Instance;
            if (pcam == null)
                return;

            var pstate = pcam.State;
            if (pstate == null)
                return;

            var third = pstate.As<ThirdPersonState>();
            if (third == null)
                return;

            double x = Math.Abs(third.XRotationFromLastResetPoint);
            double mult = x / (Math.PI * 0.5);
            ftime *= mult;

            long ms = (long)(ftime * 1000.0);
            if (ms < 33)
                return;

            this.Stabilize.AddTweenFrom(ms, this.FinalResult.Transform.Position);
        }
        
        internal void HandleZoom(ThirdPersonState third, bool zoomIn)
        {
            if (third == null)
                return;

            this._init_z();

            if (this._min_zoom == null || this._inc_zoom == null)
                return;

            float min = this._min_zoom.GetFloat();
            float inc = this._inc_zoom.GetFloat();
            float cur = third.TargetZoomLevel;
            float next = cur + (zoomIn ? -1.0f : 1.0f) * inc;

            if(cur <= min && zoomIn)
            {
                third.TargetZoomLevel = min;
                this.SetWantState(WantStates.EnabledFromZoom);
                return;
            }

            if (next < min)
                next = min;
            else if (next > 1.0f)
                next = 1.0f;

            third.TargetZoomLevel = next;

            if (!zoomIn && this.AlreadyHasWantState())
                this.SetWantState(WantStates.DisabledFromZoom);
        }
        
        private bool CalculateEnabled(CameraUpdate update)
        {
            int keyCode = Settings.Instance.ToggleHotkey;
            if (keyCode > 0 && NetScriptFramework.Tools.Input.IsPressed((NetScriptFramework.Tools.VirtualKeys)keyCode))
            {
                if (!this.HadKey)
                {
                    this.HadKey = true;
                    if (this.IsEnabled)
                        this.SetWantState(WantStates.DisabledFromHotkey);
                    else
                        this.SetWantState(WantStates.EnabledFromHotkey);
                }
            }
            else
                this.HadKey = false;

            update.Values.WantEnabled.Update(this.Plugin.Time, this.IsEnabled);
            update.Values.WantDisabled.Update(this.Plugin.Time, this.IsEnabled);

            if (update.Values.WantDisabled.CurrentValue > 0.0 || update.Values.WantEnabled.CurrentValue <= 0.0)
                return false;

            switch(update.GameCameraState.Id)
            {
                case TESCameraStates.Free:
                case TESCameraStates.FirstPerson:
                case TESCameraStates.TweenMenu:
                case TESCameraStates.AutoVanity:
                    return false;

                case TESCameraStates.VATS:
                    {
                        if (Settings.Instance.DisableDuringKillmove)
                            return false;
                    }
                    break;
            }

            var menuManager = MenuManager.Instance;
            if (menuManager == null)
                return false;

            if (menuManager.IsMenuOpen("RaceSex Menu"))
                return false;

            return true;
        }

        internal void UpdateHeadtrack()
        {
            if (!this.LastActorWasPlayer)
                return;

            if (this.Values.HeadTrackEnabled.CurrentValue == 0)
                return;

            var plr = PlayerCharacter.Instance;
            if (plr == null)
                return;

            var camera = PlayerCamera.Instance;
            if (camera == null)
                return;

            var state = camera.State;
            if (state == null)
                return;

            var third = state.As<ThirdPersonState>();
            if (third == null)
                return;

            float fullZ = plr.Rotation.Z + third.XRotationFromLastResetPoint;
            float fullX = third.YRotationFromLastResetPoint - plr.Rotation.X;

            this.TempResult.Transform.CopyFrom(this.FinalResult.Transform);
            var rot = this.TempResult.Transform.Rotation;
            rot.Identity(1.0f);
            rot.RotateX(fullX, rot);
            rot.RotateZ(-fullZ, rot);

            var pos = this.TempResult.Transform.Position;
            var amt = this.Offset1Result.Transform.Position;
            amt.X = 0.0f;
            amt.Y = 1000.0f;
            amt.Z = 0.0f;
            this.TempResult.Transform.Translate(amt, pos);

            plr.SetLookAtPosition(pos);
        }

        internal void Initialize()
        {
            if (this.IsInitialized)
                throw new InvalidOperationException();
            this.IsInitialized = true;

#if PROFILING
            this._performance_timer.Start();
#endif

            this.Values = new CameraValueMap(this);
            this.Stack = new CameraStack(this);
            this.Cull = new CameraCull(this);
            this.Hide = new CameraHideHelper(this);

            this.BaseHead = new CameraResult();
            this.BaseRoot = new CameraResult();
            this.BaseResult = new CameraResult();
            this.Offset1Result = new CameraResult();
            this.InputResult = new CameraResult();
            this.Offset2Result = new CameraResult();
            this.FinalResult = new CameraResult();
            this.TempResult = new CameraResult();
        }

        internal bool Update(UpdateCameraEventArgs e)
        {
            if (e.Camera == null || !e.Camera.Is<PlayerCamera>())
                return false;

            var target = this.SelectTarget(e);
            if (target == null)
                return false;
            
            var update = this.SetupUpdate(e, target);
            if (update != null)
                this.DoUpdate(update);
            
            return true;
        }

        internal NiTransform LastResult
        {
            get
            {
                return this.FinalResult.Transform;
            }
        }
        
        private CameraUpdate SetupUpdate(UpdateCameraEventArgs e, CameraTarget target)
        {
            if (target == null)
                return null;

            var cameraBase = e.Camera;
            var playerCamera = cameraBase.As<PlayerCamera>();
            if (playerCamera == null)
                return null;

            var cameraNode = playerCamera.Node;
            if (cameraNode == null)
                return null;

            var cameraState = playerCamera.State;
            if (cameraState == null)
                return null;

            var update = new CameraUpdate(this, this.FinalResult, target, playerCamera, cameraNode, cameraState, this.Values);
            return update;
        }

        private CameraTarget SelectTarget(UpdateCameraEventArgs e)
        {
            var cameraBase = e.Camera;
            var playerCamera = cameraBase.As<PlayerCamera>();
            if (playerCamera == null)
                return null;

            TESObjectREFR target = null;
            uint refHandle = playerCamera.TargetRefHandle;
            using (var objRef = new ObjectRefHolder(refHandle))
            {
                if (objRef.IsValid)
                    target = objRef.Object;
            }

            var t = CameraTarget.Create(target);
            if (t == null)
                return null;

            var actor = t.Actor;
            var obj = t.Object;
            this.LastActorWasPlayer = actor != null && actor.IsPlayer;
            this.LastTargetFormId = obj != null ? obj.FormId : 0;
            
            return t;
        }

        internal void FixMouseSensitivity(ref float x, ref float y, float seconds)
        {
            if (seconds <= 0.0f)
            {
                x = 0.0f;
                y = 0.0f;
                return;
            }

            this.InitMouseSettings();

            bool enabled = this.IsEnabled;
            float sens = this._fMouseHeading != null ? this._fMouseHeading.GetFloat() : 0.0125f;
            float xsens = this._fMouseHeadingXScale != null ? this._fMouseHeadingXScale.GetFloat() : 0.02f;
            float ysens = this._fMouseHeadingYScale != null ? this._fMouseHeadingYScale.GetFloat() : 0.85f;
            float sens2 = enabled ? Settings.Instance.LookSensitivity : 1.0f;
            float xsens2 = enabled ? Settings.Instance.LookSensitivityHorizontal : 1.0f;
            float ysens2 = enabled ? Settings.Instance.LookSensitivityVertical : 1.0f;

            int fix = Settings.Instance.FixLookSensitivity;
            if (fix == 2)
                fix = enabled ? 1 : 0;

            if(fix == 1)
            {
                float mult_const = 60.0f; // 42.5f
                x *= sens * xsens * mult_const * sens2 * xsens2;
                y *= sens * ysens * sens2 * ysens2;
            }
            else
            {
                x *= (sens * xsens / seconds) * sens2 * xsens2;
                y *= sens * ysens * sens2 * ysens2;
            }

            if (this.FixSensitivityMode)
                y *= 2.0f;
        }

        private void InitMouseSettings()
        {
            if (this._fMouseSettingInit)
                return;
            this._fMouseSettingInit = true;

            this._fMouseHeading = Setting.FindSettingByName("fMouseHeadingSensitivity:Controls", true, true);
            this._fMouseHeadingXScale = Setting.FindSettingByName("fMouseHeadingXScale:Controls", true, true);
            this._fMouseHeadingYScale = Setting.FindSettingByName("fMouseHeadingYScale:Controls", true, true);
        }

        private bool _fMouseSettingInit = false;
        private Setting _fMouseHeading = null;
        private Setting _fMouseHeadingXScale = null;
        private Setting _fMouseHeadingYScale = null;

        internal void OnShadowCulling(int index)
        {
            if (this.Cull != null)
                this.Cull.OnShadowCulling(index);
        }
        
        internal void OnUpdating(int index)
        {
            if (this.Cull != null)
                this.Cull.OnUpdating(index);
        }
        
        internal bool DidCollideLastUpdate
        {
            get;
            private set;
        }
        
        private void DoUpdate(CameraUpdate update)
        {
            {
                bool wasEnabled = this.IsEnabled;
                bool isEnabled = this.CalculateEnabled(update);

                if(wasEnabled != isEnabled)
                {
                    if(!isEnabled)
                        this.Stack.DisableAll(update);

                    this.IsEnabled = isEnabled;
                    if (isEnabled)
                        this.OnEnabled(update);
                    else
                        this.OnDisabled(update);
                }
            }

            if (this.IsEnabled)
                this.OnUpdating(0);

            if (this.IsEnabled)
            {
                if (this.Stabilize == null || this.Stabilize.ShouldRecreate(update.Target))
                    this.Stabilize = new CameraStabilize(this, update.Target);

                if (this.Stabilize != null)
                    this.Stabilize.Update(update.Target.StabilizeRootNode, update.Target.HeadNode, update);
            }

            this.Stack.Check(update);
            this.Stack.Update(update);
            update.Values.Update(this.Plugin.Time, this.IsEnabled);
            this.Hide.Update(update);
            {
                bool isFpArms = this.IsEnabled && update.Values.Show1stPersonArms.CurrentValue >= 0.5;
                if(isFpArms != this.WasUsingFirstPersonArms)
                    this.WasUsingFirstPersonArms = isFpArms;
            }
            
            if (this.IsEnabled)
            {
                double mode = update.Values.SkeletonMode.CurrentValue;
                bool wantThird = true;
                if (mode <= -0.5)
                    wantThird = !this.WasUsingFirstPersonArms;
                else if (mode >= 0.5)
                    wantThird = false;
                //else wantThird = true;

                bool showFirst = this.WasUsingFirstPersonArms;
                bool showThird = true;

                if(this.DidCollideLastUpdate && Settings.Instance.HidePlayerWhenColliding == 2)
                    showThird = false;

                this.UpdateSkeleton(showFirst, showThird, wantThird);
            }

            if (this.IsEnabled)
            {
                if (this.Stabilize == null || !this.Stabilize.Get(update.Target.StabilizeRootNode, this.BaseRoot.Transform))
                    this.BaseRoot.Transform.CopyFrom(update.Target.HeadNode.WorldTransform);
                this.BaseHead.Transform.CopyFrom(update.Target.HeadNode.WorldTransform);

                CameraResult cur = null;

                // Calculate base position.
                {
                    double posRatio = update.Values.PositionFromHead.CurrentValue;
                    if (posRatio == 0.0)
                        this.BaseResult.Transform.Position.CopyFrom(this.BaseRoot.Transform.Position);
                    else if (posRatio == 1.0)
                        this.BaseResult.Transform.Position.CopyFrom(this.BaseHead.Transform.Position);
                    else
                    {
                        var pos = this.BaseResult.Transform.Position;
                        var rootPos = this.BaseRoot.Transform.Position;
                        var headPos = this.BaseHead.Transform.Position;

                        pos.X = (float)((headPos.X - rootPos.X) * posRatio + rootPos.X);
                        pos.Y = (float)((headPos.Y - rootPos.Y) * posRatio + rootPos.Y);
                        pos.Z = (float)((headPos.Z - rootPos.Z) * posRatio + rootPos.Z);
                    }
                }

                // Calculate base rotation.
                {
                    double rotRatio = update.Values.RotationFromHead.CurrentValue;
                    if (rotRatio == 0.0)
                        this.BaseResult.Transform.Rotation.CopyFrom(this.BaseRoot.Transform.Rotation);
                    else if (rotRatio == 1.0)
                        this.BaseResult.Transform.Rotation.CopyFrom(this.BaseHead.Transform.Rotation);
                    else
                    {
                        var rot = this.BaseResult.Transform.Rotation;
                        var rootRot = this.BaseRoot.Transform.Rotation;
                        var headRot = this.BaseHead.Transform.Rotation;

                        rootRot.Interpolate(headRot, (float)rotRatio, rot);
                    }
                }

                cur = this.BaseResult;

                // Calculate offset based on object rotation itself.
                {
                    var root = update.Target.RootNode;
                    if (root != null)
                    {
                        double x = this.Values.OffsetObjectPositionX.CurrentValue;
                        double y = this.Values.OffsetObjectPositionY.CurrentValue;
                        double z = this.Values.OffsetObjectPositionZ.CurrentValue;

                        if (x != 0.0 || y != 0.0 || z != 0.0)
                        {
                            this.Offset1Result.Transform.Position.CopyFrom(this.BaseResult.Transform.Position);
                            this.Offset1Result.Transform.Rotation.CopyFrom(root.WorldTransform.Rotation);
                            this.ApplyPositionOffset(this.Offset1Result.Transform, (float)x, (float)y, (float)z, this.BaseResult.Transform.Position);
                        }
                    }
                }

                // Look down offset.
                if(States.Default._look_downoffset_ratio > 0.0f || States.Default._look_downoffset_ratio_leftrightmove > 0.0f)
                {
                    float ratio = States.Default._look_downoffset_ratio;
                    var root = update.Target.RootNode;
                    if (root != null)
                    {
                        float x = Settings.Instance.DownOffsetX * ratio;
                        float y = Settings.Instance.DownOffsetY * ratio;
                        float z = Settings.Instance.DownOffsetZ * ratio;

                        y += Settings.Instance.TryFixLeftRightMovementClipping * States.Default._look_downoffset_ratio_leftrightmove;

                        if (x != 0.0f || y != 0.0f || z != 0.0f)
                        {
                            this.Offset1Result.Transform.Position.CopyFrom(this.BaseResult.Transform.Position);
                            this.Offset1Result.Transform.Rotation.CopyFrom(root.WorldTransform.Rotation);
                            this.ApplyPositionOffset(this.Offset1Result.Transform, x, y, z, this.BaseResult.Transform.Position);
                        }
                    }
                }

                // Calculate offset #1.
                {
                    float rx = (float)this.Values.Offset1RotationX.CurrentValue;
                    float ry = (float)this.Values.Offset1RotationY.CurrentValue;
                    float px = (float)this.Values.Offset1PositionX.CurrentValue;
                    float py = (float)this.Values.Offset1PositionY.CurrentValue;
                    float pz = (float)this.Values.Offset1PositionZ.CurrentValue;

                    bool hasRot = rx != 0.0f || ry != 0.0f;
                    bool hasPos = px != 0.0f || py != 0.0f || pz != 0.0f;

                    if (hasRot || hasPos)
                    {
                        this.Offset1Result.Transform.CopyFrom(cur.Transform);
                        if(hasRot)
                            this.ApplyRotationOffset(this.Offset1Result.Transform.Rotation, rx, ry, this.Offset1Result.Transform.Rotation);
                        if(hasPos)
                            this.ApplyPositionOffset(this.Offset1Result.Transform, px, py, pz, this.Offset1Result.Transform.Position);

                        cur = this.Offset1Result;
                    }
                }

                // Calculate input.
                {
                    float extraX = 0.0f;
                    float extraY = 0.0f;
                    if (this.LastActorTurnFrames > 0)
                    {
                        this.LastActorTurnFrames--;
                        extraX = this.LastActorTurnX;
                        //extraY = this.LastActorTurnY;
                    }

                    float rx = (float)(this.Values.InputRotationX.CurrentValue + extraX) * (float)this.Values.InputRotationXMultiplier.CurrentValue;
                    float ry = (float)(this.Values.InputRotationY.CurrentValue + extraY) * (float)this.Values.InputRotationYMultiplier.CurrentValue;

                    if (rx != 0.0f || ry != 0.0f)
                    {
                        this.InputResult.Transform.CopyFrom(cur.Transform);
                        this.ApplyRotationOffset(this.InputResult.Transform.Rotation, rx, ry, this.InputResult.Transform.Rotation);

                        cur = this.InputResult;
                    }
                }

                // Calculate offset #2.
                {
                    float rx = (float)this.Values.Offset2RotationX.CurrentValue;
                    float ry = (float)this.Values.Offset2RotationY.CurrentValue;
                    float px = (float)this.Values.Offset2PositionX.CurrentValue;
                    float py = (float)this.Values.Offset2PositionY.CurrentValue;
                    float pz = (float)this.Values.Offset2PositionZ.CurrentValue;

                    bool hasRot = rx != 0.0f || ry != 0.0f;
                    bool hasPos = px != 0.0f || py != 0.0f || pz != 0.0f;

                    if (hasRot || hasPos)
                    {
                        this.Offset2Result.Transform.CopyFrom(cur.Transform);
                        if(hasRot)
                            this.ApplyRotationOffset(this.Offset2Result.Transform.Rotation, rx, ry, this.Offset2Result.Transform.Rotation);
                        if(hasPos)
                            this.ApplyPositionOffset(this.Offset2Result.Transform, px, py, pz, this.Offset2Result.Transform.Position);

                        cur = this.Offset2Result;
                    }
                }

                // Apply tween from stabilize.
                {
                    if (this.Stabilize != null)
                        this.Stabilize.ApplyTween(cur.Transform.Position, this.Plugin.Time);
                }

                // Apply collision of camera so we don't go inside walls, this can be done within the same transform.
                {
                    this.DidCollideLastUpdate = CameraCollision.Apply(update, cur.Transform, cur.Transform.Position);
                }

                // Calculate final result.
                {
                    this.FinalResult.Transform.CopyFrom(cur.Transform);
                }

                update.GameCameraNode.LocalTransform.CopyFrom(this.FinalResult.Transform);
                update.GameCameraNode.Update(0.0f);

                this.Hide.UpdateFirstPersonSkeletonRotation(update);

                var third = update.GameCameraState.As<ThirdPersonState>();
                if (third != null)
                    third.Position.CopyFrom(update.GameCameraNode.LocalTransform.Position);

                if(this.WasUsingFirstPersonArms)
                    this.UpdateMagicNodePosition(update);
            }
            else
                this.DidCollideLastUpdate = false;

            if (this.IsEnabled)
                this.OnUpdating(1);

            if(!this.IsEnabled && Settings.Instance.ReplaceDefaultCamera && update.GameCameraState.Id == TESCameraStates.FirstPerson && this.IsGameCameraSwitchControlsEnabled())
            {
                update.GameCamera.EnterThirdPerson();
                this.SetWantState(WantStates.EnabledFromTogglePOV);
            }

            this.FixSensitivityMode = this.IsEnabled && update.GameCameraState.Id == TESCameraStates.ThirdPerson2 && Memory.ReadUInt8(update.GameCameraState.Address + 0xDC) != 0;
        }

        private bool FixSensitivityMode = false;

        private int? LastSkeletonParameter = null;

        internal void UpdateSkeletonWithLastParameters()
        {
            if (!this.LastSkeletonParameter.HasValue)
                return;

            int v = this.LastSkeletonParameter.Value;
            this.UpdateSkeleton((v & 1) != 0, (v & 2) != 0, (v & 4) != 0);
        }

        private void UpdateSkeleton(bool showFirst, bool showThird, bool wantThirdPersonMode)
        {
            var plr = PlayerCharacter.Instance;
            if (plr == null)
            {
                this.LastSkeletonParameter = null;
                return;
            }

            var fpSkeleton = plr.GetSkeletonNode(true);
            var tpSkeleton = plr.GetSkeletonNode(false);

            if (fpSkeleton == null || tpSkeleton == null)
            {
                this.LastSkeletonParameter = null;
                return;
            }
            
            this.LastSkeletonParameter = (showFirst ? 1 : 0) + (showThird ? 2 : 0) + (wantThirdPersonMode ? 4 : 0);

            bool isThirdPersonMode = (Memory.ReadUInt8(plr.Address + 0xBDB) & 1) != 0;
            bool isFirst = (Utility.GetNiAVFlags(fpSkeleton) & 1) == 0;
            bool isThird = (Utility.GetNiAVFlags(tpSkeleton) & 1) == 0;

            if (isFirst == showFirst && isThird == showThird && wantThirdPersonMode == isThirdPersonMode)
                return;
            
            if(wantThirdPersonMode != isThirdPersonMode)
            {
                Utility.ModNiAVFlags(fpSkeleton, 1, !wantThirdPersonMode);
                Utility.ModNiAVFlags(tpSkeleton, 1, wantThirdPersonMode);
                this.CustomSwitchSkeletonCall++;
                Memory.InvokeCdecl(this.Plugin.SwitchSkeleton, plr.Address, wantThirdPersonMode ? 0 : 1);
                this.CustomSwitchSkeletonCall--;
                Utility.ModNiAVFlags(fpSkeleton, 1, !showFirst);
                Utility.ModNiAVFlags(tpSkeleton, 1, !showThird);
                return;
            }

            if (isFirst != showFirst)
                Utility.ModNiAVFlags(fpSkeleton, 1, !showFirst);

            if (isThird != showThird)
                Utility.ModNiAVFlags(tpSkeleton, 1, !showThird);
        }

        internal void FixSpineTwist(IntPtr twistModifier)
        {
            if (!this.IsEnabled || !this.WasUsingFirstPersonArms)
                return;

            var namePtr = Memory.ReadPointer(twistModifier + 0x38);
            if (namePtr == IntPtr.Zero)
                return;

            ulong ux = Memory.ReadUInt64(namePtr);

            switch(ux)
            {
                case 0x6361747441776F42: // BowAttac -> BowAttackSpineTwistModifier
                case 0x697053636967614D: // MagicSpi -> MagicSpineTwistModifier
                case 0x70536C6175746952: // RitualSp -> RitualSpellSpineTwistModifier + RitualSpell_AimedConcentrationLoop + RitualSpell_AimedConLoop_MG
                case 0x69705374756F6853: // ShoutSpi -> ShoutSpineTwistModifier
                    {
                        Memory.WriteInt16(twistModifier + 0x64, -1);
                    }
                    break;

                /*case 0x65646F4E6B6F6F4C: // LookNode -> LookNodeRotateModifierFixed
                case 0x54746F5250747331: // 1stPRotT -> 1stPRotTwistModifier
                    break;*/
            }
        }

        internal bool IsGameCameraSwitchControlsEnabled()
        {
            var controls = PlayerControls.Instance;
            if (controls == null)
                return false;

            return Memory.InvokeCdecl(this.Plugin.PlayerControls_IsCamSwitchControlsEnabled, controls.Address).ToBool();
        }

        private void OnEnabled(CameraUpdate update)
        {
            this.LastActorTurnFrames = 0;
        }

        private void OnDisabled(CameraUpdate update)
        {
            this.UpdateSkeleton(this.GameWantsSkeletonMode > 0, this.GameWantsSkeletonMode < 0, this.GameWantsSkeletonMode < 0);
        }

        internal bool HookSwitchSkeleton(Actor actor, bool firstPerson)
        {
            if (actor == null || !actor.IsPlayer || this.CustomSwitchSkeletonCall > 0)
                return false;

            this.GameWantsSkeletonMode = firstPerson ? 1 : -1;

            if (!this.IsEnabled)
                return false;

            return true;
        }

        private int GameWantsSkeletonMode = 0;
        private int CustomSwitchSkeletonCall = 0;

        internal bool GetOverwriteWeaponNode(TESForm obj, NiPoint3 pt)
        {
            if (!this.IsEnabled)
                return false;

            if (obj == null || obj.FormId != this.LastTargetFormId)
                return false;

            var pcam = PlayerCamera.Instance;
            if (pcam == null)
                return false;

            var pn = pcam.Node;
            if (pn == null)
                return false;

            var pos = pn.WorldTransform.Position;
            pt.X = pos.X;
            pt.Y = pos.Y;
            pt.Z = pos.Z - 10.0f;
            return true;
        }

        internal NiAVObject GetOverwriteMagicNode(MagicCaster caster)
        {
            if (!this.IsEnabled)
                return null;

            if (caster == null)
                return null;

            var actorCaster = caster.As<ActorMagicCaster>();
            if (actorCaster == null)
                return null;

            var actor = actorCaster.Owner;
            if (actor == null || actor.FormId != this.LastTargetFormId)
                return null;
            
            this.InitMagicNode();

            if (this.MagicNodes == null)
                return null;

            switch(actorCaster.ActorCasterType)
            {
                case EquippedSpellSlots.LeftHand: return this.MagicNodes[0];
                case EquippedSpellSlots.RightHand: return this.MagicNodes[1];
                case EquippedSpellSlots.Other: return this.MagicNodes[2];
            }

            return null;
        }

        internal void UpdateMagicNodePosition(CameraUpdate update)
        {
            this.InitMagicNode();

            if (this.MagicNodes == null)
                return;

            //var actor = update.Target.Actor;

            for(int i = 0; i < this.MagicNodes.Length; i++)
            {
                var node = this.MagicNodes[i];
                var wt = node.WorldTransform;

                // This can't be used because the offsets don't match up when any scaling is involved.
                /*if (actor != null)
                {
                    if (i == 0)
                    {
                        var mroot = actor.GetSkeletonNode(true);
                        if(mroot != null)
                        {
                            var mnode = mroot.LookupNodeByName("NPC L Hand [LHnd]");
                            if(mnode != null)
                            {
                                wt.Rotation.CopyFrom(this.FinalResult.Transform.Rotation);
                                wt.Position.CopyFrom(mnode.WorldTransform.Position);
                                continue;
                            }
                        }
                    }
                    else if (i == 1)
                    {
                        var mroot = actor.GetSkeletonNode(true);
                        if (mroot != null)
                        {
                            var mnode = mroot.LookupNodeByName("NPC R Hand [RHnd]");
                            if (mnode != null)
                            {
                                wt.Rotation.CopyFrom(this.FinalResult.Transform.Rotation);
                                wt.Position.CopyFrom(mnode.WorldTransform.Position);
                                continue;
                            }
                        }
                    }
                }*/

                {
                    wt.CopyFrom(this.FinalResult.Transform);
                    wt.Translate(this.MagicTranslates[i], wt.Position);
                }
            }
        }

        private void InitMagicNode()
        {
            if (this.MagicNodeAllocation != null)
                return;

            int count = 3;
            int size = 0x130;
            int size2 = 0x10;
            this.MagicNodeAllocation = Memory.Allocate(size * count + size2 * count);
            this.MagicNodes = new NiNode[count];
            this.MagicTranslates = new NiPoint3[count];
            var s = Settings.Instance;
            for (int i = 0; i < count; i++)
            {
                this.MagicNodes[i] = MemoryObject.FromAddress<NiNode>(this.MagicNodeAllocation.Address + size * i);
                Memory.InvokeCdecl(this.Plugin.NiNode_ctor, this.MagicNodes[i].Address, 0);
                this.MagicNodes[i].IncRef();

                this.MagicTranslates[i] = MemoryObject.FromAddress<NiPoint3>(this.MagicNodeAllocation.Address + size * count + size2 * i);
                switch (i)
                {
                    case 0:
                        this.MagicTranslates[i].X = s.MagicLeftOffsetX;
                        this.MagicTranslates[i].Y = s.MagicLeftOffsetY;
                        this.MagicTranslates[i].Z = s.MagicLeftOffsetZ;
                        break;

                    case 1:
                        this.MagicTranslates[i].X = s.MagicRightOffsetX;
                        this.MagicTranslates[i].Y = s.MagicRightOffsetY;
                        this.MagicTranslates[i].Z = s.MagicRightOffsetZ;
                        break;

                    case 2:
                        this.MagicTranslates[i].X = s.MagicVoiceOffsetX;
                        this.MagicTranslates[i].Y = s.MagicVoiceOffsetY;
                        this.MagicTranslates[i].Z = s.MagicVoiceOffsetZ;
                        break;

                    default:
                        this.MagicTranslates[i].X = 0.0f;
                        this.MagicTranslates[i].Y = 0.0f;
                        this.MagicTranslates[i].Z = 0.0f;
                        break;
                }
            }
        }

        private MemoryAllocation MagicNodeAllocation = null;
        private NiNode[] MagicNodes = null;
        private NiPoint3[] MagicTranslates = null;

        private void ApplyRotationOffset(NiMatrix33 matrix, float x, float y, NiMatrix33 result)
        {
            if(x == 0.0f && y == 0.0f)
            {
                if(!result.Equals(matrix))
                    result.CopyFrom(matrix);
                return;
            }

            var rot = this.TempResult.Transform.Rotation;
            rot.Identity(1.0f);

            if (y != 0.0f)
                rot.RotateX(y, rot);

            if (x != 0.0f)
                rot.RotateZ(-x, rot);

            matrix.Multiply(rot, result);
        }

        private void ApplyPositionOffset(NiTransform transform, float x, float y, float z, NiPoint3 result)
        {
            if(x == 0.0f && y == 0.0f && z == 0.0f)
            {
                var tpos = transform.Position;
                if (!result.Equals(tpos))
                    result.CopyFrom(tpos);
                return;
            }

            var pos = this.TempResult.Transform.Position;
            pos.X = x;
            pos.Y = y;
            pos.Z = z;
            transform.Translate(pos, result);
        }

        internal void HandleActorTurnToCamera(Actor actor, ThirdPersonState third, bool fromFreeLookChanged)
        {
            if (third == null || actor == null)
                return;

            double x = third.XRotationFromLastResetPoint;
            double y = third.YRotationFromLastResetPoint;
            double didx = 0.0;
            double didy = 0.0;

            if (x == 0.0 && y == 0.0)
                return;

            double max = 0.0;
            double diff = this.Plugin._lastDiff2;
            double time = this.Values.ActorTurnTime.CurrentValue;

            if (time <= 0.0)
                max = Math.PI * 2.0;
            else if (diff >= 1.0)
                max = (diff * 0.001) / time * Math.PI * 2.0;

            // Turn left or right.
            if(x != 0.0)
            {
                double actual = x;
                if(Math.Abs(actual) > max)
                {
                    if (actual < 0.0)
                        actual = -max;
                    else
                        actual = max;
                }

                Memory.InvokeCdecl(this.Plugin.ActorTurnZ, actor.Address, (float)actual);
                if (actual == x)
                    third.XRotationFromLastResetPoint = 0.0f;
                else
                    third.XRotationFromLastResetPoint -= (float)actual;

                didx = actual;
            }

            // Turn up or down.
            if(y != 0.0)
            {
                double actual = y;
                Memory.InvokeCdecl(this.Plugin.ActorTurnX, actor.Address, -(float)actual);
                third.YRotationFromLastResetPoint = 0.0f;

                didy = actual;
            }

            // Fix visual error with turning.
            if(fromFreeLookChanged)
            {
                int duration = 1;
                if (this.IsEnabled && this.LastActorTurnFrames < duration)
                {
                    this.LastActorTurnX = (float)didx;
                    this.LastActorTurnY = (float)didy;
                    this.LastActorTurnFrames = duration;
                }
            }
        }

#if PROFILING
        internal enum _performance_track : int
        {
            Frame,
            CameraUpdate,

            Max
        }

        private long[] _performance_ticks = new long[(int)_performance_track.Max];
        private long[] _performance_begin = new long[(int)_performance_track.Max];
        private int[] _performance_times = new int[(int)_performance_track.Max];
        private int[] _performance_counters = new int[(int)_performance_track.Max];
        private System.Diagnostics.Stopwatch _performance_timer = new System.Diagnostics.Stopwatch();
        internal int _prof_state = 0;

        internal void begin_track(_performance_track type)
        {
            int i = (int)type;
            if (++this._performance_counters[i] != 1)
                return;

            this._performance_begin[i] = this._performance_timer.ElapsedTicks;
        }

        internal void end_track(_performance_track type)
        {
            int i = (int)type;
            if (--this._performance_counters[i] != 0)
                return;

            long now = this._performance_timer.ElapsedTicks;
            this._performance_ticks[i] += now - this._performance_begin[i];
            this._performance_times[i]++;
        }

        internal void _end_profiling()
        {
            using (var f = new System.IO.StreamWriter("SkyrimSE_IFPV_Profiling.txt", false))
            {
                f.Write(string.Format("{0,-20}", "Type"));
                long msdiv = System.Diagnostics.Stopwatch.Frequency / 1000;
                f.Write(string.Format("{0,10}", "Total"));
                f.Write(string.Format("{0,10}", "Times"));
                f.Write(string.Format("{0,10}", "Average"));
                f.WriteLine();

                for (int i = 0; i < (int)_performance_track.Max; i++)
                {
                    f.Write(string.Format("{0,-20}", ((_performance_track)i).ToString()));
                    f.Write(string.Format("{0,10}", this._performance_ticks[i] / msdiv));
                    f.Write(string.Format("{0,10}", this._performance_times[i]));
                    double avg = 0.0;
                    if (_performance_times[i] > 0)
                        avg = (double)(_performance_ticks[i] / msdiv) / (double)_performance_times[i];
                    f.Write(string.Format("{0,10}", avg.ToString("0.0000", System.Globalization.CultureInfo.InvariantCulture)));
                    f.WriteLine();
                }
            }

            NetScriptFramework.Skyrim.MenuManager.ShowHUDMessage("Stopped profiling IFPV.", null, true);
        }
#endif
    }
}
