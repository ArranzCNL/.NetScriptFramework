using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NetScriptFramework;
using NetScriptFramework.SkyrimSE;

namespace IFPV
{
    internal sealed class CameraStabilize
    {
        internal CameraStabilize(CameraMain cameraMain, CameraTarget target)
        {
            if (cameraMain == null)
                throw new ArgumentNullException("cameraMain");

            if (target == null)
                throw new ArgumentNullException("target");

            this.CameraMain = cameraMain;

            if (Allocation == null)
                Allocation = Memory.Allocate(0x60);

            this.TempPoint = MemoryObject.FromAddress<NiPoint3>(Allocation.Address);
            this.TempTransform = MemoryObject.FromAddress<NiTransform>(Allocation.Address + 0x10);
            this.TempTransform.Scale = 1.0f;
            this.TweenPoint = MemoryObject.FromAddress<NiPoint3>(Allocation.Address + 0x50);

            this.ForTarget = this.GetFromTarget(target);
        }

        internal readonly CameraMain CameraMain;

        private sealed class TargetChangeCheck
        {
            internal uint FormId = 0;
            internal string RootName = null;
            internal string HeadName = null;

            internal bool IsEqual(TargetChangeCheck other)
            {
                if (other == null)
                    return false;

                return this.FormId == other.FormId && this.RootName == other.RootName && this.HeadName == other.HeadName;
            }
        }

        private TargetChangeCheck ForTarget = null;

        private void UpdateValues(CameraUpdate update)
        {
            this.MaxHistoryDuration = (long)update.Values.StabilizeHistoryDuration.CurrentValue;
            this.IgnorePositionX = update.Values.StabilizeIgnorePositionX.CurrentValue;
            this.IgnorePositionY = update.Values.StabilizeIgnorePositionY.CurrentValue;
            this.IgnorePositionZ = update.Values.StabilizeIgnorePositionZ.CurrentValue;
            this.IgnoreRotationX = Utility.DegToRad(update.Values.StabilizeIgnoreRotationX.CurrentValue);
            this.IgnoreRotationY = Utility.DegToRad(update.Values.StabilizeIgnoreRotationY.CurrentValue);
            this.IgnoreOffsetX = Utility.DegToRad(update.Values.StabilizeIgnoreOffsetX.CurrentValue);
            this.IgnoreOffsetY = Utility.DegToRad(update.Values.StabilizeIgnoreOffsetY.CurrentValue);
        }

        private TargetChangeCheck GetFromTarget(CameraTarget target)
        {
            if (target == null)
                return new TargetChangeCheck();

            var obj = target.Object;
            var root = target.StabilizeRootNode;
            var head = target.HeadNode;

            var c = new TargetChangeCheck();
            if (obj != null)
                c.FormId = obj.FormId;
            if (root != null)
                c.RootName = (root.Name.Text ?? string.Empty).ToLowerInvariant() + "_" + root.Address.ToHexString();
            if (head != null)
                c.HeadName = (head.Name.Text ?? string.Empty).ToLowerInvariant() + "_" + head.Address.ToHexString();
            return c;
        }

        internal bool ShouldRecreate(CameraTarget current)
        {
            var other = this.GetFromTarget(current);
            if (object.ReferenceEquals(other, null) != object.ReferenceEquals(this.ForTarget, null))
                return true;
            if (this.ForTarget == null)
                return false;
            return !this.ForTarget.IsEqual(other);
        }

        internal long MaxHistoryDuration
        {
            get;
            private set;
        }

        internal double IgnorePositionX
        {
            get;
            private set;
        }

        internal double IgnorePositionY
        {
            get;
            private set;
        }

        internal double IgnorePositionZ
        {
            get;
            private set;
        }

        internal double IgnoreRotationX
        {
            get;
            private set;
        }

        internal double IgnoreRotationY
        {
            get;
            private set;
        }

        internal double IgnoreOffsetX
        {
            get;
            private set;
        }

        internal double IgnoreOffsetY
        {
            get;
            private set;
        }

        private sealed class CameraStabilizeHistoryEntry
        {
            internal long Time;
            internal float[] Position = null;
            internal float OffsetX = 0.0f;
            internal float OffsetY = 0.0f;
        }

        private readonly LinkedList<CameraStabilizeHistoryEntry> History = new LinkedList<CameraStabilizeHistoryEntry>();

        private CameraStabilizeHistoryEntry LastCalculated = null;

        private static MemoryAllocation Allocation = null;

        private NiTransform TempTransform = null;

        private NiPoint3 TempPoint = null;

        private NiPoint3 TweenPoint = null;

        private long TweenBegin = 0;

        private long TweenEnd = 0;
        
        private bool NeedRecalculate = false;

        internal void ApplyTween(NiPoint3 target, long time)
        {
            if (time >= this.TweenEnd || time < this.TweenBegin || this.TweenPoint == null)
                return;

            float sx = this.TweenPoint.X;
            float sy = this.TweenPoint.Y;
            float sz = this.TweenPoint.Z;
            float tx = target.X;
            float ty = target.Y;
            float tz = target.Z;
            float ratio = (float)(time - this.TweenBegin) / (float)(this.TweenEnd - this.TweenBegin);
            ratio = (float)Utility.ApplyFormula(ratio, TValue.TweenTypes.Linear);

            target.X = (tx - sx) * ratio + sx;
            target.Y = (ty - sy) * ratio + sy;
            target.Z = (tz - sz) * ratio + sz;
        }

        internal void AddTweenFrom(long duration, NiPoint3 cur)
        {
            if (this.LastCalculated == null || duration <= 0 || cur == null)
                return;

            long now = IFPVPlugin.Instance.Time;
            this.TweenPoint.CopyFrom(cur);
            this.TweenBegin = now;
            this.TweenEnd = now + duration;
        }

        internal void ClearTweenFrom()
        {
            this.TweenBegin = 0;
            this.TweenEnd = 0;
        }

        private void Recalculate()
        {
            long now = this.CameraMain.Plugin.Time;
            {
                long remove = now - this.MaxHistoryDuration;
                while (this.History.Count != 0)
                {
                    var n = this.History.First;
                    if (n.Value.Time <= remove)
                        this.History.RemoveFirst();
                    else
                        break;
                }
            }

            if(this.History.Count == 0)
                return;

            // Calculate weighted average.
            double totalWeight = 0.0;

            double[] totalPosition = new double[3];
            double totalOffsetX = 0.0;
            double totalOffsetY = 0.0;

            {
                var n = this.History.Last;
                while (n != null)
                {
                    var cur = n.Value;
                    n = n.Previous;

                    long diff = this.MaxHistoryDuration - (now - cur.Time);
                    double ratio = (double)diff / (double)this.MaxHistoryDuration;
                    double weight = ratio * ratio;
                    totalWeight += weight;
                    totalPosition[0] += cur.Position[0] * weight;
                    totalPosition[1] += cur.Position[1] * weight;
                    totalPosition[2] += cur.Position[2] * weight;
                    double ofx = cur.OffsetX;
                    double ofy = cur.OffsetY;
                    //this.ApplyIgnoreOffset(ref ofx, ref ofy);
                    totalOffsetX += ofx * weight;
                    totalOffsetY += ofy * weight;
                }
            }

            if (totalWeight <= 0.0)
                return;

            totalPosition[0] /= totalWeight;
            totalPosition[1] /= totalWeight;
            totalPosition[2] /= totalWeight;
            totalOffsetX /= totalWeight;
            totalOffsetY /= totalWeight;

            if(this.LastCalculated == null)
            {
                this.LastCalculated = new CameraStabilizeHistoryEntry();
                this.LastCalculated.Time = now;
                this.LastCalculated.Position = new float[3];
                this.LastCalculated.Position[0] = (float)totalPosition[0];
                this.LastCalculated.Position[1] = (float)totalPosition[1];
                this.LastCalculated.Position[2] = (float)totalPosition[2];
                this.LastCalculated.OffsetX = (float)totalOffsetX;
                this.LastCalculated.OffsetY = (float)totalOffsetY;
                return;
            }

            bool changed = false;

            {
                double value = totalPosition[0];
                double old = this.LastCalculated.Position[0];
                double ignore = this.IgnorePositionX;
                double diff = value - old;
                if(Math.Abs(diff) > ignore)
                {
                    if (diff >= 0.0)
                        diff -= ignore;
                    else
                        diff += ignore;
                    this.LastCalculated.Position[0] += (float)diff;
                    changed = true;
                }
            }

            {
                double value = totalPosition[1];
                double old = this.LastCalculated.Position[1];
                double ignore = this.IgnorePositionY;
                double diff = value - old;
                if (Math.Abs(diff) > ignore)
                {
                    if (diff >= 0.0)
                        diff -= ignore;
                    else
                        diff += ignore;
                    this.LastCalculated.Position[1] += (float)diff;
                    changed = true;
                }
            }

            {
                double value = totalPosition[2];
                double old = this.LastCalculated.Position[2];
                double ignore = this.IgnorePositionZ;
                double diff = value - old;
                if (Math.Abs(diff) > ignore)
                {
                    if (diff >= 0.0)
                        diff -= ignore;
                    else
                        diff += ignore;
                    this.LastCalculated.Position[2] += (float)diff;
                    changed = true;
                }
            }

            {
                double value = totalOffsetX;
                double old = this.LastCalculated.OffsetX;
                double ignore = this.IgnoreRotationX;
                double diff = value - old;
                if (Math.Abs(diff) > ignore)
                {
                    if (diff >= 0.0)
                        diff -= ignore;
                    else
                        diff += ignore;
                    this.LastCalculated.OffsetX += (float)diff;
                    changed = true;
                }
            }

            {
                double value = totalOffsetY;
                double old = this.LastCalculated.OffsetY;
                double ignore = this.IgnoreRotationY;
                double diff = value - old;
                if (Math.Abs(diff) > ignore)
                {
                    if (diff >= 0.0)
                        diff -= ignore;
                    else
                        diff += ignore;
                    this.LastCalculated.OffsetY += (float)diff;
                    changed = true;
                }
            }

            if (changed)
                this.LastCalculated.Time = now;
        }

        internal void Update(NiAVObject root, NiAVObject head, CameraUpdate update)
        {
            this.UpdateValues(update);

            var tpos = head.WorldTransform.Position;
            var spos = root.WorldTransform.Position;

            float x = tpos.X - spos.X;
            float y = tpos.Y - spos.Y;
            float z = tpos.Z - spos.Z;

            root.WorldTransform.Rotation.GetEulerAngles(this.TempPoint);
            float angle = this.TempPoint.Z;

            this.TempPoint.X = x;
            this.TempPoint.Y = y;
            this.TempPoint.Z = z;
            float len = this.TempPoint.Length;
            if (len > 0.0f)
                this.TempPoint.Normalize(this.TempPoint);

            tpos = this.TempTransform.Position;
            tpos.X = 0.0f;
            tpos.Y = 0.0f;
            tpos.Z = 0.0f;

            this.TempTransform.LookAt(this.TempPoint);
            this.TempTransform.Rotation.RotateZ(angle, this.TempTransform.Rotation);

            this.TempPoint.X = 0.0f;
            this.TempPoint.Y = len;
            this.TempPoint.Z = 0.0f;
            this.TempTransform.Translate(this.TempPoint, this.TempPoint);

            x = this.TempPoint.X;
            y = this.TempPoint.Y;
            z = this.TempPoint.Z;

            root.WorldTransform.Rotation.GetEulerAngles(this.TempPoint);
            head.WorldTransform.Rotation.GetEulerAngles(this.TempTransform.Position);

            double ofx = Utility.ClampToPi(this.TempTransform.Position.Z - this.TempPoint.Z);
            double ofy = Utility.ClampToPi(this.TempTransform.Position.X - this.TempPoint.X);

            this.ApplyIgnoreOffset(ref ofx, ref ofy);

            long now = this.CameraMain.Plugin.Time;

            var e = new CameraStabilizeHistoryEntry();
            e.Time = now;
            e.OffsetX = (float)ofx;
            e.OffsetY = (float)ofy;
            e.Position = new float[] { x, y, z };
            this.History.AddLast(e);

            this.NeedRecalculate = true;
        }

        internal bool Get(NiAVObject root, NiTransform result)
        {
            if(this.NeedRecalculate)
            {
                this.Recalculate();
                this.NeedRecalculate = false;
            }

            if (this.LastCalculated == null)
                return false;

            root.WorldTransform.Rotation.GetEulerAngles(this.TempPoint);
            float angle = this.TempPoint.Z;

            this.TempPoint.X = this.LastCalculated.Position[0];
            this.TempPoint.Y = this.LastCalculated.Position[1];
            this.TempPoint.Z = this.LastCalculated.Position[2];
            float len = this.TempPoint.Length;
            if (len > 0.0f)
                this.TempPoint.Normalize(this.TempPoint);

            var tpos = this.TempTransform.Position;
            tpos.X = 0.0f;
            tpos.Y = 0.0f;
            tpos.Z = 0.0f;
            this.TempTransform.LookAt(this.TempPoint);

            this.TempTransform.Rotation.RotateZ(-angle, this.TempTransform.Rotation);

            this.TempPoint.X = 0.0f;
            this.TempPoint.Y = len;
            this.TempPoint.Z = 0.0f;

            this.TempTransform.Translate(this.TempPoint, this.TempPoint);
            
            var pos = result.Position;
            var spos = root.WorldTransform.Position;
            pos.X = spos.X + this.TempPoint.X;
            pos.Y = spos.Y + this.TempPoint.Y;
            pos.Z = spos.Z + this.TempPoint.Z;

            root.WorldTransform.Rotation.GetEulerAngles(this.TempPoint);

            float y = (float)Utility.ClampToPi(this.TempPoint.X + this.LastCalculated.OffsetY);
            float x = (float)Utility.ClampToPi(this.TempPoint.Z + this.LastCalculated.OffsetX);

            var rot = result.Rotation;
            rot.Identity(1.0f);

            if (y != 0.0f)
                rot.RotateX(y, rot);

            if (x != 0.0f)
                rot.RotateZ(-x, rot);
            
            return true;
        }

        private void ApplyIgnoreOffset(ref double x, ref double y)
        {
            double ofx = x;
            double ofy = y;
            double ofxi = this.IgnoreOffsetX;
            double ofyi = this.IgnoreOffsetY;
            if (ofxi > 0.0)
            {
                if (ofx >= 0.0)
                {
                    ofx -= ofxi;
                    if (ofx < 0.0)
                        ofx = 0.0;
                }
                else
                {
                    ofx += ofxi;
                    if (ofx > 0.0)
                        ofx = 0.0;
                }
            }
            if (ofyi > 0.0)
            {
                if (ofy >= 0.0)
                {
                    ofy -= ofyi;
                    if (ofy < 0.0)
                        ofy = 0.0;
                }
                else
                {
                    ofy += ofyi;
                    if (ofy > 0.0)
                        ofy = 0.0;
                }
            }

            x = ofx;
            y = ofy;
        }
    }
}
