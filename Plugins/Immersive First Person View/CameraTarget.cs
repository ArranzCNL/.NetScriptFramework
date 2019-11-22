using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NetScriptFramework;
using NetScriptFramework.Skyrim;

namespace IFPV
{
    internal sealed class CameraTarget
    {
        private CameraTarget()
        {

        }

        internal TESObjectREFR Object
        {
            get;
            private set;
        }

        internal TESObjectREFR OriginalObject
        {
            get;
            private set;
        }

        internal Actor Actor
        {
            get;
            private set;
        }

        internal Actor OriginalActor
        {
            get;
            private set;
        }

        internal NiAVObject HeadNode
        {
            get;
            private set;
        }

        internal NiAVObject RootNode
        {
            get;
            private set;
        }

        internal NiAVObject StabilizeRootNode
        {
            get;
            private set;
        }
        
        internal static CameraTarget Create(TESObjectREFR obj)
        {
            if (obj == null)
                return null;

            TESObjectREFR originalObj = obj;
            Actor originalActor = obj.As<Actor>();

            bool isMountChange = false;
            {
                var horse = obj.As<Actor>();
                if(horse != null && horse.IsBeingRidden)
                {
                    var rider = horse.GetMountedBy();
                    if (rider != null)
                    {
                        obj = rider;
                        isMountChange = true;
                    }
                }
            }

            var t = new CameraTarget();
            t.Object = obj;
            t.Actor = obj.As<Actor>();
            t.OriginalObject = originalObj;
            t.OriginalActor = originalActor;

            var node = t.Actor != null && t.Actor.IsPlayer ? t.Actor.GetSkeletonNode(false) : obj.Node;
            if (node == null)
                return null;

            for (int i = 0; i < EyeNodeNames.Length; i++)
            {
                var name = EyeNodeNames[i];
                var n = node.LookupNodeByName(name);
                if(n != null)
                {
                    t.HeadNode = n;
                    break;
                }
            }

            if (t.HeadNode == null)
                t.HeadNode = node;

            for(int i = 0; i < RootNodeNames.Length; i++)
            {
                var name = RootNodeNames[i];
                var n = node.LookupNodeByName(name);
                if(n != null)
                {
                    t.RootNode = n;
                    break;
                }
            }

            if (t.RootNode == null)
                t.RootNode = node;

            t.StabilizeRootNode = t.RootNode;
            if(isMountChange && t.Actor != null && t.OriginalActor != null && !t.Actor.Equals(t.OriginalActor))
            {
                var stabilize = t.OriginalActor.IsPlayer ? t.OriginalActor.GetSkeletonNode(false) : t.OriginalActor.Node;
                if (stabilize != null)
                    t.StabilizeRootNode = stabilize;
            }

            return t;
        }

        private static string[] EyeNodeNames = new string[]
        {
            "NPCEyeBone",
            "NPC Head [Head]",
            "NPC Head",
            "Head [Head]",
            "HEAD",
            "Scull",
            "FireAtronach_Head [Head]",
            "ElkScull",
            "Canine_Head",
            "DragPriestNPC Head [Head]",
            "DwarvenSpiderHead_XYZ",
            "Goat_Head",
            "ChaurusFlyerHead",
            "Boar_Reikling_Head",
            "NPC_mainbody_bone",
            "RabbitHead",
            "Horker_Head01",
            "HorseScull",
            "IW Head",
            "Mammoth Head",
            "MagicEffectsNode",
            "Sabrecat_Head [Head]",
            "SlaughterfishHead",
            "Wisp Head",
            "Witchlight Body",
            "NPC Spine2 [Spn2]",
            "NPC Root [Root]"
        };

        private static string[] RootNodeNames = new string[]
        {
            // Don't use this!
            //"NPC COM [COM ]",
        };
    }
}
