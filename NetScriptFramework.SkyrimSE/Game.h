#pragma once
#pragma warning(push)
#pragma warning(disable : 4638)

#include "GameAddresses.h"

namespace NetScriptFramework
{
    namespace SkyrimSE
    {
        /// <summary>
        /// Game library header.
        /// </summary>
        /// <seealso cref="NetScriptFramework.Game" />
        private ref class SkyrimGame sealed : Game
        {
        public:
            /// <summary>
            /// Initializes a new instance of the <see cref="SkyrimGame"/> class.
            /// </summary>
            SkyrimGame() : Game()
            {
                System::Diagnostics::FileVersionInfo^ ver = System::Diagnostics::FileVersionInfo::GetVersionInfo(this->ExecutableName);
                this->AppVersion = gcnew System::Collections::Generic::List<System::Int32>();
                array<System::Int32> ^ arr = nullptr;
                if ((arr = ParseVersion(ver->ProductVersion, 0, 0, 0, 0)) != nullptr) this->AppVersion->AddRange(arr);
                if (this->AppVersion->Count == 0 && (arr = ParseVersion(ver->FileVersion, 0, 0, 0, 0)) != nullptr) this->AppVersion->AddRange(arr);
                if (this->AppVersion->Count == 0 && (arr = ParseVersion(nullptr, ver->ProductMajorPart, ver->ProductMinorPart, ver->ProductBuildPart, ver->ProductPrivatePart)) != nullptr) this->AppVersion->AddRange(arr);
                if (this->AppVersion->Count == 0 && (arr = ParseVersion(nullptr, ver->FileMajorPart, ver->FileMinorPart, ver->FileBuildPart, ver->FilePrivatePart)) != nullptr) this->AppVersion->AddRange(arr);
            }
            
            /// <summary>
            /// Gets the name of the executable of current game including file extension. For example "TESV.exe".
            /// </summary>
            /// <value>
            /// The name of the executable.
            /// </value>
            property System::String^ ExecutableName
            {
                System::String^ __clrcall get() override
                {
                    return "SkyrimSE.exe";
                }
            }
            
            /// <summary>
            /// Gets the name of the target module. This is usually equal to ExecutableName but sometimes we may want to target a DLL inside the process
            /// instead in which case they would be different.
            /// </summary>
            /// <value>
            /// The name of the module.
            /// </value>
            property System::String^ ModuleName
            {
                System::String^ __clrcall get() override
                {
                    return "SkyrimSE.exe";
                }
            }
            
            /// <summary>
            /// Gets the full name of current game. For example "The Elder Scrolls V: Skyrim"
            /// </summary>
            /// <value>
            /// The full name.
            /// </value>
            property System::String^ FullName
            {
                System::String^ __clrcall get() override
                {
                    return "The Elder Scrolls V: Skyrim Special Edition";
                }
            }
            
            /// <summary>
            /// Gets the version of current game. It is read from the executable. This is a list of four integers always.
            /// The first integer in the list is the most significant version number and last is the least significant.
            /// For example { 1, 9, 32, 0 }
            /// </summary>
            /// <value>
            /// The version of game.
            /// </value>
            property System::Collections::Generic::IReadOnlyList<System::Int32>^ GameVersion
            {
                System::Collections::Generic::IReadOnlyList<System::Int32>^ __clrcall get() override
                {
                    return this->AppVersion;
                }
            }
            
            /// <summary>
            /// Gets a value indicating whether currently loaded game version is a valid version supported by this library.
            /// This is only used during game header initialization. If it returns false the game will abort and display an error.
            /// </summary>
            /// <value>
            /// <c>true</c> if this instance is valid version; otherwise, <c>false</c>.
            /// </value>
            property System::Boolean IsValidVersion
            {
                System::Boolean __clrcall get() override
                {
#ifdef _SKYRIMSE_VER_1_5_62
                    return GameVersion[0] == 1 && GameVersion[1] == 5 && GameVersion[2] == 62  && GameVersion[3] == 0;
#endif
#ifdef _SKYRIMSE_VER_1_5_73
					return GameVersion[0] == 1 && GameVersion[1] == 5 && GameVersion[2] >= 73 && GameVersion[2] <= 80;
#endif
                }
            }
            
            /// <summary>
            /// Gets the library version. This is separate from game's version. Multiple library versions may exist for the same
            /// version of the game.
            /// </summary>
            /// <value>
            /// The library version.
            /// </value>
            property System::Int32 LibraryVersion
            {
                System::Int32 __clrcall get() override
                {
                    return 10;
                }
            }
            
            /// <summary>
            /// Gets the short name of current game. For example "Skyrim".
            /// </summary>
            /// <value>
            /// The short name.
            /// </value>
            property System::String^ ShortName
            {
                System::String^ __clrcall get() override
                {
                    return "SkyrimSE";
                }
            }
            
        private:
            /// <summary>
            /// The application version.
            /// </summary>
            initonly System::Collections::Generic::List<System::Int32>^ AppVersion;
            
        protected:
            /// <summary>
            /// Initializes the game library.
            /// </summary>
            void Initialize() override;
        };
        
        /// <summary>
        /// Implement helper functions for converting between base address types.
        /// </summary>
        [System::Runtime::CompilerServices::ExtensionAttribute]
        public ref class MCH sealed abstract
        {
        private:
            /// <summary>
            /// The internal base address value.
            /// </summary>
            static System::Nullable<System::IntPtr> _base;
            
            /// <summary>
            /// Gets the base address of main module.
            /// </summary>
            /// <returns></returns>
            static System::IntPtr GetBase()
            {
                if (!_base.HasValue)
                    _base = Main::GetMainTargetedModule()->BaseAddress;
                return _base.Value;
            }
            
        public:
            /// <summary>
            /// Convert pointer from static base address to current module's base.
            /// </summary>
            /// <param name="ptr">The pointer to convert.</param>
            /// <returns></returns>
            [System::Runtime::CompilerServices::ExtensionAttribute]
            static System::IntPtr FromBase(System::IntPtr ptr)
            {
                return System::IntPtr(ptr.ToInt64() - 0x140000000 + GetBase().ToInt64());
            }
            
            /// <summary>
            /// Convert pointer from current module's base address to static base.
            /// </summary>
            /// <param name="ptr">The pointer to convert.</param>
            /// <returns></returns>
            [System::Runtime::CompilerServices::ExtensionAttribute]
            static System::IntPtr ToBase(System::IntPtr ptr)
            {
                return System::IntPtr(ptr.ToInt64() - GetBase().ToInt64() + 0x140000000);
            }
            
            /// <summary>
            /// Convert pointer from static base address to current module's base.
            /// </summary>
            /// <param name="ptr">The pointer to convert.</param>
            /// <returns></returns>
            static System::IntPtr FromBase(System::Int64 ptr)
            {
                return System::IntPtr(ptr - 0x140000000 + GetBase().ToInt64());
            }
            
            /// <summary>
            /// Convert pointer to a convertible value.
            /// </summary>
            /// <param name="ptr">The pointer to convert.</param>
            /// <returns></returns>
            internal: static System::UInt64 u(System::IntPtr ptr)
            {
                return System::UInt64(ptr.ToInt64());
            }
            
            /// <summary>
            /// Convert pointer to a bool value.
            /// </summary>
            /// <param name="ptr">The pointer to convert.</param>
            /// <returns></returns>
            internal: static bool b(System::IntPtr ptr)
            {
                auto val = u(ptr);
                return (val & 0xFF) != 0;
            }
            
            /// <summary>
            /// Process function argument type.
            /// </summary>
            /// <param name="obj">The pointer to convert.</param>
            /// <returns></returns>
            internal:
            generic <typename T> where T : IVirtualObject
            static bool e(T% obj, System::String^ checkNullArg)
            {
                if(obj != nullptr)
                    obj = obj->As<T>();
                if(obj == nullptr)
                {
                    if(checkNullArg != nullptr) throw gcnew System::ArgumentNullException(checkNullArg);
                    return false;
                }
                return true;
            }
        };
    }
}

#pragma warning(pop)
