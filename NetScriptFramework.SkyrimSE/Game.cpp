#include "Game.h"
#include "Globals.h"
#include "Events.h"
#include "Implementations.h"

namespace NetScriptFramework
{
    namespace Skyrim
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
            RegisterType(modulePtr, "ActiveEffect", ActiveEffect::typeid, impl_ActiveEffect::typeid, 144, gcnew array<System::UInt32> { 0x1E5ED50 });
            RegisterType(modulePtr, "BaseFormComponent", BaseFormComponent::typeid, impl_BaseFormComponent::typeid, 8, gcnew array<System::UInt32> { 0x1E36E50 });
            RegisterType(modulePtr, "TESForm", TESForm::typeid, impl_TESForm::typeid, 32, gcnew array<System::UInt32> { 0x1E36EA0 }, gcnew NetScriptFramework::Tools::_Internal::TypeDebugWriter("", nullptr));
            RegisterType(modulePtr, "NiRefObject", NiRefObject::typeid, impl_NiRefObject::typeid, 16, gcnew array<System::UInt32> { 0x1E3A690 });
            RegisterType(modulePtr, "BSHandleRefObject", BSHandleRefObject::typeid, impl_BSHandleRefObject::typeid, 16, gcnew array<System::UInt32> { 0x1E40F50 });
            RegisterType(modulePtr, "BSTEventSink<>", BSTEventSink<System::Object^>::typeid->GetGenericTypeDefinition(), impl_BSTEventSink<System::Object^>::typeid->GetGenericTypeDefinition(), 8, gcnew array<System::UInt32> { 0x1E3A950, 0x1E3A9A0, 0x1E3A8F0, 0x1E3ACA0, 0x1E3ACF0, 0x1E3BBD0, 0x1E40B50, 0x1E41128, 0x1E45878, 0x1E532E0, 0x1E55A50, 0x1E5B8D8, 0x1E5BF30, 0x1E5CD80, 0x1E5EC48, 0x1E5EC90, 0x1E5F0B8, 0x1E60660, 0x1E606E8, 0x1E60380, 0x1E60D18, 0x1E60D50, 0x1E612C0, 0x1E61668, 0x1E61740, 0x1E61F28, 0x1E61F68, 0x1E61FA8, 0x1E62138, 0x1E62178, 0x1E621B8, 0x1E62020, 0x1E62060, 0x1E63470, 0x1E62B90, 0x1E62B50, 0x1E62ED0, 0x1E634B8, 0x1E62E90, 0x1E62E50, 0x1E63138, 0x1E63178, 0x1E63230, 0x1E63040, 0x1E63530, 0x1E634F0, 0x1E631F8, 0x1E62F90, 0x1E633F0, 0x1E62E10, 0x1E630F8, 0x1E62CD0, 0x1E62D10, 0x1E632F0, 0x1E62F10, 0x1E63330, 0x1E62F50, 0x1E62FC8, 0x1E632A8, 0x1E63430, 0x1E63268, 0x1E62BD0, 0x1E62DD0, 0x1E62D90, 0x1E63370, 0x1E62D50, 0x1E630B8, 0x1E63078, 0x1E63000, 0x1E62C90, 0x1E62C10, 0x1E62C50, 0x1E633B0, 0x1E63570, 0x1E631B8, 0x1E642F8, 0x1E642B0, 0x1E65AD8, 0x1E66330, 0x1E66370, 0x1E69B08, 0x1E79868, 0x1EA4D98, 0x1EA7E98, 0x1EA7E58, 0x1EA87A0, 0x1EA8920, 0x1EAA4C0, 0x1EAA500, 0x1EAA550, 0x1EAA598, 0x1EAA5E0, 0x1EAA630, 0x1EAA670, 0x1EAA6B0, 0x1EAA6F8, 0x1EAA730, 0x1EAA778, 0x1EAA7B8, 0x1EAA7F0, 0x1EAA830, 0x1EAA870, 0x1EAA8A8, 0x1EAA8E8, 0x1EAA928, 0x1EAA970, 0x1EAA9B8, 0x1EAAA00, 0x1EAAA48, 0x1EAAA90, 0x1EAAAD8, 0x1EAAB10, 0x1EAAB50, 0x1EAAB90, 0x1EAABD0, 0x1EAAC10, 0x1EAAC58, 0x1EAAC90, 0x1EAACD0, 0x1EAAD10, 0x1EAAD88, 0x1EAADC8, 0x1EAAE00, 0x1EAAE38, 0x1EAAE78, 0x1EAAEB8, 0x1EAAF00, 0x1EAAD48, 0x1EAAF48, 0x1EAA480, 0x1EB49B0, 0x1EB4A00, 0x1EB4A50, 0x1EB4AA0, 0x1EC5D80, 0x1ECA7D8, 0x1EE3D60 });
            RegisterType(modulePtr, "BSAnimationGraphEvent", BSAnimationGraphEvent::typeid, impl_BSAnimationGraphEvent::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "IAnimationGraphManagerHolder", IAnimationGraphManagerHolder::typeid, impl_IAnimationGraphManagerHolder::typeid, 8, gcnew array<System::UInt32> { 0x1E41168 });
            RegisterType(modulePtr, "TESObjectREFR", TESObjectREFR::typeid, impl_TESObjectREFR::typeid, 152, gcnew array<System::UInt32> { 0x1E39808 }, gcnew NetScriptFramework::Tools::_Internal::TypeDebugWriter("BaseForm", gcnew System::Func<IVirtualObject^, System::String^>(Debug_TESObjectREFR_BaseForm)));
            RegisterType(modulePtr, "MagicTarget", MagicTarget::typeid, impl_MagicTarget::typeid, 24, gcnew array<System::UInt32> { 0x1E38170 });
            RegisterType(modulePtr, "ActorValueOwner", ActorValueOwner::typeid, impl_ActorValueOwner::typeid, 8, gcnew array<System::UInt32> { 0x1E45850 });
            RegisterType(modulePtr, "IMovementInterface", IMovementInterface::typeid, impl_IMovementInterface::typeid, 8, gcnew array<System::UInt32> { 0x1E64238 });
            RegisterType(modulePtr, "IMovementState", IMovementState::typeid, impl_IMovementState::typeid, 8, gcnew array<System::UInt32> { 0x1E64210 });
            RegisterType(modulePtr, "ActorState", ActorState::typeid, impl_ActorState::typeid, 16, gcnew array<System::UInt32> { 0x1E64398 });
            RegisterType(modulePtr, "BSTransformDeltaEvent", BSTransformDeltaEvent::typeid, impl_BSTransformDeltaEvent::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "bhkCharacterMoveFinishEvent", bhkCharacterMoveFinishEvent::typeid, impl_bhkCharacterMoveFinishEvent::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "IPostAnimationChannelUpdateFunctor", IPostAnimationChannelUpdateFunctor::typeid, impl_IPostAnimationChannelUpdateFunctor::typeid, 8, gcnew array<System::UInt32> { 0x1E64268 });
            RegisterType(modulePtr, "Actor", Actor::typeid, impl_Actor::typeid, 688, gcnew array<System::UInt32> { 0x1E3AB48 });
            RegisterType(modulePtr, "BSFixedString", BSFixedString::typeid, impl_BSFixedString::typeid, 8, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "BSScript", BSScript::typeid, impl_BSScript::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "BSScript::NF_util", BSScript::NF_util::typeid, impl_BSScript::impl_NF_util::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "BSScript::NF_util::NativeFunctionBase", BSScript::NF_util::NativeFunctionBase::typeid, impl_BSScript::impl_NF_util::impl_NativeFunctionBase::typeid, 80, gcnew array<System::UInt32> { 0x1EABD50 });
            RegisterType(modulePtr, "BSScript::IFunction", BSScript::IFunction::typeid, impl_BSScript::impl_IFunction::typeid, 16, gcnew array<System::UInt32> { 0x1EABCC8 });
            RegisterType(modulePtr, "BSIntrusiveRefCounted", BSIntrusiveRefCounted::typeid, impl_BSIntrusiveRefCounted::typeid, 16, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "BSTArrayBase", BSTArrayBase::typeid, impl_BSTArrayBase::typeid, 24, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "BSTArrayBase::IAllocatorFunctor", BSTArrayBase::IAllocatorFunctor::typeid, impl_BSTArrayBase::impl_IAllocatorFunctor::typeid, -1, gcnew array<System::UInt32> { 0x1E37600 });
            RegisterType(modulePtr, "GameFunction", GameFunction::typeid, impl_GameFunction::typeid, 72, nullptr);
            RegisterType(modulePtr, "ListNode<>", ListNode<System::Object^>::typeid->GetGenericTypeDefinition(), impl_ListNode<System::Object^>::typeid->GetGenericTypeDefinition(), 16, nullptr);
            RegisterType(modulePtr, "NiObject", NiObject::typeid, impl_NiObject::typeid, 16, gcnew array<System::UInt32> { 0x1E3A6B8 });
            RegisterType(modulePtr, "NiObjectNET", NiObjectNET::typeid, impl_NiObjectNET::typeid, 48, gcnew array<System::UInt32> { 0x1E3A6D8 }, gcnew NetScriptFramework::Tools::_Internal::TypeDebugWriter("", nullptr));
            RegisterType(modulePtr, "NiAVObject", NiAVObject::typeid, impl_NiAVObject::typeid, 272, gcnew array<System::UInt32> { 0x1E3A700 });
            RegisterType(modulePtr, "NiNode", NiNode::typeid, impl_NiNode::typeid, 296, gcnew array<System::UInt32> { 0x1E3AA38 });
            RegisterType(modulePtr, "NiTObjectArray<>", NiTObjectArray<System::Object^>::typeid->GetGenericTypeDefinition(), impl_NiTObjectArray<System::Object^>::typeid->GetGenericTypeDefinition(), 24, gcnew array<System::UInt32> { 0x1E46AF0, 0x1E5FF10, 0x1EBFFB0, 0x1EC1740, 0x1EC2580, 0x1EC32B0, 0x1EC3370, 0x1EE29B0 });
            RegisterType(modulePtr, "NiPoint3", NiPoint3::typeid, impl_NiPoint3::typeid, 12, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "NiPointer<>", NiPointer<NiRefObject^>::typeid->GetGenericTypeDefinition(), impl_NiPointer<NiRefObject^>::typeid->GetGenericTypeDefinition(), 8, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "NiTArray<,>", NiTArray<System::Object^, System::Object^>::typeid->GetGenericTypeDefinition(), impl_NiTArray<System::Object^, System::Object^>::typeid->GetGenericTypeDefinition(), 24, gcnew array<System::UInt32> { 0x1E3AA60, 0x1E3AAC0, 0x1E3CAB0, 0x1E41DF0, 0x1E46B40, 0x1E55220, 0x1E5FF50, 0x1E8DA50, 0x1EC0000, 0x1EC04F0, 0x1EC0698, 0x1EC0730, 0x1EC0820, 0x1EC0F00, 0x1EC11B0, 0x1EC12F0, 0x1EC1480, 0x1EC1790, 0x1EC1C20, 0x1EC25D0, 0x1EC2B90, 0x1EC3300, 0x1EC33C0, 0x1EC4790, 0x1EC4BB0, 0x1EE0690, 0x1EE2A00, 0x1EE2AC0, 0x1EE2DA0, 0x1EE2EC0, 0x1EE2F80, 0x1EE3040, 0x1EE30F0 });
            RegisterType(modulePtr, "TESFullName", TESFullName::typeid, impl_TESFullName::typeid, 16, gcnew array<System::UInt32> { 0x1E36F70 });
            RegisterType(modulePtr, "BSExtraDataList", BSExtraDataList::typeid, impl_BSExtraDataList::typeid, 24, nullptr);
            RegisterType(modulePtr, "TESObjectCELL", TESObjectCELL::typeid, impl_TESObjectCELL::typeid, 320, gcnew array<System::UInt32> { 0x1E396F0 });
            RegisterType(modulePtr, "TESModel", TESModel::typeid, impl_TESModel::typeid, 40, gcnew array<System::UInt32> { 0x1E36FF0 });
            RegisterType(modulePtr, "TESWorldSpace", TESWorldSpace::typeid, impl_TESWorldSpace::typeid, 856, gcnew array<System::UInt32> { 0x1E396C8 });
            RegisterType(modulePtr, "TESWeightForm", TESWeightForm::typeid, impl_TESWeightForm::typeid, 16, gcnew array<System::UInt32> { 0x1E37080 });
            RegisterType(modulePtr, "NiTNewInterface<>", NiTNewInterface<System::Object^>::typeid->GetGenericTypeDefinition(), impl_NiTNewInterface<System::Object^>::typeid->GetGenericTypeDefinition(), -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "NiTransform", NiTransform::typeid, impl_NiTransform::typeid, 52, nullptr);
            RegisterType(modulePtr, "NiMatrix33", NiMatrix33::typeid, impl_NiMatrix33::typeid, 36, nullptr);
            RegisterType(modulePtr, "TESCameraState", TESCameraState::typeid, impl_TESCameraState::typeid, 32, gcnew array<System::UInt32> { 0x1E3D4C8 });
            RegisterType(modulePtr, "TESCamera", TESCamera::typeid, impl_TESCamera::typeid, 56, gcnew array<System::UInt32> { 0x1E3D518 });
            RegisterType(modulePtr, "PlayerInputHandler", PlayerInputHandler::typeid, impl_PlayerInputHandler::typeid, 16, gcnew array<System::UInt32> { 0x1E5D010 });
            RegisterType(modulePtr, "FirstPersonState", FirstPersonState::typeid, impl_FirstPersonState::typeid, 144, gcnew array<System::UInt32> { 0x1EA4098 });
            RegisterType(modulePtr, "ThirdPersonState", ThirdPersonState::typeid, impl_ThirdPersonState::typeid, 232, gcnew array<System::UInt32> { 0x1E5D040 });
            RegisterType(modulePtr, "Character", Character::typeid, impl_Character::typeid, 688, gcnew array<System::UInt32> { 0x1E5F3A0 });
            RegisterType(modulePtr, "MenuOpenCloseEvent", MenuOpenCloseEvent::typeid, impl_MenuOpenCloseEvent::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "MenuModeChangeEvent", MenuModeChangeEvent::typeid, impl_MenuModeChangeEvent::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "UserEventEnabledEvent", UserEventEnabledEvent::typeid, impl_UserEventEnabledEvent::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "TESTrackedStatsEvent", TESTrackedStatsEvent::typeid, impl_TESTrackedStatsEvent::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "PlayerCharacter", PlayerCharacter::typeid, impl_PlayerCharacter::typeid, 3040, gcnew array<System::UInt32> { 0x1E66248 });
            RegisterType(modulePtr, "TESWeather", TESWeather::typeid, impl_TESWeather::typeid, 2264, gcnew array<System::UInt32> { 0x1E3FF88 });
            RegisterType(modulePtr, "BGSMenuDisplayObject", BGSMenuDisplayObject::typeid, impl_BGSMenuDisplayObject::typeid, 16, gcnew array<System::UInt32> { 0x1E37738 });
            RegisterType(modulePtr, "BGSKeywordForm", BGSKeywordForm::typeid, impl_BGSKeywordForm::typeid, 24, gcnew array<System::UInt32> { 0x1E36F98 });
            RegisterType(modulePtr, "EffectSetting", EffectSetting::typeid, impl_EffectSetting::typeid, 408, gcnew array<System::UInt32> { 0x1E37598 });
            RegisterType(modulePtr, "BSTArray<>", BSTArray<System::Object^>::typeid->GetGenericTypeDefinition(), impl_BSTArray<System::Object^>::typeid->GetGenericTypeDefinition(), 24, nullptr);
            RegisterType(modulePtr, "BGSKeyword", BGSKeyword::typeid, impl_BGSKeyword::typeid, 40, gcnew array<System::UInt32> { 0x1E399C8 });
            RegisterType(modulePtr, "BSTArrayAllocatorFunctor<>", BSTArrayAllocatorFunctor<System::Object^>::typeid->GetGenericTypeDefinition(), impl_BSTArrayAllocatorFunctor<System::Object^>::typeid->GetGenericTypeDefinition(), -1, gcnew array<System::UInt32> { 0x1E37640, 0x1E39A20, 0x1E3A4B0, 0x1E3A2A0, 0x1E3B700, 0x1E3C430, 0x1E43420, 0x1E488B0, 0x1E56B50, 0x1E56BB0, 0x1E57120, 0x1E5B5C0, 0x1E5C940, 0x1E64C70, 0x1E67420, 0x1E674B0, 0x1E67510, 0x1E67570, 0x1E79370, 0x1E796C0, 0x1E7B730, 0x1EA4290, 0x1EA4C60, 0x1EA53A0, 0x1EA5620, 0x1EBDD60, 0x1ECAB20, 0x1ECF180, 0x1ED2460 });
            RegisterType(modulePtr, "BSTArrayHeapAllocator", BSTArrayHeapAllocator::typeid, impl_BSTArrayHeapAllocator::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "NiCollisionObject", NiCollisionObject::typeid, impl_NiCollisionObject::typeid, 24, gcnew array<System::UInt32> { 0x1E3DDD8 });
            RegisterType(modulePtr, "bhkRefObject", bhkRefObject::typeid, impl_bhkRefObject::typeid, 24, gcnew array<System::UInt32> { 0x1E40EE8 });
            RegisterType(modulePtr, "bhkSerializable", bhkSerializable::typeid, impl_bhkSerializable::typeid, 32, gcnew array<System::UInt32> { 0x1E40EC0 });
            RegisterType(modulePtr, "bhkWorldObject", bhkWorldObject::typeid, impl_bhkWorldObject::typeid, 40, gcnew array<System::UInt32> { 0x1E3DDB0 });
            RegisterType(modulePtr, "bhkNiCollisionObject", bhkNiCollisionObject::typeid, impl_bhkNiCollisionObject::typeid, 40, gcnew array<System::UInt32> { 0x1E3DE00 });
            RegisterType(modulePtr, "bhkEntity", bhkEntity::typeid, impl_bhkEntity::typeid, 40, gcnew array<System::UInt32> { 0x1E41108 });
            RegisterType(modulePtr, "bhkRigidBody", bhkRigidBody::typeid, impl_bhkRigidBody::typeid, 64, gcnew array<System::UInt32> { 0x1E3DE30 });
            RegisterType(modulePtr, "PlayerCamera", PlayerCamera::typeid, impl_PlayerCamera::typeid, 360, gcnew array<System::UInt32> { 0x1EA40C0 });
            RegisterType(modulePtr, "PositionPlayerEvent", PositionPlayerEvent::typeid, impl_PositionPlayerEvent::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "BSGamerProfileEvent", BSGamerProfileEvent::typeid, impl_BSGamerProfileEvent::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "Main", Main::typeid, impl_Main::typeid, 624, gcnew array<System::UInt32> { 0x1E61AE0 });
            RegisterType(modulePtr, "TESDescription", TESDescription::typeid, impl_TESDescription::typeid, 16, gcnew array<System::UInt32> { 0x1E37F68 });
            RegisterType(modulePtr, "TESTexture", TESTexture::typeid, impl_TESTexture::typeid, 16, gcnew array<System::UInt32> { 0x1E37030 });
            RegisterType(modulePtr, "TESIcon", TESIcon::typeid, impl_TESIcon::typeid, 16, gcnew array<System::UInt32> { 0x1E37010 });
            RegisterType(modulePtr, "BGSPerk", BGSPerk::typeid, impl_BGSPerk::typeid, 128, gcnew array<System::UInt32> { 0x1E376C0 });
            RegisterType(modulePtr, "BGSEquipType", BGSEquipType::typeid, impl_BGSEquipType::typeid, 16, gcnew array<System::UInt32> { 0x1E370A8 });
            RegisterType(modulePtr, "TESShout", TESShout::typeid, impl_TESShout::typeid, 168, gcnew array<System::UInt32> { 0x1E3BB58 });
            RegisterType(modulePtr, "TESWordOfPower", TESWordOfPower::typeid, impl_TESWordOfPower::typeid, 56, gcnew array<System::UInt32> { 0x1E44360 });
            RegisterType(modulePtr, "TESObject", TESObject::typeid, impl_TESObject::typeid, 32, gcnew array<System::UInt32> { 0x1E36F50 });
            RegisterType(modulePtr, "TESBoundObject", TESBoundObject::typeid, impl_TESBoundObject::typeid, 48, gcnew array<System::UInt32> { 0x1E36F28 });
            RegisterType(modulePtr, "MagicItem", MagicItem::typeid, impl_MagicItem::typeid, 144, gcnew array<System::UInt32> { 0x1E36F08 });
            RegisterType(modulePtr, "SpellItem", SpellItem::typeid, impl_SpellItem::typeid, 232, gcnew array<System::UInt32> { 0x1E36EC0 });
            RegisterType(modulePtr, "TESSpellList", TESSpellList::typeid, impl_TESSpellList::typeid, 16, gcnew array<System::UInt32> { 0x1E3B5E8 });
            RegisterType(modulePtr, "BGSSkinForm", BGSSkinForm::typeid, impl_BGSSkinForm::typeid, 16, gcnew array<System::UInt32> { 0x1E3B408 });
            RegisterType(modulePtr, "BGSBipedObjectForm", BGSBipedObjectForm::typeid, impl_BGSBipedObjectForm::typeid, 16, gcnew array<System::UInt32> { 0x1E3B130 });
            RegisterType(modulePtr, "BGSAttackDataForm", BGSAttackDataForm::typeid, impl_BGSAttackDataForm::typeid, 16, gcnew array<System::UInt32> { 0x1E3B0E0 });
            RegisterType(modulePtr, "TESRace", TESRace::typeid, impl_TESRace::typeid, 1208, gcnew array<System::UInt32> { 0x1E3BB10 });
            RegisterType(modulePtr, "BGSLocation", BGSLocation::typeid, impl_BGSLocation::typeid, 240, gcnew array<System::UInt32> { 0x1E3F860 });
            RegisterType(modulePtr, "DataHandler", DataHandler::typeid, impl_DataHandler::typeid, 3520, nullptr);
            RegisterType(modulePtr, "TESReactionForm", TESReactionForm::typeid, impl_TESReactionForm::typeid, 32, gcnew array<System::UInt32> { 0x1E3B610 });
            RegisterType(modulePtr, "TESFaction", TESFaction::typeid, impl_TESFaction::typeid, 256, gcnew array<System::UInt32> { 0x1E39910 });
            RegisterType(modulePtr, "TESPackage", TESPackage::typeid, impl_TESPackage::typeid, 224, gcnew array<System::UInt32> { 0x1E39878 });
            RegisterType(modulePtr, "TESRaceForm", TESRaceForm::typeid, impl_TESRaceForm::typeid, 16, gcnew array<System::UInt32> { 0x1E3B5C0 });
            RegisterType(modulePtr, "TESEnchantableForm", TESEnchantableForm::typeid, impl_TESEnchantableForm::typeid, 24, gcnew array<System::UInt32> { 0x1E37808 });
            RegisterType(modulePtr, "TESValueForm", TESValueForm::typeid, impl_TESValueForm::typeid, 16, gcnew array<System::UInt32> { 0x1E37960 });
            RegisterType(modulePtr, "BGSDestructibleObjectForm", BGSDestructibleObjectForm::typeid, impl_BGSDestructibleObjectForm::typeid, 16, gcnew array<System::UInt32> { 0x1E370D0 });
            RegisterType(modulePtr, "BGSPickupPutdownSounds", BGSPickupPutdownSounds::typeid, impl_BGSPickupPutdownSounds::typeid, 24, gcnew array<System::UInt32> { 0x1E37100 });
            RegisterType(modulePtr, "TESBipedModelForm", TESBipedModelForm::typeid, impl_TESBipedModelForm::typeid, 240, gcnew array<System::UInt32> { 0x1E3A278 });
            RegisterType(modulePtr, "BGSBlockBashData", BGSBlockBashData::typeid, impl_BGSBlockBashData::typeid, 24, gcnew array<System::UInt32> { 0x1E3B160 });
            RegisterType(modulePtr, "TESObjectARMO", TESObjectARMO::typeid, impl_TESObjectARMO::typeid, 552, gcnew array<System::UInt32> { 0x1E3B430 });
            RegisterType(modulePtr, "TESBoundAnimObject", TESBoundAnimObject::typeid, impl_TESBoundAnimObject::typeid, 48, gcnew array<System::UInt32> { 0x1E3E678 });
            RegisterType(modulePtr, "TESActorBaseData", TESActorBaseData::typeid, impl_TESActorBaseData::typeid, 88, gcnew array<System::UInt32> { 0x1E3B4A0 });
            RegisterType(modulePtr, "TESContainer", TESContainer::typeid, impl_TESContainer::typeid, 24, gcnew array<System::UInt32> { 0x1E3B4F8 });
            RegisterType(modulePtr, "TESContainer::Data", TESContainer::Data::typeid, impl_TESContainer::impl_Data::typeid, 24, nullptr);
            RegisterType(modulePtr, "TESContainer::Entry", TESContainer::Entry::typeid, impl_TESContainer::impl_Entry::typeid, 24, nullptr);
            RegisterType(modulePtr, "TESAIForm", TESAIForm::typeid, impl_TESAIForm::typeid, 40, gcnew array<System::UInt32> { 0x1E3B480 });
            RegisterType(modulePtr, "BGSPerkRankArray", BGSPerkRankArray::typeid, impl_BGSPerkRankArray::typeid, 24, gcnew array<System::UInt32> { 0x1E3B3A0 });
            RegisterType(modulePtr, "TESActorBase", TESActorBase::typeid, impl_TESActorBase::typeid, 336, gcnew array<System::UInt32> { 0x1E39960 });
            RegisterType(modulePtr, "BGSOverridePackCollection", BGSOverridePackCollection::typeid, impl_BGSOverridePackCollection::typeid, 40, gcnew array<System::UInt32> { 0x1E3B348 });
            RegisterType(modulePtr, "TESNPC", TESNPC::typeid, impl_TESNPC::typeid, 616, gcnew array<System::UInt32> { 0x1E3AC78 });
            RegisterType(modulePtr, "BGSAssociationType", BGSAssociationType::typeid, impl_BGSAssociationType::typeid, 72, gcnew array<System::UInt32> { 0x1E444F0 });
            RegisterType(modulePtr, "TESFile", TESFile::typeid, impl_TESFile::typeid, 1224, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "BSString", BSString::typeid, impl_BSString::typeid, 16, nullptr);
            RegisterType(modulePtr, "BGSOutfit", BGSOutfit::typeid, impl_BGSOutfit::typeid, 56, gcnew array<System::UInt32> { 0x1E3E3B8 });
            RegisterType(modulePtr, "BSExtraData", BSExtraData::typeid, impl_BSExtraData::typeid, 16, gcnew array<System::UInt32> { 0x1E380D0 });
            RegisterType(modulePtr, "ExtraContainerChanges", ExtraContainerChanges::typeid, impl_ExtraContainerChanges::typeid, 24, gcnew array<System::UInt32> { 0x1E39CE0 });
            RegisterType(modulePtr, "ExtraContainerChanges::Data", ExtraContainerChanges::Data::typeid, impl_ExtraContainerChanges::impl_Data::typeid, 32, nullptr);
            RegisterType(modulePtr, "ExtraContainerChanges::ItemEntry", ExtraContainerChanges::ItemEntry::typeid, impl_ExtraContainerChanges::impl_ItemEntry::typeid, 24, nullptr);
            RegisterType(modulePtr, "TESModelTextureSwap", TESModelTextureSwap::typeid, impl_TESModelTextureSwap::typeid, 56, gcnew array<System::UInt32> { 0x1E36FC0 });
            RegisterType(modulePtr, "BGSOpenCloseForm", BGSOpenCloseForm::typeid, impl_BGSOpenCloseForm::typeid, 8, gcnew array<System::UInt32> { 0x1E3E6A8 });
            RegisterType(modulePtr, "TESObjectCONT", TESObjectCONT::typeid, impl_TESObjectCONT::typeid, 208, gcnew array<System::UInt32> { 0x1E3F318 });
            RegisterType(modulePtr, "BSTDefaultScatterTable<,>", BSTDefaultScatterTable<System::Object^, IMemoryObject^>::typeid->GetGenericTypeDefinition(), impl_BSTDefaultScatterTable<System::Object^, IMemoryObject^>::typeid->GetGenericTypeDefinition(), 48, nullptr);
            RegisterType(modulePtr, "TES", TES::typeid, impl_TES::typeid, 696, gcnew array<System::UInt32> { 0x1E3A928 });
            RegisterType(modulePtr, "ICellAttachDetachEventSource", ICellAttachDetachEventSource::typeid, impl_ICellAttachDetachEventSource::typeid, 96, gcnew array<System::UInt32> { 0x1E3A820 });
            RegisterType(modulePtr, "BSTSingletonExplicit<>", BSTSingletonExplicit<System::Object^>::typeid->GetGenericTypeDefinition(), impl_BSTSingletonExplicit<System::Object^>::typeid->GetGenericTypeDefinition(), -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "BSResource", BSResource::typeid, impl_BSResource::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "BSResource::ArchiveStreamOpenedEvent", BSResource::ArchiveStreamOpenedEvent::typeid, impl_BSResource::impl_ArchiveStreamOpenedEvent::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "GridCellArray", GridCellArray::typeid, impl_GridCellArray::typeid, 48, gcnew array<System::UInt32> { 0x1E3CB68 });
            RegisterType(modulePtr, "GridArray", GridArray::typeid, impl_GridArray::typeid, 24, gcnew array<System::UInt32> { 0x1E3CB48 });
            RegisterType(modulePtr, "Mutex", Mutex::typeid, impl_Mutex::typeid, 8, nullptr);
            RegisterType(modulePtr, "TESQuest", TESQuest::typeid, impl_TESQuest::typeid, 616, gcnew array<System::UInt32> { 0x1E399A8 });
            RegisterType(modulePtr, "BGSStoryManagerTreeForm", BGSStoryManagerTreeForm::typeid, impl_BGSStoryManagerTreeForm::typeid, 40, gcnew array<System::UInt32> { 0x1E3AE18 });
            RegisterType(modulePtr, "BGSBaseAlias", BGSBaseAlias::typeid, impl_BGSBaseAlias::typeid, 40, gcnew array<System::UInt32> { 0x1E44DA0 });
            RegisterType(modulePtr, "BGSRefAlias", BGSRefAlias::typeid, impl_BGSRefAlias::typeid, 72, gcnew array<System::UInt32> { 0x1E45130 });
            RegisterType(modulePtr, "MenuManager", MenuManager::typeid, impl_MenuManager::typeid, 464, nullptr);
            RegisterType(modulePtr, "InputManager", InputManager::typeid, impl_InputManager::typeid, 296, nullptr);
            RegisterType(modulePtr, "ActorMagicCaster", ActorMagicCaster::typeid, impl_ActorMagicCaster::typeid, 256, gcnew array<System::UInt32> { 0x1E5EF58 });
            RegisterType(modulePtr, "MagicCaster", MagicCaster::typeid, impl_MagicCaster::typeid, 72, gcnew array<System::UInt32> { 0x1E43BC8 });
            RegisterType(modulePtr, "SimpleAnimationGraphManagerHolder", SimpleAnimationGraphManagerHolder::typeid, impl_SimpleAnimationGraphManagerHolder::typeid, 24, gcnew array<System::UInt32> { 0x1E5CCD8 });
            RegisterType(modulePtr, "BSLight", BSLight::typeid, impl_BSLight::typeid, 320, gcnew array<System::UInt32> { 0x1EE32A8 });
            RegisterType(modulePtr, "TESImageSpaceModifier", TESImageSpaceModifier::typeid, impl_TESImageSpaceModifier::typeid, 736, gcnew array<System::UInt32> { 0x1E37690 });
            RegisterType(modulePtr, "AutoVanityState", AutoVanityState::typeid, impl_AutoVanityState::typeid, 40, gcnew array<System::UInt32> { 0x1EA42E8 });
            RegisterType(modulePtr, "VATSCameraState", VATSCameraState::typeid, impl_VATSCameraState::typeid, 56, gcnew array<System::UInt32> { 0x1EA4428 });
            RegisterType(modulePtr, "FreeCameraState", FreeCameraState::typeid, impl_FreeCameraState::typeid, 80, gcnew array<System::UInt32> { 0x1EA4310 });
            RegisterType(modulePtr, "IronSightsState", IronSightsState::typeid, impl_IronSightsState::typeid, 40, gcnew array<System::UInt32> { 0x1EA4338 });
            RegisterType(modulePtr, "FurnitureCameraState", FurnitureCameraState::typeid, impl_FurnitureCameraState::typeid, 64, gcnew array<System::UInt32> { 0x1EA4360 });
            RegisterType(modulePtr, "PlayerCameraTransitionState", PlayerCameraTransitionState::typeid, impl_PlayerCameraTransitionState::typeid, 64, gcnew array<System::UInt32> { 0x1EA4390 });
            RegisterType(modulePtr, "TweenMenuCameraState", TweenMenuCameraState::typeid, impl_TweenMenuCameraState::typeid, 80, gcnew array<System::UInt32> { 0x1EA43F8 });
            RegisterType(modulePtr, "HorseCameraState", HorseCameraState::typeid, impl_HorseCameraState::typeid, 248, gcnew array<System::UInt32> { 0x1EA4070 });
            RegisterType(modulePtr, "BleedoutCameraState", BleedoutCameraState::typeid, impl_BleedoutCameraState::typeid, 312, gcnew array<System::UInt32> { 0x1EA43C8 });
            RegisterType(modulePtr, "DragonCameraState", DragonCameraState::typeid, impl_DragonCameraState::typeid, 272, gcnew array<System::UInt32> { 0x1E5D068 });
            RegisterType(modulePtr, "Setting", Setting::typeid, impl_Setting::typeid, 24, gcnew array<System::UInt32> { 0x1E37358 });
            RegisterType(modulePtr, "MenuScreenData", MenuScreenData::typeid, impl_MenuScreenData::typeid, 48, nullptr);
            RegisterType(modulePtr, "PlayerControls", PlayerControls::typeid, impl_PlayerControls::typeid, 480, gcnew array<System::UInt32> { 0x1E69938 });
            RegisterType(modulePtr, "InputEvent", InputEvent::typeid, impl_InputEvent::typeid, 24, gcnew array<System::UInt32> { 0x1E698A0 });
            RegisterType(modulePtr, "TESFurnitureEvent", TESFurnitureEvent::typeid, impl_TESFurnitureEvent::typeid, -1, gcnew array<System::UInt32>(0));
            RegisterType(modulePtr, "BGSConstructibleObject", BGSConstructibleObject::typeid, impl_BGSConstructibleObject::typeid, 88, gcnew array<System::UInt32> { 0x1E3DC98 });
            RegisterType(modulePtr, "NiLight", NiLight::typeid, impl_NiLight::typeid, 320, gcnew array<System::UInt32> { 0x1EC07A8 });
            RegisterType(modulePtr, "TESLeveledList", TESLeveledList::typeid, impl_TESLeveledList::typeid, 40, gcnew array<System::UInt32> { 0x1E3B548 });
            RegisterType(modulePtr, "TESLeveledList::Entry", TESLeveledList::Entry::typeid, impl_TESLeveledList::impl_Entry::typeid, 24, nullptr);
            RegisterType(modulePtr, "TESLeveledList::Entry::Data", TESLeveledList::Entry::Data::typeid, impl_TESLeveledList::impl_Entry::impl_Data::typeid, 24, nullptr);
            RegisterType(modulePtr, "TESGlobal", TESGlobal::typeid, impl_TESGlobal::typeid, 56, gcnew array<System::UInt32> { 0x1E380B0 });
            RegisterType(modulePtr, "TESLevItem", TESLevItem::typeid, impl_TESLevItem::typeid, 88, gcnew array<System::UInt32> { 0x1E3B6D8 });
            RegisterType(modulePtr, "TESLevSpell", TESLevSpell::typeid, impl_TESLevSpell::typeid, 88, gcnew array<System::UInt32> { 0x1E3BB30 });
            RegisterType(modulePtr, "TESLevCharacter", TESLevCharacter::typeid, impl_TESLevCharacter::typeid, 144, gcnew array<System::UInt32> { 0x1E3ECD0 });
            RegisterType(modulePtr, "BSTDefaultScatterTable2<,>", BSTDefaultScatterTable2<System::Object^, IMemoryObject^>::typeid->GetGenericTypeDefinition(), impl_BSTDefaultScatterTable2<System::Object^, IMemoryObject^>::typeid->GetGenericTypeDefinition(), 48, nullptr);
            RegisterType(modulePtr, "ExtraPoison", ExtraPoison::typeid, impl_ExtraPoison::typeid, 32, gcnew array<System::UInt32> { 0x1E385F8 });
            RegisterType(modulePtr, "AlchemyItem", AlchemyItem::typeid, impl_AlchemyItem::typeid, 360, gcnew array<System::UInt32> { 0x1E36EE0 });
            RegisterType(modulePtr, "BGSMessageIcon", BGSMessageIcon::typeid, impl_BGSMessageIcon::typeid, 24, gcnew array<System::UInt32> { 0x1E37058 });
            RegisterType(modulePtr, "TESObjectWEAP", TESObjectWEAP::typeid, impl_TESObjectWEAP::typeid, 544, gcnew array<System::UInt32> { 0x1E3AB68 });
            RegisterType(modulePtr, "TESAttackDamageForm", TESAttackDamageForm::typeid, impl_TESAttackDamageForm::typeid, 16, gcnew array<System::UInt32> { 0x1E3B4C8 });
            RegisterType(modulePtr, "BGSPreloadable", BGSPreloadable::typeid, impl_BGSPreloadable::typeid, 8, gcnew array<System::UInt32> { 0x1E3DE58 });
            RegisterType(modulePtr, "TESAmmo", TESAmmo::typeid, impl_TESAmmo::typeid, 296, gcnew array<System::UInt32> { 0x1E39858 });
            RegisterType(modulePtr, "BGSProjectile", BGSProjectile::typeid, impl_BGSProjectile::typeid, 312, gcnew array<System::UInt32> { 0x1E37260 });
            RegisterType(modulePtr, "CrossHairPickData", CrossHairPickData::typeid, impl_CrossHairPickData::typeid, 56, nullptr);
            RegisterType(modulePtr, "bhkSimpleShapePhantom", bhkSimpleShapePhantom::typeid, impl_bhkSimpleShapePhantom::typeid, 48, gcnew array<System::UInt32> { 0x1E411A0 });
            RegisterType(modulePtr, "bhkShapePhantom", bhkShapePhantom::typeid, impl_bhkShapePhantom::typeid, 48, gcnew array<System::UInt32> { 0x1E411D0 });
            RegisterType(modulePtr, "bhkPhantom", bhkPhantom::typeid, impl_bhkPhantom::typeid, 48, gcnew array<System::UInt32> { 0x1E40FE0 });
            RegisterType(modulePtr, "BSGeometry", BSGeometry::typeid, impl_BSGeometry::typeid, 344, gcnew array<System::UInt32> { 0x1E3E8E0 });
            RegisterType(modulePtr, "NiSkinInstance", NiSkinInstance::typeid, impl_NiSkinInstance::typeid, 136, gcnew array<System::UInt32> { 0x1EC0958 });
            RegisterType(modulePtr, "BSDismemberSkinInstance", BSDismemberSkinInstance::typeid, impl_BSDismemberSkinInstance::typeid, 160, gcnew array<System::UInt32> { 0x1EC0980 });
            
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
