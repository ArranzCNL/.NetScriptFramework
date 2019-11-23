using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NetScriptFramework;
using NetScriptFramework.SkyrimSE;

namespace IFPV
{
    internal static class CameraCollision
    {
        internal static bool Apply(CameraUpdate update, NiTransform transform, NiPoint3 result)
        {
            init();

            if (update == null || transform == null || result == null)
                return false;

            var actor = update.Target.Actor;
            if (actor == null)
                return false;

            var cell = actor.ParentCell;
            if (cell == null)
                return false;

            float safety = (float)(update.Values.NearClip.CurrentValue + 1.0);
            if (safety < 1.0f)
                safety = 1.0f;

            float safety2 = Math.Max(0.0f, Settings.Instance.CameraCollisionSafety);

            var tpos = transform.Position;

            TempPoint1.CopyFrom(actor.Position);
            TempPoint1.Z = tpos.Z;

            if (safety2 > 0.0f)
            {
                TempSafety.Y = -safety2 * 0.5f;
                TempTransform.CopyFrom(transform);
                TempTransform.Position.CopyFrom(TempPoint1);
                TempTransform.Translate(TempSafety, TempPoint1);
            }

            TempNormal.X = tpos.X - TempPoint1.X;
            TempNormal.Y = tpos.Y - TempPoint1.Y;
            TempNormal.Z = tpos.Z - TempPoint1.Z;

            float len = TempNormal.Length;
            if (len <= 0.0f)
                return false;

            TempNormal.Normalize(TempNormal);
            TempNormal.Multiply(len + safety + safety2, TempNormal);

            TempPoint2.X = TempPoint1.X + TempNormal.X;
            TempPoint2.Y = TempPoint1.Y + TempNormal.Y;
            TempPoint2.Z = TempPoint1.Z + TempNormal.Z;
            
            var ls = cell.RayCast(new RayCastParameters()
            {
                Begin = new float[] { TempPoint1.X, TempPoint1.Y, TempPoint1.Z },
                End = new float[] { TempPoint2.X, TempPoint2.Y, TempPoint2.Z }
            });

            if (ls == null || ls.Count == 0)
                return false;

            RayCastResult best = null;
            float bestDist = 0.0f;
            List<NiAVObject> ignore = new List<NiAVObject>(3);
            {
                var sk = actor.GetSkeletonNode(true);
                if (sk != null)
                    ignore.Add(sk);
            }
            {
                var sk = actor.GetSkeletonNode(false);
                if (sk != null)
                    ignore.Add(sk);
            }
            if(update.CachedMounted)
            {
                var mount = actor.GetMount();
                if(mount != null)
                {
                    var sk = mount.GetSkeletonNode(false);
                    if (sk != null)
                        ignore.Add(sk);
                }
            }
            
            foreach (var r in ls)
            {
                if (!IsValid(r, ignore))
                    continue;

                float dist = r.Fraction;
                if (best == null)
                {
                    best = r;
                    bestDist = dist;
                }
                else if(dist < bestDist)
                {
                    best = r;
                    bestDist = dist;
                }
            }

            if (best == null)
                return false;

            bestDist *= len + safety + safety2;
            bestDist -= safety + safety2;
            bestDist /= len + safety + safety2;

            // Negative is ok!
            
            result.X = (TempPoint2.X - TempPoint1.X) * bestDist + TempPoint1.X;
            result.Y = (TempPoint2.Y - TempPoint1.Y) * bestDist + TempPoint1.Y;
            result.Z = (TempPoint2.Z - TempPoint1.Z) * bestDist + TempPoint1.Z;

            return true;
        }

        private static bool IsValid(RayCastResult r, List<NiAVObject> ignore)
        {
            var havokObj = r.HavokObject;
            if (havokObj != IntPtr.Zero)
            {
                uint flags = Memory.ReadUInt32(havokObj + 0x2C) & 0x7F;
                ulong mask = (ulong)1 << (int)flags;
                if ((RaycastMask & mask) == 0)
                    return false;
            }

            if (ignore != null && ignore.Count != 0)
            {
                var obj = r.Object;
                if (obj != null)
                {
                    for (int i = 0; i < ignore.Count; i++)
                    {
                        var o = ignore[i];
                        if (o != null && o.Equals(obj))
                            return false;
                    }
                }
            }

            return true;
        }

        private static void SetupRaycastMask(CollisionLayers[] layers)
        {
            ulong m = 0;
            foreach (var l in layers)
            {
                ulong fl = (ulong)1 << (int)l;
                m |= fl;
            }
            RaycastMask = m;
        }

        private static void init()
        {
            if (Allocation != null)
                return;

            Allocation = Memory.Allocate(0x90);
            TempPoint1 = MemoryObject.FromAddress<NiPoint3>(Allocation.Address);
            TempPoint2 = MemoryObject.FromAddress<NiPoint3>(Allocation.Address + 0x10);
            TempNormal = MemoryObject.FromAddress<NiPoint3>(Allocation.Address + 0x20);
            TempSafety = MemoryObject.FromAddress<NiPoint3>(Allocation.Address + 0x30);
            TempTransform = MemoryObject.FromAddress<NiTransform>(Allocation.Address + 0x40);
            TempTransform.Scale = 1.0f;
            TempSafety.X = 0.0f;
            TempSafety.Y = 0.0f;
            TempSafety.Z = 0.0f;

            SetupRaycastMask(new CollisionLayers[]
            {
                CollisionLayers.AnimStatic,
                CollisionLayers.Biped,
                CollisionLayers.CharController,
                //CollisionLayers.Clutter,
                CollisionLayers.DebrisLarge,
                CollisionLayers.Ground,
                //CollisionLayers.Props,
                CollisionLayers.Static,
                CollisionLayers.Terrain,
                CollisionLayers.Trap,
                CollisionLayers.Trees,
                CollisionLayers.Unidentified,
            });
        }

        private static MemoryAllocation Allocation = null;
        private static NiPoint3 TempPoint1 = null;
        private static NiPoint3 TempPoint2 = null;
        private static NiPoint3 TempSafety = null;
        private static NiPoint3 TempNormal = null;
        private static NiTransform TempTransform = null;
        private static ulong RaycastMask = 0;
    }
}
