#pragma once
#pragma warning(push)
#pragma warning(disable : 4638)

#include "Extra2.h"

namespace NetScriptFramework
{
    namespace Skyrim
    {
        /// <summary>
        /// Base form component implementation. All inheritable components of a form derive from this type.
        /// </summary>
        public interface class BaseFormComponent : public IVirtualObject
        {
        };
        
        public interface class NiRefObject : public IVirtualObject
        {
            /// <summary>
            /// Increment the ref count manually.
            /// </summary>
            void IncRef();
            
            /// <summary>
            /// Reduce ref count of object manually. Returns true if the object was deleted in the process.
            /// </summary>
            bool DecRef();
        };
        
        public interface class BSHandleRefObject : public NiRefObject
        {
        };
        
        generic <typename T1>
        public interface class BSTEventSink : public IVirtualObject
        {
        };
        
        public interface class BSAnimationGraphEvent : public IMemoryObject
        {
        };
        
        public interface class IAnimationGraphManagerHolder : public IVirtualObject
        {
        };
        
        public interface class IMovementInterface : public IVirtualObject
        {
        };
        
        public interface class IMovementState : public IMovementInterface
        {
        };
        
        public interface class ActorState : public IMovementState
        {
        };
        
        public interface class BSTransformDeltaEvent : public IMemoryObject
        {
        };
        
        public interface class bhkCharacterMoveFinishEvent : public IMemoryObject
        {
        };
        
        public interface class IPostAnimationChannelUpdateFunctor : public IVirtualObject
        {
        };
        
        /// <summary>
        /// Actor value indices list.
        /// </summary>
        public enum class ActorValueIndices
        {
            Aggression = 0,
            
            Confidence = 0x1,
            
            Energy = 0x2,
            
            Morality = 0x3,
            
            Mood = 0x4,
            
            Assistance = 0x5,
            
            OneHanded = 0x6,
            
            TwoHanded = 0x7,
            
            Marksman = 0x8,
            
            Block = 0x9,
            
            Smithing = 0xA,
            
            HeavyArmor = 0xB,
            
            LightArmor = 0xC,
            
            Pickpocket = 0xD,
            
            Lockpicking = 0xE,
            
            Sneak = 0xF,
            
            Alchemy = 0x10,
            
            Speechcraft = 0x11,
            
            Alteration = 0x12,
            
            Conjuration = 0x13,
            
            Destruction = 0x14,
            
            Illusion = 0x15,
            
            Restoration = 0x16,
            
            Enchanting = 0x17,
            
            Health = 0x18,
            
            Magicka = 0x19,
            
            Stamina = 0x1A,
            
            HealRate = 0x1B,
            
            MagickaRate = 0x1C,
            
            StaminaRate = 0x1D,
            
            SpeedMult = 0x1E,
            
            InventoryWeight = 0x1F,
            
            CarryWeight = 0x20,
            
            CritChance = 0x21,
            
            MeleeDamage = 0x22,
            
            UnarmedDamage = 0x23,
            
            Mass = 0x24,
            
            VoicePoints = 0x25,
            
            VoiceRate = 0x26,
            
            DamageResist = 0x27,
            
            PoisonResist = 0x28,
            
            FireResist = 0x29,
            
            ElectricResist = 0x2A,
            
            FrostResist = 0x2B,
            
            MagicResist = 0x2C,
            
            DiseaseResist = 0x2D,
            
            PerceptionCondition = 0x2E,
            
            EnduranceCondition = 0x2F,
            
            LeftAttackCondition = 0x30,
            
            RightAttackCondition = 0x31,
            
            LeftMobilityCondition = 0x32,
            
            RightMobilityCondition = 0x33,
            
            BrainCondition = 0x34,
            
            Paralysis = 0x35,
            
            Invisibility = 0x36,
            
            NightEye = 0x37,
            
            DetectLifeRange = 0x38,
            
            WaterBreathing = 0x39,
            
            WaterWalking = 0x3A,
            
            IgnoreCrippledLimbs = 0x3B,
            
            Fame = 0x3C,
            
            Infamy = 0x3D,
            
            JumpingBonus = 0x3E,
            
            WardPower = 0x3F,
            
            RightItemCharge = 0x40,
            
            ArmorPerks = 0x41,
            
            ShieldPerks = 0x42,
            
            WardDeflection = 0x43,
            
            Variable01 = 0x44,
            
            Variable02 = 0x45,
            
            Variable03 = 0x46,
            
            Variable04 = 0x47,
            
            Variable05 = 0x48,
            
            Variable06 = 0x49,
            
            Variable07 = 0x4A,
            
            Variable08 = 0x4B,
            
            Variable09 = 0x4C,
            
            Variable10 = 0x4D,
            
            BowSpeedBonus = 0x4E,
            
            FavorActive = 0x4F,
            
            FavorsPerDay = 0x50,
            
            FavorsPerDayTimer = 0x51,
            
            LeftItemCharge = 0x52,
            
            AbsorbChance = 0x53,
            
            Blindness = 0x54,
            
            WeaponSpeedMult = 0x55,
            
            ShoutRecoveryMult = 0x56,
            
            BowStaggerBonus = 0x57,
            
            Telekinesis = 0x58,
            
            FavorPointsBonus = 0x59,
            
            LastBribedIntimidated = 0x5A,
            
            LastFlattered = 0x5B,
            
            MovementNoiseMult = 0x5C,
            
            BypassVendorStolenCheck = 0x5D,
            
            BypassVendorKeywordCheck = 0x5E,
            
            WaitingForPlayer = 0x5F,
            
            OneHandedMod = 0x60,
            
            TwoHandedMod = 0x61,
            
            MarksmanMod = 0x62,
            
            BlockMod = 0x63,
            
            SmithingMod = 0x64,
            
            HeavyArmorMod = 0x65,
            
            LightArmorMod = 0x66,
            
            PickPocketMod = 0x67,
            
            LockpickingMod = 0x68,
            
            SneakMod = 0x69,
            
            AlchemyMod = 0x6A,
            
            SpeechcraftMod = 0x6B,
            
            AlterationMod = 0x6C,
            
            ConjurationMod = 0x6D,
            
            DestructionMod = 0x6E,
            
            IllusionMod = 0x6F,
            
            RestorationMod = 0x70,
            
            EnchantingMod = 0x71,
            
            OneHandedSkillAdvance = 0x72,
            
            TwoHandedSkillAdvance = 0x73,
            
            MarksmanSkillAdvance = 0x74,
            
            BlockSkillAdvance = 0x75,
            
            SmithingSkillAdvance = 0x76,
            
            HeavyArmorSkillAdvance = 0x77,
            
            LightArmorSkillAdvance = 0x78,
            
            PickPocketSkillAdvance = 0x79,
            
            LockpickingSkillAdvance = 0x7A,
            
            SneakSkillAdvance = 0x7B,
            
            AlchemySkillAdvance = 0x7C,
            
            SpeechcraftSkillAdvance = 0x7D,
            
            AlterationSkillAdvance = 0x7E,
            
            ConjurationSkillAdvance = 0x7F,
            
            DestructionSkillAdvance = 0x80,
            
            IllusionSkillAdvance = 0x81,
            
            RestorationSkillAdvance = 0x82,
            
            EnchantingSkillAdvance = 0x83,
            
            LeftWeaponSpeedMult = 0x84,
            
            DragonSouls = 0x85,
            
            CombatHealthRegenMult = 0x86,
            
            OneHandedPowerMod = 0x87,
            
            TwoHandedPowerMod = 0x88,
            
            MarksmanPowerMod = 0x89,
            
            BlockPowerMod = 0x8A,
            
            SmithingPowerMod = 0x8B,
            
            HeavyArmorPowerMod = 0x8C,
            
            LightArmorPowerMod = 0x8D,
            
            PickPocketPowerMod = 0x8E,
            
            LockpickingPowerMod = 0x8F,
            
            SneakPowerMod = 0x90,
            
            AlchemyPowerMod = 0x91,
            
            SpeechcraftPowerMod = 0x92,
            
            AlterationPowerMod = 0x93,
            
            ConjurationPowerMod = 0x94,
            
            DestructionPowerMod = 0x95,
            
            IllusionPowerMod = 0x96,
            
            RestorationPowerMod = 0x97,
            
            EnchantingPowerMod = 0x98,
            
            DragonRend = 0x99,
            
            AttackDamageMult = 0x9A,
            
            HealRateMult = 0x9B,
            
            MagickaRateMult = 0x9C,
            
            StaminaRateMult = 0x9D,
            
            WerewolfPerks = 0x9E,
            
            VampirePerks = 0x9F,
            
            GrabActorOffset = 0xA0,
            
            Grabbed = 0xA1,
            
            DEPRECATED05 = 0xA2,
            
            ReflectDamage = 0xA3,
            
            Max = 0xA4,
        };
        
        public interface class ActorValueOwner : public IVirtualObject
        {
            /// <summary>
            /// Gets the current actor value.
            /// </summary>
            /// <param name="id">The type of actor value to get.</param>
            System::Single GetActorValue(ActorValueIndices id);
            
            /// <summary>
            /// Gets the maximum actor value.
            /// </summary>
            /// <param name="id">The type of actor value to get.</param>
            System::Single GetActorValueMax(ActorValueIndices id);
            
            /// <summary>
            /// Gets the base actor value.
            /// </summary>
            /// <param name="id">The type of actor value to get.</param>
            System::Single GetBaseActorValue(ActorValueIndices id);
            
            /// <summary>
            /// Damages the actor value.
            /// </summary>
            /// <param name="id">The actor value type.</param>
            /// <param name="amount">The amount to damage by.</param>
            void DamageActorValue(ActorValueIndices id, System::Single amount);
            
            /// <summary>
            /// Restores an actor value by amount.
            /// </summary>
            /// <param name="id">The actor value type.</param>
            /// <param name="amount">The amount to restore.</param>
            void RestoreActorValue(ActorValueIndices id, System::Single amount);
            
            /// <summary>
            /// Forces the actor value to specified amount.
            /// </summary>
            /// <param name="id">The actor value type to force.</param>
            /// <param name="amount">The amount to force to.</param>
            void ForceActorValue(ActorValueIndices id, System::Single amount);
            
            /// <summary>
            /// Modifies the actor value permanently.
            /// </summary>
            /// <param name="id">The type of value to modify.</param>
            /// <param name="amount">The amount to modify by.</param>
            void ModActorValue(ActorValueIndices id, System::Single amount);
            
            /// <summary>
            /// Sets the actor value.
            /// </summary>
            /// <param name="id">The actor value type to set.</param>
            /// <param name="amount">The amount to set.</param>
            void SetActorValue(ActorValueIndices id, System::Single amount);
        };
        
        /// <summary>
        /// Game's string cache entry pointer.
        /// </summary>
        public interface class BSFixedString : public IMemoryObject
        {
            /// <summary>
            /// Get the text of this string cache entry.
            /// </summary>
            property System::String^ Text
            {
                System::String^ get();
            }
            
        };
        
        public interface class BSIntrusiveRefCounted : public IVirtualObject
        {
        };
        
        public interface class BSScript : public IMemoryObject
        {
            interface class IFunction : public BSIntrusiveRefCounted
            {
            };
            
            interface class NF_util : public IMemoryObject
            {
                interface class NativeFunctionBase : public BSScript::IFunction
                {
                    /// <summary>
                    /// Gets the name of function.
                    /// </summary>
                    property BSFixedString^ FuncName
                    {
                        BSFixedString^ get();
                    }
                    
                    /// <summary>
                    /// Gets the name of owner type.
                    /// </summary>
                    property BSFixedString^ TypeName
                    {
                        BSFixedString^ get();
                    }
                };
            };
        };
        
        /// <summary>
        /// Base array implementation of game.
        /// </summary>
        public interface class BSTArrayBase : public IMemoryObject
        {
            interface class IAllocatorFunctor : public IVirtualObject
            {
            };
            
            /// <summary>
            /// Gets the pointer to array's data.
            /// </summary>
            property System::IntPtr Data
            {
                System::IntPtr get();
            }
            
            /// <summary>
            /// Gets the current capacity of array.
            /// </summary>
            property System::Int32 Capacity
            {
                System::Int32 get();
            }
            
            /// <summary>
            /// Gets the current count of elements in array.
            /// </summary>
            property System::Int32 Count
            {
                System::Int32 get();
            }
        };
        
        /// <summary>
        /// List of all form type identifiers.
        /// </summary>
        public enum class FormTypes : System::Byte
        {
            None = 0,
            
            TES4 = 0x1,
            
            Group = 0x2,
            
            GMST = 0x3,
            
            Keyword = 0x4,
            
            LocationRef = 0x5,
            
            Action = 0x6,
            
            TextureSet = 0x7,
            
            MenuIcon = 0x8,
            
            Global = 0x9,
            
            Class = 0xA,
            
            Faction = 0xB,
            
            HeadPart = 0xC,
            
            Eyes = 0xD,
            
            Race = 0xE,
            
            Sound = 0xF,
            
            AcousticSpace = 0x10,
            
            Skill = 0x11,
            
            EffectSetting = 0x12,
            
            Script = 0x13,
            
            LandTexture = 0x14,
            
            Enchantment = 0x15,
            
            Spell = 0x16,
            
            ScrollItem = 0x17,
            
            Activator = 0x18,
            
            TalkingActivator = 0x19,
            
            Armor = 0x1A,
            
            Book = 0x1B,
            
            Container = 0x1C,
            
            Door = 0x1D,
            
            Ingredient = 0x1E,
            
            Light = 0x1F,
            
            Misc = 0x20,
            
            Apparatus = 0x21,
            
            Static = 0x22,
            
            StaticCollection = 0x23,
            
            MovableStatic = 0x24,
            
            Grass = 0x25,
            
            Tree = 0x26,
            
            Flora = 0x27,
            
            Furniture = 0x28,
            
            Weapon = 0x29,
            
            Ammo = 0x2A,
            
            NPC = 0x2B,
            
            LeveledCharacter = 0x2C,
            
            Key = 0x2D,
            
            Potion = 0x2E,
            
            IdleMarker = 0x2F,
            
            Note = 0x30,
            
            ConstructibleObject = 0x31,
            
            Projectile = 0x32,
            
            Hazard = 0x33,
            
            SoulGem = 0x34,
            
            LeveledItem = 0x35,
            
            Weather = 0x36,
            
            Climate = 0x37,
            
            SPGD = 0x38,
            
            ReferenceEffect = 0x39,
            
            Region = 0x3A,
            
            NAVI = 0x3B,
            
            Cell = 0x3C,
            
            Reference = 0x3D,
            
            Character = 0x3E,
            
            Missile = 0x3F,
            
            Arrow = 0x40,
            
            Grenade = 0x41,
            
            BeamProj = 0x42,
            
            FlameProj = 0x43,
            
            ConeProj = 0x44,
            
            BarrierProj = 0x45,
            
            PHZD = 0x46,
            
            WorldSpace = 0x47,
            
            Land = 0x48,
            
            NAVM = 0x49,
            
            TLOD = 0x4A,
            
            Topic = 0x4B,
            
            TopicInfo = 0x4C,
            
            Quest = 0x4D,
            
            Idle = 0x4E,
            
            Package = 0x4F,
            
            CombatStyle = 0x50,
            
            LoadScreen = 0x51,
            
            LeveledSpell = 0x52,
            
            ANIO = 0x53,
            
            Water = 0x54,
            
            EffectShader = 0x55,
            
            TOFT = 0x56,
            
            Explosion = 0x57,
            
            Debris = 0x58,
            
            ImageSpace = 0x59,
            
            ImageSpaceMod = 0x5A,
            
            List = 0x5B,
            
            Perk = 0x5C,
            
            BodyPartData = 0x5D,
            
            AddonNode = 0x5E,
            
            ActorValueInfo = 0x5F,
            
            CameraShot = 0x60,
            
            CameraPath = 0x61,
            
            VoiceType = 0x62,
            
            MaterialType = 0x63,
            
            ImpactData = 0x64,
            
            ImpactDataSet = 0x65,
            
            ARMA = 0x66,
            
            EncounterZone = 0x67,
            
            Location = 0x68,
            
            Message = 0x69,
            
            Ragdoll = 0x6A,
            
            DOBJ = 0x6B,
            
            LightingTemplate = 0x6C,
            
            MusicType = 0x6D,
            
            Footstep = 0x6E,
            
            FootstepSet = 0x6F,
            
            StoryBranchNode = 0x70,
            
            StoryQuestNode = 0x71,
            
            StoryEventNode = 0x72,
            
            DialogueBranch = 0x73,
            
            MusicTrack = 0x74,
            
            DLVW = 0x75,
            
            WordOfPower = 0x76,
            
            Shout = 0x77,
            
            EquipSlot = 0x78,
            
            Relationship = 0x79,
            
            Scene = 0x7A,
            
            AssociationType = 0x7B,
            
            Outfit = 0x7C,
            
            Art = 0x7D,
            
            Material = 0x7E,
            
            MovementType = 0x7F,
            
            SoundDescriptor = 0x80,
            
            DualCastData = 0x81,
            
            SoundCategory = 0x82,
            
            SoundOutput = 0x83,
            
            CollisionLayer = 0x84,
            
            ColorForm = 0x85,
            
            ReverbParam = 0x86,
            
            Unk87 = 0x87,
            
            Alias = 0x88,
            
            ReferenceAlias = 0x89,
            
            LocationAlias = 0x8A,
            
            ActiveMagicEffect = 0x8B,
        };
        
        /// <summary>
        /// Structure that stores information about a game or console function registration.
        /// </summary>
        public interface class GameFunction : public IMemoryObject
        {
            /// <summary>
            /// Gets the name of function.
            /// </summary>
            property System::String^ Name
            {
                System::String^ get();
            }
            
            /// <summary>
            /// Gets the alternate name of function. This is usually the short version of name.
            /// </summary>
            property System::String^ AlternateName
            {
                System::String^ get();
            }
            
            /// <summary>
            /// Gets the identifier of this function.
            /// </summary>
            property System::Int32 Id
            {
                System::Int32 get();
            }
            
            /// <summary>
            /// Gets the description of function. This is set for console commands to describe what it does.
            /// </summary>
            property System::String^ Description
            {
                System::String^ get();
            }
            
            /// <summary>
            /// Gets the options for this function.
            /// </summary>
            property System::UInt32 Flags
            {
                System::UInt32 get();
            }
            
            /// <summary>
            /// Gets the argument type.
            /// </summary>
            property System::String^ Argument
            {
                System::String^ get();
            }
            
            /// <summary>
            /// Gets the handler function pointer.
            /// </summary>
            property System::IntPtr HandlerFunc
            {
                System::IntPtr get();
            }
            
            /// <summary>
            /// Gets the argument parser function pointer.
            /// </summary>
            property System::IntPtr ParserFunc
            {
                System::IntPtr get();
            }
            
            /// <summary>
            /// Gets the native function pointer. This is not set for all functions!
            /// </summary>
            property System::IntPtr NativeFunc
            {
                System::IntPtr get();
            }
        };
        
        /// <summary>
        /// Simple linked list node implementation.
        /// </summary>
        generic <typename T1>
        public interface class ListNode : public IMemoryObject, public System::Collections::Generic::IEnumerable<T1>
        {
            /// <summary>
            /// Gets the current item at node.
            /// </summary>
            property T1 Item
            {
                T1 get();
            }
            
            /// <summary>
            /// Gets the next node in list.
            /// </summary>
            property ListNode<T1>^ Next
            {
                ListNode<T1>^ get();
            }
            
        };
        
        public interface class NiObject : public NiRefObject
        {
            /// <summary>
            /// Create and return a clone of this object.
            /// </summary>
            NiObject^ Clone();
            
            /// <summary>
            /// Loads a NiObject from NIF file.
            /// </summary>
            /// <param name="p">The parameters.</param>
            static void LoadFromFile(NiObjectLoadParameters^ p)
            
            {
                
                	if (p == nullptr) throw gcnew System::ArgumentNullException("p");
                
                	if (p->FileName == nullptr) throw gcnew System::ArgumentNullException("p->FileName");
                
                	NiObjectLoadParameters::_RequestModelDirect(p);
                
            }
            
            /// <summary>
            /// Queues a load operation of a NiObject from NIF file.
            /// </summary>
            /// <param name="p">The parameters.</param>
            static void LoadFromFileAsync(NiObjectLoadParameters^ p)
            
            {
                
                	if (p == nullptr) throw gcnew System::ArgumentNullException("p");
                
                	if (p->FileName == nullptr) throw gcnew System::ArgumentNullException("p->FileName");
                
                	NiObjectLoadParameters::_RequestModelAsync(p);
                
            }
        };
        
        public interface class NiObjectNET : public NiObject
        {
            /// <summary>
            /// Gets the name of object.
            /// </summary>
            property BSFixedString^ Name
            {
                BSFixedString^ get();
            }
            
        };
        
        /// <summary>
        /// This class handles automatic reference count tracking of a NiRefObject.
        /// </summary>
        generic <typename T1>
        where T1 : NiRefObject
        public interface class NiPointer : public IMemoryObject
        {
            /// <summary>
            /// Gets or sets what the pointer points to.
            /// </summary>
            property T1 Target
            {
                T1 get();
                void set(T1 value);
            }
        };
        
        generic <typename T1, typename T2>
        public interface class NiTArray : public IVirtualObject, public System::Collections::Generic::IEnumerable<T1>
        {
            /// <summary>
            /// Gets the pointer to data of array.
            /// </summary>
            property System::IntPtr Data
            {
                System::IntPtr get();
            }
            
            /// <summary>
            /// Gets the capacity of array. This is the maximum amount of elements that can currently exist in the array.
            /// </summary>
            property System::UInt16 Capacity
            {
                System::UInt16 get();
            }
            
            /// <summary>
            /// Gets the actual count of elements in the array.
            /// </summary>
            property System::UInt16 Count
            {
                System::UInt16 get();
            }
            
            /// <summary>
            /// Gets or sets the count to grow array by if capacity is exceeded.
            /// </summary>
            property System::UInt16 GrowCount
            {
                System::UInt16 get();
                void set(System::UInt16 value);
            }
            
            
            /// <summary>
            /// Gets the value at specified index.
            /// </summary>
            property T1 default[System::Int32]
            {
                T1 get(System::Int32 index);
            }
        };
        
        public interface class TESFullName : public BaseFormComponent
        {
            /// <summary>
            /// Gets the text of this name instance.
            /// </summary>
            property BSFixedString^ Text
            {
                BSFixedString^ get();
            }
        };
        
        public interface class BSExtraDataList : public IMemoryObject
        {
        };
        
        public interface class TESModel : public BaseFormComponent
        {
        };
        
        /// <summary>
        /// This form is used to store weight of inventory object.
        /// </summary>
        public interface class TESWeightForm : public BaseFormComponent
        {
            /// <summary>
            /// Gets or sets the weight value.
            /// </summary>
            property System::Single Value
            {
                System::Single get();
                void set(System::Single value);
            }
        };
        
        generic <typename T1>
        public interface class NiTNewInterface : public IMemoryObject
        {
        };
        
        generic <typename T1>
        public interface class NiTObjectArray : public NiTArray<T1, NiTNewInterface<T1>^>
        {
        };
        
        /// <summary>
        /// Camera state identifiers.
        /// </summary>
        public enum class TESCameraStates : System::Int32
        {
            FirstPerson = 0,
            
            AutoVanity = 0x1,
            
            VATS = 0x2,
            
            Free = 0x3,
            
            IronSights = 0x4,
            
            Furniture = 0x5,
            
            Transition = 0x6,
            
            TweenMenu = 0x7,
            
            ThirdPerson1 = 0x8,
            
            ThirdPerson2 = 0x9,
            
            Horse = 0xA,
            
            Bleedout = 0xB,
            
            Dragon = 0xC,
        };
        
        public interface class PlayerInputHandler : public IVirtualObject
        {
        };
        
        public interface class MenuOpenCloseEvent : public IMemoryObject
        {
        };
        
        public interface class MenuModeChangeEvent : public IMemoryObject
        {
        };
        
        public interface class UserEventEnabledEvent : public IMemoryObject
        {
        };
        
        public interface class TESTrackedStatsEvent : public IMemoryObject
        {
        };
        
        public interface class BGSMenuDisplayObject : public BaseFormComponent
        {
        };
        
        public interface class BGSKeywordForm : public BaseFormComponent
        {
        };
        
        /// <summary>
        /// Typed object array implementation of game.
        /// </summary>
        generic <typename T1>
        public interface class BSTArray : BSTArrayBase, public System::Collections::Generic::IEnumerable<T1>
        {
            
            /// <summary>
            /// Gets the value at specified index.
            /// </summary>
            property T1 default[System::Int32]
            {
                T1 get(System::Int32 index);
            }
        };
        
        generic <typename T1>
        public interface class BSTArrayAllocatorFunctor : public BSTArrayBase::IAllocatorFunctor
        {
        };
        
        public interface class BSTArrayHeapAllocator : public IMemoryObject
        {
        };
        
        public interface class bhkRefObject : public NiObject
        {
        };
        
        public interface class bhkSerializable : public bhkRefObject
        {
        };
        
        /// <summary>
        /// Havok world object wrapper.
        /// </summary>
        public interface class bhkWorldObject : public bhkSerializable
        {
        };
        
        /// <summary>
        /// Havok world entity wrapper.
        /// </summary>
        public interface class bhkEntity : public bhkWorldObject
        {
        };
        
        public interface class PositionPlayerEvent : public IMemoryObject
        {
        };
        
        public interface class BSGamerProfileEvent : public IMemoryObject
        {
        };
        
        /// <summary>
        /// Main application class.
        /// </summary>
        public interface class Main : public BSTEventSink<PositionPlayerEvent^>, public BSTEventSink<BSGamerProfileEvent^>
        {
            /// <summary>
            /// Gets or sets a value whether the main game world is paused. This is the one used with ToggleFlyCam 1. This is not used to check if the game
            /// itself is paused at the moment! Use the IsGamePaused property for that.
            /// </summary>
            property System::Byte PauseGameWorld
            {
                System::Byte get();
                void set(System::Byte value);
            }
            
            /// <summary>
            /// Gets the main application instance.
            /// </summary>
            static property Main^ Instance
            {
                    Main^ get()
                    {
                        return MemoryObject::FromAddress<Main^>(Memory::ReadPointer(MCH::FromBase(0x142F4DBF8), false));
                    }
            }
            
            /// <summary>
            /// Check if the game is currently paused.
            /// </summary>
            property bool IsGamePaused
            {
                bool get();
            }
        };
        
        public interface class TESDescription : public BaseFormComponent
        {
        };
        
        public interface class TESTexture : public BaseFormComponent
        {
        };
        
        public interface class TESIcon : public TESTexture
        {
        };
        
        public interface class BGSEquipType : public BaseFormComponent
        {
        };
        
        /// <summary>
        /// List of combat states.
        /// </summary>
        public enum class ActorCombatStates : System::Int32
        {
            NotInCombat = 0,
            
            InCombat = 0x1,
            
            Searching = 0x2,
        };
        
        /// <summary>
        /// List of equip biped slots.
        /// </summary>
        public enum class EquipSlots : System::Int32
        {
            Head = 0x1E,
            
            Hair = 0x1F,
            
            Body = 0x20,
            
            Hands = 0x21,
            
            Forearms = 0x22,
            
            Amulet = 0x23,
            
            Ring = 0x24,
            
            Feet = 0x25,
            
            Calves = 0x26,
            
            Shield = 0x27,
            
            Tail = 0x28,
            
            LongHair = 0x29,
            
            Circlet = 0x2A,
            
            Ears = 0x2B,
            
            Unused_FaceMouth = 0x2C,
            
            Unused_Neck = 0x2D,
            
            Unused_ChestPrimary = 0x2E,
            
            Unused_Back = 0x2F,
            
            Unused_Misc = 0x30,
            
            Unused_PelvisPrimary = 0x31,
            
            DecapitatedHead_NordRace = 0x32,
            
            Decapitate_NordRace = 0x33,
            
            Unused_PelvisSecondary = 0x34,
            
            Unused_LegPrimary = 0x35,
            
            Unused_LegSecondary = 0x36,
            
            Unused_Jewelry = 0x37,
            
            Unused_ChestSecondary = 0x38,
            
            Unused_Shoulder = 0x39,
            
            Unused_ArmSecondary = 0x3A,
            
            Unused_ArmPrimary = 0x3B,
            
            Unused_Misc2 = 0x3C,
            
            FX01 = 0x3D,
        };
        
        /// <summary>
        /// Equipped item types (in hand).
        /// </summary>
        public enum class EquippedItemTypes : System::Int32
        {
            HandToHand = 0,
            
            OneHandedSword = 0x1,
            
            OneHandedDagger = 0x2,
            
            OneHandedAxe = 0x3,
            
            OneHandedMace = 0x4,
            
            TwoHandedSword = 0x5,
            
            TwoHandedAxeMace = 0x6,
            
            Bow = 0x7,
            
            Staff = 0x8,
            
            Magic = 0x9,
            
            Shield = 0xA,
            
            Torch = 0xB,
            
            Crossbow = 0xC,
        };
        
        /// <summary>
        /// Slots for equipping items in hands.
        /// </summary>
        public enum class EquippedHandSlots : System::Int32
        {
            LeftHand = 0,
            
            RightHand = 0x1,
        };
        
        /// <summary>
        /// Slots for equipped spell.
        /// </summary>
        public enum class EquippedSpellSlots : System::Int32
        {
            LeftHand = 0,
            
            RightHand = 0x1,
            
            Other = 0x2,
            
            Instant = 0x3,
        };
        
        /// <summary>
        /// List of reactions based on faction.
        /// </summary>
        public enum class FactionReactions : System::Int32
        {
            Neutral = 0,
            
            Enemy = 0x1,
            
            Ally = 0x2,
            
            Friend = 0x3,
        };
        
        /// <summary>
        /// List of flying states.
        /// </summary>
        public enum class FlyingStates : System::Int32
        {
            NotFlying = 0,
            
            TakingOff = 0x1,
            
            Cruising = 0x2,
            
            Hovering = 0x3,
            
            Landing = 0x4,
        };
        
        /// <summary>
        /// Relationship rank entries.
        /// </summary>
        public enum class RelationshipRanks : System::Int32
        {
            Archnemesis = -4,
            
            Enemy = -3,
            
            Foe = -2,
            
            Rival = -1,
            
            Acquaintance = 0,
            
            Friend = 0x1,
            
            Confidant = 0x2,
            
            Ally = 0x3,
            
            Lover = 0x4,
        };
        
        public interface class TESSpellList : public BaseFormComponent
        {
        };
        
        public interface class BGSSkinForm : public BaseFormComponent
        {
        };
        
        public interface class BGSBipedObjectForm : public BaseFormComponent
        {
        };
        
        public interface class BGSAttackDataForm : public BaseFormComponent
        {
        };
        
        /// <summary>
        /// Action states of actor.
        /// </summary>
        public enum class ActorActionStates : System::Int32
        {
            NotAction = 0,
            
            WantToStart = 0x2,
            
            InProgress = 0x3,
            
            WantToStop = 0x4,
        };
        
        public interface class TESReactionForm : public BaseFormComponent
        {
        };
        
        public interface class TESRaceForm : public BaseFormComponent
        {
        };
        
        public interface class TESEnchantableForm : public BaseFormComponent
        {
        };
        
        public interface class TESValueForm : public BaseFormComponent
        {
        };
        
        public interface class BGSDestructibleObjectForm : public BaseFormComponent
        {
        };
        
        public interface class BGSPickupPutdownSounds : public BaseFormComponent
        {
        };
        
        public interface class TESBipedModelForm : public BaseFormComponent
        {
        };
        
        public interface class BGSBlockBashData : public BaseFormComponent
        {
        };
        
        public interface class TESActorBaseData : public BaseFormComponent
        {
        };
        
        public interface class TESAIForm : public BaseFormComponent
        {
        };
        
        public interface class BGSPerkRankArray : public BaseFormComponent
        {
        };
        
        public interface class BGSOverridePackCollection : public BaseFormComponent
        {
        };
        
        /// <summary>
        /// Another unnecessary string thing.
        /// </summary>
        public interface class BSString : public IMemoryObject
        {
            /// <summary>
            /// Gets the text.
            /// </summary>
            property System::String^ Text
            {
                System::String^ get();
            }
            
        };
        
        /// <summary>
        /// Types for opening the container menu.
        /// </summary>
        public enum class ContainerOpenTypes : System::Int32
        {
            NormalContainerOrLoot = 0,
            
            StealFromContainer = 0x1,
            
            PickPocket = 0x2,
            
            PlayerTeammateTrade = 0x3,
        };
        
        /// <summary>
        /// List of critical stages for actor.
        /// </summary>
        public enum class ActorCriticalStages : System::Int32
        {
            None = 0,
            
            GooStart = 0x1,
            
            GooEnd = 0x2,
            
            DisintegrateStart = 0x3,
            
            DisintegrateEnd = 0x4,
        };
        
        public interface class BSExtraData : public IVirtualObject
        {
            /// <summary>
            /// Gets or sets the next entry in list.
            /// </summary>
            property BSExtraData^ Next
            {
                BSExtraData^ get();
                void set(BSExtraData^ value);
            }
        };
        
        public interface class TESModelTextureSwap : public TESModel
        {
        };
        
        public interface class BGSOpenCloseForm : public IVirtualObject
        {
        };
        
        /// <summary>
        /// Magic effect archetypes list.
        /// </summary>
        public enum class Archetypes : System::Int32
        {
            ValueMod = 0,
            
            Script = 0x1,
            
            Dispel = 0x2,
            
            CureDisease = 0x3,
            
            Absorb = 0x4,
            
            DualValueMod = 0x5,
            
            Calm = 0x6,
            
            Demoralize = 0x7,
            
            Frenzy = 0x8,
            
            Disarm = 0x9,
            
            CommandSummoned = 0xA,
            
            Invisibility = 0xB,
            
            Light = 0xC,
            
            Lock = 0xF,
            
            Open = 0x10,
            
            BoundWeapon = 0x11,
            
            SummonCreature = 0x12,
            
            DetectLife = 0x13,
            
            Telekinesis = 0x14,
            
            Paralysis = 0x15,
            
            Reanimate = 0x16,
            
            SoulTrap = 0x17,
            
            TurnUndead = 0x18,
            
            Guide = 0x19,
            
            WerewolfFeed = 0x1A,
            
            CureParalysis = 0x1B,
            
            CureAddiction = 0x1C,
            
            CurePoison = 0x1D,
            
            Concussion = 0x1E,
            
            ValueAndParts = 0x1F,
            
            AccumulateMagnitude = 0x20,
            
            Stagger = 0x21,
            
            PeakValueMod = 0x22,
            
            Cloak = 0x23,
            
            Werewolf = 0x24,
            
            SlowTime = 0x25,
            
            Rally = 0x26,
            
            EnhanceWeapon = 0x27,
            
            SpawnHazard = 0x28,
            
            Etherealize = 0x29,
            
            Banish = 0x2A,
            
            Disguise = 0x2C,
            
            GrabActor = 0x2D,
            
            VampireLord = 0x2E,
        };
        
        /// <summary>
        /// List of reasons for removing a magic effect.
        /// </summary>
        public enum class MagicEffectRemovalReasons : System::Int32
        {
            Unknown = 0,
            
            Expired = 0x1,
            
            Activation = 0x2,
            
            CastSpellOrUseMagicItem = 0x3,
            
            Attacking = 0x4,
            
            Attacked = 0x5,
            
            Dialogue = 0x6,
        };
        
        /// <summary>
        /// Default game lookup map.
        /// </summary>
        generic <typename T1, typename T2>
        where T2 : IMemoryObject
        public interface class BSTDefaultScatterTable : public IMemoryObject, public System::Collections::Generic::IEnumerable<T2>
        {
            
            /// <summary>
            /// Gets the count of objects in this table.
            /// </summary>
            property System::Int32 Count
            {
                System::Int32 get();
            }
            
            /// <summary>
            /// Gets the max count of objects that can be put in the table.
            /// </summary>
            property System::Int32 Capacity
            {
                System::Int32 get();
            }
        };
        
        public interface class ICellAttachDetachEventSource : public IVirtualObject
        {
        };
        
        generic <typename T1>
        public interface class BSTSingletonExplicit : public IMemoryObject
        {
        };
        
        public interface class BSResource : public IMemoryObject
        {
            interface class ArchiveStreamOpenedEvent : public IMemoryObject
            {
            };
        };
        
        public interface class GridArray : public IVirtualObject
        {
            /// <summary>
            /// Gets the length of grid on a single axis.
            /// </summary>
            property System::Int32 Length
            {
                System::Int32 get();
            }
        };
        
        /// <summary>
        /// Game mutex class.
        /// </summary>
        public interface class Mutex : public IMemoryObject
        {
            /// <summary>
            /// Locks the mutex with method #1.
            /// </summary>
            void Lock1();
            
            /// <summary>
            /// Unlocks the mutex with method #1.
            /// </summary>
            void Unlock1();
        };
        
        /// <summary>
        /// The game menu manager.
        /// </summary>
        public interface class MenuManager : public IMemoryObject
        {
            /// <summary>
            /// Gets or sets whether to show menus.
            /// </summary>
            property System::Byte ShowMenus
            {
                System::Byte get();
                void set(System::Byte value);
            }
            
            /// <summary>
            /// Gets the pause game counter due to menus.
            /// </summary>
            property System::Int32 PauseGameCounter
            {
                System::Int32 get();
            }
            
            /// <summary>
            /// Gets the menu manager instance.
            /// </summary>
            static property MenuManager^ Instance
            {
                    MenuManager^ get()
                    {
                        return MemoryObject::FromAddress<MenuManager^>(Memory::ReadPointer(MCH::FromBase(0x141EE5B20), false));
                    }
            }
            
            /// <summary>
            /// Check if a menu is open.
            /// </summary>
            /// <param name="name">The name of menu.</param>
            bool IsMenuOpen(System::String^ name);
            
            /// <summary>
            /// Shows a message in the top left HUD.
            /// </summary>
            /// <param name="message">The message to show.</param>
            /// <param name="uiSound">The sound to play. This should be null unless you want to play some sound, for example "UISneakAttack".</param>
            /// <param name="unk">Unknown, set true.</param>
            static void ShowHUDMessage(System::String^ message, System::String^ uiSound, bool unk)
            {
                    if(message == nullptr) return;
                    if(uiSound != nullptr && uiSound->Length == 0) uiSound = nullptr;
                    auto allocMessage = Memory::AllocateString(message, false);
                    auto allocSound = uiSound != nullptr ? Memory::AllocateString(uiSound, false) : nullptr;
                    try
                    {
                        Memory::InvokeCdecl(MCH::FromBase(0x1408DA5C0), allocMessage->Address, allocSound != nullptr ? allocSound->Address : System::IntPtr::Zero, unk ? 1 : 0);
                    }
                    finally
                    {
                        delete allocMessage;
                        if(allocSound != nullptr) delete allocSound;
                    }
            }
        };
        
        /// <summary>
        /// The input manager of game.
        /// </summary>
        public interface class InputManager : public IMemoryObject
        {
            /// <summary>
            /// Gets the input manager instance.
            /// </summary>
            static property InputManager^ Instance
            {
                    InputManager^ get()
                    {
                        return MemoryObject::FromAddress<InputManager^>(Memory::ReadPointer(MCH::FromBase(0x142EECBD0), false));
                    }
            }
        };
        
        public interface class SimpleAnimationGraphManagerHolder : public IAnimationGraphManagerHolder
        {
        };
        
        public interface class BSLight : public NiRefObject
        {
        };
        
        /// <summary>
        /// List of states for spell casting.
        /// </summary>
        public enum class MagicCastingStates : System::Int32
        {
            None = 0,
            
            Charging = 0x2,
            
            Charged = 0x3,
            
            Released = 0x4,
            
            Concentrating = 0x6,
        };
        
        /// <summary>
        /// List of extra data types.
        /// </summary>
        public enum class ExtraDataTypes
        {
            Havok = 0x1,
            
            Cell3D = 0x2,
            
            CellWaterType = 0x3,
            
            RegionList = 0x4,
            
            SeenData = 0x5,
            
            EditorID = 0x6,
            
            CellMusicType = 0x7,
            
            CellSkyRegion = 0x8,
            
            ProcessMiddleLow = 0x9,
            
            DetachTime = 0xA,
            
            PersistentCell = 0xB,
            
            Action = 0xD,
            
            StartingPosition = 0xE,
            
            AnimGraphManager = 0x10,
            
            UsedMarkers = 0x12,
            
            DistantData = 0x13,
            
            RagDollData = 0x14,
            
            ContainerChanges = 0x15,
            
            Worn = 0x16,
            
            WornLeft = 0x17,
            
            PackageStartLocation = 0x18,
            
            Package = 0x19,
            
            TresPassPackage = 0x1A,
            
            RunOncePacks = 0x1B,
            
            ReferenceHandle = 0x1C,
            
            Follower = 0x1D,
            
            LevCreaModifier = 0x1E,
            
            Ghost = 0x1F,
            
            OriginalReference = 0x20,
            
            Ownership = 0x21,
            
            Global = 0x22,
            
            Rank = 0x23,
            
            Count = 0x24,
            
            Health = 0x25,
            
            TimeLeft = 0x27,
            
            Charge = 0x28,
            
            Light = 0x29,
            
            Lock = 0x2A,
            
            Teleport = 0x2B,
            
            MapMarker = 0x2C,
            
            LeveledCreature = 0x2D,
            
            LeveledItem = 0x2E,
            
            Scale = 0x2F,
            
            Seed = 0x30,
            
            MagicCaster = 0x31,
            
            PlayerCrimeList = 0x34,
            
            EnableStateParent = 0x36,
            
            EnableStateChildren = 0x37,
            
            ItemDropper = 0x38,
            
            DroppedItemList = 0x39,
            
            RandomTeleportMarker = 0x3A,
            
            SavedHavokData = 0x3C,
            
            CannotWear = 0x3D,
            
            Poison = 0x3E,
            
            LastFinishedSequence = 0x40,
            
            SavedAnimation = 0x41,
            
            NorthRotation = 0x42,
            
            SpawnContainer = 0x43,
            
            FriendHits = 0x44,
            
            HeadingTarget = 0x45,
            
            RefractionProperty = 0x47,
            
            StartingWorldOrCell = 0x48,
            
            Hotkey = 0x49,
            
            EditiorRefMoveData = 0x4B,
            
            InfoGeneralTopic = 0x4C,
            
            HasNoRumors = 0x4D,
            
            Sound = 0x4E,
            
            TerminalState = 0x4F,
            
            LinkedRef = 0x50,
            
            LinkedRefChildren = 0x51,
            
            ActivateRef = 0x52,
            
            ActivateRefChildren = 0x53,
            
            CanTalkToPlayer = 0x54,
            
            ObjectHealth = 0x55,
            
            CellImageSpace = 0x56,
            
            NavMeshPortal = 0x57,
            
            ModelSwap = 0x58,
            
            Radius = 0x59,
            
            FactionChanges = 0x5B,
            
            DismemberedLimbs = 0x5C,
            
            ActorCause = 0x5D,
            
            MultiBound = 0x5E,
            
            MultiBoundData = 0x5F,
            
            MultiBoundRef = 0x60,
            
            ReflectedRefs = 0x61,
            
            ReflectorRefs = 0x62,
            
            EmittanceSource = 0x63,
            
            RadioData = 0x64,
            
            CombatStyle = 0x65,
            
            Primitive = 0x67,
            
            OpenCloseActivateRef = 0x68,
            
            AnimNoteReceiver = 0x69,
            
            Ammo = 0x6A,
            
            PatrolRefData = 0x6B,
            
            PackageData = 0x6C,
            
            OcclusionShape = 0x6D,
            
            CollisionData = 0x6E,
            
            SayTopicInfoOnceADay = 0x6F,
            
            EncounterZone = 0x70,
            
            SayTopicInfo = 0x71,
            
            OcclusionPlaneRefData = 0x72,
            
            PortalRefData = 0x73,
            
            Portal = 0x74,
            
            Room = 0x75,
            
            HealthPerc = 0x76,
            
            RoomRefData = 0x77,
            
            GuardedRefData = 0x78,
            
            CreatureAwakeSound = 0x79,
            
            Horse = 0x7B,
            
            IgnoredBySandbox = 0x7C,
            
            CellAcousticSpace = 0x7D,
            
            ReservedMarkers = 0x7E,
            
            WeaponIdleSound = 0x7F,
            
            WaterLightRefs = 0x80,
            
            LitWaterRefs = 0x81,
            
            WeaponAttackSound = 0x82,
            
            ActivateLoopSound = 0x83,
            
            PatrolRefInUseData = 0x84,
            
            AshPileRef = 0x85,
            
            FollowerSwimBreadcrumbs = 0x87,
            
            AliasInstanceArray = 0x88,
            
            Location = 0x89,
            
            LocationRefType = 0x8B,
            
            PromotedRef = 0x8C,
            
            OutfitItem = 0x8E,
            
            LeveledItemBase = 0x90,
            
            LightData = 0x91,
            
            SceneData = 0x92,
            
            BadPosition = 0x93,
            
            HeadTrackingWeight = 0x94,
            
            FromAlias = 0x95,
            
            ShouldWear = 0x96,
            
            FavorCost = 0x97,
            
            AttachedArrows3D = 0x98,
            
            TextDisplayData = 0x99,
            
            AlphaCutoff = 0x9A,
            
            Enchantment = 0x9B,
            
            Soul = 0x9C,
            
            ForcedTarget = 0x9D,
            
            UniqueID = 0x9F,
            
            Flags = 0xA0,
            
            RefrPath = 0xA1,
            
            DecalGroup = 0xA2,
            
            LockList = 0xA3,
            
            ForcedLandingMarker = 0xA4,
            
            LargeRefOwnerCells = 0xA5,
            
            CellWaterEnvMap = 0xA6,
            
            CellGrassData = 0xA7,
            
            TeleportName = 0xA8,
            
            Interaction = 0xA9,
            
            WaterData = 0xAA,
            
            WaterCurrentZoneData = 0xAB,
            
            AttachRef = 0xAC,
            
            AttachRefChildren = 0xAD,
            
            GroupConstraint = 0xAE,
            
            ScriptedAnimDependence = 0xAF,
            
            CachedScale = 0xB0,
            
            RaceData = 0xB1,
            
            GIDBuffer = 0xB2,
            
            MissingRefIDs = 0xB3,
            
            HavokLink = 0xB4,
        };
        
        /// <summary>
        /// List of collision layers.
        /// </summary>
        public enum class CollisionLayers : System::Int32
        {
            Unidentified = 0,
            
            Static = 0x1,
            
            AnimStatic = 0x2,
            
            Transparent = 0x3,
            
            Clutter = 0x4,
            
            Weapon = 0x5,
            
            Projectile = 0x6,
            
            Spell = 0x7,
            
            Biped = 0x8,
            
            Trees = 0x9,
            
            Props = 0xA,
            
            Water = 0xB,
            
            Trigger = 0xC,
            
            Terrain = 0xD,
            
            Trap = 0xE,
            
            NonCollidable = 0xF,
            
            CloudTrap = 0x10,
            
            Ground = 0x11,
            
            Portal = 0x12,
            
            DebrisSmall = 0x13,
            
            DebrisLarge = 0x14,
            
            AcousticSpace = 0x15,
            
            ActorZone = 0x16,
            
            ProjectileZone = 0x17,
            
            GasTrap = 0x18,
            
            Shellcasing = 0x19,
            
            TransparentSmall = 0x1A,
            
            InvisibleWall = 0x1B,
            
            TransparentSmallAnim = 0x1C,
            
            Ward = 0x1D,
            
            CharController = 0x1E,
            
            StairHelper = 0x1F,
            
            DeadBip = 0x20,
            
            BipedNoCC = 0x21,
            
            AvoidBox = 0x22,
            
            CollisionBox = 0x23,
            
            CameraSphere = 0x24,
            
            DoorDetection = 0x25,
            
            ConeProjectile = 0x26,
            
            Camera = 0x27,
            
            ItemPicker = 0x28,
            
            Los = 0x29,
            
            PathingPick = 0x2A,
            
            CustomPick1 = 0x2B,
            
            CustomPick2 = 0x2C,
            
            SpellExplosion = 0x2D,
            
            DroppingPick = 0x2E,
            
            DeadActorZone = 0x2F,
            
            TriggerFallingTrap = 0x30,
            
            Navcut = 0x31,
            
            Critter = 0x32,
            
            SpellTrigger = 0x33,
            
            LivingAndDeadActors = 0x34,
            
            Detection = 0x35,
            
            TrapTrigger = 0x36,
        };
        
        /// <summary>
        /// Types of INI setting values.
        /// </summary>
        public enum class SettingTypes : System::Int32
        {
            Bool = 0,
            
            Char = 0x1,
            
            h = 0x2,
            
            Int = 0x3,
            
            UInt = 0x4,
            
            Float = 0x5,
            
            String = 0x6,
            
            Color = 0x7,
            
            a = 0x8,
            
            Unknown = 0x9,
        };
        
        /// <summary>
        /// INI setting.
        /// </summary>
        public interface class Setting : public IVirtualObject
        {
            /// <summary>
            /// Gets the name of setting. For example "fMouseHeadingSensitivity:Controls".
            /// </summary>
            property System::String^ Name
            {
                System::String^ get();
            }
            
            /// <summary>
            /// Gets the type of this setting.
            /// </summary>
            property SettingTypes Type
            {
                SettingTypes get();
            }
            
            /// <summary>
            /// Gets setting by name.
            /// </summary>
            /// <param name="name">The name. This is not case sensitive but must include the section as well.</param>
            /// <param name="searchIni">Search in Skyrim.ini file.</param>
            /// <param name="searchPrefIni">Search in SkyrimPrefs.ini file.</param>
            static Setting^ FindSettingByName(System::String^ name, bool searchIni, bool searchPrefIni)
            {
                    if(name == nullptr) throw gcnew System::ArgumentNullException("name");
                    auto func = MCH::FromBase(0x1403106C0);
                    auto str = Memory::AllocateString(name, false);
                    try
                    {
                        if(searchIni)
                        {
                            auto ptr = Memory::ReadPointer(MCH::FromBase(0x143044758), false);
                            if(ptr != System::IntPtr::Zero)
                            {
                                auto result = MemoryObject::FromAddress<Setting^>(Memory::InvokeCdecl(func, ptr, str->Address));
                                if(result != nullptr) return result;
                            }
                        }
                        if(searchPrefIni)
                        {
                            auto ptr = Memory::ReadPointer(MCH::FromBase(0x142F92A48), false);
                            if(ptr != System::IntPtr::Zero)
                            {
                                auto result = MemoryObject::FromAddress<Setting^>(Memory::InvokeCdecl(func, ptr, str->Address));
                                if(result != nullptr) return result;
                            }
                        }
                    }
                    finally
                    {
                        delete str;
                    }
                    return nullptr;
            }
            
            /// <summary>
            /// Gets the value as integer. This is only valid if the type is integer or unsigned integer.
            /// </summary>
            System::Int32 GetInt();
            
            /// <summary>
            /// Gets the value as float. This is only valid if the type is float.
            /// </summary>
            System::Single GetFloat();
            
            /// <summary>
            /// Gets the value as bool. This is only valid if the type is bool.
            /// </summary>
            bool GetBool();
            
            /// <summary>
            /// Gets the value as string. This is only valid if the type is string.
            /// </summary>
            System::String^ GetString();
            
            /// <summary>
            /// Sets the value as bool. This is only valid if type is bool.
            /// </summary>
            /// <param name="value">The value to set.</param>
            bool SetBool(bool value);
            
            /// <summary>
            /// Sets the value as integer. This is only valid if type is integer or unsigned integer.
            /// </summary>
            /// <param name="value">The value to set.</param>
            bool SetInt(System::Int32 value);
            
            /// <summary>
            /// Sets the value as float. This is only valid if type is float.
            /// </summary>
            /// <param name="value">The value to set.</param>
            bool SetFloat(System::Single value);
            
            /// <summary>
            /// Sets the value as string. This is only valid if type is string.
            /// </summary>
            /// <param name="value">The value to set.</param>
            bool SetString(System::String^ value);
        };
        
        public interface class MenuScreenData : public IMemoryObject
        {
            /// <summary>
            /// Gets the mouse X position in menu screen. This only changes if menu mode is set.
            /// </summary>
            property System::Single MouseXPosition
            {
                System::Single get();
            }
            
            /// <summary>
            /// Gets the mouse Y position in menu screen. This only changes if menu mode is set.
            /// </summary>
            property System::Single MouseYPosition
            {
                System::Single get();
            }
            
            /// <summary>
            /// Gets the screen width.
            /// </summary>
            property System::Single ScreenWidth
            {
                System::Single get();
            }
            
            /// <summary>
            /// Gets the screen height.
            /// </summary>
            property System::Single ScreenHeight
            {
                System::Single get();
            }
            
            /// <summary>
            /// Gets the menu screen data instance.
            /// </summary>
            static property MenuScreenData^ Instance
            {
                    MenuScreenData^ get()
                    {
                        return MemoryObject::FromAddress<MenuScreenData^>(Memory::ReadPointer(MCH::FromBase(0x142F4E140), false));
                    }
            }
        };
        
        public interface class InputEvent : public IVirtualObject
        {
        };
        
        public interface class TESFurnitureEvent : public IMemoryObject
        {
        };
        
        /// <summary>
        /// Player controls.
        /// </summary>
        public interface class PlayerControls : public BSTEventSink<InputEvent^>, public BSTEventSink<MenuOpenCloseEvent^>, public BSTEventSink<MenuModeChangeEvent^>, public BSTEventSink<TESFurnitureEvent^>
        {
            /// <summary>
            /// Gets or sets how much mouse moved horizontally. +X is right and -X is left.
            /// </summary>
            property System::Single MouseMovedX
            {
                System::Single get();
                void set(System::Single value);
            }
            
            /// <summary>
            /// Gets or sets how much mouse moved vertically. +Y is up and -Y is down.
            /// </summary>
            property System::Single MouseMovedY
            {
                System::Single get();
                void set(System::Single value);
            }
            
            /// <summary>
            /// Gets the PlayerControls instance.
            /// </summary>
            static property PlayerControls^ Instance
            {
                    PlayerControls^ get()
                    {
                        return MemoryObject::FromAddress<PlayerControls^>(Memory::ReadPointer(MCH::FromBase(0x142EECBD8), false));
                    }
            }
        };
        
        /// <summary>
        /// Leveled list form flags.
        /// </summary>
        [System::FlagsAttribute]
        public enum class TESLeveledListFlags : System::Byte
        {
            None = 0,
            
            CalculateFromAllLevelsLessOrEqualToPlayer = 0x1,
            
            CalculateForEachItemInCount = 0x2,
            
            UseAll = 0x4,
            
            SpecialLoot = 0x8,
        };
        
        /// <summary>
        /// Default game lookup map.
        /// </summary>
        generic <typename T1, typename T2>
        where T2 : IMemoryObject
        public interface class BSTDefaultScatterTable2 : public IMemoryObject, public System::Collections::Generic::IEnumerable<T2>
        {
            /// <summary>
            /// Gets the max count of objects that can be put in the table.
            /// </summary>
            property System::Int32 Capacity
            {
                System::Int32 get();
            }
            
            /// <summary>
            /// Gets the count of objects in this table.
            /// </summary>
            property System::Int32 Count
            {
                System::Int32 get();
            }
            
        };
        
        public interface class BGSMessageIcon : public BaseFormComponent
        {
        };
        
        public interface class TESAttackDamageForm : public BaseFormComponent
        {
        };
        
        public interface class BGSPreloadable : public BaseFormComponent
        {
        };
        
        /// <summary>
        /// Types of character states.
        /// </summary>
        public enum class bhkCharacterStateTypes : System::Int32
        {
            OnGround = 0,
            
            Jumping = 0x1,
            
            InAir = 0x2,
            
            Climbing = 0x3,
            
            Flying = 0x4,
            
            Swimming = 0x5,
            
            Unknown = 0xFF,
        };
        
        public interface class bhkPhantom : public bhkWorldObject
        {
        };
        
        public interface class bhkShapePhantom : public bhkPhantom
        {
        };
        
        public interface class bhkSimpleShapePhantom : public bhkShapePhantom
        {
        };
        
        /// <summary>
        /// Flags for mod file.
        /// </summary>
        [System::FlagsAttribute]
        public enum class TESFileRecordFlags : System::UInt32
        {
            None = 0,
            
            ESM = 0x1,
            
            Localized = 0x80,
            
            ESL = 0x200,
        };
        
        /// <summary>
        /// A plugin mod file.
        /// </summary>
        public interface class TESFile : public IMemoryObject
        {
            /// <summary>
            /// Gets the index if this file is not marked as ESL.
            /// </summary>
            property System::Byte EspIndex
            {
                System::Byte get();
            }
            
            /// <summary>
            /// Gets the author of file.
            /// </summary>
            property BSString^ Author
            {
                BSString^ get();
            }
            
            /// <summary>
            /// Gets the description of file.
            /// </summary>
            property BSString^ Description
            {
                BSString^ get();
            }
            
            /// <summary>
            /// Gets or sets the file record flags.
            /// </summary>
            property TESFileRecordFlags RecordFlags
            {
                TESFileRecordFlags get();
                void set(TESFileRecordFlags value);
            }
            
            /// <summary>
            /// Gets the index if this file is marked as ESL.
            /// </summary>
            property System::UInt16 EslIndex
            {
                System::UInt16 get();
            }
            
            /// <summary>
            /// Gets the name of mod file.
            /// </summary>
            property System::String^ Name
            {
                System::String^ get();
            }
            
            /// <summary>
            /// Gets the index of file. The index will be between 0 and 255 if ESP or ESM and will be between 0 and 4095 if ESL. Check RecordFlags for the
            /// ESL flag to see how to handle the index.
            /// </summary>
            property System::Int32 Index
            {
                System::Int32 get();
            }
        };
        
        public interface class NiSkinInstance : public NiObject
        {
        };
        
        public interface class BSDismemberSkinInstance : public NiSkinInstance
        {
        };
        interface class Actor;
        interface class EffectSetting;
        
        /// <summary>
        /// Magic effect instance.
        /// </summary>
        public interface class ActiveEffect : public IVirtualObject
        {
            /// <summary>
            /// Gets the caster actor.
            /// </summary>
            property Actor^ Caster
            {
                Actor^ get();
            }
            
            /// <summary>
            /// Gets the target of effect.
            /// </summary>
            property Actor^ Target
            {
                Actor^ get();
            }
            
            /// <summary>
            /// Dispel (remove) this effect.
            /// </summary>
            void Dispel();
            
            /// <summary>
            /// Gets the base effect that this instance is created from.
            /// </summary>
            property EffectSetting^ BaseEffect
            {
                EffectSetting^ get();
            }
            
            /// <summary>
            /// Check if effect is marked as inactive.
            /// </summary>
            property bool IsInactive
            {
                bool get();
            }
        };
        interface class BGSKeyword;
        
        /// <summary>
        /// Base form class. All forms in the game are inherited from this. Equivalent to the papyrus Form type.
        /// </summary>
        public interface class TESForm : public BaseFormComponent
        {
            /// <summary>
            /// Gets the flags of this form.
            /// </summary>
            property System::UInt32 FormFlags
            {
                System::UInt32 get();
            }
            
            /// <summary>
            /// Gets the unique identifier of this form.
            /// </summary>
            property System::UInt32 FormId
            {
                System::UInt32 get();
            }
            
            /// <summary>
            /// Gets the type identifier of this form.
            /// </summary>
            property FormTypes FormType
            {
                FormTypes get();
            }
            
            /// <summary>
            /// Gets the editor name for this form. Not all form types have this info and may return empty or null string.
            /// </summary>
            property System::String^ EditorId
            {
                System::String^ get();
            }
            
            /// <summary>
            /// Gets the name of form.
            /// </summary>
            property System::String^ Name
            {
                System::String^ get();
            }
            
            /// <summary>
            /// Determines whether this form has the "known" flag set. This is used for forms like spells and words of power.
            /// </summary>
            property bool PlayerKnows
            {
                bool get();
            }
            
            
            /// <summary>
            /// Lookups the form by identifier.
            /// </summary>
            /// <param name="formId">The form identifier.</param>
            /// <returns></returns>
            static TESForm^ LookupFormById(System::UInt32 formId)
            
            {
                return MemoryObject::FromAddress<TESForm^>(Memory::InvokeCdecl(MCH::FromBase(0x140194420), formId));
            }
            
            /// <summary>
            /// Lookups the form by identifier.
            /// </summary>
            /// <param name="formId">The form identifier.</param>
            /// <returns></returns>
            generic <typename T>
            where T : TESForm
            static T LookupFormById(System::UInt32 formId)
            
            {
                return MemoryObject::FromAddressSafeCast<T>(Memory::InvokeCdecl(MCH::FromBase(0x140194420), formId));
            }
            
            /// <summary>
            /// Gets the gold value of this form.
            /// </summary>
            property System::Int32 GoldValue
            {
                System::Int32 get();
            }
            
            /// <summary>
            /// Check if form has the specified keyword.
            /// </summary>
            /// <param name="keyword">The keyword to check for.</param>
            bool HasKeyword(BGSKeyword^ keyword);
            
            /// <summary>
            /// Check if form has the specified keyword.
            /// </summary>
            /// <param name="keyword">The keyword to check for.</param>
            bool HasKeywordText(System::String^ keyword);
            
            /// <summary>
            /// Check if form has a 3D model. This does not check if the model is loaded now! It only checks if it potentially has a world model.
            /// </summary>
            property bool Has3D
            {
                bool get();
            }
            
            /// <summary>
            /// Lookups the form by identifier from specific file.
            /// </summary>
            /// <param name="formId">The form identifier.</param>
            /// <param name="fileName">The file name.</param>
            /// <returns></returns>
            static TESForm^ LookupFormFromFile(System::UInt32 formId, System::String^ fileName)
            ;
            
            /// <summary>
            /// Lookups the form by identifier from specific file.
            /// </summary>
            /// <param name="formId">The form identifier.</param>
            /// <param name="fileName">The file name.</param>
            /// <returns></returns>
            generic <typename T>
            where T : TESForm
            static T LookupFormFromFile(System::UInt32 formId, System::String^ fileName)
            
            {
                auto form = LookupFormFromFile(formId, fileName);
                if(form == nullptr) return T();
                return form->As<T>();
            }
            
            /// <summary>
            /// Iterate through all game forms.
            /// </summary>
            /// <param name="func">The function to run on each form. If you return false the iteration stops.</param>
            /// <returns></returns>
            static void ForEachForm(System::Func<TESForm^, bool>^ func)
            {
                if(func == nullptr) throw gcnew System::ArgumentNullException("func");
                Memory::InvokeCdecl(MCH::FromBase(0x140C074C0), MCH::FromBase(0x141EEB150));
                try
                {
                    auto ptr = Memory::ReadPointer(MCH::FromBase(0x141EEACB8), false);
                    auto formMap = MemoryObject::FromAddress<BSTDefaultScatterTable2<unsigned int, TESForm^>^>(ptr);
                    if(formMap != nullptr)
                    {
                        for each(TESForm^ form in formMap)
                        {
                            if(!func(form)) break;
                        }
                    }
                }
                finally
                {
                    Memory::InvokeCdecl(MCH::FromBase(0x140C07780), MCH::FromBase(0x141EEB150));
                }
            }
        };
        
        public interface class TESWeather : public TESForm
        {
        };
        
        public interface class EffectSetting : public TESForm, public TESFullName, public BGSMenuDisplayObject, public BGSKeywordForm
        {
            /// <summary>
            /// Gets the archetype of effect.
            /// </summary>
            property Archetypes Archetype
            {
                Archetypes get();
            }
        };
        
        public interface class BGSKeyword : public TESForm
        {
            /// <summary>
            /// Gets the keyword text.
            /// </summary>
            property BSFixedString^ KeywordText
            {
                BSFixedString^ get();
            }
        };
        
        /// <summary>
        /// Perk form.
        /// </summary>
        public interface class BGSPerk : public TESForm, public TESFullName, public TESDescription, public TESIcon
        {
        };
        
        /// <summary>
        /// The word of power form.
        /// </summary>
        public interface class TESWordOfPower : public TESForm, public TESFullName
        {
        };
        
        public interface class TESObject : public TESForm
        {
        };
        
        public interface class TESBoundObject : public TESObject
        {
        };
        
        public interface class MagicItem : public TESBoundObject, public TESFullName, public BGSKeywordForm
        {
        };
        
        /// <summary>
        /// Spell form.
        /// </summary>
        public interface class SpellItem : public MagicItem, public BGSEquipType, public BGSMenuDisplayObject, public TESDescription
        {
        };
        
        /// <summary>
        /// Shout form.
        /// </summary>
        public interface class TESShout : public TESForm, public TESFullName, public BGSMenuDisplayObject, public BGSEquipType, public TESDescription
        {
            /// <summary>
            /// Gets or sets the first word of power.
            /// </summary>
            property TESWordOfPower^ Word1
            {
                TESWordOfPower^ get();
                void set(TESWordOfPower^ value);
            }
            
            /// <summary>
            /// Gets or sets the first spell.
            /// </summary>
            property SpellItem^ Spell1
            {
                SpellItem^ get();
                void set(SpellItem^ value);
            }
            
            /// <summary>
            /// Gets or sets the second word of power.
            /// </summary>
            property TESWordOfPower^ Word2
            {
                TESWordOfPower^ get();
                void set(TESWordOfPower^ value);
            }
            
            /// <summary>
            /// Gets or sets the second spell.
            /// </summary>
            property SpellItem^ Spell2
            {
                SpellItem^ get();
                void set(SpellItem^ value);
            }
            
            /// <summary>
            /// Gets or sets the third word of power.
            /// </summary>
            property TESWordOfPower^ Word3
            {
                TESWordOfPower^ get();
                void set(TESWordOfPower^ value);
            }
            
            /// <summary>
            /// Gets or sets the third spell.
            /// </summary>
            property SpellItem^ Spell3
            {
                SpellItem^ get();
                void set(SpellItem^ value);
            }
        };
        
        public interface class TESRace : public TESForm, public TESFullName, public TESDescription, public TESSpellList, public BGSSkinForm, public BGSBipedObjectForm, public BGSKeywordForm, public BGSAttackDataForm
        {
            /// <summary>
            /// Check if this race can head track.
            /// </summary>
            property bool CanHeadTrack
            {
                bool get();
            }
        };
        
        /// <summary>
        /// Location form.
        /// </summary>
        public interface class BGSLocation : public TESForm, public TESFullName, public BGSKeywordForm
        {
            /// <summary>
            /// Gets the parent location.
            /// </summary>
            property BGSLocation^ ParentLocation
            {
                BGSLocation^ get();
            }
        };
        
        /// <summary>
        /// Game data handler.
        /// </summary>
        public interface class DataHandler : public IMemoryObject
        {
            /// <summary>
            /// Gets the loaded mods.
            /// </summary>
            property ListNode<TESFile^>^ LoadedMods
            {
                ListNode<TESFile^>^ get();
            }
            
            /// <summary>
            /// Gets an array of all forms by form type.
            /// </summary>
            /// <param name="type">The form type.</param>
            BSTArray<TESForm^>^ GetAllFormsByType(FormTypes type);
            
            /// <summary>
            /// Gets the data handler instance.
            /// </summary>
            static property DataHandler^ Instance
            {
                DataHandler^ get()
                {
                    return MemoryObject::FromAddress<DataHandler^>(Memory::ReadPointer(MCH::FromBase(0x141EE5428), false));
                }
            }
        };
        
        /// <summary>
        /// Game faction form.
        /// </summary>
        public interface class TESFaction : public TESForm, public TESFullName, public TESReactionForm
        {
        };
        
        /// <summary>
        /// Game package form.
        /// </summary>
        public interface class TESPackage : public TESForm
        {
        };
        
        /// <summary>
        /// Game armor equipment form.
        /// </summary>
        public interface class TESObjectARMO : public TESBoundObject, public TESFullName, public TESRaceForm, public TESEnchantableForm, public TESValueForm, public TESWeightForm, public BGSDestructibleObjectForm, public BGSPickupPutdownSounds, public TESBipedModelForm, public BGSEquipType, public BGSBipedObjectForm, public BGSBlockBashData, public BGSKeywordForm, public TESDescription
        {
        };
        
        public interface class TESBoundAnimObject : public TESBoundObject
        {
        };
        
        public interface class TESContainer : public BaseFormComponent
        {
            interface class Data : public IMemoryObject
            {
            };
            
            interface class Entry : public IMemoryObject
            {
                /// <summary>
                /// Gets or sets the count of item.
                /// </summary>
                property System::Int32 Count
                {
                    System::Int32 get();
                    void set(System::Int32 value);
                }
                
                /// <summary>
                /// Gets or sets the item.
                /// </summary>
                property TESForm^ Item
                {
                    TESForm^ get();
                    void set(TESForm^ value);
                }
                
                /// <summary>
                /// Gets the entry data.
                /// </summary>
                property TESContainer::Data^ EntryData
                {
                    TESContainer::Data^ get();
                }
            };
            
            /// <summary>
            /// Gets the count of container entries.
            /// </summary>
            property System::Int32 ContainerEntriesCount
            {
                System::Int32 get();
            }
            
            /// <summary>
            /// Gets the container entry with index.
            /// </summary>
            /// <param name="index">The index of entry.</param>
            TESContainer::Entry^ GetContainerEntry(System::Int32 index);
        };
        
        public interface class TESActorBase : public TESBoundAnimObject, public TESActorBaseData, public TESContainer, public TESSpellList, public TESAIForm, public TESFullName, public ActorValueOwner, public BGSDestructibleObjectForm, public BGSSkinForm, public BGSKeywordForm, public BGSAttackDataForm, public BGSPerkRankArray
        {
        };
        
        /// <summary>
        /// Equivalent to ActorBase papyrus form.
        /// </summary>
        public interface class TESNPC : public TESActorBase, public TESRaceForm, public BGSOverridePackCollection, public BSTEventSink<MenuOpenCloseEvent^>
        {
        };
        
        /// <summary>
        /// Association form.
        /// </summary>
        public interface class BGSAssociationType : public TESForm
        {
        };
        
        /// <summary>
        /// The outfit form.
        /// </summary>
        public interface class BGSOutfit : public TESForm
        {
        };
        
        /// <summary>
        /// Container object.
        /// </summary>
        public interface class TESObjectCONT : public TESBoundAnimObject, public TESContainer, public TESFullName, public TESModelTextureSwap, public TESWeightForm, public BGSDestructibleObjectForm, public BGSOpenCloseForm
        {
        };
        
        public interface class BGSStoryManagerTreeForm : public TESForm
        {
        };
        
        /// <summary>
        /// Magic caster data.
        /// </summary>
        public interface class MagicCaster : public IVirtualObject
        {
            /// <summary>
            /// Gets the item that is being cast now. This is null unless actively charging or casting.
            /// </summary>
            property MagicItem^ CastItem
            {
                MagicItem^ get();
            }
            
            /// <summary>
            /// Gets the timer in seconds. For charging state it's the time left in seconds until charge is complete and can be released. For concentration
            /// state it's the amount of time in seconds we have been channeling for.
            /// </summary>
            property System::Single Timer
            {
                System::Single get();
            }
            
            /// <summary>
            /// Gets the state of this cast.
            /// </summary>
            property MagicCastingStates State
            {
                MagicCastingStates get();
            }
            
            /// <summary>
            /// Gets the cost of spell or the cost per second for concentration type spells. This is only valid while state is not none.
            /// </summary>
            property System::Single Cost
            {
                System::Single get();
            }
        };
        
        public interface class BGSConstructibleObject : public TESForm
        {
            /// <summary>
            /// Gets or sets the required keyword for the crafting station where this object can be made.
            /// </summary>
            property BGSKeyword^ CraftingStationKeyword
            {
                BGSKeyword^ get();
                void set(BGSKeyword^ value);
            }
            
            /// <summary>
            /// Gets or sets the created item.
            /// </summary>
            property TESForm^ CreatedItem
            {
                TESForm^ get();
                void set(TESForm^ value);
            }
            
            /// <summary>
            /// Gets or sets the count of how many items are created from one craft.
            /// </summary>
            property System::Int16 CreatedCount
            {
                System::Int16 get();
                void set(System::Int16 value);
            }
            
            /// <summary>
            /// Gets the requirements.
            /// </summary>
            property TESContainer^ Requirements
            {
                TESContainer^ get();
            }
        };
        
        public interface class TESGlobal : public TESForm
        {
        };
        
        /// <summary>
        /// Leveled list component of form.
        /// </summary>
        public interface class TESLeveledList : public BaseFormComponent
        {
            /// <summary>
            /// Entry of leveled list.
            /// </summary>
            interface class Entry : public IMemoryObject
            {
                /// <summary>
                /// Extra data of the entry.
                /// </summary>
                interface class Data : public IMemoryObject
                {
                    /// <summary>
                    /// Gets or sets the owner form. This is either an NPC or faction.
                    /// </summary>
                    property TESForm^ Owner
                    {
                        TESForm^ get();
                        void set(TESForm^ value);
                    }
                    
                    /// <summary>
                    /// Gets or sets the health. This is not a per cent here as it is in the creation kit! It's instead ratio where 1.2 is 120 per cent.
                    /// </summary>
                    property System::Single Health
                    {
                        System::Single get();
                        void set(System::Single value);
                    }
                    
                    /// <summary>
                    /// Gets or sets the global. This is only possible if the owner is set and is an NPC!
                    /// </summary>
                    property TESGlobal^ Global
                    {
                        TESGlobal^ get();
                        void set(TESGlobal^ value);
                    }
                    
                    /// <summary>
                    /// Gets or sets the required rank. This is only possible if owner is set and is a faction!
                    /// </summary>
                    property System::Int32 RequiredRank
                    {
                        System::Int32 get();
                        void set(System::Int32 value);
                    }
                };
                
                /// <summary>
                /// Gets or sets the form.
                /// </summary>
                property TESForm^ Form
                {
                    TESForm^ get();
                    void set(TESForm^ value);
                }
                
                /// <summary>
                /// Gets or sets the count.
                /// </summary>
                property System::Int16 Count
                {
                    System::Int16 get();
                    void set(System::Int16 value);
                }
                
                /// <summary>
                /// Gets or sets the player level when this item can begin appearing.
                /// </summary>
                property System::Int16 Level
                {
                    System::Int16 get();
                    void set(System::Int16 value);
                }
                
                /// <summary>
                /// Gets or sets the extra data.
                /// </summary>
                property TESLeveledList::Entry::Data^ Extra
                {
                    TESLeveledList::Entry::Data^ get();
                    void set(TESLeveledList::Entry::Data^ value);
                }
            };
            
            /// <summary>
            /// Gets or sets the leveled list array data base address.
            /// </summary>
            property System::IntPtr LeveledListEntriesArray
            {
                System::IntPtr get();
                void set(System::IntPtr value);
            }
            
            /// <summary>
            /// Gets or sets the skip chance of leveled list in per cent. This is only used if the global is not set.
            /// </summary>
            property System::Byte LeveledListSkipChance
            {
                System::Byte get();
                void set(System::Byte value);
            }
            
            /// <summary>
            /// Gets or sets the leveled list flags.
            /// </summary>
            property TESLeveledListFlags LeveledListFlagsValue
            {
                TESLeveledListFlags get();
                void set(TESLeveledListFlags value);
            }
            
            /// <summary>
            /// Gets or sets the amount of entries in the leveled list array. Setting this manually is not a good idea unless you're also changing the
            /// array.
            /// </summary>
            property System::Byte LeveledListEntriesCount
            {
                System::Byte get();
                void set(System::Byte value);
            }
            
            /// <summary>
            /// Gets or sets the global that is used to calculate the "skip" chance of this leveled list. If no global then regular skip chance variable on
            /// this form is used instead.
            /// </summary>
            property TESGlobal^ LeveledListSkipChanceGlobal
            {
                TESGlobal^ get();
                void set(TESGlobal^ value);
            }
            
            /// <summary>
            /// Gets the entry of leveled list by index.
            /// </summary>
            /// <param name="index">The index of entry in leveled list.</param>
            TESLeveledList::Entry^ GetLeveledListEntry(System::Int32 index);
            
            /// <summary>
            /// Gets all the leveled list entries.
            /// </summary>
            /// <returns></returns>
            System::Collections::Generic::List<TESLeveledList::Entry^>^ GetLeveledListEntries();
            
            /// <summary>
            /// Sets all the leveled list entries.
            /// </summary>
            /// <param name="entries">The entries.</param>
            void SetLeveledListEntries(System::Collections::Generic::IReadOnlyList<TESLeveledList::Entry^>^ entries);
        };
        
        /// <summary>
        /// Leveled item form.
        /// </summary>
        public interface class TESLevItem : public TESBoundObject, public TESLeveledList
        {
        };
        
        /// <summary>
        /// Leveled spell form.
        /// </summary>
        public interface class TESLevSpell : public TESBoundObject, public TESLeveledList
        {
        };
        
        /// <summary>
        /// Leveled NPC form.
        /// </summary>
        public interface class TESLevCharacter : public TESBoundAnimObject, public TESLeveledList, public TESModelTextureSwap
        {
        };
        
        public interface class AlchemyItem : public MagicItem, public TESModelTextureSwap, public TESIcon, public BGSMessageIcon, public TESWeightForm, public BGSEquipType, public BGSDestructibleObjectForm, public BGSPickupPutdownSounds
        {
        };
        
        /// <summary>
        /// Poison data of item.
        /// </summary>
        public interface class ExtraPoison : public BSExtraData
        {
            /// <summary>
            /// Gets or sets the count of charges left.
            /// </summary>
            property System::Int32 Count
            {
                System::Int32 get();
                void set(System::Int32 value);
            }
            
            /// <summary>
            /// Gets or sets the poison entry.
            /// </summary>
            property AlchemyItem^ Item
            {
                AlchemyItem^ get();
                void set(AlchemyItem^ value);
            }
        };
        
        public interface class BGSProjectile : public TESBoundObject, public TESFullName, public TESModel, public BGSPreloadable, public BGSDestructibleObjectForm
        {
        };
        
        /// <summary>
        /// Ammo form.
        /// </summary>
        public interface class TESAmmo : public TESBoundObject, public TESFullName, public TESModelTextureSwap, public TESIcon, public BGSMessageIcon, public TESValueForm, public TESWeightForm, public BGSDestructibleObjectForm, public BGSPickupPutdownSounds, public TESDescription, public BGSKeywordForm
        {
            /// <summary>
            /// Gets or sets the projectile data for this ammo form.
            /// </summary>
            property BGSProjectile^ ProjectileData
            {
                BGSProjectile^ get();
                void set(BGSProjectile^ value);
            }
        };
        interface class TESObjectCELL;
        
        public interface class TESWorldSpace : public TESForm, public TESFullName, public TESModel
        {
            /// <summary>
            /// Gets the cell by its coordinates.
            /// </summary>
            /// <param name="x">The X coordinate of cell.</param>
            /// <param name="y">The Y coordinate of cell.</param>
            TESObjectCELL^ GetCellByCoordinates(System::Int32 x, System::Int32 y);
            
            /// <summary>
            /// Gets the cell by position in world.
            /// </summary>
            /// <param name="x">The X position.</param>
            /// <param name="y">The Y position.</param>
            TESObjectCELL^ GetCellByPosition(System::Single x, System::Single y);
        };
        
        /// <summary>
        /// Grid of loaded cells.
        /// </summary>
        public interface class GridCellArray : public GridArray
        {
            /// <summary>
            /// Gets the cell in the grid. The arguments are not cell coordinates in world space but rather cell index in the grid!
            /// </summary>
            /// <param name="x">The index of cell in grid.</param>
            /// <param name="y">The index of cell in grid.</param>
            TESObjectCELL^ GetCell(System::Int32 x, System::Int32 y);
        };
        
        public interface class TES : public ICellAttachDetachEventSource, public BSTEventSink<BSResource::ArchiveStreamOpenedEvent^>, public BSTEventSink<PositionPlayerEvent^>
        {
            /// <summary>
            /// Gets the cell grid of worldspace.
            /// </summary>
            property GridCellArray^ CellGrid
            {
                GridCellArray^ get();
            }
            
            /// <summary>
            /// Gets the current interior cell.
            /// </summary>
            property TESObjectCELL^ CurrentInteriorCell
            {
                TESObjectCELL^ get();
            }
            
            /// <summary>
            /// Gets the uGridsToLoad:General INI setting value.
            /// </summary>
            property System::Int32 GridsToLoad
            {
                System::Int32 get();
            }
            
            /// <summary>
            /// Gets loaded cells.
            /// </summary>
            System::Collections::Generic::List<TESObjectCELL^>^ GetLoadedCells();
            
            /// <summary>
            /// Gets the TES game world handler.
            /// </summary>
            static property TES^ Instance
            {
                TES^ get()
                {
                    return MemoryObject::FromAddress<TES^>(Memory::ReadPointer(MCH::FromBase(0x142F4DB20), false));
                }
            }
        };
        interface class NiPoint3;
        
        public interface class NiMatrix33 : public IMemoryObject
        {
            property System::IntPtr Data
            {
                System::IntPtr get();
            }
            
            /// <summary>
            /// Calculate inverse of this matrix.
            /// </summary>
            /// <param name="result">The result is set here.</param>
            void Inverse(NiMatrix33^ result);
            
            /// <summary>
            /// Set the matrix to default.
            /// </summary>
            /// <param name="scale">The scale to set.</param>
            void Identity(System::Single scale);
            
            /// <summary>
            /// Multiply two matrices.
            /// </summary>
            /// <param name="other">The other matrix to multiply with.</param>
            /// <param name="result">The result will be set here.</param>
            void Multiply(NiMatrix33^ other, NiMatrix33^ result);
            
            /// <summary>
            /// Transpose the matrix.
            /// </summary>
            /// <param name="result">The result will be set here.</param>
            void Transpose(NiMatrix33^ result);
            
            /// <summary>
            /// Gets or sets the value at specified index.
            /// </summary>
            property float default[System::Int32, System::Int32]
            {
                float get(System::Int32 i, System::Int32 j);
                void set(System::Int32 i, System::Int32 j, float value);
            }
            
            /// <summary>
            /// Rotates the matrix round Z axis.
            /// </summary>
            /// <param name="rad">Amount to rotate by.</param>
            /// <param name="result">The result is set here.</param>
            void RotateZ(System::Single rad, NiMatrix33^ result);
            
            /// <summary>
            /// Rotates the matrix around Y axis.
            /// </summary>
            /// <param name="rad">Amount to rotate by.</param>
            /// <param name="result">The result is set here.</param>
            void RotateY(System::Single rad, NiMatrix33^ result);
            
            /// <summary>
            /// Rotates the matrix around X axis.
            /// </summary>
            /// <param name="rad">Amount to rotate by.</param>
            /// <param name="result">The result is set here.</param>
            void RotateX(System::Single rad, NiMatrix33^ result);
            
            /// <summary>
            /// Gets the axis angle representation of the rotation matrix.
            /// </summary>
            /// <param name="resultAxis">The result axis will be set here.</param>
            /// <param name="angle">The result angle will be set here (in radians).</param>
            void GetAxisAngle(NiPoint3^ resultAxis, System::Single% angle);
            
            /// <summary>
            /// Gets the rotation matrix from axis angle representation.
            /// </summary>
            /// <param name="axis">The axis.</param>
            /// <param name="angle">The angle (in radians).</param>
            void GetFromAxisAngle(NiPoint3^ axis, System::Single angle);
            
            /// <summary>
            /// Gets the euler angles from rotation matrix (as radian).
            /// </summary>
            /// <param name="result">The resulting angles will be set here (as radian).</param>
            void GetEulerAngles(NiPoint3^ result);
            
            /// <summary>
            /// Interpolate between two rotation matrices.
            /// </summary>
            /// <param name="other">The other rotation matrix.</param>
            /// <param name="ratio">The ratio of interpolation where 0 is current matrix and 1 is the other matrix.</param>
            /// <param name="result">The result will be set here.</param>
            void Interpolate(NiMatrix33^ other, System::Single ratio, NiMatrix33^ result);
        };
        
        /// <summary>
        /// Data type for a point in three dimensional space.
        /// </summary>
        public interface class NiPoint3 : public IMemoryObject
        {
            /// <summary>
            /// Gets or sets the value on the X-coordinate.
            /// </summary>
            property System::Single X
            {
                System::Single get();
                void set(System::Single value);
            }
            
            /// <summary>
            /// Gets or sets the value on the Y-coordinate.
            /// </summary>
            property System::Single Y
            {
                System::Single get();
                void set(System::Single value);
            }
            
            /// <summary>
            /// Gets or sets the value on the Z-coordinate.
            /// </summary>
            property System::Single Z
            {
                System::Single get();
                void set(System::Single value);
            }
            
            /// <summary>
            /// Gets the length of the vector.
            /// </summary>
            property System::Single Length
            {
                System::Single get();
            }
            
            /// <summary>
            /// Determine if this vector is zero.
            /// </summary>
            property bool IsZero
            {
                bool get();
            }
            
            /// <summary>
            /// Turn this vector into a normal.
            /// </summary>
            /// <param name="result">The result will be set here.</param>
            void Normalize(NiPoint3^ result);
            
            /// <summary>
            /// Gets the distance between two points.
            /// </summary>
            /// <param name="other">Other point.</param>
            System::Single GetDistance(NiPoint3^ other);
            
            /// <summary>
            /// Calculate the cross product.
            /// </summary>
            /// <param name="other">The other point to calculate with.</param>
            /// <param name="result">The result will be set in this instance.</param>
            void Cross(NiPoint3^ other, NiPoint3^ result);
            
            /// <summary>
            /// Calculate the dot product.
            /// </summary>
            /// <param name="other">The other point.</param>
            System::Single Dot(NiPoint3^ other);
            
            /// <summary>
            /// Add together two points.
            /// </summary>
            /// <param name="other">The other point to add.</param>
            /// <param name="result">The result will be set here.</param>
            void Add(NiPoint3^ other, NiPoint3^ result);
            
            /// <summary>
            /// Subtract one point from another.
            /// </summary>
            /// <param name="other">The other point to subtract by.</param>
            /// <param name="result">The result will be set here.</param>
            void Subtract(NiPoint3^ other, NiPoint3^ result);
            
            /// <summary>
            /// Multiply a point by an amount.
            /// </summary>
            /// <param name="amount">The amount to multiply by.</param>
            /// <param name="result">The result will be set here.</param>
            void Multiply(System::Single amount, NiPoint3^ result);
            
            /// <summary>
            /// Gets the angle difference of two vectors as a rotation matrix.
            /// </summary>
            /// <param name="other">The other vector to get difference from.</param>
            /// <param name="result">The resulting rotation matrix will be set here.</param>
            void GetAngleDifference(NiPoint3^ other, NiMatrix33^ result);
        };
        
        public interface class NiTransform : public IMemoryObject
        {
            /// <summary>
            /// The rotation matrix.
            /// </summary>
            property NiMatrix33^ Rotation
            {
                NiMatrix33^ get();
            }
            
            /// <summary>
            /// The position.
            /// </summary>
            property NiPoint3^ Position
            {
                NiPoint3^ get();
            }
            
            /// <summary>
            /// The scale.
            /// </summary>
            property System::Single Scale
            {
                System::Single get();
                void set(System::Single value);
            }
            
            /// <summary>
            /// Sets the rotation matrix to look at a specific point given the transform's current location.
            /// </summary>
            /// <param name="target">The target location to look at.</param>
            void LookAt(NiPoint3^ target);
            
            /// <summary>
            /// Moves the transform along its three axes depending on the rotation matrix. +X is right. -X is left. +Y is forward. -Y is backwards. +Z is
            /// up. -Z is down.
            /// </summary>
            /// <param name="amount">The amount to move in each axis. +X is right. -X is left. +Y is forward. -Y is backwards. +Z is up. -Z is down.</param>
            /// <param name="result">The resulting position will be set here.</param>
            void Translate(NiPoint3^ amount, NiPoint3^ result);
        };
        
        /// <summary>
        /// Wrapper for havok rigid body.
        /// </summary>
        public interface class bhkRigidBody : public bhkEntity
        {
            /// <summary>
            /// Activate the havok object.
            /// </summary>
            void Activate();
            
            /// <summary>
            /// Deactivate the havok object.
            /// </summary>
            void Deactivate();
            
            void ApplyLinearImpulse(NiPoint3^ amount);
        };
        
        /// <summary>
        /// Crosshair reference data.
        /// </summary>
        public interface class CrossHairPickData : public IMemoryObject
        {
            /// <summary>
            /// Gets the current object reference handle. This is 0 if no activatable object reference.
            /// </summary>
            property System::UInt32 TargetRefHandle
            {
                System::UInt32 get();
            }
            
            /// <summary>
            /// Gets the target actor reference handle. This is only set if the target is an actor.
            /// </summary>
            property System::UInt32 TargetActorRefHandle
            {
                System::UInt32 get();
            }
            
            /// <summary>
            /// Gets the collision point. This is a very large value if nothing was in range of picker. This is also set if something was in range of picker
            /// but isn't activatable.
            /// </summary>
            property NiPoint3^ CollisionPoint
            {
                NiPoint3^ get();
            }
            
            /// <summary>
            /// Gets the target collision object that we hit. This appears to only be set if target is an actor.
            /// </summary>
            property bhkRigidBody^ TargetCollider
            {
                bhkRigidBody^ get();
            }
            
            /// <summary>
            /// Gets the pick collider object. This is the shape used to calculate the collision point of pickable object.
            /// </summary>
            property bhkSimpleShapePhantom^ PickCollider
            {
                bhkSimpleShapePhantom^ get();
            }
            
            /// <summary>
            /// Gets the CrossHairPickData instance.
            /// </summary>
            static property CrossHairPickData^ Instance
            {
                    CrossHairPickData^ get()
                    {
                        return MemoryObject::FromAddress<CrossHairPickData^>(Memory::ReadPointer(MCH::FromBase(0x142F281D0), false));
                    }
            }
        };
        interface class NiNode;
        
        /// <summary>
        /// Actor magic caster type.
        /// </summary>
        public interface class ActorMagicCaster : public MagicCaster, public SimpleAnimationGraphManagerHolder, public BSTEventSink<BSAnimationGraphEvent^>
        {
            /// <summary>
            /// Gets the owner actor.
            /// </summary>
            property Actor^ Owner
            {
                Actor^ get();
            }
            
            /// <summary>
            /// The light effect attached to the node.
            /// </summary>
            property BSLight^ EffectLight
            {
                BSLight^ get();
            }
            
            /// <summary>
            /// Gets the node where effect in hand would be placed if actor is wielding any magic. This is always set even if there's no actual magic
            /// equipped. e.g. NPC L MagicNode [LMag]
            /// </summary>
            property NiNode^ EffectNode
            {
                NiNode^ get();
            }
            
            /// <summary>
            /// Gets the caster race.
            /// </summary>
            property TESRace^ CasterRace
            {
                TESRace^ get();
            }
            
            /// <summary>
            /// Gets the magic node. This is only set if actually wielding any magic. It is most likely where the effect will be fired from. e.g. MagicLeft
            /// </summary>
            property NiNode^ FireNode
            {
                NiNode^ get();
            }
            
            /// <summary>
            /// Gets the type of caster this is.
            /// </summary>
            property EquippedSpellSlots ActorCasterType
            {
                EquippedSpellSlots get();
            }
        };
        
        /// <summary>
        /// Image space modifier form.
        /// </summary>
        public interface class TESImageSpaceModifier : public TESForm
        {
            /// <summary>
            /// Applies this image space modifier now.
            /// </summary>
            /// <param name="strength">The strength. Set 1.0 for normal.</param>
            /// <param name="node">Unknown node. This is null in almost all cases.</param>
            void Apply(System::Single strength, NiNode^ node);
            
            /// <summary>
            /// Removes this image space modifier.
            /// </summary>
            void Remove();
        };
        interface class TESObjectREFR;
        
        /// <summary>
        /// Implementation of active magic effect owner.
        /// </summary>
        public interface class MagicTarget : public IVirtualObject
        {
            /// <summary>
            /// Gets the active magic effects list.
            /// </summary>
            property ListNode<ActiveEffect^>^ ActiveEffects
            {
                ListNode<ActiveEffect^>^ get();
            }
            
            /// <summary>
            /// Check if target has magic effect with the specified keyword.
            /// </summary>
            /// <param name="keyword">The keyword to check.</param>
            /// <param name="item">If a magic effect is found the item where it came from will be set here. If multiple magic effects with the specified keyword then only the first item will be returned.</param>
            bool HasMagicEffectWithKeyword(BGSKeyword^ keyword, MagicItem^% item);
            
            /// <summary>
            /// Check if target has magic effect with the specified keyword.
            /// </summary>
            /// <param name="keyword">The keyword name to check.</param>
            /// <param name="item">If a magic effect is found the item where it came from will be set here. If multiple magic effects with the specified keyword then only the first item will be returned.</param>
            bool HasMagicEffectWithKeywordText(System::String^ keyword, MagicItem^% item);
            
            /// <summary>
            /// Check if this target has a magic effect.
            /// </summary>
            /// <param name="effect">The effect to search.</param>
            bool HasMagicEffect(EffectSetting^ effect);
            
            /// <summary>
            /// Dispels all effects with specified archetype.
            /// </summary>
            /// <param name="archetype">The effect types to remove.</param>
            /// <param name="onlyFromCaster">Only remove effects whose caster is this object. If this is null then remove all effects of this archetype.</param>
            void DispelEffectsWithArchetype(Archetypes archetype, TESObjectREFR^ onlyFromCaster);
            
            /// <summary>
            /// Check if this owner has any magic effects that deal damage.
            /// </summary>
            property bool HasMagicEffectThatCausesDamage
            {
                bool get();
            }
            
            /// <summary>
            /// Finds the first effect that matches archetype.
            /// </summary>
            /// <param name="archetype">The archetype to search for.</param>
            /// <param name="allowInactive">Allow effect to have inactive flag?</param>
            ActiveEffect^ FindFirstEffectWithArchetype(Archetypes archetype, bool allowInactive);
        };
        
        /// <summary>
        /// Inventory data.
        /// </summary>
        public interface class ExtraContainerChanges : public BSExtraData
        {
            /// <summary>
            /// Item entry in inventory.
            /// </summary>
            interface class ItemEntry : public IMemoryObject
            {
                /// <summary>
                /// Gets the template of object.
                /// </summary>
                property TESForm^ Template
                {
                    TESForm^ get();
                }
                
                /// <summary>
                /// Gets the extra data of object.
                /// </summary>
                property ListNode<BSExtraDataList^>^ ExtraData
                {
                    ListNode<BSExtraDataList^>^ get();
                }
                
                /// <summary>
                /// Gets the count of this object.
                /// </summary>
                property System::Int32 Count
                {
                    System::Int32 get();
                }
            };
            
            /// <summary>
            /// Inventory data.
            /// </summary>
            interface class Data : public IMemoryObject
            {
                /// <summary>
                /// Gets the owner of this data.
                /// </summary>
                property TESObjectREFR^ Owner
                {
                    TESObjectREFR^ get();
                }
                
                /// <summary>
                /// Gets the objects in this inventory.
                /// </summary>
                property ListNode<ExtraContainerChanges::ItemEntry^>^ Objects
                {
                    ListNode<ExtraContainerChanges::ItemEntry^>^ get();
                }
            };
        };
        
        /// <summary>
        /// Base object reference class. Equivalent to the papyrus ObjectReference type.
        /// </summary>
        public interface class TESObjectREFR : public TESForm, public BSHandleRefObject, public BSTEventSink<BSAnimationGraphEvent^>, public IAnimationGraphManagerHolder
        {
            /// <summary>
            /// Gets the base form of this reference.
            /// </summary>
            property TESForm^ BaseForm
            {
                TESForm^ get();
            }
            
            /// <summary>
            /// Gets the parent cell of this reference.
            /// </summary>
            property TESObjectCELL^ ParentCell
            {
                TESObjectCELL^ get();
            }
            
            /// <summary>
            /// Gets the extra data of this reference.
            /// </summary>
            property BSExtraDataList^ ExtraDataList
            {
                BSExtraDataList^ get();
            }
            
            /// <summary>
            /// Gets the position of object reference.
            /// </summary>
            property NiPoint3^ Position
            {
                NiPoint3^ get();
            }
            
            /// <summary>
            /// Gets the rotation of object.
            /// </summary>
            property NiPoint3^ Rotation
            {
                NiPoint3^ get();
            }
            
            /// <summary>
            /// Gets the root node of object. This is null if not loaded.
            /// </summary>
            property NiNode^ Node
            {
                NiNode^ get();
            }
            
            /// <summary>
            /// Activate this object.
            /// </summary>
            /// <param name="activator">The object who is performing this activation.</param>
            /// <param name="skipEvents">Skip script processing and use default object activate processing only?</param>
            bool Activate(TESObjectREFR^ activator, bool skipEvents);
            
            /// <summary>
            /// Gets the current location of object.
            /// </summary>
            property BGSLocation^ CurrentLocation
            {
                BGSLocation^ get();
            }
            
            /// <summary>
            /// Force open the inventory of this object. Does nothing if this object is not a container or actor. If type is set to Normal and this object
            /// is not an actor the type may be overwritten to steal if the player does not own the container!
            /// </summary>
            /// <param name="type">The type of opening. If type is set to Normal and this object is not an actor the type may be overwritten to steal if the player does not own the container!</param>
            void OpenInventory(ContainerOpenTypes type);
            
            /// <summary>
            /// Check if this object is capable of having objects in it as container.
            /// </summary>
            property bool HasInventory
            {
                bool get();
            }
            
            /// <summary>
            /// Gets the inventory of object. This may return null.
            /// </summary>
            property ExtraContainerChanges::Data^ Inventory
            {
                ExtraContainerChanges::Data^ get();
            }
            
            /// <summary>
            /// Sets the animation graph variable and returns if successful. If false is returned it's most likely the variable was not found in the
            /// animation graph.
            /// </summary>
            /// <param name="name">The variable name.</param>
            /// <param name="value">The value to set.</param>
            bool SetAnimationVariableBool(System::String^ name, bool value);
            
            /// <summary>
            /// Gets the magic caster component of object.
            /// </summary>
            /// <param name="slot">The slot. Only left, right, other are valid (other is voice slot).</param>
            MagicCaster^ GetMagicCaster(EquippedSpellSlots slot);
            
            
            /// <summary>
            /// Gets the extra data by type.
            /// </summary>
            /// <param name="type">The type of extra data.</param>
            BSExtraData^ GetExtraData(ExtraDataTypes type);
            
            /// <summary>
            /// Gets the root skeleton node.
            /// </summary>
            /// <param name="firstPerson">Get first person or third person skeleton?</param>
            NiNode^ GetSkeletonNode(bool firstPerson);
        };
        
        /// <summary>
        /// Actor class implementation of game. This is equivalent to the papyrus "Actor" type.
        /// </summary>
        public interface class Actor : public TESObjectREFR, public MagicTarget, public ActorValueOwner, public ActorState, public BSTEventSink<BSTransformDeltaEvent^>, public BSTEventSink<bhkCharacterMoveFinishEvent^>, public IPostAnimationChannelUpdateFunctor
        {
            /// <summary>
            /// Gets or sets the race of actor.
            /// </summary>
            property TESRace^ Race
            {
                TESRace^ get();
                void set(TESRace^ value);
            }
            
            /// <summary>
            /// Updates the movement controller location for actor.
            /// </summary>
            /// <param name="pos">The position to update to.</param>
            void UpdateMovementControllerPosition(NiPoint3^ pos);
            
            /// <summary>
            /// Adds the perk to actor.
            /// </summary>
            /// <param name="perk">The perk to add.</param>
            void AddPerk(BGSPerk^ perk);
            
            /// <summary>
            /// Adds a shout to this actor.
            /// </summary>
            /// <param name="shout">The shout to add.</param>
            void AddShout(TESShout^ shout);
            
            /// <summary>
            /// Adds a spell to this actor. Returns true on success.
            /// </summary>
            /// <param name="spell">The spell to add.</param>
            /// <param name="showLearnedMessage">Show the learned spell message in HUD? If this actor is not player the argument is ignored.</param>
            bool AddSpell(SpellItem^ spell, bool showLearnedMessage);
            
            /// <summary>
            /// Sets whether to allow bleedout dialogue for this actor.
            /// </summary>
            /// <param name="allow">Allow or not?</param>
            void AllowBleedoutDialogue(bool allow);
            
            /// <summary>
            /// Sets whether to allow player dialogue or not.
            /// </summary>
            /// <param name="allow">Allow or not?</param>
            void AllowPCDialogue(bool allow);
            
            /// <summary>
            /// Clears this actor's arrested state.
            /// </summary>
            void ClearArrested();
            
            /// <summary>
            /// Can this actor fly here?
            /// </summary>
            property bool CanFlyHere
            {
                bool get();
            }
            
            /// <summary>
            /// Clear all expression overrides on this actor.
            /// </summary>
            void ClearExpressionOverride();
            
            /// <summary>
            /// Clear shot arrows from actor.
            /// </summary>
            void ClearExtraArrows();
            
            /// <summary>
            /// Clear movement offset.
            /// </summary>
            void ClearKeepOffsetFromActor();
            
            /// <summary>
            /// Clears the actor from looking at an object.
            /// </summary>
            void ClearLookAtObject();
            
            /// <summary>
            /// Dismounts the actor.
            /// </summary>
            bool Dismount();
            
            /// <summary>
            /// Dispel all spells from the actor.
            /// </summary>
            void DispelAllSpells();
            
            /// <summary>
            /// Attempts to dispel a spell from actor.
            /// </summary>
            /// <param name="spell">The spell to dispel.</param>
            bool DispelSpell(SpellItem^ spell);
            
            /// <summary>
            /// Applies a spell to target in combat.
            /// </summary>
            /// <param name="spell">The spell to apply.</param>
            /// <param name="target">The target.</param>
            void DoCombatSpellApply(SpellItem^ spell, TESObjectREFR^ target);
            
            /// <summary>
            /// Force actor to draw their weapon.
            /// </summary>
            void DrawWeapon();
            
            /// <summary>
            /// Enable or disable the actor's AI.
            /// </summary>
            /// <param name="enable">Enable or disable?</param>
            void EnableAI(bool enable);
            
            /// <summary>
            /// Remove actor from end deferred kill state.
            /// </summary>
            void EndDeferredKill();
            
            /// <summary>
            /// Equips an item on this actor.
            /// </summary>
            /// <param name="form">The object to equip.</param>
            /// <param name="preventUnequip">Prevent unequipping the item?</param>
            /// <param name="silent">Do this silently?</param>
            void EquipItem(TESForm^ form, bool preventUnequip, bool silent);
            
            /// <summary>
            /// Equips a shout on the actor.
            /// </summary>
            /// <param name="shout">The shout to equip.</param>
            void EquipShout(TESShout^ shout);
            
            /// <summary>
            /// Force actor to re-evaluate package.
            /// </summary>
            void EvaluatePackage();
            
            /// <summary>
            /// Gets the amount of gold required to bribe actor.
            /// </summary>
            System::Int32 GetBribeAmount();
            
            /// <summary>
            /// Gets the combat state of actor.
            /// </summary>
            property ActorCombatStates CombatState
            {
                ActorCombatStates get();
            }
            
            /// <summary>
            /// Gets the combat target of this actor.
            /// </summary>
            property Actor^ CombatTarget
            {
                Actor^ get();
            }
            
            /// <summary>
            /// Gets or sets the crime faction of this actor. This may be null if no crime faction.
            /// </summary>
            property TESFaction^ CrimeFaction
            {
                TESFaction^ get();
                void set(TESFaction^ value);
            }
            
            /// <summary>
            /// Gets the current package of actor.
            /// </summary>
            property TESPackage^ CurrentPackage
            {
                TESPackage^ get();
            }
            
            /// <summary>
            /// Gets the current actor's dialogue target.
            /// </summary>
            property Actor^ DialogueTarget
            {
                Actor^ get();
            }
            
            /// <summary>
            /// Gets the equipped armor in slot.
            /// </summary>
            /// <param name="slot">The slot to check.</param>
            TESObjectARMO^ GetEquippedArmorInSlot(EquipSlots slot);
            
            /// <summary>
            /// Gets the type of item equipped.
            /// </summary>
            /// <param name="slot">The slot to check.</param>
            EquippedItemTypes GetEquippedItemType(EquippedHandSlots slot);
            
            /// <summary>
            /// Gets the equipped shield of actor.
            /// </summary>
            TESObjectARMO^ GetEquippedShield();
            
            /// <summary>
            /// Gets the currently equipped shout.
            /// </summary>
            TESShout^ GetEquippedShout();
            
            /// <summary>
            /// Gets the equipped spell.
            /// </summary>
            /// <param name="slot">The slot to check.</param>
            SpellItem^ GetEquippedSpell(EquippedSpellSlots slot);
            
            /// <summary>
            /// Gets the faction rank of actor. The result is -2 if actor is not in faction. -1 if actor is in faction but the rank was set to -1 (this
            /// should be treated as not in faction but may eventually become in faction). And any other value for the rank in faction.
            /// </summary>
            /// <param name="faction">The faction to check.</param>
            System::Int32 GetFactionRank(TESFaction^ faction);
            
            /// <summary>
            /// Gets the reaction of this actor to another actor based on faction.
            /// </summary>
            /// <param name="other">The other actor.</param>
            FactionReactions GetFactionReaction(Actor^ other);
            
            /// <summary>
            /// Gets the flying state of actor.
            /// </summary>
            property FlyingStates FlyingState
            {
                FlyingStates get();
            }
            
            /// <summary>
            /// Gets or sets the forced landing marker this actor must land at.
            /// </summary>
            property TESObjectREFR^ ForcedLandingMarker
            {
                TESObjectREFR^ get();
                void set(TESObjectREFR^ value);
            }
            
            /// <summary>
            /// Gets the amount of gold currently on this actor.
            /// </summary>
            System::Int32 GetGoldAmount();
            
            /// <summary>
            /// Gets the highest relationship rank this actor has. This does not take into account changes made during gameplay.
            /// </summary>
            property RelationshipRanks HighestRelationshipRank
            {
                RelationshipRanks get();
            }
            
            /// <summary>
            /// Gets the killer of this actor.
            /// </summary>
            property Actor^ KilledBy
            {
                Actor^ get();
            }
            
            /// <summary>
            /// Gets the level of actor.
            /// </summary>
            property System::Int32 Level
            {
                System::Int32 get();
            }
            
            /// <summary>
            /// Gets the base form of actor. If this is a leveled actor it will return the base leveled form generated during gameplay as
            /// GetLeveledActorBase papyrus command would. If you want the base-base form of a leveled actor get BaseForm instead and cast it to TESNPC
            /// type.
            /// </summary>
            property TESNPC^ BaseActor
            {
                TESNPC^ get();
            }
            
            /// <summary>
            /// Gets the actor's current light level.
            /// </summary>
            property System::Single LightLevel
            {
                System::Single get();
            }
            
            /// <summary>
            /// Gets the lowest relationship rank this actor has.
            /// </summary>
            property RelationshipRanks LowestRelationshipRank
            {
                RelationshipRanks get();
            }
            
            /// <summary>
            /// Gets or sets whether this actor can recover from a bleedout or not.
            /// </summary>
            property bool NoBleedoutRecovery
            {
                bool get();
                void set(bool value);
            }
            
            /// <summary>
            /// Gets or sets whether this actor receives player control input.
            /// </summary>
            property bool ReceivesPlayerControls
            {
                bool get();
                void set(bool value);
            }
            
            /// <summary>
            /// Gets the relationship rank between this actor and another.
            /// </summary>
            /// <param name="other">The other actor.</param>
            RelationshipRanks GetRelationshipRank(Actor^ other);
            
            /// <summary>
            /// Gets the sitting state of actor.
            /// </summary>
            property ActorActionStates SitState
            {
                ActorActionStates get();
            }
            
            /// <summary>
            /// Gets the sleep state of actor.
            /// </summary>
            property ActorActionStates SleepState
            {
                ActorActionStates get();
            }
            
            /// <summary>
            /// Gets the time until actor can shout again (in seconds).
            /// </summary>
            property System::Single VoiceRecoveryTime
            {
                System::Single get();
                void set(System::Single value);
            }
            
            /// <summary>
            /// Gets the total warmth rating of actor.
            /// </summary>
            property System::Single WarmthRating
            {
                System::Single get();
            }
            
            /// <summary>
            /// Check if this actor has association with another. If the other actor is null check if actor has association of the specified type with
            /// anyone.
            /// </summary>
            /// <param name="type">The association type.</param>
            /// <param name="other">The other actor. If this is null check whether actor has the specified association with anyone.</param>
            bool HasAssociation(BGSAssociationType^ type, Actor^ other);
            
            /// <summary>
            /// Check if this actor has family relationship with another actor. If the other actor is null then check if has family relationship with
            /// anyone.
            /// </summary>
            /// <param name="other">The other actor. If this is null then check for family relationship with anyone.</param>
            bool HasFamilyRelationship(Actor^ other);
            
            /// <summary>
            /// Check if this actor has line of sight with an object. Only player can check line of sight with a non-actor!
            /// </summary>
            /// <param name="other">The other object.</param>
            bool HasLOS_Papyrus(TESObjectREFR^ other);
            
            /// <summary>
            /// Check if this actor has parent relationship with another.
            /// </summary>
            /// <param name="other">The other actor.</param>
            bool HasParentRelationship(Actor^ other);
            
            /// <summary>
            /// Check if this actor is alarmed right now.
            /// </summary>
            property bool IsAlarmed
            {
                bool get();
            }
            
            /// <summary>
            /// Get or set if actor is allowed to fly.
            /// </summary>
            property bool IsAllowedToFly
            {
                bool get();
                void set(bool value);
            }
            
            /// <summary>
            /// Check if this actor is arrested right now.
            /// </summary>
            property bool IsArrested
            {
                bool get();
            }
            
            /// <summary>
            /// Check if this actor is in bleedout state.
            /// </summary>
            property bool IsBleedingOut
            {
                bool get();
            }
            
            /// <summary>
            /// Check if actor is dead.
            /// </summary>
            property bool IsDead
            {
                bool get();
            }
            
            /// <summary>
            /// Check if this actor can detect another.
            /// </summary>
            /// <param name="target">The target actor.</param>
            bool CanDetect(Actor^ target);
            
            /// <summary>
            /// Check if an item is equipped.
            /// </summary>
            /// <param name="form">The object to check. This may be a list as well.</param>
            bool IsEquipped(TESForm^ form);
            
            /// <summary>
            /// Check if this is player's last ridden horse.
            /// </summary>
            property bool IsPlayersLastRiddenHorse
            {
                bool get();
            }
            
            /// <summary>
            /// Check if this actor is arresting their target.
            /// </summary>
            property bool IsArrestingTarget
            {
                bool get();
            }
            
            /// <summary>
            /// Gets or sets if this actor is alerted.
            /// </summary>
            property bool IsAlerted
            {
                bool get();
                void set(bool value);
            }
            
            /// <summary>
            /// Check if actor has the specified perk.
            /// </summary>
            /// <param name="perk">The perk to check for.</param>
            bool HasPerk(BGSPerk^ perk);
            
            /// <summary>
            /// Check if actor has a spell or shout.
            /// </summary>
            /// <param name="spellOrShout">The spell or shout form.</param>
            bool HasSpell(TESForm^ spellOrShout);
            
            /// <summary>
            /// Gets or sets if actor is bribed by player.
            /// </summary>
            property bool IsBribed
            {
                bool get();
                void set(bool value);
            }
            
            /// <summary>
            /// Check if actor has a child race.
            /// </summary>
            property bool IsChild
            {
                bool get();
            }
            
            /// <summary>
            /// Check if actor is commanded.
            /// </summary>
            property bool IsCommandedActor
            {
                bool get();
            }
            
            /// <summary>
            /// Gets or sets if actor is doing favor for player now.
            /// </summary>
            property bool IsDoingFavor
            {
                bool get();
                void set(bool value);
            }
            
            /// <summary>
            /// Check if actor is marked as essential.
            /// </summary>
            property bool IsEssential
            {
                bool get();
            }
            
            /// <summary>
            /// Check if actor is flying.
            /// </summary>
            property bool IsFlying
            {
                bool get();
            }
            
            /// <summary>
            /// Gets or sets if actor is a ghost. Ethereal form does this.
            /// </summary>
            property bool IsGhost
            {
                bool get();
                void set(bool value);
            }
            
            /// <summary>
            /// Check if actor is a guard.
            /// </summary>
            property bool IsGuard
            {
                bool get();
            }
            
            /// <summary>
            /// Check if this actor is hostile to another actor.
            /// </summary>
            /// <param name="target">The target actor to check hostility towards.</param>
            bool IsHostileToActor(Actor^ target);
            
            /// <summary>
            /// Check if this actor is in combat now.
            /// </summary>
            property bool IsInCombat
            {
                bool get();
            }
            
            /// <summary>
            /// Check if this actor is in faction.
            /// </summary>
            /// <param name="faction">The specified faction.</param>
            bool IsInFaction(TESFaction^ faction);
            
            /// <summary>
            /// Check if actor is in killmove now.
            /// </summary>
            property bool IsInKillmove
            {
                bool get();
            }
            
            /// <summary>
            /// Gets or sets if actor is in intimidated.
            /// </summary>
            property bool IsIntimidated
            {
                bool get();
                void set(bool value);
            }
            
            /// <summary>
            /// Check if actor is on mount.
            /// </summary>
            property bool IsOnMount
            {
                bool get();
            }
            
            /// <summary>
            /// Check if actor is over encumbered.
            /// </summary>
            property bool IsOverEncumbered
            {
                bool get();
            }
            
            /// <summary>
            /// Check if actor is marked as player's teammate.
            /// </summary>
            property bool IsPlayerTeammate
            {
                bool get();
            }
            
            /// <summary>
            /// Check if actor is running.
            /// </summary>
            property bool IsRunning
            {
                bool get();
            }
            
            /// <summary>
            /// Gets or sets if actor is sneaking.
            /// </summary>
            property bool IsSneaking
            {
                bool get();
                void set(bool value);
            }
            
            /// <summary>
            /// Check if actor is sprinting.
            /// </summary>
            property bool IsSprinting
            {
                bool get();
            }
            
            /// <summary>
            /// Check if actor is trespassing.
            /// </summary>
            property bool IsTrespassing
            {
                bool get();
            }
            
            /// <summary>
            /// Gets or sets if actor is unconscious.
            /// </summary>
            property bool IsUnconscious
            {
                bool get();
                void set(bool value);
            }
            
            /// <summary>
            /// Check if actor has weapon out.
            /// </summary>
            property bool IsWeaponDrawn
            {
                bool get();
            }
            
            /// <summary>
            /// Kills this actor.
            /// </summary>
            /// <param name="killer">The actor who is marked as killer.</param>
            /// <param name="noEvents">If true then don't raise any kill events.</param>
            /// <param name="force">If true then kill even if actor is essential or otherwise unkillable.</param>
            void Kill(Actor^ killer, bool noEvents, bool force);
            
            /// <summary>
            /// Check if this actor is the player character.
            /// </summary>
            property bool IsPlayer
            {
                bool get();
            }
            
            /// <summary>
            /// Removes the actor from specified faction.
            /// </summary>
            /// <param name="faction">The faction to remove from.</param>
            void RemoveFromFaction(TESFaction^ faction);
            
            /// <summary>
            /// Removes actor from all the factions.
            /// </summary>
            void RemoveFromAllFactions();
            
            /// <summary>
            /// Removes a perk from actor.
            /// </summary>
            /// <param name="perk">The perk to remove.</param>
            void RemovePerk(BGSPerk^ perk);
            
            /// <summary>
            /// Removes a shout from this actor.
            /// </summary>
            /// <param name="shout">The shout to remove.</param>
            bool RemoveShout(TESShout^ shout);
            
            /// <summary>
            /// Removes a spell from actor. Always returns true.
            /// </summary>
            /// <param name="spell">The spell to remove.</param>
            bool RemoveSpell(SpellItem^ spell);
            
            /// <summary>
            /// Resets the health and limbs of actor.
            /// </summary>
            void ResetHealthAndLimbs();
            
            /// <summary>
            /// Resurrect this actor.
            /// </summary>
            void Resurrect();
            
            /// <summary>
            /// Sends the alarm as if an actor was just assaulted by another.
            /// </summary>
            /// <param name="assaulter">The actor who assaulted this actor.</param>
            void SendAssaultAlarm(Actor^ assaulter);
            
            /// <summary>
            /// Have this actor believe they caught someone trespassing.
            /// </summary>
            /// <param name="criminal">The actor who was caught trespassing (bad guy).</param>
            void SendTrespassAlarm(Actor^ criminal);
            
            /// <summary>
            /// Sets if actor is allowed to fly.
            /// </summary>
            /// <param name="allowFly">Allowed to fly?</param>
            /// <param name="allowCrash">Allow crash?</param>
            /// <param name="allowSearch">Allow search?</param>
            void SetAllowFlyingEx(bool allowFly, bool allowCrash, bool allowSearch);
            
            /// <summary>
            /// Sets the alpha value of actor (transparency).
            /// </summary>
            /// <param name="alpha">The alpha value. Valid is between 0 and 1 where 0 is completely transparent and 1 is solid.</param>
            /// <param name="fade">Fade to the value instead of immediately popping?</param>
            void SetAlpha(System::Single alpha, bool fade);
            
            /// <summary>
            /// Should this actor be attacked by all other actors when its detected?
            /// </summary>
            /// <param name="should">Should or not.</param>
            void SetAttackedByAllOnSight(bool should);
            
            /// <summary>
            /// Sets the critical stage for actor and handles the associated effects.
            /// </summary>
            /// <param name="stage">The stage.</param>
            void SetCriticalStage(ActorCriticalStages stage);
            
            /// <summary>
            /// Sets actor not to move.
            /// </summary>
            /// <param name="dontMove">Allow move or not?</param>
            void SetDontMove(bool dontMove);
            
            /// <summary>
            /// Sets the expression override on actor.
            /// </summary>
            /// <param name="expression">The expression ID.</param>
            /// <param name="amount">The amount. This is from 0 to 1.</param>
            bool SetExpressionOverride(System::Int32 expression, System::Single amount);
            
            /// <summary>
            /// Gets or sets whether the head tracking mode is enabled for this actor.
            /// </summary>
            property bool IsHeadTrackingEnabled
            {
                bool get();
                void set(bool value);
            }
            
            /// <summary>
            /// Sets this actor's head tracking target object.
            /// </summary>
            /// <param name="target">The object to look at.</param>
            /// <param name="whilePathing">Also continue looking at object while pathing?</param>
            void SetLookAtObject(TESObjectREFR^ target, bool whilePathing);
            
            /// <summary>
            /// Gets or sets whether this actor's detection state of player will affect the stealth meter.
            /// </summary>
            property bool ShowOnStealthMeter
            {
                bool get();
                void set(bool value);
            }
            
            /// <summary>
            /// Sets the outfit of this actor.
            /// </summary>
            /// <param name="outfit">The outfit to set.</param>
            /// <param name="sleepOutfit">Set sleep outfit or normal?</param>
            void SetOutfit(BGSOutfit^ outfit, bool sleepOutfit);
            
            /// <summary>
            /// Sets the player as resisting arrest from this actor's faction.
            /// </summary>
            void SetPlayerResistingArrest();
            
            /// <summary>
            /// Sets this actor as being player teammate or not.
            /// </summary>
            /// <param name="teammate">Is teammate?</param>
            /// <param name="canDoFavors">Can this actor do favors?</param>
            void SetPlayerTeammate(bool teammate, bool canDoFavors);
            
            /// <summary>
            /// Sets the relationship rank of this actor with another.
            /// </summary>
            /// <param name="other">The other actor.</param>
            /// <param name="rank">The rank.</param>
            void SetRelationshipRank(Actor^ other, RelationshipRanks rank);
            
            /// <summary>
            /// Sets if actor is restrained.
            /// </summary>
            /// <param name="restrained">Is restrained?</param>
            void SetRestrained(bool restrained);
            
            /// <summary>
            /// Sets the vehicle of actor.
            /// </summary>
            /// <param name="vehicle">The vehicle to set. If null then clear vehicle.</param>
            void SetVehicle(TESObjectREFR^ vehicle);
            
            /// <summary>
            /// Show barter menu for this actor.
            /// </summary>
            void ShowBarterMenu();
            
            /// <summary>
            /// Tries to start combat with target. Returns false if failed.
            /// </summary>
            /// <param name="target">The target.</param>
            bool StartCombat(Actor^ target);
            
            /// <summary>
            /// Go into deferred kill state.
            /// </summary>
            void StartDeferredKill();
            
            /// <summary>
            /// Stops the combat alarm from this actor.
            /// </summary>
            void StopCombatAlarm();
            
            /// <summary>
            /// Stops combat on this actor.
            /// </summary>
            void StopCombat();
            
            /// <summary>
            /// Attempts to trap the soul of target and returns if successful.
            /// </summary>
            /// <param name="target">The target actor whose soul to trap.</param>
            bool TrapSoul(Actor^ target);
            
            /// <summary>
            /// Unlock owned doors in cell of actor. Only works in interior.
            /// </summary>
            void UnlockOwnedDoorsInCell();
            
            /// <summary>
            /// Unequip all items.
            /// </summary>
            void UnequipAll();
            
            /// <summary>
            /// Removes all equipment from an item slot.
            /// </summary>
            /// <param name="slot">The slot to unequip.</param>
            void UnequipItemSlot(EquipSlots slot);
            
            /// <summary>
            /// Unequip an item from actor.
            /// </summary>
            /// <param name="form">The item to unequip.</param>
            /// <param name="preventEquip">Prevent equipping it again?</param>
            /// <param name="silent">Is it silent unequip?</param>
            void UnequipItem(TESForm^ form, bool preventEquip, bool silent);
            
            /// <summary>
            /// Unequips the specified shout.
            /// </summary>
            /// <param name="shout">The shout to unequip.</param>
            void UnequipShout(TESShout^ shout);
            
            /// <summary>
            /// Unequips the spell from actor.
            /// </summary>
            /// <param name="spell">The spell to unequip.</param>
            /// <param name="slot">The slot to unequip from.</param>
            void UnequipSpell(SpellItem^ spell, EquippedSpellSlots slot);
            
            /// <summary>
            /// Equip a spell on actor.
            /// </summary>
            /// <param name="spell">The spell to equip.</param>
            /// <param name="slot">The slot to equip in.</param>
            void EquipSpell(SpellItem^ spell, EquippedSpellSlots slot);
            
            /// <summary>
            /// Check if intimidate would succeed on actor.
            /// </summary>
            property bool WillIntimidateSucceed
            {
                bool get();
            }
            
            /// <summary>
            /// Check if a worn item has the specified keyword.
            /// </summary>
            /// <param name="keyword">The keyword to check for.</param>
            bool WornHasKeyword(BGSKeyword^ keyword);
            
            /// <summary>
            /// Check if a worn item has the specified keyword.
            /// </summary>
            /// <param name="keyword">The keyword to check for.</param>
            bool WornHasKeywordText(System::String^ keyword);
            
            /// <summary>
            /// Clears the actor from looking at a specific position.
            /// </summary>
            void ClearLookAtPosition();
            
            /// <summary>
            /// Makes actor look at a specific position. This has to be called every time after the actor has already updated their headtracking targets or
            /// it will be overwritten always.
            /// </summary>
            /// <param name="position">The position to look at.</param>
            void SetLookAtPosition(NiPoint3^ position);
            
            /// <summary>
            /// Interrupt all casting of this actor.
            /// </summary>
            void InterruptCast();
            
            /// <summary>
            /// Check if this actor is being ridden (horse).
            /// </summary>
            property bool IsBeingRidden
            {
                bool get();
            }
            
            /// <summary>
            /// Check if this actor is on a flying mount.
            /// </summary>
            property bool IsOnFlyingMount
            {
                bool get();
            }
            
            /// <summary>
            /// Gets the current movement state of actor.
            /// </summary>
            property bhkCharacterStateTypes MovementState
            {
                bhkCharacterStateTypes get();
            }
            
            /// <summary>
            /// Gets a value indicating if this actor is currently in the jump state. You may also want to check IsFalling because after the jump state the
            /// actor will be in the falling state even though it's part of the jump.
            /// </summary>
            property bool IsJumping
            {
                bool get();
            }
            
            /// <summary>
            /// Gets a value indicating whether this actor is currently falling.
            /// </summary>
            property bool IsFalling
            {
                bool get();
            }
            
            /// <summary>
            /// Gets the current mount if actor is mounted.
            /// </summary>
            Actor^ GetMount();
            
            /// <summary>
            /// Gets the actor who is currently mounting this actor.
            /// </summary>
            Actor^ GetMountedBy();
        };
        
        public interface class TESObjectCELL : public TESForm, public TESFullName
        {
            /// <summary>
            /// Gets the extra data of this cell.
            /// </summary>
            property BSExtraDataList^ ExtraDataList
            {
                BSExtraDataList^ get();
            }
            
            /// <summary>
            /// Gets the world space of this cell.
            /// </summary>
            property TESWorldSpace^ WorldSpace
            {
                TESWorldSpace^ get();
            }
            
            /// <summary>
            /// The locker for reference table. Use Mutex #1 method to access.
            /// </summary>
            property Mutex^ ReferenceLocker
            {
                Mutex^ get();
            }
            
            /// <summary>
            /// Gets the references in this cell.
            /// </summary>
            property BSTDefaultScatterTable<System::UInt32, TESObjectREFR^>^ References
            {
                BSTDefaultScatterTable<System::UInt32, TESObjectREFR^>^ get();
            }
            
            /// <summary>
            /// Check if this cell is marked as interior or exterior.
            /// </summary>
            property bool IsInterior
            {
                bool get();
            }
            
            /// <summary>
            /// Perform ray casting in this or nearby cell.
            /// </summary>
            System::Collections::Generic::List<RayCastResult^>^ RayCast(RayCastParameters^ p);
            
            /// <summary>
            /// Gets the owner form of cell. This could be actor or faction.
            /// </summary>
            property TESForm^ OwnerForm
            {
                TESForm^ get();
            }
            
            /// <summary>
            /// Gets a value indicating whether this cell is attached.
            /// </summary>
            property bool IsAttached
            {
                bool get();
            }
            
            /// <summary>
            /// Gets the X coordinate of cell in it's worldspace grid. This will return zero for interior cells.
            /// </summary>
            property System::Int32 CoordinateX
            {
                System::Int32 get();
            }
            
            /// <summary>
            /// Gets the Y coordinate of cell in it's worldspace grid. This will return zero for interior cells.
            /// </summary>
            property System::Int32 CoordinateY
            {
                System::Int32 get();
            }
        };
        
        public interface class Character : public Actor
        {
        };
        
        /// <summary>
        /// The player character.
        /// </summary>
        public interface class PlayerCharacter : public Character, public BSTEventSink<MenuOpenCloseEvent^>, public BSTEventSink<MenuModeChangeEvent^>, public BSTEventSink<UserEventEnabledEvent^>, public BSTEventSink<TESTrackedStatsEvent^>
        {
            /// <summary>
            /// Gets the player character instance.
            /// </summary>
            static property PlayerCharacter^ Instance
            {
                PlayerCharacter^ get()
                {
                    return MemoryObject::FromAddress<PlayerCharacter^>(Memory::ReadPointer(MCH::FromBase(0x142F4DEF8), false));
                }
            }
        };
        
        /// <summary>
        /// Weapon item.
        /// </summary>
        public interface class TESObjectWEAP : public TESBoundObject, public TESFullName, public TESModelTextureSwap, public TESIcon, public TESEnchantableForm, public TESValueForm, public TESWeightForm, public TESAttackDamageForm, public BGSDestructibleObjectForm, public BGSEquipType, public BGSPreloadable, public BGSMessageIcon, public BGSPickupPutdownSounds, public BGSBlockBashData, public BGSKeywordForm, public TESDescription
        {
            /// <summary>
            /// Fires this weapon (bow, crossbow).
            /// </summary>
            /// <param name="source">The source where weapon is fired from.</param>
            /// <param name="ammo">Overwrite ammo? If this is not set and source is actor then get source's ammo instead.</param>
            /// <param name="enchant">The enchantment on the weapon to use when firing.</param>
            /// <param name="poison">The poison on the weapon to use when firing.</param>
            void Fire(TESObjectREFR^ source, TESAmmo^ ammo, MagicItem^ enchant, MagicItem^ poison);
        };
        interface class NiCollisionObject;
        
        public interface class NiAVObject : public NiObjectNET
        {
            /// <summary>
            /// Gets the parent node of this object.
            /// </summary>
            property NiNode^ Parent
            {
                NiNode^ get();
            }
            
            /// <summary>
            /// Gets the index of this object in parent node child array. This is negative if not added to a parent.
            /// </summary>
            property System::Int32 Index
            {
                System::Int32 get();
            }
            
            /// <summary>
            /// Local self only transform.
            /// </summary>
            property NiTransform^ LocalTransform
            {
                NiTransform^ get();
            }
            
            /// <summary>
            /// World cumulative transform.
            /// </summary>
            property NiTransform^ WorldTransform
            {
                NiTransform^ get();
            }
            
            /// <summary>
            /// This is a world transform that gets updated once per frame only.
            /// </summary>
            property NiTransform^ FrameTransform
            {
                NiTransform^ get();
            }
            
            /// <summary>
            /// Gets the collision object.
            /// </summary>
            property NiCollisionObject^ Collidable
            {
                NiCollisionObject^ get();
            }
            
            /// <summary>
            /// Gets the owner object. This is set if this is the primary root node for a game object (form).
            /// </summary>
            property TESObjectREFR^ OwnerObject
            {
                TESObjectREFR^ get();
            }
            
            /// <summary>
            /// Update this node. This should be called if you change the local transform of object and don't expect for it to be updated automatically or
            /// it's a havok object and don't want havok to overwrite the position back.
            /// </summary>
            /// <param name="time">The time to set in time controllers. Set negative or zero to not update time controllers.</param>
            void Update(System::Single time);
            
            /// <summary>
            /// Detach the object from parent node. This object will be deleted unless you manually IncRef before calling this function or it's still used
            /// somewhere else!
            /// </summary>
            void Detach();
            
            /// <summary>
            /// Update this node. This should be called if you change the local transform of object and don't expect for it to be updated automatically or
            /// it's a havok object and don't want havok to overwrite the position back.
            /// </summary>
            /// <param name="time">The time to set in time controllers. Set negative or zero to not update time controllers.</param>
            /// <param name="flags">The custom flags to use for update.</param>
            void UpdateEx(System::Single time, System::UInt32 flags);
        };
        
        public interface class NiNode : public NiAVObject
        {
            /// <summary>
            /// Gets the child nodes.
            /// </summary>
            property NiTObjectArray<NiAVObject^>^ Children
            {
                NiTObjectArray<NiAVObject^>^ get();
            }
            
            /// <summary>
            /// Looks up the child node by it's name.
            /// </summary>
            /// <param name="name">The name of node. This is not case sensitive.</param>
            NiNode^ LookupNodeByName(System::String^ name);
            
            /// <summary>
            /// Attaches an object to this node.
            /// </summary>
            /// <param name="obj">The object to attach.</param>
            void AttachObject(NiAVObject^ obj);
        };
        
        public interface class NiCollisionObject : public NiObject
        {
            /// <summary>
            /// Gets the owner object or node.
            /// </summary>
            property NiAVObject^ OwnerObject
            {
                NiAVObject^ get();
            }
        };
        
        /// <summary>
        /// Havok collidable wrapper.
        /// </summary>
        public interface class bhkNiCollisionObject : public NiCollisionObject
        {
            /// <summary>
            /// Gets the havok world object wrapper.
            /// </summary>
            property bhkWorldObject^ WorldObject
            {
                bhkWorldObject^ get();
            }
        };
        
        public interface class NiLight : public NiAVObject
        {
            /// <summary>
            /// Gets the color of light. R/G/B as float ranging from 0 to 1.
            /// </summary>
            property NiPoint3^ Color
            {
                NiPoint3^ get();
            }
            
            /// <summary>
            /// Gets the radius of light.
            /// </summary>
            property NiPoint3^ Radius
            {
                NiPoint3^ get();
            }
        };
        
        public interface class BSGeometry : public NiAVObject
        {
            /// <summary>
            /// Gets the skin instance.
            /// </summary>
            property NiSkinInstance^ Skin
            {
                NiSkinInstance^ get();
            }
        };
        interface class TESCamera;
        
        /// <summary>
        /// Camera state handler.
        /// </summary>
        public interface class TESCameraState : public BSIntrusiveRefCounted
        {
            /// <summary>
            /// Gets the parent camera of state.
            /// </summary>
            property TESCamera^ Camera
            {
                TESCamera^ get();
            }
            
            /// <summary>
            /// Gets the identifier of this state.
            /// </summary>
            property TESCameraStates Id
            {
                TESCameraStates get();
            }
            
            /// <summary>
            /// Gets the current position of this camera state.
            /// </summary>
            /// <param name="result">The result will be set in this point.</param>
            void GetCurrentPosition(NiPoint3^ result);
        };
        
        /// <summary>
        /// Base camera implementation.
        /// </summary>
        public interface class TESCamera : public IVirtualObject
        {
            /// <summary>
            /// Gets the node of camera. Example "WorldRoot CameraNode".
            /// </summary>
            property NiNode^ Node
            {
                NiNode^ get();
            }
            
            /// <summary>
            /// Gets the current state of camera.
            /// </summary>
            property TESCameraState^ State
            {
                TESCameraState^ get();
            }
        };
        
        /// <summary>
        /// First person camera state.
        /// </summary>
        public interface class FirstPersonState : public TESCameraState, public PlayerInputHandler
        {
            /// <summary>
            /// Gets the control node. This is the "Camera Control" node name from skeleton?
            /// </summary>
            property NiNode^ ControlNode
            {
                NiNode^ get();
            }
            
            /// <summary>
            /// Gets the attached node. Example "Camera1st [Cam1]".
            /// </summary>
            property NiNode^ AttachedNode
            {
                NiNode^ get();
            }
            
            /// <summary>
            /// Gets the player character's current position. This is not the camera position!
            /// </summary>
            property NiPoint3^ PlayerPosition
            {
                NiPoint3^ get();
            }
        };
        
        /// <summary>
        /// Third person camera state.
        /// </summary>
        public interface class ThirdPersonState : public TESCameraState, public PlayerInputHandler
        {
            /// <summary>
            /// Gets the position. This is the actual camera position and not player position!
            /// </summary>
            property NiPoint3^ Position
            {
                NiPoint3^ get();
            }
            
            /// <summary>
            /// Gets the over shoulder offsets.
            /// </summary>
            property NiPoint3^ OverShoulderOffset
            {
                NiPoint3^ get();
            }
            
            /// <summary>
            /// Gets the attached node. For example "Camera3rd [Cam3]".
            /// </summary>
            property NiNode^ Node
            {
                NiNode^ get();
            }
            
            /// <summary>
            /// Gets the target node.
            /// </summary>
            property NiPointer<NiNode^>^ TargetNode
            {
                NiPointer<NiNode^>^ get();
            }
            
            /// <summary>
            /// Gets the target node name.
            /// </summary>
            property BSFixedString^ TargetNodeName
            {
                BSFixedString^ get();
            }
            
            /// <summary>
            /// Gets the control node. For example "Camera Control".
            /// </summary>
            property NiNode^ ControlNode
            {
                NiNode^ get();
            }
            
            /// <summary>
            /// Gets or sets the X rotation from last reset point. This is in radians. This is the one where if you move mouse left or right.
            /// </summary>
            property System::Single XRotationFromLastResetPoint
            {
                System::Single get();
                void set(System::Single value);
            }
            
            /// <summary>
            /// Gets or sets the Y rotation from last reset point. This is in radians. This is the one where if you move mouse down or up.
            /// </summary>
            property System::Single YRotationFromLastResetPoint
            {
                System::Single get();
                void set(System::Single value);
            }
            
            /// <summary>
            /// Gets or sets the target zoom level that we are zooming to.
            /// </summary>
            property System::Single TargetZoomLevel
            {
                System::Single get();
                void set(System::Single value);
            }
            
            /// <summary>
            /// Gets or sets the current zoom level that we have zoomed to.
            /// </summary>
            property System::Single CurrentZoomLevel
            {
                System::Single get();
                void set(System::Single value);
            }
            
            /// <summary>
            /// Gets the last camera collision point. This is only set if the camera collides with something in its path.
            /// </summary>
            property NiPoint3^ LastCollisionPoint
            {
                NiPoint3^ get();
            }
            
            /// <summary>
            /// Check if forced free look mode is set. This is true if the player character should not be snapped to camera direction even if they are
            /// moving.
            /// </summary>
            property bool IsFreeLookMode
            {
                bool get();
            }
        };
        
        public interface class AutoVanityState : public TESCameraState
        {
        };
        
        public interface class VATSCameraState : public TESCameraState
        {
        };
        
        public interface class FreeCameraState : public TESCameraState, public PlayerInputHandler
        {
        };
        
        public interface class IronSightsState : public TESCameraState
        {
        };
        
        /// <summary>
        /// This camera state is used as we are currently in the process of sitting down or standing up. It is not used while sitting.
        /// </summary>
        public interface class FurnitureCameraState : public TESCameraState
        {
        };
        
        /// <summary>
        /// State for transitioning between ThirdPerson1 and ThirdPerson2. Used for things like entering forge or tanning rack.
        /// </summary>
        public interface class PlayerCameraTransitionState : public TESCameraState
        {
            /// <summary>
            /// Gets the state to transition from.
            /// </summary>
            property TESCameraState^ TransitionFrom
            {
                TESCameraState^ get();
            }
            
            /// <summary>
            /// Gets the state to transition to.
            /// </summary>
            property TESCameraState^ TransitionTo
            {
                TESCameraState^ get();
            }
        };
        
        public interface class TweenMenuCameraState : public TESCameraState
        {
            /// <summary>
            /// Gets or sets the target X turn. This is the sideways turn where + is right and - is left.
            /// </summary>
            property System::Single TargetXTurn
            {
                System::Single get();
                void set(System::Single value);
            }
            
            /// <summary>
            /// Gets or sets the target Y turn. This is the vertical turn where + is down and - is up.
            /// </summary>
            property System::Single TargetYTurn
            {
                System::Single get();
                void set(System::Single value);
            }
            
            /// <summary>
            /// Gets or sets the current Y turn.
            /// </summary>
            property System::Single CurrentYTurn
            {
                System::Single get();
                void set(System::Single value);
            }
            
            /// <summary>
            /// Gets or sets the current X turn.
            /// </summary>
            property System::Single CurrentXTurn
            {
                System::Single get();
                void set(System::Single value);
            }
        };
        
        /// <summary>
        /// This state is used while mounted, while mounting and while dismounting.
        /// </summary>
        public interface class HorseCameraState : public ThirdPersonState
        {
            /// <summary>
            /// Gets the reference handle of the horse the player is currently riding.
            /// </summary>
            property System::UInt32 HorseRefHandle
            {
                System::UInt32 get();
            }
            
            /// <summary>
            /// This is the direction where horse is currently facing in radians. This is not the direction of the camera or where player wants to go but
            /// actual horse direction.
            /// </summary>
            property System::Single HorseCurrentDirection
            {
                System::Single get();
            }
        };
        
        public interface class BleedoutCameraState : public ThirdPersonState
        {
        };
        
        public interface class DragonCameraState : public ThirdPersonState
        {
        };
        
        /// <summary>
        /// Player game camera.
        /// </summary>
        public interface class PlayerCamera : public TESCamera
        {
            /// <summary>
            /// Gets state instance.
            /// </summary>
            property FirstPersonState^ CameraFirstPersonState
            {
                FirstPersonState^ get();
            }
            
            /// <summary>
            /// Gets state instance.
            /// </summary>
            property AutoVanityState^ CameraAutoVanityState
            {
                AutoVanityState^ get();
            }
            
            /// <summary>
            /// Gets state instance.
            /// </summary>
            property VATSCameraState^ CameraVATSCameraState
            {
                VATSCameraState^ get();
            }
            
            /// <summary>
            /// Gets state instance.
            /// </summary>
            property FreeCameraState^ CameraFreeCameraState
            {
                FreeCameraState^ get();
            }
            
            /// <summary>
            /// Gets state instance.
            /// </summary>
            property IronSightsState^ CameraIronSightsState
            {
                IronSightsState^ get();
            }
            
            /// <summary>
            /// Gets state instance.
            /// </summary>
            property FurnitureCameraState^ CameraFurnitureCameraState
            {
                FurnitureCameraState^ get();
            }
            
            /// <summary>
            /// Gets state instance.
            /// </summary>
            property PlayerCameraTransitionState^ CameraPlayerCameraTransitionState
            {
                PlayerCameraTransitionState^ get();
            }
            
            /// <summary>
            /// Gets state instance.
            /// </summary>
            property TweenMenuCameraState^ CameraTweenMenuCameraState
            {
                TweenMenuCameraState^ get();
            }
            
            /// <summary>
            /// Gets state instance.
            /// </summary>
            property ThirdPersonState^ CameraThirdPersonState1
            {
                ThirdPersonState^ get();
            }
            
            /// <summary>
            /// Gets state instance.
            /// </summary>
            property ThirdPersonState^ CameraThirdPersonState2
            {
                ThirdPersonState^ get();
            }
            
            /// <summary>
            /// Gets state instance.
            /// </summary>
            property HorseCameraState^ CameraHorseCameraState
            {
                HorseCameraState^ get();
            }
            
            /// <summary>
            /// Gets state instance.
            /// </summary>
            property BleedoutCameraState^ CameraBleedoutCameraState
            {
                BleedoutCameraState^ get();
            }
            
            /// <summary>
            /// Gets state instance.
            /// </summary>
            property DragonCameraState^ CameraDragonCameraState
            {
                DragonCameraState^ get();
            }
            
            /// <summary>
            /// Gets or sets whether to enable the auto vanity mode.
            /// </summary>
            property System::Byte EnableVanityMode
            {
                System::Byte get();
                void set(System::Byte value);
            }
            
            /// <summary>
            /// Gets the collision object.
            /// </summary>
            property NiCollisionObject^ Collidable
            {
                NiCollisionObject^ get();
            }
            
            /// <summary>
            /// Gets the last node position.
            /// </summary>
            property NiPoint3^ LastNodePosition
            {
                NiPoint3^ get();
            }
            
            /// <summary>
            /// Gets the seconds since last input.
            /// </summary>
            property System::Single TimeSinceLastInput
            {
                System::Single get();
            }
            
            /// <summary>
            /// Gets the camera target ref handle id.
            /// </summary>
            property System::UInt32 TargetRefHandle
            {
                System::UInt32 get();
            }
            
            /// <summary>
            /// Gets the player camera instance.
            /// </summary>
            static property PlayerCamera^ Instance
            {
                    PlayerCamera^ get()
                    {
                        return MemoryObject::FromAddress<PlayerCamera^>(Memory::ReadPointer(MCH::FromBase(0x142EEC9B8), false));
                    }
            }
            
            /// <summary>
            /// Enter first person mode with camera.
            /// </summary>
            void EnterFirstPerson();
            
            /// <summary>
            /// Enter third person mode with camera.
            /// </summary>
            void EnterThirdPerson();
        };
        interface class BGSBaseAlias;
        
        public interface class TESQuest : public BGSStoryManagerTreeForm, public TESFullName
        {
            /// <summary>
            /// Gets the alias from this quest.
            /// </summary>
            /// <param name="id">The ID of the alias within this quest.</param>
            BGSBaseAlias^ GetAlias(System::Int32 id);
        };
        
        public interface class BGSBaseAlias : public IVirtualObject
        {
            /// <summary>
            /// Gets the parent quest where this alias is.
            /// </summary>
            property TESQuest^ OwningQuest
            {
                TESQuest^ get();
            }
        };
        
        /// <summary>
        /// Reference alias.
        /// </summary>
        public interface class BGSRefAlias : public BGSBaseAlias
        {
            /// <summary>
            /// Clears this alias from pointing to anything.
            /// </summary>
            void Clear();
            
            /// <summary>
            /// Gets or sets the reference that this alias points to.
            /// </summary>
            property TESObjectREFR^ Reference
            {
                TESObjectREFR^ get();
                void set(TESObjectREFR^ value);
            }
        };
    }
}

#pragma warning(pop)
