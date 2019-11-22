using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IFPV.States
{
    abstract class Moving : CameraState
    {
        internal override int Priority
        {
            get
            {
                return (int)Priorities.Moving;
            }
        }

        internal protected abstract int IsDirection
        {
            get;
        }

        internal override bool Check(CameraUpdate update)
        {
            if (!update.CameraMain.IsEnabled)
                return false;

            if (update.CachedMounted)
                return false;

            _update_check(update);
            return _move_dir == IsDirection;
        }

        internal static int _move_dir
        {
            get;
            private set;
        } = -1;
        private static long _move_update = -1;

        private static void _update_check(CameraUpdate update)
        {
            long now = update.CameraMain.Plugin.Time;
            if (now == _move_update)
                return;
            _move_update = now;

            var actor = update.Target.Actor;
            if(actor == null)
            {
                _move_dir = -1;
                return;
            }
            
            uint moveFlags = NetScriptFramework.Memory.ReadUInt32(actor.Address + 0xC0) & 0x3FFF;
            uint mask = 0xCF;

            if ((moveFlags & mask) == 0)
            {
                _move_dir = -1;
                return;
            }
            
            double dir = NetScriptFramework.Memory.InvokeCdeclF(update.CameraMain.Plugin.Actor_GetMoveDirection, actor.Address);
            double pi = Math.PI;
            dir = dir + pi;
            dir %= pi * 2.0;

            dir = Utility.RadToDeg(dir);
            dir -= 180.0;

            if(dir >= -22.5 && dir < 22.5)
            {
                _move_dir = 0;
                return;
            }

            if(dir >= 22.5 && dir < 67.5)
            {
                _move_dir = 1;
                return;
            }

            if (dir >= 67.5 && dir < 112.5)
            {
                _move_dir = 2;
                return;
            }

            if (dir >= 112.5 && dir < 157.5)
            {
                _move_dir = 3;
                return;
            }

            if (dir >= 157.5 || dir < -157.5)
            {
                _move_dir = 4;
                return;
            }

            if(dir >= -157.5 && dir < -112.5)
            {
                _move_dir = 5;
                return;
            }

            if (dir >= -112.5 && dir < -67.5)
            {
                _move_dir = 6;
                return;
            }

            if (dir >= -67.5 && dir < -22.5)
            {
                _move_dir = 7;
                return;
            }

            // Some fraction error?
            _move_dir = 0;

            /*
            -0.79   0   0.79

            -1.57       1.57

            -2.36   pi  2.36
            */
        }

        protected void Enter_Forwards(CameraUpdate update, bool diagonal)
        {

        }

        protected void Enter_Backwards(CameraUpdate update, bool diagonal)
        {
            if(Settings.Instance.Enable360WalkAnimationCompatibilityMode)
            {
                bool ok = true;
                if(!Settings.Instance.My360WalkAnimationActivatesWithSneakToo)
                {
                    var actor = update.Target.Actor;
                    if (actor == null || actor.IsSneaking)
                        ok = false;
                }

                if (ok && !Settings.Instance.My360WalkAnimationActivatesWithSwimToo)
                {
                    var actor = update.Target.Actor;
                    if (actor == null)
                        ok = false;
                    else
                    {
                        uint flags = NetScriptFramework.Memory.ReadUInt32(actor.Address + 0xC0);
                        if ((flags & 0x400) != 0)
                            ok = false;
                    }
                }

                if (ok)
                {
                    //update.Values.Offset1PositionY.AddModifier(this, CameraValueModifier.ModifierTypes.Multiply, -1.0);
                    update.Values.StabilizeIgnoreOffsetX.AddModifier(this, CameraValueModifier.ModifierTypes.Force, 360.0);
                }
            }
        }

        protected void Enter_Left(CameraUpdate update, bool diagonal)
        {
            
        }

        protected void Enter_Right(CameraUpdate update, bool diagonal)
        {
            
        }
    }

    class Moving_Forward  : Moving
    {
        protected internal override int IsDirection
        {
            get
            {
                return 0;
            }
        }

        internal override void OnEntering(CameraUpdate update)
        {
            base.OnEntering(update);

            this.Enter_Forwards(update, false);
        }
    }

    class Moving_ForwardRight : Moving
    {
        protected internal override int IsDirection
        {
            get
            {
                return 1;
            }
        }

        internal override void OnEntering(CameraUpdate update)
        {
            base.OnEntering(update);

            this.Enter_Forwards(update, true);
            this.Enter_Right(update, true);
        }
    }

    class Moving_Right : Moving
    {
        protected internal override int IsDirection
        {
            get
            {
                return 2;
            }
        }

        internal override void OnEntering(CameraUpdate update)
        {
            base.OnEntering(update);

            this.Enter_Right(update, false);
        }
    }

    class Moving_BackwardRight : Moving
    {
        protected internal override int IsDirection
        {
            get
            {
                return 3;
            }
        }

        internal override void OnEntering(CameraUpdate update)
        {
            base.OnEntering(update);

            this.Enter_Backwards(update, true);
            this.Enter_Right(update, true);
        }
    }

    class Moving_Backward : Moving
    {
        protected internal override int IsDirection
        {
            get
            {
                return 4;
            }
        }

        internal override void OnEntering(CameraUpdate update)
        {
            base.OnEntering(update);

            this.Enter_Backwards(update, false);
        }
    }

    class Moving_BackwardLeft : Moving
    {
        protected internal override int IsDirection
        {
            get
            {
                return 5;
            }
        }

        internal override void OnEntering(CameraUpdate update)
        {
            base.OnEntering(update);

            this.Enter_Backwards(update, true);
            this.Enter_Left(update, true);
        }
    }

    class Moving_Left : Moving
    {
        protected internal override int IsDirection
        {
            get
            {
                return 6;
            }
        }

        internal override void OnEntering(CameraUpdate update)
        {
            base.OnEntering(update);

            this.Enter_Left(update, false);
        }
    }

    class Moving_ForwardLeft : Moving
    {
        protected internal override int IsDirection
        {
            get
            {
                return 7;
            }
        }

        internal override void OnEntering(CameraUpdate update)
        {
            base.OnEntering(update);

            this.Enter_Forwards(update, true);
            this.Enter_Left(update, true);
        }
    }
}
