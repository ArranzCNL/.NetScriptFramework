#pragma once
#pragma warning(push)
#pragma warning(disable : 4638)

#include "Interfaces.h"
#include "Extra.h"
#include "GameAddresses.h"

namespace NetScriptFramework
{
    namespace SkyrimSE
    {
        /// <summary>
        /// Implementation of interface <see cref="BaseFormComponent"/>.
        /// </summary>
        private ref class impl_BaseFormComponent sealed : public VirtualObject, public BaseFormComponent
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="NiRefObject"/>.
        /// </summary>
        private ref class impl_NiRefObject sealed : public VirtualObject, public NiRefObject
        {
        public:
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.IncRef"/>.
            /// </summary>
            virtual void __clrcall IncRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                Memory::InterlockedIncrement32(self->Address + 0x8, false);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.DecRef"/>.
            /// </summary>
            virtual bool __clrcall DecRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                auto result = Memory::InterlockedDecrement32(self->Address + 0x8, false);
                if(this->Is<BSHandleRefObject^>()) result = result & 0x3FF;
                if(result == 0)
                {
                    self->InvokeVTableThisCall(0, 0x8);
                    return true;
                }
                return false;
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BSHandleRefObject"/>.
        /// </summary>
        private ref class impl_BSHandleRefObject sealed : public VirtualObject, public BSHandleRefObject
        {
        public:
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.IncRef"/>.
            /// </summary>
            virtual void __clrcall IncRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                Memory::InterlockedIncrement32(self->Address + 0x8, false);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.DecRef"/>.
            /// </summary>
            virtual bool __clrcall DecRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                auto result = Memory::InterlockedDecrement32(self->Address + 0x8, false);
                if(this->Is<BSHandleRefObject^>()) result = result & 0x3FF;
                if(result == 0)
                {
                    self->InvokeVTableThisCall(0, 0x8);
                    return true;
                }
                return false;
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BSTEventSink"/>.
        /// </summary>
        generic <typename T1>
        private ref class impl_BSTEventSink sealed : public VirtualObject, public BSTEventSink<T1>
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BSAnimationGraphEvent"/>.
        /// </summary>
        private ref class impl_BSAnimationGraphEvent sealed : public MemoryObject, public BSAnimationGraphEvent
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="IAnimationGraphManagerHolder"/>.
        /// </summary>
        private ref class impl_IAnimationGraphManagerHolder sealed : public VirtualObject, public IAnimationGraphManagerHolder
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="IMovementInterface"/>.
        /// </summary>
        private ref class impl_IMovementInterface sealed : public VirtualObject, public IMovementInterface
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="IMovementState"/>.
        /// </summary>
        private ref class impl_IMovementState sealed : public VirtualObject, public IMovementState
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="ActorState"/>.
        /// </summary>
        private ref class impl_ActorState sealed : public VirtualObject, public ActorState
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BSTransformDeltaEvent"/>.
        /// </summary>
        private ref class impl_BSTransformDeltaEvent sealed : public MemoryObject, public BSTransformDeltaEvent
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="bhkCharacterMoveFinishEvent"/>.
        /// </summary>
        private ref class impl_bhkCharacterMoveFinishEvent sealed : public MemoryObject, public bhkCharacterMoveFinishEvent
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="IPostAnimationChannelUpdateFunctor"/>.
        /// </summary>
        private ref class impl_IPostAnimationChannelUpdateFunctor sealed : public VirtualObject, public IPostAnimationChannelUpdateFunctor
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="ActorValueOwner"/>.
        /// </summary>
        private ref class impl_ActorValueOwner sealed : public VirtualObject, public ActorValueOwner
        {
        public:
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.GetActorValue"/>.
            /// </summary>
            virtual System::Single __clrcall GetActorValue(ActorValueIndices id) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                return (float)self->InvokeVTableThisCallF(0, 0x8, (int)id);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.GetActorValueMax"/>.
            /// </summary>
            virtual System::Single __clrcall GetActorValueMax(ActorValueIndices id) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                return (float)self->InvokeVTableThisCallF(0, 0x10, (int)id);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.GetBaseActorValue"/>.
            /// </summary>
            virtual System::Single __clrcall GetBaseActorValue(ActorValueIndices id) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                return (float)self->InvokeVTableThisCallF(0, 0x18, (int)id);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.DamageActorValue"/>.
            /// </summary>
            virtual void __clrcall DamageActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                if(id == ActorValueIndices::Health)
                {
                    auto actor = this->As<Actor^>();
                    if(actor != nullptr)
                    {
                        auto resultPtr = actor->InvokeVTableThisCall(0, 0x2F0);
                        if((MCH::u(resultPtr) & 0xFF) != 0)
                        {
                            actor->InvokeVTableThisCall(0, 0x820, 0, amount);
                            return;
                        }
                    }
                }
                self->InvokeVTableThisCall(0, 0x30, 2, (int)id, amount);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.RestoreActorValue"/>.
            /// </summary>
            virtual void __clrcall RestoreActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto actor = this->As<Actor^>();
                if(actor == nullptr) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::ActorValueOwner_RestoreActorValue), actor->Address, (int)id, amount);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.ForceActorValue"/>.
            /// </summary>
            virtual void __clrcall ForceActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                amount -= self->GetActorValue(id);
                self->InvokeVTableThisCall(0, 0x30, 0, (int)id, amount);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.ModActorValue"/>.
            /// </summary>
            virtual void __clrcall ModActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                self->InvokeVTableThisCall(0, 0x30, 0, (int)id, amount);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.SetActorValue"/>.
            /// </summary>
            virtual void __clrcall SetActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                self->InvokeVTableThisCall(0, 0x38, (int)id, amount);
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BSFixedString"/>.
        /// </summary>
        private ref class impl_BSFixedString sealed : public MemoryObject, public BSFixedString
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="BSFixedString.Text"/>.
            /// </summary>
            virtual property System::String^ Text
            {
                System::String^ __clrcall get() sealed
                {
                    auto addr = Memory::ReadPointer(this->Address + 0x0, false);
                    return addr != System::IntPtr::Zero ? Memory::ReadString(addr, false, false) : nullptr;
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                return Text;
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BSIntrusiveRefCounted"/>.
        /// </summary>
        private ref class impl_BSIntrusiveRefCounted sealed : public VirtualObject, public BSIntrusiveRefCounted
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BSScript"/>.
        /// </summary>
        private ref class impl_BSScript sealed : public MemoryObject, public BSScript
        {
        public:
            /// <summary>
            /// Implementation of interface <see cref="BSScript.IFunction"/>.
            /// </summary>
            ref class impl_IFunction sealed : public VirtualObject, public BSScript::IFunction
            {
            public:
            };
            
            /// <summary>
            /// Implementation of interface <see cref="BSScript.NF_util"/>.
            /// </summary>
            ref class impl_NF_util sealed : public MemoryObject, public BSScript::NF_util
            {
            public:
                /// <summary>
                /// Implementation of interface <see cref="BSScript.NF_util.NativeFunctionBase"/>.
                /// </summary>
                ref class impl_NativeFunctionBase sealed : public VirtualObject, public BSScript::NF_util::NativeFunctionBase
                {
                public:
                    /// <summary>
                    /// Implementation of property <see cref="BSScript.NF_util.NativeFunctionBase.FuncName"/>.
                    /// </summary>
                    virtual property BSFixedString^ FuncName
                    {
                        BSFixedString^ __clrcall get() sealed
                        {
                            return MemoryObject::FromAddress<BSFixedString^>(this->Address + 0x10);
                        }
                    }
                    
                    /// <summary>
                    /// Implementation of property <see cref="BSScript.NF_util.NativeFunctionBase.TypeName"/>.
                    /// </summary>
                    virtual property BSFixedString^ TypeName
                    {
                        BSFixedString^ __clrcall get() sealed
                        {
                            return MemoryObject::FromAddress<BSFixedString^>(this->Address + 0x18);
                        }
                    }
                };
            };
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BSTArrayBase"/>.
        /// </summary>
        private ref class impl_BSTArrayBase sealed : public MemoryObject, public BSTArrayBase
        {
        public:
            /// <summary>
            /// Implementation of interface <see cref="BSTArrayBase.IAllocatorFunctor"/>.
            /// </summary>
            ref class impl_IAllocatorFunctor sealed : public VirtualObject, public BSTArrayBase::IAllocatorFunctor
            {
            public:
            };
            
            /// <summary>
            /// Implementation of property <see cref="BSTArrayBase.Data"/>.
            /// </summary>
            virtual property System::IntPtr Data
            {
                System::IntPtr __clrcall get() sealed
                {
                    return Memory::ReadPointer(this->Address + 0x0, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="BSTArrayBase.Capacity"/>.
            /// </summary>
            virtual property System::Int32 Capacity
            {
                System::Int32 __clrcall get() sealed
                {
                    return Memory::ReadInt32(this->Address + 0x8, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="BSTArrayBase.Count"/>.
            /// </summary>
            virtual property System::Int32 Count
            {
                System::Int32 __clrcall get() sealed
                {
                    return Memory::ReadInt32(this->Address + 0x10, false);
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="GameFunction"/>.
        /// </summary>
        private ref class impl_GameFunction sealed : public MemoryObject, public GameFunction
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="GameFunction.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto addr = Memory::ReadPointer(this->Address + 0x0, false);
                    return addr != System::IntPtr::Zero ? Memory::ReadString(addr, false, false) : nullptr;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="GameFunction.AlternateName"/>.
            /// </summary>
            virtual property System::String^ AlternateName
            {
                System::String^ __clrcall get() sealed
                {
                    auto addr = Memory::ReadPointer(this->Address + 0x8, false);
                    return addr != System::IntPtr::Zero ? Memory::ReadString(addr, false, false) : nullptr;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="GameFunction.Id"/>.
            /// </summary>
            virtual property System::Int32 Id
            {
                System::Int32 __clrcall get() sealed
                {
                    return Memory::ReadInt32(this->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="GameFunction.Description"/>.
            /// </summary>
            virtual property System::String^ Description
            {
                System::String^ __clrcall get() sealed
                {
                    auto addr = Memory::ReadPointer(this->Address + 0x18, false);
                    return addr != System::IntPtr::Zero ? Memory::ReadString(addr, false, false) : nullptr;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="GameFunction.Flags"/>.
            /// </summary>
            virtual property System::UInt32 Flags
            {
                System::UInt32 __clrcall get() sealed
                {
                    return Memory::ReadUInt32(this->Address + 0x20, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="GameFunction.Argument"/>.
            /// </summary>
            virtual property System::String^ Argument
            {
                System::String^ __clrcall get() sealed
                {
                    auto addr = Memory::ReadPointer(this->Address + 0x28, false);
                    return addr != System::IntPtr::Zero ? Memory::ReadString(addr, false, false) : nullptr;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="GameFunction.HandlerFunc"/>.
            /// </summary>
            virtual property System::IntPtr HandlerFunc
            {
                System::IntPtr __clrcall get() sealed
                {
                    return Memory::ReadPointer(this->Address + 0x30, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="GameFunction.ParserFunc"/>.
            /// </summary>
            virtual property System::IntPtr ParserFunc
            {
                System::IntPtr __clrcall get() sealed
                {
                    return Memory::ReadPointer(this->Address + 0x38, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="GameFunction.NativeFunc"/>.
            /// </summary>
            virtual property System::IntPtr NativeFunc
            {
                System::IntPtr __clrcall get() sealed
                {
                    return Memory::ReadPointer(this->Address + 0x40, false);
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="ListNode"/>.
        /// </summary>
        generic <typename T1>
        private ref class impl_ListNode sealed : public MemoryObject, public ListNode<T1>, public System::Collections::Generic::IEnumerable<T1>
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="ListNode.Item"/>.
            /// </summary>
            virtual property T1 Item
            {
                T1 __clrcall get() sealed
                {
                    System::Int32 size = NetScriptFramework::Tools::GenericMemoryHelper::SizeOf<T1>(false);
                    return NetScriptFramework::Tools::GenericMemoryHelper::FromBytes<T1>(Memory::ReadBytes(this->Address + 0x0, size, false), false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ListNode.Next"/>.
            /// </summary>
            virtual property ListNode<T1>^ Next
            {
                ListNode<T1>^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<ListNode<T1>^>(Memory::ReadPointer(this->Address + 0x8, false));
                }
            }
            
            virtual System::Collections::Generic::IEnumerator<T1>^ GetEnumerator() sealed = System::Collections::Generic::IEnumerable<T1>::GetEnumerator
            {
                return gcnew enumerator(this);
            }
            
            virtual System::Collections::IEnumerator^ GetEnumeratorBase() sealed = System::Collections::IEnumerable::GetEnumerator
            {
                return GetEnumerator();
            }
            
            private:
            ref class enumerator : public System::Collections::Generic::IEnumerator<T1>
            {
                public:
                enumerator(ListNode<T1>^ p)
                {
                    _p = p;
                    _i = nullptr;
                }
                
                virtual ~enumerator() { }
                
                initonly ListNode<T1>^ _p;
                ListNode<T1>^ _i;
                
                property T1 Current
                {
                    virtual T1 get() sealed
                    {
                        return _i->Item;
                    }
                }
                
                property System::Object^ CurrentBase
                {
                    virtual System::Object^ get() sealed = System::Collections::IEnumerator::Current::get
                    {
                        return Current;
                    }
                }
                
                virtual bool MoveNext() sealed
                {
                    if(_i == nullptr)
                        _i = _p;
                    else
                        _i = _i->Next;
                    return _i->Next != nullptr;
                }
                
                virtual void Reset() sealed
                {
                    _i = nullptr;
                }
            };
            public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="NiObject"/>.
        /// </summary>
        private ref class impl_NiObject sealed : public VirtualObject, public NiObject
        {
        public:
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.IncRef"/>.
            /// </summary>
            virtual void __clrcall IncRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                Memory::InterlockedIncrement32(self->Address + 0x8, false);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.DecRef"/>.
            /// </summary>
            virtual bool __clrcall DecRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                auto result = Memory::InterlockedDecrement32(self->Address + 0x8, false);
                if(this->Is<BSHandleRefObject^>()) result = result & 0x3FF;
                if(result == 0)
                {
                    self->InvokeVTableThisCall(0, 0x8);
                    return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiObject.Clone"/>.
            /// </summary>
            virtual NiObject^ __clrcall Clone() sealed
            {
                auto self = this;
                System::IntPtr result = System::IntPtr::Zero;
                stack100 alloc;
                alloc.set(0x18, MCH::FromBase(GameAddress::gUnkCloneValue1));
                alloc.set(0x48, MCH::FromBase(GameAddress::gUnkCloneValue2));
                alloc.set(0x60, Memory::ReadInt32(MCH::FromBase(GameAddress::gUnkCloneValue3), false));
                alloc.set(0x64, Memory::ReadUInt8(MCH::FromBase(GameAddress::gUnkCloneValue4), false));
                alloc.set(0x68, 1.0f);
                alloc.set(0x6C, 1.0f);
                alloc.set(0x70, 1.0f);
                result = Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_1), self->Address, alloc.ptr());
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_2), alloc.ptr() + 0x38);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_3), alloc.ptr() + 0x8);
                return MemoryObject::FromAddressSafeCast<NiObject^>(result);
            }
            
            
        };
        
        /// <summary>
        /// Implementation of interface <see cref="NiObjectNET"/>.
        /// </summary>
        private ref class impl_NiObjectNET sealed : public VirtualObject, public NiObjectNET
        {
        public:
            /// <summary>
            /// Implementation of method <see cref="NiObject.Clone"/>.
            /// </summary>
            virtual NiObject^ __clrcall Clone() sealed
            {
                auto self = this;
                System::IntPtr result = System::IntPtr::Zero;
                stack100 alloc;
                alloc.set(0x18, MCH::FromBase(GameAddress::gUnkCloneValue1));
                alloc.set(0x48, MCH::FromBase(GameAddress::gUnkCloneValue2));
                alloc.set(0x60, Memory::ReadInt32(MCH::FromBase(GameAddress::gUnkCloneValue3), false));
                alloc.set(0x64, Memory::ReadUInt8(MCH::FromBase(GameAddress::gUnkCloneValue4), false));
                alloc.set(0x68, 1.0f);
                alloc.set(0x6C, 1.0f);
                alloc.set(0x70, 1.0f);
                result = Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_1), self->Address, alloc.ptr());
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_2), alloc.ptr() + 0x38);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_3), alloc.ptr() + 0x8);
                return MemoryObject::FromAddressSafeCast<NiObject^>(result);
            }
            
            
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.IncRef"/>.
            /// </summary>
            virtual void __clrcall IncRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                Memory::InterlockedIncrement32(self->Address + 0x8, false);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.DecRef"/>.
            /// </summary>
            virtual bool __clrcall DecRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                auto result = Memory::InterlockedDecrement32(self->Address + 0x8, false);
                if(this->Is<BSHandleRefObject^>()) result = result & 0x3FF;
                if(result == 0)
                {
                    self->InvokeVTableThisCall(0, 0x8);
                    return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiObjectNET.Name"/>.
            /// </summary>
            virtual property BSFixedString^ Name
            {
                BSFixedString^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<BSFixedString^>(this->Address + 0x10);
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name->Text;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\"";
                return name;
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="NiPointer"/>.
        /// </summary>
        generic <typename T1>
        where T1 : NiRefObject
        private ref class impl_NiPointer sealed : public MemoryObject, public NiPointer<T1>
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="NiPointer.Target"/>.
            /// </summary>
            virtual property T1 Target
            {
                T1 __clrcall get() sealed
                {
                    auto ptr = Memory::ReadPointer(this->Address + 0x0, false);
                    if(ptr == System::IntPtr::Zero) return T1();
                    return MemoryObject::FromAddress<T1>(ptr);
                }
                void __clrcall set(T1 value) sealed
                {
                    auto prev = this->Target;
                    if(value == nullptr)
                    {
                    Memory::WritePointer(this->Address + 0x0, System::IntPtr::Zero, false);
                    }
                    else
                    {
                    value->IncRef();
                    Memory::WritePointer(this->Address + 0x0, value->Address, false);
                    }
                    if(prev != nullptr) prev->DecRef();
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="NiTArray"/>.
        /// </summary>
        generic <typename T1, typename T2>
        private ref class impl_NiTArray sealed : public VirtualObject, public NiTArray<T1, T2>, public System::Collections::Generic::IEnumerable<T1>
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="NiTArray.Data"/>.
            /// </summary>
            virtual property System::IntPtr Data
            {
                System::IntPtr __clrcall get() sealed
                {
                    return Memory::ReadPointer(this->Address + 0x8, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiTArray.Capacity"/>.
            /// </summary>
            virtual property System::UInt16 Capacity
            {
                System::UInt16 __clrcall get() sealed
                {
                    return Memory::ReadUInt16(this->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiTArray.Count"/>.
            /// </summary>
            virtual property System::UInt16 Count
            {
                System::UInt16 __clrcall get() sealed
                {
                    return Memory::ReadUInt16(this->Address + 0x12, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiTArray.GrowCount"/>.
            /// </summary>
            virtual property System::UInt16 GrowCount
            {
                System::UInt16 __clrcall get() sealed
                {
                    return Memory::ReadUInt16(this->Address + 0x16, false);
                }
                void __clrcall set(System::UInt16 value) sealed
                {
                    Memory::WriteUInt16(this->Address + 0x16, value, false);
                }
            }
            
            virtual System::Collections::Generic::IEnumerator<T1>^ GetEnumerator() sealed = System::Collections::Generic::IEnumerable<T1>::GetEnumerator
            {
                return gcnew enumerator(this);
            }
            
            virtual System::Collections::IEnumerator^ GetEnumeratorBase() sealed = System::Collections::IEnumerable::GetEnumerator
            {
                return GetEnumerator();
            }
            
            private:
            ref class enumerator : public System::Collections::Generic::IEnumerator<T1>
            {
                public:
                enumerator(NiTArray<T1, T2>^ p)
                {
                    _p = p;
                    _i = -1;
                }
                
                virtual ~enumerator() { }
                
                initonly NiTArray<T1, T2>^ _p;
                System::Int32 _i;
                
                property T1 Current
                {
                    virtual T1 get() sealed
                    {
                        return _p->default[_i];
                    }
                }
                
                property System::Object^ CurrentBase
                {
                    virtual System::Object^ get() sealed = System::Collections::IEnumerator::Current::get
                    {
                        return Current;
                    }
                }
                
                virtual bool MoveNext() sealed
                {
                    do
                    {
                        _i++;
                        if(_i >= _p->Count) break;
                        if(Memory::ReadPointer(_p->Data + System::IntPtr::Size * _i, false) != System::IntPtr::Zero) return true;
                    }
                    while(true);
                    return false;
                }
                
                virtual void Reset() sealed
                {
                    _i = -1;
                }
            };
            public:
            
            /// <summary>
            /// Implementation of property <see cref="NiTArray.default"/>.
            /// </summary>
            virtual property T1 default[System::Int32]
            {
                T1 __clrcall get(System::Int32 index) sealed
                {
                    if (index < 0)
                        throw gcnew System::IndexOutOfRangeException("The index of an array can not be negative!");
                    if (index >= (System::Int32)Count)
                        throw gcnew System::IndexOutOfRangeException("The index of an array must be less than the count of elements!");
                    
                    System::Int32 stride = NetScriptFramework::Tools::GenericMemoryHelper::SizeOf<T1>(false);
                    return NetScriptFramework::Tools::GenericMemoryHelper::FromBytes<T1>(Memory::ReadBytes(Data + stride * index, stride, false), false);
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESFullName"/>.
        /// </summary>
        private ref class impl_TESFullName sealed : public VirtualObject, public TESFullName
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESFullName.Text"/>.
            /// </summary>
            virtual property BSFixedString^ Text
            {
                BSFixedString^ __clrcall get() sealed
                {
                    auto self = this->As<TESFullName^>();
                    return MemoryObject::FromAddress<BSFixedString^>(self->Address + 0x8);
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BSExtraDataList"/>.
        /// </summary>
        private ref class impl_BSExtraDataList sealed : public MemoryObject, public BSExtraDataList
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESModel"/>.
        /// </summary>
        private ref class impl_TESModel sealed : public VirtualObject, public TESModel
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESWeightForm"/>.
        /// </summary>
        private ref class impl_TESWeightForm sealed : public VirtualObject, public TESWeightForm
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESWeightForm.Value"/>.
            /// </summary>
            virtual property System::Single Value
            {
                System::Single __clrcall get() sealed
                {
                    auto self = this->As<TESWeightForm^>();
                    return Memory::ReadFloat(self->Address + 0x8, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    auto self = this->As<TESWeightForm^>();
                    Memory::WriteFloat(self->Address + 0x8, value, false);
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="NiTNewInterface"/>.
        /// </summary>
        generic <typename T1>
        private ref class impl_NiTNewInterface sealed : public MemoryObject, public NiTNewInterface<T1>
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="NiTObjectArray"/>.
        /// </summary>
        generic <typename T1>
        private ref class impl_NiTObjectArray sealed : public VirtualObject, public NiTObjectArray<T1>
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="NiTArray.Data"/>.
            /// </summary>
            virtual property System::IntPtr Data
            {
                System::IntPtr __clrcall get() sealed
                {
                    return Memory::ReadPointer(this->Address + 0x8, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiTArray.Capacity"/>.
            /// </summary>
            virtual property System::UInt16 Capacity
            {
                System::UInt16 __clrcall get() sealed
                {
                    return Memory::ReadUInt16(this->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiTArray.Count"/>.
            /// </summary>
            virtual property System::UInt16 Count
            {
                System::UInt16 __clrcall get() sealed
                {
                    return Memory::ReadUInt16(this->Address + 0x12, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiTArray.GrowCount"/>.
            /// </summary>
            virtual property System::UInt16 GrowCount
            {
                System::UInt16 __clrcall get() sealed
                {
                    return Memory::ReadUInt16(this->Address + 0x16, false);
                }
                void __clrcall set(System::UInt16 value) sealed
                {
                    Memory::WriteUInt16(this->Address + 0x16, value, false);
                }
            }
            
            virtual System::Collections::Generic::IEnumerator<T1>^ GetEnumerator() sealed = System::Collections::Generic::IEnumerable<T1>::GetEnumerator
            {
                return gcnew enumerator(this);
            }
            
            virtual System::Collections::IEnumerator^ GetEnumeratorBase() sealed = System::Collections::IEnumerable::GetEnumerator
            {
                return GetEnumerator();
            }
            
            private:
            ref class enumerator : public System::Collections::Generic::IEnumerator<T1>
            {
                public:
                enumerator(NiTObjectArray<T1>^ p)
                {
                    _p = p;
                    _i = -1;
                }
                
                virtual ~enumerator() { }
                
                initonly NiTObjectArray<T1>^ _p;
                System::Int32 _i;
                
                property T1 Current
                {
                    virtual T1 get() sealed
                    {
                        return _p->default[_i];
                    }
                }
                
                property System::Object^ CurrentBase
                {
                    virtual System::Object^ get() sealed = System::Collections::IEnumerator::Current::get
                    {
                        return Current;
                    }
                }
                
                virtual bool MoveNext() sealed
                {
                    do
                    {
                        _i++;
                        if(_i >= _p->Count) break;
                        if(Memory::ReadPointer(_p->Data + System::IntPtr::Size * _i, false) != System::IntPtr::Zero) return true;
                    }
                    while(true);
                    return false;
                }
                
                virtual void Reset() sealed
                {
                    _i = -1;
                }
            };
            public:
            
            /// <summary>
            /// Implementation of property <see cref="NiTArray.default"/>.
            /// </summary>
            virtual property T1 default[System::Int32]
            {
                T1 __clrcall get(System::Int32 index) sealed
                {
                    if (index < 0)
                        throw gcnew System::IndexOutOfRangeException("The index of an array can not be negative!");
                    if (index >= (System::Int32)Count)
                        throw gcnew System::IndexOutOfRangeException("The index of an array must be less than the count of elements!");
                    
                    System::Int32 stride = NetScriptFramework::Tools::GenericMemoryHelper::SizeOf<T1>(false);
                    return NetScriptFramework::Tools::GenericMemoryHelper::FromBytes<T1>(Memory::ReadBytes(Data + stride * index, stride, false), false);
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="PlayerInputHandler"/>.
        /// </summary>
        private ref class impl_PlayerInputHandler sealed : public VirtualObject, public PlayerInputHandler
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="MenuOpenCloseEvent"/>.
        /// </summary>
        private ref class impl_MenuOpenCloseEvent sealed : public MemoryObject, public MenuOpenCloseEvent
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="MenuModeChangeEvent"/>.
        /// </summary>
        private ref class impl_MenuModeChangeEvent sealed : public MemoryObject, public MenuModeChangeEvent
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="UserEventEnabledEvent"/>.
        /// </summary>
        private ref class impl_UserEventEnabledEvent sealed : public MemoryObject, public UserEventEnabledEvent
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESTrackedStatsEvent"/>.
        /// </summary>
        private ref class impl_TESTrackedStatsEvent sealed : public MemoryObject, public TESTrackedStatsEvent
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BGSMenuDisplayObject"/>.
        /// </summary>
        private ref class impl_BGSMenuDisplayObject sealed : public VirtualObject, public BGSMenuDisplayObject
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BGSKeywordForm"/>.
        /// </summary>
        private ref class impl_BGSKeywordForm sealed : public VirtualObject, public BGSKeywordForm
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BSTArray"/>.
        /// </summary>
        generic <typename T1>
        private ref class impl_BSTArray sealed : public MemoryObject, public BSTArray<T1>, BSTArrayBase, public System::Collections::Generic::IEnumerable<T1>
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="BSTArrayBase.Data"/>.
            /// </summary>
            virtual property System::IntPtr Data
            {
                System::IntPtr __clrcall get() sealed
                {
                    return Memory::ReadPointer(this->Address + 0x0, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="BSTArrayBase.Capacity"/>.
            /// </summary>
            virtual property System::Int32 Capacity
            {
                System::Int32 __clrcall get() sealed
                {
                    return Memory::ReadInt32(this->Address + 0x8, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="BSTArrayBase.Count"/>.
            /// </summary>
            virtual property System::Int32 Count
            {
                System::Int32 __clrcall get() sealed
                {
                    return Memory::ReadInt32(this->Address + 0x10, false);
                }
            }
            
            virtual System::Collections::Generic::IEnumerator<T1>^ GetEnumerator() sealed = System::Collections::Generic::IEnumerable<T1>::GetEnumerator
            {
                return gcnew enumerator(this);
            }
            
            virtual System::Collections::IEnumerator^ GetEnumeratorBase() sealed = System::Collections::IEnumerable::GetEnumerator
            {
                return GetEnumerator();
            }
            
            private:
            ref class enumerator : public System::Collections::Generic::IEnumerator<T1>
            {
                public:
                enumerator(BSTArray<T1>^ p)
                {
                    _p = p;
                    _i = -1;
                }
                
                virtual ~enumerator() { }
                
                initonly BSTArray<T1>^ _p;
                System::Int32 _i;
                
                property T1 Current
                {
                    virtual T1 get() sealed
                    {
                        return _p->default[_i];
                    }
                }
                
                property System::Object^ CurrentBase
                {
                    virtual System::Object^ get() sealed = System::Collections::IEnumerator::Current::get
                    {
                        return Current;
                    }
                }
                
                virtual bool MoveNext() sealed
                {
                    _i++;
                    return _i < _p->Count;
                }
                
                virtual void Reset() sealed
                {
                    _i = -1;
                }
            };
            public:
            
            /// <summary>
            /// Implementation of property <see cref="BSTArray.default"/>.
            /// </summary>
            virtual property T1 default[System::Int32]
            {
                T1 __clrcall get(System::Int32 index) sealed
                {
                    if (index < 0)
                        throw gcnew System::IndexOutOfRangeException("The index of an array can not be negative!");
                    if (index >= Count)
                        throw gcnew System::IndexOutOfRangeException("The index of an array must be less than the count of elements!");
                    
                    System::Int32 stride = NetScriptFramework::Tools::GenericMemoryHelper::SizeOf<T1>(false);
                    return NetScriptFramework::Tools::GenericMemoryHelper::FromBytes<T1>(Memory::ReadBytes(Data + stride * index, stride, false), false);
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BSTArrayAllocatorFunctor"/>.
        /// </summary>
        generic <typename T1>
        private ref class impl_BSTArrayAllocatorFunctor sealed : public VirtualObject, public BSTArrayAllocatorFunctor<T1>
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BSTArrayHeapAllocator"/>.
        /// </summary>
        private ref class impl_BSTArrayHeapAllocator sealed : public MemoryObject, public BSTArrayHeapAllocator
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="bhkRefObject"/>.
        /// </summary>
        private ref class impl_bhkRefObject sealed : public VirtualObject, public bhkRefObject
        {
        public:
            /// <summary>
            /// Implementation of method <see cref="NiObject.Clone"/>.
            /// </summary>
            virtual NiObject^ __clrcall Clone() sealed
            {
                auto self = this;
                System::IntPtr result = System::IntPtr::Zero;
                stack100 alloc;
                alloc.set(0x18, MCH::FromBase(GameAddress::gUnkCloneValue1));
                alloc.set(0x48, MCH::FromBase(GameAddress::gUnkCloneValue2));
                alloc.set(0x60, Memory::ReadInt32(MCH::FromBase(GameAddress::gUnkCloneValue3), false));
                alloc.set(0x64, Memory::ReadUInt8(MCH::FromBase(GameAddress::gUnkCloneValue4), false));
                alloc.set(0x68, 1.0f);
                alloc.set(0x6C, 1.0f);
                alloc.set(0x70, 1.0f);
                result = Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_1), self->Address, alloc.ptr());
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_2), alloc.ptr() + 0x38);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_3), alloc.ptr() + 0x8);
                return MemoryObject::FromAddressSafeCast<NiObject^>(result);
            }
            
            
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.IncRef"/>.
            /// </summary>
            virtual void __clrcall IncRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                Memory::InterlockedIncrement32(self->Address + 0x8, false);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.DecRef"/>.
            /// </summary>
            virtual bool __clrcall DecRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                auto result = Memory::InterlockedDecrement32(self->Address + 0x8, false);
                if(this->Is<BSHandleRefObject^>()) result = result & 0x3FF;
                if(result == 0)
                {
                    self->InvokeVTableThisCall(0, 0x8);
                    return true;
                }
                return false;
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="bhkSerializable"/>.
        /// </summary>
        private ref class impl_bhkSerializable sealed : public VirtualObject, public bhkSerializable
        {
        public:
            /// <summary>
            /// Implementation of method <see cref="NiObject.Clone"/>.
            /// </summary>
            virtual NiObject^ __clrcall Clone() sealed
            {
                auto self = this;
                System::IntPtr result = System::IntPtr::Zero;
                stack100 alloc;
                alloc.set(0x18, MCH::FromBase(GameAddress::gUnkCloneValue1));
                alloc.set(0x48, MCH::FromBase(GameAddress::gUnkCloneValue2));
                alloc.set(0x60, Memory::ReadInt32(MCH::FromBase(GameAddress::gUnkCloneValue3), false));
                alloc.set(0x64, Memory::ReadUInt8(MCH::FromBase(GameAddress::gUnkCloneValue4), false));
                alloc.set(0x68, 1.0f);
                alloc.set(0x6C, 1.0f);
                alloc.set(0x70, 1.0f);
                result = Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_1), self->Address, alloc.ptr());
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_2), alloc.ptr() + 0x38);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_3), alloc.ptr() + 0x8);
                return MemoryObject::FromAddressSafeCast<NiObject^>(result);
            }
            
            
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.IncRef"/>.
            /// </summary>
            virtual void __clrcall IncRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                Memory::InterlockedIncrement32(self->Address + 0x8, false);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.DecRef"/>.
            /// </summary>
            virtual bool __clrcall DecRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                auto result = Memory::InterlockedDecrement32(self->Address + 0x8, false);
                if(this->Is<BSHandleRefObject^>()) result = result & 0x3FF;
                if(result == 0)
                {
                    self->InvokeVTableThisCall(0, 0x8);
                    return true;
                }
                return false;
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="bhkWorldObject"/>.
        /// </summary>
        private ref class impl_bhkWorldObject sealed : public VirtualObject, public bhkWorldObject
        {
        public:
            /// <summary>
            /// Implementation of method <see cref="NiObject.Clone"/>.
            /// </summary>
            virtual NiObject^ __clrcall Clone() sealed
            {
                auto self = this;
                System::IntPtr result = System::IntPtr::Zero;
                stack100 alloc;
                alloc.set(0x18, MCH::FromBase(GameAddress::gUnkCloneValue1));
                alloc.set(0x48, MCH::FromBase(GameAddress::gUnkCloneValue2));
                alloc.set(0x60, Memory::ReadInt32(MCH::FromBase(GameAddress::gUnkCloneValue3), false));
                alloc.set(0x64, Memory::ReadUInt8(MCH::FromBase(GameAddress::gUnkCloneValue4), false));
                alloc.set(0x68, 1.0f);
                alloc.set(0x6C, 1.0f);
                alloc.set(0x70, 1.0f);
                result = Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_1), self->Address, alloc.ptr());
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_2), alloc.ptr() + 0x38);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_3), alloc.ptr() + 0x8);
                return MemoryObject::FromAddressSafeCast<NiObject^>(result);
            }
            
            
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.IncRef"/>.
            /// </summary>
            virtual void __clrcall IncRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                Memory::InterlockedIncrement32(self->Address + 0x8, false);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.DecRef"/>.
            /// </summary>
            virtual bool __clrcall DecRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                auto result = Memory::InterlockedDecrement32(self->Address + 0x8, false);
                if(this->Is<BSHandleRefObject^>()) result = result & 0x3FF;
                if(result == 0)
                {
                    self->InvokeVTableThisCall(0, 0x8);
                    return true;
                }
                return false;
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="bhkEntity"/>.
        /// </summary>
        private ref class impl_bhkEntity sealed : public VirtualObject, public bhkEntity
        {
        public:
            /// <summary>
            /// Implementation of method <see cref="NiObject.Clone"/>.
            /// </summary>
            virtual NiObject^ __clrcall Clone() sealed
            {
                auto self = this;
                System::IntPtr result = System::IntPtr::Zero;
                stack100 alloc;
                alloc.set(0x18, MCH::FromBase(GameAddress::gUnkCloneValue1));
                alloc.set(0x48, MCH::FromBase(GameAddress::gUnkCloneValue2));
                alloc.set(0x60, Memory::ReadInt32(MCH::FromBase(GameAddress::gUnkCloneValue3), false));
                alloc.set(0x64, Memory::ReadUInt8(MCH::FromBase(GameAddress::gUnkCloneValue4), false));
                alloc.set(0x68, 1.0f);
                alloc.set(0x6C, 1.0f);
                alloc.set(0x70, 1.0f);
                result = Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_1), self->Address, alloc.ptr());
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_2), alloc.ptr() + 0x38);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_3), alloc.ptr() + 0x8);
                return MemoryObject::FromAddressSafeCast<NiObject^>(result);
            }
            
            
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.IncRef"/>.
            /// </summary>
            virtual void __clrcall IncRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                Memory::InterlockedIncrement32(self->Address + 0x8, false);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.DecRef"/>.
            /// </summary>
            virtual bool __clrcall DecRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                auto result = Memory::InterlockedDecrement32(self->Address + 0x8, false);
                if(this->Is<BSHandleRefObject^>()) result = result & 0x3FF;
                if(result == 0)
                {
                    self->InvokeVTableThisCall(0, 0x8);
                    return true;
                }
                return false;
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="PositionPlayerEvent"/>.
        /// </summary>
        private ref class impl_PositionPlayerEvent sealed : public MemoryObject, public PositionPlayerEvent
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BSGamerProfileEvent"/>.
        /// </summary>
        private ref class impl_BSGamerProfileEvent sealed : public MemoryObject, public BSGamerProfileEvent
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="Main"/>.
        /// </summary>
        private ref class impl_Main sealed : public VirtualObject, public Main
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="Main.PauseGameWorld"/>.
            /// </summary>
            virtual property System::Byte PauseGameWorld
            {
                System::Byte __clrcall get() sealed
                {
                    return Memory::ReadUInt8(this->Address + 0x16, false);
                }
                void __clrcall set(System::Byte value) sealed
                {
                    Memory::WriteUInt8(this->Address + 0x16, value, false);
                }
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="Main.IsGamePaused"/>.
            /// </summary>
            virtual property bool IsGamePaused
            {
                bool __clrcall get() sealed
                {
                    if(this->PauseGameWorld != 0) return true;
                    if(Memory::ReadUInt8(MCH::FromBase(GameAddress::Main_IsGamePaused_Get+2), false) != 0) return true;
                    auto menuManager = MenuManager::Instance;
                    if(menuManager != nullptr && menuManager->PauseGameCounter > 0) return true;
                    return false;
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESDescription"/>.
        /// </summary>
        private ref class impl_TESDescription sealed : public VirtualObject, public TESDescription
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESTexture"/>.
        /// </summary>
        private ref class impl_TESTexture sealed : public VirtualObject, public TESTexture
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESIcon"/>.
        /// </summary>
        private ref class impl_TESIcon sealed : public VirtualObject, public TESIcon
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BGSEquipType"/>.
        /// </summary>
        private ref class impl_BGSEquipType sealed : public VirtualObject, public BGSEquipType
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESSpellList"/>.
        /// </summary>
        private ref class impl_TESSpellList sealed : public VirtualObject, public TESSpellList
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BGSSkinForm"/>.
        /// </summary>
        private ref class impl_BGSSkinForm sealed : public VirtualObject, public BGSSkinForm
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BGSBipedObjectForm"/>.
        /// </summary>
        private ref class impl_BGSBipedObjectForm sealed : public VirtualObject, public BGSBipedObjectForm
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BGSAttackDataForm"/>.
        /// </summary>
        private ref class impl_BGSAttackDataForm sealed : public VirtualObject, public BGSAttackDataForm
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESReactionForm"/>.
        /// </summary>
        private ref class impl_TESReactionForm sealed : public VirtualObject, public TESReactionForm
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESRaceForm"/>.
        /// </summary>
        private ref class impl_TESRaceForm sealed : public VirtualObject, public TESRaceForm
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESEnchantableForm"/>.
        /// </summary>
        private ref class impl_TESEnchantableForm sealed : public VirtualObject, public TESEnchantableForm
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESValueForm"/>.
        /// </summary>
        private ref class impl_TESValueForm sealed : public VirtualObject, public TESValueForm
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BGSDestructibleObjectForm"/>.
        /// </summary>
        private ref class impl_BGSDestructibleObjectForm sealed : public VirtualObject, public BGSDestructibleObjectForm
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BGSPickupPutdownSounds"/>.
        /// </summary>
        private ref class impl_BGSPickupPutdownSounds sealed : public VirtualObject, public BGSPickupPutdownSounds
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESBipedModelForm"/>.
        /// </summary>
        private ref class impl_TESBipedModelForm sealed : public VirtualObject, public TESBipedModelForm
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BGSBlockBashData"/>.
        /// </summary>
        private ref class impl_BGSBlockBashData sealed : public VirtualObject, public BGSBlockBashData
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESActorBaseData"/>.
        /// </summary>
        private ref class impl_TESActorBaseData sealed : public VirtualObject, public TESActorBaseData
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESAIForm"/>.
        /// </summary>
        private ref class impl_TESAIForm sealed : public VirtualObject, public TESAIForm
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BGSPerkRankArray"/>.
        /// </summary>
        private ref class impl_BGSPerkRankArray sealed : public VirtualObject, public BGSPerkRankArray
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BGSOverridePackCollection"/>.
        /// </summary>
        private ref class impl_BGSOverridePackCollection sealed : public VirtualObject, public BGSOverridePackCollection
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BSString"/>.
        /// </summary>
        private ref class impl_BSString sealed : public MemoryObject, public BSString
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="BSString.Text"/>.
            /// </summary>
            virtual property System::String^ Text
            {
                System::String^ __clrcall get() sealed
                {
                    auto addr = Memory::ReadPointer(this->Address + 0x0, false);
                    return addr != System::IntPtr::Zero ? Memory::ReadString(addr, false, false) : nullptr;
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                return Text;
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BSExtraData"/>.
        /// </summary>
        private ref class impl_BSExtraData sealed : public VirtualObject, public BSExtraData
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="BSExtraData.Next"/>.
            /// </summary>
            virtual property BSExtraData^ Next
            {
                BSExtraData^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<BSExtraData^>(Memory::ReadPointer(this->Address + 0x8, false));
                }
                void __clrcall set(BSExtraData^ value) sealed
                {
                    Memory::WritePointer(this->Address + 0x8, value != nullptr ? value->Address : System::IntPtr::Zero, false);
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESModelTextureSwap"/>.
        /// </summary>
        private ref class impl_TESModelTextureSwap sealed : public VirtualObject, public TESModelTextureSwap
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BGSOpenCloseForm"/>.
        /// </summary>
        private ref class impl_BGSOpenCloseForm sealed : public VirtualObject, public BGSOpenCloseForm
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BSTDefaultScatterTable"/>.
        /// </summary>
        generic <typename T1, typename T2>
        where T2 : IMemoryObject
        private ref class impl_BSTDefaultScatterTable sealed : public MemoryObject, public BSTDefaultScatterTable<T1, T2>, public System::Collections::Generic::IEnumerable<T2>
        {
        public:
            virtual System::Collections::Generic::IEnumerator<T2>^ GetEnumerator() sealed = System::Collections::Generic::IEnumerable<T2>::GetEnumerator
            {
                return gcnew enumerator(this);
            }
            
            virtual System::Collections::IEnumerator^ GetEnumeratorBase() sealed = System::Collections::IEnumerable::GetEnumerator
            {
                return GetEnumerator();
            }
            
            private:
            ref class enumerator : public System::Collections::Generic::IEnumerator<T2>
            {
                public:
                enumerator(BSTDefaultScatterTable<T1, T2>^ p)
                {
                    _p = p;
                    this->Reset();
                }
                
                virtual ~enumerator() { }
                
                initonly BSTDefaultScatterTable<T1, T2>^ _p;
                System::IntPtr _curPtr;
                System::IntPtr _endPtr;
                bool _first;
                
                property T2 Current
                {
                    virtual T2 get() sealed
                    {
                        if(_curPtr == _endPtr) throw gcnew System::InvalidOperationException();
                        return MemoryObject::FromAddress<T2>(Memory::ReadPointer(_curPtr, false));
                    }
                }
                
                property System::Object^ CurrentBase
                {
                    virtual System::Object^ get() sealed = System::Collections::IEnumerator::Current::get
                    {
                        return Current;
                    }
                }
                
                virtual bool MoveNext() sealed
                {
                    if(_curPtr == _endPtr) return false;
                    if(_first) _first = false;
                    else _curPtr = _curPtr + 0x10;
                    while(_curPtr != _endPtr)
                    {
                        if(Memory::ReadPointer(_curPtr + 8, false) != System::IntPtr::Zero) return true;
                        _curPtr = _curPtr + 0x10;
                    }
                    return false;
                }
                
                virtual void Reset() sealed
                {
                    _first = true;
                    _curPtr = Memory::ReadPointer(_p->Address + 0x28, false);
                    _endPtr = _curPtr;
                    if(_curPtr != System::IntPtr::Zero) _endPtr = _curPtr + 0x10 * Memory::ReadInt32(_p->Address + 0xC, false);
                }
            };
            public:
            
            /// <summary>
            /// Implementation of property <see cref="BSTDefaultScatterTable.Count"/>.
            /// </summary>
            virtual property System::Int32 Count
            {
                System::Int32 __clrcall get() sealed
                {
                    int free = Memory::ReadInt32(this->Address + 0x10, false);
                    return this->Capacity - free;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="BSTDefaultScatterTable.Capacity"/>.
            /// </summary>
            virtual property System::Int32 Capacity
            {
                System::Int32 __clrcall get() sealed
                {
                    return Memory::ReadInt32(this->Address + 0xC, false);
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="ICellAttachDetachEventSource"/>.
        /// </summary>
        private ref class impl_ICellAttachDetachEventSource sealed : public VirtualObject, public ICellAttachDetachEventSource
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BSTSingletonExplicit"/>.
        /// </summary>
        generic <typename T1>
        private ref class impl_BSTSingletonExplicit sealed : public MemoryObject, public BSTSingletonExplicit<T1>
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BSResource"/>.
        /// </summary>
        private ref class impl_BSResource sealed : public MemoryObject, public BSResource
        {
        public:
            /// <summary>
            /// Implementation of interface <see cref="BSResource.ArchiveStreamOpenedEvent"/>.
            /// </summary>
            ref class impl_ArchiveStreamOpenedEvent sealed : public MemoryObject, public BSResource::ArchiveStreamOpenedEvent
            {
            public:
            };
        };
        
        /// <summary>
        /// Implementation of interface <see cref="GridArray"/>.
        /// </summary>
        private ref class impl_GridArray sealed : public VirtualObject, public GridArray
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="GridArray.Length"/>.
            /// </summary>
            virtual property System::Int32 Length
            {
                System::Int32 __clrcall get() sealed
                {
                    return Memory::ReadInt32(this->Address + 0x10, false);
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="Mutex"/>.
        /// </summary>
        private ref class impl_Mutex sealed : public MemoryObject, public Mutex
        {
        public:
            /// <summary>
            /// Implementation of method <see cref="Mutex.Lock1"/>.
            /// </summary>
            virtual void __clrcall Lock1() sealed
            {
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Mutex_Lock1), this->Address, 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Mutex.Unlock1"/>.
            /// </summary>
            virtual void __clrcall Unlock1() sealed
            {
                int curThread = Memory::GetCurrentNativeThreadId();
                int lockedThread = Memory::ReadInterlockedInt32(this->Address, false);
                if(curThread != lockedThread) return;
                int count = Memory::ReadInt32(this->Address + 4, false);
                if(count == 1)
                {
                    Memory::WriteInterlockedInt32(this->Address, 0, false);
                    Memory::WriteInterlockedInt32(this->Address + 4, 0, false);
                }
                else
                {
                    Memory::InterlockedDecrement32(this->Address + 4, false);
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="MenuManager"/>.
        /// </summary>
        private ref class impl_MenuManager sealed : public MemoryObject, public MenuManager
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="MenuManager.ShowMenus"/>.
            /// </summary>
            virtual property System::Byte ShowMenus
            {
                System::Byte __clrcall get() sealed
                {
                    return Memory::ReadUInt8(this->Address + 0x1C0, false);
                }
                void __clrcall set(System::Byte value) sealed
                {
                    Memory::WriteUInt8(this->Address + 0x1C0, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="MenuManager.PauseGameCounter"/>.
            /// </summary>
            virtual property System::Int32 PauseGameCounter
            {
                System::Int32 __clrcall get() sealed
                {
                    return Memory::ReadInt32(this->Address + 0x160, false);
                }
            }
            
            
            /// <summary>
            /// Implementation of method <see cref="MenuManager.IsMenuOpen"/>.
            /// </summary>
            virtual bool __clrcall IsMenuOpen(System::String^ name) sealed
            {
                if(name == nullptr) return false;
                StringRefHolder^ str = gcnew StringRefHolder(name);
                try
                {
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::MenuManager_IsMenuOpen), this->Address, str->AddressOf)) & 0xFF) != 0;
                }
                finally
                {
                    delete str;
                }
            }
            
        };
        
        /// <summary>
        /// Implementation of interface <see cref="InputManager"/>.
        /// </summary>
        private ref class impl_InputManager sealed : public MemoryObject, public InputManager
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="SimpleAnimationGraphManagerHolder"/>.
        /// </summary>
        private ref class impl_SimpleAnimationGraphManagerHolder sealed : public VirtualObject, public SimpleAnimationGraphManagerHolder
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BSLight"/>.
        /// </summary>
        private ref class impl_BSLight sealed : public VirtualObject, public BSLight
        {
        public:
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.IncRef"/>.
            /// </summary>
            virtual void __clrcall IncRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                Memory::InterlockedIncrement32(self->Address + 0x8, false);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.DecRef"/>.
            /// </summary>
            virtual bool __clrcall DecRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                auto result = Memory::InterlockedDecrement32(self->Address + 0x8, false);
                if(this->Is<BSHandleRefObject^>()) result = result & 0x3FF;
                if(result == 0)
                {
                    self->InvokeVTableThisCall(0, 0x8);
                    return true;
                }
                return false;
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="Setting"/>.
        /// </summary>
        private ref class impl_Setting sealed : public VirtualObject, public Setting
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="Setting.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto addr = Memory::ReadPointer(this->Address + 0x10, false);
                    return addr != System::IntPtr::Zero ? Memory::ReadString(addr, false, false) : nullptr;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Setting.Type"/>.
            /// </summary>
            virtual property SettingTypes Type
            {
                SettingTypes __clrcall get() sealed
                {
                    return (SettingTypes)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Setting_Type_Get), Memory::ReadPointer(this->Address + 0x10, false))) & 0x7FFFFFFF);
                }
            }
            
            
            /// <summary>
            /// Implementation of method <see cref="Setting.GetInt"/>.
            /// </summary>
            virtual System::Int32 __clrcall GetInt() sealed
            {
                auto t = this->Type;
                if(t == SettingTypes::Int || t == SettingTypes::UInt) return Memory::ReadInt32(this->Address + 0x8, false);
                return 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Setting.GetFloat"/>.
            /// </summary>
            virtual System::Single __clrcall GetFloat() sealed
            {
                auto t = this->Type;
                if(t == SettingTypes::Float) return Memory::ReadFloat(this->Address + 0x8, false);
                return 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Setting.GetBool"/>.
            /// </summary>
            virtual bool __clrcall GetBool() sealed
            {
                auto t = this->Type;
                if(t == SettingTypes::Bool) return Memory::ReadUInt8(this->Address + 0x8, false) != 0;
                return false;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Setting.GetString"/>.
            /// </summary>
            virtual System::String^ __clrcall GetString() sealed
            {
                auto t = this->Type;
                if(t == SettingTypes::String)
                {
                    auto ptr = Memory::ReadPointer(this->Address + 0x8, false);
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
                return nullptr;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Setting.SetBool"/>.
            /// </summary>
            virtual bool __clrcall SetBool(bool value) sealed
            {
                auto t = this->Type;
                if(t == SettingTypes::Bool)
                {
                    Memory::WriteUInt8(this->Address + 0x8, value ? 1 : 0, false);
                    return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Setting.SetInt"/>.
            /// </summary>
            virtual bool __clrcall SetInt(System::Int32 value) sealed
            {
                auto t = this->Type;
                if(t == SettingTypes::Int || t == SettingTypes::UInt)
                {
                    Memory::WriteInt32(this->Address + 0x8, value, false);
                    return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Setting.SetFloat"/>.
            /// </summary>
            virtual bool __clrcall SetFloat(System::Single value) sealed
            {
                auto t = this->Type;
                if(t == SettingTypes::Float)
                {
                    Memory::WriteFloat(this->Address + 0x8, value, false);
                    return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Setting.SetString"/>.
            /// </summary>
            virtual bool __clrcall SetString(System::String^ value) sealed
            {
                if(value == nullptr) throw gcnew System::ArgumentNullException("value");
                if(this->Type != SettingTypes::String) return false;
                auto str = Memory::AllocateString(value, false);
                try
                {
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Setting_SetString), this->Address, str->Address);
                }
                finally
                {
                    delete str;
                }
                return true;
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="MenuScreenData"/>.
        /// </summary>
        private ref class impl_MenuScreenData sealed : public MemoryObject, public MenuScreenData
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="MenuScreenData.MouseXPosition"/>.
            /// </summary>
            virtual property System::Single MouseXPosition
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0x4, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="MenuScreenData.MouseYPosition"/>.
            /// </summary>
            virtual property System::Single MouseYPosition
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0x8, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="MenuScreenData.ScreenWidth"/>.
            /// </summary>
            virtual property System::Single ScreenWidth
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="MenuScreenData.ScreenHeight"/>.
            /// </summary>
            virtual property System::Single ScreenHeight
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0x18, false);
                }
            }
            
        };
        
        /// <summary>
        /// Implementation of interface <see cref="InputEvent"/>.
        /// </summary>
        private ref class impl_InputEvent sealed : public VirtualObject, public InputEvent
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESFurnitureEvent"/>.
        /// </summary>
        private ref class impl_TESFurnitureEvent sealed : public MemoryObject, public TESFurnitureEvent
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="PlayerControls"/>.
        /// </summary>
        private ref class impl_PlayerControls sealed : public VirtualObject, public PlayerControls
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="PlayerControls.MouseMovedX"/>.
            /// </summary>
            virtual property System::Single MouseMovedX
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0x2C, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    Memory::WriteFloat(this->Address + 0x2C, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="PlayerControls.MouseMovedY"/>.
            /// </summary>
            virtual property System::Single MouseMovedY
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0x30, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    Memory::WriteFloat(this->Address + 0x30, value, false);
                }
            }
            
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BSTDefaultScatterTable2"/>.
        /// </summary>
        generic <typename T1, typename T2>
        where T2 : IMemoryObject
        private ref class impl_BSTDefaultScatterTable2 sealed : public MemoryObject, public BSTDefaultScatterTable2<T1, T2>, public System::Collections::Generic::IEnumerable<T2>
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="BSTDefaultScatterTable2.Capacity"/>.
            /// </summary>
            virtual property System::Int32 Capacity
            {
                System::Int32 __clrcall get() sealed
                {
                    return Memory::ReadInt32(this->Address + 0xC, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="BSTDefaultScatterTable2.Count"/>.
            /// </summary>
            virtual property System::Int32 Count
            {
                System::Int32 __clrcall get() sealed
                {
                    int free = Memory::ReadInt32(this->Address + 0x10, false);
                    return this->Capacity - free;
                }
            }
            
            virtual System::Collections::Generic::IEnumerator<T2>^ GetEnumerator() sealed = System::Collections::Generic::IEnumerable<T2>::GetEnumerator
            {
                return gcnew enumerator(this);
            }
            
            virtual System::Collections::IEnumerator^ GetEnumeratorBase() sealed = System::Collections::IEnumerable::GetEnumerator
            {
                return GetEnumerator();
            }
            
            private:
            ref class enumerator : public System::Collections::Generic::IEnumerator<T2>
            {
                public:
                enumerator(BSTDefaultScatterTable2<T1, T2>^ p)
                {
                    _p = p;
                    this->Reset();
                }
                
                virtual ~enumerator() { }
                
                initonly BSTDefaultScatterTable2<T1, T2>^ _p;
                System::IntPtr _curPtr;
                System::IntPtr _endPtr;
                bool _first;
                
                property T2 Current
                {
                    virtual T2 get() sealed
                    {
                        if(_curPtr == _endPtr) throw gcnew System::InvalidOperationException();
                        return MemoryObject::FromAddress<T2>(Memory::ReadPointer(_curPtr + 8, false));
                    }
                }
                
                property System::Object^ CurrentBase
                {
                    virtual System::Object^ get() sealed = System::Collections::IEnumerator::Current::get
                    {
                        return Current;
                    }
                }
                
                virtual bool MoveNext() sealed
                {
                    if(_curPtr == _endPtr) return false;
                    if(_first) _first = false;
                    else _curPtr = _curPtr + 0x18;
                    while(_curPtr != _endPtr)
                    {
                        if(Memory::ReadPointer(_curPtr + 0x10, false) != System::IntPtr::Zero) return true;
                        _curPtr = _curPtr + 0x18;
                    }
                    return false;
                }
                
                virtual void Reset() sealed
                {
                    _first = true;
                    _curPtr = Memory::ReadPointer(_p->Address + 0x28, false);
                    _endPtr = _curPtr;
                    if(_curPtr != System::IntPtr::Zero) _endPtr = _curPtr + 0x18 * Memory::ReadInt32(_p->Address + 0xC, false);
                }
            };
            public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BGSMessageIcon"/>.
        /// </summary>
        private ref class impl_BGSMessageIcon sealed : public VirtualObject, public BGSMessageIcon
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESAttackDamageForm"/>.
        /// </summary>
        private ref class impl_TESAttackDamageForm sealed : public VirtualObject, public TESAttackDamageForm
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BGSPreloadable"/>.
        /// </summary>
        private ref class impl_BGSPreloadable sealed : public VirtualObject, public BGSPreloadable
        {
        public:
        };
        
        /// <summary>
        /// Implementation of interface <see cref="bhkPhantom"/>.
        /// </summary>
        private ref class impl_bhkPhantom sealed : public VirtualObject, public bhkPhantom
        {
        public:
            /// <summary>
            /// Implementation of method <see cref="NiObject.Clone"/>.
            /// </summary>
            virtual NiObject^ __clrcall Clone() sealed
            {
                auto self = this;
                System::IntPtr result = System::IntPtr::Zero;
                stack100 alloc;
                alloc.set(0x18, MCH::FromBase(GameAddress::gUnkCloneValue1));
                alloc.set(0x48, MCH::FromBase(GameAddress::gUnkCloneValue2));
                alloc.set(0x60, Memory::ReadInt32(MCH::FromBase(GameAddress::gUnkCloneValue3), false));
                alloc.set(0x64, Memory::ReadUInt8(MCH::FromBase(GameAddress::gUnkCloneValue4), false));
                alloc.set(0x68, 1.0f);
                alloc.set(0x6C, 1.0f);
                alloc.set(0x70, 1.0f);
                result = Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_1), self->Address, alloc.ptr());
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_2), alloc.ptr() + 0x38);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_3), alloc.ptr() + 0x8);
                return MemoryObject::FromAddressSafeCast<NiObject^>(result);
            }
            
            
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.IncRef"/>.
            /// </summary>
            virtual void __clrcall IncRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                Memory::InterlockedIncrement32(self->Address + 0x8, false);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.DecRef"/>.
            /// </summary>
            virtual bool __clrcall DecRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                auto result = Memory::InterlockedDecrement32(self->Address + 0x8, false);
                if(this->Is<BSHandleRefObject^>()) result = result & 0x3FF;
                if(result == 0)
                {
                    self->InvokeVTableThisCall(0, 0x8);
                    return true;
                }
                return false;
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="bhkShapePhantom"/>.
        /// </summary>
        private ref class impl_bhkShapePhantom sealed : public VirtualObject, public bhkShapePhantom
        {
        public:
            /// <summary>
            /// Implementation of method <see cref="NiObject.Clone"/>.
            /// </summary>
            virtual NiObject^ __clrcall Clone() sealed
            {
                auto self = this;
                System::IntPtr result = System::IntPtr::Zero;
                stack100 alloc;
                alloc.set(0x18, MCH::FromBase(GameAddress::gUnkCloneValue1));
                alloc.set(0x48, MCH::FromBase(GameAddress::gUnkCloneValue2));
                alloc.set(0x60, Memory::ReadInt32(MCH::FromBase(GameAddress::gUnkCloneValue3), false));
                alloc.set(0x64, Memory::ReadUInt8(MCH::FromBase(GameAddress::gUnkCloneValue4), false));
                alloc.set(0x68, 1.0f);
                alloc.set(0x6C, 1.0f);
                alloc.set(0x70, 1.0f);
                result = Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_1), self->Address, alloc.ptr());
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_2), alloc.ptr() + 0x38);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_3), alloc.ptr() + 0x8);
                return MemoryObject::FromAddressSafeCast<NiObject^>(result);
            }
            
            
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.IncRef"/>.
            /// </summary>
            virtual void __clrcall IncRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                Memory::InterlockedIncrement32(self->Address + 0x8, false);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.DecRef"/>.
            /// </summary>
            virtual bool __clrcall DecRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                auto result = Memory::InterlockedDecrement32(self->Address + 0x8, false);
                if(this->Is<BSHandleRefObject^>()) result = result & 0x3FF;
                if(result == 0)
                {
                    self->InvokeVTableThisCall(0, 0x8);
                    return true;
                }
                return false;
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="bhkSimpleShapePhantom"/>.
        /// </summary>
        private ref class impl_bhkSimpleShapePhantom sealed : public VirtualObject, public bhkSimpleShapePhantom
        {
        public:
            /// <summary>
            /// Implementation of method <see cref="NiObject.Clone"/>.
            /// </summary>
            virtual NiObject^ __clrcall Clone() sealed
            {
                auto self = this;
                System::IntPtr result = System::IntPtr::Zero;
                stack100 alloc;
                alloc.set(0x18, MCH::FromBase(GameAddress::gUnkCloneValue1));
                alloc.set(0x48, MCH::FromBase(GameAddress::gUnkCloneValue2));
                alloc.set(0x60, Memory::ReadInt32(MCH::FromBase(GameAddress::gUnkCloneValue3), false));
                alloc.set(0x64, Memory::ReadUInt8(MCH::FromBase(GameAddress::gUnkCloneValue4), false));
                alloc.set(0x68, 1.0f);
                alloc.set(0x6C, 1.0f);
                alloc.set(0x70, 1.0f);
                result = Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_1), self->Address, alloc.ptr());
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_2), alloc.ptr() + 0x38);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_3), alloc.ptr() + 0x8);
                return MemoryObject::FromAddressSafeCast<NiObject^>(result);
            }
            
            
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.IncRef"/>.
            /// </summary>
            virtual void __clrcall IncRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                Memory::InterlockedIncrement32(self->Address + 0x8, false);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.DecRef"/>.
            /// </summary>
            virtual bool __clrcall DecRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                auto result = Memory::InterlockedDecrement32(self->Address + 0x8, false);
                if(this->Is<BSHandleRefObject^>()) result = result & 0x3FF;
                if(result == 0)
                {
                    self->InvokeVTableThisCall(0, 0x8);
                    return true;
                }
                return false;
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESFile"/>.
        /// </summary>
        private ref class impl_TESFile sealed : public MemoryObject, public TESFile
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESFile.EspIndex"/>.
            /// </summary>
            virtual property System::Byte EspIndex
            {
                System::Byte __clrcall get() sealed
                {
                    return Memory::ReadUInt8(this->Address + 0x478, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESFile.Author"/>.
            /// </summary>
            virtual property BSString^ Author
            {
                BSString^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<BSString^>(this->Address + 0x480);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESFile.Description"/>.
            /// </summary>
            virtual property BSString^ Description
            {
                BSString^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<BSString^>(this->Address + 0x490);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESFile.RecordFlags"/>.
            /// </summary>
            virtual property TESFileRecordFlags RecordFlags
            {
                TESFileRecordFlags __clrcall get() sealed
                {
                    return (TESFileRecordFlags)Memory::ReadUInt32(this->Address + 0x438, false);
                }
                void __clrcall set(TESFileRecordFlags value) sealed
                {
                    Memory::WriteUInt32(this->Address + 0x438, (System::UInt32)value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESFile.EslIndex"/>.
            /// </summary>
            virtual property System::UInt16 EslIndex
            {
                System::UInt16 __clrcall get() sealed
                {
                    return Memory::ReadUInt16(this->Address + 0x47A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESFile.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    return Memory::ReadString(this->Address + 0x58, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESFile.Index"/>.
            /// </summary>
            virtual property System::Int32 Index
            {
                System::Int32 __clrcall get() sealed
                {
                    if((this->RecordFlags & TESFileRecordFlags::ESL) != TESFileRecordFlags::None) return EslIndex;
                    return EspIndex;
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="NiSkinInstance"/>.
        /// </summary>
        private ref class impl_NiSkinInstance sealed : public VirtualObject, public NiSkinInstance
        {
        public:
            /// <summary>
            /// Implementation of method <see cref="NiObject.Clone"/>.
            /// </summary>
            virtual NiObject^ __clrcall Clone() sealed
            {
                auto self = this;
                System::IntPtr result = System::IntPtr::Zero;
                stack100 alloc;
                alloc.set(0x18, MCH::FromBase(GameAddress::gUnkCloneValue1));
                alloc.set(0x48, MCH::FromBase(GameAddress::gUnkCloneValue2));
                alloc.set(0x60, Memory::ReadInt32(MCH::FromBase(GameAddress::gUnkCloneValue3), false));
                alloc.set(0x64, Memory::ReadUInt8(MCH::FromBase(GameAddress::gUnkCloneValue4), false));
                alloc.set(0x68, 1.0f);
                alloc.set(0x6C, 1.0f);
                alloc.set(0x70, 1.0f);
                result = Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_1), self->Address, alloc.ptr());
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_2), alloc.ptr() + 0x38);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_3), alloc.ptr() + 0x8);
                return MemoryObject::FromAddressSafeCast<NiObject^>(result);
            }
            
            
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.IncRef"/>.
            /// </summary>
            virtual void __clrcall IncRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                Memory::InterlockedIncrement32(self->Address + 0x8, false);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.DecRef"/>.
            /// </summary>
            virtual bool __clrcall DecRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                auto result = Memory::InterlockedDecrement32(self->Address + 0x8, false);
                if(this->Is<BSHandleRefObject^>()) result = result & 0x3FF;
                if(result == 0)
                {
                    self->InvokeVTableThisCall(0, 0x8);
                    return true;
                }
                return false;
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BSDismemberSkinInstance"/>.
        /// </summary>
        private ref class impl_BSDismemberSkinInstance sealed : public VirtualObject, public BSDismemberSkinInstance
        {
        public:
            /// <summary>
            /// Implementation of method <see cref="NiObject.Clone"/>.
            /// </summary>
            virtual NiObject^ __clrcall Clone() sealed
            {
                auto self = this;
                System::IntPtr result = System::IntPtr::Zero;
                stack100 alloc;
                alloc.set(0x18, MCH::FromBase(GameAddress::gUnkCloneValue1));
                alloc.set(0x48, MCH::FromBase(GameAddress::gUnkCloneValue2));
                alloc.set(0x60, Memory::ReadInt32(MCH::FromBase(GameAddress::gUnkCloneValue3), false));
                alloc.set(0x64, Memory::ReadUInt8(MCH::FromBase(GameAddress::gUnkCloneValue4), false));
                alloc.set(0x68, 1.0f);
                alloc.set(0x6C, 1.0f);
                alloc.set(0x70, 1.0f);
                result = Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_1), self->Address, alloc.ptr());
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_2), alloc.ptr() + 0x38);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_3), alloc.ptr() + 0x8);
                return MemoryObject::FromAddressSafeCast<NiObject^>(result);
            }
            
            
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.IncRef"/>.
            /// </summary>
            virtual void __clrcall IncRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                Memory::InterlockedIncrement32(self->Address + 0x8, false);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.DecRef"/>.
            /// </summary>
            virtual bool __clrcall DecRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                auto result = Memory::InterlockedDecrement32(self->Address + 0x8, false);
                if(this->Is<BSHandleRefObject^>()) result = result & 0x3FF;
                if(result == 0)
                {
                    self->InvokeVTableThisCall(0, 0x8);
                    return true;
                }
                return false;
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="ActiveEffect"/>.
        /// </summary>
        private ref class impl_ActiveEffect sealed : public VirtualObject, public ActiveEffect
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="ActiveEffect.Caster"/>.
            /// </summary>
            virtual property Actor^ Caster
            {
                Actor^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<Actor^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::ActiveEffect_Caster_Get), 0, 0, self->Address));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ActiveEffect.Target"/>.
            /// </summary>
            virtual property Actor^ Target
            {
                Actor^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<Actor^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::ActiveEffect_Target_Get), 0, 0, self->Address));
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActiveEffect.Dispel"/>.
            /// </summary>
            virtual void __clrcall Dispel() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::ActiveEffect_Dispel), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of property <see cref="ActiveEffect.BaseEffect"/>.
            /// </summary>
            virtual property EffectSetting^ BaseEffect
            {
                EffectSetting^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<EffectSetting^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::ActiveEffect_BaseEffect_Get), 0, 0, self->Address));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ActiveEffect.IsInactive"/>.
            /// </summary>
            virtual property bool IsInactive
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    System::UInt32 flags = Memory::ReadUInt32(self->Address + 0x7C, false);
                    return (flags & 0x8000) != 0;
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESForm"/>.
        /// </summary>
        private ref class impl_TESForm sealed : public VirtualObject, public TESForm
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESWeather"/>.
        /// </summary>
        private ref class impl_TESWeather sealed : public VirtualObject, public TESWeather
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
        };
        
        /// <summary>
        /// Implementation of interface <see cref="EffectSetting"/>.
        /// </summary>
        private ref class impl_EffectSetting sealed : public VirtualObject, public EffectSetting
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
            
            /// <summary>
            /// Implementation of property <see cref="TESFullName.Text"/>.
            /// </summary>
            virtual property BSFixedString^ Text
            {
                BSFixedString^ __clrcall get() sealed
                {
                    auto self = this->As<TESFullName^>();
                    return MemoryObject::FromAddress<BSFixedString^>(self->Address + 0x8);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="EffectSetting.Archetype"/>.
            /// </summary>
            virtual property Archetypes Archetype
            {
                Archetypes __clrcall get() sealed
                {
                    return (Archetypes)Memory::ReadInt32(this->Address + 0xC0, false);
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BGSKeyword"/>.
        /// </summary>
        private ref class impl_BGSKeyword sealed : public VirtualObject, public BGSKeyword
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
            
            /// <summary>
            /// Implementation of property <see cref="BGSKeyword.KeywordText"/>.
            /// </summary>
            virtual property BSFixedString^ KeywordText
            {
                BSFixedString^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<BSFixedString^>(this->Address + 0x20);
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BGSPerk"/>.
        /// </summary>
        private ref class impl_BGSPerk sealed : public VirtualObject, public BGSPerk
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
            
            /// <summary>
            /// Implementation of property <see cref="TESFullName.Text"/>.
            /// </summary>
            virtual property BSFixedString^ Text
            {
                BSFixedString^ __clrcall get() sealed
                {
                    auto self = this->As<TESFullName^>();
                    return MemoryObject::FromAddress<BSFixedString^>(self->Address + 0x8);
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESWordOfPower"/>.
        /// </summary>
        private ref class impl_TESWordOfPower sealed : public VirtualObject, public TESWordOfPower
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
            
            /// <summary>
            /// Implementation of property <see cref="TESFullName.Text"/>.
            /// </summary>
            virtual property BSFixedString^ Text
            {
                BSFixedString^ __clrcall get() sealed
                {
                    auto self = this->As<TESFullName^>();
                    return MemoryObject::FromAddress<BSFixedString^>(self->Address + 0x8);
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESObject"/>.
        /// </summary>
        private ref class impl_TESObject sealed : public VirtualObject, public TESObject
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESBoundObject"/>.
        /// </summary>
        private ref class impl_TESBoundObject sealed : public VirtualObject, public TESBoundObject
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
        };
        
        /// <summary>
        /// Implementation of interface <see cref="MagicItem"/>.
        /// </summary>
        private ref class impl_MagicItem sealed : public VirtualObject, public MagicItem
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESFullName.Text"/>.
            /// </summary>
            virtual property BSFixedString^ Text
            {
                BSFixedString^ __clrcall get() sealed
                {
                    auto self = this->As<TESFullName^>();
                    return MemoryObject::FromAddress<BSFixedString^>(self->Address + 0x8);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
        };
        
        /// <summary>
        /// Implementation of interface <see cref="SpellItem"/>.
        /// </summary>
        private ref class impl_SpellItem sealed : public VirtualObject, public SpellItem
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESFullName.Text"/>.
            /// </summary>
            virtual property BSFixedString^ Text
            {
                BSFixedString^ __clrcall get() sealed
                {
                    auto self = this->As<TESFullName^>();
                    return MemoryObject::FromAddress<BSFixedString^>(self->Address + 0x8);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESShout"/>.
        /// </summary>
        private ref class impl_TESShout sealed : public VirtualObject, public TESShout
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
            
            /// <summary>
            /// Implementation of property <see cref="TESFullName.Text"/>.
            /// </summary>
            virtual property BSFixedString^ Text
            {
                BSFixedString^ __clrcall get() sealed
                {
                    auto self = this->As<TESFullName^>();
                    return MemoryObject::FromAddress<BSFixedString^>(self->Address + 0x8);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESShout.Word1"/>.
            /// </summary>
            virtual property TESWordOfPower^ Word1
            {
                TESWordOfPower^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESWordOfPower^>(Memory::ReadPointer(this->Address + 0x60, false));
                }
                void __clrcall set(TESWordOfPower^ value) sealed
                {
                    Memory::WritePointer(this->Address + 0x60, value != nullptr ? value->Address : System::IntPtr::Zero, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESShout.Spell1"/>.
            /// </summary>
            virtual property SpellItem^ Spell1
            {
                SpellItem^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<SpellItem^>(Memory::ReadPointer(this->Address + 0x68, false));
                }
                void __clrcall set(SpellItem^ value) sealed
                {
                    Memory::WritePointer(this->Address + 0x68, value != nullptr ? value->Address : System::IntPtr::Zero, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESShout.Word2"/>.
            /// </summary>
            virtual property TESWordOfPower^ Word2
            {
                TESWordOfPower^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESWordOfPower^>(Memory::ReadPointer(this->Address + 0x78, false));
                }
                void __clrcall set(TESWordOfPower^ value) sealed
                {
                    Memory::WritePointer(this->Address + 0x78, value != nullptr ? value->Address : System::IntPtr::Zero, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESShout.Spell2"/>.
            /// </summary>
            virtual property SpellItem^ Spell2
            {
                SpellItem^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<SpellItem^>(Memory::ReadPointer(this->Address + 0x80, false));
                }
                void __clrcall set(SpellItem^ value) sealed
                {
                    Memory::WritePointer(this->Address + 0x80, value != nullptr ? value->Address : System::IntPtr::Zero, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESShout.Word3"/>.
            /// </summary>
            virtual property TESWordOfPower^ Word3
            {
                TESWordOfPower^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESWordOfPower^>(Memory::ReadPointer(this->Address + 0x90, false));
                }
                void __clrcall set(TESWordOfPower^ value) sealed
                {
                    Memory::WritePointer(this->Address + 0x90, value != nullptr ? value->Address : System::IntPtr::Zero, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESShout.Spell3"/>.
            /// </summary>
            virtual property SpellItem^ Spell3
            {
                SpellItem^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<SpellItem^>(Memory::ReadPointer(this->Address + 0x98, false));
                }
                void __clrcall set(SpellItem^ value) sealed
                {
                    Memory::WritePointer(this->Address + 0x98, value != nullptr ? value->Address : System::IntPtr::Zero, false);
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESRace"/>.
        /// </summary>
        private ref class impl_TESRace sealed : public VirtualObject, public TESRace
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
            
            /// <summary>
            /// Implementation of property <see cref="TESFullName.Text"/>.
            /// </summary>
            virtual property BSFixedString^ Text
            {
                BSFixedString^ __clrcall get() sealed
                {
                    auto self = this->As<TESFullName^>();
                    return MemoryObject::FromAddress<BSFixedString^>(self->Address + 0x8);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESRace.CanHeadTrack"/>.
            /// </summary>
            virtual property bool CanHeadTrack
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    System::UInt32 flags = Memory::ReadUInt32(self->Address + 0x108, false);
                    return (flags & 0x8000) != 0;
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BGSLocation"/>.
        /// </summary>
        private ref class impl_BGSLocation sealed : public VirtualObject, public BGSLocation
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
            
            /// <summary>
            /// Implementation of property <see cref="TESFullName.Text"/>.
            /// </summary>
            virtual property BSFixedString^ Text
            {
                BSFixedString^ __clrcall get() sealed
                {
                    auto self = this->As<TESFullName^>();
                    return MemoryObject::FromAddress<BSFixedString^>(self->Address + 0x8);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="BGSLocation.ParentLocation"/>.
            /// </summary>
            virtual property BGSLocation^ ParentLocation
            {
                BGSLocation^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<BGSLocation^>(Memory::ReadPointer(this->Address + 0x48, false));
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="DataHandler"/>.
        /// </summary>
        private ref class impl_DataHandler sealed : public MemoryObject, public DataHandler
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="DataHandler.LoadedMods"/>.
            /// </summary>
            virtual property ListNode<TESFile^>^ LoadedMods
            {
                ListNode<TESFile^>^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<ListNode<TESFile^>^>(this->Address + 0xD60);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="DataHandler.GetAllFormsByType"/>.
            /// </summary>
            virtual BSTArray<TESForm^>^ __clrcall GetAllFormsByType(FormTypes type) sealed
            {
                int id = (int)type;
                if(id < 0 || id >= 0x8C) return nullptr;
                int stride = MemoryObject::SizeOf<BSTArray<TESForm^>^>();
                return MemoryObject::FromAddress<BSTArray<TESForm^>^>(this->Address + 0x10 + id * stride);
            }
            
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESFaction"/>.
        /// </summary>
        private ref class impl_TESFaction sealed : public VirtualObject, public TESFaction
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
            
            /// <summary>
            /// Implementation of property <see cref="TESFullName.Text"/>.
            /// </summary>
            virtual property BSFixedString^ Text
            {
                BSFixedString^ __clrcall get() sealed
                {
                    auto self = this->As<TESFullName^>();
                    return MemoryObject::FromAddress<BSFixedString^>(self->Address + 0x8);
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESPackage"/>.
        /// </summary>
        private ref class impl_TESPackage sealed : public VirtualObject, public TESPackage
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESObjectARMO"/>.
        /// </summary>
        private ref class impl_TESObjectARMO sealed : public VirtualObject, public TESObjectARMO
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESFullName.Text"/>.
            /// </summary>
            virtual property BSFixedString^ Text
            {
                BSFixedString^ __clrcall get() sealed
                {
                    auto self = this->As<TESFullName^>();
                    return MemoryObject::FromAddress<BSFixedString^>(self->Address + 0x8);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESWeightForm.Value"/>.
            /// </summary>
            virtual property System::Single Value
            {
                System::Single __clrcall get() sealed
                {
                    auto self = this->As<TESWeightForm^>();
                    return Memory::ReadFloat(self->Address + 0x8, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    auto self = this->As<TESWeightForm^>();
                    Memory::WriteFloat(self->Address + 0x8, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESBoundAnimObject"/>.
        /// </summary>
        private ref class impl_TESBoundAnimObject sealed : public VirtualObject, public TESBoundAnimObject
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESContainer"/>.
        /// </summary>
        private ref class impl_TESContainer sealed : public VirtualObject, public TESContainer
        {
        public:
            /// <summary>
            /// Implementation of interface <see cref="TESContainer.Data"/>.
            /// </summary>
            ref class impl_Data sealed : public MemoryObject, public TESContainer::Data
            {
            public:
            };
            
            /// <summary>
            /// Implementation of interface <see cref="TESContainer.Entry"/>.
            /// </summary>
            ref class impl_Entry sealed : public MemoryObject, public TESContainer::Entry
            {
            public:
                /// <summary>
                /// Implementation of property <see cref="TESContainer.Entry.Count"/>.
                /// </summary>
                virtual property System::Int32 Count
                {
                    System::Int32 __clrcall get() sealed
                    {
                        return Memory::ReadInt32(this->Address + 0x0, false);
                    }
                    void __clrcall set(System::Int32 value) sealed
                    {
                        Memory::WriteInt32(this->Address + 0x0, value, false);
                    }
                }
                
                /// <summary>
                /// Implementation of property <see cref="TESContainer.Entry.Item"/>.
                /// </summary>
                virtual property TESForm^ Item
                {
                    TESForm^ __clrcall get() sealed
                    {
                        return MemoryObject::FromAddress<TESForm^>(Memory::ReadPointer(this->Address + 0x8, false));
                    }
                    void __clrcall set(TESForm^ value) sealed
                    {
                        Memory::WritePointer(this->Address + 0x8, value != nullptr ? value->Address : System::IntPtr::Zero, false);
                    }
                }
                
                /// <summary>
                /// Implementation of property <see cref="TESContainer.Entry.EntryData"/>.
                /// </summary>
                virtual property TESContainer::Data^ EntryData
                {
                    TESContainer::Data^ __clrcall get() sealed
                    {
                        return MemoryObject::FromAddress<TESContainer::Data^>(Memory::ReadPointer(this->Address + 0x10, false));
                    }
                }
            };
            
            /// <summary>
            /// Implementation of property <see cref="TESContainer.ContainerEntriesCount"/>.
            /// </summary>
            virtual property System::Int32 ContainerEntriesCount
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESContainer^>();
                    return Memory::ReadInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESContainer.GetContainerEntry"/>.
            /// </summary>
            virtual TESContainer::Entry^ __clrcall GetContainerEntry(System::Int32 index) sealed
            {
                auto self = this->As<TESContainer^>();
                if(index < 0 || index >= self->ContainerEntriesCount) return nullptr;
                auto ptr = Memory::ReadPointer(self->Address + 0x8, false);
                if(ptr == System::IntPtr::Zero) return nullptr;
                ptr = ptr + index * 8;
                ptr = Memory::ReadPointer(ptr, false);
                return MemoryObject::FromAddress<TESContainer::Entry^>(ptr);
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESActorBase"/>.
        /// </summary>
        private ref class impl_TESActorBase sealed : public VirtualObject, public TESActorBase
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESContainer.ContainerEntriesCount"/>.
            /// </summary>
            virtual property System::Int32 ContainerEntriesCount
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESContainer^>();
                    return Memory::ReadInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESContainer.GetContainerEntry"/>.
            /// </summary>
            virtual TESContainer::Entry^ __clrcall GetContainerEntry(System::Int32 index) sealed
            {
                auto self = this->As<TESContainer^>();
                if(index < 0 || index >= self->ContainerEntriesCount) return nullptr;
                auto ptr = Memory::ReadPointer(self->Address + 0x8, false);
                if(ptr == System::IntPtr::Zero) return nullptr;
                ptr = ptr + index * 8;
                ptr = Memory::ReadPointer(ptr, false);
                return MemoryObject::FromAddress<TESContainer::Entry^>(ptr);
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESFullName.Text"/>.
            /// </summary>
            virtual property BSFixedString^ Text
            {
                BSFixedString^ __clrcall get() sealed
                {
                    auto self = this->As<TESFullName^>();
                    return MemoryObject::FromAddress<BSFixedString^>(self->Address + 0x8);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.GetActorValue"/>.
            /// </summary>
            virtual System::Single __clrcall GetActorValue(ActorValueIndices id) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                return (float)self->InvokeVTableThisCallF(0, 0x8, (int)id);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.GetActorValueMax"/>.
            /// </summary>
            virtual System::Single __clrcall GetActorValueMax(ActorValueIndices id) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                return (float)self->InvokeVTableThisCallF(0, 0x10, (int)id);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.GetBaseActorValue"/>.
            /// </summary>
            virtual System::Single __clrcall GetBaseActorValue(ActorValueIndices id) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                return (float)self->InvokeVTableThisCallF(0, 0x18, (int)id);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.DamageActorValue"/>.
            /// </summary>
            virtual void __clrcall DamageActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                if(id == ActorValueIndices::Health)
                {
                    auto actor = this->As<Actor^>();
                    if(actor != nullptr)
                    {
                        auto resultPtr = actor->InvokeVTableThisCall(0, 0x2F0);
                        if((MCH::u(resultPtr) & 0xFF) != 0)
                        {
                            actor->InvokeVTableThisCall(0, 0x820, 0, amount);
                            return;
                        }
                    }
                }
                self->InvokeVTableThisCall(0, 0x30, 2, (int)id, amount);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.RestoreActorValue"/>.
            /// </summary>
            virtual void __clrcall RestoreActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto actor = this->As<Actor^>();
                if(actor == nullptr) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::ActorValueOwner_RestoreActorValue), actor->Address, (int)id, amount);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.ForceActorValue"/>.
            /// </summary>
            virtual void __clrcall ForceActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                amount -= self->GetActorValue(id);
                self->InvokeVTableThisCall(0, 0x30, 0, (int)id, amount);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.ModActorValue"/>.
            /// </summary>
            virtual void __clrcall ModActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                self->InvokeVTableThisCall(0, 0x30, 0, (int)id, amount);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.SetActorValue"/>.
            /// </summary>
            virtual void __clrcall SetActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                self->InvokeVTableThisCall(0, 0x38, (int)id, amount);
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESNPC"/>.
        /// </summary>
        private ref class impl_TESNPC sealed : public VirtualObject, public TESNPC
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESContainer.ContainerEntriesCount"/>.
            /// </summary>
            virtual property System::Int32 ContainerEntriesCount
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESContainer^>();
                    return Memory::ReadInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESContainer.GetContainerEntry"/>.
            /// </summary>
            virtual TESContainer::Entry^ __clrcall GetContainerEntry(System::Int32 index) sealed
            {
                auto self = this->As<TESContainer^>();
                if(index < 0 || index >= self->ContainerEntriesCount) return nullptr;
                auto ptr = Memory::ReadPointer(self->Address + 0x8, false);
                if(ptr == System::IntPtr::Zero) return nullptr;
                ptr = ptr + index * 8;
                ptr = Memory::ReadPointer(ptr, false);
                return MemoryObject::FromAddress<TESContainer::Entry^>(ptr);
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESFullName.Text"/>.
            /// </summary>
            virtual property BSFixedString^ Text
            {
                BSFixedString^ __clrcall get() sealed
                {
                    auto self = this->As<TESFullName^>();
                    return MemoryObject::FromAddress<BSFixedString^>(self->Address + 0x8);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.GetActorValue"/>.
            /// </summary>
            virtual System::Single __clrcall GetActorValue(ActorValueIndices id) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                return (float)self->InvokeVTableThisCallF(0, 0x8, (int)id);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.GetActorValueMax"/>.
            /// </summary>
            virtual System::Single __clrcall GetActorValueMax(ActorValueIndices id) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                return (float)self->InvokeVTableThisCallF(0, 0x10, (int)id);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.GetBaseActorValue"/>.
            /// </summary>
            virtual System::Single __clrcall GetBaseActorValue(ActorValueIndices id) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                return (float)self->InvokeVTableThisCallF(0, 0x18, (int)id);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.DamageActorValue"/>.
            /// </summary>
            virtual void __clrcall DamageActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                if(id == ActorValueIndices::Health)
                {
                    auto actor = this->As<Actor^>();
                    if(actor != nullptr)
                    {
                        auto resultPtr = actor->InvokeVTableThisCall(0, 0x2F0);
                        if((MCH::u(resultPtr) & 0xFF) != 0)
                        {
                            actor->InvokeVTableThisCall(0, 0x820, 0, amount);
                            return;
                        }
                    }
                }
                self->InvokeVTableThisCall(0, 0x30, 2, (int)id, amount);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.RestoreActorValue"/>.
            /// </summary>
            virtual void __clrcall RestoreActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto actor = this->As<Actor^>();
                if(actor == nullptr) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::ActorValueOwner_RestoreActorValue), actor->Address, (int)id, amount);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.ForceActorValue"/>.
            /// </summary>
            virtual void __clrcall ForceActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                amount -= self->GetActorValue(id);
                self->InvokeVTableThisCall(0, 0x30, 0, (int)id, amount);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.ModActorValue"/>.
            /// </summary>
            virtual void __clrcall ModActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                self->InvokeVTableThisCall(0, 0x30, 0, (int)id, amount);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.SetActorValue"/>.
            /// </summary>
            virtual void __clrcall SetActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                self->InvokeVTableThisCall(0, 0x38, (int)id, amount);
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BGSAssociationType"/>.
        /// </summary>
        private ref class impl_BGSAssociationType sealed : public VirtualObject, public BGSAssociationType
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BGSOutfit"/>.
        /// </summary>
        private ref class impl_BGSOutfit sealed : public VirtualObject, public BGSOutfit
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESObjectCONT"/>.
        /// </summary>
        private ref class impl_TESObjectCONT sealed : public VirtualObject, public TESObjectCONT
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESContainer.ContainerEntriesCount"/>.
            /// </summary>
            virtual property System::Int32 ContainerEntriesCount
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESContainer^>();
                    return Memory::ReadInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESContainer.GetContainerEntry"/>.
            /// </summary>
            virtual TESContainer::Entry^ __clrcall GetContainerEntry(System::Int32 index) sealed
            {
                auto self = this->As<TESContainer^>();
                if(index < 0 || index >= self->ContainerEntriesCount) return nullptr;
                auto ptr = Memory::ReadPointer(self->Address + 0x8, false);
                if(ptr == System::IntPtr::Zero) return nullptr;
                ptr = ptr + index * 8;
                ptr = Memory::ReadPointer(ptr, false);
                return MemoryObject::FromAddress<TESContainer::Entry^>(ptr);
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESFullName.Text"/>.
            /// </summary>
            virtual property BSFixedString^ Text
            {
                BSFixedString^ __clrcall get() sealed
                {
                    auto self = this->As<TESFullName^>();
                    return MemoryObject::FromAddress<BSFixedString^>(self->Address + 0x8);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESWeightForm.Value"/>.
            /// </summary>
            virtual property System::Single Value
            {
                System::Single __clrcall get() sealed
                {
                    auto self = this->As<TESWeightForm^>();
                    return Memory::ReadFloat(self->Address + 0x8, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    auto self = this->As<TESWeightForm^>();
                    Memory::WriteFloat(self->Address + 0x8, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BGSStoryManagerTreeForm"/>.
        /// </summary>
        private ref class impl_BGSStoryManagerTreeForm sealed : public VirtualObject, public BGSStoryManagerTreeForm
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
        };
        
        /// <summary>
        /// Implementation of interface <see cref="MagicCaster"/>.
        /// </summary>
        private ref class impl_MagicCaster sealed : public VirtualObject, public MagicCaster
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="MagicCaster.CastItem"/>.
            /// </summary>
            virtual property MagicItem^ CastItem
            {
                MagicItem^ __clrcall get() sealed
                {
                    auto self = this->As<MagicCaster^>();
                    return MemoryObject::FromAddress<MagicItem^>(Memory::ReadPointer(self->Address + 0x28, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="MagicCaster.Timer"/>.
            /// </summary>
            virtual property System::Single Timer
            {
                System::Single __clrcall get() sealed
                {
                    auto self = this->As<MagicCaster^>();
                    return Memory::ReadFloat(self->Address + 0x34, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="MagicCaster.State"/>.
            /// </summary>
            virtual property MagicCastingStates State
            {
                MagicCastingStates __clrcall get() sealed
                {
                    auto self = this->As<MagicCaster^>();
                    return (MagicCastingStates)Memory::ReadInt32(self->Address + 0x30, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="MagicCaster.Cost"/>.
            /// </summary>
            virtual property System::Single Cost
            {
                System::Single __clrcall get() sealed
                {
                    auto self = this->As<MagicCaster^>();
                    return Memory::ReadFloat(self->Address + 0x38, false);
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BGSConstructibleObject"/>.
        /// </summary>
        private ref class impl_BGSConstructibleObject sealed : public VirtualObject, public BGSConstructibleObject
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
            
            /// <summary>
            /// Implementation of property <see cref="BGSConstructibleObject.CraftingStationKeyword"/>.
            /// </summary>
            virtual property BGSKeyword^ CraftingStationKeyword
            {
                BGSKeyword^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<BGSKeyword^>(Memory::ReadPointer(this->Address + 0x48, false));
                }
                void __clrcall set(BGSKeyword^ value) sealed
                {
                    Memory::WritePointer(this->Address + 0x48, value != nullptr ? value->Address : System::IntPtr::Zero, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="BGSConstructibleObject.CreatedItem"/>.
            /// </summary>
            virtual property TESForm^ CreatedItem
            {
                TESForm^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESForm^>(Memory::ReadPointer(this->Address + 0x40, false));
                }
                void __clrcall set(TESForm^ value) sealed
                {
                    Memory::WritePointer(this->Address + 0x40, value != nullptr ? value->Address : System::IntPtr::Zero, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="BGSConstructibleObject.CreatedCount"/>.
            /// </summary>
            virtual property System::Int16 CreatedCount
            {
                System::Int16 __clrcall get() sealed
                {
                    return Memory::ReadInt16(this->Address + 0x50, false);
                }
                void __clrcall set(System::Int16 value) sealed
                {
                    Memory::WriteInt16(this->Address + 0x50, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="BGSConstructibleObject.Requirements"/>.
            /// </summary>
            virtual property TESContainer^ Requirements
            {
                TESContainer^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESContainer^>(this->Address + 0x20);
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESGlobal"/>.
        /// </summary>
        private ref class impl_TESGlobal sealed : public VirtualObject, public TESGlobal
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESLeveledList"/>.
        /// </summary>
        private ref class impl_TESLeveledList sealed : public VirtualObject, public TESLeveledList
        {
        public:
            /// <summary>
            /// Implementation of interface <see cref="TESLeveledList.Entry"/>.
            /// </summary>
            ref class impl_Entry sealed : public MemoryObject, public TESLeveledList::Entry
            {
            public:
                /// <summary>
                /// Implementation of interface <see cref="TESLeveledList.Entry.Data"/>.
                /// </summary>
                ref class impl_Data sealed : public MemoryObject, public TESLeveledList::Entry::Data
                {
                public:
                    /// <summary>
                    /// Implementation of property <see cref="TESLeveledList.Entry.Data.Owner"/>.
                    /// </summary>
                    virtual property TESForm^ Owner
                    {
                        TESForm^ __clrcall get() sealed
                        {
                            return MemoryObject::FromAddress<TESForm^>(Memory::ReadPointer(this->Address + 0x0, false));
                        }
                        void __clrcall set(TESForm^ value) sealed
                        {
                            Memory::WritePointer(this->Address + 0x0, value != nullptr ? value->Address : System::IntPtr::Zero, false);
                        }
                    }
                    
                    /// <summary>
                    /// Implementation of property <see cref="TESLeveledList.Entry.Data.Health"/>.
                    /// </summary>
                    virtual property System::Single Health
                    {
                        System::Single __clrcall get() sealed
                        {
                            return Memory::ReadFloat(this->Address + 0x10, false);
                        }
                        void __clrcall set(System::Single value) sealed
                        {
                            Memory::WriteFloat(this->Address + 0x10, value, false);
                        }
                    }
                    
                    /// <summary>
                    /// Implementation of property <see cref="TESLeveledList.Entry.Data.Global"/>.
                    /// </summary>
                    virtual property TESGlobal^ Global
                    {
                        TESGlobal^ __clrcall get() sealed
                        {
                            auto self = this;
                            auto owner = this->Owner;
                            if(owner == nullptr || !owner->Is<TESNPC^>()) return nullptr;
                            auto ptr = Memory::ReadPointer(self->Address + 0x8, false);
                            if(MCH::u(ptr) == 0xFFFFFFFF) return nullptr;
                            return MemoryObject::FromAddress<TESGlobal^>(ptr);
                        }
                        void __clrcall set(TESGlobal^ value) sealed
                        {
                            auto self = this;
                            auto owner = this->Owner;
                            if(owner == nullptr || !owner->Is<TESNPC^>()) return;
                            Memory::WritePointer(self->Address + 0x8, value != nullptr ? value->Address : System::IntPtr::Zero, false);
                        }
                    }
                    
                    /// <summary>
                    /// Implementation of property <see cref="TESLeveledList.Entry.Data.RequiredRank"/>.
                    /// </summary>
                    virtual property System::Int32 RequiredRank
                    {
                        System::Int32 __clrcall get() sealed
                        {
                            auto self = this;
                            auto owner = this->Owner;
                            if(owner == nullptr || !owner->Is<TESFaction^>()) return -1;
                            return Memory::ReadInt32(self->Address + 0x8, false);
                        }
                        void __clrcall set(System::Int32 value) sealed
                        {
                            auto self = this;
                            auto owner = this->Owner;
                            if(owner == nullptr || !owner->Is<TESFaction^>()) return;
                            Memory::WriteInt32(self->Address + 0x8, value, false);
                        }
                    }
                };
                
                /// <summary>
                /// Implementation of property <see cref="TESLeveledList.Entry.Form"/>.
                /// </summary>
                virtual property TESForm^ Form
                {
                    TESForm^ __clrcall get() sealed
                    {
                        return MemoryObject::FromAddress<TESForm^>(Memory::ReadPointer(this->Address + 0x0, false));
                    }
                    void __clrcall set(TESForm^ value) sealed
                    {
                        Memory::WritePointer(this->Address + 0x0, value != nullptr ? value->Address : System::IntPtr::Zero, false);
                    }
                }
                
                /// <summary>
                /// Implementation of property <see cref="TESLeveledList.Entry.Count"/>.
                /// </summary>
                virtual property System::Int16 Count
                {
                    System::Int16 __clrcall get() sealed
                    {
                        return Memory::ReadInt16(this->Address + 0x8, false);
                    }
                    void __clrcall set(System::Int16 value) sealed
                    {
                        Memory::WriteInt16(this->Address + 0x8, value, false);
                    }
                }
                
                /// <summary>
                /// Implementation of property <see cref="TESLeveledList.Entry.Level"/>.
                /// </summary>
                virtual property System::Int16 Level
                {
                    System::Int16 __clrcall get() sealed
                    {
                        return Memory::ReadInt16(this->Address + 0xA, false);
                    }
                    void __clrcall set(System::Int16 value) sealed
                    {
                        Memory::WriteInt16(this->Address + 0xA, value, false);
                    }
                }
                
                /// <summary>
                /// Implementation of property <see cref="TESLeveledList.Entry.Extra"/>.
                /// </summary>
                virtual property TESLeveledList::Entry::Data^ Extra
                {
                    TESLeveledList::Entry::Data^ __clrcall get() sealed
                    {
                        return MemoryObject::FromAddress<TESLeveledList::Entry::Data^>(Memory::ReadPointer(this->Address + 0x10, false));
                    }
                    void __clrcall set(TESLeveledList::Entry::Data^ value) sealed
                    {
                        Memory::WritePointer(this->Address + 0x10, value != nullptr ? value->Address : System::IntPtr::Zero, false);
                    }
                }
            };
            
            /// <summary>
            /// Implementation of property <see cref="TESLeveledList.LeveledListEntriesArray"/>.
            /// </summary>
            virtual property System::IntPtr LeveledListEntriesArray
            {
                System::IntPtr __clrcall get() sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    return Memory::ReadPointer(self->Address + 0x8, false);
                }
                void __clrcall set(System::IntPtr value) sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    Memory::WritePointer(self->Address + 0x8, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESLeveledList.LeveledListSkipChance"/>.
            /// </summary>
            virtual property System::Byte LeveledListSkipChance
            {
                System::Byte __clrcall get() sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    return Memory::ReadUInt8(self->Address + 0x10, false);
                }
                void __clrcall set(System::Byte value) sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    Memory::WriteUInt8(self->Address + 0x10, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESLeveledList.LeveledListFlagsValue"/>.
            /// </summary>
            virtual property TESLeveledListFlags LeveledListFlagsValue
            {
                TESLeveledListFlags __clrcall get() sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    return (TESLeveledListFlags)Memory::ReadUInt8(self->Address + 0x11, false);
                }
                void __clrcall set(TESLeveledListFlags value) sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    Memory::WriteUInt8(self->Address + 0x11, (System::Byte)value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESLeveledList.LeveledListEntriesCount"/>.
            /// </summary>
            virtual property System::Byte LeveledListEntriesCount
            {
                System::Byte __clrcall get() sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    return Memory::ReadUInt8(self->Address + 0x12, false);
                }
                void __clrcall set(System::Byte value) sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    Memory::WriteUInt8(self->Address + 0x12, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESLeveledList.LeveledListSkipChanceGlobal"/>.
            /// </summary>
            virtual property TESGlobal^ LeveledListSkipChanceGlobal
            {
                TESGlobal^ __clrcall get() sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    return MemoryObject::FromAddress<TESGlobal^>(Memory::ReadPointer(self->Address + 0x20, false));
                }
                void __clrcall set(TESGlobal^ value) sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    Memory::WritePointer(self->Address + 0x20, value != nullptr ? value->Address : System::IntPtr::Zero, false);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESLeveledList.GetLeveledListEntry"/>.
            /// </summary>
            virtual TESLeveledList::Entry^ __clrcall GetLeveledListEntry(System::Int32 index) sealed
            {
                int max = this->LeveledListEntriesCount;
                if(index < 0 || index >= max) return nullptr;
                auto ptr = this->LeveledListEntriesArray;
                if(ptr == System::IntPtr::Zero) return nullptr;
                ptr = ptr + MemoryObject::SizeOf<TESLeveledList::Entry^>() * index;
                return MemoryObject::FromAddress<TESLeveledList::Entry^>(ptr);
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESLeveledList.GetLeveledListEntries"/>.
            /// </summary>
            /// <returns></returns>
            virtual System::Collections::Generic::List<TESLeveledList::Entry^>^ __clrcall GetLeveledListEntries() sealed
            {
                	auto ptr = this->LeveledListEntriesArray;
                	if (ptr == System::IntPtr::Zero) return nullptr;
                
                	int max = this->LeveledListEntriesCount;
                	int size = MemoryObject::SizeOf<TESLeveledList::Entry^>();
                	auto ls = gcnew System::Collections::Generic::List<TESLeveledList::Entry^>(System::Math::Min(32, max));
                	for (int i = 0; i < max; i++)
                	{
                		auto obj = MemoryObject::FromAddress<TESLeveledList::Entry^>(ptr);
                		ls->Add(obj);
                		ptr = ptr + size;
                	}
                	return ls;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESLeveledList.SetLeveledListEntries"/>.
            /// </summary>
            /// <param name="entries">The entries.</param>
            virtual void __clrcall SetLeveledListEntries(System::Collections::Generic::IReadOnlyList<TESLeveledList::Entry^>^ entries) sealed
            {
                	if (entries != nullptr && entries->Count > 255)
                		throw gcnew System::ArgumentOutOfRangeException("Unable to create leveled list array with more than 255 entries!");
                
                	auto ptr2 = this->LeveledListEntriesArray;
                    auto old = this->GetLeveledListEntries();
                
                	if (entries != nullptr)
                    {
                	int size = MemoryObject::SizeOf<TESLeveledList::Entry^>();
                	auto ptr = Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESLeveledList_SetLeveledListEntries_1), MCH::FromBase(GameAddress::GameAddress::gMemoryManager), size * entries->Count + 8, 0);
                	Memory::WriteInt64(ptr, entries->Count, false);
                	ptr = ptr + 8;
                	for (int i = 0; i < entries->Count; i++)
                	{
                		auto cur = MemoryObject::FromAddress<TESLeveledList::Entry^>(ptr + size * i);
                		auto e = entries[i];
                		if (e == nullptr)
                		{
                			cur->Form = nullptr;
                			cur->Count = 1;
                			cur->Level = 1;
                			Memory::WriteUInt64(cur->Address + 0x10, 0, false);
                		}
                		else
                		{
                			cur->CopyFrom(e);
                		}
                	}
                
                	this->LeveledListEntriesArray = ptr;
                	this->LeveledListEntriesCount = (System::Byte)entries->Count;
                    }
                    else
                    {
                        this->LeveledListEntriesArray = System::IntPtr::Zero;
                	    this->LeveledListEntriesCount = 0;
                    }
                	if (ptr2 != System::IntPtr::Zero)
                {
                    for each(auto ent in old)
                    {
                        auto data = ent->Extra;
                        if(data != nullptr) Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESLeveledList_SetLeveledListEntries_2), MCH::FromBase(GameAddress::GameAddress::gMemoryManager), data->Address, 0);
                    }
                    		Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESLeveledList_SetLeveledListEntries_2), MCH::FromBase(GameAddress::GameAddress::gMemoryManager), ptr2 - 8, 0);
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESLevItem"/>.
        /// </summary>
        private ref class impl_TESLevItem sealed : public VirtualObject, public TESLevItem
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESLeveledList.LeveledListEntriesArray"/>.
            /// </summary>
            virtual property System::IntPtr LeveledListEntriesArray
            {
                System::IntPtr __clrcall get() sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    return Memory::ReadPointer(self->Address + 0x8, false);
                }
                void __clrcall set(System::IntPtr value) sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    Memory::WritePointer(self->Address + 0x8, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESLeveledList.LeveledListSkipChance"/>.
            /// </summary>
            virtual property System::Byte LeveledListSkipChance
            {
                System::Byte __clrcall get() sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    return Memory::ReadUInt8(self->Address + 0x10, false);
                }
                void __clrcall set(System::Byte value) sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    Memory::WriteUInt8(self->Address + 0x10, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESLeveledList.LeveledListFlagsValue"/>.
            /// </summary>
            virtual property TESLeveledListFlags LeveledListFlagsValue
            {
                TESLeveledListFlags __clrcall get() sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    return (TESLeveledListFlags)Memory::ReadUInt8(self->Address + 0x11, false);
                }
                void __clrcall set(TESLeveledListFlags value) sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    Memory::WriteUInt8(self->Address + 0x11, (System::Byte)value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESLeveledList.LeveledListEntriesCount"/>.
            /// </summary>
            virtual property System::Byte LeveledListEntriesCount
            {
                System::Byte __clrcall get() sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    return Memory::ReadUInt8(self->Address + 0x12, false);
                }
                void __clrcall set(System::Byte value) sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    Memory::WriteUInt8(self->Address + 0x12, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESLeveledList.LeveledListSkipChanceGlobal"/>.
            /// </summary>
            virtual property TESGlobal^ LeveledListSkipChanceGlobal
            {
                TESGlobal^ __clrcall get() sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    return MemoryObject::FromAddress<TESGlobal^>(Memory::ReadPointer(self->Address + 0x20, false));
                }
                void __clrcall set(TESGlobal^ value) sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    Memory::WritePointer(self->Address + 0x20, value != nullptr ? value->Address : System::IntPtr::Zero, false);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESLeveledList.GetLeveledListEntry"/>.
            /// </summary>
            virtual TESLeveledList::Entry^ __clrcall GetLeveledListEntry(System::Int32 index) sealed
            {
                int max = this->LeveledListEntriesCount;
                if(index < 0 || index >= max) return nullptr;
                auto ptr = this->LeveledListEntriesArray;
                if(ptr == System::IntPtr::Zero) return nullptr;
                ptr = ptr + MemoryObject::SizeOf<TESLeveledList::Entry^>() * index;
                return MemoryObject::FromAddress<TESLeveledList::Entry^>(ptr);
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESLeveledList.GetLeveledListEntries"/>.
            /// </summary>
            /// <returns></returns>
            virtual System::Collections::Generic::List<TESLeveledList::Entry^>^ __clrcall GetLeveledListEntries() sealed
            {
                	auto ptr = this->LeveledListEntriesArray;
                	if (ptr == System::IntPtr::Zero) return nullptr;
                
                	int max = this->LeveledListEntriesCount;
                	int size = MemoryObject::SizeOf<TESLeveledList::Entry^>();
                	auto ls = gcnew System::Collections::Generic::List<TESLeveledList::Entry^>(System::Math::Min(32, max));
                	for (int i = 0; i < max; i++)
                	{
                		auto obj = MemoryObject::FromAddress<TESLeveledList::Entry^>(ptr);
                		ls->Add(obj);
                		ptr = ptr + size;
                	}
                	return ls;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESLeveledList.SetLeveledListEntries"/>.
            /// </summary>
            /// <param name="entries">The entries.</param>
            virtual void __clrcall SetLeveledListEntries(System::Collections::Generic::IReadOnlyList<TESLeveledList::Entry^>^ entries) sealed
            {
                	if (entries != nullptr && entries->Count > 255)
                		throw gcnew System::ArgumentOutOfRangeException("Unable to create leveled list array with more than 255 entries!");
                
                	auto ptr2 = this->LeveledListEntriesArray;
                    auto old = this->GetLeveledListEntries();
                
                	if (entries != nullptr)
                    {
                	int size = MemoryObject::SizeOf<TESLeveledList::Entry^>();
                	auto ptr = Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESLeveledList_SetLeveledListEntries_1), MCH::FromBase(GameAddress::GameAddress::gMemoryManager), size * entries->Count + 8, 0);
                	Memory::WriteInt64(ptr, entries->Count, false);
                	ptr = ptr + 8;
                	for (int i = 0; i < entries->Count; i++)
                	{
                		auto cur = MemoryObject::FromAddress<TESLeveledList::Entry^>(ptr + size * i);
                		auto e = entries[i];
                		if (e == nullptr)
                		{
                			cur->Form = nullptr;
                			cur->Count = 1;
                			cur->Level = 1;
                			Memory::WriteUInt64(cur->Address + 0x10, 0, false);
                		}
                		else
                		{
                			cur->CopyFrom(e);
                		}
                	}
                
                	this->LeveledListEntriesArray = ptr;
                	this->LeveledListEntriesCount = (System::Byte)entries->Count;
                    }
                    else
                    {
                        this->LeveledListEntriesArray = System::IntPtr::Zero;
                	    this->LeveledListEntriesCount = 0;
                    }
                	if (ptr2 != System::IntPtr::Zero)
                {
                    for each(auto ent in old)
                    {
                        auto data = ent->Extra;
                        if(data != nullptr) Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESLeveledList_SetLeveledListEntries_2), MCH::FromBase(GameAddress::GameAddress::gMemoryManager), data->Address, 0);
                    }
                    		Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESLeveledList_SetLeveledListEntries_2), MCH::FromBase(GameAddress::GameAddress::gMemoryManager), ptr2 - 8, 0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESLevSpell"/>.
        /// </summary>
        private ref class impl_TESLevSpell sealed : public VirtualObject, public TESLevSpell
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESLeveledList.LeveledListEntriesArray"/>.
            /// </summary>
            virtual property System::IntPtr LeveledListEntriesArray
            {
                System::IntPtr __clrcall get() sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    return Memory::ReadPointer(self->Address + 0x8, false);
                }
                void __clrcall set(System::IntPtr value) sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    Memory::WritePointer(self->Address + 0x8, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESLeveledList.LeveledListSkipChance"/>.
            /// </summary>
            virtual property System::Byte LeveledListSkipChance
            {
                System::Byte __clrcall get() sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    return Memory::ReadUInt8(self->Address + 0x10, false);
                }
                void __clrcall set(System::Byte value) sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    Memory::WriteUInt8(self->Address + 0x10, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESLeveledList.LeveledListFlagsValue"/>.
            /// </summary>
            virtual property TESLeveledListFlags LeveledListFlagsValue
            {
                TESLeveledListFlags __clrcall get() sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    return (TESLeveledListFlags)Memory::ReadUInt8(self->Address + 0x11, false);
                }
                void __clrcall set(TESLeveledListFlags value) sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    Memory::WriteUInt8(self->Address + 0x11, (System::Byte)value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESLeveledList.LeveledListEntriesCount"/>.
            /// </summary>
            virtual property System::Byte LeveledListEntriesCount
            {
                System::Byte __clrcall get() sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    return Memory::ReadUInt8(self->Address + 0x12, false);
                }
                void __clrcall set(System::Byte value) sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    Memory::WriteUInt8(self->Address + 0x12, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESLeveledList.LeveledListSkipChanceGlobal"/>.
            /// </summary>
            virtual property TESGlobal^ LeveledListSkipChanceGlobal
            {
                TESGlobal^ __clrcall get() sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    return MemoryObject::FromAddress<TESGlobal^>(Memory::ReadPointer(self->Address + 0x20, false));
                }
                void __clrcall set(TESGlobal^ value) sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    Memory::WritePointer(self->Address + 0x20, value != nullptr ? value->Address : System::IntPtr::Zero, false);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESLeveledList.GetLeveledListEntry"/>.
            /// </summary>
            virtual TESLeveledList::Entry^ __clrcall GetLeveledListEntry(System::Int32 index) sealed
            {
                int max = this->LeveledListEntriesCount;
                if(index < 0 || index >= max) return nullptr;
                auto ptr = this->LeveledListEntriesArray;
                if(ptr == System::IntPtr::Zero) return nullptr;
                ptr = ptr + MemoryObject::SizeOf<TESLeveledList::Entry^>() * index;
                return MemoryObject::FromAddress<TESLeveledList::Entry^>(ptr);
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESLeveledList.GetLeveledListEntries"/>.
            /// </summary>
            /// <returns></returns>
            virtual System::Collections::Generic::List<TESLeveledList::Entry^>^ __clrcall GetLeveledListEntries() sealed
            {
                	auto ptr = this->LeveledListEntriesArray;
                	if (ptr == System::IntPtr::Zero) return nullptr;
                
                	int max = this->LeveledListEntriesCount;
                	int size = MemoryObject::SizeOf<TESLeveledList::Entry^>();
                	auto ls = gcnew System::Collections::Generic::List<TESLeveledList::Entry^>(System::Math::Min(32, max));
                	for (int i = 0; i < max; i++)
                	{
                		auto obj = MemoryObject::FromAddress<TESLeveledList::Entry^>(ptr);
                		ls->Add(obj);
                		ptr = ptr + size;
                	}
                	return ls;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESLeveledList.SetLeveledListEntries"/>.
            /// </summary>
            /// <param name="entries">The entries.</param>
            virtual void __clrcall SetLeveledListEntries(System::Collections::Generic::IReadOnlyList<TESLeveledList::Entry^>^ entries) sealed
            {
                	if (entries != nullptr && entries->Count > 255)
                		throw gcnew System::ArgumentOutOfRangeException("Unable to create leveled list array with more than 255 entries!");
                
                	auto ptr2 = this->LeveledListEntriesArray;
                    auto old = this->GetLeveledListEntries();
                
                	if (entries != nullptr)
                    {
                	int size = MemoryObject::SizeOf<TESLeveledList::Entry^>();
                	auto ptr = Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESLeveledList_SetLeveledListEntries_1), MCH::FromBase(GameAddress::GameAddress::gMemoryManager), size * entries->Count + 8, 0);
                	Memory::WriteInt64(ptr, entries->Count, false);
                	ptr = ptr + 8;
                	for (int i = 0; i < entries->Count; i++)
                	{
                		auto cur = MemoryObject::FromAddress<TESLeveledList::Entry^>(ptr + size * i);
                		auto e = entries[i];
                		if (e == nullptr)
                		{
                			cur->Form = nullptr;
                			cur->Count = 1;
                			cur->Level = 1;
                			Memory::WriteUInt64(cur->Address + 0x10, 0, false);
                		}
                		else
                		{
                			cur->CopyFrom(e);
                		}
                	}
                
                	this->LeveledListEntriesArray = ptr;
                	this->LeveledListEntriesCount = (System::Byte)entries->Count;
                    }
                    else
                    {
                        this->LeveledListEntriesArray = System::IntPtr::Zero;
                	    this->LeveledListEntriesCount = 0;
                    }
                	if (ptr2 != System::IntPtr::Zero)
                {
                    for each(auto ent in old)
                    {
                        auto data = ent->Extra;
                        if(data != nullptr) Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESLeveledList_SetLeveledListEntries_2), MCH::FromBase(GameAddress::GameAddress::gMemoryManager), data->Address, 0);
                    }
                    		Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESLeveledList_SetLeveledListEntries_2), MCH::FromBase(GameAddress::GameAddress::gMemoryManager), ptr2 - 8, 0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESLevCharacter"/>.
        /// </summary>
        private ref class impl_TESLevCharacter sealed : public VirtualObject, public TESLevCharacter
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESLeveledList.LeveledListEntriesArray"/>.
            /// </summary>
            virtual property System::IntPtr LeveledListEntriesArray
            {
                System::IntPtr __clrcall get() sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    return Memory::ReadPointer(self->Address + 0x8, false);
                }
                void __clrcall set(System::IntPtr value) sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    Memory::WritePointer(self->Address + 0x8, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESLeveledList.LeveledListSkipChance"/>.
            /// </summary>
            virtual property System::Byte LeveledListSkipChance
            {
                System::Byte __clrcall get() sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    return Memory::ReadUInt8(self->Address + 0x10, false);
                }
                void __clrcall set(System::Byte value) sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    Memory::WriteUInt8(self->Address + 0x10, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESLeveledList.LeveledListFlagsValue"/>.
            /// </summary>
            virtual property TESLeveledListFlags LeveledListFlagsValue
            {
                TESLeveledListFlags __clrcall get() sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    return (TESLeveledListFlags)Memory::ReadUInt8(self->Address + 0x11, false);
                }
                void __clrcall set(TESLeveledListFlags value) sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    Memory::WriteUInt8(self->Address + 0x11, (System::Byte)value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESLeveledList.LeveledListEntriesCount"/>.
            /// </summary>
            virtual property System::Byte LeveledListEntriesCount
            {
                System::Byte __clrcall get() sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    return Memory::ReadUInt8(self->Address + 0x12, false);
                }
                void __clrcall set(System::Byte value) sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    Memory::WriteUInt8(self->Address + 0x12, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESLeveledList.LeveledListSkipChanceGlobal"/>.
            /// </summary>
            virtual property TESGlobal^ LeveledListSkipChanceGlobal
            {
                TESGlobal^ __clrcall get() sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    return MemoryObject::FromAddress<TESGlobal^>(Memory::ReadPointer(self->Address + 0x20, false));
                }
                void __clrcall set(TESGlobal^ value) sealed
                {
                    auto self = this->As<TESLeveledList^>();
                    Memory::WritePointer(self->Address + 0x20, value != nullptr ? value->Address : System::IntPtr::Zero, false);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESLeveledList.GetLeveledListEntry"/>.
            /// </summary>
            virtual TESLeveledList::Entry^ __clrcall GetLeveledListEntry(System::Int32 index) sealed
            {
                int max = this->LeveledListEntriesCount;
                if(index < 0 || index >= max) return nullptr;
                auto ptr = this->LeveledListEntriesArray;
                if(ptr == System::IntPtr::Zero) return nullptr;
                ptr = ptr + MemoryObject::SizeOf<TESLeveledList::Entry^>() * index;
                return MemoryObject::FromAddress<TESLeveledList::Entry^>(ptr);
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESLeveledList.GetLeveledListEntries"/>.
            /// </summary>
            /// <returns></returns>
            virtual System::Collections::Generic::List<TESLeveledList::Entry^>^ __clrcall GetLeveledListEntries() sealed
            {
                	auto ptr = this->LeveledListEntriesArray;
                	if (ptr == System::IntPtr::Zero) return nullptr;
                
                	int max = this->LeveledListEntriesCount;
                	int size = MemoryObject::SizeOf<TESLeveledList::Entry^>();
                	auto ls = gcnew System::Collections::Generic::List<TESLeveledList::Entry^>(System::Math::Min(32, max));
                	for (int i = 0; i < max; i++)
                	{
                		auto obj = MemoryObject::FromAddress<TESLeveledList::Entry^>(ptr);
                		ls->Add(obj);
                		ptr = ptr + size;
                	}
                	return ls;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESLeveledList.SetLeveledListEntries"/>.
            /// </summary>
            /// <param name="entries">The entries.</param>
            virtual void __clrcall SetLeveledListEntries(System::Collections::Generic::IReadOnlyList<TESLeveledList::Entry^>^ entries) sealed
            {
                	if (entries != nullptr && entries->Count > 255)
                		throw gcnew System::ArgumentOutOfRangeException("Unable to create leveled list array with more than 255 entries!");
                
                	auto ptr2 = this->LeveledListEntriesArray;
                    auto old = this->GetLeveledListEntries();
                
                	if (entries != nullptr)
                    {
                	int size = MemoryObject::SizeOf<TESLeveledList::Entry^>();
                	auto ptr = Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESLeveledList_SetLeveledListEntries_1), MCH::FromBase(GameAddress::GameAddress::gMemoryManager), size * entries->Count + 8, 0);
                	Memory::WriteInt64(ptr, entries->Count, false);
                	ptr = ptr + 8;
                	for (int i = 0; i < entries->Count; i++)
                	{
                		auto cur = MemoryObject::FromAddress<TESLeveledList::Entry^>(ptr + size * i);
                		auto e = entries[i];
                		if (e == nullptr)
                		{
                			cur->Form = nullptr;
                			cur->Count = 1;
                			cur->Level = 1;
                			Memory::WriteUInt64(cur->Address + 0x10, 0, false);
                		}
                		else
                		{
                			cur->CopyFrom(e);
                		}
                	}
                
                	this->LeveledListEntriesArray = ptr;
                	this->LeveledListEntriesCount = (System::Byte)entries->Count;
                    }
                    else
                    {
                        this->LeveledListEntriesArray = System::IntPtr::Zero;
                	    this->LeveledListEntriesCount = 0;
                    }
                	if (ptr2 != System::IntPtr::Zero)
                {
                    for each(auto ent in old)
                    {
                        auto data = ent->Extra;
                        if(data != nullptr) Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESLeveledList_SetLeveledListEntries_2), MCH::FromBase(GameAddress::GameAddress::gMemoryManager), data->Address, 0);
                    }
                    		Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESLeveledList_SetLeveledListEntries_2), MCH::FromBase(GameAddress::GameAddress::gMemoryManager), ptr2 - 8, 0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
        };
        
        /// <summary>
        /// Implementation of interface <see cref="AlchemyItem"/>.
        /// </summary>
        private ref class impl_AlchemyItem sealed : public VirtualObject, public AlchemyItem
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESWeightForm.Value"/>.
            /// </summary>
            virtual property System::Single Value
            {
                System::Single __clrcall get() sealed
                {
                    auto self = this->As<TESWeightForm^>();
                    return Memory::ReadFloat(self->Address + 0x8, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    auto self = this->As<TESWeightForm^>();
                    Memory::WriteFloat(self->Address + 0x8, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESFullName.Text"/>.
            /// </summary>
            virtual property BSFixedString^ Text
            {
                BSFixedString^ __clrcall get() sealed
                {
                    auto self = this->As<TESFullName^>();
                    return MemoryObject::FromAddress<BSFixedString^>(self->Address + 0x8);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
        };
        
        /// <summary>
        /// Implementation of interface <see cref="ExtraPoison"/>.
        /// </summary>
        private ref class impl_ExtraPoison sealed : public VirtualObject, public ExtraPoison
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="BSExtraData.Next"/>.
            /// </summary>
            virtual property BSExtraData^ Next
            {
                BSExtraData^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<BSExtraData^>(Memory::ReadPointer(this->Address + 0x8, false));
                }
                void __clrcall set(BSExtraData^ value) sealed
                {
                    Memory::WritePointer(this->Address + 0x8, value != nullptr ? value->Address : System::IntPtr::Zero, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ExtraPoison.Count"/>.
            /// </summary>
            virtual property System::Int32 Count
            {
                System::Int32 __clrcall get() sealed
                {
                    return Memory::ReadInt32(this->Address + 0x18, false);
                }
                void __clrcall set(System::Int32 value) sealed
                {
                    Memory::WriteInt32(this->Address + 0x18, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ExtraPoison.Item"/>.
            /// </summary>
            virtual property AlchemyItem^ Item
            {
                AlchemyItem^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<AlchemyItem^>(Memory::ReadPointer(this->Address + 0x10, false));
                }
                void __clrcall set(AlchemyItem^ value) sealed
                {
                    Memory::WritePointer(this->Address + 0x10, value != nullptr ? value->Address : System::IntPtr::Zero, false);
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BGSProjectile"/>.
        /// </summary>
        private ref class impl_BGSProjectile sealed : public VirtualObject, public BGSProjectile
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESFullName.Text"/>.
            /// </summary>
            virtual property BSFixedString^ Text
            {
                BSFixedString^ __clrcall get() sealed
                {
                    auto self = this->As<TESFullName^>();
                    return MemoryObject::FromAddress<BSFixedString^>(self->Address + 0x8);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESAmmo"/>.
        /// </summary>
        private ref class impl_TESAmmo sealed : public VirtualObject, public TESAmmo
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESFullName.Text"/>.
            /// </summary>
            virtual property BSFixedString^ Text
            {
                BSFixedString^ __clrcall get() sealed
                {
                    auto self = this->As<TESFullName^>();
                    return MemoryObject::FromAddress<BSFixedString^>(self->Address + 0x8);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESWeightForm.Value"/>.
            /// </summary>
            virtual property System::Single Value
            {
                System::Single __clrcall get() sealed
                {
                    auto self = this->As<TESWeightForm^>();
                    return Memory::ReadFloat(self->Address + 0x8, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    auto self = this->As<TESWeightForm^>();
                    Memory::WriteFloat(self->Address + 0x8, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
            
            /// <summary>
            /// Implementation of property <see cref="TESAmmo.ProjectileData"/>.
            /// </summary>
            virtual property BGSProjectile^ ProjectileData
            {
                BGSProjectile^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<BGSProjectile^>(Memory::ReadPointer(this->Address + 0x110, false));
                }
                void __clrcall set(BGSProjectile^ value) sealed
                {
                    Memory::WritePointer(this->Address + 0x110, value != nullptr ? value->Address : System::IntPtr::Zero, false);
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESWorldSpace"/>.
        /// </summary>
        private ref class impl_TESWorldSpace sealed : public VirtualObject, public TESWorldSpace
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
            
            /// <summary>
            /// Implementation of property <see cref="TESFullName.Text"/>.
            /// </summary>
            virtual property BSFixedString^ Text
            {
                BSFixedString^ __clrcall get() sealed
                {
                    auto self = this->As<TESFullName^>();
                    return MemoryObject::FromAddress<BSFixedString^>(self->Address + 0x8);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESWorldSpace.GetCellByCoordinates"/>.
            /// </summary>
            virtual TESObjectCELL^ __clrcall GetCellByCoordinates(System::Int32 x, System::Int32 y) sealed
            {
                auto self = this;
                if(x < -32768 || x > 0x7FFF || y < -32768 || y > 0x7FFF) return nullptr;
                System::UInt32 mask = (System::UInt32)x << 16;
                mask |= (System::UInt32)y;
                return MemoryObject::FromAddress<TESObjectCELL^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESWorldSpace_GetCellByCoordinates), self->Address, mask));
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESWorldSpace.GetCellByPosition"/>.
            /// </summary>
            virtual TESObjectCELL^ __clrcall GetCellByPosition(System::Single x, System::Single y) sealed
            {
                auto self = this;
                stack10 s;
                s.set<float>(0, x);
                s.set<float>(4, y);
                return MemoryObject::FromAddress<TESObjectCELL^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESWorldSpace_GetCellByPosition), self->Address, s.ptr()));
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="GridCellArray"/>.
        /// </summary>
        private ref class impl_GridCellArray sealed : public VirtualObject, public GridCellArray
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="GridArray.Length"/>.
            /// </summary>
            virtual property System::Int32 Length
            {
                System::Int32 __clrcall get() sealed
                {
                    return Memory::ReadInt32(this->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="GridCellArray.GetCell"/>.
            /// </summary>
            virtual TESObjectCELL^ __clrcall GetCell(System::Int32 x, System::Int32 y) sealed
            {
                auto self = this;
                auto gridPtr = Memory::InvokeCdecl(MCH::FromBase(GameAddress::GridCellArray_GetCell), self->Address, x, y);
                if(gridPtr != System::IntPtr::Zero) gridPtr = Memory::ReadPointer(gridPtr, false);
                return MemoryObject::FromAddress<TESObjectCELL^>(gridPtr);
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TES"/>.
        /// </summary>
        private ref class impl_TES sealed : public VirtualObject, public TES
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TES.CellGrid"/>.
            /// </summary>
            virtual property GridCellArray^ CellGrid
            {
                GridCellArray^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<GridCellArray^>(Memory::ReadPointer(this->Address + 0x78, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TES.CurrentInteriorCell"/>.
            /// </summary>
            virtual property TESObjectCELL^ CurrentInteriorCell
            {
                TESObjectCELL^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESObjectCELL^>(Memory::ReadPointer(this->Address + 0xC0, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TES.GridsToLoad"/>.
            /// </summary>
            virtual property System::Int32 GridsToLoad
            {
                System::Int32 __clrcall get() sealed
                {
                    return Memory::ReadInt32(MCH::FromBase(GameAddress::TES_GridsToLoad_Get) + 8, false);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TES.GetLoadedCells"/>.
            /// </summary>
            virtual System::Collections::Generic::List<TESObjectCELL^>^ __clrcall GetLoadedCells() sealed
            {
                System::Collections::Generic::List<TESObjectCELL^>^ ls = nullptr;
                auto interior = this->CurrentInteriorCell;
                if(interior != nullptr)
                {
                    ls = gcnew System::Collections::Generic::List<TESObjectCELL^>(1);
                    if(interior->IsAttached) ls->Add(interior);
                }
                else
                {
                    ls = gcnew System::Collections::Generic::List<TESObjectCELL^>(32);
                    auto grid = this->CellGrid;
                    if(grid != nullptr)
                    {
                        int length = grid->Length;
                        for(int i = 0; i < length; i++)
                        {
                            for(int j = 0; j < length; j++)
                            {
                                auto cell = grid->GetCell(i, j);
                                if(cell != nullptr && cell->IsAttached) ls->Add(cell);
                            }
                        }
                    }
                }
                return ls;
            }
            
        };
        
        /// <summary>
        /// Implementation of interface <see cref="NiMatrix33"/>.
        /// </summary>
        private ref class impl_NiMatrix33 sealed : public MemoryObject, public NiMatrix33
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="NiMatrix33.Data"/>.
            /// </summary>
            virtual property System::IntPtr Data
            {
                System::IntPtr __clrcall get() sealed
                {
                    return Address;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiMatrix33.Inverse"/>.
            /// </summary>
            virtual void __clrcall Inverse(NiMatrix33^ result) sealed
            {
                if(!this->IsValid) throw gcnew MemoryAccessException(this->Address);
                if(!result->IsValid) throw gcnew MemoryAccessException(result->Address);
                
                float tmp[9];
                float * m = (float*)this->Data.ToPointer();
                
                tmp[0] = m[4] * m[8] - m[5] * m[7];
                tmp[1] = m[2] * m[7] - m[1] * m[8];
                tmp[2] = m[1] * m[5] - m[2] * m[4];
                tmp[3] = m[5] * m[6] - m[3] * m[8];
                tmp[4] = m[0] * m[8] - m[2] * m[6];
                tmp[5] = m[2] * m[3] - m[0] * m[5];
                tmp[6] = m[3] * m[7] - m[4] * m[6];
                tmp[7] = m[1] * m[6] - m[0] * m[7];
                tmp[8] = m[0] * m[4] - m[1] * m[3];
                
                float determinant = m[0] * tmp[0] + m[1] * tmp[3] + m[2] * tmp[6];
                if (System::Math::Abs(determinant) <= System::Single::Epsilon)
                {
                    result->Identity(1.0f);
                    return;
                }
                
                m = (float*)result->Data.ToPointer();
                float invDeterminant = 1.0f / determinant;
                m[0] = invDeterminant * tmp[0];
                m[1] = invDeterminant * tmp[1];
                m[2] = invDeterminant * tmp[2];
                m[3] = invDeterminant * tmp[3];
                m[4] = invDeterminant * tmp[4];
                m[5] = invDeterminant * tmp[5];
                m[6] = invDeterminant * tmp[6];
                m[7] = invDeterminant * tmp[7];
                m[8] = invDeterminant * tmp[8];
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiMatrix33.Identity"/>.
            /// </summary>
            virtual void __clrcall Identity(System::Single scale) sealed
            {
                for(int i = 0; i < 3; i++)
                {
                    for(int j = 0; j < 3; j++)
                    {
                        this[i, j] = i == j ? scale : 0.0f;
                    }
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiMatrix33.Multiply"/>.
            /// </summary>
            virtual void __clrcall Multiply(NiMatrix33^ other, NiMatrix33^ result) sealed
            {
                if(!this->IsValid) throw gcnew MemoryAccessException(this->Address);
                if(!other->IsValid) throw gcnew MemoryAccessException(other->Address);
                if(!result->IsValid) throw gcnew MemoryAccessException(result->Address);
                
                float r[9];
                float temp = 0.0f;
                float * fd = (float*)this->Data.ToPointer();
                float * sd = (float*)other->Data.ToPointer();
                for(int a = 0; a < 3; a++)
                {
                    for(int b = 0; b < 3; b++)
                    {
                        for(int c = 0; c < 3; c++)
                        {
                            temp += fd[b * 3 + c] * sd[c * 3 + a];
                        }
                        r[b * 3 + a] = temp;
                        temp = 0.0f;
                    }
                }
                
                float * m = (float*)result->Data.ToPointer();
                for(int i = 0; i < 9; i++) m[i] = r[i];
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiMatrix33.Transpose"/>.
            /// </summary>
            virtual void __clrcall Transpose(NiMatrix33^ result) sealed
            {
                if(!this->IsValid) throw gcnew MemoryAccessException(this->Address);
                if(!result->IsValid) throw gcnew MemoryAccessException(result->Address);
                
                float r[9];
                float * m = (float*)this->Data.ToPointer();
                for(int i = 0; i < 3; i++)
                {
                    for(int j = 0; j < 3; j++) r[i * 3 + j] = m[i + j * 3];
                }
                m = (float*)result->Data.ToPointer();
                for(int j = 0; j < 9; j++) m[j] = r[j];
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiMatrix33.default"/>.
            /// </summary>
            virtual property float default[System::Int32, System::Int32]
            {
                float __clrcall get(System::Int32 i, System::Int32 j) sealed
                {
                    if (i < 0 || i >= 3) throw gcnew System::IndexOutOfRangeException("i");
                    if (j < 0 || j >= 3) throw gcnew System::IndexOutOfRangeException("j");
                    //float * m = (float*)this->Data.ToPointer();
                    //return m[i * 3 + j];
                    return Memory::ReadFloat(this->Data + ((i * 3 + j) * 4), false);
                }
                void __clrcall set(System::Int32 i, System::Int32 j, float value) sealed
                {
                    if (i < 0 || i >= 3) throw gcnew System::IndexOutOfRangeException("i");
                    if (j < 0 || j >= 3) throw gcnew System::IndexOutOfRangeException("j");
                    //float * m = (float*)this->Data.ToPointer();
                    //m[i * 3 + j] = value;
                    return Memory::WriteFloat(this->Data + ((i * 3 + j) * 4), value, false);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiMatrix33.RotateZ"/>.
            /// </summary>
            virtual void __clrcall RotateZ(System::Single rad, NiMatrix33^ result) sealed
            {
                float c = (float)System::Math::Cos(rad);
                float s = (float)System::Math::Sin(rad);
                
                stack40 r;
                NiMatrix33^ R = MemoryObject::FromAddress<NiMatrix33^>(r.ptr());
                R->Identity(1.0f);
                
                R[0, 0] = c;
                R[0, 1] = -s;
                
                R[1, 0] = s;
                R[1, 1] = c;
                
                R->Multiply(this, result);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiMatrix33.RotateY"/>.
            /// </summary>
            virtual void __clrcall RotateY(System::Single rad, NiMatrix33^ result) sealed
            {
                float c = (float)System::Math::Cos(rad);
                float s = (float)System::Math::Sin(rad);
                
                stack40 r;
                NiMatrix33^ R = MemoryObject::FromAddress<NiMatrix33^>(r.ptr());
                R->Identity(1.0f);
                
                R[0, 0] = c;
                R[0, 2] = s;
                
                R[2, 0] = -s;
                R[2, 2] = c;
                
                R->Multiply(this, result);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiMatrix33.RotateX"/>.
            /// </summary>
            virtual void __clrcall RotateX(System::Single rad, NiMatrix33^ result) sealed
            {
                float c = (float)System::Math::Cos(rad);
                float s = (float)System::Math::Sin(rad);
                
                stack40 r;
                NiMatrix33^ R = MemoryObject::FromAddress<NiMatrix33^>(r.ptr());
                R->Identity(1.0f);
                
                R[1, 1] = c;
                R[1, 2] = -s;
                
                R[2, 1] = s;
                R[2, 2] = c;
                
                R->Multiply(this, result);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiMatrix33.GetAxisAngle"/>.
            /// </summary>
            virtual void __clrcall GetAxisAngle(NiPoint3^ resultAxis, System::Single% angle) sealed
            {
                float c2 = this[0, 0] + this[1, 1] + this[2, 2] - 1.0f;
                resultAxis->X = this[2, 1] - this[1, 2];
                resultAxis->Y = this[0, 2] - this[2, 0];
                resultAxis->Z = this[1, 0] - this[0, 1];
                float s2 = resultAxis->Length;
                
                if(s2 > 0.0f)
                {
                    angle = (float)System::Math::Atan2(s2, c2);
                    resultAxis->Normalize(resultAxis);
                    return;
                }
                
                if(c2 >= 2.0f)
                {
                    angle = 0.0f;
                    resultAxis->X = 1.0f;
                    resultAxis->Y = 0.0f;
                    resultAxis->Z = 0.0f;
                    return;
                }
                
                angle = (float)System::Math::PI;
                
                if(this[2, 2] > this[0, 0] && this[2, 2] > this[1, 1])
                {
                    resultAxis->Z = 0.5f * (float)System::Math::Sqrt(this[2, 2] - this[0, 0] - this[1, 1] + 1.0f);
                    float dbla = 0.5f / resultAxis->Z;
                    resultAxis->X = dbla * this[0, 2];
                    resultAxis->Y = dbla * this[1, 2];
                    return;
                }
                
                if(this[1, 1] > this[0, 0] && this[1, 1] > this[2, 2])
                {
                    resultAxis->Y = 0.5f * (float)System::Math::Sqrt(this[1, 1] - this[0, 0] - this[2, 2] + 1.0f);
                    float dbla = 0.5f / resultAxis->Y;
                    resultAxis->X = dbla * this[0, 1];
                    resultAxis->Z = dbla * this[1, 2];
                    return;
                }
                
                {
                    resultAxis->X = 0.5f * (float)System::Math::Sqrt(this[0, 0] - this[1, 1] - this[2, 2] + 1.0f);
                    float dbla = 0.5f / resultAxis->X;
                    resultAxis->Y = dbla * this[0, 1];
                    resultAxis->Z = dbla * this[0, 2];
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiMatrix33.GetFromAxisAngle"/>.
            /// </summary>
            virtual void __clrcall GetFromAxisAngle(NiPoint3^ axis, System::Single angle) sealed
            {
                NiMatrix33^ result = this;
                result->Identity(1.0f);
                
                float c = (float)System::Math::Cos(angle);
                float s = (float)System::Math::Sin(angle);
                float t = 1.0f - c;
                
                result[0, 0] = c + axis->X * axis->X * t;
                result[1, 1] = c + axis->Y * axis->Y * t;
                result[2, 2] = c + axis->Z * axis->Z * t;
                
                float tmp1 = axis->X * axis->Y * t;
                float tmp2 = axis->Z * s;
                result[1, 0] = tmp1 + tmp2;
                result[0, 1] = tmp1 - tmp2;
                tmp1 = axis->X * axis->Z * t;
                tmp2 = axis->Y * s;
                result[2, 0] = tmp1 - tmp2;
                result[0, 2] = tmp1 + tmp2;
                tmp1 = axis->Y * axis->Z * t;
                tmp2 = axis->X * s;
                result[2, 1] = tmp1 + tmp2;
                result[1, 2] = tmp1 - tmp2;
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiMatrix33.GetEulerAngles"/>.
            /// </summary>
            virtual void __clrcall GetEulerAngles(NiPoint3^ result) sealed
            {
                if((float)System::Math::Abs(this[0, 2] + 1.0f) < System::Single::Epsilon)
                {
                    result->X = 0.0f;
                    result->Y = (float)System::Math::PI * 0.5f;
                    result->Z = (float)System::Math::Atan2(this[1, 0], this[2, 0]);
                    return;
                }
                
                if((float)System::Math::Abs(this[0, 2] - 1.0f) < System::Single::Epsilon)
                {
                    result->X = 0.0f;
                    result->Y = -(float)System::Math::PI * 0.5f;
                    result->Z = (float)System::Math::Atan2(-this[1, 0], -this[2, 0]);
                    return;
                }
                
                float x1 = -(float)System::Math::Asin(this[0, 2]);
                float cx1 = (float)System::Math::Cos(x1);
                result->X = x1;
                result->Y = (float)System::Math::Atan2(this[1, 2] / cx1, this[2, 2] / cx1);
                result->Z = (float)System::Math::Atan2(this[0, 1] / cx1, this[0, 0] / cx1);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiMatrix33.Interpolate"/>.
            /// </summary>
            virtual void __clrcall Interpolate(NiMatrix33^ other, System::Single ratio, NiMatrix33^ result) sealed
            {
                stack40 s_aT;
                stack40 s_delta;
                stack10 s_point;
                
                NiMatrix33^ aT = MemoryObject::FromAddress<NiMatrix33^>(s_aT.ptr());
                NiMatrix33^ delta = MemoryObject::FromAddress<NiMatrix33^>(s_delta.ptr());
                NiPoint3^ point = MemoryObject::FromAddress<NiPoint3^>(s_point.ptr());
                
                this->Transpose(aT);
                other->Multiply(aT, delta);
                float deltaAngle = 0.0f;
                delta->GetAxisAngle(point, deltaAngle);
                aT->GetFromAxisAngle(point, deltaAngle * ratio);
                aT->Multiply(this, result);
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="NiPoint3"/>.
        /// </summary>
        private ref class impl_NiPoint3 sealed : public MemoryObject, public NiPoint3
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="NiPoint3.X"/>.
            /// </summary>
            virtual property System::Single X
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0x0, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    Memory::WriteFloat(this->Address + 0x0, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiPoint3.Y"/>.
            /// </summary>
            virtual property System::Single Y
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0x4, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    Memory::WriteFloat(this->Address + 0x4, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiPoint3.Z"/>.
            /// </summary>
            virtual property System::Single Z
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0x8, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    Memory::WriteFloat(this->Address + 0x8, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiPoint3.Length"/>.
            /// </summary>
            virtual property System::Single Length
            {
                System::Single __clrcall get() sealed
                {
                    float x = this->X;
                    float y = this->Y;
                    float z = this->Z;
                    return (float)System::Math::Sqrt((x * x) + (y * y) + (z * z));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiPoint3.IsZero"/>.
            /// </summary>
            virtual property bool IsZero
            {
                bool __clrcall get() sealed
                {
                    return this->X == 0.0f && this->Y == 0.0f && this->Z == 0.0f;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiPoint3.Normalize"/>.
            /// </summary>
            virtual void __clrcall Normalize(NiPoint3^ result) sealed
            {
                float len = this->Length;
                if(len > 0.0f)
                {
                    result->X = this->X / len;
                    result->Y = this->Y / len;
                    result->Z = this->Z / len;
                }
                else
                {
                    result->X = 0.0f;
                    result->Y = 0.0f;
                    result->Z = 0.0f;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiPoint3.GetDistance"/>.
            /// </summary>
            virtual System::Single __clrcall GetDistance(NiPoint3^ other) sealed
            {
                float x = this->X - other->X;
                float y = this->Y - other->Y;
                float z = this->Z - other->Z;
                return (float)System::Math::Sqrt(x * x + y * y + z * z);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiPoint3.Cross"/>.
            /// </summary>
            virtual void __clrcall Cross(NiPoint3^ other, NiPoint3^ result) sealed
            {
                float ax = this->X;
                float ay = this->Y;
                float az = this->Z;
                float bx = other->X;
                float by = other->Y;
                float bz = other->Z;
                result->X = (ay * bz) - (az * by);
                result->Y = (az * bx) - (ax * bz);
                result->Z = (ax * by) - (ay * bx);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiPoint3.Dot"/>.
            /// </summary>
            virtual System::Single __clrcall Dot(NiPoint3^ other) sealed
            {
                return this->X * other->X + this->Y * other->Y + this->Z * other->Z;
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiPoint3.Add"/>.
            /// </summary>
            virtual void __clrcall Add(NiPoint3^ other, NiPoint3^ result) sealed
            {
                result->X = this->X + other->X;
                result->Y = this->Y + other->Y;
                result->Z = this->Z + other->Z;
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiPoint3.Subtract"/>.
            /// </summary>
            virtual void __clrcall Subtract(NiPoint3^ other, NiPoint3^ result) sealed
            {
                result->X = this->X - other->X;
                result->Y = this->Y - other->Y;
                result->Z = this->Z - other->Z;
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiPoint3.Multiply"/>.
            /// </summary>
            virtual void __clrcall Multiply(System::Single amount, NiPoint3^ result) sealed
            {
                result->X = this->X * amount;
                result->Y = this->Y * amount;
                result->Z = this->Z * amount;
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiPoint3.GetAngleDifference"/>.
            /// </summary>
            virtual void __clrcall GetAngleDifference(NiPoint3^ other, NiMatrix33^ result) sealed
            {
                stack10 s_axis;
                NiPoint3^ axis = MemoryObject::FromAddress<NiPoint3^>(s_axis.ptr());
                float angle = (float)System::Math::Acos(this->Dot(other));
                this->Cross(other, axis);
                axis->Normalize(axis);
                result->GetFromAxisAngle(axis, angle);
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="NiTransform"/>.
        /// </summary>
        private ref class impl_NiTransform sealed : public MemoryObject, public NiTransform
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="NiTransform.Rotation"/>.
            /// </summary>
            virtual property NiMatrix33^ Rotation
            {
                NiMatrix33^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiMatrix33^>(this->Address + 0x0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiTransform.Position"/>.
            /// </summary>
            virtual property NiPoint3^ Position
            {
                NiPoint3^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPoint3^>(this->Address + 0x24);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiTransform.Scale"/>.
            /// </summary>
            virtual property System::Single Scale
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0x30, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    Memory::WriteFloat(this->Address + 0x30, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiTransform.LookAt"/>.
            /// </summary>
            virtual void __clrcall LookAt(NiPoint3^ target) sealed
            {
                stack10 s_x;
                stack10 s_y;
                stack10 s_up;
                stack10 s_dir;
                
                NiPoint3^ x = MemoryObject::FromAddress<NiPoint3^>(s_x.ptr());
                NiPoint3^ y = MemoryObject::FromAddress<NiPoint3^>(s_y.ptr());
                NiPoint3^ up = MemoryObject::FromAddress<NiPoint3^>(s_up.ptr());
                NiPoint3^ dir = MemoryObject::FromAddress<NiPoint3^>(s_dir.ptr());
                
                auto pos = this->Position;
                dir->X = target->X - pos->X;
                dir->Y = target->Y - pos->Y;
                dir->Z = target->Z - pos->Z;
                dir->Normalize(dir);
                
                NiPoint3^ z = dir;
                
                up->X = 0.0f;
                up->Y = 0.0f;
                up->Z = 1.0f;
                
                up->Cross(z, x);
                x->Normalize(x);
                
                z->Cross(x, y);
                y->Normalize(y);
                
                auto rot = this->Rotation;
                rot[0, 0] = -x->X;
                rot[1, 0] = -x->Y;
                rot[2, 0] = -x->Z;
                rot[0, 1] = z->X;
                rot[1, 1] = z->Y;
                rot[2, 1] = z->Z;
                rot[0, 2] = y->X;
                rot[1, 2] = y->Y;
                rot[2, 2] = y->Z;
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiTransform.Translate"/>.
            /// </summary>
            virtual void __clrcall Translate(NiPoint3^ amount, NiPoint3^ result) sealed
            {
                if(!this->IsValid) throw gcnew MemoryAccessException(this->Address);
                
                float a[3];
                a[0] = amount->X;
                a[1] = amount->Y;
                a[2] = amount->Z;
                float * m = (float*)this->Rotation->Data.ToPointer();
                float r[3];
                
                r[0] = m[0] * a[0] + m[1] * a[1] + m[2] * a[2] + this->Position->X;
                r[1] = m[3] * a[0] + m[4] * a[1] + m[5] * a[2] + this->Position->Y;
                r[2] = m[6] * a[0] + m[7] * a[1] + m[8] * a[2] + this->Position->Z;
                
                result->X = r[0];
                result->Y = r[1];
                result->Z = r[2];
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="bhkRigidBody"/>.
        /// </summary>
        private ref class impl_bhkRigidBody sealed : public VirtualObject, public bhkRigidBody
        {
        public:
            /// <summary>
            /// Implementation of method <see cref="NiObject.Clone"/>.
            /// </summary>
            virtual NiObject^ __clrcall Clone() sealed
            {
                auto self = this;
                System::IntPtr result = System::IntPtr::Zero;
                stack100 alloc;
                alloc.set(0x18, MCH::FromBase(GameAddress::gUnkCloneValue1));
                alloc.set(0x48, MCH::FromBase(GameAddress::gUnkCloneValue2));
                alloc.set(0x60, Memory::ReadInt32(MCH::FromBase(GameAddress::gUnkCloneValue3), false));
                alloc.set(0x64, Memory::ReadUInt8(MCH::FromBase(GameAddress::gUnkCloneValue4), false));
                alloc.set(0x68, 1.0f);
                alloc.set(0x6C, 1.0f);
                alloc.set(0x70, 1.0f);
                result = Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_1), self->Address, alloc.ptr());
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_2), alloc.ptr() + 0x38);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_3), alloc.ptr() + 0x8);
                return MemoryObject::FromAddressSafeCast<NiObject^>(result);
            }
            
            
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.IncRef"/>.
            /// </summary>
            virtual void __clrcall IncRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                Memory::InterlockedIncrement32(self->Address + 0x8, false);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.DecRef"/>.
            /// </summary>
            virtual bool __clrcall DecRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                auto result = Memory::InterlockedDecrement32(self->Address + 0x8, false);
                if(this->Is<BSHandleRefObject^>()) result = result & 0x3FF;
                if(result == 0)
                {
                    self->InvokeVTableThisCall(0, 0x8);
                    return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of method <see cref="bhkRigidBody.Activate"/>.
            /// </summary>
            virtual void __clrcall Activate() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::bhkRigidBody_Activate), self->Address, 1);
            }
            
            /// <summary>
            /// Implementation of method <see cref="bhkRigidBody.Deactivate"/>.
            /// </summary>
            virtual void __clrcall Deactivate() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::bhkRigidBody_Activate), self->Address, 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="bhkRigidBody.ApplyLinearImpulse"/>.
            /// </summary>
            virtual void __clrcall ApplyLinearImpulse(NiPoint3^ amount) sealed
            {
                auto self = this;
                if(amount == nullptr) throw gcnew System::ArgumentNullException("amount");
                stack10 vec;
                vec.set(0, amount);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::bhkRigidBody_ApplyLinearImpulse), self->Address, vec.ptr());
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="CrossHairPickData"/>.
        /// </summary>
        private ref class impl_CrossHairPickData sealed : public MemoryObject, public CrossHairPickData
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="CrossHairPickData.TargetRefHandle"/>.
            /// </summary>
            virtual property System::UInt32 TargetRefHandle
            {
                System::UInt32 __clrcall get() sealed
                {
                    return Memory::ReadUInt32(this->Address + 0x4, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="CrossHairPickData.TargetActorRefHandle"/>.
            /// </summary>
            virtual property System::UInt32 TargetActorRefHandle
            {
                System::UInt32 __clrcall get() sealed
                {
                    return Memory::ReadUInt32(this->Address + 0x8, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="CrossHairPickData.CollisionPoint"/>.
            /// </summary>
            virtual property NiPoint3^ CollisionPoint
            {
                NiPoint3^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPoint3^>(this->Address + 0x10);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="CrossHairPickData.TargetCollider"/>.
            /// </summary>
            virtual property bhkRigidBody^ TargetCollider
            {
                bhkRigidBody^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<bhkRigidBody^>(Memory::ReadPointer(this->Address + 0x20, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="CrossHairPickData.PickCollider"/>.
            /// </summary>
            virtual property bhkSimpleShapePhantom^ PickCollider
            {
                bhkSimpleShapePhantom^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<bhkSimpleShapePhantom^>(Memory::ReadPointer(this->Address + 0x28, false));
                }
            }
            
        };
        
        /// <summary>
        /// Implementation of interface <see cref="ActorMagicCaster"/>.
        /// </summary>
        private ref class impl_ActorMagicCaster sealed : public VirtualObject, public ActorMagicCaster
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="MagicCaster.CastItem"/>.
            /// </summary>
            virtual property MagicItem^ CastItem
            {
                MagicItem^ __clrcall get() sealed
                {
                    auto self = this->As<MagicCaster^>();
                    return MemoryObject::FromAddress<MagicItem^>(Memory::ReadPointer(self->Address + 0x28, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="MagicCaster.Timer"/>.
            /// </summary>
            virtual property System::Single Timer
            {
                System::Single __clrcall get() sealed
                {
                    auto self = this->As<MagicCaster^>();
                    return Memory::ReadFloat(self->Address + 0x34, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="MagicCaster.State"/>.
            /// </summary>
            virtual property MagicCastingStates State
            {
                MagicCastingStates __clrcall get() sealed
                {
                    auto self = this->As<MagicCaster^>();
                    return (MagicCastingStates)Memory::ReadInt32(self->Address + 0x30, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="MagicCaster.Cost"/>.
            /// </summary>
            virtual property System::Single Cost
            {
                System::Single __clrcall get() sealed
                {
                    auto self = this->As<MagicCaster^>();
                    return Memory::ReadFloat(self->Address + 0x38, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ActorMagicCaster.Owner"/>.
            /// </summary>
            virtual property Actor^ Owner
            {
                Actor^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<Actor^>(Memory::ReadPointer(this->Address + 0xB8, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ActorMagicCaster.EffectLight"/>.
            /// </summary>
            virtual property BSLight^ EffectLight
            {
                BSLight^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<BSLight^>(Memory::ReadPointer(this->Address + 0xC8, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ActorMagicCaster.EffectNode"/>.
            /// </summary>
            virtual property NiNode^ EffectNode
            {
                NiNode^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiNode^>(Memory::ReadPointer(this->Address + 0xC0, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ActorMagicCaster.CasterRace"/>.
            /// </summary>
            virtual property TESRace^ CasterRace
            {
                TESRace^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESRace^>(Memory::ReadPointer(this->Address + 0x90, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ActorMagicCaster.FireNode"/>.
            /// </summary>
            virtual property NiNode^ FireNode
            {
                NiNode^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiNode^>(Memory::ReadPointer(this->Address + 0x78, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ActorMagicCaster.ActorCasterType"/>.
            /// </summary>
            virtual property EquippedSpellSlots ActorCasterType
            {
                EquippedSpellSlots __clrcall get() sealed
                {
                    return (EquippedSpellSlots)Memory::ReadInt32(this->Address + 0xF4, false);
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESImageSpaceModifier"/>.
        /// </summary>
        private ref class impl_TESImageSpaceModifier sealed : public VirtualObject, public TESImageSpaceModifier
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
            
            /// <summary>
            /// Implementation of method <see cref="TESImageSpaceModifier.Apply"/>.
            /// </summary>
            virtual void __clrcall Apply(System::Single strength, NiNode^ node) sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESImageSpaceModifier_Apply), self->Address, strength, node != nullptr ? node->Address : System::IntPtr::Zero);
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESImageSpaceModifier.Remove"/>.
            /// </summary>
            virtual void __clrcall Remove() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESImageSpaceModifier_Remove), 0, 0, self->Address);
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="MagicTarget"/>.
        /// </summary>
        private ref class impl_MagicTarget sealed : public VirtualObject, public MagicTarget
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="MagicTarget.ActiveEffects"/>.
            /// </summary>
            virtual property ListNode<ActiveEffect^>^ ActiveEffects
            {
                ListNode<ActiveEffect^>^ __clrcall get() sealed
                {
                    auto self = this->As<MagicTarget^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x38);
                    return MemoryObject::FromAddress<ListNode<ActiveEffect^>^>(ptr);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="MagicTarget.HasMagicEffectWithKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasMagicEffectWithKeyword(BGSKeyword^ keyword, MagicItem^% item) sealed
            {
                auto self = this->As<MagicTarget^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                stack10 s;
                System::UInt64 p = MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::MagicTarget_HasMagicEffectWithKeyword), self->Address, keyword->Address, s.ptr()));
                if((p & 0xFF) == 0) return false;
                System::IntPtr itemPtr = System::IntPtr(s.get<void*>(0));
                if(itemPtr != System::IntPtr::Zero) item = MemoryObject::FromAddress<MagicItem^>(itemPtr);
                return true;
            }
            
            /// <summary>
            /// Implementation of method <see cref="MagicTarget.HasMagicEffectWithKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasMagicEffectWithKeywordText(System::String^ keyword, MagicItem^% item) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasMagicEffectWithKeyword(kw, item)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of method <see cref="MagicTarget.HasMagicEffect"/>.
            /// </summary>
            virtual bool __clrcall HasMagicEffect(EffectSetting^ effect) sealed
            {
                auto self = this->As<MagicTarget^>();
                MCH::e<EffectSetting^>(effect, "effect");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::MagicTarget_HasMagicEffect), self->Address, effect->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="MagicTarget.DispelEffectsWithArchetype"/>.
            /// </summary>
            virtual void __clrcall DispelEffectsWithArchetype(Archetypes archetype, TESObjectREFR^ onlyFromCaster) sealed
            {
                auto self = this->As<MagicTarget^>();
                MCH::e<TESObjectREFR^>(onlyFromCaster, nullptr);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::MagicTarget_DispelEffectsWithArchetype), self->Address, (int)archetype, onlyFromCaster != nullptr ? onlyFromCaster->Address : System::IntPtr::Zero);
            }
            
            /// <summary>
            /// Implementation of property <see cref="MagicTarget.HasMagicEffectThatCausesDamage"/>.
            /// </summary>
            virtual property bool HasMagicEffectThatCausesDamage
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<MagicTarget^>();
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::MagicTarget_HasMagicEffectThatCausesDamage_Get), self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="MagicTarget.FindFirstEffectWithArchetype"/>.
            /// </summary>
            virtual ActiveEffect^ __clrcall FindFirstEffectWithArchetype(Archetypes archetype, bool allowInactive) sealed
            {
                auto self = this->As<MagicTarget^>();
                auto ptr = Memory::InvokeCdecl(MCH::FromBase(GameAddress::MagicTarget_FindFirstEffectWithArchetype), self->Address, (int)archetype, allowInactive ? 1 : 0);
                return MemoryObject::FromAddress<ActiveEffect^>(ptr);
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="ExtraContainerChanges"/>.
        /// </summary>
        private ref class impl_ExtraContainerChanges sealed : public VirtualObject, public ExtraContainerChanges
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="BSExtraData.Next"/>.
            /// </summary>
            virtual property BSExtraData^ Next
            {
                BSExtraData^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<BSExtraData^>(Memory::ReadPointer(this->Address + 0x8, false));
                }
                void __clrcall set(BSExtraData^ value) sealed
                {
                    Memory::WritePointer(this->Address + 0x8, value != nullptr ? value->Address : System::IntPtr::Zero, false);
                }
            }
            
            /// <summary>
            /// Implementation of interface <see cref="ExtraContainerChanges.ItemEntry"/>.
            /// </summary>
            ref class impl_ItemEntry sealed : public MemoryObject, public ExtraContainerChanges::ItemEntry
            {
            public:
                /// <summary>
                /// Implementation of property <see cref="ExtraContainerChanges.ItemEntry.Template"/>.
                /// </summary>
                virtual property TESForm^ Template
                {
                    TESForm^ __clrcall get() sealed
                    {
                        return MemoryObject::FromAddress<TESForm^>(Memory::ReadPointer(this->Address + 0x0, false));
                    }
                }
                
                /// <summary>
                /// Implementation of property <see cref="ExtraContainerChanges.ItemEntry.ExtraData"/>.
                /// </summary>
                virtual property ListNode<BSExtraDataList^>^ ExtraData
                {
                    ListNode<BSExtraDataList^>^ __clrcall get() sealed
                    {
                        return MemoryObject::FromAddress<ListNode<BSExtraDataList^>^>(Memory::ReadPointer(this->Address + 0x8, false));
                    }
                }
                
                /// <summary>
                /// Implementation of property <see cref="ExtraContainerChanges.ItemEntry.Count"/>.
                /// </summary>
                virtual property System::Int32 Count
                {
                    System::Int32 __clrcall get() sealed
                    {
                        return Memory::ReadInt32(this->Address + 0x10, false);
                    }
                }
            };
            
            /// <summary>
            /// Implementation of interface <see cref="ExtraContainerChanges.Data"/>.
            /// </summary>
            ref class impl_Data sealed : public MemoryObject, public ExtraContainerChanges::Data
            {
            public:
                /// <summary>
                /// Implementation of property <see cref="ExtraContainerChanges.Data.Owner"/>.
                /// </summary>
                virtual property TESObjectREFR^ Owner
                {
                    TESObjectREFR^ __clrcall get() sealed
                    {
                        return MemoryObject::FromAddress<TESObjectREFR^>(Memory::ReadPointer(this->Address + 0x8, false));
                    }
                }
                
                /// <summary>
                /// Implementation of property <see cref="ExtraContainerChanges.Data.Objects"/>.
                /// </summary>
                virtual property ListNode<ExtraContainerChanges::ItemEntry^>^ Objects
                {
                    ListNode<ExtraContainerChanges::ItemEntry^>^ __clrcall get() sealed
                    {
                        return MemoryObject::FromAddress<ListNode<ExtraContainerChanges::ItemEntry^>^>(Memory::ReadPointer(this->Address + 0x0, false));
                    }
                }
            };
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESObjectREFR"/>.
        /// </summary>
        private ref class impl_TESObjectREFR sealed : public VirtualObject, public TESObjectREFR
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.IncRef"/>.
            /// </summary>
            virtual void __clrcall IncRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                Memory::InterlockedIncrement32(self->Address + 0x8, false);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.DecRef"/>.
            /// </summary>
            virtual bool __clrcall DecRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                auto result = Memory::InterlockedDecrement32(self->Address + 0x8, false);
                if(this->Is<BSHandleRefObject^>()) result = result & 0x3FF;
                if(result == 0)
                {
                    self->InvokeVTableThisCall(0, 0x8);
                    return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.BaseForm"/>.
            /// </summary>
            virtual property TESForm^ BaseForm
            {
                TESForm^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESForm^>(Memory::ReadPointer(this->Address + 0x40, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.ParentCell"/>.
            /// </summary>
            virtual property TESObjectCELL^ ParentCell
            {
                TESObjectCELL^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESObjectCELL^>(Memory::ReadPointer(this->Address + 0x60, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.ExtraDataList"/>.
            /// </summary>
            virtual property BSExtraDataList^ ExtraDataList
            {
                BSExtraDataList^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<BSExtraDataList^>(this->Address + 0x70);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.Position"/>.
            /// </summary>
            virtual property NiPoint3^ Position
            {
                NiPoint3^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPoint3^>(this->Address + 0x54);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.Rotation"/>.
            /// </summary>
            virtual property NiPoint3^ Rotation
            {
                NiPoint3^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPoint3^>(this->Address + 0x48);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.Node"/>.
            /// </summary>
            virtual property NiNode^ Node
            {
                NiNode^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<NiNode^>(self->InvokeVTableThisCall(0, 0x380, 0));
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESObjectREFR.Activate"/>.
            /// </summary>
            virtual bool __clrcall Activate(TESObjectREFR^ activator, bool skipEvents) sealed
            {
                auto self = this;
                MCH::e<TESObjectREFR^>(activator, "activator");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_Activate), self->Address, activator->Address, 0, 0, 1, skipEvents ? 1 : 0)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.CurrentLocation"/>.
            /// </summary>
            virtual property BGSLocation^ CurrentLocation
            {
                BGSLocation^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<BGSLocation^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_CurrentLocation_Get), self->Address));
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESObjectREFR.OpenInventory"/>.
            /// </summary>
            virtual void __clrcall OpenInventory(ContainerOpenTypes type) sealed
            {
                auto self = this;
                if(!self->HasInventory) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_OpenInventory), self->Address, (int)type);
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.HasInventory"/>.
            /// </summary>
            virtual property bool HasInventory
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    if(self->FormType == FormTypes::Character) return true;
                    if(this->Is<TESObjectCONT^>()) return true;
                    return false;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.Inventory"/>.
            /// </summary>
            virtual property ExtraContainerChanges::Data^ Inventory
            {
                ExtraContainerChanges::Data^ __clrcall get() sealed
                {
                    auto self = this;
                    auto ptr = Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_Inventory_Get), self->Address);
                    return MemoryObject::FromAddress<ExtraContainerChanges::Data^>(ptr);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESObjectREFR.SetAnimationVariableBool"/>.
            /// </summary>
            virtual bool __clrcall SetAnimationVariableBool(System::String^ name, bool value) sealed
            {
                if(name == nullptr) return false;
                auto graph = this->As<IAnimationGraphManagerHolder^>();
                if(graph == nullptr) return false;
                StringRefHolder^ str = gcnew StringRefHolder(name);
                try
                {
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_SetAnimationVariableBool), graph->Address, str->AddressOf, value ? 1 : 0)) & 0xFF) == 0;
                }
                finally
                {
                    delete str;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESObjectREFR.GetMagicCaster"/>.
            /// </summary>
            virtual MagicCaster^ __clrcall GetMagicCaster(EquippedSpellSlots slot) sealed
            {
                auto self = this;
                int sl = (int)slot;
                if(sl < 0 || sl > 2) return nullptr;
                auto ptr = self->InvokeVTableThisCall(0, 0x2E0, sl);
                return MemoryObject::FromAddress<MagicCaster^>(ptr);
            }
            
            
            /// <summary>
            /// Implementation of method <see cref="TESObjectREFR.GetExtraData"/>.
            /// </summary>
            virtual BSExtraData^ __clrcall GetExtraData(ExtraDataTypes type) sealed
            {
                auto self = this;
                auto ptr = Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_GetExtraData), self->Address, (int)type);
                return MemoryObject::FromAddress<BSExtraData^>(ptr);
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESObjectREFR.GetSkeletonNode"/>.
            /// </summary>
            virtual NiNode^ __clrcall GetSkeletonNode(bool firstPerson) sealed
            {
                auto self = this;
                auto ptr = self->InvokeVTableThisCall(0, 0x378, firstPerson ? 1 : 0);
                return MemoryObject::FromAddress<NiNode^>(ptr);
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="Actor"/>.
        /// </summary>
        private ref class impl_Actor sealed : public VirtualObject, public Actor
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.BaseForm"/>.
            /// </summary>
            virtual property TESForm^ BaseForm
            {
                TESForm^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESForm^>(Memory::ReadPointer(this->Address + 0x40, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.ParentCell"/>.
            /// </summary>
            virtual property TESObjectCELL^ ParentCell
            {
                TESObjectCELL^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESObjectCELL^>(Memory::ReadPointer(this->Address + 0x60, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.ExtraDataList"/>.
            /// </summary>
            virtual property BSExtraDataList^ ExtraDataList
            {
                BSExtraDataList^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<BSExtraDataList^>(this->Address + 0x70);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.Position"/>.
            /// </summary>
            virtual property NiPoint3^ Position
            {
                NiPoint3^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPoint3^>(this->Address + 0x54);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.Rotation"/>.
            /// </summary>
            virtual property NiPoint3^ Rotation
            {
                NiPoint3^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPoint3^>(this->Address + 0x48);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.Node"/>.
            /// </summary>
            virtual property NiNode^ Node
            {
                NiNode^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<NiNode^>(self->InvokeVTableThisCall(0, 0x380, 0));
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESObjectREFR.Activate"/>.
            /// </summary>
            virtual bool __clrcall Activate(TESObjectREFR^ activator, bool skipEvents) sealed
            {
                auto self = this;
                MCH::e<TESObjectREFR^>(activator, "activator");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_Activate), self->Address, activator->Address, 0, 0, 1, skipEvents ? 1 : 0)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.CurrentLocation"/>.
            /// </summary>
            virtual property BGSLocation^ CurrentLocation
            {
                BGSLocation^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<BGSLocation^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_CurrentLocation_Get), self->Address));
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESObjectREFR.OpenInventory"/>.
            /// </summary>
            virtual void __clrcall OpenInventory(ContainerOpenTypes type) sealed
            {
                auto self = this;
                if(!self->HasInventory) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_OpenInventory), self->Address, (int)type);
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.HasInventory"/>.
            /// </summary>
            virtual property bool HasInventory
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    if(self->FormType == FormTypes::Character) return true;
                    if(this->Is<TESObjectCONT^>()) return true;
                    return false;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.Inventory"/>.
            /// </summary>
            virtual property ExtraContainerChanges::Data^ Inventory
            {
                ExtraContainerChanges::Data^ __clrcall get() sealed
                {
                    auto self = this;
                    auto ptr = Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_Inventory_Get), self->Address);
                    return MemoryObject::FromAddress<ExtraContainerChanges::Data^>(ptr);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESObjectREFR.SetAnimationVariableBool"/>.
            /// </summary>
            virtual bool __clrcall SetAnimationVariableBool(System::String^ name, bool value) sealed
            {
                if(name == nullptr) return false;
                auto graph = this->As<IAnimationGraphManagerHolder^>();
                if(graph == nullptr) return false;
                StringRefHolder^ str = gcnew StringRefHolder(name);
                try
                {
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_SetAnimationVariableBool), graph->Address, str->AddressOf, value ? 1 : 0)) & 0xFF) == 0;
                }
                finally
                {
                    delete str;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESObjectREFR.GetMagicCaster"/>.
            /// </summary>
            virtual MagicCaster^ __clrcall GetMagicCaster(EquippedSpellSlots slot) sealed
            {
                auto self = this;
                int sl = (int)slot;
                if(sl < 0 || sl > 2) return nullptr;
                auto ptr = self->InvokeVTableThisCall(0, 0x2E0, sl);
                return MemoryObject::FromAddress<MagicCaster^>(ptr);
            }
            
            
            /// <summary>
            /// Implementation of method <see cref="TESObjectREFR.GetExtraData"/>.
            /// </summary>
            virtual BSExtraData^ __clrcall GetExtraData(ExtraDataTypes type) sealed
            {
                auto self = this;
                auto ptr = Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_GetExtraData), self->Address, (int)type);
                return MemoryObject::FromAddress<BSExtraData^>(ptr);
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESObjectREFR.GetSkeletonNode"/>.
            /// </summary>
            virtual NiNode^ __clrcall GetSkeletonNode(bool firstPerson) sealed
            {
                auto self = this;
                auto ptr = self->InvokeVTableThisCall(0, 0x378, firstPerson ? 1 : 0);
                return MemoryObject::FromAddress<NiNode^>(ptr);
            }
            
            /// <summary>
            /// Implementation of property <see cref="MagicTarget.ActiveEffects"/>.
            /// </summary>
            virtual property ListNode<ActiveEffect^>^ ActiveEffects
            {
                ListNode<ActiveEffect^>^ __clrcall get() sealed
                {
                    auto self = this->As<MagicTarget^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x38);
                    return MemoryObject::FromAddress<ListNode<ActiveEffect^>^>(ptr);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="MagicTarget.HasMagicEffectWithKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasMagicEffectWithKeyword(BGSKeyword^ keyword, MagicItem^% item) sealed
            {
                auto self = this->As<MagicTarget^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                stack10 s;
                System::UInt64 p = MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::MagicTarget_HasMagicEffectWithKeyword), self->Address, keyword->Address, s.ptr()));
                if((p & 0xFF) == 0) return false;
                System::IntPtr itemPtr = System::IntPtr(s.get<void*>(0));
                if(itemPtr != System::IntPtr::Zero) item = MemoryObject::FromAddress<MagicItem^>(itemPtr);
                return true;
            }
            
            /// <summary>
            /// Implementation of method <see cref="MagicTarget.HasMagicEffectWithKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasMagicEffectWithKeywordText(System::String^ keyword, MagicItem^% item) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasMagicEffectWithKeyword(kw, item)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of method <see cref="MagicTarget.HasMagicEffect"/>.
            /// </summary>
            virtual bool __clrcall HasMagicEffect(EffectSetting^ effect) sealed
            {
                auto self = this->As<MagicTarget^>();
                MCH::e<EffectSetting^>(effect, "effect");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::MagicTarget_HasMagicEffect), self->Address, effect->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="MagicTarget.DispelEffectsWithArchetype"/>.
            /// </summary>
            virtual void __clrcall DispelEffectsWithArchetype(Archetypes archetype, TESObjectREFR^ onlyFromCaster) sealed
            {
                auto self = this->As<MagicTarget^>();
                MCH::e<TESObjectREFR^>(onlyFromCaster, nullptr);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::MagicTarget_DispelEffectsWithArchetype), self->Address, (int)archetype, onlyFromCaster != nullptr ? onlyFromCaster->Address : System::IntPtr::Zero);
            }
            
            /// <summary>
            /// Implementation of property <see cref="MagicTarget.HasMagicEffectThatCausesDamage"/>.
            /// </summary>
            virtual property bool HasMagicEffectThatCausesDamage
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<MagicTarget^>();
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::MagicTarget_HasMagicEffectThatCausesDamage_Get), self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="MagicTarget.FindFirstEffectWithArchetype"/>.
            /// </summary>
            virtual ActiveEffect^ __clrcall FindFirstEffectWithArchetype(Archetypes archetype, bool allowInactive) sealed
            {
                auto self = this->As<MagicTarget^>();
                auto ptr = Memory::InvokeCdecl(MCH::FromBase(GameAddress::MagicTarget_FindFirstEffectWithArchetype), self->Address, (int)archetype, allowInactive ? 1 : 0);
                return MemoryObject::FromAddress<ActiveEffect^>(ptr);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.GetActorValue"/>.
            /// </summary>
            virtual System::Single __clrcall GetActorValue(ActorValueIndices id) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                return (float)self->InvokeVTableThisCallF(0, 0x8, (int)id);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.GetActorValueMax"/>.
            /// </summary>
            virtual System::Single __clrcall GetActorValueMax(ActorValueIndices id) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                return (float)self->InvokeVTableThisCallF(0, 0x10, (int)id);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.GetBaseActorValue"/>.
            /// </summary>
            virtual System::Single __clrcall GetBaseActorValue(ActorValueIndices id) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                return (float)self->InvokeVTableThisCallF(0, 0x18, (int)id);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.DamageActorValue"/>.
            /// </summary>
            virtual void __clrcall DamageActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                if(id == ActorValueIndices::Health)
                {
                    auto actor = this->As<Actor^>();
                    if(actor != nullptr)
                    {
                        auto resultPtr = actor->InvokeVTableThisCall(0, 0x2F0);
                        if((MCH::u(resultPtr) & 0xFF) != 0)
                        {
                            actor->InvokeVTableThisCall(0, 0x820, 0, amount);
                            return;
                        }
                    }
                }
                self->InvokeVTableThisCall(0, 0x30, 2, (int)id, amount);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.RestoreActorValue"/>.
            /// </summary>
            virtual void __clrcall RestoreActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto actor = this->As<Actor^>();
                if(actor == nullptr) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::ActorValueOwner_RestoreActorValue), actor->Address, (int)id, amount);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.ForceActorValue"/>.
            /// </summary>
            virtual void __clrcall ForceActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                amount -= self->GetActorValue(id);
                self->InvokeVTableThisCall(0, 0x30, 0, (int)id, amount);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.ModActorValue"/>.
            /// </summary>
            virtual void __clrcall ModActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                self->InvokeVTableThisCall(0, 0x30, 0, (int)id, amount);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.SetActorValue"/>.
            /// </summary>
            virtual void __clrcall SetActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                self->InvokeVTableThisCall(0, 0x38, (int)id, amount);
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.IncRef"/>.
            /// </summary>
            virtual void __clrcall IncRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                Memory::InterlockedIncrement32(self->Address + 0x8, false);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.DecRef"/>.
            /// </summary>
            virtual bool __clrcall DecRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                auto result = Memory::InterlockedDecrement32(self->Address + 0x8, false);
                if(this->Is<BSHandleRefObject^>()) result = result & 0x3FF;
                if(result == 0)
                {
                    self->InvokeVTableThisCall(0, 0x8);
                    return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.Race"/>.
            /// </summary>
            virtual property TESRace^ Race
            {
                TESRace^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESRace^>(Memory::ReadPointer(this->Address + 0x1F0, false));
                }
                void __clrcall set(TESRace^ value) sealed
                {
                    auto self = this;
                    MCH::e<TESRace^>(value, "value");
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_Race_Set), 0, 0, self->Address, value->Address);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.UpdateMovementControllerPosition"/>.
            /// </summary>
            virtual void __clrcall UpdateMovementControllerPosition(NiPoint3^ pos) sealed
            {
                auto self = this;
                if(pos == nullptr) throw gcnew System::ArgumentNullException("pos");
                auto controller = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_UpdateMovementControllerPosition), self->Address);
                if(controller != System::IntPtr::Zero)
                {
                    auto type = this->MovementState;
                    if(type != bhkCharacterStateTypes::Flying)
                    {
                        stack10 alloc;
                        alloc.set(0, pos->X * 0.0142875f);
                        alloc.set(4, pos->Y * 0.0142875f);
                        alloc.set(8, pos->Z * 0.0142875f);
                        auto vtable = Memory::ReadPointer(controller, false);
                        Memory::InvokeCdecl(vtable + 24, controller, alloc.ptr(), 1, 0);
                    }
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.AddPerk"/>.
            /// </summary>
            virtual void __clrcall AddPerk(BGSPerk^ perk) sealed
            {
                auto self = this;
                MCH::e<BGSPerk^>(perk, "perk");
                self->InvokeVTableThisCall(0, 0x7D8, perk->Address, 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.AddShout"/>.
            /// </summary>
            virtual void __clrcall AddShout(TESShout^ shout) sealed
            {
                auto self = this;
                MCH::e<TESShout^>(shout, "shout");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_AddShout), self->Address, shout->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.AddSpell"/>.
            /// </summary>
            virtual bool __clrcall AddSpell(SpellItem^ spell, bool showLearnedMessage) sealed
            {
                auto self = this;
                MCH::e<SpellItem^>(spell, "spell");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_AddSpell), 0, 0, self->Address, spell->Address, showLearnedMessage ? 1 : 0)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.AllowBleedoutDialogue"/>.
            /// </summary>
            virtual void __clrcall AllowBleedoutDialogue(bool allow) sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_AllowBleedoutDialogue), 0, 0, self->Address, allow ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.AllowPCDialogue"/>.
            /// </summary>
            virtual void __clrcall AllowPCDialogue(bool allow) sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_AllowPCDialogue), 0, 0, self->Address, allow ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.ClearArrested"/>.
            /// </summary>
            virtual void __clrcall ClearArrested() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ClearArrested), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.CanFlyHere"/>.
            /// </summary>
            virtual property bool CanFlyHere
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_CanFlyHere_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.ClearExpressionOverride"/>.
            /// </summary>
            virtual void __clrcall ClearExpressionOverride() sealed
            {
                auto self = this;
                auto ptr = self->InvokeVTableThisCall(0, 0x318);
                if(ptr == System::IntPtr::Zero) return;
                Memory::WriteUInt8(ptr + 542, 0, false);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.ClearExtraArrows"/>.
            /// </summary>
            virtual void __clrcall ClearExtraArrows() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ClearExtraArrows), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.ClearKeepOffsetFromActor"/>.
            /// </summary>
            virtual void __clrcall ClearKeepOffsetFromActor() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ClearKeepOffsetFromActor), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.ClearLookAtObject"/>.
            /// </summary>
            virtual void __clrcall ClearLookAtObject() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ClearLookAtObject), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.Dismount"/>.
            /// </summary>
            virtual bool __clrcall Dismount() sealed
            {
                auto self = this;
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_Dismount), 0, 0, self->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.DispelAllSpells"/>.
            /// </summary>
            virtual void __clrcall DispelAllSpells() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_DispelAllSpells), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.DispelSpell"/>.
            /// </summary>
            virtual bool __clrcall DispelSpell(SpellItem^ spell) sealed
            {
                auto self = this;
                MCH::e<SpellItem^>(spell, "spell");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_DispelSpell), 0, 0, self->Address, spell->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.DoCombatSpellApply"/>.
            /// </summary>
            virtual void __clrcall DoCombatSpellApply(SpellItem^ spell, TESObjectREFR^ target) sealed
            {
                auto self = this;
                MCH::e<SpellItem^>(spell, "spell");
                MCH::e<TESObjectREFR^>(target, "target");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_DoCombatSpellApply), 0, 0, self->Address, spell->Address, target->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.DrawWeapon"/>.
            /// </summary>
            virtual void __clrcall DrawWeapon() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_DrawWeapon), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.EnableAI"/>.
            /// </summary>
            virtual void __clrcall EnableAI(bool enable) sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_EnableAI), 0, 0, self->Address, enable ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.EndDeferredKill"/>.
            /// </summary>
            virtual void __clrcall EndDeferredKill() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_EndDeferredKill), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.EquipItem"/>.
            /// </summary>
            virtual void __clrcall EquipItem(TESForm^ form, bool preventUnequip, bool silent) sealed
            {
                auto self = this;
                MCH::e<TESForm^>(form, "form");
                auto has3d = MCH::u(form->InvokeVTableThisCall(0, 0x138));
                if((has3d & 0xFF) == 0) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_EquipItem), 0, 0, self->Address, form->Address, preventUnequip ? 1 : 0, silent ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.EquipShout"/>.
            /// </summary>
            virtual void __clrcall EquipShout(TESShout^ shout) sealed
            {
                auto self = this;
                MCH::e<TESShout^>(shout, "shout");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_EquipShout), 0, 0, self->Address, shout->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.EvaluatePackage"/>.
            /// </summary>
            virtual void __clrcall EvaluatePackage() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_EvaluatePackage), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetBribeAmount"/>.
            /// </summary>
            virtual System::Int32 __clrcall GetBribeAmount() sealed
            {
                auto self = this;
                return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetBribeAmount), 0, 0, self->Address)) & 0xFFFFFFFF);
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.CombatState"/>.
            /// </summary>
            virtual property ActorCombatStates CombatState
            {
                ActorCombatStates __clrcall get() sealed
                {
                    auto self = this;
                    return (ActorCombatStates)(System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_CombatState_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.CombatTarget"/>.
            /// </summary>
            virtual property Actor^ CombatTarget
            {
                Actor^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<Actor^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_CombatTarget_Get), 0, 0, self->Address));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.CrimeFaction"/>.
            /// </summary>
            virtual property TESFaction^ CrimeFaction
            {
                TESFaction^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<TESFaction^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_CrimeFaction_Get), 0, 0, self->Address));
                }
                void __clrcall set(TESFaction^ value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_CrimeFaction_Set), 0, 0, self->Address, value != nullptr ? value->Address : System::IntPtr::Zero);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.CurrentPackage"/>.
            /// </summary>
            virtual property TESPackage^ CurrentPackage
            {
                TESPackage^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<TESPackage^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_CurrentPackage_Get), 0, 0, self->Address));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.DialogueTarget"/>.
            /// </summary>
            virtual property Actor^ DialogueTarget
            {
                Actor^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<Actor^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_DialogueTarget_Get), 0, 0, self->Address));
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetEquippedArmorInSlot"/>.
            /// </summary>
            virtual TESObjectARMO^ __clrcall GetEquippedArmorInSlot(EquipSlots slot) sealed
            {
                auto self = this;
                auto ptr = Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_Inventory_Get), self->Address);
                if(ptr == System::IntPtr::Zero) return nullptr;
                return MemoryObject::FromAddressSafeCast<TESObjectARMO^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetEquippedArmorInSlot), ptr, (int)slot));
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetEquippedItemType"/>.
            /// </summary>
            virtual EquippedItemTypes __clrcall GetEquippedItemType(EquippedHandSlots slot) sealed
            {
                auto self = this;
                auto ptr = Memory::ReadPointer(self->Address + 0xF0, false);
                int rs = 0;
                if(ptr != System::IntPtr::Zero)
                {
                    System::IntPtr obj = System::IntPtr::Zero;
                    if(slot == EquippedHandSlots::LeftHand) obj = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetEquippedItemType_LeftHand), ptr);
                    else if(slot == EquippedHandSlots::RightHand) obj = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetEquippedItemType_RightHand), ptr);
                    if(obj != System::IntPtr::Zero)
                    {
                        auto typeId = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetEquippedItemType_ItemType), obj);
                        rs = (int)(typeId.ToInt64() & 0xFFFF);
                    }
                }
                return (EquippedItemTypes)rs;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetEquippedShield"/>.
            /// </summary>
            virtual TESObjectARMO^ __clrcall GetEquippedShield() sealed
            {
                auto self = this;
                return MemoryObject::FromAddress<TESObjectARMO^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetEquippedShield), 0, 0, self->Address));
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetEquippedShout"/>.
            /// </summary>
            virtual TESShout^ __clrcall GetEquippedShout() sealed
            {
                auto self = this;
                return MemoryObject::FromAddress<TESShout^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetEquippedShout), 0, 0, self->Address));
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetEquippedSpell"/>.
            /// </summary>
            virtual SpellItem^ __clrcall GetEquippedSpell(EquippedSpellSlots slot) sealed
            {
                auto self = this;
                System::UInt32 arg = (System::UInt32)slot;
                if(arg >= 4) return nullptr;
                return MemoryObject::FromAddress<SpellItem^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetEquippedSpell), 0, 0, self->Address, arg));
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetFactionRank"/>.
            /// </summary>
            virtual System::Int32 __clrcall GetFactionRank(TESFaction^ faction) sealed
            {
                auto self = this;
                MCH::e<TESFaction^>(faction, "faction");
                return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetFactionRank), 0, 0, self->Address, faction->Address)) & 0xFFFFFFFF);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetFactionReaction"/>.
            /// </summary>
            virtual FactionReactions __clrcall GetFactionReaction(Actor^ other) sealed
            {
                auto self = this;
                MCH::e<Actor^>(other, "other");
                return (FactionReactions)(System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetFactionReaction), 0, 0, self->Address, other->Address)) & 0xFFFFFFFF);
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.FlyingState"/>.
            /// </summary>
            virtual property FlyingStates FlyingState
            {
                FlyingStates __clrcall get() sealed
                {
                    auto self = this;
                    return (FlyingStates)(System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_FlyingState_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.ForcedLandingMarker"/>.
            /// </summary>
            virtual property TESObjectREFR^ ForcedLandingMarker
            {
                TESObjectREFR^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<TESObjectREFR^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ForcedLandingMarker_Get), 0, 0, self->Address));
                }
                void __clrcall set(TESObjectREFR^ value) sealed
                {
                    auto self = this;
                    MCH::e<TESObjectREFR^>(value, nullptr);
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ForcedLandingMarker_Set), 0, 0, self->Address, value != nullptr ? value->Address : System::IntPtr::Zero);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetGoldAmount"/>.
            /// </summary>
            virtual System::Int32 __clrcall GetGoldAmount() sealed
            {
                auto self = this;
                return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetGoldAmount), 0, 0, self->Address)) & 0xFFFFFFFF);
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.HighestRelationshipRank"/>.
            /// </summary>
            virtual property RelationshipRanks HighestRelationshipRank
            {
                RelationshipRanks __clrcall get() sealed
                {
                    auto self = this;
                    return (RelationshipRanks)(System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_HighestRelationshipRank_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.KilledBy"/>.
            /// </summary>
            virtual property Actor^ KilledBy
            {
                Actor^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<Actor^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_KilledBy_Get), 0, 0, self->Address));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.Level"/>.
            /// </summary>
            virtual property System::Int32 Level
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this;
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_Level_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.BaseActor"/>.
            /// </summary>
            virtual property TESNPC^ BaseActor
            {
                TESNPC^ __clrcall get() sealed
                {
                    auto self = this;
                    auto npc = MemoryObject::FromAddress<TESNPC^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_BaseActor_Get), 0, 0, self->Address));
                    if(npc == nullptr)
                    {
                    auto obj = self->BaseForm;
                    if(obj != nullptr)
                    npc = obj->As<TESNPC^>();
                    }
                    return npc;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.LightLevel"/>.
            /// </summary>
            virtual property System::Single LightLevel
            {
                System::Single __clrcall get() sealed
                {
                    auto self = this;
                    return (float)Memory::InvokeCdeclF(MCH::FromBase(GameAddress::Actor_LightLevel_Get), 0, 0, self->Address);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.LowestRelationshipRank"/>.
            /// </summary>
            virtual property RelationshipRanks LowestRelationshipRank
            {
                RelationshipRanks __clrcall get() sealed
                {
                    auto self = this;
                    return (RelationshipRanks)(System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_LowestRelationshipRank_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.NoBleedoutRecovery"/>.
            /// </summary>
            virtual property bool NoBleedoutRecovery
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_NoBleedoutRecovery_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_NoBleedoutRecovery_Set), 0, 0, self->Address, value ? 1 : 0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.ReceivesPlayerControls"/>.
            /// </summary>
            virtual property bool ReceivesPlayerControls
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ReceivesPlayerControls_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ReceivesPlayerControls_Set), 0, 0, self->Address, value ? 1 : 0);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetRelationshipRank"/>.
            /// </summary>
            virtual RelationshipRanks __clrcall GetRelationshipRank(Actor^ other) sealed
            {
                auto self = this;
                MCH::e<Actor^>(other, "other");
                return (RelationshipRanks)(System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetRelationshipRank), 0, 0, self->Address, other->Address)) & 0xFFFFFFFF);
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.SitState"/>.
            /// </summary>
            virtual property ActorActionStates SitState
            {
                ActorActionStates __clrcall get() sealed
                {
                    auto self = this;
                    return (ActorActionStates)(System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SitState_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.SleepState"/>.
            /// </summary>
            virtual property ActorActionStates SleepState
            {
                ActorActionStates __clrcall get() sealed
                {
                    auto self = this;
                    return (ActorActionStates)(System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SleepState_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.VoiceRecoveryTime"/>.
            /// </summary>
            virtual property System::Single VoiceRecoveryTime
            {
                System::Single __clrcall get() sealed
                {
                    auto self = this;
                    return (float)Memory::InvokeCdeclF(MCH::FromBase(GameAddress::Actor_VoiceRecoveryTime_Get), 0, 0, self->Address);
                }
                void __clrcall set(System::Single value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_VoiceRecoveryTime_Set), 0, 0, self->Address, value);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.WarmthRating"/>.
            /// </summary>
            virtual property System::Single WarmthRating
            {
                System::Single __clrcall get() sealed
                {
                    auto self = this;
                    return (float)Memory::InvokeCdeclF(MCH::FromBase(GameAddress::Actor_WarmthRating_Get), 0, 0, self->Address);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.HasAssociation"/>.
            /// </summary>
            virtual bool __clrcall HasAssociation(BGSAssociationType^ type, Actor^ other) sealed
            {
                auto self = this;
                MCH::e<BGSAssociationType^>(type, "type");
                MCH::e<Actor^>(other, nullptr);
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_HasAssociation), 0, 0, self->Address, type->Address, other != nullptr ? other->Address : System::IntPtr::Zero)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.HasFamilyRelationship"/>.
            /// </summary>
            virtual bool __clrcall HasFamilyRelationship(Actor^ other) sealed
            {
                auto self = this;
                MCH::e<Actor^>(other, nullptr);
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_HasFamilyRelationship), 0, 0, self->Address, other != nullptr ? other->Address : System::IntPtr::Zero)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.HasLOS_Papyrus"/>.
            /// </summary>
            virtual bool __clrcall HasLOS_Papyrus(TESObjectREFR^ other) sealed
            {
                auto self = this;
                MCH::e<TESObjectREFR^>(other, "other");
                if(other->FormType != FormTypes::Character && !self->Equals(PlayerCharacter::Instance)) return false;
                stack10 s;
                auto ptrResult = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_HasLOS_Papyrus), self->Address, other->Address, s.ptr());
                auto result = MCH::u(ptrResult);
                return (result & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.HasParentRelationship"/>.
            /// </summary>
            virtual bool __clrcall HasParentRelationship(Actor^ other) sealed
            {
                auto self = this;
                MCH::e<Actor^>(other, "other");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_HasParentRelationship), 0, 0, self->Address, other->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsAlarmed"/>.
            /// </summary>
            virtual property bool IsAlarmed
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsAlarmed_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsAllowedToFly"/>.
            /// </summary>
            virtual property bool IsAllowedToFly
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsAllowedToFly_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsAllowedToFly_Set), 0, 0, self->Address, value ? 1 : 0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsArrested"/>.
            /// </summary>
            virtual property bool IsArrested
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsArrested_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsBleedingOut"/>.
            /// </summary>
            virtual property bool IsBleedingOut
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsBleedingOut_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsDead"/>.
            /// </summary>
            virtual property bool IsDead
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsDead_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.CanDetect"/>.
            /// </summary>
            virtual bool __clrcall CanDetect(Actor^ target) sealed
            {
                auto self = this;
                MCH::e<Actor^>(target, "target");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_CanDetect), 0, 0, target->Address, self->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.IsEquipped"/>.
            /// </summary>
            virtual bool __clrcall IsEquipped(TESForm^ form) sealed
            {
                auto self = this;
                MCH::e<TESForm^>(form, "form");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsEquipped), 0, 0, self->Address, form->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsPlayersLastRiddenHorse"/>.
            /// </summary>
            virtual property bool IsPlayersLastRiddenHorse
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsPlayersLastRiddenHorse_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsArrestingTarget"/>.
            /// </summary>
            virtual property bool IsArrestingTarget
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsArrestingTarget_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsAlerted"/>.
            /// </summary>
            virtual property bool IsAlerted
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsAlerted_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsAlerted_Set), 0, 0, self->Address, value ? 1 : 0);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.HasPerk"/>.
            /// </summary>
            virtual bool __clrcall HasPerk(BGSPerk^ perk) sealed
            {
                auto self = this;
                MCH::e<BGSPerk^>(perk, "perk");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_HasPerk), 0, 0, self->Address, perk->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.HasSpell"/>.
            /// </summary>
            virtual bool __clrcall HasSpell(TESForm^ spellOrShout) sealed
            {
                auto self = this;
                if(spellOrShout == nullptr) throw gcnew System::ArgumentNullException("spellOrShout");
                auto formType = spellOrShout->FormType;
                if(formType == FormTypes::Spell)
                {
                    auto arg = spellOrShout->As<SpellItem^>();
                    if(arg != nullptr) return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_HasSpell_Spell), self->Address, arg->Address)) & 0xFF) != 0;
                }
                else if(formType == FormTypes::Shout)
                {
                    auto arg = spellOrShout->As<TESShout^>();
                    if(arg != nullptr) return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_HasSpell_Shout), self->Address, arg->Address)) & 0xFF) != 0;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsBribed"/>.
            /// </summary>
            virtual property bool IsBribed
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsBribed_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsBribed_Set), 0, 0, self->Address, value ? 1 : 0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsChild"/>.
            /// </summary>
            virtual property bool IsChild
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsChild_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsCommandedActor"/>.
            /// </summary>
            virtual property bool IsCommandedActor
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsCommandedActor_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsDoingFavor"/>.
            /// </summary>
            virtual property bool IsDoingFavor
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsDoingFavor_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsDoingFavor_Set), 0, 0, self->Address, value ? 1 : 0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsEssential"/>.
            /// </summary>
            virtual property bool IsEssential
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsEssential_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsFlying"/>.
            /// </summary>
            virtual property bool IsFlying
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsFlying_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsGhost"/>.
            /// </summary>
            virtual property bool IsGhost
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsGhost_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsGhost_Set), 0, 0, self->Address, value ? 1 : 0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsGuard"/>.
            /// </summary>
            virtual property bool IsGuard
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsGuard_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.IsHostileToActor"/>.
            /// </summary>
            virtual bool __clrcall IsHostileToActor(Actor^ target) sealed
            {
                auto self = this;
                MCH::e<Actor^>(target, "target");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsHostileToActor), 0, 0, self->Address, target->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsInCombat"/>.
            /// </summary>
            virtual property bool IsInCombat
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsInCombat_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.IsInFaction"/>.
            /// </summary>
            virtual bool __clrcall IsInFaction(TESFaction^ faction) sealed
            {
                auto self = this;
                MCH::e<TESFaction^>(faction, "faction");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsInFaction), 0, 0, self->Address, faction->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsInKillmove"/>.
            /// </summary>
            virtual property bool IsInKillmove
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsInKillmove_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsIntimidated"/>.
            /// </summary>
            virtual property bool IsIntimidated
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsIntimidated_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsIntimidated_Set), 0, 0, self->Address, value ? 1 : 0 );
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsOnMount"/>.
            /// </summary>
            virtual property bool IsOnMount
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsOnMount_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsOverEncumbered"/>.
            /// </summary>
            virtual property bool IsOverEncumbered
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsOverEncumbered_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsPlayerTeammate"/>.
            /// </summary>
            virtual property bool IsPlayerTeammate
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsPlayerTeammate_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsRunning"/>.
            /// </summary>
            virtual property bool IsRunning
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsRunning_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsSneaking"/>.
            /// </summary>
            virtual property bool IsSneaking
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsSneaking_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    if(this->IsSneaking == value) return;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsSneaking_Set), 0, 0, self->Address); // This is a toggle
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsSprinting"/>.
            /// </summary>
            virtual property bool IsSprinting
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsSprinting_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsTrespassing"/>.
            /// </summary>
            virtual property bool IsTrespassing
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsTrespassing_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsUnconscious"/>.
            /// </summary>
            virtual property bool IsUnconscious
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsUnconscious_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsUnconscious_Set), 0, 0, self->Address, value ? 1 : 0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsWeaponDrawn"/>.
            /// </summary>
            virtual property bool IsWeaponDrawn
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsWeaponDrawn_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.Kill"/>.
            /// </summary>
            virtual void __clrcall Kill(Actor^ killer, bool noEvents, bool force) sealed
            {
                auto self = this;
                MCH::e<Actor^>(killer, nullptr);
                if(!force)
                {
                    auto mt = this->As<MagicTarget^>();
                    if(mt == nullptr) return;
                    auto res1 = MCH::u(mt->InvokeVTableThisCall(0, 0x20));
                    auto res2 = MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_Kill_1), self->Address));
                    bool ok = (res1 & 0xFF) == 0 || (res2 & 0xFF) != 0;
                    if(!ok) return;
                }
                if((Memory::ReadUInt32(self->Address + 0xC0, false) & 0x1E00000) == 0xE00000)
                {
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_Kill_2), self->Address, 0, noEvents ? 0 : 1);
                }
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_Kill_3), self->Address, killer != nullptr ? killer->Address : System::IntPtr::Zero, (double)0.0, noEvents ? 0 : 1, 0);
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsPlayer"/>.
            /// </summary>
            virtual property bool IsPlayer
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    auto plr = PlayerCharacter::Instance;
                    if(plr == nullptr) return false;
                    return self->Address == plr->Address;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.RemoveFromFaction"/>.
            /// </summary>
            virtual void __clrcall RemoveFromFaction(TESFaction^ faction) sealed
            {
                auto self = this;
                MCH::e<TESFaction^>(faction, "faction");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_RemoveFromFaction), 0, 0, self->Address, faction->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.RemoveFromAllFactions"/>.
            /// </summary>
            virtual void __clrcall RemoveFromAllFactions() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_RemoveFromAllFactions), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.RemovePerk"/>.
            /// </summary>
            virtual void __clrcall RemovePerk(BGSPerk^ perk) sealed
            {
                auto self = this;
                MCH::e<BGSPerk^>(perk, "perk");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_RemovePerk), 0, 0, self->Address, perk->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.RemoveShout"/>.
            /// </summary>
            virtual bool __clrcall RemoveShout(TESShout^ shout) sealed
            {
                auto self = this;
                MCH::e<TESShout^>(shout, "shout");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_RemoveShout), 0, 0, self->Address, shout->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.RemoveSpell"/>.
            /// </summary>
            virtual bool __clrcall RemoveSpell(SpellItem^ spell) sealed
            {
                auto self = this;
                MCH::e<SpellItem^>(spell, "spell");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_RemoveSpell), 0, 0, self->Address, spell->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.ResetHealthAndLimbs"/>.
            /// </summary>
            virtual void __clrcall ResetHealthAndLimbs() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ResetHealthAndLimbs), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.Resurrect"/>.
            /// </summary>
            virtual void __clrcall Resurrect() sealed
            {
                auto self = this;
                System::IntPtr arg = System::IntPtr::Zero;
                if(self->InvokeVTableThisCall(0, 0x380) != System::IntPtr::Zero) arg = System::IntPtr(1);
                self->InvokeVTableThisCall(0, 0x558, 1, arg);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SendAssaultAlarm"/>.
            /// </summary>
            virtual void __clrcall SendAssaultAlarm(Actor^ assaulter) sealed
            {
                auto self = this;
                MCH::e<Actor^>(assaulter, "assaulter");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SendAssaultAlarm_1), self->Address, assaulter->Address);
                System::UInt32 flags = Memory::ReadUInt32(self->Address + 0xE0, false);
                if(((flags >> 30) & 1) != 0) return;
                auto process = Memory::ReadPointer(self->Address + 0xF0, false);
                if(process == System::IntPtr::Zero) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SendAssaultAlarm_2), process, self->Address, assaulter->Address, 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SendTrespassAlarm"/>.
            /// </summary>
            virtual void __clrcall SendTrespassAlarm(Actor^ criminal) sealed
            {
                auto self = this;
                MCH::e<Actor^>(criminal, "criminal");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SendTrespassAlarm), 0, 0, self->Address, criminal->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetAllowFlyingEx"/>.
            /// </summary>
            virtual void __clrcall SetAllowFlyingEx(bool allowFly, bool allowCrash, bool allowSearch) sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetAllowFlyingEx), 0, 0, self->Address, allowFly ? 1 : 0, allowCrash ? 1 : 0, allowSearch ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetAlpha"/>.
            /// </summary>
            virtual void __clrcall SetAlpha(System::Single alpha, bool fade) sealed
            {
                auto self = this;
                auto process = Memory::ReadPointer(self->Address + 0xF0, false);
                if(process == System::IntPtr::Zero) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetAlpha), 0, 0, self->Address, alpha, fade ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetAttackedByAllOnSight"/>.
            /// </summary>
            virtual void __clrcall SetAttackedByAllOnSight(bool should) sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetAttackedByAllOnSight), 0, 0, self->Address, should ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetCriticalStage"/>.
            /// </summary>
            virtual void __clrcall SetCriticalStage(ActorCriticalStages stage) sealed
            {
                auto self = this;
                int _s = (int)stage;
                if(_s < 0 || _s >= 5) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetCriticalStage), self->Address, (int)stage);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetDontMove"/>.
            /// </summary>
            virtual void __clrcall SetDontMove(bool dontMove) sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetDontMove), 0, 0, self->Address, dontMove ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetExpressionOverride"/>.
            /// </summary>
            virtual bool __clrcall SetExpressionOverride(System::Int32 expression, System::Single amount) sealed
            {
                auto self = this;
                if(expression <= 0 || expression > 16) return false;
                amount = System::Math::Min(1.0f, System::Math::Max(0.0f, amount));
                auto faceAnim = self->InvokeVTableThisCall(0, 0x318);
                if(faceAnim == System::IntPtr::Zero) return false;
                Memory::WriteUInt8(faceAnim + 0x21E, 0, false);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetExpressionOverride), faceAnim, expression, amount);
                Memory::WriteUInt8(faceAnim + 0x21E, 1, false);
                return true;
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsHeadTrackingEnabled"/>.
            /// </summary>
            virtual property bool IsHeadTrackingEnabled
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    System::UInt32 flags = Memory::ReadUInt32(self->Address + 0xC4, false);
                    return (flags & 8) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    System::UInt32 flags = Memory::ReadUInt32(self->Address + 0xC4, false);
                    if(value) flags |= 8;
                    else flags &= ~8;
                    Memory::WriteUInt32(self->Address + 0xC4, flags, false);
                    if(this->IsPlayer) this->SetAnimationVariableBool("IsNPC", value);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetLookAtObject"/>.
            /// </summary>
            virtual void __clrcall SetLookAtObject(TESObjectREFR^ target, bool whilePathing) sealed
            {
                auto self = this;
                MCH::e<TESObjectREFR^>(target, nullptr);
                if(target == nullptr)
                {
                    this->ClearLookAtObject();
                    return;
                }
                auto process = Memory::ReadPointer(self->Address + 0xF0, false);
                if(process == System::IntPtr::Zero) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetLookAtObject), 0, 0, self->Address, target->Address, whilePathing ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.ShowOnStealthMeter"/>.
            /// </summary>
            virtual property bool ShowOnStealthMeter
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    System::UInt32 flags = Memory::ReadUInt32(self->Address + 0x1FC, false);
                    bool notShowFlag = (flags & 0x4000000) != 0;
                    return !notShowFlag;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ShowOnStealthMeter_Set), 0, 0, self->Address, !value ? 1 : 0);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetOutfit"/>.
            /// </summary>
            virtual void __clrcall SetOutfit(BGSOutfit^ outfit, bool sleepOutfit) sealed
            {
                auto self = this;
                MCH::e<BGSOutfit^>(outfit, "outfit");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetOutfit), 0, 0, self->Address, outfit->Address, sleepOutfit ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetPlayerResistingArrest"/>.
            /// </summary>
            virtual void __clrcall SetPlayerResistingArrest() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetPlayerResistingArrest), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetPlayerTeammate"/>.
            /// </summary>
            virtual void __clrcall SetPlayerTeammate(bool teammate, bool canDoFavors) sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetPlayerTeammate), 0, 0, self->Address, teammate ? 1 : 0, canDoFavors ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetRelationshipRank"/>.
            /// </summary>
            virtual void __clrcall SetRelationshipRank(Actor^ other, RelationshipRanks rank) sealed
            {
                auto self = this;
                MCH::e<Actor^>(other, "other");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetRelationshipRank), 0, 0, self->Address, other->Address, (int)rank);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetRestrained"/>.
            /// </summary>
            virtual void __clrcall SetRestrained(bool restrained) sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetRestrained), 0, 0, self->Address, restrained ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetVehicle"/>.
            /// </summary>
            virtual void __clrcall SetVehicle(TESObjectREFR^ vehicle) sealed
            {
                auto self = this;
                MCH::e<TESObjectREFR^>(vehicle, nullptr);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetVehicle), 0, 0, self->Address, vehicle != nullptr ? vehicle->Address : System::IntPtr::Zero);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.ShowBarterMenu"/>.
            /// </summary>
            virtual void __clrcall ShowBarterMenu() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ShowBarterMenu), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.StartCombat"/>.
            /// </summary>
            virtual bool __clrcall StartCombat(Actor^ target) sealed
            {
                auto self = this;
                MCH::e<Actor^>(target, "target");
                if(self->IsPlayer) return false;
                if(Memory::ReadPointer(self->Address + 0xF0, false) == System::IntPtr::Zero) return false;
                if(Memory::ReadPointer(target->Address + 0xF0, false) == System::IntPtr::Zero) return false;
                if((MCH::u(self->InvokeVTableThisCall(0, 0x4C8, 0)) & 0xFF) != 0) return false;
                if((MCH::u(target->InvokeVTableThisCall(0, 0x4C8, 0)) & 0xFF) != 0) return false;
                if(!target->IsPlayer)
                {
                    auto p = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_StartCombat_1), self->Address);
                    if((MCH::u(p) & 0xFF) != 0) return false;
                }
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_StartCombat_2), Memory::ReadPointer(MCH::FromBase(GameAddress::Actor_StartCombat_3), false), self->Address, target->Address);
                return true;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.StartDeferredKill"/>.
            /// </summary>
            virtual void __clrcall StartDeferredKill() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_StartDeferredKill), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.StopCombatAlarm"/>.
            /// </summary>
            virtual void __clrcall StopCombatAlarm() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_StopCombatAlarm), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.StopCombat"/>.
            /// </summary>
            virtual void __clrcall StopCombat() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_StopCombat), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.TrapSoul"/>.
            /// </summary>
            virtual bool __clrcall TrapSoul(Actor^ target) sealed
            {
                auto self = this;
                MCH::e<Actor^>(target, "target");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_TrapSoul), 0, 0, self->Address, target->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.UnlockOwnedDoorsInCell"/>.
            /// </summary>
            virtual void __clrcall UnlockOwnedDoorsInCell() sealed
            {
                auto self = this;
                auto cell = this->ParentCell;
                if(cell == nullptr || !cell->IsInterior) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_UnlockOwnedDoorsInCell), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.UnequipAll"/>.
            /// </summary>
            virtual void __clrcall UnequipAll() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_UnequipAll), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.UnequipItemSlot"/>.
            /// </summary>
            virtual void __clrcall UnequipItemSlot(EquipSlots slot) sealed
            {
                auto self = this;
                auto data = Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_Inventory_Get), self->Address);
                if(data == System::IntPtr::Zero) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_UnequipItemSlot), data, (int)slot, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.UnequipItem"/>.
            /// </summary>
            virtual void __clrcall UnequipItem(TESForm^ form, bool preventEquip, bool silent) sealed
            {
                auto self = this;
                MCH::e<TESForm^>(form, "form");
                if(!form->Has3D) return;
                auto cont = Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_Inventory_Get), self->Address);
                if(cont == System::IntPtr::Zero) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_UnequipItem), 0, 0, self->Address, form->Address, preventEquip ? 1 : 0, silent ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.UnequipShout"/>.
            /// </summary>
            virtual void __clrcall UnequipShout(TESShout^ shout) sealed
            {
                auto self = this;
                MCH::e<TESShout^>(shout, "shout");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_UnequipShout), 0, 0, self->Address, shout->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.UnequipSpell"/>.
            /// </summary>
            virtual void __clrcall UnequipSpell(SpellItem^ spell, EquippedSpellSlots slot) sealed
            {
                auto self = this;
                MCH::e<SpellItem^>(spell, "spell");
                int _s = (int)slot;
                if(_s < 0 || _s >= 3) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_UnequipSpell), 0, 0, self->Address, spell->Address, (int)slot);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.EquipSpell"/>.
            /// </summary>
            virtual void __clrcall EquipSpell(SpellItem^ spell, EquippedSpellSlots slot) sealed
            {
                auto self = this;
                MCH::e<SpellItem^>(spell, "spell");
                int _s = (int)slot;
                if(_s < 0 || _s >= 3) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_EquipSpell), 0, 0, self->Address, spell->Address, (int)slot);
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.WillIntimidateSucceed"/>.
            /// </summary>
            virtual property bool WillIntimidateSucceed
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_WillIntimidateSucceed_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.WornHasKeyword"/>.
            /// </summary>
            virtual bool __clrcall WornHasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this;
                MCH::e<BGSKeyword^>(keyword, "keyword");
                auto cont = Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_Inventory_Get), self->Address);
                if(cont == System::IntPtr::Zero) return false;
                auto result = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_WornHasKeyword), cont, keyword->Address);
                return (MCH::u(result) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.WornHasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall WornHasKeywordText(System::String^ keyword) sealed
            {
                auto self = this;
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto cont = Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_Inventory_Get), self->Address);
                if(cont == System::IntPtr::Zero) return false;
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    auto result = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_WornHasKeyword), cont, kw->Address);
                    if((MCH::u(result) & 0xFF) != 0) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.ClearLookAtPosition"/>.
            /// </summary>
            virtual void __clrcall ClearLookAtPosition() sealed
            {
                auto self = this;
                auto process = Memory::ReadPointer(self->Address + 0xF0, false);
                if(process == System::IntPtr::Zero) return;
                auto race = this->Race;
                if(race == nullptr || !race->CanHeadTrack) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ClearLookAtPosition), process, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetLookAtPosition"/>.
            /// </summary>
            virtual void __clrcall SetLookAtPosition(NiPoint3^ position) sealed
            {
                auto self = this;
                if(position == nullptr)
                {
                    this->ClearLookAtPosition();
                    return;
                }
                auto process = Memory::ReadPointer(self->Address + 0xF0, false);
                if(process == System::IntPtr::Zero) return;
                auto race = this->Race;
                if(race == nullptr || !race->CanHeadTrack) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetLookAtPosition), process, self->Address, position->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.InterruptCast"/>.
            /// </summary>
            virtual void __clrcall InterruptCast() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_InterruptCast), self->Address, 0);
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsBeingRidden"/>.
            /// </summary>
            virtual property bool IsBeingRidden
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return MCH::b(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsBeingRidden_Get), self->Address));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsOnFlyingMount"/>.
            /// </summary>
            virtual property bool IsOnFlyingMount
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return MCH::b(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsOnFlyingMount_Get), self->Address));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.MovementState"/>.
            /// </summary>
            virtual property bhkCharacterStateTypes MovementState
            {
                bhkCharacterStateTypes __clrcall get() sealed
                {
                    auto self = this;
                    auto ptr = Memory::ReadPointer(self->Address + 0xF0, false);
                    if(ptr != System::IntPtr::Zero)
                    {
						ptr = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_UpdateMovementControllerPosition), ptr);
						if(ptr != System::IntPtr::Zero)
						{
							ptr = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_MovementState_Get), ptr + 480);
							return (bhkCharacterStateTypes)((int)(MCH::u(ptr) & 0xFF));
						}
                    }
                    return bhkCharacterStateTypes::Unknown;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsJumping"/>.
            /// </summary>
            virtual property bool IsJumping
            {
                bool __clrcall get() sealed
                {
                    return this->MovementState == bhkCharacterStateTypes::Jumping;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsFalling"/>.
            /// </summary>
            virtual property bool IsFalling
            {
                bool __clrcall get() sealed
                {
                    return this->MovementState == bhkCharacterStateTypes::InAir;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetMount"/>.
            /// </summary>
            virtual Actor^ __clrcall GetMount() sealed
            {
                auto self = this;
                Actor^ result = nullptr;
                MemoryAllocation^ alloc = Memory::Allocate(0x10, 0, false);
                try
                {
                    Memory::WritePointer(alloc->Address, System::IntPtr::Zero, false);
                    if(MCH::b(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetMount), self->Address, alloc->Address)))
                    {
                        result = MemoryObject::FromAddress<Actor^>(Memory::ReadPointer(alloc->Address, false));
                        if(result != nullptr) result->DecRef();
                    }
                }
                finally
                {
                    delete alloc;
                }
                return result;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetMountedBy"/>.
            /// </summary>
            virtual Actor^ __clrcall GetMountedBy() sealed
            {
                auto self = this;
                Actor^ result = nullptr;
                MemoryAllocation^ alloc = Memory::Allocate(0x10, 0, false);
                try
                {
                    Memory::WritePointer(alloc->Address, System::IntPtr::Zero, false);
                    if(MCH::b(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetMountedBy), self->Address, alloc->Address)))
                    {
                        result = MemoryObject::FromAddress<Actor^>(Memory::ReadPointer(alloc->Address, false));
                        if(result != nullptr) result->DecRef();
                    }
                }
                finally
                {
                    delete alloc;
                }
                return result;
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESObjectCELL"/>.
        /// </summary>
        private ref class impl_TESObjectCELL sealed : public VirtualObject, public TESObjectCELL
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
            
            /// <summary>
            /// Implementation of property <see cref="TESFullName.Text"/>.
            /// </summary>
            virtual property BSFixedString^ Text
            {
                BSFixedString^ __clrcall get() sealed
                {
                    auto self = this->As<TESFullName^>();
                    return MemoryObject::FromAddress<BSFixedString^>(self->Address + 0x8);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectCELL.ExtraDataList"/>.
            /// </summary>
            virtual property BSExtraDataList^ ExtraDataList
            {
                BSExtraDataList^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<BSExtraDataList^>(this->Address + 0x48);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectCELL.WorldSpace"/>.
            /// </summary>
            virtual property TESWorldSpace^ WorldSpace
            {
                TESWorldSpace^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESWorldSpace^>(Memory::ReadPointer(this->Address + 0x120, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectCELL.ReferenceLocker"/>.
            /// </summary>
            virtual property Mutex^ ReferenceLocker
            {
                Mutex^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<Mutex^>(this->Address + 0x118);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectCELL.References"/>.
            /// </summary>
            virtual property BSTDefaultScatterTable<System::UInt32, TESObjectREFR^>^ References
            {
                BSTDefaultScatterTable<System::UInt32, TESObjectREFR^>^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<BSTDefaultScatterTable<System::UInt32, TESObjectREFR^>^>(this->Address + 0x80);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectCELL.IsInterior"/>.
            /// </summary>
            virtual property bool IsInterior
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectCELL_IsInterior_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESObjectCELL.RayCast"/>.
            /// </summary>
            virtual System::Collections::Generic::List<RayCastResult^>^ RayCast(RayCastParameters^ p)
            {
                if(p == nullptr) throw gcnew System::ArgumentNullException("p");
                p->Cell = this;
                return _Havok::RayCast(p);
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectCELL.OwnerForm"/>.
            /// </summary>
            virtual property TESForm^ OwnerForm
            {
                TESForm^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<TESForm^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectCELL_OwnerForm_Get), self->Address));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectCELL.IsAttached"/>.
            /// </summary>
            virtual property bool IsAttached
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectCELL_IsAttached_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectCELL.CoordinateX"/>.
            /// </summary>
            virtual property System::Int32 CoordinateX
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this;
                    stack20 s;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectCELL_Coordinate_Get), self->Address, s.ptr(), s.ptr() + 0x10);
                    return s.get<int>(0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectCELL.CoordinateY"/>.
            /// </summary>
            virtual property System::Int32 CoordinateY
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this;
                    stack20 s;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectCELL_Coordinate_Get), self->Address, s.ptr(), s.ptr() + 0x10);
                    return s.get<int>(0x10);
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="Character"/>.
        /// </summary>
        private ref class impl_Character sealed : public VirtualObject, public Character
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="Actor.Race"/>.
            /// </summary>
            virtual property TESRace^ Race
            {
                TESRace^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESRace^>(Memory::ReadPointer(this->Address + 0x1F0, false));
                }
                void __clrcall set(TESRace^ value) sealed
                {
                    auto self = this;
                    MCH::e<TESRace^>(value, "value");
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_Race_Set), 0, 0, self->Address, value->Address);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.UpdateMovementControllerPosition"/>.
            /// </summary>
            virtual void __clrcall UpdateMovementControllerPosition(NiPoint3^ pos) sealed
            {
                auto self = this;
                if(pos == nullptr) throw gcnew System::ArgumentNullException("pos");
                auto controller = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_UpdateMovementControllerPosition), self->Address);
                if(controller != System::IntPtr::Zero)
                {
                    auto type = this->MovementState;
                    if(type != bhkCharacterStateTypes::Flying)
                    {
                        stack10 alloc;
                        alloc.set(0, pos->X * 0.0142875f);
                        alloc.set(4, pos->Y * 0.0142875f);
                        alloc.set(8, pos->Z * 0.0142875f);
                        auto vtable = Memory::ReadPointer(controller, false);
                        Memory::InvokeCdecl(vtable + 24, controller, alloc.ptr(), 1, 0);
                    }
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.AddPerk"/>.
            /// </summary>
            virtual void __clrcall AddPerk(BGSPerk^ perk) sealed
            {
                auto self = this;
                MCH::e<BGSPerk^>(perk, "perk");
                self->InvokeVTableThisCall(0, 0x7D8, perk->Address, 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.AddShout"/>.
            /// </summary>
            virtual void __clrcall AddShout(TESShout^ shout) sealed
            {
                auto self = this;
                MCH::e<TESShout^>(shout, "shout");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_AddShout), self->Address, shout->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.AddSpell"/>.
            /// </summary>
            virtual bool __clrcall AddSpell(SpellItem^ spell, bool showLearnedMessage) sealed
            {
                auto self = this;
                MCH::e<SpellItem^>(spell, "spell");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_AddSpell), 0, 0, self->Address, spell->Address, showLearnedMessage ? 1 : 0)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.AllowBleedoutDialogue"/>.
            /// </summary>
            virtual void __clrcall AllowBleedoutDialogue(bool allow) sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_AllowBleedoutDialogue), 0, 0, self->Address, allow ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.AllowPCDialogue"/>.
            /// </summary>
            virtual void __clrcall AllowPCDialogue(bool allow) sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_AllowPCDialogue), 0, 0, self->Address, allow ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.ClearArrested"/>.
            /// </summary>
            virtual void __clrcall ClearArrested() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ClearArrested), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.CanFlyHere"/>.
            /// </summary>
            virtual property bool CanFlyHere
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_CanFlyHere_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.ClearExpressionOverride"/>.
            /// </summary>
            virtual void __clrcall ClearExpressionOverride() sealed
            {
                auto self = this;
                auto ptr = self->InvokeVTableThisCall(0, 0x318);
                if(ptr == System::IntPtr::Zero) return;
                Memory::WriteUInt8(ptr + 542, 0, false);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.ClearExtraArrows"/>.
            /// </summary>
            virtual void __clrcall ClearExtraArrows() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ClearExtraArrows), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.ClearKeepOffsetFromActor"/>.
            /// </summary>
            virtual void __clrcall ClearKeepOffsetFromActor() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ClearKeepOffsetFromActor), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.ClearLookAtObject"/>.
            /// </summary>
            virtual void __clrcall ClearLookAtObject() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ClearLookAtObject), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.Dismount"/>.
            /// </summary>
            virtual bool __clrcall Dismount() sealed
            {
                auto self = this;
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_Dismount), 0, 0, self->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.DispelAllSpells"/>.
            /// </summary>
            virtual void __clrcall DispelAllSpells() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_DispelAllSpells), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.DispelSpell"/>.
            /// </summary>
            virtual bool __clrcall DispelSpell(SpellItem^ spell) sealed
            {
                auto self = this;
                MCH::e<SpellItem^>(spell, "spell");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_DispelSpell), 0, 0, self->Address, spell->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.DoCombatSpellApply"/>.
            /// </summary>
            virtual void __clrcall DoCombatSpellApply(SpellItem^ spell, TESObjectREFR^ target) sealed
            {
                auto self = this;
                MCH::e<SpellItem^>(spell, "spell");
                MCH::e<TESObjectREFR^>(target, "target");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_DoCombatSpellApply), 0, 0, self->Address, spell->Address, target->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.DrawWeapon"/>.
            /// </summary>
            virtual void __clrcall DrawWeapon() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_DrawWeapon), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.EnableAI"/>.
            /// </summary>
            virtual void __clrcall EnableAI(bool enable) sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_EnableAI), 0, 0, self->Address, enable ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.EndDeferredKill"/>.
            /// </summary>
            virtual void __clrcall EndDeferredKill() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_EndDeferredKill), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.EquipItem"/>.
            /// </summary>
            virtual void __clrcall EquipItem(TESForm^ form, bool preventUnequip, bool silent) sealed
            {
                auto self = this;
                MCH::e<TESForm^>(form, "form");
                auto has3d = MCH::u(form->InvokeVTableThisCall(0, 0x138));
                if((has3d & 0xFF) == 0) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_EquipItem), 0, 0, self->Address, form->Address, preventUnequip ? 1 : 0, silent ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.EquipShout"/>.
            /// </summary>
            virtual void __clrcall EquipShout(TESShout^ shout) sealed
            {
                auto self = this;
                MCH::e<TESShout^>(shout, "shout");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_EquipShout), 0, 0, self->Address, shout->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.EvaluatePackage"/>.
            /// </summary>
            virtual void __clrcall EvaluatePackage() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_EvaluatePackage), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetBribeAmount"/>.
            /// </summary>
            virtual System::Int32 __clrcall GetBribeAmount() sealed
            {
                auto self = this;
                return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetBribeAmount), 0, 0, self->Address)) & 0xFFFFFFFF);
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.CombatState"/>.
            /// </summary>
            virtual property ActorCombatStates CombatState
            {
                ActorCombatStates __clrcall get() sealed
                {
                    auto self = this;
                    return (ActorCombatStates)(System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_CombatState_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.CombatTarget"/>.
            /// </summary>
            virtual property Actor^ CombatTarget
            {
                Actor^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<Actor^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_CombatTarget_Get), 0, 0, self->Address));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.CrimeFaction"/>.
            /// </summary>
            virtual property TESFaction^ CrimeFaction
            {
                TESFaction^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<TESFaction^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_CrimeFaction_Get), 0, 0, self->Address));
                }
                void __clrcall set(TESFaction^ value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_CrimeFaction_Set), 0, 0, self->Address, value != nullptr ? value->Address : System::IntPtr::Zero);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.CurrentPackage"/>.
            /// </summary>
            virtual property TESPackage^ CurrentPackage
            {
                TESPackage^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<TESPackage^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_CurrentPackage_Get), 0, 0, self->Address));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.DialogueTarget"/>.
            /// </summary>
            virtual property Actor^ DialogueTarget
            {
                Actor^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<Actor^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_DialogueTarget_Get), 0, 0, self->Address));
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetEquippedArmorInSlot"/>.
            /// </summary>
            virtual TESObjectARMO^ __clrcall GetEquippedArmorInSlot(EquipSlots slot) sealed
            {
                auto self = this;
                auto ptr = Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_Inventory_Get), self->Address);
                if(ptr == System::IntPtr::Zero) return nullptr;
                return MemoryObject::FromAddressSafeCast<TESObjectARMO^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetEquippedArmorInSlot), ptr, (int)slot));
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetEquippedItemType"/>.
            /// </summary>
            virtual EquippedItemTypes __clrcall GetEquippedItemType(EquippedHandSlots slot) sealed
            {
                auto self = this;
                auto ptr = Memory::ReadPointer(self->Address + 0xF0, false);
                int rs = 0;
                if(ptr != System::IntPtr::Zero)
                {
                    System::IntPtr obj = System::IntPtr::Zero;
                    if(slot == EquippedHandSlots::LeftHand) obj = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetEquippedItemType_LeftHand), ptr);
                    else if(slot == EquippedHandSlots::RightHand) obj = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetEquippedItemType_RightHand), ptr);
                    if(obj != System::IntPtr::Zero)
                    {
                        auto typeId = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetEquippedItemType_ItemType), obj);
                        rs = (int)(typeId.ToInt64() & 0xFFFF);
                    }
                }
                return (EquippedItemTypes)rs;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetEquippedShield"/>.
            /// </summary>
            virtual TESObjectARMO^ __clrcall GetEquippedShield() sealed
            {
                auto self = this;
                return MemoryObject::FromAddress<TESObjectARMO^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetEquippedShield), 0, 0, self->Address));
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetEquippedShout"/>.
            /// </summary>
            virtual TESShout^ __clrcall GetEquippedShout() sealed
            {
                auto self = this;
                return MemoryObject::FromAddress<TESShout^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetEquippedShout), 0, 0, self->Address));
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetEquippedSpell"/>.
            /// </summary>
            virtual SpellItem^ __clrcall GetEquippedSpell(EquippedSpellSlots slot) sealed
            {
                auto self = this;
                System::UInt32 arg = (System::UInt32)slot;
                if(arg >= 4) return nullptr;
                return MemoryObject::FromAddress<SpellItem^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetEquippedSpell), 0, 0, self->Address, arg));
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetFactionRank"/>.
            /// </summary>
            virtual System::Int32 __clrcall GetFactionRank(TESFaction^ faction) sealed
            {
                auto self = this;
                MCH::e<TESFaction^>(faction, "faction");
                return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetFactionRank), 0, 0, self->Address, faction->Address)) & 0xFFFFFFFF);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetFactionReaction"/>.
            /// </summary>
            virtual FactionReactions __clrcall GetFactionReaction(Actor^ other) sealed
            {
                auto self = this;
                MCH::e<Actor^>(other, "other");
                return (FactionReactions)(System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetFactionReaction), 0, 0, self->Address, other->Address)) & 0xFFFFFFFF);
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.FlyingState"/>.
            /// </summary>
            virtual property FlyingStates FlyingState
            {
                FlyingStates __clrcall get() sealed
                {
                    auto self = this;
                    return (FlyingStates)(System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_FlyingState_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.ForcedLandingMarker"/>.
            /// </summary>
            virtual property TESObjectREFR^ ForcedLandingMarker
            {
                TESObjectREFR^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<TESObjectREFR^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ForcedLandingMarker_Get), 0, 0, self->Address));
                }
                void __clrcall set(TESObjectREFR^ value) sealed
                {
                    auto self = this;
                    MCH::e<TESObjectREFR^>(value, nullptr);
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ForcedLandingMarker_Set), 0, 0, self->Address, value != nullptr ? value->Address : System::IntPtr::Zero);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetGoldAmount"/>.
            /// </summary>
            virtual System::Int32 __clrcall GetGoldAmount() sealed
            {
                auto self = this;
                return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetGoldAmount), 0, 0, self->Address)) & 0xFFFFFFFF);
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.HighestRelationshipRank"/>.
            /// </summary>
            virtual property RelationshipRanks HighestRelationshipRank
            {
                RelationshipRanks __clrcall get() sealed
                {
                    auto self = this;
                    return (RelationshipRanks)(System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_HighestRelationshipRank_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.KilledBy"/>.
            /// </summary>
            virtual property Actor^ KilledBy
            {
                Actor^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<Actor^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_KilledBy_Get), 0, 0, self->Address));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.Level"/>.
            /// </summary>
            virtual property System::Int32 Level
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this;
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_Level_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.BaseActor"/>.
            /// </summary>
            virtual property TESNPC^ BaseActor
            {
                TESNPC^ __clrcall get() sealed
                {
                    auto self = this;
                    auto npc = MemoryObject::FromAddress<TESNPC^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_BaseActor_Get), 0, 0, self->Address));
                    if(npc == nullptr)
                    {
                    auto obj = self->BaseForm;
                    if(obj != nullptr)
                    npc = obj->As<TESNPC^>();
                    }
                    return npc;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.LightLevel"/>.
            /// </summary>
            virtual property System::Single LightLevel
            {
                System::Single __clrcall get() sealed
                {
                    auto self = this;
                    return (float)Memory::InvokeCdeclF(MCH::FromBase(GameAddress::Actor_LightLevel_Get), 0, 0, self->Address);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.LowestRelationshipRank"/>.
            /// </summary>
            virtual property RelationshipRanks LowestRelationshipRank
            {
                RelationshipRanks __clrcall get() sealed
                {
                    auto self = this;
                    return (RelationshipRanks)(System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_LowestRelationshipRank_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.NoBleedoutRecovery"/>.
            /// </summary>
            virtual property bool NoBleedoutRecovery
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_NoBleedoutRecovery_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_NoBleedoutRecovery_Set), 0, 0, self->Address, value ? 1 : 0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.ReceivesPlayerControls"/>.
            /// </summary>
            virtual property bool ReceivesPlayerControls
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ReceivesPlayerControls_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ReceivesPlayerControls_Set), 0, 0, self->Address, value ? 1 : 0);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetRelationshipRank"/>.
            /// </summary>
            virtual RelationshipRanks __clrcall GetRelationshipRank(Actor^ other) sealed
            {
                auto self = this;
                MCH::e<Actor^>(other, "other");
                return (RelationshipRanks)(System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetRelationshipRank), 0, 0, self->Address, other->Address)) & 0xFFFFFFFF);
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.SitState"/>.
            /// </summary>
            virtual property ActorActionStates SitState
            {
                ActorActionStates __clrcall get() sealed
                {
                    auto self = this;
                    return (ActorActionStates)(System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SitState_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.SleepState"/>.
            /// </summary>
            virtual property ActorActionStates SleepState
            {
                ActorActionStates __clrcall get() sealed
                {
                    auto self = this;
                    return (ActorActionStates)(System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SleepState_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.VoiceRecoveryTime"/>.
            /// </summary>
            virtual property System::Single VoiceRecoveryTime
            {
                System::Single __clrcall get() sealed
                {
                    auto self = this;
                    return (float)Memory::InvokeCdeclF(MCH::FromBase(GameAddress::Actor_VoiceRecoveryTime_Get), 0, 0, self->Address);
                }
                void __clrcall set(System::Single value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_VoiceRecoveryTime_Set), 0, 0, self->Address, value);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.WarmthRating"/>.
            /// </summary>
            virtual property System::Single WarmthRating
            {
                System::Single __clrcall get() sealed
                {
                    auto self = this;
                    return (float)Memory::InvokeCdeclF(MCH::FromBase(GameAddress::Actor_WarmthRating_Get), 0, 0, self->Address);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.HasAssociation"/>.
            /// </summary>
            virtual bool __clrcall HasAssociation(BGSAssociationType^ type, Actor^ other) sealed
            {
                auto self = this;
                MCH::e<BGSAssociationType^>(type, "type");
                MCH::e<Actor^>(other, nullptr);
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_HasAssociation), 0, 0, self->Address, type->Address, other != nullptr ? other->Address : System::IntPtr::Zero)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.HasFamilyRelationship"/>.
            /// </summary>
            virtual bool __clrcall HasFamilyRelationship(Actor^ other) sealed
            {
                auto self = this;
                MCH::e<Actor^>(other, nullptr);
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_HasFamilyRelationship), 0, 0, self->Address, other != nullptr ? other->Address : System::IntPtr::Zero)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.HasLOS_Papyrus"/>.
            /// </summary>
            virtual bool __clrcall HasLOS_Papyrus(TESObjectREFR^ other) sealed
            {
                auto self = this;
                MCH::e<TESObjectREFR^>(other, "other");
                if(other->FormType != FormTypes::Character && !self->Equals(PlayerCharacter::Instance)) return false;
                stack10 s;
                auto ptrResult = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_HasLOS_Papyrus), self->Address, other->Address, s.ptr());
                auto result = MCH::u(ptrResult);
                return (result & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.HasParentRelationship"/>.
            /// </summary>
            virtual bool __clrcall HasParentRelationship(Actor^ other) sealed
            {
                auto self = this;
                MCH::e<Actor^>(other, "other");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_HasParentRelationship), 0, 0, self->Address, other->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsAlarmed"/>.
            /// </summary>
            virtual property bool IsAlarmed
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsAlarmed_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsAllowedToFly"/>.
            /// </summary>
            virtual property bool IsAllowedToFly
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsAllowedToFly_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsAllowedToFly_Set), 0, 0, self->Address, value ? 1 : 0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsArrested"/>.
            /// </summary>
            virtual property bool IsArrested
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsArrested_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsBleedingOut"/>.
            /// </summary>
            virtual property bool IsBleedingOut
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsBleedingOut_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsDead"/>.
            /// </summary>
            virtual property bool IsDead
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsDead_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.CanDetect"/>.
            /// </summary>
            virtual bool __clrcall CanDetect(Actor^ target) sealed
            {
                auto self = this;
                MCH::e<Actor^>(target, "target");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_CanDetect), 0, 0, target->Address, self->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.IsEquipped"/>.
            /// </summary>
            virtual bool __clrcall IsEquipped(TESForm^ form) sealed
            {
                auto self = this;
                MCH::e<TESForm^>(form, "form");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsEquipped), 0, 0, self->Address, form->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsPlayersLastRiddenHorse"/>.
            /// </summary>
            virtual property bool IsPlayersLastRiddenHorse
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsPlayersLastRiddenHorse_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsArrestingTarget"/>.
            /// </summary>
            virtual property bool IsArrestingTarget
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsArrestingTarget_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsAlerted"/>.
            /// </summary>
            virtual property bool IsAlerted
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsAlerted_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsAlerted_Set), 0, 0, self->Address, value ? 1 : 0);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.HasPerk"/>.
            /// </summary>
            virtual bool __clrcall HasPerk(BGSPerk^ perk) sealed
            {
                auto self = this;
                MCH::e<BGSPerk^>(perk, "perk");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_HasPerk), 0, 0, self->Address, perk->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.HasSpell"/>.
            /// </summary>
            virtual bool __clrcall HasSpell(TESForm^ spellOrShout) sealed
            {
                auto self = this;
                if(spellOrShout == nullptr) throw gcnew System::ArgumentNullException("spellOrShout");
                auto formType = spellOrShout->FormType;
                if(formType == FormTypes::Spell)
                {
                    auto arg = spellOrShout->As<SpellItem^>();
                    if(arg != nullptr) return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_HasSpell_Spell), self->Address, arg->Address)) & 0xFF) != 0;
                }
                else if(formType == FormTypes::Shout)
                {
                    auto arg = spellOrShout->As<TESShout^>();
                    if(arg != nullptr) return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_HasSpell_Shout), self->Address, arg->Address)) & 0xFF) != 0;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsBribed"/>.
            /// </summary>
            virtual property bool IsBribed
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsBribed_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsBribed_Set), 0, 0, self->Address, value ? 1 : 0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsChild"/>.
            /// </summary>
            virtual property bool IsChild
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsChild_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsCommandedActor"/>.
            /// </summary>
            virtual property bool IsCommandedActor
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsCommandedActor_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsDoingFavor"/>.
            /// </summary>
            virtual property bool IsDoingFavor
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsDoingFavor_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsDoingFavor_Set), 0, 0, self->Address, value ? 1 : 0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsEssential"/>.
            /// </summary>
            virtual property bool IsEssential
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsEssential_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsFlying"/>.
            /// </summary>
            virtual property bool IsFlying
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsFlying_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsGhost"/>.
            /// </summary>
            virtual property bool IsGhost
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsGhost_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsGhost_Set), 0, 0, self->Address, value ? 1 : 0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsGuard"/>.
            /// </summary>
            virtual property bool IsGuard
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsGuard_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.IsHostileToActor"/>.
            /// </summary>
            virtual bool __clrcall IsHostileToActor(Actor^ target) sealed
            {
                auto self = this;
                MCH::e<Actor^>(target, "target");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsHostileToActor), 0, 0, self->Address, target->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsInCombat"/>.
            /// </summary>
            virtual property bool IsInCombat
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsInCombat_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.IsInFaction"/>.
            /// </summary>
            virtual bool __clrcall IsInFaction(TESFaction^ faction) sealed
            {
                auto self = this;
                MCH::e<TESFaction^>(faction, "faction");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsInFaction), 0, 0, self->Address, faction->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsInKillmove"/>.
            /// </summary>
            virtual property bool IsInKillmove
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsInKillmove_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsIntimidated"/>.
            /// </summary>
            virtual property bool IsIntimidated
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsIntimidated_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsIntimidated_Set), 0, 0, self->Address, value ? 1 : 0 );
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsOnMount"/>.
            /// </summary>
            virtual property bool IsOnMount
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsOnMount_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsOverEncumbered"/>.
            /// </summary>
            virtual property bool IsOverEncumbered
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsOverEncumbered_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsPlayerTeammate"/>.
            /// </summary>
            virtual property bool IsPlayerTeammate
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsPlayerTeammate_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsRunning"/>.
            /// </summary>
            virtual property bool IsRunning
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsRunning_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsSneaking"/>.
            /// </summary>
            virtual property bool IsSneaking
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsSneaking_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    if(this->IsSneaking == value) return;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsSneaking_Set), 0, 0, self->Address); // This is a toggle
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsSprinting"/>.
            /// </summary>
            virtual property bool IsSprinting
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsSprinting_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsTrespassing"/>.
            /// </summary>
            virtual property bool IsTrespassing
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsTrespassing_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsUnconscious"/>.
            /// </summary>
            virtual property bool IsUnconscious
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsUnconscious_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsUnconscious_Set), 0, 0, self->Address, value ? 1 : 0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsWeaponDrawn"/>.
            /// </summary>
            virtual property bool IsWeaponDrawn
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsWeaponDrawn_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.Kill"/>.
            /// </summary>
            virtual void __clrcall Kill(Actor^ killer, bool noEvents, bool force) sealed
            {
                auto self = this;
                MCH::e<Actor^>(killer, nullptr);
                if(!force)
                {
                    auto mt = this->As<MagicTarget^>();
                    if(mt == nullptr) return;
                    auto res1 = MCH::u(mt->InvokeVTableThisCall(0, 0x20));
                    auto res2 = MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_Kill_1), self->Address));
                    bool ok = (res1 & 0xFF) == 0 || (res2 & 0xFF) != 0;
                    if(!ok) return;
                }
                if((Memory::ReadUInt32(self->Address + 0xC0, false) & 0x1E00000) == 0xE00000)
                {
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_Kill_2), self->Address, 0, noEvents ? 0 : 1);
                }
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_Kill_3), self->Address, killer != nullptr ? killer->Address : System::IntPtr::Zero, (double)0.0, noEvents ? 0 : 1, 0);
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsPlayer"/>.
            /// </summary>
            virtual property bool IsPlayer
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    auto plr = PlayerCharacter::Instance;
                    if(plr == nullptr) return false;
                    return self->Address == plr->Address;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.RemoveFromFaction"/>.
            /// </summary>
            virtual void __clrcall RemoveFromFaction(TESFaction^ faction) sealed
            {
                auto self = this;
                MCH::e<TESFaction^>(faction, "faction");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_RemoveFromFaction), 0, 0, self->Address, faction->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.RemoveFromAllFactions"/>.
            /// </summary>
            virtual void __clrcall RemoveFromAllFactions() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_RemoveFromAllFactions), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.RemovePerk"/>.
            /// </summary>
            virtual void __clrcall RemovePerk(BGSPerk^ perk) sealed
            {
                auto self = this;
                MCH::e<BGSPerk^>(perk, "perk");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_RemovePerk), 0, 0, self->Address, perk->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.RemoveShout"/>.
            /// </summary>
            virtual bool __clrcall RemoveShout(TESShout^ shout) sealed
            {
                auto self = this;
                MCH::e<TESShout^>(shout, "shout");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_RemoveShout), 0, 0, self->Address, shout->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.RemoveSpell"/>.
            /// </summary>
            virtual bool __clrcall RemoveSpell(SpellItem^ spell) sealed
            {
                auto self = this;
                MCH::e<SpellItem^>(spell, "spell");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_RemoveSpell), 0, 0, self->Address, spell->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.ResetHealthAndLimbs"/>.
            /// </summary>
            virtual void __clrcall ResetHealthAndLimbs() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ResetHealthAndLimbs), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.Resurrect"/>.
            /// </summary>
            virtual void __clrcall Resurrect() sealed
            {
                auto self = this;
                System::IntPtr arg = System::IntPtr::Zero;
                if(self->InvokeVTableThisCall(0, 0x380) != System::IntPtr::Zero) arg = System::IntPtr(1);
                self->InvokeVTableThisCall(0, 0x558, 1, arg);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SendAssaultAlarm"/>.
            /// </summary>
            virtual void __clrcall SendAssaultAlarm(Actor^ assaulter) sealed
            {
                auto self = this;
                MCH::e<Actor^>(assaulter, "assaulter");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SendAssaultAlarm_1), self->Address, assaulter->Address);
                System::UInt32 flags = Memory::ReadUInt32(self->Address + 0xE0, false);
                if(((flags >> 30) & 1) != 0) return;
                auto process = Memory::ReadPointer(self->Address + 0xF0, false);
                if(process == System::IntPtr::Zero) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SendAssaultAlarm_2), process, self->Address, assaulter->Address, 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SendTrespassAlarm"/>.
            /// </summary>
            virtual void __clrcall SendTrespassAlarm(Actor^ criminal) sealed
            {
                auto self = this;
                MCH::e<Actor^>(criminal, "criminal");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SendTrespassAlarm), 0, 0, self->Address, criminal->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetAllowFlyingEx"/>.
            /// </summary>
            virtual void __clrcall SetAllowFlyingEx(bool allowFly, bool allowCrash, bool allowSearch) sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetAllowFlyingEx), 0, 0, self->Address, allowFly ? 1 : 0, allowCrash ? 1 : 0, allowSearch ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetAlpha"/>.
            /// </summary>
            virtual void __clrcall SetAlpha(System::Single alpha, bool fade) sealed
            {
                auto self = this;
                auto process = Memory::ReadPointer(self->Address + 0xF0, false);
                if(process == System::IntPtr::Zero) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetAlpha), 0, 0, self->Address, alpha, fade ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetAttackedByAllOnSight"/>.
            /// </summary>
            virtual void __clrcall SetAttackedByAllOnSight(bool should) sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetAttackedByAllOnSight), 0, 0, self->Address, should ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetCriticalStage"/>.
            /// </summary>
            virtual void __clrcall SetCriticalStage(ActorCriticalStages stage) sealed
            {
                auto self = this;
                int _s = (int)stage;
                if(_s < 0 || _s >= 5) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetCriticalStage), self->Address, (int)stage);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetDontMove"/>.
            /// </summary>
            virtual void __clrcall SetDontMove(bool dontMove) sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetDontMove), 0, 0, self->Address, dontMove ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetExpressionOverride"/>.
            /// </summary>
            virtual bool __clrcall SetExpressionOverride(System::Int32 expression, System::Single amount) sealed
            {
                auto self = this;
                if(expression <= 0 || expression > 16) return false;
                amount = System::Math::Min(1.0f, System::Math::Max(0.0f, amount));
                auto faceAnim = self->InvokeVTableThisCall(0, 0x318);
                if(faceAnim == System::IntPtr::Zero) return false;
                Memory::WriteUInt8(faceAnim + 0x21E, 0, false);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetExpressionOverride), faceAnim, expression, amount);
                Memory::WriteUInt8(faceAnim + 0x21E, 1, false);
                return true;
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsHeadTrackingEnabled"/>.
            /// </summary>
            virtual property bool IsHeadTrackingEnabled
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    System::UInt32 flags = Memory::ReadUInt32(self->Address + 0xC4, false);
                    return (flags & 8) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    System::UInt32 flags = Memory::ReadUInt32(self->Address + 0xC4, false);
                    if(value) flags |= 8;
                    else flags &= ~8;
                    Memory::WriteUInt32(self->Address + 0xC4, flags, false);
                    if(this->IsPlayer) this->SetAnimationVariableBool("IsNPC", value);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetLookAtObject"/>.
            /// </summary>
            virtual void __clrcall SetLookAtObject(TESObjectREFR^ target, bool whilePathing) sealed
            {
                auto self = this;
                MCH::e<TESObjectREFR^>(target, nullptr);
                if(target == nullptr)
                {
                    this->ClearLookAtObject();
                    return;
                }
                auto process = Memory::ReadPointer(self->Address + 0xF0, false);
                if(process == System::IntPtr::Zero) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetLookAtObject), 0, 0, self->Address, target->Address, whilePathing ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.ShowOnStealthMeter"/>.
            /// </summary>
            virtual property bool ShowOnStealthMeter
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    System::UInt32 flags = Memory::ReadUInt32(self->Address + 0x1FC, false);
                    bool notShowFlag = (flags & 0x4000000) != 0;
                    return !notShowFlag;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ShowOnStealthMeter_Set), 0, 0, self->Address, !value ? 1 : 0);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetOutfit"/>.
            /// </summary>
            virtual void __clrcall SetOutfit(BGSOutfit^ outfit, bool sleepOutfit) sealed
            {
                auto self = this;
                MCH::e<BGSOutfit^>(outfit, "outfit");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetOutfit), 0, 0, self->Address, outfit->Address, sleepOutfit ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetPlayerResistingArrest"/>.
            /// </summary>
            virtual void __clrcall SetPlayerResistingArrest() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetPlayerResistingArrest), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetPlayerTeammate"/>.
            /// </summary>
            virtual void __clrcall SetPlayerTeammate(bool teammate, bool canDoFavors) sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetPlayerTeammate), 0, 0, self->Address, teammate ? 1 : 0, canDoFavors ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetRelationshipRank"/>.
            /// </summary>
            virtual void __clrcall SetRelationshipRank(Actor^ other, RelationshipRanks rank) sealed
            {
                auto self = this;
                MCH::e<Actor^>(other, "other");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetRelationshipRank), 0, 0, self->Address, other->Address, (int)rank);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetRestrained"/>.
            /// </summary>
            virtual void __clrcall SetRestrained(bool restrained) sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetRestrained), 0, 0, self->Address, restrained ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetVehicle"/>.
            /// </summary>
            virtual void __clrcall SetVehicle(TESObjectREFR^ vehicle) sealed
            {
                auto self = this;
                MCH::e<TESObjectREFR^>(vehicle, nullptr);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetVehicle), 0, 0, self->Address, vehicle != nullptr ? vehicle->Address : System::IntPtr::Zero);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.ShowBarterMenu"/>.
            /// </summary>
            virtual void __clrcall ShowBarterMenu() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ShowBarterMenu), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.StartCombat"/>.
            /// </summary>
            virtual bool __clrcall StartCombat(Actor^ target) sealed
            {
                auto self = this;
                MCH::e<Actor^>(target, "target");
                if(self->IsPlayer) return false;
                if(Memory::ReadPointer(self->Address + 0xF0, false) == System::IntPtr::Zero) return false;
                if(Memory::ReadPointer(target->Address + 0xF0, false) == System::IntPtr::Zero) return false;
                if((MCH::u(self->InvokeVTableThisCall(0, 0x4C8, 0)) & 0xFF) != 0) return false;
                if((MCH::u(target->InvokeVTableThisCall(0, 0x4C8, 0)) & 0xFF) != 0) return false;
                if(!target->IsPlayer)
                {
                    auto p = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_StartCombat_1), self->Address);
                    if((MCH::u(p) & 0xFF) != 0) return false;
                }
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_StartCombat_2), Memory::ReadPointer(MCH::FromBase(GameAddress::Actor_StartCombat_3), false), self->Address, target->Address);
                return true;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.StartDeferredKill"/>.
            /// </summary>
            virtual void __clrcall StartDeferredKill() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_StartDeferredKill), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.StopCombatAlarm"/>.
            /// </summary>
            virtual void __clrcall StopCombatAlarm() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_StopCombatAlarm), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.StopCombat"/>.
            /// </summary>
            virtual void __clrcall StopCombat() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_StopCombat), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.TrapSoul"/>.
            /// </summary>
            virtual bool __clrcall TrapSoul(Actor^ target) sealed
            {
                auto self = this;
                MCH::e<Actor^>(target, "target");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_TrapSoul), 0, 0, self->Address, target->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.UnlockOwnedDoorsInCell"/>.
            /// </summary>
            virtual void __clrcall UnlockOwnedDoorsInCell() sealed
            {
                auto self = this;
                auto cell = this->ParentCell;
                if(cell == nullptr || !cell->IsInterior) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_UnlockOwnedDoorsInCell), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.UnequipAll"/>.
            /// </summary>
            virtual void __clrcall UnequipAll() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_UnequipAll), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.UnequipItemSlot"/>.
            /// </summary>
            virtual void __clrcall UnequipItemSlot(EquipSlots slot) sealed
            {
                auto self = this;
                auto data = Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_Inventory_Get), self->Address);
                if(data == System::IntPtr::Zero) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_UnequipItemSlot), data, (int)slot, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.UnequipItem"/>.
            /// </summary>
            virtual void __clrcall UnequipItem(TESForm^ form, bool preventEquip, bool silent) sealed
            {
                auto self = this;
                MCH::e<TESForm^>(form, "form");
                if(!form->Has3D) return;
                auto cont = Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_Inventory_Get), self->Address);
                if(cont == System::IntPtr::Zero) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_UnequipItem), 0, 0, self->Address, form->Address, preventEquip ? 1 : 0, silent ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.UnequipShout"/>.
            /// </summary>
            virtual void __clrcall UnequipShout(TESShout^ shout) sealed
            {
                auto self = this;
                MCH::e<TESShout^>(shout, "shout");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_UnequipShout), 0, 0, self->Address, shout->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.UnequipSpell"/>.
            /// </summary>
            virtual void __clrcall UnequipSpell(SpellItem^ spell, EquippedSpellSlots slot) sealed
            {
                auto self = this;
                MCH::e<SpellItem^>(spell, "spell");
                int _s = (int)slot;
                if(_s < 0 || _s >= 3) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_UnequipSpell), 0, 0, self->Address, spell->Address, (int)slot);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.EquipSpell"/>.
            /// </summary>
            virtual void __clrcall EquipSpell(SpellItem^ spell, EquippedSpellSlots slot) sealed
            {
                auto self = this;
                MCH::e<SpellItem^>(spell, "spell");
                int _s = (int)slot;
                if(_s < 0 || _s >= 3) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_EquipSpell), 0, 0, self->Address, spell->Address, (int)slot);
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.WillIntimidateSucceed"/>.
            /// </summary>
            virtual property bool WillIntimidateSucceed
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_WillIntimidateSucceed_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.WornHasKeyword"/>.
            /// </summary>
            virtual bool __clrcall WornHasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this;
                MCH::e<BGSKeyword^>(keyword, "keyword");
                auto cont = Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_Inventory_Get), self->Address);
                if(cont == System::IntPtr::Zero) return false;
                auto result = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_WornHasKeyword), cont, keyword->Address);
                return (MCH::u(result) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.WornHasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall WornHasKeywordText(System::String^ keyword) sealed
            {
                auto self = this;
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto cont = Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_Inventory_Get), self->Address);
                if(cont == System::IntPtr::Zero) return false;
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    auto result = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_WornHasKeyword), cont, kw->Address);
                    if((MCH::u(result) & 0xFF) != 0) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.ClearLookAtPosition"/>.
            /// </summary>
            virtual void __clrcall ClearLookAtPosition() sealed
            {
                auto self = this;
                auto process = Memory::ReadPointer(self->Address + 0xF0, false);
                if(process == System::IntPtr::Zero) return;
                auto race = this->Race;
                if(race == nullptr || !race->CanHeadTrack) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ClearLookAtPosition), process, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetLookAtPosition"/>.
            /// </summary>
            virtual void __clrcall SetLookAtPosition(NiPoint3^ position) sealed
            {
                auto self = this;
                if(position == nullptr)
                {
                    this->ClearLookAtPosition();
                    return;
                }
                auto process = Memory::ReadPointer(self->Address + 0xF0, false);
                if(process == System::IntPtr::Zero) return;
                auto race = this->Race;
                if(race == nullptr || !race->CanHeadTrack) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetLookAtPosition), process, self->Address, position->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.InterruptCast"/>.
            /// </summary>
            virtual void __clrcall InterruptCast() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_InterruptCast), self->Address, 0);
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsBeingRidden"/>.
            /// </summary>
            virtual property bool IsBeingRidden
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return MCH::b(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsBeingRidden_Get), self->Address));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsOnFlyingMount"/>.
            /// </summary>
            virtual property bool IsOnFlyingMount
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return MCH::b(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsOnFlyingMount_Get), self->Address));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.MovementState"/>.
            /// </summary>
            virtual property bhkCharacterStateTypes MovementState
            {
                bhkCharacterStateTypes __clrcall get() sealed
                {
                    auto self = this;
                    auto ptr = Memory::ReadPointer(self->Address + 0xF0, false);
                    if(ptr != System::IntPtr::Zero)
                    {
                    ptr = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_UpdateMovementControllerPosition), ptr);
                    if(ptr != System::IntPtr::Zero)
                    {
                    ptr = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_MovementState_Get), ptr + 480);
                    return (bhkCharacterStateTypes)((int)(MCH::u(ptr) & 0xFF));
                    }
                    }
                    return bhkCharacterStateTypes::Unknown;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsJumping"/>.
            /// </summary>
            virtual property bool IsJumping
            {
                bool __clrcall get() sealed
                {
                    return this->MovementState == bhkCharacterStateTypes::Jumping;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsFalling"/>.
            /// </summary>
            virtual property bool IsFalling
            {
                bool __clrcall get() sealed
                {
                    return this->MovementState == bhkCharacterStateTypes::InAir;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetMount"/>.
            /// </summary>
            virtual Actor^ __clrcall GetMount() sealed
            {
                auto self = this;
                Actor^ result = nullptr;
                MemoryAllocation^ alloc = Memory::Allocate(0x10, 0, false);
                try
                {
                    Memory::WritePointer(alloc->Address, System::IntPtr::Zero, false);
                    if(MCH::b(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetMount), self->Address, alloc->Address)))
                    {
                        result = MemoryObject::FromAddress<Actor^>(Memory::ReadPointer(alloc->Address, false));
                        if(result != nullptr) result->DecRef();
                    }
                }
                finally
                {
                    delete alloc;
                }
                return result;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetMountedBy"/>.
            /// </summary>
            virtual Actor^ __clrcall GetMountedBy() sealed
            {
                auto self = this;
                Actor^ result = nullptr;
                MemoryAllocation^ alloc = Memory::Allocate(0x10, 0, false);
                try
                {
                    Memory::WritePointer(alloc->Address, System::IntPtr::Zero, false);
                    if(MCH::b(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetMountedBy), self->Address, alloc->Address)))
                    {
                        result = MemoryObject::FromAddress<Actor^>(Memory::ReadPointer(alloc->Address, false));
                        if(result != nullptr) result->DecRef();
                    }
                }
                finally
                {
                    delete alloc;
                }
                return result;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.BaseForm"/>.
            /// </summary>
            virtual property TESForm^ BaseForm
            {
                TESForm^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESForm^>(Memory::ReadPointer(this->Address + 0x40, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.ParentCell"/>.
            /// </summary>
            virtual property TESObjectCELL^ ParentCell
            {
                TESObjectCELL^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESObjectCELL^>(Memory::ReadPointer(this->Address + 0x60, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.ExtraDataList"/>.
            /// </summary>
            virtual property BSExtraDataList^ ExtraDataList
            {
                BSExtraDataList^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<BSExtraDataList^>(this->Address + 0x70);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.Position"/>.
            /// </summary>
            virtual property NiPoint3^ Position
            {
                NiPoint3^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPoint3^>(this->Address + 0x54);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.Rotation"/>.
            /// </summary>
            virtual property NiPoint3^ Rotation
            {
                NiPoint3^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPoint3^>(this->Address + 0x48);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.Node"/>.
            /// </summary>
            virtual property NiNode^ Node
            {
                NiNode^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<NiNode^>(self->InvokeVTableThisCall(0, 0x380, 0));
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESObjectREFR.Activate"/>.
            /// </summary>
            virtual bool __clrcall Activate(TESObjectREFR^ activator, bool skipEvents) sealed
            {
                auto self = this;
                MCH::e<TESObjectREFR^>(activator, "activator");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_Activate), self->Address, activator->Address, 0, 0, 1, skipEvents ? 1 : 0)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.CurrentLocation"/>.
            /// </summary>
            virtual property BGSLocation^ CurrentLocation
            {
                BGSLocation^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<BGSLocation^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_CurrentLocation_Get), self->Address));
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESObjectREFR.OpenInventory"/>.
            /// </summary>
            virtual void __clrcall OpenInventory(ContainerOpenTypes type) sealed
            {
                auto self = this;
                if(!self->HasInventory) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_OpenInventory), self->Address, (int)type);
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.HasInventory"/>.
            /// </summary>
            virtual property bool HasInventory
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    if(self->FormType == FormTypes::Character) return true;
                    if(this->Is<TESObjectCONT^>()) return true;
                    return false;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.Inventory"/>.
            /// </summary>
            virtual property ExtraContainerChanges::Data^ Inventory
            {
                ExtraContainerChanges::Data^ __clrcall get() sealed
                {
                    auto self = this;
                    auto ptr = Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_Inventory_Get), self->Address);
                    return MemoryObject::FromAddress<ExtraContainerChanges::Data^>(ptr);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESObjectREFR.SetAnimationVariableBool"/>.
            /// </summary>
            virtual bool __clrcall SetAnimationVariableBool(System::String^ name, bool value) sealed
            {
                if(name == nullptr) return false;
                auto graph = this->As<IAnimationGraphManagerHolder^>();
                if(graph == nullptr) return false;
                StringRefHolder^ str = gcnew StringRefHolder(name);
                try
                {
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_SetAnimationVariableBool), graph->Address, str->AddressOf, value ? 1 : 0)) & 0xFF) == 0;
                }
                finally
                {
                    delete str;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESObjectREFR.GetMagicCaster"/>.
            /// </summary>
            virtual MagicCaster^ __clrcall GetMagicCaster(EquippedSpellSlots slot) sealed
            {
                auto self = this;
                int sl = (int)slot;
                if(sl < 0 || sl > 2) return nullptr;
                auto ptr = self->InvokeVTableThisCall(0, 0x2E0, sl);
                return MemoryObject::FromAddress<MagicCaster^>(ptr);
            }
            
            
            /// <summary>
            /// Implementation of method <see cref="TESObjectREFR.GetExtraData"/>.
            /// </summary>
            virtual BSExtraData^ __clrcall GetExtraData(ExtraDataTypes type) sealed
            {
                auto self = this;
                auto ptr = Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_GetExtraData), self->Address, (int)type);
                return MemoryObject::FromAddress<BSExtraData^>(ptr);
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESObjectREFR.GetSkeletonNode"/>.
            /// </summary>
            virtual NiNode^ __clrcall GetSkeletonNode(bool firstPerson) sealed
            {
                auto self = this;
                auto ptr = self->InvokeVTableThisCall(0, 0x378, firstPerson ? 1 : 0);
                return MemoryObject::FromAddress<NiNode^>(ptr);
            }
            
            /// <summary>
            /// Implementation of property <see cref="MagicTarget.ActiveEffects"/>.
            /// </summary>
            virtual property ListNode<ActiveEffect^>^ ActiveEffects
            {
                ListNode<ActiveEffect^>^ __clrcall get() sealed
                {
                    auto self = this->As<MagicTarget^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x38);
                    return MemoryObject::FromAddress<ListNode<ActiveEffect^>^>(ptr);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="MagicTarget.HasMagicEffectWithKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasMagicEffectWithKeyword(BGSKeyword^ keyword, MagicItem^% item) sealed
            {
                auto self = this->As<MagicTarget^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                stack10 s;
                System::UInt64 p = MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::MagicTarget_HasMagicEffectWithKeyword), self->Address, keyword->Address, s.ptr()));
                if((p & 0xFF) == 0) return false;
                System::IntPtr itemPtr = System::IntPtr(s.get<void*>(0));
                if(itemPtr != System::IntPtr::Zero) item = MemoryObject::FromAddress<MagicItem^>(itemPtr);
                return true;
            }
            
            /// <summary>
            /// Implementation of method <see cref="MagicTarget.HasMagicEffectWithKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasMagicEffectWithKeywordText(System::String^ keyword, MagicItem^% item) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasMagicEffectWithKeyword(kw, item)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of method <see cref="MagicTarget.HasMagicEffect"/>.
            /// </summary>
            virtual bool __clrcall HasMagicEffect(EffectSetting^ effect) sealed
            {
                auto self = this->As<MagicTarget^>();
                MCH::e<EffectSetting^>(effect, "effect");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::MagicTarget_HasMagicEffect), self->Address, effect->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="MagicTarget.DispelEffectsWithArchetype"/>.
            /// </summary>
            virtual void __clrcall DispelEffectsWithArchetype(Archetypes archetype, TESObjectREFR^ onlyFromCaster) sealed
            {
                auto self = this->As<MagicTarget^>();
                MCH::e<TESObjectREFR^>(onlyFromCaster, nullptr);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::MagicTarget_DispelEffectsWithArchetype), self->Address, (int)archetype, onlyFromCaster != nullptr ? onlyFromCaster->Address : System::IntPtr::Zero);
            }
            
            /// <summary>
            /// Implementation of property <see cref="MagicTarget.HasMagicEffectThatCausesDamage"/>.
            /// </summary>
            virtual property bool HasMagicEffectThatCausesDamage
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<MagicTarget^>();
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::MagicTarget_HasMagicEffectThatCausesDamage_Get), self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="MagicTarget.FindFirstEffectWithArchetype"/>.
            /// </summary>
            virtual ActiveEffect^ __clrcall FindFirstEffectWithArchetype(Archetypes archetype, bool allowInactive) sealed
            {
                auto self = this->As<MagicTarget^>();
                auto ptr = Memory::InvokeCdecl(MCH::FromBase(GameAddress::MagicTarget_FindFirstEffectWithArchetype), self->Address, (int)archetype, allowInactive ? 1 : 0);
                return MemoryObject::FromAddress<ActiveEffect^>(ptr);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.GetActorValue"/>.
            /// </summary>
            virtual System::Single __clrcall GetActorValue(ActorValueIndices id) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                return (float)self->InvokeVTableThisCallF(0, 0x8, (int)id);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.GetActorValueMax"/>.
            /// </summary>
            virtual System::Single __clrcall GetActorValueMax(ActorValueIndices id) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                return (float)self->InvokeVTableThisCallF(0, 0x10, (int)id);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.GetBaseActorValue"/>.
            /// </summary>
            virtual System::Single __clrcall GetBaseActorValue(ActorValueIndices id) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                return (float)self->InvokeVTableThisCallF(0, 0x18, (int)id);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.DamageActorValue"/>.
            /// </summary>
            virtual void __clrcall DamageActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                if(id == ActorValueIndices::Health)
                {
                    auto actor = this->As<Actor^>();
                    if(actor != nullptr)
                    {
                        auto resultPtr = actor->InvokeVTableThisCall(0, 0x2F0);
                        if((MCH::u(resultPtr) & 0xFF) != 0)
                        {
                            actor->InvokeVTableThisCall(0, 0x820, 0, amount);
                            return;
                        }
                    }
                }
                self->InvokeVTableThisCall(0, 0x30, 2, (int)id, amount);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.RestoreActorValue"/>.
            /// </summary>
            virtual void __clrcall RestoreActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto actor = this->As<Actor^>();
                if(actor == nullptr) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::ActorValueOwner_RestoreActorValue), actor->Address, (int)id, amount);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.ForceActorValue"/>.
            /// </summary>
            virtual void __clrcall ForceActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                amount -= self->GetActorValue(id);
                self->InvokeVTableThisCall(0, 0x30, 0, (int)id, amount);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.ModActorValue"/>.
            /// </summary>
            virtual void __clrcall ModActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                self->InvokeVTableThisCall(0, 0x30, 0, (int)id, amount);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.SetActorValue"/>.
            /// </summary>
            virtual void __clrcall SetActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                self->InvokeVTableThisCall(0, 0x38, (int)id, amount);
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.IncRef"/>.
            /// </summary>
            virtual void __clrcall IncRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                Memory::InterlockedIncrement32(self->Address + 0x8, false);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.DecRef"/>.
            /// </summary>
            virtual bool __clrcall DecRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                auto result = Memory::InterlockedDecrement32(self->Address + 0x8, false);
                if(this->Is<BSHandleRefObject^>()) result = result & 0x3FF;
                if(result == 0)
                {
                    self->InvokeVTableThisCall(0, 0x8);
                    return true;
                }
                return false;
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="PlayerCharacter"/>.
        /// </summary>
        private ref class impl_PlayerCharacter sealed : public VirtualObject, public PlayerCharacter
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="Actor.Race"/>.
            /// </summary>
            virtual property TESRace^ Race
            {
                TESRace^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESRace^>(Memory::ReadPointer(this->Address + 0x1F0, false));
                }
                void __clrcall set(TESRace^ value) sealed
                {
                    auto self = this;
                    MCH::e<TESRace^>(value, "value");
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_Race_Set), 0, 0, self->Address, value->Address);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.UpdateMovementControllerPosition"/>.
            /// </summary>
            virtual void __clrcall UpdateMovementControllerPosition(NiPoint3^ pos) sealed
            {
                auto self = this;
                if(pos == nullptr) throw gcnew System::ArgumentNullException("pos");
                auto controller = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_UpdateMovementControllerPosition), self->Address);
                if(controller != System::IntPtr::Zero)
                {
                    auto type = this->MovementState;
                    if(type != bhkCharacterStateTypes::Flying)
                    {
                        stack10 alloc;
                        alloc.set(0, pos->X * 0.0142875f);
                        alloc.set(4, pos->Y * 0.0142875f);
                        alloc.set(8, pos->Z * 0.0142875f);
                        auto vtable = Memory::ReadPointer(controller, false);
                        Memory::InvokeCdecl(vtable + 24, controller, alloc.ptr(), 1, 0);
                    }
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.AddPerk"/>.
            /// </summary>
            virtual void __clrcall AddPerk(BGSPerk^ perk) sealed
            {
                auto self = this;
                MCH::e<BGSPerk^>(perk, "perk");
                self->InvokeVTableThisCall(0, 0x7D8, perk->Address, 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.AddShout"/>.
            /// </summary>
            virtual void __clrcall AddShout(TESShout^ shout) sealed
            {
                auto self = this;
                MCH::e<TESShout^>(shout, "shout");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_AddShout), self->Address, shout->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.AddSpell"/>.
            /// </summary>
            virtual bool __clrcall AddSpell(SpellItem^ spell, bool showLearnedMessage) sealed
            {
                auto self = this;
                MCH::e<SpellItem^>(spell, "spell");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_AddSpell), 0, 0, self->Address, spell->Address, showLearnedMessage ? 1 : 0)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.AllowBleedoutDialogue"/>.
            /// </summary>
            virtual void __clrcall AllowBleedoutDialogue(bool allow) sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_AllowBleedoutDialogue), 0, 0, self->Address, allow ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.AllowPCDialogue"/>.
            /// </summary>
            virtual void __clrcall AllowPCDialogue(bool allow) sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_AllowPCDialogue), 0, 0, self->Address, allow ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.ClearArrested"/>.
            /// </summary>
            virtual void __clrcall ClearArrested() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ClearArrested), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.CanFlyHere"/>.
            /// </summary>
            virtual property bool CanFlyHere
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_CanFlyHere_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.ClearExpressionOverride"/>.
            /// </summary>
            virtual void __clrcall ClearExpressionOverride() sealed
            {
                auto self = this;
                auto ptr = self->InvokeVTableThisCall(0, 0x318);
                if(ptr == System::IntPtr::Zero) return;
                Memory::WriteUInt8(ptr + 542, 0, false);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.ClearExtraArrows"/>.
            /// </summary>
            virtual void __clrcall ClearExtraArrows() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ClearExtraArrows), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.ClearKeepOffsetFromActor"/>.
            /// </summary>
            virtual void __clrcall ClearKeepOffsetFromActor() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ClearKeepOffsetFromActor), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.ClearLookAtObject"/>.
            /// </summary>
            virtual void __clrcall ClearLookAtObject() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ClearLookAtObject), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.Dismount"/>.
            /// </summary>
            virtual bool __clrcall Dismount() sealed
            {
                auto self = this;
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_Dismount), 0, 0, self->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.DispelAllSpells"/>.
            /// </summary>
            virtual void __clrcall DispelAllSpells() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_DispelAllSpells), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.DispelSpell"/>.
            /// </summary>
            virtual bool __clrcall DispelSpell(SpellItem^ spell) sealed
            {
                auto self = this;
                MCH::e<SpellItem^>(spell, "spell");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_DispelSpell), 0, 0, self->Address, spell->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.DoCombatSpellApply"/>.
            /// </summary>
            virtual void __clrcall DoCombatSpellApply(SpellItem^ spell, TESObjectREFR^ target) sealed
            {
                auto self = this;
                MCH::e<SpellItem^>(spell, "spell");
                MCH::e<TESObjectREFR^>(target, "target");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_DoCombatSpellApply), 0, 0, self->Address, spell->Address, target->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.DrawWeapon"/>.
            /// </summary>
            virtual void __clrcall DrawWeapon() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_DrawWeapon), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.EnableAI"/>.
            /// </summary>
            virtual void __clrcall EnableAI(bool enable) sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_EnableAI), 0, 0, self->Address, enable ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.EndDeferredKill"/>.
            /// </summary>
            virtual void __clrcall EndDeferredKill() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_EndDeferredKill), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.EquipItem"/>.
            /// </summary>
            virtual void __clrcall EquipItem(TESForm^ form, bool preventUnequip, bool silent) sealed
            {
                auto self = this;
                MCH::e<TESForm^>(form, "form");
                auto has3d = MCH::u(form->InvokeVTableThisCall(0, 0x138));
                if((has3d & 0xFF) == 0) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_EquipItem), 0, 0, self->Address, form->Address, preventUnequip ? 1 : 0, silent ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.EquipShout"/>.
            /// </summary>
            virtual void __clrcall EquipShout(TESShout^ shout) sealed
            {
                auto self = this;
                MCH::e<TESShout^>(shout, "shout");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_EquipShout), 0, 0, self->Address, shout->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.EvaluatePackage"/>.
            /// </summary>
            virtual void __clrcall EvaluatePackage() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_EvaluatePackage), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetBribeAmount"/>.
            /// </summary>
            virtual System::Int32 __clrcall GetBribeAmount() sealed
            {
                auto self = this;
                return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetBribeAmount), 0, 0, self->Address)) & 0xFFFFFFFF);
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.CombatState"/>.
            /// </summary>
            virtual property ActorCombatStates CombatState
            {
                ActorCombatStates __clrcall get() sealed
                {
                    auto self = this;
                    return (ActorCombatStates)(System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_CombatState_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.CombatTarget"/>.
            /// </summary>
            virtual property Actor^ CombatTarget
            {
                Actor^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<Actor^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_CombatTarget_Get), 0, 0, self->Address));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.CrimeFaction"/>.
            /// </summary>
            virtual property TESFaction^ CrimeFaction
            {
                TESFaction^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<TESFaction^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_CrimeFaction_Get), 0, 0, self->Address));
                }
                void __clrcall set(TESFaction^ value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_CrimeFaction_Set), 0, 0, self->Address, value != nullptr ? value->Address : System::IntPtr::Zero);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.CurrentPackage"/>.
            /// </summary>
            virtual property TESPackage^ CurrentPackage
            {
                TESPackage^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<TESPackage^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_CurrentPackage_Get), 0, 0, self->Address));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.DialogueTarget"/>.
            /// </summary>
            virtual property Actor^ DialogueTarget
            {
                Actor^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<Actor^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_DialogueTarget_Get), 0, 0, self->Address));
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetEquippedArmorInSlot"/>.
            /// </summary>
            virtual TESObjectARMO^ __clrcall GetEquippedArmorInSlot(EquipSlots slot) sealed
            {
                auto self = this;
                auto ptr = Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_Inventory_Get), self->Address);
                if(ptr == System::IntPtr::Zero) return nullptr;
                return MemoryObject::FromAddressSafeCast<TESObjectARMO^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetEquippedArmorInSlot), ptr, (int)slot));
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetEquippedItemType"/>.
            /// </summary>
            virtual EquippedItemTypes __clrcall GetEquippedItemType(EquippedHandSlots slot) sealed
            {
                auto self = this;
                auto ptr = Memory::ReadPointer(self->Address + 0xF0, false);
                int rs = 0;
                if(ptr != System::IntPtr::Zero)
                {
                    System::IntPtr obj = System::IntPtr::Zero;
                    if(slot == EquippedHandSlots::LeftHand) obj = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetEquippedItemType_LeftHand), ptr);
                    else if(slot == EquippedHandSlots::RightHand) obj = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetEquippedItemType_RightHand), ptr);
                    if(obj != System::IntPtr::Zero)
                    {
                        auto typeId = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetEquippedItemType_ItemType), obj);
                        rs = (int)(typeId.ToInt64() & 0xFFFF);
                    }
                }
                return (EquippedItemTypes)rs;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetEquippedShield"/>.
            /// </summary>
            virtual TESObjectARMO^ __clrcall GetEquippedShield() sealed
            {
                auto self = this;
                return MemoryObject::FromAddress<TESObjectARMO^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetEquippedShield), 0, 0, self->Address));
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetEquippedShout"/>.
            /// </summary>
            virtual TESShout^ __clrcall GetEquippedShout() sealed
            {
                auto self = this;
                return MemoryObject::FromAddress<TESShout^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetEquippedShout), 0, 0, self->Address));
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetEquippedSpell"/>.
            /// </summary>
            virtual SpellItem^ __clrcall GetEquippedSpell(EquippedSpellSlots slot) sealed
            {
                auto self = this;
                System::UInt32 arg = (System::UInt32)slot;
                if(arg >= 4) return nullptr;
                return MemoryObject::FromAddress<SpellItem^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetEquippedSpell), 0, 0, self->Address, arg));
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetFactionRank"/>.
            /// </summary>
            virtual System::Int32 __clrcall GetFactionRank(TESFaction^ faction) sealed
            {
                auto self = this;
                MCH::e<TESFaction^>(faction, "faction");
                return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetFactionRank), 0, 0, self->Address, faction->Address)) & 0xFFFFFFFF);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetFactionReaction"/>.
            /// </summary>
            virtual FactionReactions __clrcall GetFactionReaction(Actor^ other) sealed
            {
                auto self = this;
                MCH::e<Actor^>(other, "other");
                return (FactionReactions)(System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetFactionReaction), 0, 0, self->Address, other->Address)) & 0xFFFFFFFF);
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.FlyingState"/>.
            /// </summary>
            virtual property FlyingStates FlyingState
            {
                FlyingStates __clrcall get() sealed
                {
                    auto self = this;
                    return (FlyingStates)(System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_FlyingState_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.ForcedLandingMarker"/>.
            /// </summary>
            virtual property TESObjectREFR^ ForcedLandingMarker
            {
                TESObjectREFR^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<TESObjectREFR^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ForcedLandingMarker_Get), 0, 0, self->Address));
                }
                void __clrcall set(TESObjectREFR^ value) sealed
                {
                    auto self = this;
                    MCH::e<TESObjectREFR^>(value, nullptr);
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ForcedLandingMarker_Set), 0, 0, self->Address, value != nullptr ? value->Address : System::IntPtr::Zero);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetGoldAmount"/>.
            /// </summary>
            virtual System::Int32 __clrcall GetGoldAmount() sealed
            {
                auto self = this;
                return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetGoldAmount), 0, 0, self->Address)) & 0xFFFFFFFF);
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.HighestRelationshipRank"/>.
            /// </summary>
            virtual property RelationshipRanks HighestRelationshipRank
            {
                RelationshipRanks __clrcall get() sealed
                {
                    auto self = this;
                    return (RelationshipRanks)(System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_HighestRelationshipRank_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.KilledBy"/>.
            /// </summary>
            virtual property Actor^ KilledBy
            {
                Actor^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<Actor^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_KilledBy_Get), 0, 0, self->Address));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.Level"/>.
            /// </summary>
            virtual property System::Int32 Level
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this;
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_Level_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.BaseActor"/>.
            /// </summary>
            virtual property TESNPC^ BaseActor
            {
                TESNPC^ __clrcall get() sealed
                {
                    auto self = this;
                    auto npc = MemoryObject::FromAddress<TESNPC^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_BaseActor_Get), 0, 0, self->Address));
                    if(npc == nullptr)
                    {
                    auto obj = self->BaseForm;
                    if(obj != nullptr)
                    npc = obj->As<TESNPC^>();
                    }
                    return npc;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.LightLevel"/>.
            /// </summary>
            virtual property System::Single LightLevel
            {
                System::Single __clrcall get() sealed
                {
                    auto self = this;
                    return (float)Memory::InvokeCdeclF(MCH::FromBase(GameAddress::Actor_LightLevel_Get), 0, 0, self->Address);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.LowestRelationshipRank"/>.
            /// </summary>
            virtual property RelationshipRanks LowestRelationshipRank
            {
                RelationshipRanks __clrcall get() sealed
                {
                    auto self = this;
                    return (RelationshipRanks)(System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_LowestRelationshipRank_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.NoBleedoutRecovery"/>.
            /// </summary>
            virtual property bool NoBleedoutRecovery
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_NoBleedoutRecovery_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_NoBleedoutRecovery_Set), 0, 0, self->Address, value ? 1 : 0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.ReceivesPlayerControls"/>.
            /// </summary>
            virtual property bool ReceivesPlayerControls
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ReceivesPlayerControls_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ReceivesPlayerControls_Set), 0, 0, self->Address, value ? 1 : 0);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetRelationshipRank"/>.
            /// </summary>
            virtual RelationshipRanks __clrcall GetRelationshipRank(Actor^ other) sealed
            {
                auto self = this;
                MCH::e<Actor^>(other, "other");
                return (RelationshipRanks)(System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetRelationshipRank), 0, 0, self->Address, other->Address)) & 0xFFFFFFFF);
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.SitState"/>.
            /// </summary>
            virtual property ActorActionStates SitState
            {
                ActorActionStates __clrcall get() sealed
                {
                    auto self = this;
                    return (ActorActionStates)(System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SitState_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.SleepState"/>.
            /// </summary>
            virtual property ActorActionStates SleepState
            {
                ActorActionStates __clrcall get() sealed
                {
                    auto self = this;
                    return (ActorActionStates)(System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SleepState_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.VoiceRecoveryTime"/>.
            /// </summary>
            virtual property System::Single VoiceRecoveryTime
            {
                System::Single __clrcall get() sealed
                {
                    auto self = this;
                    return (float)Memory::InvokeCdeclF(MCH::FromBase(GameAddress::Actor_VoiceRecoveryTime_Get), 0, 0, self->Address);
                }
                void __clrcall set(System::Single value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_VoiceRecoveryTime_Set), 0, 0, self->Address, value);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.WarmthRating"/>.
            /// </summary>
            virtual property System::Single WarmthRating
            {
                System::Single __clrcall get() sealed
                {
                    auto self = this;
                    return (float)Memory::InvokeCdeclF(MCH::FromBase(GameAddress::Actor_WarmthRating_Get), 0, 0, self->Address);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.HasAssociation"/>.
            /// </summary>
            virtual bool __clrcall HasAssociation(BGSAssociationType^ type, Actor^ other) sealed
            {
                auto self = this;
                MCH::e<BGSAssociationType^>(type, "type");
                MCH::e<Actor^>(other, nullptr);
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_HasAssociation), 0, 0, self->Address, type->Address, other != nullptr ? other->Address : System::IntPtr::Zero)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.HasFamilyRelationship"/>.
            /// </summary>
            virtual bool __clrcall HasFamilyRelationship(Actor^ other) sealed
            {
                auto self = this;
                MCH::e<Actor^>(other, nullptr);
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_HasFamilyRelationship), 0, 0, self->Address, other != nullptr ? other->Address : System::IntPtr::Zero)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.HasLOS_Papyrus"/>.
            /// </summary>
            virtual bool __clrcall HasLOS_Papyrus(TESObjectREFR^ other) sealed
            {
                auto self = this;
                MCH::e<TESObjectREFR^>(other, "other");
                if(other->FormType != FormTypes::Character && !self->Equals(PlayerCharacter::Instance)) return false;
                stack10 s;
                auto ptrResult = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_HasLOS_Papyrus), self->Address, other->Address, s.ptr());
                auto result = MCH::u(ptrResult);
                return (result & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.HasParentRelationship"/>.
            /// </summary>
            virtual bool __clrcall HasParentRelationship(Actor^ other) sealed
            {
                auto self = this;
                MCH::e<Actor^>(other, "other");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_HasParentRelationship), 0, 0, self->Address, other->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsAlarmed"/>.
            /// </summary>
            virtual property bool IsAlarmed
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsAlarmed_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsAllowedToFly"/>.
            /// </summary>
            virtual property bool IsAllowedToFly
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsAllowedToFly_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsAllowedToFly_Set), 0, 0, self->Address, value ? 1 : 0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsArrested"/>.
            /// </summary>
            virtual property bool IsArrested
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsArrested_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsBleedingOut"/>.
            /// </summary>
            virtual property bool IsBleedingOut
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsBleedingOut_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsDead"/>.
            /// </summary>
            virtual property bool IsDead
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsDead_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.CanDetect"/>.
            /// </summary>
            virtual bool __clrcall CanDetect(Actor^ target) sealed
            {
                auto self = this;
                MCH::e<Actor^>(target, "target");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_CanDetect), 0, 0, target->Address, self->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.IsEquipped"/>.
            /// </summary>
            virtual bool __clrcall IsEquipped(TESForm^ form) sealed
            {
                auto self = this;
                MCH::e<TESForm^>(form, "form");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsEquipped), 0, 0, self->Address, form->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsPlayersLastRiddenHorse"/>.
            /// </summary>
            virtual property bool IsPlayersLastRiddenHorse
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsPlayersLastRiddenHorse_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsArrestingTarget"/>.
            /// </summary>
            virtual property bool IsArrestingTarget
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsArrestingTarget_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsAlerted"/>.
            /// </summary>
            virtual property bool IsAlerted
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsAlerted_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsAlerted_Set), 0, 0, self->Address, value ? 1 : 0);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.HasPerk"/>.
            /// </summary>
            virtual bool __clrcall HasPerk(BGSPerk^ perk) sealed
            {
                auto self = this;
                MCH::e<BGSPerk^>(perk, "perk");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_HasPerk), 0, 0, self->Address, perk->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.HasSpell"/>.
            /// </summary>
            virtual bool __clrcall HasSpell(TESForm^ spellOrShout) sealed
            {
                auto self = this;
                if(spellOrShout == nullptr) throw gcnew System::ArgumentNullException("spellOrShout");
                auto formType = spellOrShout->FormType;
                if(formType == FormTypes::Spell)
                {
                    auto arg = spellOrShout->As<SpellItem^>();
                    if(arg != nullptr) return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_HasSpell_Spell), self->Address, arg->Address)) & 0xFF) != 0;
                }
                else if(formType == FormTypes::Shout)
                {
                    auto arg = spellOrShout->As<TESShout^>();
                    if(arg != nullptr) return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_HasSpell_Shout), self->Address, arg->Address)) & 0xFF) != 0;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsBribed"/>.
            /// </summary>
            virtual property bool IsBribed
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsBribed_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsBribed_Set), 0, 0, self->Address, value ? 1 : 0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsChild"/>.
            /// </summary>
            virtual property bool IsChild
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsChild_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsCommandedActor"/>.
            /// </summary>
            virtual property bool IsCommandedActor
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsCommandedActor_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsDoingFavor"/>.
            /// </summary>
            virtual property bool IsDoingFavor
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsDoingFavor_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsDoingFavor_Set), 0, 0, self->Address, value ? 1 : 0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsEssential"/>.
            /// </summary>
            virtual property bool IsEssential
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsEssential_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsFlying"/>.
            /// </summary>
            virtual property bool IsFlying
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsFlying_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsGhost"/>.
            /// </summary>
            virtual property bool IsGhost
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsGhost_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsGhost_Set), 0, 0, self->Address, value ? 1 : 0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsGuard"/>.
            /// </summary>
            virtual property bool IsGuard
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsGuard_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.IsHostileToActor"/>.
            /// </summary>
            virtual bool __clrcall IsHostileToActor(Actor^ target) sealed
            {
                auto self = this;
                MCH::e<Actor^>(target, "target");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsHostileToActor), 0, 0, self->Address, target->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsInCombat"/>.
            /// </summary>
            virtual property bool IsInCombat
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsInCombat_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.IsInFaction"/>.
            /// </summary>
            virtual bool __clrcall IsInFaction(TESFaction^ faction) sealed
            {
                auto self = this;
                MCH::e<TESFaction^>(faction, "faction");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsInFaction), 0, 0, self->Address, faction->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsInKillmove"/>.
            /// </summary>
            virtual property bool IsInKillmove
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsInKillmove_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsIntimidated"/>.
            /// </summary>
            virtual property bool IsIntimidated
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsIntimidated_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsIntimidated_Set), 0, 0, self->Address, value ? 1 : 0 );
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsOnMount"/>.
            /// </summary>
            virtual property bool IsOnMount
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsOnMount_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsOverEncumbered"/>.
            /// </summary>
            virtual property bool IsOverEncumbered
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsOverEncumbered_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsPlayerTeammate"/>.
            /// </summary>
            virtual property bool IsPlayerTeammate
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsPlayerTeammate_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsRunning"/>.
            /// </summary>
            virtual property bool IsRunning
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsRunning_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsSneaking"/>.
            /// </summary>
            virtual property bool IsSneaking
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsSneaking_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    if(this->IsSneaking == value) return;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsSneaking_Set), 0, 0, self->Address); // This is a toggle
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsSprinting"/>.
            /// </summary>
            virtual property bool IsSprinting
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsSprinting_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsTrespassing"/>.
            /// </summary>
            virtual property bool IsTrespassing
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsTrespassing_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsUnconscious"/>.
            /// </summary>
            virtual property bool IsUnconscious
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsUnconscious_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsUnconscious_Set), 0, 0, self->Address, value ? 1 : 0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsWeaponDrawn"/>.
            /// </summary>
            virtual property bool IsWeaponDrawn
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsWeaponDrawn_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.Kill"/>.
            /// </summary>
            virtual void __clrcall Kill(Actor^ killer, bool noEvents, bool force) sealed
            {
                auto self = this;
                MCH::e<Actor^>(killer, nullptr);
                if(!force)
                {
                    auto mt = this->As<MagicTarget^>();
                    if(mt == nullptr) return;
                    auto res1 = MCH::u(mt->InvokeVTableThisCall(0, 0x20));
                    auto res2 = MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_Kill_1), self->Address));
                    bool ok = (res1 & 0xFF) == 0 || (res2 & 0xFF) != 0;
                    if(!ok) return;
                }
                if((Memory::ReadUInt32(self->Address + 0xC0, false) & 0x1E00000) == 0xE00000)
                {
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_Kill_2), self->Address, 0, noEvents ? 0 : 1);
                }
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_Kill_3), self->Address, killer != nullptr ? killer->Address : System::IntPtr::Zero, (double)0.0, noEvents ? 0 : 1, 0);
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsPlayer"/>.
            /// </summary>
            virtual property bool IsPlayer
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    auto plr = PlayerCharacter::Instance;
                    if(plr == nullptr) return false;
                    return self->Address == plr->Address;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.RemoveFromFaction"/>.
            /// </summary>
            virtual void __clrcall RemoveFromFaction(TESFaction^ faction) sealed
            {
                auto self = this;
                MCH::e<TESFaction^>(faction, "faction");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_RemoveFromFaction), 0, 0, self->Address, faction->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.RemoveFromAllFactions"/>.
            /// </summary>
            virtual void __clrcall RemoveFromAllFactions() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_RemoveFromAllFactions), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.RemovePerk"/>.
            /// </summary>
            virtual void __clrcall RemovePerk(BGSPerk^ perk) sealed
            {
                auto self = this;
                MCH::e<BGSPerk^>(perk, "perk");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_RemovePerk), 0, 0, self->Address, perk->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.RemoveShout"/>.
            /// </summary>
            virtual bool __clrcall RemoveShout(TESShout^ shout) sealed
            {
                auto self = this;
                MCH::e<TESShout^>(shout, "shout");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_RemoveShout), 0, 0, self->Address, shout->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.RemoveSpell"/>.
            /// </summary>
            virtual bool __clrcall RemoveSpell(SpellItem^ spell) sealed
            {
                auto self = this;
                MCH::e<SpellItem^>(spell, "spell");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_RemoveSpell), 0, 0, self->Address, spell->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.ResetHealthAndLimbs"/>.
            /// </summary>
            virtual void __clrcall ResetHealthAndLimbs() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ResetHealthAndLimbs), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.Resurrect"/>.
            /// </summary>
            virtual void __clrcall Resurrect() sealed
            {
                auto self = this;
                System::IntPtr arg = System::IntPtr::Zero;
                if(self->InvokeVTableThisCall(0, 0x380) != System::IntPtr::Zero) arg = System::IntPtr(1);
                self->InvokeVTableThisCall(0, 0x558, 1, arg);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SendAssaultAlarm"/>.
            /// </summary>
            virtual void __clrcall SendAssaultAlarm(Actor^ assaulter) sealed
            {
                auto self = this;
                MCH::e<Actor^>(assaulter, "assaulter");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SendAssaultAlarm_1), self->Address, assaulter->Address);
                System::UInt32 flags = Memory::ReadUInt32(self->Address + 0xE0, false);
                if(((flags >> 30) & 1) != 0) return;
                auto process = Memory::ReadPointer(self->Address + 0xF0, false);
                if(process == System::IntPtr::Zero) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SendAssaultAlarm_2), process, self->Address, assaulter->Address, 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SendTrespassAlarm"/>.
            /// </summary>
            virtual void __clrcall SendTrespassAlarm(Actor^ criminal) sealed
            {
                auto self = this;
                MCH::e<Actor^>(criminal, "criminal");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SendTrespassAlarm), 0, 0, self->Address, criminal->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetAllowFlyingEx"/>.
            /// </summary>
            virtual void __clrcall SetAllowFlyingEx(bool allowFly, bool allowCrash, bool allowSearch) sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetAllowFlyingEx), 0, 0, self->Address, allowFly ? 1 : 0, allowCrash ? 1 : 0, allowSearch ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetAlpha"/>.
            /// </summary>
            virtual void __clrcall SetAlpha(System::Single alpha, bool fade) sealed
            {
                auto self = this;
                auto process = Memory::ReadPointer(self->Address + 0xF0, false);
                if(process == System::IntPtr::Zero) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetAlpha), 0, 0, self->Address, alpha, fade ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetAttackedByAllOnSight"/>.
            /// </summary>
            virtual void __clrcall SetAttackedByAllOnSight(bool should) sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetAttackedByAllOnSight), 0, 0, self->Address, should ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetCriticalStage"/>.
            /// </summary>
            virtual void __clrcall SetCriticalStage(ActorCriticalStages stage) sealed
            {
                auto self = this;
                int _s = (int)stage;
                if(_s < 0 || _s >= 5) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetCriticalStage), self->Address, (int)stage);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetDontMove"/>.
            /// </summary>
            virtual void __clrcall SetDontMove(bool dontMove) sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetDontMove), 0, 0, self->Address, dontMove ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetExpressionOverride"/>.
            /// </summary>
            virtual bool __clrcall SetExpressionOverride(System::Int32 expression, System::Single amount) sealed
            {
                auto self = this;
                if(expression <= 0 || expression > 16) return false;
                amount = System::Math::Min(1.0f, System::Math::Max(0.0f, amount));
                auto faceAnim = self->InvokeVTableThisCall(0, 0x318);
                if(faceAnim == System::IntPtr::Zero) return false;
                Memory::WriteUInt8(faceAnim + 0x21E, 0, false);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetExpressionOverride), faceAnim, expression, amount);
                Memory::WriteUInt8(faceAnim + 0x21E, 1, false);
                return true;
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsHeadTrackingEnabled"/>.
            /// </summary>
            virtual property bool IsHeadTrackingEnabled
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    System::UInt32 flags = Memory::ReadUInt32(self->Address + 0xC4, false);
                    return (flags & 8) != 0;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    System::UInt32 flags = Memory::ReadUInt32(self->Address + 0xC4, false);
                    if(value) flags |= 8;
                    else flags &= ~8;
                    Memory::WriteUInt32(self->Address + 0xC4, flags, false);
                    if(this->IsPlayer) this->SetAnimationVariableBool("IsNPC", value);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetLookAtObject"/>.
            /// </summary>
            virtual void __clrcall SetLookAtObject(TESObjectREFR^ target, bool whilePathing) sealed
            {
                auto self = this;
                MCH::e<TESObjectREFR^>(target, nullptr);
                if(target == nullptr)
                {
                    this->ClearLookAtObject();
                    return;
                }
                auto process = Memory::ReadPointer(self->Address + 0xF0, false);
                if(process == System::IntPtr::Zero) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetLookAtObject), 0, 0, self->Address, target->Address, whilePathing ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.ShowOnStealthMeter"/>.
            /// </summary>
            virtual property bool ShowOnStealthMeter
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    System::UInt32 flags = Memory::ReadUInt32(self->Address + 0x1FC, false);
                    bool notShowFlag = (flags & 0x4000000) != 0;
                    return !notShowFlag;
                }
                void __clrcall set(bool value) sealed
                {
                    auto self = this;
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ShowOnStealthMeter_Set), 0, 0, self->Address, !value ? 1 : 0);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetOutfit"/>.
            /// </summary>
            virtual void __clrcall SetOutfit(BGSOutfit^ outfit, bool sleepOutfit) sealed
            {
                auto self = this;
                MCH::e<BGSOutfit^>(outfit, "outfit");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetOutfit), 0, 0, self->Address, outfit->Address, sleepOutfit ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetPlayerResistingArrest"/>.
            /// </summary>
            virtual void __clrcall SetPlayerResistingArrest() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetPlayerResistingArrest), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetPlayerTeammate"/>.
            /// </summary>
            virtual void __clrcall SetPlayerTeammate(bool teammate, bool canDoFavors) sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetPlayerTeammate), 0, 0, self->Address, teammate ? 1 : 0, canDoFavors ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetRelationshipRank"/>.
            /// </summary>
            virtual void __clrcall SetRelationshipRank(Actor^ other, RelationshipRanks rank) sealed
            {
                auto self = this;
                MCH::e<Actor^>(other, "other");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetRelationshipRank), 0, 0, self->Address, other->Address, (int)rank);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetRestrained"/>.
            /// </summary>
            virtual void __clrcall SetRestrained(bool restrained) sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetRestrained), 0, 0, self->Address, restrained ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetVehicle"/>.
            /// </summary>
            virtual void __clrcall SetVehicle(TESObjectREFR^ vehicle) sealed
            {
                auto self = this;
                MCH::e<TESObjectREFR^>(vehicle, nullptr);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetVehicle), 0, 0, self->Address, vehicle != nullptr ? vehicle->Address : System::IntPtr::Zero);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.ShowBarterMenu"/>.
            /// </summary>
            virtual void __clrcall ShowBarterMenu() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ShowBarterMenu), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.StartCombat"/>.
            /// </summary>
            virtual bool __clrcall StartCombat(Actor^ target) sealed
            {
                auto self = this;
                MCH::e<Actor^>(target, "target");
                if(self->IsPlayer) return false;
                if(Memory::ReadPointer(self->Address + 0xF0, false) == System::IntPtr::Zero) return false;
                if(Memory::ReadPointer(target->Address + 0xF0, false) == System::IntPtr::Zero) return false;
                if((MCH::u(self->InvokeVTableThisCall(0, 0x4C8, 0)) & 0xFF) != 0) return false;
                if((MCH::u(target->InvokeVTableThisCall(0, 0x4C8, 0)) & 0xFF) != 0) return false;
                if(!target->IsPlayer)
                {
                    auto p = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_StartCombat_1), self->Address);
                    if((MCH::u(p) & 0xFF) != 0) return false;
                }
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_StartCombat_2), Memory::ReadPointer(MCH::FromBase(GameAddress::Actor_StartCombat_3), false), self->Address, target->Address);
                return true;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.StartDeferredKill"/>.
            /// </summary>
            virtual void __clrcall StartDeferredKill() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_StartDeferredKill), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.StopCombatAlarm"/>.
            /// </summary>
            virtual void __clrcall StopCombatAlarm() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_StopCombatAlarm), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.StopCombat"/>.
            /// </summary>
            virtual void __clrcall StopCombat() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_StopCombat), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.TrapSoul"/>.
            /// </summary>
            virtual bool __clrcall TrapSoul(Actor^ target) sealed
            {
                auto self = this;
                MCH::e<Actor^>(target, "target");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_TrapSoul), 0, 0, self->Address, target->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.UnlockOwnedDoorsInCell"/>.
            /// </summary>
            virtual void __clrcall UnlockOwnedDoorsInCell() sealed
            {
                auto self = this;
                auto cell = this->ParentCell;
                if(cell == nullptr || !cell->IsInterior) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_UnlockOwnedDoorsInCell), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.UnequipAll"/>.
            /// </summary>
            virtual void __clrcall UnequipAll() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_UnequipAll), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.UnequipItemSlot"/>.
            /// </summary>
            virtual void __clrcall UnequipItemSlot(EquipSlots slot) sealed
            {
                auto self = this;
                auto data = Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_Inventory_Get), self->Address);
                if(data == System::IntPtr::Zero) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_UnequipItemSlot), data, (int)slot, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.UnequipItem"/>.
            /// </summary>
            virtual void __clrcall UnequipItem(TESForm^ form, bool preventEquip, bool silent) sealed
            {
                auto self = this;
                MCH::e<TESForm^>(form, "form");
                if(!form->Has3D) return;
                auto cont = Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_Inventory_Get), self->Address);
                if(cont == System::IntPtr::Zero) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_UnequipItem), 0, 0, self->Address, form->Address, preventEquip ? 1 : 0, silent ? 1 : 0);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.UnequipShout"/>.
            /// </summary>
            virtual void __clrcall UnequipShout(TESShout^ shout) sealed
            {
                auto self = this;
                MCH::e<TESShout^>(shout, "shout");
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_UnequipShout), 0, 0, self->Address, shout->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.UnequipSpell"/>.
            /// </summary>
            virtual void __clrcall UnequipSpell(SpellItem^ spell, EquippedSpellSlots slot) sealed
            {
                auto self = this;
                MCH::e<SpellItem^>(spell, "spell");
                int _s = (int)slot;
                if(_s < 0 || _s >= 3) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_UnequipSpell), 0, 0, self->Address, spell->Address, (int)slot);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.EquipSpell"/>.
            /// </summary>
            virtual void __clrcall EquipSpell(SpellItem^ spell, EquippedSpellSlots slot) sealed
            {
                auto self = this;
                MCH::e<SpellItem^>(spell, "spell");
                int _s = (int)slot;
                if(_s < 0 || _s >= 3) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_EquipSpell), 0, 0, self->Address, spell->Address, (int)slot);
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.WillIntimidateSucceed"/>.
            /// </summary>
            virtual property bool WillIntimidateSucceed
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_WillIntimidateSucceed_Get), 0, 0, self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.WornHasKeyword"/>.
            /// </summary>
            virtual bool __clrcall WornHasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this;
                MCH::e<BGSKeyword^>(keyword, "keyword");
                auto cont = Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_Inventory_Get), self->Address);
                if(cont == System::IntPtr::Zero) return false;
                auto result = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_WornHasKeyword), cont, keyword->Address);
                return (MCH::u(result) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.WornHasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall WornHasKeywordText(System::String^ keyword) sealed
            {
                auto self = this;
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto cont = Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_Inventory_Get), self->Address);
                if(cont == System::IntPtr::Zero) return false;
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    auto result = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_WornHasKeyword), cont, kw->Address);
                    if((MCH::u(result) & 0xFF) != 0) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.ClearLookAtPosition"/>.
            /// </summary>
            virtual void __clrcall ClearLookAtPosition() sealed
            {
                auto self = this;
                auto process = Memory::ReadPointer(self->Address + 0xF0, false);
                if(process == System::IntPtr::Zero) return;
                auto race = this->Race;
                if(race == nullptr || !race->CanHeadTrack) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_ClearLookAtPosition), process, self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.SetLookAtPosition"/>.
            /// </summary>
            virtual void __clrcall SetLookAtPosition(NiPoint3^ position) sealed
            {
                auto self = this;
                if(position == nullptr)
                {
                    this->ClearLookAtPosition();
                    return;
                }
                auto process = Memory::ReadPointer(self->Address + 0xF0, false);
                if(process == System::IntPtr::Zero) return;
                auto race = this->Race;
                if(race == nullptr || !race->CanHeadTrack) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_SetLookAtPosition), process, self->Address, position->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.InterruptCast"/>.
            /// </summary>
            virtual void __clrcall InterruptCast() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_InterruptCast), self->Address, 0);
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsBeingRidden"/>.
            /// </summary>
            virtual property bool IsBeingRidden
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return MCH::b(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsBeingRidden_Get), self->Address));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsOnFlyingMount"/>.
            /// </summary>
            virtual property bool IsOnFlyingMount
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return MCH::b(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_IsOnFlyingMount_Get), self->Address));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.MovementState"/>.
            /// </summary>
            virtual property bhkCharacterStateTypes MovementState
            {
                bhkCharacterStateTypes __clrcall get() sealed
                {
                    auto self = this;
                    auto ptr = Memory::ReadPointer(self->Address + 0xF0, false);
                    if(ptr != System::IntPtr::Zero)
                    {
                    ptr = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_UpdateMovementControllerPosition), ptr);
                    if(ptr != System::IntPtr::Zero)
                    {
                    ptr = Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_MovementState_Get), ptr + 480);
                    return (bhkCharacterStateTypes)((int)(MCH::u(ptr) & 0xFF));
                    }
                    }
                    return bhkCharacterStateTypes::Unknown;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsJumping"/>.
            /// </summary>
            virtual property bool IsJumping
            {
                bool __clrcall get() sealed
                {
                    return this->MovementState == bhkCharacterStateTypes::Jumping;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="Actor.IsFalling"/>.
            /// </summary>
            virtual property bool IsFalling
            {
                bool __clrcall get() sealed
                {
                    return this->MovementState == bhkCharacterStateTypes::InAir;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetMount"/>.
            /// </summary>
            virtual Actor^ __clrcall GetMount() sealed
            {
                auto self = this;
                Actor^ result = nullptr;
                MemoryAllocation^ alloc = Memory::Allocate(0x10, 0, false);
                try
                {
                    Memory::WritePointer(alloc->Address, System::IntPtr::Zero, false);
                    if(MCH::b(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetMount), self->Address, alloc->Address)))
                    {
                        result = MemoryObject::FromAddress<Actor^>(Memory::ReadPointer(alloc->Address, false));
                        if(result != nullptr) result->DecRef();
                    }
                }
                finally
                {
                    delete alloc;
                }
                return result;
            }
            
            /// <summary>
            /// Implementation of method <see cref="Actor.GetMountedBy"/>.
            /// </summary>
            virtual Actor^ __clrcall GetMountedBy() sealed
            {
                auto self = this;
                Actor^ result = nullptr;
                MemoryAllocation^ alloc = Memory::Allocate(0x10, 0, false);
                try
                {
                    Memory::WritePointer(alloc->Address, System::IntPtr::Zero, false);
                    if(MCH::b(Memory::InvokeCdecl(MCH::FromBase(GameAddress::Actor_GetMountedBy), self->Address, alloc->Address)))
                    {
                        result = MemoryObject::FromAddress<Actor^>(Memory::ReadPointer(alloc->Address, false));
                        if(result != nullptr) result->DecRef();
                    }
                }
                finally
                {
                    delete alloc;
                }
                return result;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.BaseForm"/>.
            /// </summary>
            virtual property TESForm^ BaseForm
            {
                TESForm^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESForm^>(Memory::ReadPointer(this->Address + 0x40, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.ParentCell"/>.
            /// </summary>
            virtual property TESObjectCELL^ ParentCell
            {
                TESObjectCELL^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESObjectCELL^>(Memory::ReadPointer(this->Address + 0x60, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.ExtraDataList"/>.
            /// </summary>
            virtual property BSExtraDataList^ ExtraDataList
            {
                BSExtraDataList^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<BSExtraDataList^>(this->Address + 0x70);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.Position"/>.
            /// </summary>
            virtual property NiPoint3^ Position
            {
                NiPoint3^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPoint3^>(this->Address + 0x54);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.Rotation"/>.
            /// </summary>
            virtual property NiPoint3^ Rotation
            {
                NiPoint3^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPoint3^>(this->Address + 0x48);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.Node"/>.
            /// </summary>
            virtual property NiNode^ Node
            {
                NiNode^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<NiNode^>(self->InvokeVTableThisCall(0, 0x380, 0));
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESObjectREFR.Activate"/>.
            /// </summary>
            virtual bool __clrcall Activate(TESObjectREFR^ activator, bool skipEvents) sealed
            {
                auto self = this;
                MCH::e<TESObjectREFR^>(activator, "activator");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_Activate), self->Address, activator->Address, 0, 0, 1, skipEvents ? 1 : 0)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.CurrentLocation"/>.
            /// </summary>
            virtual property BGSLocation^ CurrentLocation
            {
                BGSLocation^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<BGSLocation^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_CurrentLocation_Get), self->Address));
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESObjectREFR.OpenInventory"/>.
            /// </summary>
            virtual void __clrcall OpenInventory(ContainerOpenTypes type) sealed
            {
                auto self = this;
                if(!self->HasInventory) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_OpenInventory), self->Address, (int)type);
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.HasInventory"/>.
            /// </summary>
            virtual property bool HasInventory
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    if(self->FormType == FormTypes::Character) return true;
                    if(this->Is<TESObjectCONT^>()) return true;
                    return false;
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESObjectREFR.Inventory"/>.
            /// </summary>
            virtual property ExtraContainerChanges::Data^ Inventory
            {
                ExtraContainerChanges::Data^ __clrcall get() sealed
                {
                    auto self = this;
                    auto ptr = Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_Inventory_Get), self->Address);
                    return MemoryObject::FromAddress<ExtraContainerChanges::Data^>(ptr);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESObjectREFR.SetAnimationVariableBool"/>.
            /// </summary>
            virtual bool __clrcall SetAnimationVariableBool(System::String^ name, bool value) sealed
            {
                if(name == nullptr) return false;
                auto graph = this->As<IAnimationGraphManagerHolder^>();
                if(graph == nullptr) return false;
                StringRefHolder^ str = gcnew StringRefHolder(name);
                try
                {
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_SetAnimationVariableBool), graph->Address, str->AddressOf, value ? 1 : 0)) & 0xFF) == 0;
                }
                finally
                {
                    delete str;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESObjectREFR.GetMagicCaster"/>.
            /// </summary>
            virtual MagicCaster^ __clrcall GetMagicCaster(EquippedSpellSlots slot) sealed
            {
                auto self = this;
                int sl = (int)slot;
                if(sl < 0 || sl > 2) return nullptr;
                auto ptr = self->InvokeVTableThisCall(0, 0x2E0, sl);
                return MemoryObject::FromAddress<MagicCaster^>(ptr);
            }
            
            
            /// <summary>
            /// Implementation of method <see cref="TESObjectREFR.GetExtraData"/>.
            /// </summary>
            virtual BSExtraData^ __clrcall GetExtraData(ExtraDataTypes type) sealed
            {
                auto self = this;
                auto ptr = Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectREFR_GetExtraData), self->Address, (int)type);
                return MemoryObject::FromAddress<BSExtraData^>(ptr);
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESObjectREFR.GetSkeletonNode"/>.
            /// </summary>
            virtual NiNode^ __clrcall GetSkeletonNode(bool firstPerson) sealed
            {
                auto self = this;
                auto ptr = self->InvokeVTableThisCall(0, 0x378, firstPerson ? 1 : 0);
                return MemoryObject::FromAddress<NiNode^>(ptr);
            }
            
            /// <summary>
            /// Implementation of property <see cref="MagicTarget.ActiveEffects"/>.
            /// </summary>
            virtual property ListNode<ActiveEffect^>^ ActiveEffects
            {
                ListNode<ActiveEffect^>^ __clrcall get() sealed
                {
                    auto self = this->As<MagicTarget^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x38);
                    return MemoryObject::FromAddress<ListNode<ActiveEffect^>^>(ptr);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="MagicTarget.HasMagicEffectWithKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasMagicEffectWithKeyword(BGSKeyword^ keyword, MagicItem^% item) sealed
            {
                auto self = this->As<MagicTarget^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                stack10 s;
                System::UInt64 p = MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::MagicTarget_HasMagicEffectWithKeyword), self->Address, keyword->Address, s.ptr()));
                if((p & 0xFF) == 0) return false;
                System::IntPtr itemPtr = System::IntPtr(s.get<void*>(0));
                if(itemPtr != System::IntPtr::Zero) item = MemoryObject::FromAddress<MagicItem^>(itemPtr);
                return true;
            }
            
            /// <summary>
            /// Implementation of method <see cref="MagicTarget.HasMagicEffectWithKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasMagicEffectWithKeywordText(System::String^ keyword, MagicItem^% item) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasMagicEffectWithKeyword(kw, item)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of method <see cref="MagicTarget.HasMagicEffect"/>.
            /// </summary>
            virtual bool __clrcall HasMagicEffect(EffectSetting^ effect) sealed
            {
                auto self = this->As<MagicTarget^>();
                MCH::e<EffectSetting^>(effect, "effect");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::MagicTarget_HasMagicEffect), self->Address, effect->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="MagicTarget.DispelEffectsWithArchetype"/>.
            /// </summary>
            virtual void __clrcall DispelEffectsWithArchetype(Archetypes archetype, TESObjectREFR^ onlyFromCaster) sealed
            {
                auto self = this->As<MagicTarget^>();
                MCH::e<TESObjectREFR^>(onlyFromCaster, nullptr);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::MagicTarget_DispelEffectsWithArchetype), self->Address, (int)archetype, onlyFromCaster != nullptr ? onlyFromCaster->Address : System::IntPtr::Zero);
            }
            
            /// <summary>
            /// Implementation of property <see cref="MagicTarget.HasMagicEffectThatCausesDamage"/>.
            /// </summary>
            virtual property bool HasMagicEffectThatCausesDamage
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<MagicTarget^>();
                    return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::MagicTarget_HasMagicEffectThatCausesDamage_Get), self->Address)) & 0xFF) != 0;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="MagicTarget.FindFirstEffectWithArchetype"/>.
            /// </summary>
            virtual ActiveEffect^ __clrcall FindFirstEffectWithArchetype(Archetypes archetype, bool allowInactive) sealed
            {
                auto self = this->As<MagicTarget^>();
                auto ptr = Memory::InvokeCdecl(MCH::FromBase(GameAddress::MagicTarget_FindFirstEffectWithArchetype), self->Address, (int)archetype, allowInactive ? 1 : 0);
                return MemoryObject::FromAddress<ActiveEffect^>(ptr);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.GetActorValue"/>.
            /// </summary>
            virtual System::Single __clrcall GetActorValue(ActorValueIndices id) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                return (float)self->InvokeVTableThisCallF(0, 0x8, (int)id);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.GetActorValueMax"/>.
            /// </summary>
            virtual System::Single __clrcall GetActorValueMax(ActorValueIndices id) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                return (float)self->InvokeVTableThisCallF(0, 0x10, (int)id);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.GetBaseActorValue"/>.
            /// </summary>
            virtual System::Single __clrcall GetBaseActorValue(ActorValueIndices id) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                return (float)self->InvokeVTableThisCallF(0, 0x18, (int)id);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.DamageActorValue"/>.
            /// </summary>
            virtual void __clrcall DamageActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                if(id == ActorValueIndices::Health)
                {
                    auto actor = this->As<Actor^>();
                    if(actor != nullptr)
                    {
                        auto resultPtr = actor->InvokeVTableThisCall(0, 0x2F0);
                        if((MCH::u(resultPtr) & 0xFF) != 0)
                        {
                            actor->InvokeVTableThisCall(0, 0x820, 0, amount);
                            return;
                        }
                    }
                }
                self->InvokeVTableThisCall(0, 0x30, 2, (int)id, amount);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.RestoreActorValue"/>.
            /// </summary>
            virtual void __clrcall RestoreActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto actor = this->As<Actor^>();
                if(actor == nullptr) return;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::ActorValueOwner_RestoreActorValue), actor->Address, (int)id, amount);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.ForceActorValue"/>.
            /// </summary>
            virtual void __clrcall ForceActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                amount -= self->GetActorValue(id);
                self->InvokeVTableThisCall(0, 0x30, 0, (int)id, amount);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.ModActorValue"/>.
            /// </summary>
            virtual void __clrcall ModActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                self->InvokeVTableThisCall(0, 0x30, 0, (int)id, amount);
            }
            
            /// <summary>
            /// Implementation of method <see cref="ActorValueOwner.SetActorValue"/>.
            /// </summary>
            virtual void __clrcall SetActorValue(ActorValueIndices id, System::Single amount) sealed
            {
                auto self = this->As<ActorValueOwner^>();
                self->InvokeVTableThisCall(0, 0x38, (int)id, amount);
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.IncRef"/>.
            /// </summary>
            virtual void __clrcall IncRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                Memory::InterlockedIncrement32(self->Address + 0x8, false);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.DecRef"/>.
            /// </summary>
            virtual bool __clrcall DecRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                auto result = Memory::InterlockedDecrement32(self->Address + 0x8, false);
                if(this->Is<BSHandleRefObject^>()) result = result & 0x3FF;
                if(result == 0)
                {
                    self->InvokeVTableThisCall(0, 0x8);
                    return true;
                }
                return false;
            }
            
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESObjectWEAP"/>.
        /// </summary>
        private ref class impl_TESObjectWEAP sealed : public VirtualObject, public TESObjectWEAP
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESFullName.Text"/>.
            /// </summary>
            virtual property BSFixedString^ Text
            {
                BSFixedString^ __clrcall get() sealed
                {
                    auto self = this->As<TESFullName^>();
                    return MemoryObject::FromAddress<BSFixedString^>(self->Address + 0x8);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESWeightForm.Value"/>.
            /// </summary>
            virtual property System::Single Value
            {
                System::Single __clrcall get() sealed
                {
                    auto self = this->As<TESWeightForm^>();
                    return Memory::ReadFloat(self->Address + 0x8, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    auto self = this->As<TESWeightForm^>();
                    Memory::WriteFloat(self->Address + 0x8, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
            
            /// <summary>
            /// Implementation of method <see cref="TESObjectWEAP.Fire"/>.
            /// </summary>
            virtual void __clrcall Fire(TESObjectREFR^ source, TESAmmo^ ammo, MagicItem^ enchant, MagicItem^ poison) sealed
            {
                auto self = this;
                MCH::e<TESObjectREFR^>(source, nullptr);
                MCH::e<TESAmmo^>(ammo, nullptr);
                MCH::e<MagicItem^>(enchant, nullptr);
                MCH::e<MagicItem^>(poison, nullptr);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESObjectWEAP_Fire), self->Address, source != nullptr ? source->Address : System::IntPtr::Zero, ammo != nullptr ? ammo->Address : System::IntPtr::Zero, enchant != nullptr ? enchant->Address : System::IntPtr::Zero, poison != nullptr ? poison->Address : System::IntPtr::Zero);
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="NiAVObject"/>.
        /// </summary>
        private ref class impl_NiAVObject sealed : public VirtualObject, public NiAVObject
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="NiObjectNET.Name"/>.
            /// </summary>
            virtual property BSFixedString^ Name
            {
                BSFixedString^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<BSFixedString^>(this->Address + 0x10);
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name->Text;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\"";
                return name;
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiObject.Clone"/>.
            /// </summary>
            virtual NiObject^ __clrcall Clone() sealed
            {
                auto self = this;
                System::IntPtr result = System::IntPtr::Zero;
                stack100 alloc;
                alloc.set(0x18, MCH::FromBase(GameAddress::gUnkCloneValue1));
                alloc.set(0x48, MCH::FromBase(GameAddress::gUnkCloneValue2));
                alloc.set(0x60, Memory::ReadInt32(MCH::FromBase(GameAddress::gUnkCloneValue3), false));
                alloc.set(0x64, Memory::ReadUInt8(MCH::FromBase(GameAddress::gUnkCloneValue4), false));
                alloc.set(0x68, 1.0f);
                alloc.set(0x6C, 1.0f);
                alloc.set(0x70, 1.0f);
                result = Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_1), self->Address, alloc.ptr());
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_2), alloc.ptr() + 0x38);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_3), alloc.ptr() + 0x8);
                return MemoryObject::FromAddressSafeCast<NiObject^>(result);
            }
            
            
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.IncRef"/>.
            /// </summary>
            virtual void __clrcall IncRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                Memory::InterlockedIncrement32(self->Address + 0x8, false);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.DecRef"/>.
            /// </summary>
            virtual bool __clrcall DecRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                auto result = Memory::InterlockedDecrement32(self->Address + 0x8, false);
                if(this->Is<BSHandleRefObject^>()) result = result & 0x3FF;
                if(result == 0)
                {
                    self->InvokeVTableThisCall(0, 0x8);
                    return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiAVObject.Parent"/>.
            /// </summary>
            virtual property NiNode^ Parent
            {
                NiNode^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiNode^>(Memory::ReadPointer(this->Address + 0x30, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiAVObject.Index"/>.
            /// </summary>
            virtual property System::Int32 Index
            {
                System::Int32 __clrcall get() sealed
                {
                    return Memory::ReadInt32(this->Address + 0x38, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiAVObject.LocalTransform"/>.
            /// </summary>
            virtual property NiTransform^ LocalTransform
            {
                NiTransform^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiTransform^>(this->Address + 0x48);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiAVObject.WorldTransform"/>.
            /// </summary>
            virtual property NiTransform^ WorldTransform
            {
                NiTransform^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiTransform^>(this->Address + 0x7C);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiAVObject.FrameTransform"/>.
            /// </summary>
            virtual property NiTransform^ FrameTransform
            {
                NiTransform^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiTransform^>(this->Address + 0xB0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiAVObject.Collidable"/>.
            /// </summary>
            virtual property NiCollisionObject^ Collidable
            {
                NiCollisionObject^ __clrcall get() sealed
                {
                    auto self = this;
                    auto ptr = Memory::ReadPointer(self->Address + 0x40, false);
                    return MemoryObject::FromAddress<NiCollisionObject^>(ptr);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiAVObject.OwnerObject"/>.
            /// </summary>
            virtual property TESObjectREFR^ OwnerObject
            {
                TESObjectREFR^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESObjectREFR^>(Memory::ReadPointer(this->Address + 0xF8, false));
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiAVObject.Update"/>.
            /// </summary>
            virtual void __clrcall Update(System::Single time) sealed
            {
                auto self = this;
                stack10 alloc;
                if(time > 0.0f)
                {
                    alloc.set<float>(0, time);
                    alloc.set<int>(4, 1);
                }
                if(this->Collidable != nullptr)
                {
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiAVObject_Update_Collidable), self->Address, 1);
                }
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiAVObject_Update), self->Address, alloc.ptr());
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiAVObject.Detach"/>.
            /// </summary>
            virtual void __clrcall Detach() sealed
            {
                auto parent = Parent;
                if(parent != nullptr)
                {
                    stack10 alloc;
                    parent->InvokeVTableThisCall(0, 0x1C0, this->Address, alloc.ptr());
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiAVObject.UpdateEx"/>.
            /// </summary>
            virtual void __clrcall UpdateEx(System::Single time, System::UInt32 flags) sealed
            {
                auto self = this;
                stack10 alloc;
                alloc.set<float>(0, time);
                alloc.set<int>(4, (int)flags);
                if(this->Collidable != nullptr)
                {
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiAVObject_Update_Collidable), self->Address, 1);
                }
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiAVObject_Update), self->Address, alloc.ptr());
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="NiNode"/>.
        /// </summary>
        private ref class impl_NiNode sealed : public VirtualObject, public NiNode
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="NiAVObject.Parent"/>.
            /// </summary>
            virtual property NiNode^ Parent
            {
                NiNode^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiNode^>(Memory::ReadPointer(this->Address + 0x30, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiAVObject.Index"/>.
            /// </summary>
            virtual property System::Int32 Index
            {
                System::Int32 __clrcall get() sealed
                {
                    return Memory::ReadInt32(this->Address + 0x38, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiAVObject.LocalTransform"/>.
            /// </summary>
            virtual property NiTransform^ LocalTransform
            {
                NiTransform^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiTransform^>(this->Address + 0x48);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiAVObject.WorldTransform"/>.
            /// </summary>
            virtual property NiTransform^ WorldTransform
            {
                NiTransform^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiTransform^>(this->Address + 0x7C);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiAVObject.FrameTransform"/>.
            /// </summary>
            virtual property NiTransform^ FrameTransform
            {
                NiTransform^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiTransform^>(this->Address + 0xB0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiAVObject.Collidable"/>.
            /// </summary>
            virtual property NiCollisionObject^ Collidable
            {
                NiCollisionObject^ __clrcall get() sealed
                {
                    auto self = this;
                    auto ptr = Memory::ReadPointer(self->Address + 0x40, false);
                    return MemoryObject::FromAddress<NiCollisionObject^>(ptr);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiAVObject.OwnerObject"/>.
            /// </summary>
            virtual property TESObjectREFR^ OwnerObject
            {
                TESObjectREFR^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESObjectREFR^>(Memory::ReadPointer(this->Address + 0xF8, false));
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiAVObject.Update"/>.
            /// </summary>
            virtual void __clrcall Update(System::Single time) sealed
            {
                auto self = this;
                stack10 alloc;
                if(time > 0.0f)
                {
                    alloc.set<float>(0, time);
                    alloc.set<int>(4, 1);
                }
                if(this->Collidable != nullptr)
                {
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiAVObject_Update_Collidable), self->Address, 1);
                }
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiAVObject_Update), self->Address, alloc.ptr());
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiAVObject.Detach"/>.
            /// </summary>
            virtual void __clrcall Detach() sealed
            {
                auto parent = Parent;
                if(parent != nullptr)
                {
                    stack10 alloc;
                    parent->InvokeVTableThisCall(0, 0x1C0, this->Address, alloc.ptr());
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiAVObject.UpdateEx"/>.
            /// </summary>
            virtual void __clrcall UpdateEx(System::Single time, System::UInt32 flags) sealed
            {
                auto self = this;
                stack10 alloc;
                alloc.set<float>(0, time);
                alloc.set<int>(4, (int)flags);
                if(this->Collidable != nullptr)
                {
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiAVObject_Update_Collidable), self->Address, 1);
                }
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiAVObject_Update), self->Address, alloc.ptr());
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiObjectNET.Name"/>.
            /// </summary>
            virtual property BSFixedString^ Name
            {
                BSFixedString^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<BSFixedString^>(this->Address + 0x10);
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name->Text;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\"";
                return name;
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiObject.Clone"/>.
            /// </summary>
            virtual NiObject^ __clrcall Clone() sealed
            {
                auto self = this;
                System::IntPtr result = System::IntPtr::Zero;
                stack100 alloc;
                alloc.set(0x18, MCH::FromBase(GameAddress::gUnkCloneValue1));
                alloc.set(0x48, MCH::FromBase(GameAddress::gUnkCloneValue2));
                alloc.set(0x60, Memory::ReadInt32(MCH::FromBase(GameAddress::gUnkCloneValue3), false));
                alloc.set(0x64, Memory::ReadUInt8(MCH::FromBase(GameAddress::gUnkCloneValue4), false));
                alloc.set(0x68, 1.0f);
                alloc.set(0x6C, 1.0f);
                alloc.set(0x70, 1.0f);
                result = Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_1), self->Address, alloc.ptr());
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_2), alloc.ptr() + 0x38);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_3), alloc.ptr() + 0x8);
                return MemoryObject::FromAddressSafeCast<NiObject^>(result);
            }
            
            
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.IncRef"/>.
            /// </summary>
            virtual void __clrcall IncRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                Memory::InterlockedIncrement32(self->Address + 0x8, false);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.DecRef"/>.
            /// </summary>
            virtual bool __clrcall DecRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                auto result = Memory::InterlockedDecrement32(self->Address + 0x8, false);
                if(this->Is<BSHandleRefObject^>()) result = result & 0x3FF;
                if(result == 0)
                {
                    self->InvokeVTableThisCall(0, 0x8);
                    return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiNode.Children"/>.
            /// </summary>
            virtual property NiTObjectArray<NiAVObject^>^ Children
            {
                NiTObjectArray<NiAVObject^>^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiTObjectArray<NiAVObject^>^>(this->Address + 0x110);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiNode.LookupNodeByName"/>.
            /// </summary>
            virtual NiNode^ __clrcall LookupNodeByName(System::String^ name) sealed
            {
                auto self = this;
                StringRefHolder^ str = gcnew StringRefHolder(name);
                try
                {
                    return MemoryObject::FromAddress<NiNode^>(self->InvokeVTableThisCall(0, 0x150, str->AddressOf, 1));
                }
                finally
                {
                    delete str;
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiNode.AttachObject"/>.
            /// </summary>
            virtual void __clrcall AttachObject(NiAVObject^ obj) sealed
            {
                auto self = this;
                MCH::e<NiAVObject^>(obj, "obj");
                self->InvokeVTableThisCall(0, 0x1A8, obj->Address, 0);
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="NiCollisionObject"/>.
        /// </summary>
        private ref class impl_NiCollisionObject sealed : public VirtualObject, public NiCollisionObject
        {
        public:
            /// <summary>
            /// Implementation of method <see cref="NiObject.Clone"/>.
            /// </summary>
            virtual NiObject^ __clrcall Clone() sealed
            {
                auto self = this;
                System::IntPtr result = System::IntPtr::Zero;
                stack100 alloc;
                alloc.set(0x18, MCH::FromBase(GameAddress::gUnkCloneValue1));
                alloc.set(0x48, MCH::FromBase(GameAddress::gUnkCloneValue2));
                alloc.set(0x60, Memory::ReadInt32(MCH::FromBase(GameAddress::gUnkCloneValue3), false));
                alloc.set(0x64, Memory::ReadUInt8(MCH::FromBase(GameAddress::gUnkCloneValue4), false));
                alloc.set(0x68, 1.0f);
                alloc.set(0x6C, 1.0f);
                alloc.set(0x70, 1.0f);
                result = Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_1), self->Address, alloc.ptr());
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_2), alloc.ptr() + 0x38);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_3), alloc.ptr() + 0x8);
                return MemoryObject::FromAddressSafeCast<NiObject^>(result);
            }
            
            
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.IncRef"/>.
            /// </summary>
            virtual void __clrcall IncRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                Memory::InterlockedIncrement32(self->Address + 0x8, false);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.DecRef"/>.
            /// </summary>
            virtual bool __clrcall DecRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                auto result = Memory::InterlockedDecrement32(self->Address + 0x8, false);
                if(this->Is<BSHandleRefObject^>()) result = result & 0x3FF;
                if(result == 0)
                {
                    self->InvokeVTableThisCall(0, 0x8);
                    return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiCollisionObject.OwnerObject"/>.
            /// </summary>
            virtual property NiAVObject^ OwnerObject
            {
                NiAVObject^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiAVObject^>(Memory::ReadPointer(this->Address + 0x10, false));
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="bhkNiCollisionObject"/>.
        /// </summary>
        private ref class impl_bhkNiCollisionObject sealed : public VirtualObject, public bhkNiCollisionObject
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="NiCollisionObject.OwnerObject"/>.
            /// </summary>
            virtual property NiAVObject^ OwnerObject
            {
                NiAVObject^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiAVObject^>(Memory::ReadPointer(this->Address + 0x10, false));
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiObject.Clone"/>.
            /// </summary>
            virtual NiObject^ __clrcall Clone() sealed
            {
                auto self = this;
                System::IntPtr result = System::IntPtr::Zero;
                stack100 alloc;
                alloc.set(0x18, MCH::FromBase(GameAddress::gUnkCloneValue1));
                alloc.set(0x48, MCH::FromBase(GameAddress::gUnkCloneValue2));
                alloc.set(0x60, Memory::ReadInt32(MCH::FromBase(GameAddress::gUnkCloneValue3), false));
                alloc.set(0x64, Memory::ReadUInt8(MCH::FromBase(GameAddress::gUnkCloneValue4), false));
                alloc.set(0x68, 1.0f);
                alloc.set(0x6C, 1.0f);
                alloc.set(0x70, 1.0f);
                result = Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_1), self->Address, alloc.ptr());
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_2), alloc.ptr() + 0x38);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_3), alloc.ptr() + 0x8);
                return MemoryObject::FromAddressSafeCast<NiObject^>(result);
            }
            
            
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.IncRef"/>.
            /// </summary>
            virtual void __clrcall IncRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                Memory::InterlockedIncrement32(self->Address + 0x8, false);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.DecRef"/>.
            /// </summary>
            virtual bool __clrcall DecRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                auto result = Memory::InterlockedDecrement32(self->Address + 0x8, false);
                if(this->Is<BSHandleRefObject^>()) result = result & 0x3FF;
                if(result == 0)
                {
                    self->InvokeVTableThisCall(0, 0x8);
                    return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="bhkNiCollisionObject.WorldObject"/>.
            /// </summary>
            virtual property bhkWorldObject^ WorldObject
            {
                bhkWorldObject^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<bhkWorldObject^>(Memory::ReadPointer(this->Address + 0x20, false));
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="NiLight"/>.
        /// </summary>
        private ref class impl_NiLight sealed : public VirtualObject, public NiLight
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="NiAVObject.Parent"/>.
            /// </summary>
            virtual property NiNode^ Parent
            {
                NiNode^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiNode^>(Memory::ReadPointer(this->Address + 0x30, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiAVObject.Index"/>.
            /// </summary>
            virtual property System::Int32 Index
            {
                System::Int32 __clrcall get() sealed
                {
                    return Memory::ReadInt32(this->Address + 0x38, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiAVObject.LocalTransform"/>.
            /// </summary>
            virtual property NiTransform^ LocalTransform
            {
                NiTransform^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiTransform^>(this->Address + 0x48);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiAVObject.WorldTransform"/>.
            /// </summary>
            virtual property NiTransform^ WorldTransform
            {
                NiTransform^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiTransform^>(this->Address + 0x7C);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiAVObject.FrameTransform"/>.
            /// </summary>
            virtual property NiTransform^ FrameTransform
            {
                NiTransform^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiTransform^>(this->Address + 0xB0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiAVObject.Collidable"/>.
            /// </summary>
            virtual property NiCollisionObject^ Collidable
            {
                NiCollisionObject^ __clrcall get() sealed
                {
                    auto self = this;
                    auto ptr = Memory::ReadPointer(self->Address + 0x40, false);
                    return MemoryObject::FromAddress<NiCollisionObject^>(ptr);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiAVObject.OwnerObject"/>.
            /// </summary>
            virtual property TESObjectREFR^ OwnerObject
            {
                TESObjectREFR^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESObjectREFR^>(Memory::ReadPointer(this->Address + 0xF8, false));
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiAVObject.Update"/>.
            /// </summary>
            virtual void __clrcall Update(System::Single time) sealed
            {
                auto self = this;
                stack10 alloc;
                if(time > 0.0f)
                {
                    alloc.set<float>(0, time);
                    alloc.set<int>(4, 1);
                }
                if(this->Collidable != nullptr)
                {
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiAVObject_Update_Collidable), self->Address, 1);
                }
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiAVObject_Update), self->Address, alloc.ptr());
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiAVObject.Detach"/>.
            /// </summary>
            virtual void __clrcall Detach() sealed
            {
                auto parent = Parent;
                if(parent != nullptr)
                {
                    stack10 alloc;
                    parent->InvokeVTableThisCall(0, 0x1C0, this->Address, alloc.ptr());
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiAVObject.UpdateEx"/>.
            /// </summary>
            virtual void __clrcall UpdateEx(System::Single time, System::UInt32 flags) sealed
            {
                auto self = this;
                stack10 alloc;
                alloc.set<float>(0, time);
                alloc.set<int>(4, (int)flags);
                if(this->Collidable != nullptr)
                {
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiAVObject_Update_Collidable), self->Address, 1);
                }
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiAVObject_Update), self->Address, alloc.ptr());
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiObjectNET.Name"/>.
            /// </summary>
            virtual property BSFixedString^ Name
            {
                BSFixedString^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<BSFixedString^>(this->Address + 0x10);
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name->Text;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\"";
                return name;
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiObject.Clone"/>.
            /// </summary>
            virtual NiObject^ __clrcall Clone() sealed
            {
                auto self = this;
                System::IntPtr result = System::IntPtr::Zero;
                stack100 alloc;
                alloc.set(0x18, MCH::FromBase(GameAddress::gUnkCloneValue1));
                alloc.set(0x48, MCH::FromBase(GameAddress::gUnkCloneValue2));
                alloc.set(0x60, Memory::ReadInt32(MCH::FromBase(GameAddress::gUnkCloneValue3), false));
                alloc.set(0x64, Memory::ReadUInt8(MCH::FromBase(GameAddress::gUnkCloneValue4), false));
                alloc.set(0x68, 1.0f);
                alloc.set(0x6C, 1.0f);
                alloc.set(0x70, 1.0f);
                result = Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_1), self->Address, alloc.ptr());
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_2), alloc.ptr() + 0x38);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_3), alloc.ptr() + 0x8);
                return MemoryObject::FromAddressSafeCast<NiObject^>(result);
            }
            
            
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.IncRef"/>.
            /// </summary>
            virtual void __clrcall IncRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                Memory::InterlockedIncrement32(self->Address + 0x8, false);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.DecRef"/>.
            /// </summary>
            virtual bool __clrcall DecRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                auto result = Memory::InterlockedDecrement32(self->Address + 0x8, false);
                if(this->Is<BSHandleRefObject^>()) result = result & 0x3FF;
                if(result == 0)
                {
                    self->InvokeVTableThisCall(0, 0x8);
                    return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiLight.Color"/>.
            /// </summary>
            virtual property NiPoint3^ Color
            {
                NiPoint3^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPoint3^>(this->Address + 0x11C);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiLight.Radius"/>.
            /// </summary>
            virtual property NiPoint3^ Radius
            {
                NiPoint3^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPoint3^>(this->Address + 0x128);
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BSGeometry"/>.
        /// </summary>
        private ref class impl_BSGeometry sealed : public VirtualObject, public BSGeometry
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="NiAVObject.Parent"/>.
            /// </summary>
            virtual property NiNode^ Parent
            {
                NiNode^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiNode^>(Memory::ReadPointer(this->Address + 0x30, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiAVObject.Index"/>.
            /// </summary>
            virtual property System::Int32 Index
            {
                System::Int32 __clrcall get() sealed
                {
                    return Memory::ReadInt32(this->Address + 0x38, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiAVObject.LocalTransform"/>.
            /// </summary>
            virtual property NiTransform^ LocalTransform
            {
                NiTransform^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiTransform^>(this->Address + 0x48);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiAVObject.WorldTransform"/>.
            /// </summary>
            virtual property NiTransform^ WorldTransform
            {
                NiTransform^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiTransform^>(this->Address + 0x7C);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiAVObject.FrameTransform"/>.
            /// </summary>
            virtual property NiTransform^ FrameTransform
            {
                NiTransform^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiTransform^>(this->Address + 0xB0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiAVObject.Collidable"/>.
            /// </summary>
            virtual property NiCollisionObject^ Collidable
            {
                NiCollisionObject^ __clrcall get() sealed
                {
                    auto self = this;
                    auto ptr = Memory::ReadPointer(self->Address + 0x40, false);
                    return MemoryObject::FromAddress<NiCollisionObject^>(ptr);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiAVObject.OwnerObject"/>.
            /// </summary>
            virtual property TESObjectREFR^ OwnerObject
            {
                TESObjectREFR^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESObjectREFR^>(Memory::ReadPointer(this->Address + 0xF8, false));
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiAVObject.Update"/>.
            /// </summary>
            virtual void __clrcall Update(System::Single time) sealed
            {
                auto self = this;
                stack10 alloc;
                if(time > 0.0f)
                {
                    alloc.set<float>(0, time);
                    alloc.set<int>(4, 1);
                }
                if(this->Collidable != nullptr)
                {
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiAVObject_Update_Collidable), self->Address, 1);
                }
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiAVObject_Update), self->Address, alloc.ptr());
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiAVObject.Detach"/>.
            /// </summary>
            virtual void __clrcall Detach() sealed
            {
                auto parent = Parent;
                if(parent != nullptr)
                {
                    stack10 alloc;
                    parent->InvokeVTableThisCall(0, 0x1C0, this->Address, alloc.ptr());
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiAVObject.UpdateEx"/>.
            /// </summary>
            virtual void __clrcall UpdateEx(System::Single time, System::UInt32 flags) sealed
            {
                auto self = this;
                stack10 alloc;
                alloc.set<float>(0, time);
                alloc.set<int>(4, (int)flags);
                if(this->Collidable != nullptr)
                {
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiAVObject_Update_Collidable), self->Address, 1);
                }
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiAVObject_Update), self->Address, alloc.ptr());
            }
            
            /// <summary>
            /// Implementation of property <see cref="NiObjectNET.Name"/>.
            /// </summary>
            virtual property BSFixedString^ Name
            {
                BSFixedString^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<BSFixedString^>(this->Address + 0x10);
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name->Text;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\"";
                return name;
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiObject.Clone"/>.
            /// </summary>
            virtual NiObject^ __clrcall Clone() sealed
            {
                auto self = this;
                System::IntPtr result = System::IntPtr::Zero;
                stack100 alloc;
                alloc.set(0x18, MCH::FromBase(GameAddress::gUnkCloneValue1));
                alloc.set(0x48, MCH::FromBase(GameAddress::gUnkCloneValue2));
                alloc.set(0x60, Memory::ReadInt32(MCH::FromBase(GameAddress::gUnkCloneValue3), false));
                alloc.set(0x64, Memory::ReadUInt8(MCH::FromBase(GameAddress::gUnkCloneValue4), false));
                alloc.set(0x68, 1.0f);
                alloc.set(0x6C, 1.0f);
                alloc.set(0x70, 1.0f);
                result = Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_1), self->Address, alloc.ptr());
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_2), alloc.ptr() + 0x38);
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::NiObject_Clone_3), alloc.ptr() + 0x8);
                return MemoryObject::FromAddressSafeCast<NiObject^>(result);
            }
            
            
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.IncRef"/>.
            /// </summary>
            virtual void __clrcall IncRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                Memory::InterlockedIncrement32(self->Address + 0x8, false);
            }
            
            /// <summary>
            /// Implementation of method <see cref="NiRefObject.DecRef"/>.
            /// </summary>
            virtual bool __clrcall DecRef() sealed
            {
                auto self = this->As<NiRefObject^>();
                auto result = Memory::InterlockedDecrement32(self->Address + 0x8, false);
                if(this->Is<BSHandleRefObject^>()) result = result & 0x3FF;
                if(result == 0)
                {
                    self->InvokeVTableThisCall(0, 0x8);
                    return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="BSGeometry.Skin"/>.
            /// </summary>
            virtual property NiSkinInstance^ Skin
            {
                NiSkinInstance^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiSkinInstance^>(this->Address + 0x130);
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESCameraState"/>.
        /// </summary>
        private ref class impl_TESCameraState sealed : public VirtualObject, public TESCameraState
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESCameraState.Camera"/>.
            /// </summary>
            virtual property TESCamera^ Camera
            {
                TESCamera^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESCamera^>(Memory::ReadPointer(this->Address + 0x10, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESCameraState.Id"/>.
            /// </summary>
            virtual property TESCameraStates Id
            {
                TESCameraStates __clrcall get() sealed
                {
                    return (TESCameraStates)Memory::ReadInt32(this->Address + 0x18, false);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESCameraState.GetCurrentPosition"/>.
            /// </summary>
            virtual void __clrcall GetCurrentPosition(NiPoint3^ result) sealed
            {
                auto self = this;
                if(result == nullptr) throw gcnew System::ArgumentNullException("result");
                stack10 alloc;
                self->InvokeVTableThisCall(0, 0x28, alloc.ptr());
                result->X = alloc.get<float>(0);
                result->Y = alloc.get<float>(4);
                result->Z = alloc.get<float>(8);
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESCamera"/>.
        /// </summary>
        private ref class impl_TESCamera sealed : public VirtualObject, public TESCamera
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESCamera.Node"/>.
            /// </summary>
            virtual property NiNode^ Node
            {
                NiNode^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiNode^>(Memory::ReadPointer(this->Address + 0x20, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESCamera.State"/>.
            /// </summary>
            virtual property TESCameraState^ State
            {
                TESCameraState^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESCameraState^>(Memory::ReadPointer(this->Address + 0x28, false));
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="FirstPersonState"/>.
        /// </summary>
        private ref class impl_FirstPersonState sealed : public VirtualObject, public FirstPersonState
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESCameraState.Camera"/>.
            /// </summary>
            virtual property TESCamera^ Camera
            {
                TESCamera^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESCamera^>(Memory::ReadPointer(this->Address + 0x10, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESCameraState.Id"/>.
            /// </summary>
            virtual property TESCameraStates Id
            {
                TESCameraStates __clrcall get() sealed
                {
                    return (TESCameraStates)Memory::ReadInt32(this->Address + 0x18, false);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESCameraState.GetCurrentPosition"/>.
            /// </summary>
            virtual void __clrcall GetCurrentPosition(NiPoint3^ result) sealed
            {
                auto self = this;
                if(result == nullptr) throw gcnew System::ArgumentNullException("result");
                stack10 alloc;
                self->InvokeVTableThisCall(0, 0x28, alloc.ptr());
                result->X = alloc.get<float>(0);
                result->Y = alloc.get<float>(4);
                result->Z = alloc.get<float>(8);
            }
            
            /// <summary>
            /// Implementation of property <see cref="FirstPersonState.ControlNode"/>.
            /// </summary>
            virtual property NiNode^ ControlNode
            {
                NiNode^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiNode^>(Memory::ReadPointer(this->Address + 0x60, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="FirstPersonState.AttachedNode"/>.
            /// </summary>
            virtual property NiNode^ AttachedNode
            {
                NiNode^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiNode^>(Memory::ReadPointer(this->Address + 0x58, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="FirstPersonState.PlayerPosition"/>.
            /// </summary>
            virtual property NiPoint3^ PlayerPosition
            {
                NiPoint3^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPoint3^>(this->Address + 0x30);
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="ThirdPersonState"/>.
        /// </summary>
        private ref class impl_ThirdPersonState sealed : public VirtualObject, public ThirdPersonState
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESCameraState.Camera"/>.
            /// </summary>
            virtual property TESCamera^ Camera
            {
                TESCamera^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESCamera^>(Memory::ReadPointer(this->Address + 0x10, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESCameraState.Id"/>.
            /// </summary>
            virtual property TESCameraStates Id
            {
                TESCameraStates __clrcall get() sealed
                {
                    return (TESCameraStates)Memory::ReadInt32(this->Address + 0x18, false);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESCameraState.GetCurrentPosition"/>.
            /// </summary>
            virtual void __clrcall GetCurrentPosition(NiPoint3^ result) sealed
            {
                auto self = this;
                if(result == nullptr) throw gcnew System::ArgumentNullException("result");
                stack10 alloc;
                self->InvokeVTableThisCall(0, 0x28, alloc.ptr());
                result->X = alloc.get<float>(0);
                result->Y = alloc.get<float>(4);
                result->Z = alloc.get<float>(8);
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.Position"/>.
            /// </summary>
            virtual property NiPoint3^ Position
            {
                NiPoint3^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPoint3^>(this->Address + 0x40);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.OverShoulderOffset"/>.
            /// </summary>
            virtual property NiPoint3^ OverShoulderOffset
            {
                NiPoint3^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPoint3^>(this->Address + 0x5C);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.Node"/>.
            /// </summary>
            virtual property NiNode^ Node
            {
                NiNode^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiNode^>(Memory::ReadPointer(this->Address + 0x30, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.TargetNode"/>.
            /// </summary>
            virtual property NiPointer<NiNode^>^ TargetNode
            {
                NiPointer<NiNode^>^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPointer<NiNode^>^>(this->Address + 0xA0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.TargetNodeName"/>.
            /// </summary>
            virtual property BSFixedString^ TargetNodeName
            {
                BSFixedString^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<BSFixedString^>(this->Address + 0xA8);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.ControlNode"/>.
            /// </summary>
            virtual property NiNode^ ControlNode
            {
                NiNode^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiNode^>(Memory::ReadPointer(this->Address + 0x38, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.XRotationFromLastResetPoint"/>.
            /// </summary>
            virtual property System::Single XRotationFromLastResetPoint
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0xD4, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    Memory::WriteFloat(this->Address + 0xD4, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.YRotationFromLastResetPoint"/>.
            /// </summary>
            virtual property System::Single YRotationFromLastResetPoint
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0xD8, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    Memory::WriteFloat(this->Address + 0xD8, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.TargetZoomLevel"/>.
            /// </summary>
            virtual property System::Single TargetZoomLevel
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0x74, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    Memory::WriteFloat(this->Address + 0x74, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.CurrentZoomLevel"/>.
            /// </summary>
            virtual property System::Single CurrentZoomLevel
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0x78, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    Memory::WriteFloat(this->Address + 0x78, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.LastCollisionPoint"/>.
            /// </summary>
            virtual property NiPoint3^ LastCollisionPoint
            {
                NiPoint3^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPoint3^>(this->Address + 0x90);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.IsFreeLookMode"/>.
            /// </summary>
            virtual property bool IsFreeLookMode
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return MCH::b(self->InvokeVTableThisCall(0, 0x60));
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="AutoVanityState"/>.
        /// </summary>
        private ref class impl_AutoVanityState sealed : public VirtualObject, public AutoVanityState
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESCameraState.Camera"/>.
            /// </summary>
            virtual property TESCamera^ Camera
            {
                TESCamera^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESCamera^>(Memory::ReadPointer(this->Address + 0x10, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESCameraState.Id"/>.
            /// </summary>
            virtual property TESCameraStates Id
            {
                TESCameraStates __clrcall get() sealed
                {
                    return (TESCameraStates)Memory::ReadInt32(this->Address + 0x18, false);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESCameraState.GetCurrentPosition"/>.
            /// </summary>
            virtual void __clrcall GetCurrentPosition(NiPoint3^ result) sealed
            {
                auto self = this;
                if(result == nullptr) throw gcnew System::ArgumentNullException("result");
                stack10 alloc;
                self->InvokeVTableThisCall(0, 0x28, alloc.ptr());
                result->X = alloc.get<float>(0);
                result->Y = alloc.get<float>(4);
                result->Z = alloc.get<float>(8);
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="VATSCameraState"/>.
        /// </summary>
        private ref class impl_VATSCameraState sealed : public VirtualObject, public VATSCameraState
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESCameraState.Camera"/>.
            /// </summary>
            virtual property TESCamera^ Camera
            {
                TESCamera^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESCamera^>(Memory::ReadPointer(this->Address + 0x10, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESCameraState.Id"/>.
            /// </summary>
            virtual property TESCameraStates Id
            {
                TESCameraStates __clrcall get() sealed
                {
                    return (TESCameraStates)Memory::ReadInt32(this->Address + 0x18, false);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESCameraState.GetCurrentPosition"/>.
            /// </summary>
            virtual void __clrcall GetCurrentPosition(NiPoint3^ result) sealed
            {
                auto self = this;
                if(result == nullptr) throw gcnew System::ArgumentNullException("result");
                stack10 alloc;
                self->InvokeVTableThisCall(0, 0x28, alloc.ptr());
                result->X = alloc.get<float>(0);
                result->Y = alloc.get<float>(4);
                result->Z = alloc.get<float>(8);
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="FreeCameraState"/>.
        /// </summary>
        private ref class impl_FreeCameraState sealed : public VirtualObject, public FreeCameraState
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESCameraState.Camera"/>.
            /// </summary>
            virtual property TESCamera^ Camera
            {
                TESCamera^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESCamera^>(Memory::ReadPointer(this->Address + 0x10, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESCameraState.Id"/>.
            /// </summary>
            virtual property TESCameraStates Id
            {
                TESCameraStates __clrcall get() sealed
                {
                    return (TESCameraStates)Memory::ReadInt32(this->Address + 0x18, false);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESCameraState.GetCurrentPosition"/>.
            /// </summary>
            virtual void __clrcall GetCurrentPosition(NiPoint3^ result) sealed
            {
                auto self = this;
                if(result == nullptr) throw gcnew System::ArgumentNullException("result");
                stack10 alloc;
                self->InvokeVTableThisCall(0, 0x28, alloc.ptr());
                result->X = alloc.get<float>(0);
                result->Y = alloc.get<float>(4);
                result->Z = alloc.get<float>(8);
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="IronSightsState"/>.
        /// </summary>
        private ref class impl_IronSightsState sealed : public VirtualObject, public IronSightsState
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESCameraState.Camera"/>.
            /// </summary>
            virtual property TESCamera^ Camera
            {
                TESCamera^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESCamera^>(Memory::ReadPointer(this->Address + 0x10, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESCameraState.Id"/>.
            /// </summary>
            virtual property TESCameraStates Id
            {
                TESCameraStates __clrcall get() sealed
                {
                    return (TESCameraStates)Memory::ReadInt32(this->Address + 0x18, false);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESCameraState.GetCurrentPosition"/>.
            /// </summary>
            virtual void __clrcall GetCurrentPosition(NiPoint3^ result) sealed
            {
                auto self = this;
                if(result == nullptr) throw gcnew System::ArgumentNullException("result");
                stack10 alloc;
                self->InvokeVTableThisCall(0, 0x28, alloc.ptr());
                result->X = alloc.get<float>(0);
                result->Y = alloc.get<float>(4);
                result->Z = alloc.get<float>(8);
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="FurnitureCameraState"/>.
        /// </summary>
        private ref class impl_FurnitureCameraState sealed : public VirtualObject, public FurnitureCameraState
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESCameraState.Camera"/>.
            /// </summary>
            virtual property TESCamera^ Camera
            {
                TESCamera^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESCamera^>(Memory::ReadPointer(this->Address + 0x10, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESCameraState.Id"/>.
            /// </summary>
            virtual property TESCameraStates Id
            {
                TESCameraStates __clrcall get() sealed
                {
                    return (TESCameraStates)Memory::ReadInt32(this->Address + 0x18, false);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESCameraState.GetCurrentPosition"/>.
            /// </summary>
            virtual void __clrcall GetCurrentPosition(NiPoint3^ result) sealed
            {
                auto self = this;
                if(result == nullptr) throw gcnew System::ArgumentNullException("result");
                stack10 alloc;
                self->InvokeVTableThisCall(0, 0x28, alloc.ptr());
                result->X = alloc.get<float>(0);
                result->Y = alloc.get<float>(4);
                result->Z = alloc.get<float>(8);
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="PlayerCameraTransitionState"/>.
        /// </summary>
        private ref class impl_PlayerCameraTransitionState sealed : public VirtualObject, public PlayerCameraTransitionState
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESCameraState.Camera"/>.
            /// </summary>
            virtual property TESCamera^ Camera
            {
                TESCamera^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESCamera^>(Memory::ReadPointer(this->Address + 0x10, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESCameraState.Id"/>.
            /// </summary>
            virtual property TESCameraStates Id
            {
                TESCameraStates __clrcall get() sealed
                {
                    return (TESCameraStates)Memory::ReadInt32(this->Address + 0x18, false);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESCameraState.GetCurrentPosition"/>.
            /// </summary>
            virtual void __clrcall GetCurrentPosition(NiPoint3^ result) sealed
            {
                auto self = this;
                if(result == nullptr) throw gcnew System::ArgumentNullException("result");
                stack10 alloc;
                self->InvokeVTableThisCall(0, 0x28, alloc.ptr());
                result->X = alloc.get<float>(0);
                result->Y = alloc.get<float>(4);
                result->Z = alloc.get<float>(8);
            }
            
            /// <summary>
            /// Implementation of property <see cref="PlayerCameraTransitionState.TransitionFrom"/>.
            /// </summary>
            virtual property TESCameraState^ TransitionFrom
            {
                TESCameraState^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESCameraState^>(Memory::ReadPointer(this->Address + 0x28, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="PlayerCameraTransitionState.TransitionTo"/>.
            /// </summary>
            virtual property TESCameraState^ TransitionTo
            {
                TESCameraState^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESCameraState^>(Memory::ReadPointer(this->Address + 0x30, false));
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TweenMenuCameraState"/>.
        /// </summary>
        private ref class impl_TweenMenuCameraState sealed : public VirtualObject, public TweenMenuCameraState
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESCameraState.Camera"/>.
            /// </summary>
            virtual property TESCamera^ Camera
            {
                TESCamera^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESCamera^>(Memory::ReadPointer(this->Address + 0x10, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESCameraState.Id"/>.
            /// </summary>
            virtual property TESCameraStates Id
            {
                TESCameraStates __clrcall get() sealed
                {
                    return (TESCameraStates)Memory::ReadInt32(this->Address + 0x18, false);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESCameraState.GetCurrentPosition"/>.
            /// </summary>
            virtual void __clrcall GetCurrentPosition(NiPoint3^ result) sealed
            {
                auto self = this;
                if(result == nullptr) throw gcnew System::ArgumentNullException("result");
                stack10 alloc;
                self->InvokeVTableThisCall(0, 0x28, alloc.ptr());
                result->X = alloc.get<float>(0);
                result->Y = alloc.get<float>(4);
                result->Z = alloc.get<float>(8);
            }
            
            /// <summary>
            /// Implementation of property <see cref="TweenMenuCameraState.TargetXTurn"/>.
            /// </summary>
            virtual property System::Single TargetXTurn
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0x40, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    Memory::WriteFloat(this->Address + 0x40, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TweenMenuCameraState.TargetYTurn"/>.
            /// </summary>
            virtual property System::Single TargetYTurn
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0x3C, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    Memory::WriteFloat(this->Address + 0x3C, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TweenMenuCameraState.CurrentYTurn"/>.
            /// </summary>
            virtual property System::Single CurrentYTurn
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0x34, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    Memory::WriteFloat(this->Address + 0x34, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TweenMenuCameraState.CurrentXTurn"/>.
            /// </summary>
            virtual property System::Single CurrentXTurn
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0x38, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    Memory::WriteFloat(this->Address + 0x38, value, false);
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="HorseCameraState"/>.
        /// </summary>
        private ref class impl_HorseCameraState sealed : public VirtualObject, public HorseCameraState
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.Position"/>.
            /// </summary>
            virtual property NiPoint3^ Position
            {
                NiPoint3^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPoint3^>(this->Address + 0x40);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.OverShoulderOffset"/>.
            /// </summary>
            virtual property NiPoint3^ OverShoulderOffset
            {
                NiPoint3^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPoint3^>(this->Address + 0x5C);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.Node"/>.
            /// </summary>
            virtual property NiNode^ Node
            {
                NiNode^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiNode^>(Memory::ReadPointer(this->Address + 0x30, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.TargetNode"/>.
            /// </summary>
            virtual property NiPointer<NiNode^>^ TargetNode
            {
                NiPointer<NiNode^>^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPointer<NiNode^>^>(this->Address + 0xA0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.TargetNodeName"/>.
            /// </summary>
            virtual property BSFixedString^ TargetNodeName
            {
                BSFixedString^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<BSFixedString^>(this->Address + 0xA8);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.ControlNode"/>.
            /// </summary>
            virtual property NiNode^ ControlNode
            {
                NiNode^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiNode^>(Memory::ReadPointer(this->Address + 0x38, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.XRotationFromLastResetPoint"/>.
            /// </summary>
            virtual property System::Single XRotationFromLastResetPoint
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0xD4, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    Memory::WriteFloat(this->Address + 0xD4, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.YRotationFromLastResetPoint"/>.
            /// </summary>
            virtual property System::Single YRotationFromLastResetPoint
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0xD8, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    Memory::WriteFloat(this->Address + 0xD8, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.TargetZoomLevel"/>.
            /// </summary>
            virtual property System::Single TargetZoomLevel
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0x74, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    Memory::WriteFloat(this->Address + 0x74, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.CurrentZoomLevel"/>.
            /// </summary>
            virtual property System::Single CurrentZoomLevel
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0x78, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    Memory::WriteFloat(this->Address + 0x78, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.LastCollisionPoint"/>.
            /// </summary>
            virtual property NiPoint3^ LastCollisionPoint
            {
                NiPoint3^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPoint3^>(this->Address + 0x90);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.IsFreeLookMode"/>.
            /// </summary>
            virtual property bool IsFreeLookMode
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return MCH::b(self->InvokeVTableThisCall(0, 0x60));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESCameraState.Camera"/>.
            /// </summary>
            virtual property TESCamera^ Camera
            {
                TESCamera^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESCamera^>(Memory::ReadPointer(this->Address + 0x10, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESCameraState.Id"/>.
            /// </summary>
            virtual property TESCameraStates Id
            {
                TESCameraStates __clrcall get() sealed
                {
                    return (TESCameraStates)Memory::ReadInt32(this->Address + 0x18, false);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESCameraState.GetCurrentPosition"/>.
            /// </summary>
            virtual void __clrcall GetCurrentPosition(NiPoint3^ result) sealed
            {
                auto self = this;
                if(result == nullptr) throw gcnew System::ArgumentNullException("result");
                stack10 alloc;
                self->InvokeVTableThisCall(0, 0x28, alloc.ptr());
                result->X = alloc.get<float>(0);
                result->Y = alloc.get<float>(4);
                result->Z = alloc.get<float>(8);
            }
            
            /// <summary>
            /// Implementation of property <see cref="HorseCameraState.HorseRefHandle"/>.
            /// </summary>
            virtual property System::UInt32 HorseRefHandle
            {
                System::UInt32 __clrcall get() sealed
                {
                    return Memory::ReadUInt32(this->Address + 0xE8, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="HorseCameraState.HorseCurrentDirection"/>.
            /// </summary>
            virtual property System::Single HorseCurrentDirection
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0xEC, false);
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BleedoutCameraState"/>.
        /// </summary>
        private ref class impl_BleedoutCameraState sealed : public VirtualObject, public BleedoutCameraState
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.Position"/>.
            /// </summary>
            virtual property NiPoint3^ Position
            {
                NiPoint3^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPoint3^>(this->Address + 0x40);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.OverShoulderOffset"/>.
            /// </summary>
            virtual property NiPoint3^ OverShoulderOffset
            {
                NiPoint3^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPoint3^>(this->Address + 0x5C);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.Node"/>.
            /// </summary>
            virtual property NiNode^ Node
            {
                NiNode^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiNode^>(Memory::ReadPointer(this->Address + 0x30, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.TargetNode"/>.
            /// </summary>
            virtual property NiPointer<NiNode^>^ TargetNode
            {
                NiPointer<NiNode^>^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPointer<NiNode^>^>(this->Address + 0xA0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.TargetNodeName"/>.
            /// </summary>
            virtual property BSFixedString^ TargetNodeName
            {
                BSFixedString^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<BSFixedString^>(this->Address + 0xA8);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.ControlNode"/>.
            /// </summary>
            virtual property NiNode^ ControlNode
            {
                NiNode^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiNode^>(Memory::ReadPointer(this->Address + 0x38, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.XRotationFromLastResetPoint"/>.
            /// </summary>
            virtual property System::Single XRotationFromLastResetPoint
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0xD4, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    Memory::WriteFloat(this->Address + 0xD4, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.YRotationFromLastResetPoint"/>.
            /// </summary>
            virtual property System::Single YRotationFromLastResetPoint
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0xD8, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    Memory::WriteFloat(this->Address + 0xD8, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.TargetZoomLevel"/>.
            /// </summary>
            virtual property System::Single TargetZoomLevel
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0x74, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    Memory::WriteFloat(this->Address + 0x74, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.CurrentZoomLevel"/>.
            /// </summary>
            virtual property System::Single CurrentZoomLevel
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0x78, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    Memory::WriteFloat(this->Address + 0x78, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.LastCollisionPoint"/>.
            /// </summary>
            virtual property NiPoint3^ LastCollisionPoint
            {
                NiPoint3^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPoint3^>(this->Address + 0x90);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.IsFreeLookMode"/>.
            /// </summary>
            virtual property bool IsFreeLookMode
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return MCH::b(self->InvokeVTableThisCall(0, 0x60));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESCameraState.Camera"/>.
            /// </summary>
            virtual property TESCamera^ Camera
            {
                TESCamera^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESCamera^>(Memory::ReadPointer(this->Address + 0x10, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESCameraState.Id"/>.
            /// </summary>
            virtual property TESCameraStates Id
            {
                TESCameraStates __clrcall get() sealed
                {
                    return (TESCameraStates)Memory::ReadInt32(this->Address + 0x18, false);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESCameraState.GetCurrentPosition"/>.
            /// </summary>
            virtual void __clrcall GetCurrentPosition(NiPoint3^ result) sealed
            {
                auto self = this;
                if(result == nullptr) throw gcnew System::ArgumentNullException("result");
                stack10 alloc;
                self->InvokeVTableThisCall(0, 0x28, alloc.ptr());
                result->X = alloc.get<float>(0);
                result->Y = alloc.get<float>(4);
                result->Z = alloc.get<float>(8);
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="DragonCameraState"/>.
        /// </summary>
        private ref class impl_DragonCameraState sealed : public VirtualObject, public DragonCameraState
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.Position"/>.
            /// </summary>
            virtual property NiPoint3^ Position
            {
                NiPoint3^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPoint3^>(this->Address + 0x40);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.OverShoulderOffset"/>.
            /// </summary>
            virtual property NiPoint3^ OverShoulderOffset
            {
                NiPoint3^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPoint3^>(this->Address + 0x5C);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.Node"/>.
            /// </summary>
            virtual property NiNode^ Node
            {
                NiNode^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiNode^>(Memory::ReadPointer(this->Address + 0x30, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.TargetNode"/>.
            /// </summary>
            virtual property NiPointer<NiNode^>^ TargetNode
            {
                NiPointer<NiNode^>^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPointer<NiNode^>^>(this->Address + 0xA0);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.TargetNodeName"/>.
            /// </summary>
            virtual property BSFixedString^ TargetNodeName
            {
                BSFixedString^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<BSFixedString^>(this->Address + 0xA8);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.ControlNode"/>.
            /// </summary>
            virtual property NiNode^ ControlNode
            {
                NiNode^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiNode^>(Memory::ReadPointer(this->Address + 0x38, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.XRotationFromLastResetPoint"/>.
            /// </summary>
            virtual property System::Single XRotationFromLastResetPoint
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0xD4, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    Memory::WriteFloat(this->Address + 0xD4, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.YRotationFromLastResetPoint"/>.
            /// </summary>
            virtual property System::Single YRotationFromLastResetPoint
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0xD8, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    Memory::WriteFloat(this->Address + 0xD8, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.TargetZoomLevel"/>.
            /// </summary>
            virtual property System::Single TargetZoomLevel
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0x74, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    Memory::WriteFloat(this->Address + 0x74, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.CurrentZoomLevel"/>.
            /// </summary>
            virtual property System::Single CurrentZoomLevel
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0x78, false);
                }
                void __clrcall set(System::Single value) sealed
                {
                    Memory::WriteFloat(this->Address + 0x78, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.LastCollisionPoint"/>.
            /// </summary>
            virtual property NiPoint3^ LastCollisionPoint
            {
                NiPoint3^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPoint3^>(this->Address + 0x90);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="ThirdPersonState.IsFreeLookMode"/>.
            /// </summary>
            virtual property bool IsFreeLookMode
            {
                bool __clrcall get() sealed
                {
                    auto self = this;
                    return MCH::b(self->InvokeVTableThisCall(0, 0x60));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESCameraState.Camera"/>.
            /// </summary>
            virtual property TESCamera^ Camera
            {
                TESCamera^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESCamera^>(Memory::ReadPointer(this->Address + 0x10, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESCameraState.Id"/>.
            /// </summary>
            virtual property TESCameraStates Id
            {
                TESCameraStates __clrcall get() sealed
                {
                    return (TESCameraStates)Memory::ReadInt32(this->Address + 0x18, false);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESCameraState.GetCurrentPosition"/>.
            /// </summary>
            virtual void __clrcall GetCurrentPosition(NiPoint3^ result) sealed
            {
                auto self = this;
                if(result == nullptr) throw gcnew System::ArgumentNullException("result");
                stack10 alloc;
                self->InvokeVTableThisCall(0, 0x28, alloc.ptr());
                result->X = alloc.get<float>(0);
                result->Y = alloc.get<float>(4);
                result->Z = alloc.get<float>(8);
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="PlayerCamera"/>.
        /// </summary>
        private ref class impl_PlayerCamera sealed : public VirtualObject, public PlayerCamera
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESCamera.Node"/>.
            /// </summary>
            virtual property NiNode^ Node
            {
                NiNode^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiNode^>(Memory::ReadPointer(this->Address + 0x20, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESCamera.State"/>.
            /// </summary>
            virtual property TESCameraState^ State
            {
                TESCameraState^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESCameraState^>(Memory::ReadPointer(this->Address + 0x28, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="PlayerCamera.CameraFirstPersonState"/>.
            /// </summary>
            virtual property FirstPersonState^ CameraFirstPersonState
            {
                FirstPersonState^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<FirstPersonState^>(Memory::ReadPointer(this->Address + 0xB8, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="PlayerCamera.CameraAutoVanityState"/>.
            /// </summary>
            virtual property AutoVanityState^ CameraAutoVanityState
            {
                AutoVanityState^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<AutoVanityState^>(Memory::ReadPointer(this->Address + 0xC0, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="PlayerCamera.CameraVATSCameraState"/>.
            /// </summary>
            virtual property VATSCameraState^ CameraVATSCameraState
            {
                VATSCameraState^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<VATSCameraState^>(Memory::ReadPointer(this->Address + 0xC8, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="PlayerCamera.CameraFreeCameraState"/>.
            /// </summary>
            virtual property FreeCameraState^ CameraFreeCameraState
            {
                FreeCameraState^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<FreeCameraState^>(Memory::ReadPointer(this->Address + 0xD0, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="PlayerCamera.CameraIronSightsState"/>.
            /// </summary>
            virtual property IronSightsState^ CameraIronSightsState
            {
                IronSightsState^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<IronSightsState^>(Memory::ReadPointer(this->Address + 0xD8, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="PlayerCamera.CameraFurnitureCameraState"/>.
            /// </summary>
            virtual property FurnitureCameraState^ CameraFurnitureCameraState
            {
                FurnitureCameraState^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<FurnitureCameraState^>(Memory::ReadPointer(this->Address + 0xE0, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="PlayerCamera.CameraPlayerCameraTransitionState"/>.
            /// </summary>
            virtual property PlayerCameraTransitionState^ CameraPlayerCameraTransitionState
            {
                PlayerCameraTransitionState^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<PlayerCameraTransitionState^>(Memory::ReadPointer(this->Address + 0xE8, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="PlayerCamera.CameraTweenMenuCameraState"/>.
            /// </summary>
            virtual property TweenMenuCameraState^ CameraTweenMenuCameraState
            {
                TweenMenuCameraState^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TweenMenuCameraState^>(Memory::ReadPointer(this->Address + 0xF0, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="PlayerCamera.CameraThirdPersonState1"/>.
            /// </summary>
            virtual property ThirdPersonState^ CameraThirdPersonState1
            {
                ThirdPersonState^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<ThirdPersonState^>(Memory::ReadPointer(this->Address + 0xF8, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="PlayerCamera.CameraThirdPersonState2"/>.
            /// </summary>
            virtual property ThirdPersonState^ CameraThirdPersonState2
            {
                ThirdPersonState^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<ThirdPersonState^>(Memory::ReadPointer(this->Address + 0x100, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="PlayerCamera.CameraHorseCameraState"/>.
            /// </summary>
            virtual property HorseCameraState^ CameraHorseCameraState
            {
                HorseCameraState^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<HorseCameraState^>(Memory::ReadPointer(this->Address + 0x108, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="PlayerCamera.CameraBleedoutCameraState"/>.
            /// </summary>
            virtual property BleedoutCameraState^ CameraBleedoutCameraState
            {
                BleedoutCameraState^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<BleedoutCameraState^>(Memory::ReadPointer(this->Address + 0x110, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="PlayerCamera.CameraDragonCameraState"/>.
            /// </summary>
            virtual property DragonCameraState^ CameraDragonCameraState
            {
                DragonCameraState^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<DragonCameraState^>(Memory::ReadPointer(this->Address + 0x118, false));
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="PlayerCamera.EnableVanityMode"/>.
            /// </summary>
            virtual property System::Byte EnableVanityMode
            {
                System::Byte __clrcall get() sealed
                {
                    return Memory::ReadUInt8(this->Address + 0x160, false);
                }
                void __clrcall set(System::Byte value) sealed
                {
                    Memory::WriteUInt8(this->Address + 0x160, value, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="PlayerCamera.Collidable"/>.
            /// </summary>
            virtual property NiCollisionObject^ Collidable
            {
                NiCollisionObject^ __clrcall get() sealed
                {
                    auto self = this;
                    auto ptr = Memory::ReadPointer(self->Address + 0x128, false);
                    return MemoryObject::FromAddress<NiCollisionObject^>(ptr);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="PlayerCamera.LastNodePosition"/>.
            /// </summary>
            virtual property NiPoint3^ LastNodePosition
            {
                NiPoint3^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<NiPoint3^>(this->Address + 0x144);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="PlayerCamera.TimeSinceLastInput"/>.
            /// </summary>
            virtual property System::Single TimeSinceLastInput
            {
                System::Single __clrcall get() sealed
                {
                    return Memory::ReadFloat(this->Address + 0x150, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="PlayerCamera.TargetRefHandle"/>.
            /// </summary>
            virtual property System::UInt32 TargetRefHandle
            {
                System::UInt32 __clrcall get() sealed
                {
                    return Memory::ReadUInt32(this->Address + 0x3C, false);
                }
            }
            
            
            /// <summary>
            /// Implementation of method <see cref="PlayerCamera.EnterFirstPerson"/>.
            /// </summary>
            virtual void __clrcall EnterFirstPerson() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::PlayerCamera_EnterFirstPerson), self->Address);
            }
            
            /// <summary>
            /// Implementation of method <see cref="PlayerCamera.EnterThirdPerson"/>.
            /// </summary>
            virtual void __clrcall EnterThirdPerson() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::PlayerCamera_EnterThirdPerson), self->Address);
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="TESQuest"/>.
        /// </summary>
        private ref class impl_TESQuest sealed : public VirtualObject, public TESQuest
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="TESFullName.Text"/>.
            /// </summary>
            virtual property BSFixedString^ Text
            {
                BSFixedString^ __clrcall get() sealed
                {
                    auto self = this->As<TESFullName^>();
                    return MemoryObject::FromAddress<BSFixedString^>(self->Address + 0x8);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormFlags"/>.
            /// </summary>
            virtual property System::UInt32 FormFlags
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x10, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormId"/>.
            /// </summary>
            virtual property System::UInt32 FormId
            {
                System::UInt32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return Memory::ReadUInt32(self->Address + 0x14, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.FormType"/>.
            /// </summary>
            virtual property FormTypes FormType
            {
                FormTypes __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (FormTypes)Memory::ReadUInt8(self->Address + 0x1A, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.EditorId"/>.
            /// </summary>
            virtual property System::String^ EditorId
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto ptr = self->InvokeVTableThisCall(0, 0x190);
                    if(ptr == System::IntPtr::Zero)
                        return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Name"/>.
            /// </summary>
            virtual property System::String^ Name
            {
                System::String^ __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    stack10 s;
                    auto ptr = self->InvokeVTableThisCall(0, 0x170, s.ptr());
                    if(ptr == System::IntPtr::Zero) return nullptr;
                    return Memory::ReadString(ptr, false, false);
                }
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.PlayerKnows"/>.
            /// </summary>
            virtual property bool PlayerKnows
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return _IntPtrExtensions::ToBool(self->InvokeVTableThisCall(0, 0xB8));
                }
            }
            
            /// <summary>
            /// Returns a <see cref="System.String" /> that represents this instance.
            /// </summary>
            virtual System::String^ ToString() override sealed
            {
                auto name = this->Name;
                auto editorId = this->EditorId;
                if(System::String::IsNullOrEmpty(name))
                    name = "";
                else
                    name = "\"" + name + "\" ";
                if(System::String::IsNullOrEmpty(editorId))
                    editorId = "";
                else
                    editorId = editorId + " ";
                return editorId + name + "0x" + this->FormId.ToString("X") + " (" + this->FormType.ToString() + ")";
            }
            
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.GoldValue"/>.
            /// </summary>
            virtual property System::Int32 GoldValue
            {
                System::Int32 __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    return (System::Int32)(MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_GoldValue_Get), 0, 0, self->Address)) & 0xFFFFFFFF);
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeyword"/>.
            /// </summary>
            virtual bool __clrcall HasKeyword(BGSKeyword^ keyword) sealed
            {
                auto self = this->As<TESForm^>();
                MCH::e<BGSKeyword^>(keyword, "keyword");
                return (MCH::u(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESForm_HasKeyword), 0, 0, self->Address, keyword->Address)) & 0xFF) != 0;
            }
            
            /// <summary>
            /// Implementation of method <see cref="TESForm.HasKeywordText"/>.
            /// </summary>
            virtual bool __clrcall HasKeywordText(System::String^ keyword) sealed
            {
                if(keyword == nullptr) throw gcnew System::ArgumentNullException("keyword");
                auto ls = KeywordCache::Get(keyword);
                for each(BGSKeyword^ kw in ls)
                {
                    if(this->HasKeyword(kw)) return true;
                }
                return false;
            }
            
            /// <summary>
            /// Implementation of property <see cref="TESForm.Has3D"/>.
            /// </summary>
            virtual property bool Has3D
            {
                bool __clrcall get() sealed
                {
                    auto self = this->As<TESForm^>();
                    auto p = self->InvokeVTableThisCall(0, 0x138);
                    return (MCH::u(p) & 0xFF) != 0;
                }
            }
            
            
            
            /// <summary>
            /// Implementation of method <see cref="TESQuest.GetAlias"/>.
            /// </summary>
            virtual BGSBaseAlias^ __clrcall GetAlias(System::Int32 id) sealed
            {
                auto self = this;
                return MemoryObject::FromAddress<BGSBaseAlias^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::TESQuest_GetAlias), 0, 0, self->Address, id));
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BGSBaseAlias"/>.
        /// </summary>
        private ref class impl_BGSBaseAlias sealed : public VirtualObject, public BGSBaseAlias
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="BGSBaseAlias.OwningQuest"/>.
            /// </summary>
            virtual property TESQuest^ OwningQuest
            {
                TESQuest^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESQuest^>(Memory::ReadPointer(this->Address + 0x10, false));
                }
            }
        };
        
        /// <summary>
        /// Implementation of interface <see cref="BGSRefAlias"/>.
        /// </summary>
        private ref class impl_BGSRefAlias sealed : public VirtualObject, public BGSRefAlias
        {
        public:
            /// <summary>
            /// Implementation of property <see cref="BGSBaseAlias.OwningQuest"/>.
            /// </summary>
            virtual property TESQuest^ OwningQuest
            {
                TESQuest^ __clrcall get() sealed
                {
                    return MemoryObject::FromAddress<TESQuest^>(Memory::ReadPointer(this->Address + 0x10, false));
                }
            }
            
            /// <summary>
            /// Implementation of method <see cref="BGSRefAlias.Clear"/>.
            /// </summary>
            virtual void __clrcall Clear() sealed
            {
                auto self = this;
                Memory::InvokeCdecl(MCH::FromBase(GameAddress::BGSRefAlias_Clear), 0, 0, self->Address);
            }
            
            /// <summary>
            /// Implementation of property <see cref="BGSRefAlias.Reference"/>.
            /// </summary>
            virtual property TESObjectREFR^ Reference
            {
                TESObjectREFR^ __clrcall get() sealed
                {
                    auto self = this;
                    return MemoryObject::FromAddress<TESObjectREFR^>(Memory::InvokeCdecl(MCH::FromBase(GameAddress::BGSRefAlias_Reference_Get), 0, 0, self->Address));
                }
                void __clrcall set(TESObjectREFR^ value) sealed
                {
                    auto self = this;
                    MCH::e<TESObjectREFR^>(value, nullptr);
                    if(value == nullptr)
                    {
						this->Clear();
						return;
                    }
                    Memory::InvokeCdecl(MCH::FromBase(GameAddress::BGSRefAlias_Reference_Set), 0, 0, self->Address, value->Address);
                }
            }
        };
    }
}

#pragma warning(pop)
