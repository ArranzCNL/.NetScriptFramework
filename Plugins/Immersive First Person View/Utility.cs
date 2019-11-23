using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IFPV
{
    internal static class Utility
    {
        internal static double RadToDeg(double rad)
        {
            return rad * (180.0 / Math.PI);
        }

        internal static double DegToRad(double deg)
        {
            return deg * (Math.PI / 180.0);
        }

        internal static double ClampToPi(double rad)
        {
            double min = -Math.PI;
            double max = Math.PI;
            //double min = 0.0;
            //double max = Math.PI * 2.0;
            double add = Math.PI * 2.0;

            if(rad < min)
            {
                do
                {
                    rad += add;
                }
                while (rad < min);
            }
            else if(rad > max)
            {
                do
                {
                    rad -= add;
                } while (rad > max);
            }

            return rad;
        }

        internal static uint GetNiAVFlags(NetScriptFramework.SkyrimSE.NiAVObject obj)
        {
            return NetScriptFramework.Memory.ReadUInt32(obj.Address + 0xF4);
        }

        internal static void SetNiAVFlags(NetScriptFramework.SkyrimSE.NiAVObject obj, uint flags)
        {
            NetScriptFramework.Memory.WriteUInt32(obj.Address + 0xF4, flags);
        }

        internal static void ModNiAVFlags(NetScriptFramework.SkyrimSE.NiAVObject obj, uint flags, bool add)
        {
            uint ofl = GetNiAVFlags(obj);
            uint fl = ofl;
            if (add)
                fl |= flags;
            else
                fl &= ~flags;

            if (ofl != fl)
                SetNiAVFlags(obj, fl);
        }

        internal static double ApplyFormula(double ratio, TValue.TweenTypes type)
        {
            if (ratio < 0.0)
                return 0.0;
            if (ratio > 1.0)
                return 1.0;

            switch(type)
            {
                case TValue.TweenTypes.Linear:
                    return ratio;

                case TValue.TweenTypes.Accelerating:
                    return ratio * ratio;

                case TValue.TweenTypes.Decelerating:
                    return Math.Sqrt(ratio);

                case TValue.TweenTypes.AccelAndDecel:
                    return Math.Sin(ratio * Math.PI - Math.PI * 0.5) * 0.5 + 0.5;

                default:
                    return ratio;
            }
        }
    }
}
