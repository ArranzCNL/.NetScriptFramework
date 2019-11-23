#pragma once
#include "Game.h"
#include "GameAddresses.h"

namespace NetScriptFramework
{
	namespace SkyrimSE
	{		
		/// <summary>
		/// Implements game string handling.
		/// </summary>
		/// <seealso cref="TemporaryObject" />
		public ref class StringRefHolder sealed : TemporaryObject
		{
		public:			
			/// <summary>
			/// Initializes a new instance of the <see cref="StringRefHolder"/> class.
			/// </summary>
			/// <param name="text">The text.</param>
			StringRefHolder(System::String^ text)
			{
				if (text == nullptr)
					return;

				auto bytes = System::Text::Encoding::UTF8->GetBytes(text);
				_alloc = Memory::Allocate(0x10 + bytes->Length + 8, 0, false);
				{
					Memory::WriteBytes(_alloc->Address + 0x10, bytes, false);
					Memory::WriteUInt32(_alloc->Address + 0x10 + bytes->Length, 0, false);
					Memory::InvokeCdecl(MCH::FromBase(GameAddress::BSFixedString__Initialize), _alloc->Address, _alloc->Address + 0x10);
				}
			}

			/// <summary>
			/// Gets the address of the allocation. This is usually what is passed as function argument.
			/// </summary>
			property System::IntPtr AddressOf
			{
				System::IntPtr __clrcall get()
				{
					if (_alloc == nullptr)
						return System::IntPtr::Zero;

					return _alloc->Address;
				}
			}

			/// <summary>
			/// Gets the value of the string.
			/// </summary>
			property System::IntPtr Value
			{
				System::IntPtr __clrcall get()
				{
					if (_alloc == nullptr)
						return System::IntPtr::Zero;

					return Memory::ReadPointer(_alloc->Address, false);
				}
			}

			/// <summary>
			/// Gets the text value of the string. This may or may not be equal to what was passed as argument in constructor!
			/// </summary>
			property System::String^ Text
			{
				System::String^ __clrcall get()
				{
					auto ptr = Value;
					if (ptr == System::IntPtr::Zero)
						return nullptr;

					return Memory::ReadString(ptr, false, false);
				}
			}

		private:
			MemoryAllocation^ _alloc = nullptr;

		protected:
			void Free() override
			{
				if (_alloc != nullptr)
				{
					Memory::InvokeCdecl(MCH::FromBase(GameAddress::BSFixedString__Release), _alloc->Address);

					delete _alloc;
					_alloc = nullptr;
				}
			}
		};
		
		/// <summary>
		/// Game's memory related functions.
		/// </summary>
		public ref class MemoryManager sealed
		{
		private:			
			/// <summary>
			/// Prevents a default instance of the <see cref="MemoryManager"/> class from being created.
			/// </summary>
			MemoryManager() { }
			
			/// <summary>
			/// Initializes this instance if it's not already initialized.
			/// </summary>
			static void Initialize()
			{
				if (Memory::ReadInt32(MCH::FromBase(GameAddress::gMemoryManagerState), false) == 2)
					return;

				Memory::InvokeCdecl(MCH::FromBase(GameAddress::Memory__static_ctor), MCH::FromBase(GameAddress::gMemoryManager), MCH::FromBase(GameAddress::gMemoryManagerState));
			}

		public:			
			/// <summary>
			/// Determines whether the memory manager of game is initialized. It is still ok to use the memory related functions as we will initialize it ourself if it's not already.
			/// </summary>
			/// <returns></returns>
			static bool IsInitialized()
			{
				return Memory::ReadInt32(MCH::FromBase(GameAddress::gMemoryManagerState), false) == 2;
			}

			/// <summary>
			/// Allocates the memory with specified size.
			/// </summary>
			/// <param name="size">The size.</param>
			/// <param name="align">The alignment.</param>
			/// <returns></returns>
			static System::IntPtr Allocate(System::Int32 size, System::Int32 align)
			{
				if (size < 0)
					throw gcnew System::ArgumentOutOfRangeException("size", "Size of allocation can not be negative!");
				if (align < 0)
					throw gcnew System::ArgumentOutOfRangeException("align", "Alignment can not be negative!");

				Initialize();

				return Memory::InvokeCdecl(MCH::FromBase(GameAddress::Memory__Allocate), MCH::FromBase(GameAddress::gMemoryManager), size, align);
			}

			/// <summary>
			/// Frees the specified memory allocation.
			/// </summary>
			/// <param name="buf">The buffer returned from Allocate.</param>
			/// <param name="aligned">if set to <c>true</c> then it was allocated as aligned.</param>
			static void Free(System::IntPtr buf, bool aligned)
			{
				if (buf == System::IntPtr::Zero)
					throw gcnew System::ArgumentNullException("buf");

				Initialize();

				Memory::InvokeCdecl(MCH::FromBase(GameAddress::Memory__Free), MCH::FromBase(GameAddress::gMemoryManager), buf, aligned ? 1 : 0);
			}
		};

		/// <summary>
		/// Implements game object reference handling.
		/// </summary>
		/// <seealso cref="TemporaryObject" />
		public ref class ObjectRefHolder sealed : TemporaryObject
		{
		public:
			/// <summary>
			/// Initializes a new instance of the <see cref="ObjectRefHolder" /> class.
			/// </summary>
			/// <param name="obj">The object to create reference ID for.</param>
			ObjectRefHolder(TESObjectREFR^ obj)
			{
				if (obj == nullptr)
					return;

				_allocated = false;
				_obj = obj;
				MemoryAllocation^ alloc = Memory::Allocate(0x10, 0, false);
				Memory::WriteUInt32(alloc->Address, 0, false);
				try
				{
					Memory::InvokeCdecl(MCH::FromBase(GameAddress::CreateRefHandleId), alloc->Address, obj->Address);
					_value = Memory::ReadUInt32(alloc->Address, false);
				}
				finally
				{
					if (alloc != nullptr)
						delete alloc;
				}
			}
			
			/// <summary>
			/// Initializes a new instance of the <see cref="ObjectRefHolder"/> class.
			/// </summary>
			/// <param name="refId">The reference identifier to look up.</param>
			ObjectRefHolder(System::UInt32 refId)
			{
				_value = refId;
				_allocated = true;
				if (refId != 0)
				{
					MemoryAllocation^ alloc = Memory::Allocate(0x20, 0, false);
					Memory::WriteUInt32(alloc->Address, refId, false);
					Memory::WritePointer(alloc->Address + 0x10, System::IntPtr::Zero, false);
					try
					{
						Memory::InvokeCdecl(MCH::FromBase(GameAddress::LookupObjectByRefHandle), alloc->Address, alloc->Address + 0x10);
						System::IntPtr result = Memory::ReadPointer(alloc->Address + 0x10, false);
						if (result != System::IntPtr::Zero)
							_obj = MemoryObject::FromAddress<TESObjectREFR^>(result);
					}
					finally
					{
						if (alloc != nullptr)
							delete alloc;
					}
				}
			}
			
			/// <summary>
			/// Gets the handle ID. This is zero if not valid!
			/// </summary>
			/// <value>
			/// The handle.
			/// </value>
			property System::UInt32 Handle
			{
				System::UInt32 get()
				{
					return _value;
				}
			}
			
			/// <summary>
			/// Gets the object instance. This is null if not valid!
			/// </summary>
			/// <value>
			/// The object.
			/// </value>
			property TESObjectREFR^ Object
			{
				TESObjectREFR^ get()
				{
					return _obj;
				}
			}
			
			/// <summary>
			/// Returns true if this handle is valid.
			/// </summary>
			/// <value>
			///   <c>true</c> if this instance is valid; otherwise, <c>false</c>.
			/// </value>
			property bool IsValid
			{
				bool get()
				{
					return _obj != nullptr && _value != 0;
				}
			}

		private:
			TESObjectREFR^ _obj = nullptr;
			System::UInt32 _value = 0;
			bool _allocated;

		protected:
			void Free() override
			{
				if (_obj != nullptr && _value != 0 && _allocated)
				{
					_obj->DecRef();
					_obj = nullptr;
					_value = 0;
				}
			}
		};
	}
}
