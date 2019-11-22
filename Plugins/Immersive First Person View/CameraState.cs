using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IFPV
{
    internal abstract class CameraState
    {
        internal CameraStack Stack
        {
            get;
            private set;
        }

        internal bool IsActive
        {
            get;
            private set;
        }

        internal bool __wActivate
        {
            get;
            set;
        }

        internal virtual int Priority
        {
            get
            {
                return 0;
            }
        }

        internal virtual int Group
        {
            get
            {
                return 0;
            }
        }
        
        internal virtual void OnEntering(CameraUpdate update)
        {

        }
        
        internal virtual void OnLeaving(CameraUpdate update)
        {

        }
        
        internal virtual bool Check(CameraUpdate update)
        {
            return true;
        }

        internal virtual void Update(CameraUpdate update)
        {

        }
        
        internal virtual void Initialize()
        {

        }

        internal void _init(CameraStack s)
        {
            this.Stack = s;
        }

        internal void _set(bool a)
        {
            this.IsActive = a;

            //NetScriptFramework.Debug.GUI.WriteLine((a ? ">>> " : "<<< ") + this.GetType().Name);
            
            if (!a)
            {
                foreach (var m in this.RemoveModifiersOnLeave)
                {
                    long time = m.AutoRemoveDelay;
                    if (time > 0)
                        m.RemoveDelayed(time);
                    else
                        m.Remove();
                }
                this.RemoveModifiersOnLeave.Clear();
            }
        }

        internal readonly List<CameraValueModifier> RemoveModifiersOnLeave = new List<CameraValueModifier>();

        protected void AddHeadBobModifier(CameraUpdate update, bool forceHeadBob = false, bool forceReducedStabilizeHistory = false, double multiplier = 1.0, long extraDuration = 0)
        {
            bool headBob = forceHeadBob || Settings.Instance.HeadBob;
            if (headBob)
            {
                double value = 0.5;
                double amount = (forceHeadBob ? 1.0 : Settings.Instance.HeadBobAmount) * multiplier;
                if(amount > 0.01)
                {
                    value /= amount;
                    update.Values.StabilizeIgnorePositionZ.AddModifier(this, CameraValueModifier.ModifierTypes.SetIfPreviousIsHigherThanThis, value, true, extraDuration);
                }
            }

            if (headBob || forceReducedStabilizeHistory)
                update.Values.StabilizeHistoryDuration.AddModifier(this, CameraValueModifier.ModifierTypes.SetIfPreviousIsHigherThanThis, 100.0, true, extraDuration);
        }
    }
}
