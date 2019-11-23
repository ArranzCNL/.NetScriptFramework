#include "Game.h"
#include "GameAddresses.h"
#include "Globals.h"
#include "Events.h"
#include "Implementations.h"

namespace NetScriptFramework
{
    namespace SkyrimSE
    {
        System::String^ Debug_TESObjectREFR_BaseForm(IVirtualObject^ obj)
        {
            TESObjectREFR^ a = safe_cast<TESObjectREFR^>(obj);
            auto bf = a->BaseForm;
            if(bf == nullptr) return "NULL";
            return bf->ToString();
        }
        
        void _Initialize_KeywordCache(MainMenuEventArgs^ e)
        {
            KeywordCache::Initialize();
        }
        
        int _Sort_Modlist(TESFile^ a, TESFile^ b)
        {
            bool aesl = (a->RecordFlags & TESFileRecordFlags::ESL) != TESFileRecordFlags::None;
            bool besl = (b->RecordFlags & TESFileRecordFlags::ESL) != TESFileRecordFlags::None;
            if(aesl != besl) return aesl.CompareTo(besl);
            return a->Index.CompareTo(b->Index);
        }
        
        void _CrashLog_WriteModList(CrashLogEventArgs^ e)
        {
            if(e->Skip) return;
            DataHandler^ data = DataHandler::Instance;
            if(data == nullptr) return;
            auto mods2 = data->LoadedMods;
            if(mods2 == nullptr) return;
            auto mods = gcnew System::Collections::Generic::List<TESFile^>(256);
            for each(TESFile^ m in mods2) mods->Add(m);
            mods->Sort(gcnew System::Comparison<TESFile^>(_Sort_Modlist));
            e->Output->AppendLine();
            e->Output->AppendLine("Game plugins (" + mods->Count + ")");
            e->Output->AppendLine("{");
            for each(TESFile^ mod in mods)
            {
                auto name = mod->Name;
                if(name == nullptr) name = "(null)";
                if((mod->RecordFlags & TESFileRecordFlags::ESL) == TESFileRecordFlags::None)
                    e->Output->AppendLine("  [" + mod->Index.ToString("X2") + "] " + name);
                else
                    e->Output->AppendLine("  [FE " + mod->Index.ToString("X3") + "] " + name);
            }
            e->Output->AppendLine("}");
        }
        
        void SkyrimGame::Initialize()
        {
            // Perform base class initialization.
            Game::Initialize();
            
            // Register types.
            auto modules = System::Diagnostics::Process::GetCurrentProcess()->Modules;
            System::IntPtr modulePtr = System::IntPtr::Zero;
            for (System::Int32 i = 0; i < modules->Count; i++)
            {
                if (modules[i]->ModuleName == this->ExecutableName)
                {
                    modulePtr = modules[i]->BaseAddress;
                    break;
                }
            }
            RegisterType(modulePtr, "ActiveEffect", ActiveEffect::typeid, impl_ActiveEffect::typeid, 144, gcnew array<System::UInt32> { GameAddress::ActiveEffect });
            RegisterType(modulePtr, "BaseFormComponent", BaseFormComponent::typeid, impl_BaseFormComponent::typeid, 8, gcnew array<System::UInt32> { GameAddress::BaseFormComponent });
            RegisterType(modulePtr, "TESForm", TESForm::typeid, impl_TESForm::typeid, 32, gcnew array<System::UInt32> { GameAddress::TESForm }, gcnew NetScriptFramework::Tools::_Internal::TypeDebugWriter("", nullptr));
            RegisterType(modulePtr, "NiRefObject", NiRefObject::typeid, impl_NiRefObject::typeid, 16, gcnew array<System::UInt32> { GameAddress::NiRefObject });
            RegisterType(modulePtr, "BSHandleRefObject", BSHandleRefObject::typeid, impl_BSHandleRefObject::typeid, 16, gcnew array<System::UInt32> { GameAddress::BSHandleRefObject });
            RegisterType(modulePtr, "BSTEventSink<>", BSTEventSink<System::Object^>::typeid->GetGenericTypeDefinition(), impl_BSTEventSink<System::Object^>::typeid->GetGenericTypeDefinition(), 8, 
				gcnew array<System::UInt32>	{
					GameAddress::BSTEventSink_UArchiveStreamOpenedEvent_BSResource,
					GameAddress::BSTEventSink_UPositionPlayerEvent,
					GameAddress::BSTEventSink_VBSSystemEvent,
					GameAddress::BSTEventSink_UArchiveRegisteredEvent_BSResource,
					GameAddress::BSTEventSink_UClearArchiveRegistryEvent_BSResource,
					GameAddress::BSTEventSink_UBGSAnimSoundEvent,
					GameAddress::BSTEventSink_UTESCellReadyToApplyDecalsEvent,
					GameAddress::BSTEventSink_UBSAnimationGraphEvent,
					GameAddress::BSTEventSink_VMenuOpenCloseEvent,
					GameAddress::BSTEventSink_UTESSpellCastEvent,
					GameAddress::BSTEventSink_UCellAttachDetachEvent,
					GameAddress::BSTEventSink_UBGSActorCellEvent,
					GameAddress::BSTEventSink_UTESQuestStageItemDoneEvent,
					GameAddress::BSTEventSink_UNameFoundEvent_BSResource,
					GameAddress::BSTEventSink_UBSGamerProfileEvent,
					GameAddress::BSTEventSink_UBGSSaveLoadManagerEvent,
					GameAddress::BSTEventSink_UActorInventoryEvent,
					GameAddress::BSTEventSink_UBGSActorDeathEvent,
					GameAddress::BSTEventSink_VMenuModeChangeEvent,
					GameAddress::BSTEventSink_UEvent_DefaultObjectsReadyEvent,
					GameAddress::BSTEventSink_VBSSaveDataEvent,
					GameAddress::BSTEventSink_UNameChangedEvent_RaceSexMenuEvent,
					GameAddress::BSTEventSink_UTESDataHandlerPostBuildFileListEvent,
					GameAddress::BSTEventSink_PEAVInputEvent,
					GameAddress::BSTEventSink_UBeamProjectileImpactEvent,
					GameAddress::BSTEventSink_UTESOpenCloseEvent,
					GameAddress::BSTEventSink_UTESSleepStartEvent,
					GameAddress::BSTEventSink_UTESSleepStopEvent,
					GameAddress::BSTEventSink_UBGSFootstepEvent,
					GameAddress::BSTEventSink_UBGSCombatImpactEvent,
					GameAddress::BSTEventSink_UBGSCollisionSoundEvent,
					GameAddress::BSTEventSink_UTESWaitStartEvent,
					GameAddress::BSTEventSink_UTESWaitStopEvent,
					GameAddress::BSTEventSink_UItemHarvested_TESHarvestEvent,
					GameAddress::BSTEventSink_UEvent_ActorKill,
					GameAddress::BSTEventSink_UEvent_ActorItemEquipped,
					GameAddress::BSTEventSink_UEvent_Pickpocket,
					GameAddress::BSTEventSink_UEvent_BooksRead,
					GameAddress::BSTEventSink_UEvent_LevelIncrease,
					GameAddress::BSTEventSink_UEvent_SkillIncrease,
					GameAddress::BSTEventSink_UEvent_WordLearned,
					GameAddress::BSTEventSink_UEvent_WordUnlocked,
					GameAddress::BSTEventSink_UEvent_Inventory,
					GameAddress::BSTEventSink_UEvent_Bounty,
					GameAddress::BSTEventSink_UEvent_QuestStatus,
					GameAddress::BSTEventSink_UEvent_ObjectiveState,
					GameAddress::BSTEventSink_UEvent_Trespass,
					GameAddress::BSTEventSink_UEvent_FinePaid,
					GameAddress::BSTEventSink_UEvent_HoursPassed,
					GameAddress::BSTEventSink_UEvent_DaysPassed,
					GameAddress::BSTEventSink_UEvent_DaysJailed,
					GameAddress::BSTEventSink_UEvent_CriticalHitEvent,
					GameAddress::BSTEventSink_UEvent_DisarmedEvent,
					GameAddress::BSTEventSink_UEvent_ItemsPickpocketed,
					GameAddress::BSTEventSink_UEvent_ItemSteal,
					GameAddress::BSTEventSink_UEvent_ItemCrafted,
					GameAddress::BSTEventSink_UEvent_LocationDiscovery,
					GameAddress::BSTEventSink_UEvent_Jailing,
					GameAddress::BSTEventSink_UEvent_ChestsLooted,
					GameAddress::BSTEventSink_UEvent_TimesTrained,
					GameAddress::BSTEventSink_UEvent_TimesBartered,
					GameAddress::BSTEventSink_UEvent_ContractedDisease,
					GameAddress::BSTEventSink_UEvent_SpellsLearned,
					GameAddress::BSTEventSink_UEvent_DragonSoulGained,
					GameAddress::BSTEventSink_UEvent_SoulGemsUsed,
					GameAddress::BSTEventSink_UEvent_SoulsTrapped,
					GameAddress::BSTEventSink_UEvent_PoisonedWeapon,
					GameAddress::BSTEventSink_UEvent_ShoutAttack,
					GameAddress::BSTEventSink_UEvent_JailEscape,
					GameAddress::BSTEventSink_UEvent_GrandTheftHorse,
					GameAddress::BSTEventSink_UEvent_AssaultCrime,
					GameAddress::BSTEventSink_UEvent_MurderCrime,
					GameAddress::BSTEventSink_UEvent_LocksPicked,
					GameAddress::BSTEventSink_UEvent_LocationCleared,
					GameAddress::BSTEventSink_UEvent_ShoutMastered,
					GameAddress::BSTEventSink_VBSTransformDeltaEvent,
					GameAddress::BSTEventSink_VbhkCharacterMoveFinishEvent,
					GameAddress::BSTEventSink_UBGSEventProcessedEvent,
					GameAddress::BSTEventSink_VUserEventEnabledEvent,
					GameAddress::BSTEventSink_UTESTrackedStatsEvent,
					GameAddress::BSTEventSink_UTESFurnitureEvent,
					GameAddress::BSTEventSink_VBSProceduralGeomEvent,
					GameAddress::BSTEventSink_UBSRemoteGamepadEvent,
					GameAddress::BSTEventSink_UEvent_WeaponAttack,
					GameAddress::BSTEventSink_UEvent_SpellAttack,
					GameAddress::BSTEventSink_UBSPathEvent,
					GameAddress::BSTEventSink_UTESQuestStartStopEvent,
					GameAddress::BSTEventSink_UTESActivateEvent,
					GameAddress::BSTEventSink_UTESActiveEffectApplyRemoveEvent,
					GameAddress::BSTEventSink_UTESActorLocationChangeEvent,
					GameAddress::BSTEventSink_UTESBookReadEvent,
					GameAddress::BSTEventSink_UTESCellAttachDetachEvent,
					GameAddress::BSTEventSink_UTESCellFullyLoadedEvent,
					GameAddress::BSTEventSink_UTESCombatEvent,
					GameAddress::BSTEventSink_UTESContainerChangedEvent,
					GameAddress::BSTEventSink_UTESDeathEvent,
					GameAddress::BSTEventSink_UTESDestructionStageChangedEvent,
					GameAddress::BSTEventSink_UTESEnterBleedoutEvent,
					GameAddress::BSTEventSink_UTESEquipEvent,
					GameAddress::BSTEventSink_UTESFormDeleteEvent,
					GameAddress::BSTEventSink_UTESGrabReleaseEvent,
					GameAddress::BSTEventSink_UTESHitEvent,
					GameAddress::BSTEventSink_UTESInitScriptEvent,
					GameAddress::BSTEventSink_UTESLoadGameEvent,
					GameAddress::BSTEventSink_UTESLockChangedEvent,
					GameAddress::BSTEventSink_UTESMagicEffectApplyEvent,
					GameAddress::BSTEventSink_UTESMagicWardHitEvent,
					GameAddress::BSTEventSink_UTESMoveAttachDetachEvent,
					GameAddress::BSTEventSink_UTESObjectLoadedEvent,
					GameAddress::BSTEventSink_UTESObjectREFRTranslationEvent,
					GameAddress::BSTEventSink_UTESPackageEvent,
					GameAddress::BSTEventSink_UTESPerkEntryRunEvent,
					GameAddress::BSTEventSink_UTESQuestInitEvent,
					GameAddress::BSTEventSink_UTESQuestStageEvent,
					GameAddress::BSTEventSink_UTESResetEvent,
					GameAddress::BSTEventSink_UTESResolveNPCTemplatesEvent,
					GameAddress::BSTEventSink_UTESSceneEvent,
					GameAddress::BSTEventSink_UTESSceneActionEvent,
					GameAddress::BSTEventSink_UTESScenePhaseEvent,
					GameAddress::BSTEventSink_UTESSellEvent,
					GameAddress::BSTEventSink_UTESTopicInfoEvent,
					GameAddress::BSTEventSink_UTESTrapHitEvent,
					GameAddress::BSTEventSink_UTESTriggerEvent,
					GameAddress::BSTEventSink_UTESTriggerEnterEvent,
					GameAddress::BSTEventSink_UTESTriggerLeaveEvent,
					GameAddress::BSTEventSink_UTESUniqueIDChangeEvent,
					GameAddress::BSTEventSink_UTESSwitchRaceCompleteEvent,
					GameAddress::BSTEventSink_UTESPlayerBowShotEvent,
					GameAddress::BSTEventSink_UTESFastTravelEndEvent,
					GameAddress::BSTEventSink_UStatsEvent_BSScript,
					GameAddress::BSTEventSink_UDeviceConnected_SpeechRecognitionEvents,
					GameAddress::BSTEventSink_UDeviceReady_SpeechRecognitionEvents,
					GameAddress::BSTEventSink_interference_SpeechRecognitionEvents,
					GameAddress::BSTEventSink_URecognition_SpeechRecognitionEvents,
					GameAddress::BSTEventSink_UThreadEvent_BSThreadEvent,
					GameAddress::BSTEventSink_UBSMusicEvent,
					GameAddress::BSTEventSink_UBSGamepadEvent });

            RegisterType(modulePtr, "BSAnimationGraphEvent", BSAnimationGraphEvent::typeid, impl_BSAnimationGraphEvent::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "IAnimationGraphManagerHolder", IAnimationGraphManagerHolder::typeid, impl_IAnimationGraphManagerHolder::typeid, 8, gcnew array<System::UInt32> { GameAddress::IAnimationGraphManagerHolder });
            RegisterType(modulePtr, "TESObjectREFR", TESObjectREFR::typeid, impl_TESObjectREFR::typeid, 152, gcnew array<System::UInt32> { GameAddress::TESObjectREFR }, gcnew NetScriptFramework::Tools::_Internal::TypeDebugWriter("BaseForm", gcnew System::Func<IVirtualObject^, System::String^>(Debug_TESObjectREFR_BaseForm)));
            RegisterType(modulePtr, "MagicTarget", MagicTarget::typeid, impl_MagicTarget::typeid, 24, gcnew array<System::UInt32> { GameAddress::MagicTarget });
            RegisterType(modulePtr, "ActorValueOwner", ActorValueOwner::typeid, impl_ActorValueOwner::typeid, 8, gcnew array<System::UInt32> { GameAddress::ActorValueOwner });
            RegisterType(modulePtr, "IMovementInterface", IMovementInterface::typeid, impl_IMovementInterface::typeid, 8, gcnew array<System::UInt32> { GameAddress::IMovementInterface });
            RegisterType(modulePtr, "IMovementState", IMovementState::typeid, impl_IMovementState::typeid, 8, gcnew array<System::UInt32> { GameAddress::IMovementState });
            RegisterType(modulePtr, "ActorState", ActorState::typeid, impl_ActorState::typeid, 16, gcnew array<System::UInt32> { GameAddress::ActorState });
            RegisterType(modulePtr, "BSTransformDeltaEvent", BSTransformDeltaEvent::typeid, impl_BSTransformDeltaEvent::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "bhkCharacterMoveFinishEvent", bhkCharacterMoveFinishEvent::typeid, impl_bhkCharacterMoveFinishEvent::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "IPostAnimationChannelUpdateFunctor", IPostAnimationChannelUpdateFunctor::typeid, impl_IPostAnimationChannelUpdateFunctor::typeid, 8, gcnew array<System::UInt32> { GameAddress::IPostAnimationChannelUpdateFunctor });
            RegisterType(modulePtr, "Actor", Actor::typeid, impl_Actor::typeid, 688, gcnew array<System::UInt32> { GameAddress::Actor });
            RegisterType(modulePtr, "BSFixedString", BSFixedString::typeid, impl_BSFixedString::typeid, 8, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "BSScript", BSScript::typeid, impl_BSScript::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "BSScript::NF_util", BSScript::NF_util::typeid, impl_BSScript::impl_NF_util::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "BSScript::NF_util::NativeFunctionBase", BSScript::NF_util::NativeFunctionBase::typeid, impl_BSScript::impl_NF_util::impl_NativeFunctionBase::typeid, 80, gcnew array<System::UInt32> { GameAddress::BSScript__NF_util__NativeFunctionBase });
            RegisterType(modulePtr, "BSScript::IFunction", BSScript::IFunction::typeid, impl_BSScript::impl_IFunction::typeid, 16, gcnew array<System::UInt32> { GameAddress::BSScript__IFunction });
            RegisterType(modulePtr, "BSIntrusiveRefCounted", BSIntrusiveRefCounted::typeid, impl_BSIntrusiveRefCounted::typeid, 16, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "BSTArrayBase", BSTArrayBase::typeid, impl_BSTArrayBase::typeid, 24, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "BSTArrayBase::IAllocatorFunctor", BSTArrayBase::IAllocatorFunctor::typeid, impl_BSTArrayBase::impl_IAllocatorFunctor::typeid, -1, gcnew array<System::UInt32> { GameAddress::BSTArrayBase__IAllocatorFunctor });
            RegisterType(modulePtr, "GameFunction", GameFunction::typeid, impl_GameFunction::typeid, 72, nullptr);
            RegisterType(modulePtr, "ListNode<>", ListNode<System::Object^>::typeid->GetGenericTypeDefinition(), impl_ListNode<System::Object^>::typeid->GetGenericTypeDefinition(), 16, nullptr);
            RegisterType(modulePtr, "NiObject", NiObject::typeid, impl_NiObject::typeid, 16, gcnew array<System::UInt32> { GameAddress::NiObject });
            RegisterType(modulePtr, "NiObjectNET", NiObjectNET::typeid, impl_NiObjectNET::typeid, 48, gcnew array<System::UInt32> { GameAddress::NiObjectNET }, gcnew NetScriptFramework::Tools::_Internal::TypeDebugWriter("", nullptr));
            RegisterType(modulePtr, "NiAVObject", NiAVObject::typeid, impl_NiAVObject::typeid, 272, gcnew array<System::UInt32> { GameAddress::NiAVObject });
            RegisterType(modulePtr, "NiNode", NiNode::typeid, impl_NiNode::typeid, 296, gcnew array<System::UInt32> { GameAddress::NiNode });
            RegisterType(modulePtr, "NiTObjectArray<>", NiTObjectArray<System::Object^>::typeid->GetGenericTypeDefinition(), impl_NiTObjectArray<System::Object^>::typeid->GetGenericTypeDefinition(), 24, 
				gcnew array<System::UInt32> { 
					GameAddress::NiTObjectArray_VNiPointer_VbhkRigidBody,
					GameAddress::NiTObjectArray_VNiPointer_VNiNode,
					GameAddress::NiTObjectArray_VNiPointer_VNiAVObject,
					GameAddress::NiTObjectArray_VNiPointer_VNiControllerSequence,
					GameAddress::NiTObjectArray_VNiPointer_VNiTransformController,
					GameAddress::NiTObjectArray_VNiPointer_VBSTriShape,
					GameAddress::NiTObjectArray_VNiPointer_VNiGeometry,
					GameAddress::NiTObjectArray_VNiPointer_VNiTexture });

            RegisterType(modulePtr, "NiPoint3", NiPoint3::typeid, impl_NiPoint3::typeid, 12, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "NiPointer<>", NiPointer<NiRefObject^>::typeid->GetGenericTypeDefinition(), impl_NiPointer<NiRefObject^>::typeid->GetGenericTypeDefinition(), 8, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "NiTArray<,>", NiTArray<System::Object^, System::Object^>::typeid->GetGenericTypeDefinition(), impl_NiTArray<System::Object^, System::Object^>::typeid->GetGenericTypeDefinition(), 24, 
				gcnew array<System::UInt32> { 
					GameAddress::NiTArray_PEAVTESObjectCELL__VNiTMallocInterface_PEAVTESObjectCELL,
					GameAddress::NiTArray_PEAVBGSAddonNode__VNiTMallocInterface_PEAVBGSAddonNode,
					GameAddress::NiTArray_PEAUBSAnimNoteReceiverType_BSAnimNoteReceiver__VNiTMallocInterface_PEAUBSAnimNoteReceiverType_BSAnimNoteReceiver,
					GameAddress::NiTArray_PEAVBGSCameraPath__VNiTMallocInterface_PEAVBGSCameraPath,
					GameAddress::NiTArray_VNiPointer_VbhkRigidBody____VNiTNewInterface_VNiPointer_VbhkRigidBody,
					GameAddress::NiTArray_PEAVNiAVObject__VNiTMallocInterface_PEAVNiAVObject,
					GameAddress::NiTArray_VNiPointer_VNiNode____VNiTNewInterface_VNiPointer_VNiNode,
					GameAddress::NiTArray_PEAVCombatGroup__VNiTMallocInterface_PEAVCombatGroup,
					GameAddress::NiTArray_VNiPointer_VNiAVObject____VNiTNewInterface_VNiPointer_VNiAVObject,
					GameAddress::NiTArray_P6AXAEAVNiStream__PEAVNiObject___ZVNiTMallocInterface_P6AXAEAVNiStream__PEAVNiObject___Z,
					GameAddress::NiTArray_GVNiTMallocInterface_G,
					GameAddress::NiTArray_VNiPointer_VNiRefObject____VNiTNewInterface_VNiPointer_VNiRefObject,
					GameAddress::NiTArray_IVNiTMallocInterface_I,
					GameAddress::NiTArray_VNiPointer_VNiMetricsOutputModule____VNiTNewInterface_VNiPointer_VNiMetricsOutputModule,
					GameAddress::NiTArray_PEADVNiTMallocInterface_PEAD,
					GameAddress::NiTArray_PEAVRecord_NiPick__VNiTScrapHeapInterface_PEAVRecord_NiPick,
					GameAddress::NiTArray_PEAVNiBoundingVolume__VNiTMallocInterface_PEAVNiBoundingVolume,
					GameAddress::NiTArray_VNiPointer_VNiControllerSequence____VNiTNewInterface_VNiPointer_VNiControllerSequence,
					GameAddress::NiTArray_PEAUBSAnimReceiverType_BSAnimNoteListener__VNiTMallocInterface_PEAUBSAnimReceiverType_BSAnimNoteListener,
					GameAddress::NiTArray_VNiPointer_VNiTransformController____VNiTNewInterface_VNiPointer_VNiTransformController,
					GameAddress::NiTArray_PEAVNiTObjectArray_VNiPointer_VNiAVObject______VNiTMallocInterface_PEAVNiTObjectArray_VNiPointer_VNiAVObject,
					GameAddress::NiTArray_VNiPointer_VBSTriShape____VNiTNewInterface_VNiPointer_VBSTriShape,
					GameAddress::NiTArray_VNiPointer_VNiGeometry____VNiTNewInterface_VNiPointer_VNiGeometry,
					GameAddress::NiTArray_VNiPointer_VNiAVObject____VNiTMallocInterface_VNiPointer_VNiAVObject,
					GameAddress::NiTArray_PEAVNiTPrimitiveSet_PEAVNiNode____VNiTMallocInterface_PEAVNiTPrimitiveSet_PEAVNiNode,
					GameAddress::NiTArray_PEAVImageSpaceEffect__VNiTMallocInterface_PEAVImageSpaceEffect,
					GameAddress::NiTArray_VNiPointer_VNiTexture____VNiTNewInterface_VNiPointer_VNiTexture,
					GameAddress::NiTArray_W4TextureFilterMode_BSGraphics__VNiTMallocInterface_W4TextureFilterMode_BSGraphics,
					GameAddress::NiTArray_NVNiTMallocInterface_N,
					GameAddress::NiTArray_PEAVImageSpaceEffectParam__VNiTMallocInterface_PEAVImageSpaceEffectParam,
					GameAddress::NiTArray_PEAVImageSpaceTexture__VNiTMallocInterface_PEAVImageSpaceTexture,
					GameAddress::NiTArray_PEAVEffectInput_ImageSpaceEffect__VNiTMallocInterface_PEAVEffectInput_ImageSpaceEffect,
					GameAddress::NiTArray_HVNiTMallocInterface_H });

            RegisterType(modulePtr, "TESFullName", TESFullName::typeid, impl_TESFullName::typeid, 16, gcnew array<System::UInt32> { GameAddress::TESFullName });
            RegisterType(modulePtr, "BSExtraDataList", BSExtraDataList::typeid, impl_BSExtraDataList::typeid, 24, nullptr);
            RegisterType(modulePtr, "TESObjectCELL", TESObjectCELL::typeid, impl_TESObjectCELL::typeid, 320, gcnew array<System::UInt32> { GameAddress::TESObjectCELL });
            RegisterType(modulePtr, "TESModel", TESModel::typeid, impl_TESModel::typeid, 40, gcnew array<System::UInt32> { GameAddress::TESModel });
            RegisterType(modulePtr, "TESWorldSpace", TESWorldSpace::typeid, impl_TESWorldSpace::typeid, 856, gcnew array<System::UInt32> { GameAddress::TESWorldSpace });
            RegisterType(modulePtr, "TESWeightForm", TESWeightForm::typeid, impl_TESWeightForm::typeid, 16, gcnew array<System::UInt32> { GameAddress::TESWeightForm });
            RegisterType(modulePtr, "NiTNewInterface<>", NiTNewInterface<System::Object^>::typeid->GetGenericTypeDefinition(), impl_NiTNewInterface<System::Object^>::typeid->GetGenericTypeDefinition(), -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "NiTransform", NiTransform::typeid, impl_NiTransform::typeid, 52, nullptr);
            RegisterType(modulePtr, "NiMatrix33", NiMatrix33::typeid, impl_NiMatrix33::typeid, 36, nullptr);
            RegisterType(modulePtr, "TESCameraState", TESCameraState::typeid, impl_TESCameraState::typeid, 32, gcnew array<System::UInt32> { GameAddress::TESCameraState });
            RegisterType(modulePtr, "TESCamera", TESCamera::typeid, impl_TESCamera::typeid, 56, gcnew array<System::UInt32> { GameAddress::TESCamera });
            RegisterType(modulePtr, "PlayerInputHandler", PlayerInputHandler::typeid, impl_PlayerInputHandler::typeid, 16, gcnew array<System::UInt32> { GameAddress::PlayerInputHandler });
            RegisterType(modulePtr, "FirstPersonState", FirstPersonState::typeid, impl_FirstPersonState::typeid, 144, gcnew array<System::UInt32> { GameAddress::FirstPersonState });
            RegisterType(modulePtr, "ThirdPersonState", ThirdPersonState::typeid, impl_ThirdPersonState::typeid, 232, gcnew array<System::UInt32> { GameAddress::ThirdPersonState });
            RegisterType(modulePtr, "Character", Character::typeid, impl_Character::typeid, 688, gcnew array<System::UInt32> { GameAddress::Character });
            RegisterType(modulePtr, "MenuOpenCloseEvent", MenuOpenCloseEvent::typeid, impl_MenuOpenCloseEvent::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "MenuModeChangeEvent", MenuModeChangeEvent::typeid, impl_MenuModeChangeEvent::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "UserEventEnabledEvent", UserEventEnabledEvent::typeid, impl_UserEventEnabledEvent::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "TESTrackedStatsEvent", TESTrackedStatsEvent::typeid, impl_TESTrackedStatsEvent::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "PlayerCharacter", PlayerCharacter::typeid, impl_PlayerCharacter::typeid, 3040, gcnew array<System::UInt32> { GameAddress::PlayerCharacter });
            RegisterType(modulePtr, "TESWeather", TESWeather::typeid, impl_TESWeather::typeid, 2264, gcnew array<System::UInt32> { GameAddress::TESWeather });
            RegisterType(modulePtr, "BGSMenuDisplayObject", BGSMenuDisplayObject::typeid, impl_BGSMenuDisplayObject::typeid, 16, gcnew array<System::UInt32> { GameAddress::BGSMenuDisplayObject });
            RegisterType(modulePtr, "BGSKeywordForm", BGSKeywordForm::typeid, impl_BGSKeywordForm::typeid, 24, gcnew array<System::UInt32> { GameAddress::BGSKeywordForm });
            RegisterType(modulePtr, "EffectSetting", EffectSetting::typeid, impl_EffectSetting::typeid, 408, gcnew array<System::UInt32> { GameAddress::EffectSetting });
            RegisterType(modulePtr, "BSTArray<>", BSTArray<System::Object^>::typeid->GetGenericTypeDefinition(), impl_BSTArray<System::Object^>::typeid->GetGenericTypeDefinition(), 24, nullptr);
            RegisterType(modulePtr, "BGSKeyword", BGSKeyword::typeid, impl_BGSKeyword::typeid, 40, gcnew array<System::UInt32> { GameAddress::BGSKeyword });
            RegisterType(modulePtr, "BSTArrayAllocatorFunctor<>", BSTArrayAllocatorFunctor<System::Object^>::typeid->GetGenericTypeDefinition(), impl_BSTArrayAllocatorFunctor<System::Object^>::typeid->GetGenericTypeDefinition(), -1, 
				gcnew array<System::UInt32> { 
					GameAddress::BSTArrayAllocatorFunctor_VBSTArrayHeapAllocator,
					GameAddress::BSTArrayAllocatorFunctor_VBSTSmallArrayHeapAllocator_0BA,
					GameAddress::BSTArrayAllocatorFunctor_VBSTSmallArrayHeapAllocator_0CKA,
					GameAddress::BSTArrayAllocatorFunctor_VBSScrapArrayAllocator,
					GameAddress::BSTArrayAllocatorFunctor_VBSTSmallArrayHeapAllocator_0EAA,
					GameAddress::BSTArrayAllocatorFunctor_VBSTSmallArrayHeapAllocator_0CA,
					GameAddress::BSTArrayAllocatorFunctor_VBSTSmallArrayHeapAllocator_07,
					GameAddress::BSTArrayAllocatorFunctor_VBSTSmallArrayHeapAllocator_03,
					GameAddress::BSTArrayAllocatorFunctor_VBSTSmallArrayHeapAllocator_0BI,
					GameAddress::BSTArrayAllocatorFunctor_VBSTSmallArrayHeapAllocator_0EA,
					GameAddress::BSTArrayAllocatorFunctor_VBSTSmallArrayHeapAllocator_0HA,
					GameAddress::BSTArrayAllocatorFunctor_VBSTSmallArrayHeapAllocator_0GM,
					GameAddress::BSTArrayAllocatorFunctor_VBSTSmallArrayHeapAllocator_0EI,
					GameAddress::BSTArrayAllocatorFunctor_VBSTSmallArrayHeapAllocator_0PA,
					GameAddress::BSTArrayAllocatorFunctor_VBSTSmallArrayHeapAllocator_0BAA,
					GameAddress::BSTArrayAllocatorFunctor_VBSTSmallArrayHeapAllocator_0DI,
					GameAddress::BSTArrayAllocatorFunctor_VBSTSmallArrayHeapAllocator_0DA,
					GameAddress::BSTArrayAllocatorFunctor_VBSTSmallArrayHeapAllocator_0CI,
					GameAddress::BSTArrayAllocatorFunctor_VBSTSmallArrayHeapAllocator_0KA,
					GameAddress::BSTArrayAllocatorFunctor_VBSTSmallArrayHeapAllocator_0ICA,
					GameAddress::BSTArrayAllocatorFunctor_VBSTSmallArrayHeapAllocator_0IAA,
					GameAddress::BSTArrayAllocatorFunctor_VBSTSmallArrayHeapAllocator_0GI,
					GameAddress::BSTArrayAllocatorFunctor_VBSTSmallArrayHeapAllocator_0M,
					GameAddress::BSTArrayAllocatorFunctor_VBSTSmallArrayHeapAllocator_0OA,
					GameAddress::BSTArrayAllocatorFunctor_VBSTSmallArrayHeapAllocator_0CE,
					GameAddress::BSTArrayAllocatorFunctor_VBSTSmallArrayHeapAllocator_0IA,
					GameAddress::BSTArrayAllocatorFunctor_VBSTSmallArrayHeapAllocator_0LA,
					GameAddress::BSTArrayAllocatorFunctor_VBSTSmallArrayHeapAllocator_0HI,
					GameAddress::BSTArrayAllocatorFunctor_VBSTSmallArrayHeapAllocator_0GA });

            RegisterType(modulePtr, "BSTArrayHeapAllocator", BSTArrayHeapAllocator::typeid, impl_BSTArrayHeapAllocator::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "NiCollisionObject", NiCollisionObject::typeid, impl_NiCollisionObject::typeid, 24, gcnew array<System::UInt32> { GameAddress::NiCollisionObject });
            RegisterType(modulePtr, "bhkRefObject", bhkRefObject::typeid, impl_bhkRefObject::typeid, 24, gcnew array<System::UInt32> { GameAddress::bhkRefObject });
            RegisterType(modulePtr, "bhkSerializable", bhkSerializable::typeid, impl_bhkSerializable::typeid, 32, gcnew array<System::UInt32> { GameAddress::bhkSerializable });
            RegisterType(modulePtr, "bhkWorldObject", bhkWorldObject::typeid, impl_bhkWorldObject::typeid, 40, gcnew array<System::UInt32> { GameAddress::bhkWorldObject });
            RegisterType(modulePtr, "bhkNiCollisionObject", bhkNiCollisionObject::typeid, impl_bhkNiCollisionObject::typeid, 40, gcnew array<System::UInt32> { GameAddress::bhkNiCollisionObject });
            RegisterType(modulePtr, "bhkEntity", bhkEntity::typeid, impl_bhkEntity::typeid, 40, gcnew array<System::UInt32> { GameAddress::bhkEntity });
            RegisterType(modulePtr, "bhkRigidBody", bhkRigidBody::typeid, impl_bhkRigidBody::typeid, 64, gcnew array<System::UInt32> { GameAddress::bhkRigidBody });
            RegisterType(modulePtr, "PlayerCamera", PlayerCamera::typeid, impl_PlayerCamera::typeid, 360, gcnew array<System::UInt32> { GameAddress::PlayerCamera });
            RegisterType(modulePtr, "PositionPlayerEvent", PositionPlayerEvent::typeid, impl_PositionPlayerEvent::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "BSGamerProfileEvent", BSGamerProfileEvent::typeid, impl_BSGamerProfileEvent::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "Main", Main::typeid, impl_Main::typeid, 624, gcnew array<System::UInt32> { GameAddress::Main });
            RegisterType(modulePtr, "TESDescription", TESDescription::typeid, impl_TESDescription::typeid, 16, gcnew array<System::UInt32> { GameAddress::TESDescription });
            RegisterType(modulePtr, "TESTexture", TESTexture::typeid, impl_TESTexture::typeid, 16, gcnew array<System::UInt32> { GameAddress::TESTexture });
            RegisterType(modulePtr, "TESIcon", TESIcon::typeid, impl_TESIcon::typeid, 16, gcnew array<System::UInt32> { GameAddress::TESIcon });
            RegisterType(modulePtr, "BGSPerk", BGSPerk::typeid, impl_BGSPerk::typeid, 128, gcnew array<System::UInt32> { GameAddress::BGSPerk });
            RegisterType(modulePtr, "BGSEquipType", BGSEquipType::typeid, impl_BGSEquipType::typeid, 16, gcnew array<System::UInt32> { GameAddress::BGSEquipType });
            RegisterType(modulePtr, "TESShout", TESShout::typeid, impl_TESShout::typeid, 168, gcnew array<System::UInt32> { GameAddress::TESShout });
            RegisterType(modulePtr, "TESWordOfPower", TESWordOfPower::typeid, impl_TESWordOfPower::typeid, 56, gcnew array<System::UInt32> { GameAddress::TESWordOfPower });
            RegisterType(modulePtr, "TESObject", TESObject::typeid, impl_TESObject::typeid, 32, gcnew array<System::UInt32> { GameAddress::TESObject });
            RegisterType(modulePtr, "TESBoundObject", TESBoundObject::typeid, impl_TESBoundObject::typeid, 48, gcnew array<System::UInt32> { GameAddress::TESBoundObject });
            RegisterType(modulePtr, "MagicItem", MagicItem::typeid, impl_MagicItem::typeid, 144, gcnew array<System::UInt32> { GameAddress::MagicItem });
            RegisterType(modulePtr, "SpellItem", SpellItem::typeid, impl_SpellItem::typeid, 232, gcnew array<System::UInt32> { GameAddress::SpellItem });
            RegisterType(modulePtr, "TESSpellList", TESSpellList::typeid, impl_TESSpellList::typeid, 16, gcnew array<System::UInt32> { GameAddress::TESSpellList });
            RegisterType(modulePtr, "BGSSkinForm", BGSSkinForm::typeid, impl_BGSSkinForm::typeid, 16, gcnew array<System::UInt32> { GameAddress::BGSSkinForm });
            RegisterType(modulePtr, "BGSBipedObjectForm", BGSBipedObjectForm::typeid, impl_BGSBipedObjectForm::typeid, 16, gcnew array<System::UInt32> { GameAddress::BGSBipedObjectForm });
            RegisterType(modulePtr, "BGSAttackDataForm", BGSAttackDataForm::typeid, impl_BGSAttackDataForm::typeid, 16, gcnew array<System::UInt32> { GameAddress::BGSAttackDataForm });
            RegisterType(modulePtr, "TESRace", TESRace::typeid, impl_TESRace::typeid, 1208, gcnew array<System::UInt32> { GameAddress::TESRace });
            RegisterType(modulePtr, "BGSLocation", BGSLocation::typeid, impl_BGSLocation::typeid, 240, gcnew array<System::UInt32> { GameAddress::BGSLocation });
            RegisterType(modulePtr, "DataHandler", DataHandler::typeid, impl_DataHandler::typeid, 3520, nullptr);
            RegisterType(modulePtr, "TESReactionForm", TESReactionForm::typeid, impl_TESReactionForm::typeid, 32, gcnew array<System::UInt32> { GameAddress::TESReactionForm });
            RegisterType(modulePtr, "TESFaction", TESFaction::typeid, impl_TESFaction::typeid, 256, gcnew array<System::UInt32> { GameAddress::TESFaction });
            RegisterType(modulePtr, "TESPackage", TESPackage::typeid, impl_TESPackage::typeid, 224, gcnew array<System::UInt32> { GameAddress::TESPackage });
            RegisterType(modulePtr, "TESRaceForm", TESRaceForm::typeid, impl_TESRaceForm::typeid, 16, gcnew array<System::UInt32> { GameAddress::TESRaceForm });
            RegisterType(modulePtr, "TESEnchantableForm", TESEnchantableForm::typeid, impl_TESEnchantableForm::typeid, 24, gcnew array<System::UInt32> { GameAddress::TESEnchantableForm });
            RegisterType(modulePtr, "TESValueForm", TESValueForm::typeid, impl_TESValueForm::typeid, 16, gcnew array<System::UInt32> { GameAddress::TESValueForm });
            RegisterType(modulePtr, "BGSDestructibleObjectForm", BGSDestructibleObjectForm::typeid, impl_BGSDestructibleObjectForm::typeid, 16, gcnew array<System::UInt32> { GameAddress::BGSDestructibleObjectForm });
            RegisterType(modulePtr, "BGSPickupPutdownSounds", BGSPickupPutdownSounds::typeid, impl_BGSPickupPutdownSounds::typeid, 24, gcnew array<System::UInt32> { GameAddress::BGSPickupPutdownSounds });
            RegisterType(modulePtr, "TESBipedModelForm", TESBipedModelForm::typeid, impl_TESBipedModelForm::typeid, 240, gcnew array<System::UInt32> { GameAddress::TESBipedModelForm });
            RegisterType(modulePtr, "BGSBlockBashData", BGSBlockBashData::typeid, impl_BGSBlockBashData::typeid, 24, gcnew array<System::UInt32> { GameAddress::BGSBlockBashData });
            RegisterType(modulePtr, "TESObjectARMO", TESObjectARMO::typeid, impl_TESObjectARMO::typeid, 552, gcnew array<System::UInt32> { GameAddress::TESObjectARMO });
            RegisterType(modulePtr, "TESBoundAnimObject", TESBoundAnimObject::typeid, impl_TESBoundAnimObject::typeid, 48, gcnew array<System::UInt32> { GameAddress::TESBoundAnimObject });
            RegisterType(modulePtr, "TESActorBaseData", TESActorBaseData::typeid, impl_TESActorBaseData::typeid, 88, gcnew array<System::UInt32> { GameAddress::TESActorBaseData });
            RegisterType(modulePtr, "TESContainer", TESContainer::typeid, impl_TESContainer::typeid, 24, gcnew array<System::UInt32> { GameAddress::TESContainer });
            RegisterType(modulePtr, "TESContainer::Data", TESContainer::Data::typeid, impl_TESContainer::impl_Data::typeid, 24, nullptr);
            RegisterType(modulePtr, "TESContainer::Entry", TESContainer::Entry::typeid, impl_TESContainer::impl_Entry::typeid, 24, nullptr);
            RegisterType(modulePtr, "TESAIForm", TESAIForm::typeid, impl_TESAIForm::typeid, 40, gcnew array<System::UInt32> { GameAddress::TESAIForm });
            RegisterType(modulePtr, "BGSPerkRankArray", BGSPerkRankArray::typeid, impl_BGSPerkRankArray::typeid, 24, gcnew array<System::UInt32> { GameAddress::BGSPerkRankArray });
            RegisterType(modulePtr, "TESActorBase", TESActorBase::typeid, impl_TESActorBase::typeid, 336, gcnew array<System::UInt32> { GameAddress::TESActorBase });
            RegisterType(modulePtr, "BGSOverridePackCollection", BGSOverridePackCollection::typeid, impl_BGSOverridePackCollection::typeid, 40, gcnew array<System::UInt32> { GameAddress::BGSOverridePackCollection });
            RegisterType(modulePtr, "TESNPC", TESNPC::typeid, impl_TESNPC::typeid, 616, gcnew array<System::UInt32> { GameAddress::TESNPC });
            RegisterType(modulePtr, "BGSAssociationType", BGSAssociationType::typeid, impl_BGSAssociationType::typeid, 72, gcnew array<System::UInt32> { GameAddress::BGSAssociationType });
            RegisterType(modulePtr, "TESFile", TESFile::typeid, impl_TESFile::typeid, 1224, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "BSString", BSString::typeid, impl_BSString::typeid, 16, nullptr);
            RegisterType(modulePtr, "BGSOutfit", BGSOutfit::typeid, impl_BGSOutfit::typeid, 56, gcnew array<System::UInt32> { GameAddress::BGSOutfit });
            RegisterType(modulePtr, "BSExtraData", BSExtraData::typeid, impl_BSExtraData::typeid, 16, gcnew array<System::UInt32> { GameAddress::BSExtraData });
            RegisterType(modulePtr, "ExtraContainerChanges", ExtraContainerChanges::typeid, impl_ExtraContainerChanges::typeid, 24, gcnew array<System::UInt32> { GameAddress::ExtraContainerChanges });
            RegisterType(modulePtr, "ExtraContainerChanges::Data", ExtraContainerChanges::Data::typeid, impl_ExtraContainerChanges::impl_Data::typeid, 32, nullptr);
            RegisterType(modulePtr, "ExtraContainerChanges::ItemEntry", ExtraContainerChanges::ItemEntry::typeid, impl_ExtraContainerChanges::impl_ItemEntry::typeid, 24, nullptr);
            RegisterType(modulePtr, "TESModelTextureSwap", TESModelTextureSwap::typeid, impl_TESModelTextureSwap::typeid, 56, gcnew array<System::UInt32> { GameAddress::TESModelTextureSwap });
            RegisterType(modulePtr, "BGSOpenCloseForm", BGSOpenCloseForm::typeid, impl_BGSOpenCloseForm::typeid, 8, gcnew array<System::UInt32> { GameAddress::BGSOpenCloseForm });
            RegisterType(modulePtr, "TESObjectCONT", TESObjectCONT::typeid, impl_TESObjectCONT::typeid, 208, gcnew array<System::UInt32> { GameAddress::TESObjectCONT });
            RegisterType(modulePtr, "BSTDefaultScatterTable<,>", BSTDefaultScatterTable<System::Object^, IMemoryObject^>::typeid->GetGenericTypeDefinition(), impl_BSTDefaultScatterTable<System::Object^, IMemoryObject^>::typeid->GetGenericTypeDefinition(), 48, nullptr);
            RegisterType(modulePtr, "TES", TES::typeid, impl_TES::typeid, 696, gcnew array<System::UInt32> { GameAddress::TES });
            RegisterType(modulePtr, "ICellAttachDetachEventSource", ICellAttachDetachEventSource::typeid, impl_ICellAttachDetachEventSource::typeid, 96, gcnew array<System::UInt32> { GameAddress::ICellAttachDetachEventSource });
            RegisterType(modulePtr, "BSTSingletonExplicit<>", BSTSingletonExplicit<System::Object^>::typeid->GetGenericTypeDefinition(), impl_BSTSingletonExplicit<System::Object^>::typeid->GetGenericTypeDefinition(), -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "BSResource", BSResource::typeid, impl_BSResource::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "BSResource::ArchiveStreamOpenedEvent", BSResource::ArchiveStreamOpenedEvent::typeid, impl_BSResource::impl_ArchiveStreamOpenedEvent::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "GridCellArray", GridCellArray::typeid, impl_GridCellArray::typeid, 48, gcnew array<System::UInt32> { GameAddress::GridCellArray });
            RegisterType(modulePtr, "GridArray", GridArray::typeid, impl_GridArray::typeid, 24, gcnew array<System::UInt32> { GameAddress::GridArray });
            RegisterType(modulePtr, "Mutex", Mutex::typeid, impl_Mutex::typeid, 8, nullptr);
            RegisterType(modulePtr, "TESQuest", TESQuest::typeid, impl_TESQuest::typeid, 616, gcnew array<System::UInt32> { GameAddress::TESQuest });
            RegisterType(modulePtr, "BGSStoryManagerTreeForm", BGSStoryManagerTreeForm::typeid, impl_BGSStoryManagerTreeForm::typeid, 40, gcnew array<System::UInt32> { GameAddress::BGSStoryManagerTreeForm });
            RegisterType(modulePtr, "BGSBaseAlias", BGSBaseAlias::typeid, impl_BGSBaseAlias::typeid, 40, gcnew array<System::UInt32> { GameAddress::BGSBaseAlias });
            RegisterType(modulePtr, "BGSRefAlias", BGSRefAlias::typeid, impl_BGSRefAlias::typeid, 72, gcnew array<System::UInt32> { GameAddress::BGSRefAlias });
            RegisterType(modulePtr, "MenuManager", MenuManager::typeid, impl_MenuManager::typeid, 464, nullptr);
            RegisterType(modulePtr, "InputManager", InputManager::typeid, impl_InputManager::typeid, 296, nullptr);
            RegisterType(modulePtr, "ActorMagicCaster", ActorMagicCaster::typeid, impl_ActorMagicCaster::typeid, 256, gcnew array<System::UInt32> { GameAddress::ActorMagicCaster });
            RegisterType(modulePtr, "MagicCaster", MagicCaster::typeid, impl_MagicCaster::typeid, 72, gcnew array<System::UInt32> { GameAddress::MagicCaster });
            RegisterType(modulePtr, "SimpleAnimationGraphManagerHolder", SimpleAnimationGraphManagerHolder::typeid, impl_SimpleAnimationGraphManagerHolder::typeid, 24, gcnew array<System::UInt32> { GameAddress::SimpleAnimationGraphManagerHolder });
            RegisterType(modulePtr, "BSLight", BSLight::typeid, impl_BSLight::typeid, 320, gcnew array<System::UInt32> { GameAddress::BSLight });
            RegisterType(modulePtr, "TESImageSpaceModifier", TESImageSpaceModifier::typeid, impl_TESImageSpaceModifier::typeid, 736, gcnew array<System::UInt32> { GameAddress::TESImageSpaceModifier });
            RegisterType(modulePtr, "AutoVanityState", AutoVanityState::typeid, impl_AutoVanityState::typeid, 40, gcnew array<System::UInt32> { GameAddress::AutoVanityState });
            RegisterType(modulePtr, "VATSCameraState", VATSCameraState::typeid, impl_VATSCameraState::typeid, 56, gcnew array<System::UInt32> { GameAddress::VATSCameraState });
            RegisterType(modulePtr, "FreeCameraState", FreeCameraState::typeid, impl_FreeCameraState::typeid, 80, gcnew array<System::UInt32> { GameAddress::FreeCameraState });
            RegisterType(modulePtr, "IronSightsState", IronSightsState::typeid, impl_IronSightsState::typeid, 40, gcnew array<System::UInt32> { GameAddress::IronSightsState });
            RegisterType(modulePtr, "FurnitureCameraState", FurnitureCameraState::typeid, impl_FurnitureCameraState::typeid, 64, gcnew array<System::UInt32> { GameAddress::FurnitureCameraState });
            RegisterType(modulePtr, "PlayerCameraTransitionState", PlayerCameraTransitionState::typeid, impl_PlayerCameraTransitionState::typeid, 64, gcnew array<System::UInt32> { GameAddress::PlayerCameraTransitionState });
            RegisterType(modulePtr, "TweenMenuCameraState", TweenMenuCameraState::typeid, impl_TweenMenuCameraState::typeid, 80, gcnew array<System::UInt32> { GameAddress::TweenMenuCameraState });
            RegisterType(modulePtr, "HorseCameraState", HorseCameraState::typeid, impl_HorseCameraState::typeid, 248, gcnew array<System::UInt32> { GameAddress::HorseCameraState });
            RegisterType(modulePtr, "BleedoutCameraState", BleedoutCameraState::typeid, impl_BleedoutCameraState::typeid, 312, gcnew array<System::UInt32> { GameAddress::BleedoutCameraState });
            RegisterType(modulePtr, "DragonCameraState", DragonCameraState::typeid, impl_DragonCameraState::typeid, 272, gcnew array<System::UInt32> { GameAddress::DragonCameraState });
            RegisterType(modulePtr, "Setting", Setting::typeid, impl_Setting::typeid, 24, gcnew array<System::UInt32> { GameAddress::Setting });
            RegisterType(modulePtr, "MenuScreenData", MenuScreenData::typeid, impl_MenuScreenData::typeid, 48, nullptr);
            RegisterType(modulePtr, "PlayerControls", PlayerControls::typeid, impl_PlayerControls::typeid, 480, gcnew array<System::UInt32> { GameAddress::PlayerControls });
            RegisterType(modulePtr, "InputEvent", InputEvent::typeid, impl_InputEvent::typeid, 24, gcnew array<System::UInt32> { GameAddress::InputEvent });
            RegisterType(modulePtr, "TESFurnitureEvent", TESFurnitureEvent::typeid, impl_TESFurnitureEvent::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "BGSConstructibleObject", BGSConstructibleObject::typeid, impl_BGSConstructibleObject::typeid, 88, gcnew array<System::UInt32> { GameAddress::BGSConstructibleObject });
            RegisterType(modulePtr, "NiLight", NiLight::typeid, impl_NiLight::typeid, 320, gcnew array<System::UInt32> { GameAddress::NiLight });
            RegisterType(modulePtr, "TESLeveledList", TESLeveledList::typeid, impl_TESLeveledList::typeid, 40, gcnew array<System::UInt32> { GameAddress::TESLeveledList });
            RegisterType(modulePtr, "TESLeveledList::Entry", TESLeveledList::Entry::typeid, impl_TESLeveledList::impl_Entry::typeid, 24, nullptr);
            RegisterType(modulePtr, "TESLeveledList::Entry::Data", TESLeveledList::Entry::Data::typeid, impl_TESLeveledList::impl_Entry::impl_Data::typeid, 24, nullptr);
            RegisterType(modulePtr, "TESGlobal", TESGlobal::typeid, impl_TESGlobal::typeid, 56, gcnew array<System::UInt32> { GameAddress::TESGlobal });
            RegisterType(modulePtr, "TESLevItem", TESLevItem::typeid, impl_TESLevItem::typeid, 88, gcnew array<System::UInt32> { GameAddress::TESLevItem });
            RegisterType(modulePtr, "TESLevSpell", TESLevSpell::typeid, impl_TESLevSpell::typeid, 88, gcnew array<System::UInt32> { GameAddress::TESLevSpell });
            RegisterType(modulePtr, "TESLevCharacter", TESLevCharacter::typeid, impl_TESLevCharacter::typeid, 144, gcnew array<System::UInt32> { GameAddress::TESLevCharacter });
            RegisterType(modulePtr, "BSTDefaultScatterTable2<,>", BSTDefaultScatterTable2<System::Object^, IMemoryObject^>::typeid->GetGenericTypeDefinition(), impl_BSTDefaultScatterTable2<System::Object^, IMemoryObject^>::typeid->GetGenericTypeDefinition(), 48, nullptr);
            RegisterType(modulePtr, "ExtraPoison", ExtraPoison::typeid, impl_ExtraPoison::typeid, 32, gcnew array<System::UInt32> { GameAddress::ExtraPoison });
            RegisterType(modulePtr, "AlchemyItem", AlchemyItem::typeid, impl_AlchemyItem::typeid, 360, gcnew array<System::UInt32> { GameAddress::AlchemyItem });
            RegisterType(modulePtr, "BGSMessageIcon", BGSMessageIcon::typeid, impl_BGSMessageIcon::typeid, 24, gcnew array<System::UInt32> { GameAddress::BGSMessageIcon });
            RegisterType(modulePtr, "TESObjectWEAP", TESObjectWEAP::typeid, impl_TESObjectWEAP::typeid, 544, gcnew array<System::UInt32> { GameAddress::TESObjectWEAP });
            RegisterType(modulePtr, "TESAttackDamageForm", TESAttackDamageForm::typeid, impl_TESAttackDamageForm::typeid, 16, gcnew array<System::UInt32> { GameAddress::TESAttackDamageForm });
            RegisterType(modulePtr, "BGSPreloadable", BGSPreloadable::typeid, impl_BGSPreloadable::typeid, 8, gcnew array<System::UInt32> { GameAddress::BGSPreloadable });
            RegisterType(modulePtr, "TESAmmo", TESAmmo::typeid, impl_TESAmmo::typeid, 296, gcnew array<System::UInt32> { GameAddress::TESAmmo });
            RegisterType(modulePtr, "BGSProjectile", BGSProjectile::typeid, impl_BGSProjectile::typeid, 312, gcnew array<System::UInt32> { GameAddress::BGSProjectile });
            RegisterType(modulePtr, "CrossHairPickData", CrossHairPickData::typeid, impl_CrossHairPickData::typeid, 56, nullptr);
            RegisterType(modulePtr, "bhkSimpleShapePhantom", bhkSimpleShapePhantom::typeid, impl_bhkSimpleShapePhantom::typeid, 48, gcnew array<System::UInt32> { GameAddress::bhkSimpleShapePhantom });
            RegisterType(modulePtr, "bhkShapePhantom", bhkShapePhantom::typeid, impl_bhkShapePhantom::typeid, 48, gcnew array<System::UInt32> { GameAddress::bhkShapePhantom });
            RegisterType(modulePtr, "bhkPhantom", bhkPhantom::typeid, impl_bhkPhantom::typeid, 48, gcnew array<System::UInt32> { GameAddress::bhkPhantom });
            RegisterType(modulePtr, "BSGeometry", BSGeometry::typeid, impl_BSGeometry::typeid, 344, gcnew array<System::UInt32> { GameAddress::BSGeometry });
            RegisterType(modulePtr, "NiSkinInstance", NiSkinInstance::typeid, impl_NiSkinInstance::typeid, 136, gcnew array<System::UInt32> { GameAddress::NiSkinInstance });
            RegisterType(modulePtr, "BSDismemberSkinInstance", BSDismemberSkinInstance::typeid, impl_BSDismemberSkinInstance::typeid, 160, gcnew array<System::UInt32> { GameAddress::BSDismemberSkinInstance });
            
            // Register events.
            Events::InitializeEvents();
            
            // Register model loader.
            Events::OnFrame->Register(gcnew NetScriptFramework::Event<FrameEventArgs^>::EventHandler(NiObjectLoadParameters::_UpdateRequestModel), 0, 0, NetScriptFramework::EventRegistrationFlags::None);
            
            // Initialize keywords.
            Events::OnMainMenu->Register(gcnew NetScriptFramework::Event<MainMenuEventArgs^>::EventHandler(_Initialize_KeywordCache), 0, 1, NetScriptFramework::EventRegistrationFlags::None);
            
            // Write out mod list.
            CrashLog::OnAfterWrite->Register(gcnew NetScriptFramework::Event<CrashLogEventArgs^>::EventHandler(_CrashLog_WriteModList), 0, 0, NetScriptFramework::EventRegistrationFlags::None);
        }
    }
}
