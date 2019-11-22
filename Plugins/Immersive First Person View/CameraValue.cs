using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IFPV
{
    internal abstract class CameraValueBase
    {
        internal abstract string Name
        {
            get;
        }

        internal abstract double DefaultValue
        {
            get;
        }

        internal abstract double CurrentValue
        {
            get;
            set;
        }

        internal abstract double ChangeSpeed
        {
            get;
        }

        [Flags]
        internal enum CameraValueFlags : uint
        {
            None = 0,

            NoTween = 1,

            NoModifiers = 2,

            IncreaseInstantly = 4,

            DecreaseInstantly = 8,

            DontUpdateIfDisabled = 0x10,
        }

        internal CameraValueFlags Flags
        {
            get;
            set;
        }

        private double TargetValue
        {
            get;
            set;
        }

        private double LastValue
        {
            get;
            set;
        }

        private TValue InternalValue
        {
            get;
            set;
        }

        internal TValue.TweenTypes Formula
        {
            get;
            set;
        }

        private int UpdatedCountWhenDisabled
        {
            get;
            set;
        }

        internal CameraValueModifier AddModifier(CameraState fromState, CameraValueModifier.ModifierTypes type, double amount, bool autoRemoveOnLeaveState = true, long autoRemoveDelay = 0)
        {
            if ((this.Flags & CameraValueFlags.NoModifiers) != CameraValueFlags.None)
                return null;

            var mod = new CameraValueModifier(this, fromState, type, amount, autoRemoveOnLeaveState, autoRemoveDelay);
            bool added = false;
            for(int i = 0; i < this.Modifiers.Count; i++)
            {
                var m = this.Modifiers[i];
                if(m.Priority > mod.Priority)
                {
                    this.Modifiers.Insert(i, mod);
                    added = true;
                    break;
                }
            }

            if (!added)
                this.Modifiers.Add(mod);

            if (mod.AutoRemove && fromState != null)
                fromState.RemoveModifiersOnLeave.Add(mod);

            this.UpdatedCountWhenDisabled = 0;

            return mod;
        }

        internal void RemoveModifier(CameraValueModifier mod)
        {
            if (mod.Owner == this)
            {
                if(this.Modifiers.Remove(mod))
                    this.UpdatedCountWhenDisabled = 0;
            }
        }

        internal void Update(long now, bool enabled)
        {
            if ((this.Flags & CameraValueFlags.NoModifiers) != CameraValueFlags.None)
                return;

            if((this.Flags & CameraValueFlags.DontUpdateIfDisabled) != CameraValueFlags.None)
            {
                if (enabled)
                    this.UpdatedCountWhenDisabled = 0;
                else
                {
                    if (this.UpdatedCountWhenDisabled > 0)
                        return;
                    this.UpdatedCountWhenDisabled++;
                }
            }

            for(int i = this.Modifiers.Count - 1; i >= 0; i--)
            {
                var m = this.Modifiers[i];
                if(m.RemoveTimer.HasValue)
                {
                    long timer = m.RemoveTimer.Value;
                    if (timer < 0)
                        m.RemoveTimer = now - m.RemoveTimer.Value;
                    else if (now >= m.RemoveTimer.Value)
                        m.Remove();
                }
            }

            double wantValue = this.DefaultValue;
            double? forceValue = null;
            foreach(var x in this.Modifiers)
            {
                switch(x.Type)
                {
                    case CameraValueModifier.ModifierTypes.Set:
                        wantValue = x.Amount;
                        forceValue = null;
                        break;

                    case CameraValueModifier.ModifierTypes.SetIfPreviousIsLowerThanThis:
                        if (x.Amount > wantValue)
                        {
                            wantValue = x.Amount;
                            forceValue = null;
                        }
                        break;

                    case CameraValueModifier.ModifierTypes.SetIfPreviousIsHigherThanThis:
                        if (x.Amount < wantValue)
                        {
                            wantValue = x.Amount;
                            forceValue = null;
                        }
                        break;

                    case CameraValueModifier.ModifierTypes.Add:
                        wantValue += x.Amount;
                        forceValue = null;
                        break;

                    case CameraValueModifier.ModifierTypes.Multiply:
                        wantValue *= x.Amount;
                        forceValue = null;
                        break;

                    case CameraValueModifier.ModifierTypes.Force:
                        forceValue = x.Amount;
                        wantValue = x.Amount;
                        break;

                    default:
                        throw new NotImplementedException();
                }
            }

            if(wantValue != this.TargetValue)
            {
                this.TargetValue = wantValue;

                bool shouldTween = !forceValue.HasValue && (this.Flags & CameraValueFlags.NoTween) == CameraValueFlags.None;
                if (shouldTween && wantValue > this.LastValue && (this.Flags & CameraValueFlags.IncreaseInstantly) != CameraValueFlags.None)
                    shouldTween = false;
                if (shouldTween && wantValue < this.LastValue && (this.Flags & CameraValueFlags.DecreaseInstantly) != CameraValueFlags.None)
                    shouldTween = false;

                if (shouldTween)
                {
                    this.InternalValue = new TValue(this.LastValue, double.MinValue, double.MaxValue);
                    this.InternalValue.TweenTo(wantValue, this.ChangeSpeed, this.Formula, true);
                }
                else
                {
                    this.CurrentValue = wantValue;
                    this.LastValue = wantValue;
                }
            }
            else if(this.InternalValue != null)
            {
                this.InternalValue.Update(now);
                this.LastValue = this.InternalValue.CurrentAmount;
                this.CurrentValue = this.LastValue;
                if (this.LastValue == wantValue)
                    this.InternalValue = null;
            }
            else
            {
                double hasNow = this.CurrentValue;
                if (hasNow != wantValue)
                {
                    this.CurrentValue = wantValue;
                    this.LastValue = wantValue;
                }
            }
        }

        internal void Reset()
        {
            if ((this.Flags & CameraValueFlags.NoModifiers) != CameraValueFlags.None)
                return;

            this.Modifiers.Clear();

            double value = this.DefaultValue;
            this.LastValue = value;
            this.TargetValue = value;
            this.InternalValue = null;
            this.CurrentValue = value;
        }

        private readonly List<CameraValueModifier> Modifiers = new List<CameraValueModifier>();
    }

    internal sealed class CameraValueModifier
    {
        internal enum ModifierTypes : int
        {
            Set,
            SetIfPreviousIsHigherThanThis,
            SetIfPreviousIsLowerThanThis,
            Add,
            Multiply,
            Force,
        }

        internal CameraValueModifier(CameraValueBase owner, CameraState state, ModifierTypes type, double amount, bool autoRemove, long autoRemoveDelay)
        {
            this.Owner = owner;
            this.State = state;
            this.Type = type;
            this.Amount = amount;
            this.AutoRemove = autoRemove;
            this.AutoRemoveDelay = autoRemoveDelay;

            if (this.State != null)
                this.Priority = this.State.Priority;
            else
                this.Priority = -1000000;
        }

        internal readonly CameraValueBase Owner;

        internal readonly CameraState State;

        internal readonly ModifierTypes Type;

        internal readonly double Amount;

        internal readonly int Priority;

        internal readonly bool AutoRemove;

        internal readonly long AutoRemoveDelay;

        internal long? RemoveTimer = null;

        internal void RemoveDelayed(long time)
        {
            this.RemoveTimer = -time;
        }

        internal void Remove()
        {
            this.Owner.RemoveModifier(this);
        }
    }

    internal class CameraValueSimple : CameraValueBase
    {
        internal CameraValueSimple(string name, double defaultValue, double changeSpeed)
        {
            this._name = name;
            this._def_value = defaultValue;
            this._cur_value = defaultValue;
            this._change = changeSpeed;

            if(name == null)
            {
                var t = this.GetType().Name;
                List<string> words = new List<string>();
                StringBuilder cur = new StringBuilder(32);
                foreach(var c in t)
                {
                    if(char.IsUpper(c) && cur.Length != 0)
                    {
                        words.Add(cur.ToString().ToLowerInvariant());
                        cur.Clear();
                    }

                    cur.Append(c);
                }

                if (cur.Length != 0)
                    words.Add(cur.ToString().ToLowerInvariant());

                this._name = string.Join(" ", words);
            }
        }

        private double _cur_value;
        private double _def_value;
        private double _change;
        private string _name;

        internal override string Name
        {
            get
            {
                return this._name;
            }
        }

        internal override double CurrentValue
        {
            get
            {
                return this._cur_value;
            }

            set
            {
                this._cur_value = value;
            }
        }

        internal override double DefaultValue
        {
            get
            {
                return this._def_value;
            }
        }

        internal override double ChangeSpeed
        {
            get
            {
                return this._change;
            }
        }
    }
}
