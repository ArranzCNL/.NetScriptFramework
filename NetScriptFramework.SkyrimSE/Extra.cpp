#include "Extra2.h"
#include "Game.h"
#include "Interfaces.h"
#include "Constants.h"
#include "Extra.h"

namespace NetScriptFramework
{
	namespace Skyrim
	{
		void stack_base::set(int offset, NiPoint3^ vec)
		{
			set(offset, vec->X);
			set(offset + 4, vec->Y);
			set(offset + 8, vec->Z);
		}

		System::Collections::Generic::List<RayCastResult^>^ _Havok::RayCast(RayCastParameters^ p)
		{
			if (p == nullptr)
				throw gcnew System::ArgumentNullException("p");

			if (p->Cell == nullptr)
				throw gcnew System::NullReferenceException("RayCastParameters.Cell");

			auto result = gcnew System::Collections::Generic::List<RayCastResult^>();
			auto begin = p->Begin;
			auto end = p->End;

			if (begin == nullptr)
				begin = gcnew array<float>(3);
			if (end == nullptr)
				end = gcnew array<float>(3);

			auto havokWorldPtr = Memory::InvokeCdecl(MCH::FromBase(Constants::TESObjectCELL__GetHavokWorld), p->Cell->Address);
			if (havokWorldPtr == System::IntPtr::Zero)
				return result;

			const float havokWorldScale = 0.0142875f;
			customRayHitCollector collector;
			char _argsRaw[0x110];
			__int64 args = (__int64)_argsRaw;
			if ((args & 0xF) != 0)
				args += 0x10 - (args & 0xF);

			*((bool*)(args + 0x20)) = false;
			*((int*)(args + 0x24)) = 0; // this is sometimes set in specific actor or object ref cases
			*((float*)(args + 0x40)) = 1.0f;
			for (int i = 0; i < 3; i++)
				*((int*)(args + 0x44 + 4 * i)) = -1;
			*((int*)(args + 0x70)) = 0;
			*((__int64*)(args + 0x80)) = 0;

			for (int i = 0; i < 4; i++)
				*((__int64*)(args + 0xA0 + i * 8)) = 0;

			*((bool*)(args + 0xC0)) = false;

			*((float*)(args + 0)) = begin[0] * havokWorldScale;
			*((float*)(args + 4)) = begin[1] * havokWorldScale;
			*((float*)(args + 8)) = begin[2] * havokWorldScale;
			*((float*)(args + 0xC)) = 0.0f;

			*((float*)(args + 0x90)) = (end[0] - begin[0]) * havokWorldScale;
			*((float*)(args + 0x94)) = (end[1] - begin[1]) * havokWorldScale;
			*((float*)(args + 0x98)) = (end[2] - begin[2]) * havokWorldScale;
			*((float*)(args + 0x9C)) = 0.0f;

			*((void**)(args + 0xA8)) = &collector;

			auto vtable = Memory::ReadPointer(havokWorldPtr, false);
			auto func51 = Memory::ReadPointer(vtable + 0x198, false);
			System::IntPtr callfn = Memory::InvokeCdecl(func51, havokWorldPtr, System::IntPtr(args));

			/*if ((callfn.ToInt64() & 0xFF) == 0)
				return result;*/

			auto n = collector.first;
			while (n != 0)
			{
				auto r = gcnew RayCastResult();
				result->Add(r);
				r->Fraction = n->fraction;
				r->Normal = gcnew array<float>(3);
				r->Normal[0] = n->normal[0];
				r->Normal[1] = n->normal[1];
				r->Normal[2] = n->normal[2];
				r->Position = gcnew array<float>(3);
				r->Position[0] = (end[0] - begin[0]) * n->fraction + begin[0];
				r->Position[1] = (end[1] - begin[1]) * n->fraction + begin[1];
				r->Position[2] = (end[2] - begin[2]) * n->fraction + begin[2];

				System::IntPtr obj = System::IntPtr(n->obj);
				r->_hkObj = obj;
				//r->Debug = Memory::ReadUInt32(obj + 44, false) >> 16;
				/*if ((Memory::ReadUInt32(obj + 44) & 0xFFFF0000) == 0x10000) // Terrain
				{

				}
				else*/
				{
					obj = Memory::InvokeCdecl(MCH::FromBase(Constants::GetNiObjectFromHavokCollidable), obj);
				}
				r->_obj = obj;

				n = n->next;
			}

			return result;
		}

		NiAVObject^ RayCastResult::Object::get()
		{
			return MemoryObject::FromAddressSafeCast<NiAVObject^>(_obj);
		}

		RayCastResult^ RayCastResult::GetClosestResult(array<float>^ source, System::Collections::Generic::List<RayCastResult^>^ results, ... array<NiAVObject^>^ ignore)
		{
			if (source == nullptr)
				throw gcnew System::ArgumentNullException("source");

			if (source->Length != 3)
				throw gcnew System::ArgumentOutOfRangeException("source.Length");

			if (results != nullptr)
			{
				bool checkIgnore = ignore != nullptr && ignore->Length != 0;
				RayCastResult^ bestResult = nullptr;
				float bestDist = 0.0f;

				for each(RayCastResult^ r in results)
				{
					array<float>^ rpos = r->Position;
					float dx = rpos[0] - source[0];
					float dy = rpos[1] - source[1];
					float dz = rpos[2] - source[2];
					float dist = dx * dx + dy * dy + dz * dz;

					if (bestResult != nullptr && bestDist <= dist)
						continue;

					if (checkIgnore)
					{
						auto obj = r->Object;
						if (obj != nullptr)
						{
							bool ok = true;
							for (int i = 0; i < ignore->Length; i++)
							{
								auto io = (IMemoryObject^)ignore[i];
								if (io != nullptr && io->Equals(obj))
								{
									ok = false;
									break;
								}
							}
							if (!ok)
								continue;
						}
					}

					bestResult = r;
					bestDist = dist;
				}

				return bestResult;
			}

			return nullptr;
		}

		void NiObjectLoadParameters::_RequestModelDirect(NiObjectLoadParameters^ p)
		{
			System::Int32 result = 0;
			p->_alloc = Memory::Allocate(0x30, 0, false);
			Memory::WritePointer(p->_alloc->Address, System::IntPtr::Zero, false);
			Memory::WriteInt32(p->_alloc->Address + 0x10, 0, false);
			Memory::WriteInt32(p->_alloc->Address + 0x14, 3, false);
			Memory::WriteInt32(p->_alloc->Address + 0x18, 0x1010001, false);

			auto str = Memory::AllocateString(p->FileName, false);
			try
			{
				result = (System::Int32)(Memory::InvokeCdecl(MCH::FromBase(Constants::RequestModel2), str->Address, p->_alloc->Address, p->_alloc->Address + 0x10).ToInt64() & 0xFF);
			}
			finally
			{
				delete str;
			}

			if ((result != 0 && result != 6) || !p->Process())
				p->Finish();
		}

		void NiObjectLoadParameters::_RequestModelAsync(NiObjectLoadParameters^ p)
		{
			System::Int32 result = 0;
			p->_alloc = Memory::Allocate(0x30, 0, false);
			Memory::WritePointer(p->_alloc->Address, System::IntPtr::Zero, false);
			Memory::WriteInt32(p->_alloc->Address + 0x10, 0, false);
			Memory::WriteInt32(p->_alloc->Address + 0x14, 3, false);
			Memory::WriteInt32(p->_alloc->Address + 0x18, 0x1010001, false);

			auto str = Memory::AllocateString(p->FileName, false);
			try
			{
				result = (System::Int32)(Memory::InvokeCdecl(MCH::FromBase(Constants::RequestModel), str->Address, p->_alloc->Address, p->_alloc->Address + 0x10, 0).ToInt64() & 0xFF);
			}
			finally
			{
				delete str;
			}

			if (result == 0 || result == 6)
			{
				System::Threading::Monitor::Enter(_locker);
				try
				{
					_queued->Add(p);
				}
				finally
				{
					System::Threading::Monitor::Exit(_locker);
				}
				return;
			}

			p->Finish();
		}

		void NiObjectLoadParameters::_UpdateRequestModel(FrameEventArgs^ e)
		{
			System::Collections::Generic::List<NiObjectLoadParameters^>^ ls = nullptr;
			System::Threading::Monitor::Enter(_locker);
			try
			{
				if (_queued->Count == 0)
					return;

				ls = _queued;
				_queued = gcnew System::Collections::Generic::List<NiObjectLoadParameters^>();
			}
			finally
			{
				System::Threading::Monitor::Exit(_locker);
			}

			for (System::Int32 i = 0; i < ls->Count; )
			{
				auto p = ls[i];

				if (!p->Process())
				{
					i++;
					continue;
				}

				ls->RemoveAt(i);
			}

			if (ls->Count != 0)
			{
				System::Threading::Monitor::Enter(_locker);
				try
				{
					if (_queued->Count == 0)
						_queued = ls;
					else
						_queued->InsertRange(0, ls);
				}
				finally
				{
					System::Threading::Monitor::Exit(_locker);
				}
			}
		}

		bool NiObjectLoadParameters::Process()
		{
			auto ptr = Memory::ReadPointer(_alloc->Address, false);
			if (ptr != System::IntPtr::Zero)
			{
				auto prototypePtr = Memory::ReadPointer(ptr + 0x28, false);
				if (prototypePtr == System::IntPtr::Zero)
					return false;

				auto obj = MemoryObject::FromAddressSafeCast<NiObject^>(prototypePtr);
				if (obj != nullptr)
				{
					System::Int32 c = this->Count;
					for (System::Int32 i = 0; i < c; i++)
					{
						auto cloned = obj->Clone();
						if (cloned == nullptr)
							break;

						cloned->IncRef();
						_result->Add(cloned);
					}

					if (c <= 0 || c == _result->Count)
						_success = true;
				}
			}

			Finish();
			return true;
		}

		void NiObjectLoadParameters::Finish()
		{
			try
			{
				if (Callback != nullptr)
					Callback(this);
			}
			finally
			{
				Cleanup();
			}
		}

		void NiObjectLoadParameters::Cleanup()
		{
			for (System::Int32 i = 0; i < _result->Count; i++)
				_result[i]->DecRef();

			if (_alloc != nullptr)
			{
				auto ptr = Memory::ReadPointer(_alloc->Address, false);
				if (ptr != System::IntPtr::Zero)
				{
					auto db = Memory::ReadPointer(MCH::FromBase(Constants::gBSResourceEntryDB), false) + 0xD0;
					Memory::InvokeCdecl(MCH::FromBase(Constants::FreeRequestedModel), db, ptr);
				}

				delete _alloc;
				_alloc = nullptr;
			}
		}

		void KeywordCache::Initialize()
		{
			_map = gcnew System::Collections::Generic::Dictionary<System::String^, System::Collections::Generic::List<BGSKeyword^>^>();

			BSTArray<TESForm^>^ all = DataHandler::Instance->GetAllFormsByType(FormTypes::Keyword);
			if (all == nullptr)
				return;

			for each(TESForm^ form in all)
			{
				auto kw = form->As<BGSKeyword^>();
				if (kw == nullptr)
					continue;

				System::String^ text = kw->KeywordText->Text;
				if (text == nullptr)
					continue;

				text = text->ToLowerInvariant();
				System::Collections::Generic::List<BGSKeyword^>^ ls = nullptr;
				if (!_map->TryGetValue(text, ls))
				{
					ls = gcnew System::Collections::Generic::List<BGSKeyword^>();
					_map[text] = ls;
				}

				ls->Add(kw);
			}
		}

		TESForm^ TESForm::LookupFormFromFile(System::UInt32 formId, System::String^ fileName)
		{
			if (fileName == nullptr) throw gcnew System::ArgumentNullException("fileName");
			auto dataHandler = DataHandler::Instance;
			if (dataHandler == nullptr) return nullptr;
			auto alloc = Memory::AllocateString(fileName, false);
			try
			{
				auto filePtr = Memory::InvokeCdecl(MCH::FromBase(0x14016D3A0), dataHandler->Address, alloc->Address);
				if (filePtr == System::IntPtr::Zero) return nullptr;
				if ((MCH::u(Memory::InvokeCdecl(MCH::FromBase(0x14017C860), filePtr)) & 0xFF) == 0) return nullptr;
				stack10 s;
				s.set<unsigned int>(0, formId);
				Memory::InvokeCdecl(MCH::FromBase(0x14017E370), filePtr, s.ptr());
				formId = s.get<unsigned int>(0);
				return LookupFormById(formId);
			}
			finally
			{
				delete alloc;
			}
		}
	}
}
