using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace IFPV.States
{
    internal enum Priorities : int
    {
        Default = 0,
        Weapon = 100,
        Moving = 150,
        Running = 200,
        Walking = 300,
        Sprinting = 400,
        Sneaking = 500,
        SneakRoll = 600,
        Jumping = 700,
        Swimming = 800,
        Mounted = 900,
        MountedProcess = 1000,
        Sitting = 1100,
        SittingProcess = 1200,

        WerewolfTransform = 1300,
        VampireLordTransform = 1400,
        LichTransform = 1500,
        Werewolf = 1600,
        VampireLord = 1700,
        Lich = 1800,

        Grabbing = 1900,
        Aiming = 2000,

        CustomPassenger = 2100,

        Dialogue = 2200,
        Crafting = 2300,
        Killmove = 2400,
        Bleedout = 2450,

        Dead = 2500,
    }

    internal enum Groups : int
    {
        None = 0,

        Beast = 1,
    }
}
