using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NetScriptFramework;
using NetScriptFramework.SkyrimSE;

namespace IFPV
{
    internal sealed class CameraCull
    {
        internal CameraCull(CameraMain cameraMain)
        {
            if (cameraMain == null)
                throw new ArgumentNullException("cameraMain");

            this.CameraMain = cameraMain;
        }

        internal static float UnscaleAmount
        {
            get;
            set;
        } = 0.00087f;

        internal readonly CameraMain CameraMain;

        private readonly List<NiAVObject> Disabled = new List<NiAVObject>();

        private readonly List<Tuple<NiAVObject, float>> Unscaled = new List<Tuple<NiAVObject, float>>();
        
        private readonly object Locker = new object();

        internal void RemoveDisable(NiAVObject obj)
        {
            if (obj == null)
                return;

            bool had = false;
            lock(this.Locker)
            {
                IntPtr addr = obj.Address;
                for(int i = 0; i < this.Disabled.Count; i++)
                {
                    if(this.Disabled[i].Address == addr)
                    {
                        this.Disabled.RemoveAt(i);
                        had = true;
                        break;
                    }
                }
            }

            if (!had)
                return;

            SetEnabled(obj, true);
            obj.DecRef();
        }

        internal void AddDisable(NiAVObject obj)
        {
            if (obj == null)
                return;

            obj.IncRef();
            if(this.ShouldObjectBeDisabled)
                SetEnabled(obj, false);

            lock(this.Locker)
            {
                this.Disabled.Add(obj);
            }
        }

        internal void AddUnscale(NiAVObject obj)
        {
            if (obj == null)
                return;

            obj.IncRef();
            float orig = obj.LocalTransform.Scale;
            if (orig == UnscaleAmount)
                orig = 1.0f;
            if(this.ShouldObjectBeUnscaled)
                SetScale(obj, UnscaleAmount, true);

            lock(this.Locker)
            {
                this.Unscaled.Add(new Tuple<NiAVObject, float>(obj, orig));
            }
        }

        internal void Clear(IntPtr keepDisabled)
        {
            lock(this.Locker)
            {
                foreach (var s in this.Disabled)
                {
                    if(s.Address != keepDisabled)
                        SetEnabled(s, true);
                    s.DecRef();
                }

                this.Disabled.Clear();

                foreach(var t in this.Unscaled)
                {
                    SetScale(t.Item1, t.Item2, true);
                    t.Item1.DecRef();
                }

                this.Unscaled.Clear();
            }
        }

        private int _state_cull = 0;
        private int _state_update = 0;

        private void IncCull()
        {
            if (++this._state_cull != 1)
                return;

            foreach (var s in this.Disabled)
                SetEnabled(s, true);

            if (this._state_update <= 0)
            {
                foreach (var t in this.Unscaled)
                    SetScale(t.Item1, t.Item2, true);
            }
        }

        private void DecCull()
        {
            if (--this._state_cull != 0)
                return;

            foreach (var s in this.Disabled)
                SetEnabled(s, false);

            if (this._state_update <= 0)
            {
                foreach (var t in this.Unscaled)
                    SetScale(t.Item1, UnscaleAmount, true);
            }
        }

        private void IncUpdate()
        {
            if (++this._state_update != 1)
                return;

            if(this._state_cull <= 0)
            {
                foreach (var t in this.Unscaled)
                    SetScale(t.Item1, t.Item2, false);
            }
        }

        private void DecUpdate()
        {
            if (--this._state_update != 0)
                return;

            if(this._state_cull <= 0)
            {
                foreach (var t in this.Unscaled)
                    SetScale(t.Item1, UnscaleAmount, false);
            }
        }

        internal void OnShadowCulling(int index)
        {
            lock(this.Locker)
            {
                if (index == 0)
                    this.IncCull();
                else if (index == 1)
                    this.DecCull();
            }
        }

        internal void OnUpdating(int index)
        {
            lock(this.Locker)
            {
                if (index == 0)
                    this.IncUpdate();
                else if(index == 1)
                    this.DecUpdate();
            }
        }

        private bool ShouldObjectBeDisabled
        {
            get
            {
                return this._state_cull <= 0;
            }
        }

        private bool ShouldObjectBeUnscaled
        {
            get
            {
                return this._state_cull <= 0 && this._state_update <= 0;
            }
        }

        private void SetEnabled(NiAVObject obj, bool enabled)
        {
            if (obj.Parent == null)
                return;
            
            uint fl = Memory.ReadUInt32(obj.Address + 0xF4);
            bool hadEnabled = (fl & 1) == 0;
            if (hadEnabled == enabled)
                return;

            if (enabled)
                fl &= ~(uint)1;
            else
                fl |= 1;

            Memory.WriteUInt32(obj.Address + 0xF4, fl);
        }
        
        private void SetScale(NiAVObject obj, float scale, bool cull)
        {
            if (obj.Parent == null)
                return;
            
            obj.LocalTransform.Scale = scale;
            obj.Update(0.0f);
        }
    }
}
