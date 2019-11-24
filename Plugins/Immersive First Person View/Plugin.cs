using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NetScriptFramework;
using NetScriptFramework.SkyrimSE;

namespace IFPV
{
    public sealed class IFPVPlugin : Plugin
    {
        public override string Key
        {
            get
            {
                return "ifpv";
            }
        }

        public override string Name
        {
            get
            {
                return "Immersive First Person View";
            }
        }

        public override int Version
        {
            get
            {
                return 6;
            }
        }

        public override string Author
        {
            get
            {
                return "meh321";
            }
        }

        public override string Website
        {
            get
            {
                return "https://www.nexusmods.com/skyrimspecialedition/mods/22306";
            }
        }

        public Settings Settings
        {
            get;
            private set;
        }
        
        public long Time
        {
            get
            {
                return System.Threading.Interlocked.Read(ref _time);
            }
            private set
            {
                System.Threading.Interlocked.Exchange(ref _time, value);
            }
        }
        private long _time = 0;
        private long _lastTimer = 0;
        private long _lastDiff = 0;
        internal long _lastDiff2
        {
            get;
            private set;
        }

        private NetScriptFramework.Tools.Timer Timer = null;

        internal static IFPVPlugin Instance
        {
            get;
            private set;
        }
        
        protected override bool Initialize(bool loadedAny)
        {
            var game = NetScriptFramework.Main.Game;
            var debug = CrashLog.Debug;
            if (game == null || game.LibraryVersion < 10)
                throw new InvalidOperationException(this.Name + " requires a newer version of .NET Script Framework!");
            if (debug == null)
                throw new InvalidOperationException(this.Name + " can not run without the debug library!");

            Instance = this;
            this.init();

            return true;
        }

        private bool WasGamePaused = false;
        
        internal IntPtr PlayerControls_IsCamSwitchControlsEnabled
        {
            get;
            private set;
        }

        internal IntPtr NiNode_ctor
        {
            get;
            private set;
        }
        
        private IntPtr MagicNodeArt1;
        private IntPtr MagicNodeArt2;
        private IntPtr MagicNodeArt3;
        private IntPtr MagicNodeArt4;

        internal IntPtr ActorTurnX
        {
            get;
            private set;
        }

        internal IntPtr ActorTurnZ
        {
            get;
            private set;
        }

        internal IntPtr SwitchSkeleton
        {
            get;
            private set;
        }

        internal IntPtr Actor_GetMoveDirection
        {
            get;
            private set;
        }

        internal CameraMain CameraMain
        {
            get;
            private set;
        }

        private void init()
        {
            // Setup GameOffset - Updated PrepareFunction & InstallHook to take this value, I didn't update directly incase some use a different Offset.
            int GameOffset = 0x0; // Everything is based from 1_5_62
            var GameVersion = NetScriptFramework.Main.Game.GameVersion; // Get the game version
            if (GameVersion[0] == 1 && GameVersion[1] == 5 && GameVersion[2] >= 73 && GameVersion[2] <= 97) GameOffset = 0x1F0; // Check for game version 1_5_73 to 1_5_97, update GameOffset

            this.Timer = new NetScriptFramework.Tools.Timer();
            this.Timer.Start();

            this.Settings = new Settings();
            this.Settings.Load();

            this.PlayerControls_IsCamSwitchControlsEnabled = this.PrepareFunction("player camera switch controls check", 41263, 0, GameOffset);
            if (GameVersion[0] == 1 && GameVersion[1] == 5 && GameVersion[2] >= 73 && GameVersion[2] <= 80)
                this.NiNode_ctor = this.PrepareFunction("ninode ctor", 68936, 0, GameOffset);
            
            if (GameVersion[0] == 1 && GameVersion[1] == 5 && GameVersion[2] == 97)
                this.NiNode_ctor = this.PrepareFunction("ninode ctor", 68936, 0, -0x2C0);

            this.MagicNodeArt1 = this.PrepareFunction("magic node art 1", 33403, 0x6F, GameOffset);
            this.MagicNodeArt2 = this.PrepareFunction("magic node art 2", 33391, 0x64, GameOffset);
            this.MagicNodeArt3 = this.PrepareFunction("magic node art 3", 33375, 0xF5, GameOffset);
            this.MagicNodeArt4 = this.PrepareFunction("magic node art 4", 33683, 0x63, GameOffset);
            this.ActorTurnX = this.PrepareFunction("actor turn x", 36603, 0, GameOffset);
            this.ActorTurnZ = this.PrepareFunction("actor turn z", 36250, 0, GameOffset);
            this.SwitchSkeleton = this.PrepareFunction("switch skeleton", 39401, 0, GameOffset);
            this.Actor_GetMoveDirection = this.PrepareFunction("actor move direction", 36935, 0, GameOffset);

            this.CameraMain = new CameraMain(this);

            Events.OnFrame.Register(e =>
            {
                var main = NetScriptFramework.SkyrimSE.Main.Instance;
                if (main != null)
                {
#if PROFILING
                    if (this.CameraMain._prof_state == 1)
                    {
                        this.CameraMain.end_track(CameraMain._performance_track.Frame);
                        this.CameraMain.begin_track(CameraMain._performance_track.Frame);
                    }
#endif

                    bool paused = main.IsGamePaused;
                    bool anyPaused = paused;
                    if (paused != this.WasGamePaused)
                    {
                        anyPaused = true;
                        this.WasGamePaused = paused;
                    }

                    long now = this.Timer.Time;
                    this._lastDiff = 0;
                    if (!anyPaused)
                    {
                        long diff = now - this._lastTimer;
                        if (diff > 200)
                            diff = 200;
                        this.Time += diff;
                        this._lastDiff = diff;
                    }
                    this._lastTimer = now;
                    this._lastDiff2 = this._lastDiff;
                }
            });

            Events.OnMainMenu.Register(e =>
            {
                if (this.CameraMain != null && !this.CameraMain.IsInitialized)
                    this.CameraMain.Initialize();
            }, 0, 1);

            Events.OnUpdateCamera.Register(e =>
            {
                if (this.CameraMain != null && this.CameraMain.IsInitialized)
                {
#if PROFILING
                    if (this.CameraMain._prof_state == 1)
                        this.CameraMain.begin_track(CameraMain._performance_track.CameraUpdate);
#endif

                    bool ok;
                    if (!(ok = this.CameraMain.Update(e)))
                    {
                        if (this._lastDiff > 0)
                        {
                            this.Time -= this._lastDiff;
                            this._lastDiff = 0;
                        }
                    }

#if PROFILING
                    if (this.CameraMain._prof_state == 1)
                        this.CameraMain.end_track(CameraMain._performance_track.CameraUpdate);
#endif

#if PROFILING
                    if (ok && this.CameraMain._prof_state == 0)
                    {
                        this.CameraMain._prof_state = 1;
                        this.CameraMain.begin_track(CameraMain._performance_track.Frame);
                    }
                    else if (this.CameraMain._prof_state == 1 && NetScriptFramework.Tools.Input.IsPressed(NetScriptFramework.Tools.VirtualKeys.N9))
                    {
                        this.CameraMain._prof_state = 2;
                        this.CameraMain._end_profiling();
                    }
#endif
                }
            }, 1000);

            Events.OnUpdatedPlayerHeadtrack.Register(e =>
            {
                if (this.CameraMain != null && this.CameraMain.IsInitialized)
                    this.CameraMain.UpdateHeadtrack();
            }, 50);

            Events.OnUpdatePlayerTurnToCamera.Register(e =>
            {
                if (this.CameraMain != null && this.CameraMain.IsInitialized)
                {
                    double value = this.CameraMain.Values.FaceCamera.CurrentValue;
                    if (value >= 1.0)
                        e.FreeLook = false;
                    else if (value <= -1.0)
                        e.FreeLook = true;

                    bool isFree = e.FreeLook;
                    if (_had_free_look != isFree)
                    {
                        _had_free_look = isFree;
                        if (!isFree && this.CameraMain.IsEnabled)
                            this.CameraMain.OnMakeTurn();
                    }
                }
            }, 50);

            Events.OnShadowCullingBegin.Register(e =>
            {
                if (this.CameraMain != null && this.CameraMain.IsInitialized && this.CameraMain.IsEnabled && Settings.SeparateShadowCulling)
                {
                    e.Separate = true;
                    this.CameraMain.OnShadowCulling(0);
                }
            }, 1000);

            Events.OnShadowCullingEnd.Register(e =>
            {
                if (this.CameraMain != null && this.CameraMain.IsInitialized && this.CameraMain.IsEnabled && Settings.SeparateShadowCulling)
                    this.CameraMain.OnShadowCulling(1);
            }, 1000);

            Events.OnWeaponFireProjectilePosition.Register(e =>
            {
                if (this.CameraMain != null && this.CameraMain.IsInitialized)
                {
                    var obj = e.Attacker;
                    bool did = this.CameraMain.GetOverwriteWeaponNode(obj, e.Position);

                    if (did)
                        e.Node = null;
                }
            });

            this.InstallHook("magic fire node art", 33361, 0x7E, 7, "41 FF 90 78 03 00 00", GameOffset, ctx =>
            {
                if (this.CameraMain == null || !this.CameraMain.IsInitialized || !this.CameraMain.WasUsingFirstPersonArms)
                    return;

                var caster = MemoryObject.FromAddress<MagicCaster>(ctx.DI);
                var node = this.CameraMain.GetOverwriteMagicNode(caster);
                if (node != null)
                    ctx.DX = new IntPtr((long)1);
            });

            this.InstallHook("magic fire node", 33361, 0, 6, "40 57 48 83 EC 20", GameOffset, ctx =>
            {
                if (this.CameraMain == null || !this.CameraMain.IsInitialized || !this.CameraMain.WasUsingFirstPersonArms)
                    return;

                IntPtr calledFrom = Memory.ReadPointer(ctx.SP);
                if (calledFrom == this.MagicNodeArt1 || calledFrom == this.MagicNodeArt2 || calledFrom == this.MagicNodeArt3 || calledFrom == this.MagicNodeArt4)
                    return;

                var node = this.CameraMain.GetOverwriteMagicNode(MemoryObject.FromAddress<MagicCaster>(ctx.CX));
                if (node == null)
                    return;

                ctx.Skip();
                ctx.IP = ctx.IP + 0x2D;
                ctx.AX = node.Address;
            });

            // Block character model fading out
            this.InstallHook("block fade out", 49899, 0x3C, 6, "4C 8B F2 48 8B F9", GameOffset, ctx =>
            {
                if (this.CameraMain != null && this.CameraMain.IsInitialized && this.CameraMain.Values.BlockPlayerFadeOut.CurrentValue >= 0.5)
                {
                    if (Settings.Instance.HidePlayerWhenColliding != 1 || !this.CameraMain.DidCollideLastUpdate)
                        ctx.R13 = new IntPtr(0);
                }
            });

            // Overwrite the turn part
            this.InstallHook("actor turn overwrite", 49968, 0xBB, 0x2E, "F3 0F 10 8B D4 00 00 00", GameOffset, ctx =>
            {
                var third = MemoryObject.FromAddress<ThirdPersonState>(ctx.BX);
                var actor = MemoryObject.FromAddress<Actor>(ctx.AX);

                if (this.CameraMain != null && this.CameraMain.IsInitialized)
                    this.CameraMain.HandleActorTurnToCamera(actor, third, true);

                ctx.IP = ctx.IP + 0x10;
            }, null, true);

            if (Settings.Instance.ReplaceDefaultCamera)
            {
                // Make sure we always use the custom code instead of allowing min zoom to enter first person.
                this.InstallHook("replace zoom #1", 49970, 0x1E1, 5, "E8", GameOffset, null, ctx =>
                {
                    ctx.AX = IntPtr.Zero;
                });

                // Custom zoom
                this.InstallHook("replace zoom #1", 49970, 0x22F, 7, "48 8B 8B E8 01 00 00", GameOffset, ctx =>
                {
                    IntPtr cptr = Memory.ReadPointer(ctx.AX);
                    IntPtr dptr = Memory.ReadPointer(ctx.BX + 0x1E8);
                    var third = MemoryObject.FromAddressSafeCast<ThirdPersonState>(ctx.DI);

                    if (this.CameraMain != null && this.CameraMain.IsInitialized && third != null)
                        this.CameraMain.HandleZoom(third, cptr == dptr);

                    ctx.Skip();
                    ctx.IP = ctx.IP + 0x40;
                });

                // Dragon and horse must use regular toggle pov handler
                {
                    var ptr = PrepareFunction("dragon toggle pov", 32363, 0x1F, GameOffset);
                    if (!Memory.VerifyBytes(ptr, "74 52", true))
                        throw new InvalidOperationException("Couldn't verify byte pattern for 'dragon toggle pov'!");
                    Memory.WriteUInt8(ptr, 0xEB, true);
                    ptr = PrepareFunction("horse toggle pov", 49832, 0x1F, GameOffset);
                    if (!Memory.VerifyBytes(ptr, "74 52", true))
                        throw new InvalidOperationException("Couldn't verify byte pattern for 'horse toggle pov'!");
                    Memory.WriteUInt8(ptr, 0xEB, true);
                }

                // Don't toggle pov from zoom delayed parameter
                {
                    var ptr = PrepareFunction("zoom delayed toggle pov", 49977, 0x291, GameOffset);
                    if (!Memory.VerifyBytes(ptr, "74 1C", true))
                        throw new InvalidOperationException("Couldn't verify byte pattern for 'zoom delayed toggle pov'!");
                    Memory.WriteUInt8(ptr, 0xEB, true);
                }

                // Toggle POV hotkey was pressed
                this.InstallHook("toggle pov", 49970, 0xD5, 5, "E8", GameOffset, null, ctx =>
                {
                    // Skip default action
                    ctx.AX = new IntPtr((long)0);

                    if (this.CameraMain != null && this.CameraMain.IsInitialized)
                        this.CameraMain.SetWantState(this.CameraMain.AlreadyHasWantState() ? CameraMain.WantStates.DisabledFromTogglePOV : CameraMain.WantStates.EnabledFromTogglePOV);
                });

                // Replace forced first person mode from papyrus or other scripted events.
                this.InstallHook("replace first person", 49858, 0, 6, "40 53 48 83 EC 20", GameOffset, ctx =>
                {
                    if (this.CameraMain == null || !this.CameraMain.IsInitialized)
                        return;

                    IntPtr calledFrom = Memory.ReadPointer(ctx.SP);
                    ulong vid = 0;
                    if (!_fp_called.TryGetValue(calledFrom, out vid))
                    {
                        var fn = CrashLog.Debug.GetFunctionInfo(calledFrom, true);
                        if (fn != null)
                            vid = fn.Id;

                        _fp_called[calledFrom] = vid;
                    }

                    bool skip = false;
                    bool want = false;

                    switch (vid)
                    {
                        case 22463: // Console command
                        case 43115: // Forced by game scripted camera
                            break;

                        case 43098: // Some kind of VATS thing?
                            skip = true;
                            //want = true;
                            break;

                        case 49880: // Piece of furniture had a keyword on it
                            skip = true;
                            //want = true;
                            break;

                        default: // Other, this usually is controlled by papyrus or other script event
                            // Must let it happen otherwise Solstheim boat ride is bugged and some other stuff too probably.
                            // It's fine because if camswitch is enabled IFPV will re-enable itself anyway.
                            break;
                    }

                    if (skip)
                    {
                        ctx.Skip();
                        ctx.IP = ctx.IP + 0x39;
                    }

                    if (want && !this.CameraMain.AlreadyHasWantState())
                        this.CameraMain.SetWantState(CameraMain.WantStates.EnabledFromTogglePOV);
                });
            }

            this.InstallHook("fix crosshair pick", 39534, 0x159, 10, "F3 0F 58 45 E8 F3 0F 11 45 D8", GameOffset, ctx =>
            {
                if (this.CameraMain != null && this.CameraMain.IsInitialized && this.CameraMain.IsEnabled)
                {
                    var pt = MemoryObject.FromAddress<NiPoint3>(ctx.BP - 0x30);
                    var pcam = PlayerCamera.Instance;
                    if (pcam != null)
                    {
                        ctx.Skip();

                        pt.CopyFrom(pcam.LastNodePosition);
                    }
                }
            });

            this.InstallHook("fix look sensitivity", 41275, 0x38D, 0xE, "75 0E", GameOffset, ctx =>
            {
                if (this.CameraMain != null && this.CameraMain.IsInitialized)
                {
                    float x = Memory.ReadFloat(ctx.BX);
                    float y = Memory.ReadFloat(ctx.BX + 4);
                    this.CameraMain.FixMouseSensitivity(ref x, ref y, ctx.XMM1f);
                    Memory.WriteFloat(ctx.BX, x);
                    Memory.WriteFloat(ctx.BX + 4, y);
                }
            }, null, true);

            this.InstallHook("switch skeleton override", 39401, 0, 7, "40 55 56 48 83 EC 78", GameOffset, ctx =>
            {
                if (this.CameraMain != null && this.CameraMain.IsInitialized)
                {
                    if (this.CameraMain.HookSwitchSkeleton(MemoryObject.FromAddress<Actor>(ctx.CX), ctx.DX.ToBool()))
                    {
                        ctx.Skip();
                        ctx.IP = ctx.IP + 0x2DD;
                    }
                }
            });

            this.InstallHook("fix bound node update", 18683, 0x7C, 6, "FF 90 68 04 00 00", GameOffset, ctx =>
            {
                if (this.CameraMain != null && this.CameraMain.IsInitialized && this.CameraMain.IsEnabled)
                {
                    ctx.Skip();
                    var obj = MemoryObject.FromAddress<TESObjectREFR>(ctx.CX);
                    var node = obj.GetSkeletonNode(false);
                    ctx.AX = node != null ? node.Address : IntPtr.Zero;
                }
            });

            this.InstallHook("fix spine twist", 59246, 0x75, 5, "48 83 C4 20 5F", GameOffset, ctx =>
            {
                if (this.CameraMain != null && this.CameraMain.IsInitialized
                && System.Threading.Interlocked.CompareExchange(ref _is_spine, 0, 0) > 0
                )
                    this.CameraMain.FixSpineTwist(ctx.DI);
            });

            this.InstallHook("player update animation", 39445, 0x97, 5, "E8", GameOffset, ctx =>
            {
                System.Threading.Interlocked.Increment(ref _is_spine);
            },
            ctx =>
            {
                System.Threading.Interlocked.Decrement(ref _is_spine);
            });
            this.InstallHook("player control inc counter", 41259, 0, 5, "48 89 5C 24 08", GameOffset, ctx =>
            {
                System.Threading.Interlocked.Increment(ref _is_spine);
            });

            this.InstallHook("player controls dec counter", 41259, 0x241, 5, "48 83 C4 30 5F", GameOffset, ctx =>
            {
                System.Threading.Interlocked.Decrement(ref _is_spine);
            });

            this.InstallHook("player movement controller type", 40937, 0x2EA, 6, "FF 90 88 03 00 00", GameOffset, null, ctx =>
            {
                if (this.CameraMain != null && this.CameraMain.IsInitialized)
                {
                    if (this.CameraMain.Values.ExtraResponsiveControls.CurrentValue >= 0.5)
                        ctx.AX = IntPtr.Zero;
                }
            });

            this.InstallHook("before draw", 35560, 0x199, 7, "83 8F F4 00 00 00 01", GameOffset, ctx =>
            {
                if (this.CameraMain != null && this.CameraMain.IsInitialized && this.CameraMain.IsEnabled)
                    this.CameraMain.UpdateSkeletonWithLastParameters();
            });
        }
        
        private Dictionary<IntPtr, ulong> _fp_called = new Dictionary<IntPtr, ulong>();
        private bool _had_free_look = true;
        private int _is_spine = 0;

        private void InstallHook(string name, ulong vid, int offset, int length, string hex, int addrOffset, Action<CPURegisters> func, Action<CPURegisters> after = null, bool skip = false)
        {
            var fn = CrashLog.Debug.GetFunctionInfo(vid);

            if (fn == null)
                throw new InvalidOperationException(this.Name + " couldn't find '" + name + "' function in debug library! Plugin must be updated manually.");

            IntPtr addr = new IntPtr( (long)((CrashLog.Debug.BaseOffset + fn.Begin + (uint)offset) - (uint)addrOffset) );
            String strAddress = fn.ShortName;
            if (!string.IsNullOrEmpty(hex) && !Memory.VerifyBytes(addr, hex))
                throw new InvalidOperationException(this.Name + " couldn't match function '" + name + "' bytes! Plugin must be updated manually or there is a conflict with another plugin. " + strAddress);

            Memory.WriteHook(new HookParameters()
            {
                Address = addr,
                IncludeLength = skip ? 0 : length,
                ReplaceLength = length,
                Before = func,
                After = after
            });
        }

        private IntPtr PrepareFunction(string name, ulong vid, int offset, int addrOffset)
        {
            var fn = CrashLog.Debug.GetFunctionInfo(vid);

            if (fn == null)
                throw new InvalidOperationException(this.Name + " couldn't find '" + name + "' function in debug library! Plugin must be updated manually.");

            return new IntPtr( (long)((CrashLog.Debug.BaseOffset + fn.Begin + (ulong)offset) - (ulong)addrOffset) );
        }
    }
}
