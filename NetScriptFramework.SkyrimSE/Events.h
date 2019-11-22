#pragma once
#pragma warning(push)
#pragma warning(disable : 4638)

namespace NetScriptFramework
{
    namespace Skyrim
    {
        /// <summary>
        /// Arguments for OnBarterMenu event.
        /// </summary>
        public ref class BarterMenuEventArgs : public HookedEventArgs
        {
            private: bool __v_Entering;
            /// <summary>
            /// Are we entering or exiting the menu?
            /// </summary>
            public: property bool Entering
            {
                public: bool __clrcall get() { return __v_Entering; }
                internal: void __clrcall set(bool value) { __v_Entering = value; }
            }
            
            private: System::UInt32 __v_RefHandle;
            /// <summary>
            /// The ref handle id of the actor the player is trading with.
            /// </summary>
            public: property System::UInt32 RefHandle
            {
                public: System::UInt32 __clrcall get() { return __v_RefHandle; }
                internal: void __clrcall set(System::UInt32 value) { __v_RefHandle = value; }
            }
        };
        
        /// <summary>
        /// Arguments for OnCalculateDetection event.
        /// </summary>
        public ref class CalculateDetectionEventArgs : public HookedEventArgs
        {
            private: Actor^ __v_SourceActor;
            /// <summary>
            /// The source actor who is doing the detecting.
            /// </summary>
            public: property Actor^ SourceActor
            {
                public: Actor^ __clrcall get() { return __v_SourceActor; }
                internal: void __clrcall set(Actor^ value) { __v_SourceActor = value; }
            }
            
            private: Actor^ __v_TargetActor;
            /// <summary>
            /// The target actor who may get detected by source.
            /// </summary>
            public: property Actor^ TargetActor
            {
                public: Actor^ __clrcall get() { return __v_TargetActor; }
                internal: void __clrcall set(Actor^ value) { __v_TargetActor = value; }
            }
            
            private: System::Int32 __v_ResultValue;
            /// <summary>
            /// The resulting detection value. Positive means detected. Set -1000 for definitely not detected at all.
            /// </summary>
            public: property System::Int32 ResultValue
            {
                public: System::Int32 __clrcall get() { return __v_ResultValue; }
                public: void __clrcall set(System::Int32 value) { __v_ResultValue = value; }
            }
            
            private: NiPoint3^ __v_Position;
            /// <summary>
            /// The position where the detection occurrs.
            /// </summary>
            public: property NiPoint3^ Position
            {
                public: NiPoint3^ __clrcall get() { return __v_Position; }
                internal: void __clrcall set(NiPoint3^ value) { __v_Position = value; }
            }
        };
        
        /// <summary>
        /// Arguments for OnCameraStateChanging event.
        /// </summary>
        public ref class CameraStateChangingEventArgs : public HookedEventArgs
        {
            private: TESCamera^ __v_Camera;
            /// <summary>
            /// The camera that is about to change state.
            /// </summary>
            public: property TESCamera^ Camera
            {
                public: TESCamera^ __clrcall get() { return __v_Camera; }
                internal: void __clrcall set(TESCamera^ value) { __v_Camera = value; }
            }
            
            private: TESCameraState^ __v_PreviousState;
            /// <summary>
            /// The previous (current) state of the camera.
            /// </summary>
            public: property TESCameraState^ PreviousState
            {
                public: TESCameraState^ __clrcall get() { return __v_PreviousState; }
                internal: void __clrcall set(TESCameraState^ value) { __v_PreviousState = value; }
            }
            
            private: TESCameraState^ __v_NextState;
            /// <summary>
            /// The next state that will be set on the camera.
            /// </summary>
            public: property TESCameraState^ NextState
            {
                public: TESCameraState^ __clrcall get() { return __v_NextState; }
                public: void __clrcall set(TESCameraState^ value) { __v_NextState = value; }
            }
            
            private: bool __v_Skip;
            /// <summary>
            /// Skip changing this state.
            /// </summary>
            public: property bool Skip
            {
                public: bool __clrcall get() { return __v_Skip; }
                public: void __clrcall set(bool value) { __v_Skip = value; }
            }
        };
        
        /// <summary>
        /// Arguments for OnFrame event.
        /// </summary>
        public ref class FrameEventArgs : public HookedEventArgs
        {
        };
        
        /// <summary>
        /// Arguments for OnInterruptCast event.
        /// </summary>
        public ref class InterruptCastEventArgs : public HookedEventArgs
        {
            private: MagicCaster^ __v_Caster;
            /// <summary>
            /// The magic caster.
            /// </summary>
            public: property MagicCaster^ Caster
            {
                public: MagicCaster^ __clrcall get() { return __v_Caster; }
                internal: void __clrcall set(MagicCaster^ value) { __v_Caster = value; }
            }
        };
        
        /// <summary>
        /// Arguments for OnMagicCasterFire event.
        /// </summary>
        public ref class MagicCasterFireEventArgs : public HookedEventArgs
        {
            private: MagicCaster^ __v_Caster;
            /// <summary>
            /// The magic caster.
            /// </summary>
            public: property MagicCaster^ Caster
            {
                public: MagicCaster^ __clrcall get() { return __v_Caster; }
                internal: void __clrcall set(MagicCaster^ value) { __v_Caster = value; }
            }
            
            private: MagicItem^ __v_Item;
            /// <summary>
            /// The magic that is being cast.
            /// </summary>
            public: property MagicItem^ Item
            {
                public: MagicItem^ __clrcall get() { return __v_Item; }
                internal: void __clrcall set(MagicItem^ value) { __v_Item = value; }
            }
        };
        
        /// <summary>
        /// Arguments for OnMainMenu event.
        /// </summary>
        public ref class MainMenuEventArgs : public HookedEventArgs
        {
            private: bool __v_Entering;
            /// <summary>
            /// Are we entering or exiting the main menu?
            /// </summary>
            public: property bool Entering
            {
                public: bool __clrcall get() { return __v_Entering; }
                internal: void __clrcall set(bool value) { __v_Entering = value; }
            }
        };
        
        /// <summary>
        /// Arguments for OnReduceHUDAmmoCounter event.
        /// </summary>
        public ref class ReduceHUDAmmoCounterEventArgs : public HookedEventArgs
        {
            private: System::Int32 __v_HasAmount;
            /// <summary>
            /// The current ammo left (before reducing).
            /// </summary>
            public: property System::Int32 HasAmount
            {
                public: System::Int32 __clrcall get() { return __v_HasAmount; }
                internal: void __clrcall set(System::Int32 value) { __v_HasAmount = value; }
            }
            
            private: ExtraContainerChanges::ItemEntry^ __v_Item;
            /// <summary>
            /// The item entry being spent.
            /// </summary>
            public: property ExtraContainerChanges::ItemEntry^ Item
            {
                public: ExtraContainerChanges::ItemEntry^ __clrcall get() { return __v_Item; }
                internal: void __clrcall set(ExtraContainerChanges::ItemEntry^ value) { __v_Item = value; }
            }
            
            private: System::Int32 __v_ReduceAmount;
            /// <summary>
            /// The amount of ammo to reduce.
            /// </summary>
            public: property System::Int32 ReduceAmount
            {
                public: System::Int32 __clrcall get() { return __v_ReduceAmount; }
                public: void __clrcall set(System::Int32 value) { __v_ReduceAmount = value; }
            }
        };
        
        /// <summary>
        /// Arguments for OnRemoveMagicEffectsWithArchetype event.
        /// </summary>
        public ref class RemoveMagicEffectsWithArchetypeEventArgs : public HookedEventArgs
        {
            private: Actor^ __v_Owner;
            /// <summary>
            /// The actor who will have the effects removed.
            /// </summary>
            public: property Actor^ Owner
            {
                public: Actor^ __clrcall get() { return __v_Owner; }
                internal: void __clrcall set(Actor^ value) { __v_Owner = value; }
            }
            
            private: MagicEffectRemovalReasons __v_Reason;
            /// <summary>
            /// The reason for removing.
            /// </summary>
            public: property MagicEffectRemovalReasons Reason
            {
                public: MagicEffectRemovalReasons __clrcall get() { return __v_Reason; }
                internal: void __clrcall set(MagicEffectRemovalReasons value) { __v_Reason = value; }
            }
            
            private: Archetypes __v_Archetype;
            /// <summary>
            /// The effect archetype that is being removed.
            /// </summary>
            public: property Archetypes Archetype
            {
                public: Archetypes __clrcall get() { return __v_Archetype; }
                internal: void __clrcall set(Archetypes value) { __v_Archetype = value; }
            }
            
            private: bool __v_Skip;
            /// <summary>
            /// Skip removing the effects?
            /// </summary>
            public: property bool Skip
            {
                public: bool __clrcall get() { return __v_Skip; }
                public: void __clrcall set(bool value) { __v_Skip = value; }
            }
        };
        
        /// <summary>
        /// Arguments for OnShadowCullingBegin event.
        /// </summary>
        public ref class ShadowCullingBeginEventArgs : public HookedEventArgs
        {
            private: bool __v_Separate;
            /// <summary>
            /// Should shadow culling be separated from regular culling? It will be slower but allows enabling or disabling objects separately in different cull phases.
            /// </summary>
            public: property bool Separate
            {
                public: bool __clrcall get() { return __v_Separate; }
                public: void __clrcall set(bool value) { __v_Separate = value; }
            }
            
            internal: static System::Int64 __state;
        };
        
        /// <summary>
        /// Arguments for OnShadowCullingEnd event.
        /// </summary>
        public ref class ShadowCullingEndEventArgs : public HookedEventArgs
        {
            private: bool __v_Separate;
            /// <summary>
            /// Were the culling phases separated?
            /// </summary>
            public: property bool Separate
            {
                public: bool __clrcall get() { return __v_Separate; }
                internal: void __clrcall set(bool value) { __v_Separate = value; }
            }
        };
        
        /// <summary>
        /// Arguments for OnSpendAmmo event.
        /// </summary>
        public ref class SpendAmmoEventArgs : public HookedEventArgs
        {
            private: Actor^ __v_Spender;
            /// <summary>
            /// The actor that is spending ammo.
            /// </summary>
            public: property Actor^ Spender
            {
                public: Actor^ __clrcall get() { return __v_Spender; }
                internal: void __clrcall set(Actor^ value) { __v_Spender = value; }
            }
            
            private: TESObjectWEAP^ __v_Weapon;
            /// <summary>
            /// The weapon that is being used.
            /// </summary>
            public: property TESObjectWEAP^ Weapon
            {
                public: TESObjectWEAP^ __clrcall get() { return __v_Weapon; }
                internal: void __clrcall set(TESObjectWEAP^ value) { __v_Weapon = value; }
            }
            
            private: System::Int32 __v_HasAmount;
            /// <summary>
            /// Gets the amount of ammo the actor currently has.
            /// </summary>
            public: property System::Int32 HasAmount
            {
                public: System::Int32 __clrcall get() { return __v_HasAmount; }
                internal: void __clrcall set(System::Int32 value) { __v_HasAmount = value; }
            }
            
            private: System::Int32 __v_ReduceAmount;
            /// <summary>
            /// Gets or sets the amount of ammo being used.
            /// </summary>
            public: property System::Int32 ReduceAmount
            {
                public: System::Int32 __clrcall get() { return __v_ReduceAmount; }
                public: void __clrcall set(System::Int32 value) { __v_ReduceAmount = value; }
            }
            
            private: bool __v_Force;
            /// <summary>
            /// Force ammo to be used? If this is true then ammo will be used even if actor is not player and weapon does not have the flag to force use ammo.
            /// </summary>
            public: property bool Force
            {
                public: bool __clrcall get() { return __v_Force; }
                public: void __clrcall set(bool value) { __v_Force = value; }
            }
            
            private: bool __v_Had;
            /// <summary>
            /// Had reduce.
            /// </summary>
            public: property bool Had
            {
                internal: bool __clrcall get() { return __v_Had; }
                internal: void __clrcall set(bool value) { __v_Had = value; }
            }
        };
        
        /// <summary>
        /// Arguments for OnSpendMagicCost event.
        /// </summary>
        public ref class SpendMagicCostEventArgs : public HookedEventArgs
        {
            private: ActorMagicCaster^ __v_Spender;
            /// <summary>
            /// The actor caster that is going to spend cost.
            /// </summary>
            public: property ActorMagicCaster^ Spender
            {
                public: ActorMagicCaster^ __clrcall get() { return __v_Spender; }
                internal: void __clrcall set(ActorMagicCaster^ value) { __v_Spender = value; }
            }
            
            private: MagicItem^ __v_Item;
            /// <summary>
            /// The spell or thing being cast.
            /// </summary>
            public: property MagicItem^ Item
            {
                public: MagicItem^ __clrcall get() { return __v_Item; }
                internal: void __clrcall set(MagicItem^ value) { __v_Item = value; }
            }
            
            private: System::Int32 __v_ActorValueIndex;
            /// <summary>
            /// The actor value that is being spent to cast this. Setting this to -1 will make it not cost anything.
            /// </summary>
            public: property System::Int32 ActorValueIndex
            {
                public: System::Int32 __clrcall get() { return __v_ActorValueIndex; }
                public: void __clrcall set(System::Int32 value) { __v_ActorValueIndex = value; }
            }
        };
        
        /// <summary>
        /// Arguments for OnSpendPoison event.
        /// </summary>
        public ref class SpendPoisonEventArgs : public HookedEventArgs
        {
            private: Actor^ __v_Spender;
            /// <summary>
            /// The actor that is spending the charge.
            /// </summary>
            public: property Actor^ Spender
            {
                public: Actor^ __clrcall get() { return __v_Spender; }
                internal: void __clrcall set(Actor^ value) { __v_Spender = value; }
            }
            
            private: ExtraContainerChanges::ItemEntry^ __v_Item;
            /// <summary>
            /// The item that is being used in attack. This is the item that has the poison charge on it.
            /// </summary>
            public: property ExtraContainerChanges::ItemEntry^ Item
            {
                public: ExtraContainerChanges::ItemEntry^ __clrcall get() { return __v_Item; }
                internal: void __clrcall set(ExtraContainerChanges::ItemEntry^ value) { __v_Item = value; }
            }
            
            private: bool __v_Skip;
            /// <summary>
            /// Skip reducing the poison charge?
            /// </summary>
            public: property bool Skip
            {
                public: bool __clrcall get() { return __v_Skip; }
                public: void __clrcall set(bool value) { __v_Skip = value; }
            }
        };
        
        /// <summary>
        /// Arguments for OnUpdateCamera event.
        /// </summary>
        public ref class UpdateCameraEventArgs : public HookedEventArgs
        {
            private: TESCamera^ __v_Camera;
            /// <summary>
            /// The camera that is being updated.
            /// </summary>
            public: property TESCamera^ Camera
            {
                public: TESCamera^ __clrcall get() { return __v_Camera; }
                internal: void __clrcall set(TESCamera^ value) { __v_Camera = value; }
            }
        };
        
        /// <summary>
        /// Arguments for OnUpdatedPlayerHeadtrack event.
        /// </summary>
        public ref class UpdatedPlayerHeadtrackEventArgs : public HookedEventArgs
        {
        };
        
        /// <summary>
        /// Arguments for OnUpdatePlayerControls event.
        /// </summary>
        public ref class UpdatePlayerControlsEventArgs : public HookedEventArgs
        {
            private: PlayerControls^ __v_Controls;
            /// <summary>
            /// The player controls instance.
            /// </summary>
            public: property PlayerControls^ Controls
            {
                public: PlayerControls^ __clrcall get() { return __v_Controls; }
                internal: void __clrcall set(PlayerControls^ value) { __v_Controls = value; }
            }
        };
        
        /// <summary>
        /// Arguments for OnUpdatePlayerTurnToCamera event.
        /// </summary>
        public ref class UpdatePlayerTurnToCameraEventArgs : public HookedEventArgs
        {
            private: Actor^ __v_Target;
            /// <summary>
            /// The actor that is being controlled by camera and will be rotated or not.
            /// </summary>
            public: property Actor^ Target
            {
                public: Actor^ __clrcall get() { return __v_Target; }
                internal: void __clrcall set(Actor^ value) { __v_Target = value; }
            }
            
            private: bool __v_FreeLook;
            /// <summary>
            /// Should actor have free look or should they face the camera.
            /// </summary>
            public: property bool FreeLook
            {
                public: bool __clrcall get() { return __v_FreeLook; }
                public: void __clrcall set(bool value) { __v_FreeLook = value; }
            }
            
            private: bool __v_Moving;
            /// <summary>
            /// Is the actor moving?
            /// </summary>
            public: property bool Moving
            {
                public: bool __clrcall get() { return __v_Moving; }
                internal: void __clrcall set(bool value) { __v_Moving = value; }
            }
            
            private: bool __v_Weapon;
            /// <summary>
            /// Does the actor have weapon out?
            /// </summary>
            public: property bool Weapon
            {
                public: bool __clrcall get() { return __v_Weapon; }
                internal: void __clrcall set(bool value) { __v_Weapon = value; }
            }
            
            private: bool __v_Had;
            /// <summary>
            /// Internal value.
            /// </summary>
            public: property bool Had
            {
                internal: bool __clrcall get() { return __v_Had; }
                internal: void __clrcall set(bool value) { __v_Had = value; }
            }
        };
        
        /// <summary>
        /// Arguments for OnWeaponFireProjectilePosition event.
        /// </summary>
        public ref class WeaponFireProjectilePositionEventArgs : public HookedEventArgs
        {
            private: TESObjectREFR^ __v_Attacker;
            /// <summary>
            /// The object or actor who is firing this weapon.
            /// </summary>
            public: property TESObjectREFR^ Attacker
            {
                public: TESObjectREFR^ __clrcall get() { return __v_Attacker; }
                internal: void __clrcall set(TESObjectREFR^ value) { __v_Attacker = value; }
            }
            
            private: NiAVObject^ __v_Node;
            /// <summary>
            /// The node where the position would be copied from. Set this to null to use the current point position instead.
            /// </summary>
            public: property NiAVObject^ Node
            {
                public: NiAVObject^ __clrcall get() { return __v_Node; }
                public: void __clrcall set(NiAVObject^ value) { __v_Node = value; }
            }
            
            private: NiPoint3^ __v_Position;
            /// <summary>
            /// The position that will be used if node is null.
            /// </summary>
            public: property NiPoint3^ Position
            {
                public: NiPoint3^ __clrcall get() { return __v_Position; }
                internal: void __clrcall set(NiPoint3^ value) { __v_Position = value; }
            }
            
            private: TESObjectWEAP^ __v_Weapon;
            /// <summary>
            /// The weapon that is being fired.
            /// </summary>
            public: property TESObjectWEAP^ Weapon
            {
                public: TESObjectWEAP^ __clrcall get() { return __v_Weapon; }
                internal: void __clrcall set(TESObjectWEAP^ value) { __v_Weapon = value; }
            }
        };
        
        /// <summary>
        /// Contains hooks for game events.
        /// </summary>
        public ref class Events sealed
        {
        private: static NetScriptFramework::Event<BarterMenuEventArgs^>^ __handler_BarterMenu;
        public:
            /// <summary>
            /// Event is raised when opening or closing the trade/barter menu.
            /// </summary>
            /// <value>
            /// OnBarterMenu event handler.
            /// </value>
            static property NetScriptFramework::Event<BarterMenuEventArgs^>^ OnBarterMenu
            {
                NetScriptFramework::Event<BarterMenuEventArgs^>^ get() { return __handler_BarterMenu; }
            }
        private: static BarterMenuEventArgs^ __before_BarterMenu_1(NetScriptFramework::CPURegisters^ ctx)
            {
                BarterMenuEventArgs^ args = gcnew BarterMenuEventArgs();
                args->Entering = true;
                args->RefHandle = Memory::ReadUInt32(MCH::FromBase(0x142F72ED4), false);
                return args;
            }
            
        private: static BarterMenuEventArgs^ __before_BarterMenu_2(NetScriptFramework::CPURegisters^ ctx)
            {
                BarterMenuEventArgs^ args = gcnew BarterMenuEventArgs();
                args->Entering = false;
                args->RefHandle = Memory::ReadUInt32(MCH::FromBase(0x142F72ED4), false);
                return args;
            }
            
        private: static NetScriptFramework::Event<CalculateDetectionEventArgs^>^ __handler_CalculateDetection;
        public:
            /// <summary>
            /// Event is raised when calculating whether actor detects another.
            /// </summary>
            /// <value>
            /// OnCalculateDetection event handler.
            /// </value>
            static property NetScriptFramework::Event<CalculateDetectionEventArgs^>^ OnCalculateDetection
            {
                NetScriptFramework::Event<CalculateDetectionEventArgs^>^ get() { return __handler_CalculateDetection; }
            }
        private: static CalculateDetectionEventArgs^ __before_CalculateDetection(NetScriptFramework::CPURegisters^ ctx)
            {
                CalculateDetectionEventArgs^ args = gcnew CalculateDetectionEventArgs();
                args->SourceActor = MemoryObject::FromAddress<Actor^>(Memory::ReadPointer(ctx->SP + 0x70, false));
                args->TargetActor = MemoryObject::FromAddress<Actor^>(ctx->BX);
                args->ResultValue = Memory::ReadInt32(ctx->BP + 0xD0, false);
                args->Position = MemoryObject::FromAddress<NiPoint3^>(Memory::ReadPointer(ctx->BP - 0x68, false));
                return args;
            }
        private: static void __after_CalculateDetection(NetScriptFramework::CPURegisters^ ctx, CalculateDetectionEventArgs^ args)
            {
                int val = args->ResultValue;
                if(val < -1000) val = -1000;
                Memory::WriteInt32(ctx->BP + 0xD0, val, false);
            }
            
        private: static NetScriptFramework::Event<CameraStateChangingEventArgs^>^ __handler_CameraStateChanging;
        public:
            /// <summary>
            /// This is raised when the camera state is about to change. This is called for all cameras not only player camera!
            /// </summary>
            /// <value>
            /// OnCameraStateChanging event handler.
            /// </value>
            static property NetScriptFramework::Event<CameraStateChangingEventArgs^>^ OnCameraStateChanging
            {
                NetScriptFramework::Event<CameraStateChangingEventArgs^>^ get() { return __handler_CameraStateChanging; }
            }
        private: static CameraStateChangingEventArgs^ __before_CameraStateChanging(NetScriptFramework::CPURegisters^ ctx)
            {
                CameraStateChangingEventArgs^ args = gcnew CameraStateChangingEventArgs();
                args->Camera = MemoryObject::FromAddress<TESCamera^>(ctx->CX);
                if(args->Camera != nullptr) args->PreviousState = args->Camera->State;
                args->NextState = MemoryObject::FromAddress<TESCameraState^>(ctx->DX);
                args->Skip = false;
                return args;
            }
        private: static void __after_CameraStateChanging(NetScriptFramework::CPURegisters^ ctx, CameraStateChangingEventArgs^ args)
            {
                if(args->Skip)
                {
                ctx->IP = MCH::FromBase(0x1404F5E70 + 0x6A);
                }
                else
                {
                ctx->DX = args->NextState != nullptr ? args->NextState->Address : System::IntPtr::Zero;
                }
            }
            
        private: static NetScriptFramework::Event<FrameEventArgs^>^ __handler_Frame;
        public:
            /// <summary>
            /// Event is raised every frame.
            /// </summary>
            /// <value>
            /// OnFrame event handler.
            /// </value>
            static property NetScriptFramework::Event<FrameEventArgs^>^ OnFrame
            {
                NetScriptFramework::Event<FrameEventArgs^>^ get() { return __handler_Frame; }
            }
        private: static FrameEventArgs^ __before_Frame(NetScriptFramework::CPURegisters^ ctx)
            {
                FrameEventArgs^ args = gcnew FrameEventArgs();
                return args;
            }
            
        private: static NetScriptFramework::Event<InterruptCastEventArgs^>^ __handler_InterruptCast;
        public:
            /// <summary>
            /// Raised when casting is being interrupted.
            /// </summary>
            /// <value>
            /// OnInterruptCast event handler.
            /// </value>
            static property NetScriptFramework::Event<InterruptCastEventArgs^>^ OnInterruptCast
            {
                NetScriptFramework::Event<InterruptCastEventArgs^>^ get() { return __handler_InterruptCast; }
            }
        private: static InterruptCastEventArgs^ __before_InterruptCast(NetScriptFramework::CPURegisters^ ctx)
            {
                InterruptCastEventArgs^ args = gcnew InterruptCastEventArgs();
                args->Caster = MemoryObject::FromAddress<MagicCaster^>(ctx->BX);
                return args;
            }
            
        private: static NetScriptFramework::Event<MagicCasterFireEventArgs^>^ __handler_MagicCasterFire;
        public:
            /// <summary>
            /// Raised when magic caster fires the spell.
            /// </summary>
            /// <value>
            /// OnMagicCasterFire event handler.
            /// </value>
            static property NetScriptFramework::Event<MagicCasterFireEventArgs^>^ OnMagicCasterFire
            {
                NetScriptFramework::Event<MagicCasterFireEventArgs^>^ get() { return __handler_MagicCasterFire; }
            }
        private: static MagicCasterFireEventArgs^ __before_MagicCasterFire(NetScriptFramework::CPURegisters^ ctx)
            {
                MagicCasterFireEventArgs^ args = gcnew MagicCasterFireEventArgs();
                args->Caster = MemoryObject::FromAddress<MagicCaster^>(ctx->DI);
                args->Item = MemoryObject::FromAddress<MagicItem^>(ctx->SI);
                return args;
            }
            
        private: static NetScriptFramework::Event<MainMenuEventArgs^>^ __handler_MainMenu;
        public:
            /// <summary>
            /// Event is raised when entering or exiting the Main Menu. This is called after the initial loading icon is finished when entering for the first time. This event is raised again if player returns to main menu from game later.
            /// </summary>
            /// <value>
            /// OnMainMenu event handler.
            /// </value>
            static property NetScriptFramework::Event<MainMenuEventArgs^>^ OnMainMenu
            {
                NetScriptFramework::Event<MainMenuEventArgs^>^ get() { return __handler_MainMenu; }
            }
        private: static MainMenuEventArgs^ __before_MainMenu_1(NetScriptFramework::CPURegisters^ ctx)
            {
                MainMenuEventArgs^ args = gcnew MainMenuEventArgs();
                args->Entering = false;
                return args;
            }
            
        private: static MainMenuEventArgs^ __before_MainMenu_2(NetScriptFramework::CPURegisters^ ctx)
            {
                MainMenuEventArgs^ args = gcnew MainMenuEventArgs();
                args->Entering = true;
                return args;
            }
            
        private: static NetScriptFramework::Event<ReduceHUDAmmoCounterEventArgs^>^ __handler_ReduceHUDAmmoCounter;
        public:
            /// <summary>
            /// This is raised when player uses ammo and we are about to reduce the counter in HUD.
            /// </summary>
            /// <value>
            /// OnReduceHUDAmmoCounter event handler.
            /// </value>
            static property NetScriptFramework::Event<ReduceHUDAmmoCounterEventArgs^>^ OnReduceHUDAmmoCounter
            {
                NetScriptFramework::Event<ReduceHUDAmmoCounterEventArgs^>^ get() { return __handler_ReduceHUDAmmoCounter; }
            }
        private: static ReduceHUDAmmoCounterEventArgs^ __before_ReduceHUDAmmoCounter(NetScriptFramework::CPURegisters^ ctx)
            {
                ReduceHUDAmmoCounterEventArgs^ args = gcnew ReduceHUDAmmoCounterEventArgs();
                args->HasAmount = (int)(MCH::u(ctx->AX) & 0xFFFFFFFF);
                args->Item = MemoryObject::FromAddress<ExtraContainerChanges::ItemEntry^>(ctx->R14);
                args->ReduceAmount = 1;
                return args;
            }
        private: static void __after_ReduceHUDAmmoCounter(NetScriptFramework::CPURegisters^ ctx, ReduceHUDAmmoCounterEventArgs^ args)
            {
                int newCount = args->HasAmount - args->ReduceAmount;
                ctx->AX = System::IntPtr((long long)((unsigned int)newCount));
            }
            
        private: static NetScriptFramework::Event<RemoveMagicEffectsWithArchetypeEventArgs^>^ __handler_RemoveMagicEffectsWithArchetype;
        public:
            /// <summary>
            /// Raised when going to remove magic effects with specific archetype due to actions taken.
            /// </summary>
            /// <value>
            /// OnRemoveMagicEffectsWithArchetype event handler.
            /// </value>
            static property NetScriptFramework::Event<RemoveMagicEffectsWithArchetypeEventArgs^>^ OnRemoveMagicEffectsWithArchetype
            {
                NetScriptFramework::Event<RemoveMagicEffectsWithArchetypeEventArgs^>^ get() { return __handler_RemoveMagicEffectsWithArchetype; }
            }
        private: static RemoveMagicEffectsWithArchetypeEventArgs^ __before_RemoveMagicEffectsWithArchetype_1(NetScriptFramework::CPURegisters^ ctx)
            {
                RemoveMagicEffectsWithArchetypeEventArgs^ args = gcnew RemoveMagicEffectsWithArchetypeEventArgs();
                args->Owner = MemoryObject::FromAddress<Actor^>(ctx->BX);
                args->Reason = MagicEffectRemovalReasons::Unknown;
                args->Archetype = (Archetypes)(MCH::u(ctx->DX) & 0xFFFFFFFF);
                args->Skip = false;
                auto debug = CrashLog::Debug;
                if(debug != nullptr)
                {
                auto fromPtr = Memory::ReadPointer(ctx->SP + 0x28, false);
                auto fn = debug->GetFunctionInfo(fromPtr, true);
                if(fn != nullptr)
                {
                switch(fn->Id)
                {
                case 19369: args->Reason = MagicEffectRemovalReasons::Activation; break;
                case 33363: args->Reason = MagicEffectRemovalReasons::CastSpellOrUseMagicItem; break;
                case 36220: args->Reason = MagicEffectRemovalReasons::Dialogue; break;
                case 37650: args->Reason = MagicEffectRemovalReasons::Attacking; break;
                case 41778: args->Reason = MagicEffectRemovalReasons::Attacking; break;
                }
                }
                }
                return args;
            }
        private: static void __after_RemoveMagicEffectsWithArchetype_1(NetScriptFramework::CPURegisters^ ctx, RemoveMagicEffectsWithArchetypeEventArgs^ args)
            {
                if(args->Skip) ctx->Skip();
            }
            
        private: static RemoveMagicEffectsWithArchetypeEventArgs^ __before_RemoveMagicEffectsWithArchetype_2(NetScriptFramework::CPURegisters^ ctx)
            {
                RemoveMagicEffectsWithArchetypeEventArgs^ args = gcnew RemoveMagicEffectsWithArchetypeEventArgs();
                args->Owner = MemoryObject::FromAddress<Actor^>(ctx->BX);
                args->Reason = MagicEffectRemovalReasons::Unknown;
                args->Archetype = (Archetypes)(MCH::u(ctx->DX) & 0xFFFFFFFF);
                args->Skip = false;
                auto debug = CrashLog::Debug;
                if(debug != nullptr)
                {
                auto fromPtr = Memory::ReadPointer(ctx->SP + 0x28, false);
                auto fn = debug->GetFunctionInfo(fromPtr, true);
                if(fn != nullptr)
                {
                switch(fn->Id)
                {
                case 19369: args->Reason = MagicEffectRemovalReasons::Activation; break;
                case 33363: args->Reason = MagicEffectRemovalReasons::CastSpellOrUseMagicItem; break;
                case 36220: args->Reason = MagicEffectRemovalReasons::Dialogue; break;
                case 37650: args->Reason = MagicEffectRemovalReasons::Attacking; break;
                case 41778: args->Reason = MagicEffectRemovalReasons::Attacking; break;
                }
                }
                }
                return args;
            }
        private: static void __after_RemoveMagicEffectsWithArchetype_2(NetScriptFramework::CPURegisters^ ctx, RemoveMagicEffectsWithArchetypeEventArgs^ args)
            {
                if(args->Skip) ctx->Skip();
            }
            
        private: static RemoveMagicEffectsWithArchetypeEventArgs^ __before_RemoveMagicEffectsWithArchetype_3(NetScriptFramework::CPURegisters^ ctx)
            {
                RemoveMagicEffectsWithArchetypeEventArgs^ args = gcnew RemoveMagicEffectsWithArchetypeEventArgs();
                args->Owner = MemoryObject::FromAddress<Actor^>(ctx->DI);
                args->Reason = MagicEffectRemovalReasons::Attacked;
                args->Archetype = (Archetypes)(MCH::u(ctx->DX) & 0xFFFFFFFF);
                args->Skip = false;
                return args;
            }
        private: static void __after_RemoveMagicEffectsWithArchetype_3(NetScriptFramework::CPURegisters^ ctx, RemoveMagicEffectsWithArchetypeEventArgs^ args)
            {
                if(args->Skip) ctx->Skip();
            }
            
        private: static NetScriptFramework::Event<ShadowCullingBeginEventArgs^>^ __handler_ShadowCullingBegin;
        public:
            /// <summary>
            /// Event is raised when shadow culling is about to begin.
            /// </summary>
            /// <value>
            /// OnShadowCullingBegin event handler.
            /// </value>
            static property NetScriptFramework::Event<ShadowCullingBeginEventArgs^>^ OnShadowCullingBegin
            {
                NetScriptFramework::Event<ShadowCullingBeginEventArgs^>^ get() { return __handler_ShadowCullingBegin; }
            }
        private: static ShadowCullingBeginEventArgs^ __before_ShadowCullingBegin(NetScriptFramework::CPURegisters^ ctx)
            {
                ShadowCullingBeginEventArgs^ args = gcnew ShadowCullingBeginEventArgs();
                return args;
            }
        private: static void __after_ShadowCullingBegin(NetScriptFramework::CPURegisters^ ctx, ShadowCullingBeginEventArgs^ args)
            {
                if(args->Separate)
                {
                ShadowCullingBeginEventArgs::__state = 1;
                }
                else
                {
                ShadowCullingBeginEventArgs::__state = 0;
                auto ptr = Memory::ReadPointer(MCH::FromBase(0x143258890), false);
                Memory::InvokeCdecl(MCH::FromBase(0x140C31BC0), ptr, 0, 0);
                }
                Memory::InvokeCdecl(MCH::FromBase(0x1412FA330));
            }
            
        private: static NetScriptFramework::Event<ShadowCullingEndEventArgs^>^ __handler_ShadowCullingEnd;
        public:
            /// <summary>
            /// Event is raised when shadow culling is finishing.
            /// </summary>
            /// <value>
            /// OnShadowCullingEnd event handler.
            /// </value>
            static property NetScriptFramework::Event<ShadowCullingEndEventArgs^>^ OnShadowCullingEnd
            {
                NetScriptFramework::Event<ShadowCullingEndEventArgs^>^ get() { return __handler_ShadowCullingEnd; }
            }
        private: static ShadowCullingEndEventArgs^ __before_ShadowCullingEnd(NetScriptFramework::CPURegisters^ ctx)
            {
                ShadowCullingEndEventArgs^ args = gcnew ShadowCullingEndEventArgs();
                args->Separate = ShadowCullingBeginEventArgs::__state != 0;
                return args;
            }
        private: static void __after_ShadowCullingEnd(NetScriptFramework::CPURegisters^ ctx, ShadowCullingEndEventArgs^ args)
            {
                auto ptr = Memory::ReadPointer(MCH::FromBase(0x143258890), false);
                if(args->Separate) Memory::InvokeCdecl(MCH::FromBase(0x140C31BC0), ptr, 0, 0);
                Memory::InvokeCdecl(MCH::FromBase(0x140C31BE0), ptr);
            }
            
        private: static NetScriptFramework::Event<SpendAmmoEventArgs^>^ __handler_SpendAmmo;
        public:
            /// <summary>
            /// Event is raised just before actor is about to spend ammo.
            /// </summary>
            /// <value>
            /// OnSpendAmmo event handler.
            /// </value>
            static property NetScriptFramework::Event<SpendAmmoEventArgs^>^ OnSpendAmmo
            {
                NetScriptFramework::Event<SpendAmmoEventArgs^>^ get() { return __handler_SpendAmmo; }
            }
        private: static SpendAmmoEventArgs^ __before_SpendAmmo(NetScriptFramework::CPURegisters^ ctx)
            {
                SpendAmmoEventArgs^ args = gcnew SpendAmmoEventArgs();
                args->Spender = MemoryObject::FromAddress<Actor^>(ctx->BX);
                args->Weapon = MemoryObject::FromAddress<TESObjectWEAP^>(ctx->BP);
                args->HasAmount = (int)(MCH::u(ctx->DI) & 0xFFFFFFFF);
                args->ReduceAmount = (int)(MCH::u(ctx->SI) & 0xFFFFFFFF);
                args->Force = false;
                args->Had = args->ReduceAmount > 0;
                return args;
            }
        private: static void __after_SpendAmmo(NetScriptFramework::CPURegisters^ ctx, SpendAmmoEventArgs^ args)
            {
                if(args->Had && args->ReduceAmount <= 0)
                {
                ctx->R14 = Memory::ReadPointer(ctx->AX, false);
                ctx->IP = MCH::FromBase(0x140624A50 + 0x20A);
                return;
                }
                ctx->SI = System::IntPtr((long long)((unsigned int)args->ReduceAmount));
                if(args->Force)
                {
                ctx->R14 = Memory::ReadPointer(ctx->AX, false);
                ctx->IP = MCH::FromBase(0x140624A50 + 0xD0);
                }
            }
            
        private: static NetScriptFramework::Event<SpendMagicCostEventArgs^>^ __handler_SpendMagicCost;
        public:
            /// <summary>
            /// Event is raised when we are about to calculate the casting cost for a magic thing.
            /// </summary>
            /// <value>
            /// OnSpendMagicCost event handler.
            /// </value>
            static property NetScriptFramework::Event<SpendMagicCostEventArgs^>^ OnSpendMagicCost
            {
                NetScriptFramework::Event<SpendMagicCostEventArgs^>^ get() { return __handler_SpendMagicCost; }
            }
        private: static SpendMagicCostEventArgs^ __before_SpendMagicCost_1(NetScriptFramework::CPURegisters^ ctx)
            {
                SpendMagicCostEventArgs^ args = gcnew SpendMagicCostEventArgs();
                args->Spender = MemoryObject::FromAddress<ActorMagicCaster^>(ctx->BX);
                args->Item = MemoryObject::FromAddress<MagicItem^>(ctx->DI);
                args->ActorValueIndex = (int)(MCH::u(ctx->AX) & 0xFFFFFFFF);
                return args;
            }
        private: static void __after_SpendMagicCost_1(NetScriptFramework::CPURegisters^ ctx, SpendMagicCostEventArgs^ args)
            {
                ctx->AX = System::IntPtr((long long)((unsigned int)args->ActorValueIndex));
            }
            
        private: static NetScriptFramework::Event<SpendPoisonEventArgs^>^ __handler_SpendPoison;
        public:
            /// <summary>
            /// Event is raised when poison charge from weapon is about to be spent.
            /// </summary>
            /// <value>
            /// OnSpendPoison event handler.
            /// </value>
            static property NetScriptFramework::Event<SpendPoisonEventArgs^>^ OnSpendPoison
            {
                NetScriptFramework::Event<SpendPoisonEventArgs^>^ get() { return __handler_SpendPoison; }
            }
        private: static SpendPoisonEventArgs^ __before_SpendPoison(NetScriptFramework::CPURegisters^ ctx)
            {
                SpendPoisonEventArgs^ args = gcnew SpendPoisonEventArgs();
                args->Spender = MemoryObject::FromAddress<Actor^>(ctx->BX);
                args->Item = MemoryObject::FromAddress<ExtraContainerChanges::ItemEntry^>(ctx->DI);
                args->Skip = false;
                return args;
            }
        private: static void __after_SpendPoison(NetScriptFramework::CPURegisters^ ctx, SpendPoisonEventArgs^ args)
            {
                if(args->Skip)
                ctx->Skip();
            }
            
        private: static SpendPoisonEventArgs^ __before_SpendPoison_2(NetScriptFramework::CPURegisters^ ctx)
            {
                SpendPoisonEventArgs^ args = gcnew SpendPoisonEventArgs();
                args->Spender = MemoryObject::FromAddress<Actor^>(ctx->SI);
                args->Item = MemoryObject::FromAddress<ExtraContainerChanges::ItemEntry^>(ctx->DI);
                args->Skip = false;
                return args;
            }
        private: static void __after_SpendPoison_2(NetScriptFramework::CPURegisters^ ctx, SpendPoisonEventArgs^ args)
            {
                if(args->Skip)
                ctx->Skip();
            }
            
        private: static NetScriptFramework::Event<UpdateCameraEventArgs^>^ __handler_UpdateCamera;
        public:
            /// <summary>
            /// Event is raised when camera is updated.
            /// </summary>
            /// <value>
            /// OnUpdateCamera event handler.
            /// </value>
            static property NetScriptFramework::Event<UpdateCameraEventArgs^>^ OnUpdateCamera
            {
                NetScriptFramework::Event<UpdateCameraEventArgs^>^ get() { return __handler_UpdateCamera; }
            }
        private: static UpdateCameraEventArgs^ __before_UpdateCamera(NetScriptFramework::CPURegisters^ ctx)
            {
                UpdateCameraEventArgs^ args = gcnew UpdateCameraEventArgs();
                args->Camera = MemoryObject::FromAddress<TESCamera^>(ctx->DI);
                return args;
            }
            
        private: static NetScriptFramework::Event<UpdatedPlayerHeadtrackEventArgs^>^ __handler_UpdatedPlayerHeadtrack;
        public:
            /// <summary>
            /// This event is raised just after calculating player head track. This is here so you can overwrite it if you wish.
            /// </summary>
            /// <value>
            /// OnUpdatedPlayerHeadtrack event handler.
            /// </value>
            static property NetScriptFramework::Event<UpdatedPlayerHeadtrackEventArgs^>^ OnUpdatedPlayerHeadtrack
            {
                NetScriptFramework::Event<UpdatedPlayerHeadtrackEventArgs^>^ get() { return __handler_UpdatedPlayerHeadtrack; }
            }
        private: static UpdatedPlayerHeadtrackEventArgs^ __before_UpdatedPlayerHeadtrack(NetScriptFramework::CPURegisters^ ctx)
            {
                UpdatedPlayerHeadtrackEventArgs^ args = gcnew UpdatedPlayerHeadtrackEventArgs();
                return args;
            }
            
        private: static NetScriptFramework::Event<UpdatePlayerControlsEventArgs^>^ __handler_UpdatePlayerControls;
        public:
            /// <summary>
            /// This is raised every frame to update the player controls. It is not raised in menus or if the controls should not reach the player character for other reasons.
            /// </summary>
            /// <value>
            /// OnUpdatePlayerControls event handler.
            /// </value>
            static property NetScriptFramework::Event<UpdatePlayerControlsEventArgs^>^ OnUpdatePlayerControls
            {
                NetScriptFramework::Event<UpdatePlayerControlsEventArgs^>^ get() { return __handler_UpdatePlayerControls; }
            }
        private: static UpdatePlayerControlsEventArgs^ __before_UpdatePlayerControls(NetScriptFramework::CPURegisters^ ctx)
            {
                UpdatePlayerControlsEventArgs^ args = gcnew UpdatePlayerControlsEventArgs();
                args->Controls = MemoryObject::FromAddress<PlayerControls^>(ctx->BX);
                return args;
            }
        private: static void __after_UpdatePlayerControls(NetScriptFramework::CPURegisters^ ctx, UpdatePlayerControlsEventArgs^ args)
            {
                if(Memory::ReadUInt8(ctx->BX + 0x4F, false) == 0) ctx->IP = MCH::FromBase(0x140704FD0 + 0x9A);
            }
            
        private: static NetScriptFramework::Event<UpdatePlayerTurnToCameraEventArgs^>^ __handler_UpdatePlayerTurnToCamera;
        public:
            /// <summary>
            /// Event is raised when calculating whether player should turn to where camera is facing.
            /// </summary>
            /// <value>
            /// OnUpdatePlayerTurnToCamera event handler.
            /// </value>
            static property NetScriptFramework::Event<UpdatePlayerTurnToCameraEventArgs^>^ OnUpdatePlayerTurnToCamera
            {
                NetScriptFramework::Event<UpdatePlayerTurnToCameraEventArgs^>^ get() { return __handler_UpdatePlayerTurnToCamera; }
            }
        private: static UpdatePlayerTurnToCameraEventArgs^ __before_UpdatePlayerTurnToCamera(NetScriptFramework::CPURegisters^ ctx)
            {
                UpdatePlayerTurnToCameraEventArgs^ args = gcnew UpdatePlayerTurnToCameraEventArgs();
                args->Target = MemoryObject::FromAddress<Actor^>(ctx->AX);
                args->FreeLook = MCH::b(ctx->DI);
                args->Moving = MCH::b(ctx->DX);
                args->Weapon = !MCH::b(ctx->SI);
                args->Had = args->FreeLook;
                return args;
            }
        private: static void __after_UpdatePlayerTurnToCamera(NetScriptFramework::CPURegisters^ ctx, UpdatePlayerTurnToCameraEventArgs^ args)
            {
                if(args->Had != args->FreeLook)
                {
                ctx->DI = System::IntPtr((long long)(args->FreeLook ? 1 : 0));
                if(args->FreeLook)
                {
                ctx->DX = System::IntPtr::Zero;
                ctx->SI = System::IntPtr((long long)1);
                }
                else
                {
                ctx->SI = System::IntPtr::Zero;
                ctx->DX = System::IntPtr((long long)1);
                }
                }
            }
            
        private: static NetScriptFramework::Event<WeaponFireProjectilePositionEventArgs^>^ __handler_WeaponFireProjectilePosition;
        public:
            /// <summary>
            /// Event is raised when creating a projectile from firing a weapon. Here you can overwrite the position where the projectile begins from.
            /// </summary>
            /// <value>
            /// OnWeaponFireProjectilePosition event handler.
            /// </value>
            static property NetScriptFramework::Event<WeaponFireProjectilePositionEventArgs^>^ OnWeaponFireProjectilePosition
            {
                NetScriptFramework::Event<WeaponFireProjectilePositionEventArgs^>^ get() { return __handler_WeaponFireProjectilePosition; }
            }
        private: static WeaponFireProjectilePositionEventArgs^ __before_WeaponFireProjectilePosition(NetScriptFramework::CPURegisters^ ctx)
            {
                WeaponFireProjectilePositionEventArgs^ args = gcnew WeaponFireProjectilePositionEventArgs();
                args->Attacker = MemoryObject::FromAddress<TESObjectREFR^>(ctx->R13);
                args->Node = MemoryObject::FromAddress<NiAVObject^>(ctx->AX);
                args->Position = MemoryObject::FromAddress<NiPoint3^>(ctx->SP + 0x48);
                args->Weapon = MemoryObject::FromAddress<TESObjectWEAP^>(ctx->R12);
                return args;
            }
        private: static void __after_WeaponFireProjectilePosition(NetScriptFramework::CPURegisters^ ctx, WeaponFireProjectilePositionEventArgs^ args)
            {
                auto ptr = args->Node != nullptr ? args->Node->Address : System::IntPtr::Zero;
                ctx->AX = ptr;
                ctx->BX = ptr;
            }
        internal:
            static void InitializeEvents()
            {
                __handler_BarterMenu = gcnew NetScriptFramework::EventHook<BarterMenuEventArgs^>(NetScriptFramework::EventHookFlags::None, "BarterMenu", gcnew NetScriptFramework::EventHookParameters<BarterMenuEventArgs^>(MCH::FromBase(0x140851BF0), 5, 5, gcnew System::Func<NetScriptFramework::CPURegisters^, BarterMenuEventArgs^>(__before_BarterMenu_1), nullptr), gcnew NetScriptFramework::EventHookParameters<BarterMenuEventArgs^>(MCH::FromBase(0x1408560D9), 5, 5, gcnew System::Func<NetScriptFramework::CPURegisters^, BarterMenuEventArgs^>(__before_BarterMenu_2), nullptr));
                __handler_CalculateDetection = gcnew NetScriptFramework::EventHook<CalculateDetectionEventArgs^>(NetScriptFramework::EventHookFlags::None, "CalculateDetection", gcnew NetScriptFramework::EventHookParameters<CalculateDetectionEventArgs^>(MCH::FromBase(0x14071A0AB), 6, 6, gcnew System::Func<NetScriptFramework::CPURegisters^, CalculateDetectionEventArgs^>(__before_CalculateDetection), gcnew System::Action<NetScriptFramework::CPURegisters^, CalculateDetectionEventArgs^>(__after_CalculateDetection)));
                __handler_CameraStateChanging = gcnew NetScriptFramework::EventHook<CameraStateChangingEventArgs^>(NetScriptFramework::EventHookFlags::None, "CameraStateChanging", gcnew NetScriptFramework::EventHookParameters<CameraStateChangingEventArgs^>(MCH::FromBase(0x1404F5E70), 5, 5, gcnew System::Func<NetScriptFramework::CPURegisters^, CameraStateChangingEventArgs^>(__before_CameraStateChanging), gcnew System::Action<NetScriptFramework::CPURegisters^, CameraStateChangingEventArgs^>(__after_CameraStateChanging)));
                __handler_Frame = gcnew NetScriptFramework::EventHook<FrameEventArgs^>(NetScriptFramework::EventHookFlags::None, "Frame", gcnew NetScriptFramework::EventHookParameters<FrameEventArgs^>(MCH::FromBase(0x1405B31FE), 5, 5, gcnew System::Func<NetScriptFramework::CPURegisters^, FrameEventArgs^>(__before_Frame), nullptr));
                __handler_InterruptCast = gcnew NetScriptFramework::EventHook<InterruptCastEventArgs^>(NetScriptFramework::EventHookFlags::None, "InterruptCast", gcnew NetScriptFramework::EventHookParameters<InterruptCastEventArgs^>(MCH::FromBase(0x14054CD70), 6, 6, gcnew System::Func<NetScriptFramework::CPURegisters^, InterruptCastEventArgs^>(__before_InterruptCast), nullptr));
                __handler_MagicCasterFire = gcnew NetScriptFramework::EventHook<MagicCasterFireEventArgs^>(NetScriptFramework::EventHookFlags::None, "MagicCasterFire", gcnew NetScriptFramework::EventHookParameters<MagicCasterFireEventArgs^>(MCH::FromBase(0x14054CC37), 6, 6, gcnew System::Func<NetScriptFramework::CPURegisters^, MagicCasterFireEventArgs^>(__before_MagicCasterFire), nullptr));
                __handler_MainMenu = gcnew NetScriptFramework::EventHook<MainMenuEventArgs^>(NetScriptFramework::EventHookFlags::None, "MainMenu", gcnew NetScriptFramework::EventHookParameters<MainMenuEventArgs^>(MCH::FromBase(0x1408A7649), 5, 5, gcnew System::Func<NetScriptFramework::CPURegisters^, MainMenuEventArgs^>(__before_MainMenu_1), nullptr), gcnew NetScriptFramework::EventHookParameters<MainMenuEventArgs^>(MCH::FromBase(0x1408A14E0), 5, 5, gcnew System::Func<NetScriptFramework::CPURegisters^, MainMenuEventArgs^>(__before_MainMenu_2), nullptr));
                __handler_ReduceHUDAmmoCounter = gcnew NetScriptFramework::EventHook<ReduceHUDAmmoCounterEventArgs^>(NetScriptFramework::EventHookFlags::AlwaysRun, "ReduceHUDAmmoCounter", gcnew NetScriptFramework::EventHookParameters<ReduceHUDAmmoCounterEventArgs^>(MCH::FromBase(0x14074B99A), 7, -5, gcnew System::Func<NetScriptFramework::CPURegisters^, ReduceHUDAmmoCounterEventArgs^>(__before_ReduceHUDAmmoCounter), gcnew System::Action<NetScriptFramework::CPURegisters^, ReduceHUDAmmoCounterEventArgs^>(__after_ReduceHUDAmmoCounter)));
                __handler_RemoveMagicEffectsWithArchetype = gcnew NetScriptFramework::EventHook<RemoveMagicEffectsWithArchetypeEventArgs^>(NetScriptFramework::EventHookFlags::None, "RemoveMagicEffectsWithArchetype", gcnew NetScriptFramework::EventHookParameters<RemoveMagicEffectsWithArchetypeEventArgs^>(MCH::FromBase(0x140634D9B), 5, 5, gcnew System::Func<NetScriptFramework::CPURegisters^, RemoveMagicEffectsWithArchetypeEventArgs^>(__before_RemoveMagicEffectsWithArchetype_1), gcnew System::Action<NetScriptFramework::CPURegisters^, RemoveMagicEffectsWithArchetypeEventArgs^>(__after_RemoveMagicEffectsWithArchetype_1)), gcnew NetScriptFramework::EventHookParameters<RemoveMagicEffectsWithArchetypeEventArgs^>(MCH::FromBase(0x140634DBF), 5, 5, gcnew System::Func<NetScriptFramework::CPURegisters^, RemoveMagicEffectsWithArchetypeEventArgs^>(__before_RemoveMagicEffectsWithArchetype_2), gcnew System::Action<NetScriptFramework::CPURegisters^, RemoveMagicEffectsWithArchetypeEventArgs^>(__after_RemoveMagicEffectsWithArchetype_2)), gcnew NetScriptFramework::EventHookParameters<RemoveMagicEffectsWithArchetypeEventArgs^>(MCH::FromBase(0x140628849), 5, 5, gcnew System::Func<NetScriptFramework::CPURegisters^, RemoveMagicEffectsWithArchetypeEventArgs^>(__before_RemoveMagicEffectsWithArchetype_3), gcnew System::Action<NetScriptFramework::CPURegisters^, RemoveMagicEffectsWithArchetypeEventArgs^>(__after_RemoveMagicEffectsWithArchetype_3)));
                __handler_ShadowCullingBegin = gcnew NetScriptFramework::EventHook<ShadowCullingBeginEventArgs^>(NetScriptFramework::EventHookFlags::AlwaysRun, "ShadowCullingBegin", gcnew NetScriptFramework::EventHookParameters<ShadowCullingBeginEventArgs^>(MCH::FromBase(0x1412F9CFC), 5, 0, gcnew System::Func<NetScriptFramework::CPURegisters^, ShadowCullingBeginEventArgs^>(__before_ShadowCullingBegin), gcnew System::Action<NetScriptFramework::CPURegisters^, ShadowCullingBeginEventArgs^>(__after_ShadowCullingBegin)));
                __handler_ShadowCullingEnd = gcnew NetScriptFramework::EventHook<ShadowCullingEndEventArgs^>(NetScriptFramework::EventHookFlags::AlwaysRun, "ShadowCullingEnd", gcnew NetScriptFramework::EventHookParameters<ShadowCullingEndEventArgs^>(MCH::FromBase(0x1412F9D01), 18, 0, gcnew System::Func<NetScriptFramework::CPURegisters^, ShadowCullingEndEventArgs^>(__before_ShadowCullingEnd), gcnew System::Action<NetScriptFramework::CPURegisters^, ShadowCullingEndEventArgs^>(__after_ShadowCullingEnd)));
                __handler_SpendAmmo = gcnew NetScriptFramework::EventHook<SpendAmmoEventArgs^>(NetScriptFramework::EventHookFlags::None, "SpendAmmo", gcnew NetScriptFramework::EventHookParameters<SpendAmmoEventArgs^>(MCH::FromBase(0x140624AD4), 5, -5, gcnew System::Func<NetScriptFramework::CPURegisters^, SpendAmmoEventArgs^>(__before_SpendAmmo), gcnew System::Action<NetScriptFramework::CPURegisters^, SpendAmmoEventArgs^>(__after_SpendAmmo)));
                __handler_SpendMagicCost = gcnew NetScriptFramework::EventHook<SpendMagicCostEventArgs^>(NetScriptFramework::EventHookFlags::None, "SpendMagicCost", gcnew NetScriptFramework::EventHookParameters<SpendMagicCostEventArgs^>(MCH::FromBase(0x140542306), 6, 6, gcnew System::Func<NetScriptFramework::CPURegisters^, SpendMagicCostEventArgs^>(__before_SpendMagicCost_1), gcnew System::Action<NetScriptFramework::CPURegisters^, SpendMagicCostEventArgs^>(__after_SpendMagicCost_1)));
                __handler_SpendPoison = gcnew NetScriptFramework::EventHook<SpendPoisonEventArgs^>(NetScriptFramework::EventHookFlags::None, "SpendPoison", gcnew NetScriptFramework::EventHookParameters<SpendPoisonEventArgs^>(MCH::FromBase(0x140631418), 5, 5, gcnew System::Func<NetScriptFramework::CPURegisters^, SpendPoisonEventArgs^>(__before_SpendPoison), gcnew System::Action<NetScriptFramework::CPURegisters^, SpendPoisonEventArgs^>(__after_SpendPoison)), gcnew NetScriptFramework::EventHookParameters<SpendPoisonEventArgs^>(MCH::FromBase(0x140722409), 5, 5, gcnew System::Func<NetScriptFramework::CPURegisters^, SpendPoisonEventArgs^>(__before_SpendPoison_2), gcnew System::Action<NetScriptFramework::CPURegisters^, SpendPoisonEventArgs^>(__after_SpendPoison_2)));
                __handler_UpdateCamera = gcnew NetScriptFramework::EventHook<UpdateCameraEventArgs^>(NetScriptFramework::EventHookFlags::None, "UpdateCamera", gcnew NetScriptFramework::EventHookParameters<UpdateCameraEventArgs^>(MCH::FromBase(0x1404F5D9A), 5, 5, gcnew System::Func<NetScriptFramework::CPURegisters^, UpdateCameraEventArgs^>(__before_UpdateCamera), nullptr));
                __handler_UpdatedPlayerHeadtrack = gcnew NetScriptFramework::EventHook<UpdatedPlayerHeadtrackEventArgs^>(NetScriptFramework::EventHookFlags::None, "UpdatedPlayerHeadtrack", gcnew NetScriptFramework::EventHookParameters<UpdatedPlayerHeadtrackEventArgs^>(MCH::FromBase(0x14069F396), 8, 8, gcnew System::Func<NetScriptFramework::CPURegisters^, UpdatedPlayerHeadtrackEventArgs^>(__before_UpdatedPlayerHeadtrack), nullptr));
                __handler_UpdatePlayerControls = gcnew NetScriptFramework::EventHook<UpdatePlayerControlsEventArgs^>(NetScriptFramework::EventHookFlags::AlwaysRun, "UpdatePlayerControls", gcnew NetScriptFramework::EventHookParameters<UpdatePlayerControlsEventArgs^>(MCH::FromBase(0x140705058), 6, 0, gcnew System::Func<NetScriptFramework::CPURegisters^, UpdatePlayerControlsEventArgs^>(__before_UpdatePlayerControls), gcnew System::Action<NetScriptFramework::CPURegisters^, UpdatePlayerControlsEventArgs^>(__after_UpdatePlayerControls)));
                __handler_UpdatePlayerTurnToCamera = gcnew NetScriptFramework::EventHook<UpdatePlayerTurnToCameraEventArgs^>(NetScriptFramework::EventHookFlags::None, "UpdatePlayerTurnToCamera", gcnew NetScriptFramework::EventHookParameters<UpdatePlayerTurnToCameraEventArgs^>(MCH::FromBase(0x14084FCA3), 7, 7, gcnew System::Func<NetScriptFramework::CPURegisters^, UpdatePlayerTurnToCameraEventArgs^>(__before_UpdatePlayerTurnToCamera), gcnew System::Action<NetScriptFramework::CPURegisters^, UpdatePlayerTurnToCameraEventArgs^>(__after_UpdatePlayerTurnToCamera)));
                __handler_WeaponFireProjectilePosition = gcnew NetScriptFramework::EventHook<WeaponFireProjectilePositionEventArgs^>(NetScriptFramework::EventHookFlags::None, "WeaponFireProjectilePosition", gcnew NetScriptFramework::EventHookParameters<WeaponFireProjectilePositionEventArgs^>(MCH::FromBase(0x1402356D9), 7, 7, gcnew System::Func<NetScriptFramework::CPURegisters^, WeaponFireProjectilePositionEventArgs^>(__before_WeaponFireProjectilePosition), gcnew System::Action<NetScriptFramework::CPURegisters^, WeaponFireProjectilePositionEventArgs^>(__after_WeaponFireProjectilePosition)));
            }
        };
    }
}

#pragma warning(pop)
