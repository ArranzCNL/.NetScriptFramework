#include "Stdafx.h"
#include "RTTI.h"

#define EXPORT __declspec(dllexport)
#define RUNTIME_VERSION 4

#define ARGTYPE_FLOAT 1
#define ARGTYPE_OTHER 2

// Must be aligned to 0x10 or it will crash on first recursion
#define HOOK_CONTEXT_SIZE (sizeof(CONTEXT) + 0x40)

// context:
// p = sizeof(Pointer)
// [0] = real context
// [size-p*6] = orig return address
// [size-p*5] = rax
// [size-p*4] = rcx
// [size-p*3] = hook address
// [size-p*2] = return address
// [size-p*1] = index of context (for verify)

// Max recursive hook call depth
#define HOOK_MAX_CALLS 1024

#define TLS_STORAGE_HOOK_CALL_COUNT 0
#define TLS_STORAGE_HOOK_CONTEXT_BLOCK 1
#define TLS_STORAGE_EXCEPTION_DEPTH 2
#define TLS_STORAGE_PERFORMANCE_MONITOR 3
#define TLS_STORAGE_SIZE 4

#define PMON_DEPTH 0
#define PMON_STACK 1
#define PMON_ENTRIES 2
#define PMON_BEGIN 3
#define PMON_END 4
#define PMON_SIZE 5

#define PMONMAXSTACK 1024

#define PMONENTRY_DEPTH 0
#define PMONENTRY_CURRENT_BEGIN 1
#define PMONENTRY_TOTAL_INCLUSIVE 2
#define PMONENTRY_TOTAL_EXCLUSIVE 3
#define PMONENTRY_SIZE 4

bool is64Bit = false;
int initState = 0;

void _CriticalFail_NoLog(const char * msg)
{
	auto method = NetScriptFramework::Main::typeid->GetMethod("_CriticalException_NoLog", System::Reflection::BindingFlags::NonPublic | System::Reflection::BindingFlags::Static);
	array<System::Object^>^ p = gcnew array<System::Object^>(2);
	p[0] = gcnew System::String(msg);
	p[1] = true;
	method->Invoke(nullptr, p);
}

void _CriticalFail(const char * msg)
{
	NetScriptFramework::Main::CriticalException(gcnew System::String(msg), true);
}

#pragma managed(push, off)
void * AddPtr(void * ptr, int offset)
{
	Pointer value = (Pointer)ptr;
	value += offset;
	return (void*)value;
}

void CriticalFail(const char * fmt, ...)
{
	char msg[4096];
	va_list args;
	va_start(args, fmt);
	vsnprintf_s(msg, 4096, fmt, args);
	va_end(args);

	_CriticalFail(msg);
}

void CriticalFailNoLog(const char * fmt, ...)
{
	char msg[4096];
	va_list args;
	va_start(args, fmt);
	vsnprintf_s(msg, 4096, fmt, args);
	va_end(args);

	_CriticalFail_NoLog(msg);
}
#pragma managed(pop)

bool IsFrameworkOk()
{
	return initState == 2;
}

delegate void DoActionDelegate(System::IntPtr data, System::Int32 pass);

private ref class ManagedHook sealed abstract
{
public:
	static bool Prepare()
	{
		auto method = NetScriptFramework::Memory::typeid->GetMethod("DoAction", System::Reflection::BindingFlags::NonPublic | System::Reflection::BindingFlags::Static);
		if (method == nullptr)
		{
			CriticalFail("Initialization failed! Memory::DoAction method was not found in NetScriptFramework.dll");
			return false;
		}

		_funcPtr = method;
		_funcDel = safe_cast<DoActionDelegate^>(_funcPtr->CreateDelegate(DoActionDelegate::typeid, nullptr));

		if (_funcDel == nullptr)
		{
			CriticalFail("Initialization failed! Memory::DoAction method failed to create delegate");
			return false;
		}

		method = NetScriptFramework::Main::typeid->GetMethod("UnhandledExceptionFilter", System::Reflection::BindingFlags::NonPublic | System::Reflection::BindingFlags::Static);
		if (method == nullptr)
		{
			CriticalFail("Initialization failed! Main::UnhandledExceptionFilter method was not found in NetScriptFramework.dll");
			return false;
		}

		_exceptionPtr = method;

		method = NetScriptFramework::Main::typeid->GetMethod("OnDetachThread", System::Reflection::BindingFlags::NonPublic | System::Reflection::BindingFlags::Static);
		if (method == nullptr)
		{
			CriticalFail("Initialization failed! Main::OnDetachThread method was not found in NetScriptFramework.dll");
			return false;
		}

		_detachPtr = method;

		method = NetScriptFramework::Main::typeid->GetMethod("OnAttachThread", System::Reflection::BindingFlags::NonPublic | System::Reflection::BindingFlags::Static);
		if (method == nullptr)
		{
			CriticalFail("Initialization failed! Main::OnAttachThread method was not found in NetScriptFramework.dll");
			return false;
		}

		_attachPtr = method;
		return true;
	}

	static System::Reflection::MethodInfo^ _funcPtr = nullptr;
	static System::Reflection::MethodInfo^ _exceptionPtr = nullptr;
	static System::Reflection::MethodInfo^ _detachPtr = nullptr;
	static System::Reflection::MethodInfo^ _attachPtr = nullptr;
	static DoActionDelegate^ _funcDel = nullptr;
};

void * DoAction(void * data, unsigned int pass)
{
	pass &= 0x7F;

	ManagedHook::_funcDel(System::IntPtr(data), (int)pass);
	return data;
}

void DetachThread()
{
	array<System::Object^>^ args = gcnew array<System::Object^>(0);
	ManagedHook::_detachPtr->Invoke(nullptr, args);
}

void AttachThread()
{
	array<System::Object^>^ args = gcnew array<System::Object^>(0);
	ManagedHook::_attachPtr->Invoke(nullptr, args);
}

#pragma managed(push, off)

void HookAllocateFailed()
{
	CriticalFail("Failed to allocate hook execution context due to limit of %d reached on thread %d. Possible recusion error?", HOOK_MAX_CALLS, GetCurrentThreadId());
}

void HookVerifyError()
{
	CriticalFail("Failed hook integrity check on thread %d!", GetCurrentThreadId());
}

static DWORD dwTlsIndex = 0;

Pointer * GetExceptionDepthPointer()
{
	Pointer * depth = NULL;
	{
		auto tls = (Pointer*)TlsGetValue(dwTlsIndex);
		if (tls != NULL)
			depth = &tls[TLS_STORAGE_EXCEPTION_DEPTH];
	}
	return depth;
}

/*void _SetupPerformanceMonitor(void * begin, void * end)
{
	Pointer begin_t = (Pointer)begin;
	Pointer end_t = (Pointer)end;

	if (end_t <= begin_t)
		return;

	Pointer count = end_t - begin_t;
	auto tls = (Pointer*)TlsGetValue(dwTlsIndex);
	if (tls == NULL)
		return;

	Pointer * pmon = &tls[TLS_STORAGE_PERFORMANCE_MONITOR];
	if (*pmon)
		return;

	*pmon = (Pointer)AllocateC(PMON_SIZE * sizeof(Pointer), 0);
	pmon = (Pointer*)(*pmon);

	pmon[PMON_DEPTH] = 0;
	pmon[PMON_STACK] = (Pointer)AllocateC(PMONMAXSTACK * sizeof(Pointer), 0);
	pmon[PMON_ENTRIES] = (Pointer)AllocateC(count * sizeof(Pointer) * PMONENTRY_SIZE, 0);
	pmon[PMON_BEGIN] = begin_t;
	pmon[PMON_END] = end_t;

	for (Pointer i = 0; i < count; i++)
	{
		Pointer * entry = (Pointer*)(*((Pointer*)(pmon[PMON_ENTRIES] + sizeof(Pointer) * PMONENTRY_SIZE * i)));
		entry[PMONENTRY_DEPTH] = 0;
		entry[PMONENTRY_CURRENT_BEGIN] = 0;
		entry[PMONENTRY_TOTAL_INCLUSIVE] = 0;
		entry[PMONENTRY_TOTAL_EXCLUSIVE] = 0;
	}
}

void _FinishPerformanceMonitor()
{
	auto tls = (Pointer*)TlsGetValue(dwTlsIndex);
	if (tls == NULL)
		return;

	Pointer * pmon = &tls[TLS_STORAGE_PERFORMANCE_MONITOR];
	if (*pmon == 0)
		return;

	pmon = (Pointer*)(*pmon);

	Pointer begin_t = pmon[PMON_BEGIN];
	Pointer end_t = pmon[PMON_END];
	Pointer count = end_t - begin_t;

	System::IO::StreamWriter^ f = gcnew System::IO::StreamWriter("pmon_thread_" + GetCurrentThreadId() + ".txt", false);

	for (Pointer i = 0; i < count; i++)
	{
		Pointer * entry = (Pointer*)(*((Pointer*)(pmon[PMON_ENTRIES] + sizeof(Pointer) * PMONENTRY_SIZE * i)));
		if (entry[PMONENTRY_TOTAL_INCLUSIVE] == 0)
			continue;

		System::Int64 addr = begin_t + i;
		System::Int64 total_exc = pmon[PMONENTRY_TOTAL_EXCLUSIVE];
		System::Int64 total_inc = pmon[PMONENTRY_TOTAL_INCLUSIVE];
		f->WriteLine(addr.ToString("X") + " " + total_exc + " " + total_inc);
	}

	FreeC((void*)pmon[PMON_ENTRIES], false);
	FreeC((void*)pmon[PMON_STACK], false);
	FreeC((void*)pmon, false);

	tls[TLS_STORAGE_PERFORMANCE_MONITOR] = 0;

	f->Flush();
	delete f;
}*/

extern "C"
{
	EXPORT void IncIgnoreException()
	{
		Pointer * depth = GetExceptionDepthPointer();
		if (depth != NULL)
			*depth = *depth + 1;
	}

	EXPORT void DecIgnoreException()
	{
		Pointer * depth = GetExceptionDepthPointer();
		if (depth != NULL)
			*depth = *depth - 1;
	}

	#pragma optimize( "", off )
	EXPORT void * __stdcall InvokeThisCall(void * thisAddress, void * funcAddress, void * argCount, void * argData)
	{
		// This function body will be replaced at runtime.
		int64 result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		return (void*)result;
	}
	#pragma optimize( "", on )

	#pragma optimize( "", off )
	EXPORT void * __stdcall InvokeThisCallF(void * thisAddress, void * funcAddress, void * argCount, void * argData)
	{
		// This function body will be replaced at runtime.
		int64 result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		return (void*)result;
	}
	#pragma optimize( "", on )

#pragma optimize( "", off )
	EXPORT void * __stdcall InvokeThisCallD(void * thisAddress, void * funcAddress, void * argCount, void * argData)
	{
		// This function body will be replaced at runtime.
		int64 result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		return (void*)result;
	}
#pragma optimize( "", on )

	EXPORT void * __stdcall InvokeStdCall(void * funcAddress, void * argCount, void * argData)
	{
		return InvokeThisCall(0, funcAddress, argCount, argData);
	}

	EXPORT void * __stdcall InvokeStdCallF(void * funcAddress, void * argCount, void * argData)
	{
		return InvokeThisCallF(0, funcAddress, argCount, argData);
	}

	EXPORT void * __stdcall InvokeStdCallD(void * funcAddress, void * argCount, void * argData)
	{
		return InvokeThisCallF(0, funcAddress, argCount, argData);
	}

	#pragma optimize( "", off )
	EXPORT void * __stdcall InvokeCdecl(void * funcAddress, void * argCount, void * argData)
	{
		// This function body will be replaced at runtime.
		int64 result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		return (void*)result;
	}
	#pragma optimize( "", on )

	EXPORT void * __stdcall InvokeCdecl_addr()
	{
		return InvokeCdecl;
	}

	#pragma optimize( "", off )
	EXPORT void * __stdcall InvokeCdeclF(void * funcAddress, void * argCount, void * argData)
	{
		// This function body will be replaced at runtime.
		int64 result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		return (void*)result;
	}
	#pragma optimize( "", on )

	EXPORT void * __stdcall InvokeCdeclF_addr()
	{
		return InvokeCdeclF;
	}

#pragma optimize( "", off )
	EXPORT void * __stdcall InvokeCdeclD(void * funcAddress, void * argCount, void * argData)
	{
		// This function body will be replaced at runtime.
		int64 result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		return (void*)result;
	}
#pragma optimize( "", on )

	EXPORT void * __stdcall InvokeCdeclD_addr()
	{
		return InvokeCdeclD;
	}

#pragma optimize( "", off )
	EXPORT void __stdcall ReadDQFrom(void * source, void * dest)
	{
		// This function body will be replaced at runtime.
		int64 result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		return;
	}
#pragma optimize( "", on )

#pragma optimize( "", off )
	EXPORT void __stdcall WriteDQTo(void * source, void * dest)
	{
		// This function body will be replaced at runtime.
		int64 result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		return;
	}
#pragma optimize( "", on )

#pragma optimize( "", off )
	EXPORT void __stdcall ReadFQFrom(void * source, void * dest)
	{
		// This function body will be replaced at runtime.
		int64 result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		return;
	}
#pragma optimize( "", on )

#pragma optimize( "", off )
	EXPORT void __stdcall WriteFQTo(void * source, void * dest)
	{
		// This function body will be replaced at runtime.
		int64 result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0; result = 0;
		return;
	}
#pragma optimize( "", on )

	EXPORT void * __stdcall AllocateC(int size, int align)
	{
		if (align != 0)
			return _aligned_malloc(size, align);
		return malloc(size);
	}

	EXPORT void __stdcall FreeC(void * buf, bool align)
	{
		if (align)
			_aligned_free(buf);
		else
			free(buf);
	}

	EXPORT void * __stdcall GetDoActionAddress()
	{
		return DoAction;
	}

#define CALC_OFFSET(a) (int)((Pointer)a - (Pointer)&ctx)
	EXPORT int __stdcall GetContextOffset(int index)
	{
		CONTEXT ctx;

		switch (index)
		{
		case 0: return sizeof(CONTEXT);
#ifdef _WIN64
		case 1: return CALC_OFFSET(&ctx.Rax);
		case 2: return CALC_OFFSET(&ctx.Rbx);
		case 3: return CALC_OFFSET(&ctx.Rcx);
		case 4: return CALC_OFFSET(&ctx.Rdx);
		case 5: return CALC_OFFSET(&ctx.Rsi);
		case 6: return CALC_OFFSET(&ctx.Rdi);
		case 7: return CALC_OFFSET(&ctx.Rsp);
		case 8: return CALC_OFFSET(&ctx.Rip);
		case 9: return CALC_OFFSET(&ctx.EFlags);
		case 10: return CALC_OFFSET(&ctx.R8);
		case 11: return CALC_OFFSET(&ctx.R9);
		case 12: return CALC_OFFSET(&ctx.R10);
		case 13: return CALC_OFFSET(&ctx.R11);
		case 14: return CALC_OFFSET(&ctx.R12);
		case 15: return CALC_OFFSET(&ctx.R13);
		case 16: return CALC_OFFSET(&ctx.R14);
		case 17: return CALC_OFFSET(&ctx.R15);
		case 18: return CALC_OFFSET(&ctx.Xmm0);
		case 19: return CALC_OFFSET(&ctx.Xmm1);
		case 20: return CALC_OFFSET(&ctx.Xmm2);
		case 21: return CALC_OFFSET(&ctx.Xmm3);
		case 22: return CALC_OFFSET(&ctx.Xmm4);
		case 23: return CALC_OFFSET(&ctx.Xmm5);
		case 24: return CALC_OFFSET(&ctx.Xmm6);
		case 25: return CALC_OFFSET(&ctx.Xmm7);
		case 26: return CALC_OFFSET(&ctx.Xmm8);
		case 27: return CALC_OFFSET(&ctx.Xmm9);
		case 28: return CALC_OFFSET(&ctx.Xmm10);
		case 29: return CALC_OFFSET(&ctx.Xmm11);
		case 30: return CALC_OFFSET(&ctx.Xmm12);
		case 31: return CALC_OFFSET(&ctx.Xmm13);
		case 32: return CALC_OFFSET(&ctx.Xmm14);
		case 33: return CALC_OFFSET(&ctx.Xmm15);
		case 34: return HOOK_CONTEXT_SIZE - sizeof(Pointer);
		case 35: return HOOK_CONTEXT_SIZE - sizeof(Pointer) * 2;
		case 36: return HOOK_CONTEXT_SIZE - sizeof(Pointer) * 3;
		case 37: return CALC_OFFSET(&ctx.Rbp);
		case 38: return HOOK_CONTEXT_SIZE - sizeof(Pointer) * 4;
		case 39: return HOOK_CONTEXT_SIZE - sizeof(Pointer) * 5;
		case 40: return HOOK_CONTEXT_SIZE - sizeof(Pointer) * 6;
#else
		TODO;
#endif
		default: return -1;
		}
	}
#undef CALC_OFFSET

	EXPORT int __stdcall GetTLSIndex()
	{
		return dwTlsIndex;
	}

	EXPORT int __stdcall GetHookMaxCalls()
	{
		return HOOK_MAX_CALLS;
	}

	EXPORT int __stdcall GetHookContextSize()
	{
		return HOOK_CONTEXT_SIZE;
	}

	EXPORT void * __stdcall GetHookAllocateFail()
	{
		return HookAllocateFailed;
	}

	EXPORT void * __stdcall GetHookIntegrityFailed()
	{
		return HookVerifyError;
	}

	EXPORT void * __stdcall GetRtlCaptureContextAddress()
	{
		return RtlCaptureContext;
	}

	EXPORT void * __stdcall GetRtlRestoreContextAddress()
	{
		return RtlRestoreContext;
	}

	EXPORT void * __stdcall GetCurrentTLSValue()
	{
		return TlsGetValue(dwTlsIndex);
	}

	EXPORT int __stdcall MemoryCopy(unsigned char * source, int sourceIndex, unsigned char * destination, int destinationIndex, int length)
	{
		if (length <= 0)
			return length;

		if (sourceIndex != 0)
			source = (unsigned char*)(((Pointer)source) + sourceIndex);

		if (destinationIndex != 0)
			destination = (unsigned char*)(((Pointer)destination) + destinationIndex);

		int result = 0;
		__try
		{
			memcpy(destination, source, length);
			result = length;
		}
		__except (1)
		{
		}

		return result;
	}

	EXPORT int __stdcall MemoryReadInterlocked32(unsigned char * source, unsigned char * destination)
	{
		int result = 0;
		__try
		{
			*((unsigned int*)destination) = InterlockedCompareExchange((volatile unsigned int*)source, 0, 0);
			result = 4;
		}
		__except (1)
		{

		}
		return result;
	}

	EXPORT int __stdcall MemoryWriteInterlocked32(unsigned char * source, unsigned char * destination)
	{
		int result = 0;
		__try
		{
			*((unsigned int*)source) = InterlockedExchange((volatile unsigned int*)destination, *((unsigned int*)source));
			result = 4;
		}
		__except (1)
		{

		}
		return result;
	}

	EXPORT int __stdcall MemoryReadInterlocked64(unsigned char * source, unsigned char * destination)
	{
		int result = 0;
		__try
		{
			*((LONG64*)destination) = InterlockedCompareExchange64((volatile LONG64*)source, 0, 0);
			result = 8;
		}
		__except (1)
		{

		}
		return result;
	}

	EXPORT int __stdcall MemoryWriteInterlocked64(unsigned char * source, unsigned char * destination)
	{
		int result = 0;
		__try
		{
			*((LONG64*)source) = InterlockedExchange64((volatile LONG64*)destination, *((LONG64*)source));
			result = 8;
		}
		__except (1)
		{

		}
		return result;
	}

	EXPORT int __stdcall MemoryIncrementInterlocked32(unsigned char * source, unsigned char * destination)
	{
		int result = 0;
		__try
		{
			*((unsigned int*)source) = InterlockedIncrement((volatile unsigned int*)destination);
			result = 4;
		}
		__except (1)
		{

		}
		return result;
	}

	EXPORT int __stdcall MemoryDecrementInterlocked32(unsigned char * source, unsigned char * destination)
	{
		int result = 0;
		__try
		{
			*((unsigned int*)source) = InterlockedDecrement((volatile unsigned int*)destination);
			result = 4;
		}
		__except (1)
		{

		}
		return result;
	}

	EXPORT int __stdcall MemoryIncrementInterlocked64(unsigned char * source, unsigned char * destination)
	{
		int result = 0;
		__try
		{
			*((LONG64*)source) = InterlockedIncrement64((volatile LONG64*)destination);
			result = 8;
		}
		__except (1)
		{

		}
		return result;
	}

	EXPORT int __stdcall MemoryDecrementInterlocked64(unsigned char * source, unsigned char * destination)
	{
		int result = 0;
		__try
		{
			*((LONG64*)source) = InterlockedDecrement64((volatile LONG64*)destination);
			result = 8;
		}
		__except (1)
		{

		}
		return result;
	}

	EXPORT int __stdcall GetMemoryInfo(void * address, Pointer * resultBegin, Pointer * resultEnd, Pointer * moduleBase)
	{
		MEMORY_BASIC_INFORMATION info;
		if (VirtualQuery(address, &info, sizeof(info)) != sizeof(info))
			return 1;

		void * baseAddress = info.AllocationBase;
		if (baseAddress == NULL)
			return 2;

		IMAGE_NT_HEADERS * header = ImageNtHeader(baseAddress);
		if (header == NULL)
			return 3;

		Pointer compareAddress = (Pointer)address;

		IMAGE_SECTION_HEADER * section = (IMAGE_SECTION_HEADER*)(header + 1);
		for (WORD i = 0; i < header->FileHeader.NumberOfSections; i++)
		{
			if (memcmp(section->Name, ".text", 5) == 0)
			{
				Pointer beginAddress = (Pointer)baseAddress + (Pointer)section->VirtualAddress;
				Pointer endAddress = beginAddress + (Pointer)section->Misc.VirtualSize;

				if (compareAddress >= beginAddress && compareAddress < endAddress)
				{
					*resultBegin = beginAddress;
					*resultEnd = endAddress;
					*moduleBase = (Pointer)baseAddress;
					return 0;
				}
			}
			section++;
		}

		return -1;
	}

	EXPORT void * __stdcall Custom_RTTI_Cast(void * obj, unsigned int target, void * moduleBase)
	{
		return crtti__RTDynamicCast(obj, target, moduleBase);
	}

	EXPORT void __stdcall Explore_RTTI(void * obj, Pointer* baseObj, Pointer * data, int dataMaxCount, void * moduleBase)
	{
		crtti__Explore(obj, baseObj, data, dataMaxCount, moduleBase);
	}
}

void _ThreadStartTLS(bool allowEnterCLR)
{
	Pointer * mainStorage = (Pointer*)AllocateC(TLS_STORAGE_SIZE * sizeof(Pointer), 0);
	mainStorage[TLS_STORAGE_HOOK_CALL_COUNT] = 0;
	
	void * contextBlock = AllocateC(HOOK_CONTEXT_SIZE * (HOOK_MAX_CALLS + 1), 0);
	for (Pointer i = 0; i < (HOOK_MAX_CALLS + 1); i++)
	{
		void * contextIndex = AddPtr(contextBlock, ((int)i + 1) * HOOK_CONTEXT_SIZE - sizeof(Pointer));
		*((Pointer*)contextIndex) = i;
	}

	mainStorage[TLS_STORAGE_HOOK_CONTEXT_BLOCK] = (Pointer)contextBlock;

	mainStorage[TLS_STORAGE_EXCEPTION_DEPTH] = 0;

	TlsSetValue(dwTlsIndex, mainStorage);

	// Not allowed to enter CLR in attach :(
	/*if (allowEnterCLR)
		AttachThread();*/
}

void _ThreadStopTLS(bool allowEnterCLR)
{
	if(allowEnterCLR)
		DetachThread();

	Pointer * mainStorage = (Pointer*)TlsGetValue(dwTlsIndex);
	if (mainStorage != NULL)
	{
		void * contextBlock = (void*)mainStorage[TLS_STORAGE_HOOK_CONTEXT_BLOCK];
		if (contextBlock != NULL)
			FreeC(contextBlock, false);
	}
}

#pragma managed(pop)

private ref class FResolveHelper
{
private:
	static System::Reflection::Assembly^ _loaded = nullptr;
public:
	static System::Reflection::Assembly^ _ResolveFramework(System::Object^ sender, System::ResolveEventArgs^ args)
	{
		System::String^ fileName = args->Name;
		if (fileName->Contains(","))
			fileName = fileName->Substring(0, fileName->IndexOf(","));

		if (fileName != "NetScriptFramework")
			return nullptr;

		if (_loaded != nullptr)
			return _loaded;

		array<System::Byte>^ fileBytes = nullptr;
		array<System::Byte>^ debugBytes = nullptr;

		{
			System::IO::FileInfo^ fileInfo = gcnew System::IO::FileInfo("Data\\NetScriptFramework\\NetScriptFramework.dll");
			if (!fileInfo->Exists)
				return nullptr;

			System::IO::FileStream^ fileStream = nullptr;
			try
			{
				fileStream = fileInfo->OpenRead();
				fileBytes = gcnew array<System::Byte>((int)fileStream->Length);
				if (fileStream->Read(fileBytes, 0, fileBytes->Length) != fileBytes->Length)
					throw gcnew System::InvalidOperationException();
			}
			finally
			{
				if (fileStream != nullptr)
					fileStream->Close();
			}
		}

		{
			System::IO::FileInfo^ fileInfo = gcnew System::IO::FileInfo("Data\\NetScriptFramework\\NetScriptFramework.pdb");
			if (fileInfo->Exists)
			{
				System::IO::FileStream^ fileStream = nullptr;
				try
				{
					fileStream = fileInfo->OpenRead();
					debugBytes = gcnew array<System::Byte>((int)fileStream->Length);
					if (fileStream->Read(debugBytes, 0, debugBytes->Length) != debugBytes->Length)
						throw gcnew System::InvalidOperationException();
				}
				finally
				{
					if (fileStream != nullptr)
						fileStream->Close();
				}
			}
		}

		_loaded = debugBytes == nullptr ? System::Reflection::Assembly::Load(fileBytes) : System::Reflection::Assembly::Load(fileBytes, debugBytes);
		return _loaded;
	}
};

void InitializeEnvironment()
{
	if (initState != 0)
		return;
	initState = 1;

	is64Bit = System::IntPtr::Size != 4;

	System::AppDomain::CurrentDomain->AssemblyResolve += gcnew System::ResolveEventHandler(FResolveHelper::_ResolveFramework);
}

bool PrepareHook()
{
	return ManagedHook::Prepare();
}

bool InitializeFramework()
{
	if (initState != 1)
	{
		CriticalFail("Initialization failed! State of runtime is incorrect (%d).", initState);
		return false;
	}

	auto method = NetScriptFramework::Main::typeid->GetMethod("Initialize", System::Reflection::BindingFlags::NonPublic | System::Reflection::BindingFlags::Static);
	if (method == nullptr)
	{
		CriticalFail("Initialization failed! Main::Initialize method was not found in NetScriptFramework.dll");
		return false;
	}

	initState = 2;
	System::Object^ rsObj = method->Invoke(nullptr, gcnew array<System::Object^>(0));
	if (!System::Object::ReferenceEquals(rsObj, nullptr))
	{
		System::String^ rsMessage = safe_cast<System::String^>(rsObj);
		if (rsMessage != nullptr)
		{
			auto strPtr = System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(rsMessage);
			try
			{
				CriticalFailNoLog("Initialization failed! Main::Initialize threw an exception. See `NetScriptFramework.log.txt` file for more information. Message returned was: %s", (const char*)strPtr.ToPointer());
			}
			finally
			{
				System::Runtime::InteropServices::Marshal::FreeHGlobal(strPtr);
			}
		}
		return false;
	}
	return true;
}

bool _ShutdownFramework()
{
	// Don't report fail here, it's ok for state to not match.
	if (initState != 2)
		return false;

	auto method = NetScriptFramework::Main::typeid->GetMethod("Shutdown", System::Reflection::BindingFlags::NonPublic | System::Reflection::BindingFlags::Static);
	if (method == nullptr)
	{
		CriticalFail("Shutdown failed! Main::Shutdown method was not found in NetScriptFramework.dll");
		return false;
	}

	initState = 3;
	method->Invoke(nullptr, gcnew array<System::Object^>(0));
	return true;
}

#pragma managed(push, off)
// This is wrapped because we don't want to init CLR if state is not correct.
bool ShutdownFramework()
{
	if (initState != 2)
		return false;

	return _ShutdownFramework();
}

bool ReplaceMethod(void * target, unsigned char * data, int length)
{
	DWORD tFlags = 0;
	if (VirtualProtect(target, length, PAGE_EXECUTE_READWRITE, &tFlags))
	{
		memcpy(target, data, length);
		if (VirtualProtect(target, length, tFlags, &tFlags))
			return true;
	}

	return false;
}

bool ReplaceMethods()
{
#ifdef _WIN64
	{
		// Cdecl
		/*
		mov [rsp + 0x8], r12
		mov [rsp + 0x10], r13
		mov [rsp + 0x18], r14
		mov [rsp + 0x20], r15
		mov rax, rcx
		sub rsp, 0x108
		mov [rsp], rax
		xor rax, rax
		mov r13, rdx
		shl r13, 4
		add r13, r8
		mov r12, r8

		ProcessArgBegin:
		cmp r12, r13
		jae EndArg
		mov r14, [r12]
		mov r15, [r12+8]
		add r12, 0x10
		jmp r14

		ProcessArg:
		cmp r12, r13
		jae EndArg
		inc rax
		mov r14, [r12]
		mov r15, [r12+8]
		add r12, 0x10
		jmp r14

		DoArg0_Int: #[0x63]
		mov rcx, r15
		jmp ProcessArg

		DoArg0_Float: #[0x68]
		movss xmm0, [r12-8]
		jmp ProcessArg

		DoArg0_Double: #[0x71]
		movsd xmm0, [r12-8]
		jmp ProcessArg

		DoArg1_Int: #[0x7a]
		mov rdx, r15
		jmp ProcessArg

		DoArg1_Float: #[0x7f]
		movss xmm1, [r12-8]
		jmp ProcessArg

		DoArg1_Double: #[0x88]
		movsd xmm1, [r12-8]
		jmp ProcessArg

		DoArg2_Int: #[0x91]
		mov r8, r15
		jmp ProcessArg

		DoArg2_Float: #[0x96]
		movss xmm2, [r12-8]
		jmp ProcessArg

		DoArg2_Double: #[0x9f]
		movsd xmm2, [r12-8]
		jmp ProcessArg

		DoArg3_Int: #[0xa8]
		mov r9, r15
		jmp ProcessArg

		DoArg3_Float: #[0xad]
		movss xmm3, [r12-8]
		jmp ProcessArg

		DoArg3_Double: #[0xb6]
		movsd xmm3, [r12-8]
		jmp ProcessArg

		DoArg4: #[0xbf]
		mov [rsp+rax*8], r15
		jmp ProcessArg

		EndArg:
		mov rax, [rsp]
		call rax
		add rsp, 0x108
		mov r12, [rsp + 0x8]
		mov r13, [rsp + 0x10]
		mov r14, [rsp + 0x18]
		mov r15, [rsp + 0x20]
		ret
		*/
		{
			static unsigned char data[] = {
				0x4C, 0x89, 0x64, 0x24, 0x08, 0x4C, 0x89, 0x6C, 0x24, 0x10, 0x4C, 0x89, 0x74, 0x24, 0x18, 0x4C, 0x89, 0x7C, 0x24, 0x20, 0x48, 0x89, 0xC8, 0x48, 0x81, 0xEC, 0x08, 0x01, 0x00, 0x00, 0x48, 0x89, 0x04, 0x24, 0x48, 0x31, 0xC0, 0x49, 0x89, 0xD5, 0x49, 0xC1, 0xE5, 0x04, 0x4D, 0x01, 0xC5, 0x4D, 0x89, 0xC4, 0x4D, 0x39, 0xEC, 0x0F, 0x83, 0x8A, 0x00, 0x00, 0x00, 0x4D, 0x8B, 0x34, 0x24, 0x4D, 0x8B, 0x7C, 0x24, 0x08, 0x49, 0x83, 0xC4, 0x10, 0x41, 0xFF, 0xE6, 0x4D, 0x39, 0xEC, 0x73, 0x75, 0x48, 0xFF, 0xC0, 0x4D, 0x8B, 0x34, 0x24, 0x4D, 0x8B, 0x7C, 0x24, 0x08, 0x49, 0x83, 0xC4, 0x10, 0x41, 0xFF, 0xE6, 0x4C, 0x89, 0xF9, 0xEB, 0xE3, 0xF3, 0x41, 0x0F, 0x10, 0x44, 0x24, 0xF8, 0xEB, 0xDA, 0xF2, 0x41, 0x0F, 0x10, 0x44, 0x24, 0xF8, 0xEB, 0xD1, 0x4C, 0x89, 0xFA, 0xEB, 0xCC, 0xF3, 0x41, 0x0F, 0x10, 0x4C, 0x24, 0xF8, 0xEB, 0xC3, 0xF2, 0x41, 0x0F, 0x10, 0x4C, 0x24, 0xF8, 0xEB, 0xBA, 0x4D, 0x89, 0xF8, 0xEB, 0xB5, 0xF3, 0x41, 0x0F, 0x10, 0x54, 0x24, 0xF8, 0xEB, 0xAC, 0xF2, 0x41, 0x0F, 0x10, 0x54, 0x24, 0xF8, 0xEB, 0xA3, 0x4D, 0x89, 0xF9, 0xEB, 0x9E, 0xF3, 0x41, 0x0F, 0x10, 0x5C, 0x24, 0xF8, 0xEB, 0x95, 0xF2, 0x41, 0x0F, 0x10, 0x5C, 0x24, 0xF8, 0xEB, 0x8C, 0x4C, 0x89, 0x3C, 0xC4, 0xEB, 0x86, 0x48, 0x8B, 0x04, 0x24, 0xFF, 0xD0, 0x48, 0x81, 0xC4, 0x08, 0x01, 0x00, 0x00, 0x4C, 0x8B, 0x64, 0x24, 0x08, 0x4C, 0x8B, 0x6C, 0x24, 0x10, 0x4C, 0x8B, 0x74, 0x24, 0x18, 0x4C, 0x8B, 0x7C, 0x24, 0x20, 0xC3
			};

			if (!ReplaceMethod((void*)InvokeCdecl, data, sizeof(data)))
			{
				CriticalFail("Initialization failed! Failed to replace InvokeCdecl method.");
				return false;
			}
		}

		// CdeclF
		/*
		mov [rsp + 0x8], r12
		mov [rsp + 0x10], r13
		mov [rsp + 0x18], r14
		mov [rsp + 0x20], r15
		mov rax, rcx
		sub rsp, 0x108
		mov [rsp], rax
		xor rax, rax
		mov r13, rdx
		shl r13, 4
		add r13, r8
		mov r12, r8

		ProcessArgBegin:
		cmp r12, r13
		jge EndArg
		mov r14, [r12]
		mov r15, [r12+8]
		add r12, 0x10
		jmp r14

		ProcessArg:
		cmp r12, r13
		jge EndArg
		inc rax
		mov r14, [r12]
		mov r15, [r12+8]
		add r12, 0x10
		jmp r14

		DoArg0_Int: #[0x63]
		mov rcx, r15
		jmp ProcessArg

		DoArg0_Float: #[0x68]
		movss xmm0, [r12-8]
		jmp ProcessArg

		DoArg0_Double: #[0x71]
		movsd xmm0, [r12-8]
		jmp ProcessArg

		DoArg1_Int: #[0x7a]
		mov rdx, r15
		jmp ProcessArg

		DoArg1_Float: #[0x7f]
		movss xmm1, [r12-8]
		jmp ProcessArg

		DoArg1_Double: #[0x88]
		movsd xmm1, [r12-8]
		jmp ProcessArg

		DoArg2_Int: #[0x91]
		mov r8, r15
		jmp ProcessArg

		DoArg2_Float: #[0x96]
		movss xmm2, [r12-8]
		jmp ProcessArg

		DoArg2_Double: #[0x9f]
		movsd xmm2, [r12-8]
		jmp ProcessArg

		DoArg3_Int: #[0xa8]
		mov r9, r15
		jmp ProcessArg

		DoArg3_Float: #[0xad]
		movss xmm3, [r12-8]
		jmp ProcessArg

		DoArg3_Double: #[0xb6]
		movsd xmm3, [r12-8]
		jmp ProcessArg

		DoArg4: #[0xbf]
		mov [rsp+rax*8], r15
		jmp ProcessArg

		EndArg:
		mov rax, [rsp]
		call rax
		add rsp, 0x108
		mov r12, [rsp + 0x8]
		mov r13, [rsp + 0x10]
		mov r14, [rsp + 0x18]
		mov r15, [rsp + 0x20]
		movss [rsp+8], xmm0
		mov rax, [rsp+8]
		ret
		*/
		{
			static unsigned char data[] = {
				0x4C, 0x89, 0x64, 0x24, 0x08, 0x4C, 0x89, 0x6C, 0x24, 0x10, 0x4C, 0x89, 0x74, 0x24, 0x18, 0x4C, 0x89, 0x7C, 0x24, 0x20, 0x48, 0x89, 0xC8, 0x48, 0x81,
				0xEC, 0x08, 0x01, 0x00, 0x00, 0x48, 0x89, 0x04, 0x24, 0x48, 0x31, 0xC0, 0x49, 0x89, 0xD5, 0x49, 0xC1, 0xE5, 0x04, 0x4D, 0x01, 0xC5, 0x4D, 0x89, 0xC4,
				0x4D, 0x39, 0xEC, 0x0F, 0x8D, 0x8A, 0x00, 0x00, 0x00, 0x4D, 0x8B, 0x34, 0x24, 0x4D, 0x8B, 0x7C, 0x24, 0x08, 0x49, 0x83, 0xC4, 0x10, 0x41, 0xFF, 0xE6,
				0x4D, 0x39, 0xEC, 0x7D, 0x75, 0x48, 0xFF, 0xC0, 0x4D, 0x8B, 0x34, 0x24, 0x4D, 0x8B, 0x7C, 0x24, 0x08, 0x49, 0x83, 0xC4, 0x10, 0x41, 0xFF, 0xE6, 0x4C,
				0x89, 0xF9, 0xEB, 0xE3, 0xF3, 0x41, 0x0F, 0x10, 0x44, 0x24, 0xF8, 0xEB, 0xDA, 0xF2, 0x41, 0x0F, 0x10, 0x44, 0x24, 0xF8, 0xEB, 0xD1, 0x4C, 0x89, 0xFA,
				0xEB, 0xCC, 0xF3, 0x41, 0x0F, 0x10, 0x4C, 0x24, 0xF8, 0xEB, 0xC3, 0xF2, 0x41, 0x0F, 0x10, 0x4C, 0x24, 0xF8, 0xEB, 0xBA, 0x4D, 0x89, 0xF8, 0xEB, 0xB5,
				0xF3, 0x41, 0x0F, 0x10, 0x54, 0x24, 0xF8, 0xEB, 0xAC, 0xF2, 0x41, 0x0F, 0x10, 0x54, 0x24, 0xF8, 0xEB, 0xA3, 0x4D, 0x89, 0xF9, 0xEB, 0x9E, 0xF3, 0x41,
				0x0F, 0x10, 0x5C, 0x24, 0xF8, 0xEB, 0x95, 0xF2, 0x41, 0x0F, 0x10, 0x5C, 0x24, 0xF8, 0xEB, 0x8C, 0x4C, 0x89, 0x3C, 0xC4, 0xEB, 0x86, 0x48, 0x8B, 0x04,
				0x24, 0xFF, 0xD0, 0x48, 0x81, 0xC4, 0x08, 0x01, 0x00, 0x00, 0x4C, 0x8B, 0x64, 0x24, 0x08, 0x4C, 0x8B, 0x6C, 0x24, 0x10, 0x4C, 0x8B, 0x74, 0x24, 0x18,
				0x4C, 0x8B, 0x7C, 0x24, 0x20, 0xF3, 0x0F, 0x11, 0x44, 0x24, 0x08, 0x48, 0x8B, 0x44, 0x24, 0x08, 0xC3
			};

			if(!ReplaceMethod((void*)InvokeCdeclF, data, sizeof(data)))
			{
				CriticalFail("Initialization failed! Failed to replace InvokeCdeclF method.");
				return false;
			}
		}

		// CdeclD
		/*
		mov [rsp + 0x8], r12
		mov [rsp + 0x10], r13
		mov [rsp + 0x18], r14
		mov [rsp + 0x20], r15
		mov rax, rcx
		sub rsp, 0x108
		mov [rsp], rax
		xor rax, rax
		mov r13, rdx
		shl r13, 4
		add r13, r8
		mov r12, r8

		ProcessArgBegin:
		cmp r12, r13
		jge EndArg
		mov r14, [r12]
		mov r15, [r12+8]
		add r12, 0x10
		jmp r14

		ProcessArg:
		cmp r12, r13
		jge EndArg
		inc rax
		mov r14, [r12]
		mov r15, [r12+8]
		add r12, 0x10
		jmp r14

		DoArg0_Int: #[0x63]
		mov rcx, r15
		jmp ProcessArg

		DoArg0_Float: #[0x68]
		movss xmm0, [r12-8]
		jmp ProcessArg

		DoArg0_Double: #[0x71]
		movsd xmm0, [r12-8]
		jmp ProcessArg

		DoArg1_Int: #[0x7a]
		mov rdx, r15
		jmp ProcessArg

		DoArg1_Float: #[0x7f]
		movss xmm1, [r12-8]
		jmp ProcessArg

		DoArg1_Double: #[0x88]
		movsd xmm1, [r12-8]
		jmp ProcessArg

		DoArg2_Int: #[0x91]
		mov r8, r15
		jmp ProcessArg

		DoArg2_Float: #[0x96]
		movss xmm2, [r12-8]
		jmp ProcessArg

		DoArg2_Double: #[0x9f]
		movsd xmm2, [r12-8]
		jmp ProcessArg

		DoArg3_Int: #[0xa8]
		mov r9, r15
		jmp ProcessArg

		DoArg3_Float: #[0xad]
		movss xmm3, [r12-8]
		jmp ProcessArg

		DoArg3_Double: #[0xb6]
		movsd xmm3, [r12-8]
		jmp ProcessArg

		DoArg4: #[0xbf]
		mov [rsp+rax*8], r15
		jmp ProcessArg

		EndArg:
		mov rax, [rsp]
		call rax
		add rsp, 0x108
		mov r12, [rsp + 0x8]
		mov r13, [rsp + 0x10]
		mov r14, [rsp + 0x18]
		mov r15, [rsp + 0x20]
		movsd [rsp+8], xmm0
		mov rax, [rsp+8]
		ret
		*/
		{
			static unsigned char data[] = {
				0x4C, 0x89, 0x64, 0x24, 0x08, 0x4C, 0x89, 0x6C, 0x24, 0x10, 0x4C, 0x89, 0x74, 0x24, 0x18, 0x4C, 0x89, 0x7C, 0x24, 0x20, 0x48, 0x89, 0xC8, 0x48, 0x81,
				0xEC, 0x08, 0x01, 0x00, 0x00, 0x48, 0x89, 0x04, 0x24, 0x48, 0x31, 0xC0, 0x49, 0x89, 0xD5, 0x49, 0xC1, 0xE5, 0x04, 0x4D, 0x01, 0xC5, 0x4D, 0x89, 0xC4,
				0x4D, 0x39, 0xEC, 0x0F, 0x8D, 0x8A, 0x00, 0x00, 0x00, 0x4D, 0x8B, 0x34, 0x24, 0x4D, 0x8B, 0x7C, 0x24, 0x08, 0x49, 0x83, 0xC4, 0x10, 0x41, 0xFF, 0xE6,
				0x4D, 0x39, 0xEC, 0x7D, 0x75, 0x48, 0xFF, 0xC0, 0x4D, 0x8B, 0x34, 0x24, 0x4D, 0x8B, 0x7C, 0x24, 0x08, 0x49, 0x83, 0xC4, 0x10, 0x41, 0xFF, 0xE6, 0x4C,
				0x89, 0xF9, 0xEB, 0xE3, 0xF3, 0x41, 0x0F, 0x10, 0x44, 0x24, 0xF8, 0xEB, 0xDA, 0xF2, 0x41, 0x0F, 0x10, 0x44, 0x24, 0xF8, 0xEB, 0xD1, 0x4C, 0x89, 0xFA,
				0xEB, 0xCC, 0xF3, 0x41, 0x0F, 0x10, 0x4C, 0x24, 0xF8, 0xEB, 0xC3, 0xF2, 0x41, 0x0F, 0x10, 0x4C, 0x24, 0xF8, 0xEB, 0xBA, 0x4D, 0x89, 0xF8, 0xEB, 0xB5,
				0xF3, 0x41, 0x0F, 0x10, 0x54, 0x24, 0xF8, 0xEB, 0xAC, 0xF2, 0x41, 0x0F, 0x10, 0x54, 0x24, 0xF8, 0xEB, 0xA3, 0x4D, 0x89, 0xF9, 0xEB, 0x9E, 0xF3, 0x41,
				0x0F, 0x10, 0x5C, 0x24, 0xF8, 0xEB, 0x95, 0xF2, 0x41, 0x0F, 0x10, 0x5C, 0x24, 0xF8, 0xEB, 0x8C, 0x4C, 0x89, 0x3C, 0xC4, 0xEB, 0x86, 0x48, 0x8B, 0x04,
				0x24, 0xFF, 0xD0, 0x48, 0x81, 0xC4, 0x08, 0x01, 0x00, 0x00, 0x4C, 0x8B, 0x64, 0x24, 0x08, 0x4C, 0x8B, 0x6C, 0x24, 0x10, 0x4C, 0x8B, 0x74, 0x24, 0x18,
				0x4C, 0x8B, 0x7C, 0x24, 0x20, 0xF2, 0x0F, 0x11, 0x44, 0x24, 0x08, 0x48, 0x8B, 0x44, 0x24, 0x08
			};

			if (!ReplaceMethod((void*)InvokeCdeclD, data, sizeof(data)))
			{
				CriticalFail("Initialization failed! Failed to replace InvokeCdeclD method.");
				return false;
			}
		}

		// ReadDQFrom
		/*
		movdqu xmm0, [rcx]
		movsd [rdx], xmm0
		ret
		*/
		{
			static unsigned char data[] = {
				0xF3, 0x0F, 0x6F, 0x01, 0xF2, 0x0F, 0x11, 0x02, 0xC3
			};

			if(!ReplaceMethod((void*)ReadDQFrom, data, sizeof(data)))
			{
				CriticalFail("Initialization failed! Failed to replace ReadDQFrom method.");
				return false;
			}
		}

		// WriteDQTo
		/*
		movsd xmm0, [rcx]
		movdqu [rdx], xmm0
		ret
		*/
		{
			static unsigned char data[] = {
				0xF2, 0x0F, 0x10, 0x01, 0xF3, 0x0F, 0x7F, 0x02, 0xC3
			};

			if(!ReplaceMethod((void*)WriteDQTo, data, sizeof(data)))
			{
				CriticalFail("Initialization failed! Failed to replace WriteDQTo method.");
				return false;
			}
		}

		// ReadFQFrom
		/*
		movdqu xmm0, [rcx]
		movss [rdx], xmm0
		ret
		*/
		{
			static unsigned char data[] = {
				0xF3, 0x0F, 0x6F, 0x01, 0xF3, 0x0F, 0x11, 0x02, 0xC3
			};

			if (!ReplaceMethod((void*)ReadFQFrom, data, sizeof(data)))
			{
				CriticalFail("Initialization failed! Failed to replace ReadFQFrom method.");
				return false;
			}
		}

		// WriteFQTo
		/*
		movss xmm0, [rcx]
		movdqu [rdx], xmm0
		ret
		*/
		{
			static unsigned char data[] = {
				0xF3, 0x0F, 0x10, 0x01, 0xF3, 0x0F, 0x7F, 0x02, 0xC3
			};

			if (!ReplaceMethod((void*)WriteFQTo, data, sizeof(data)))
			{
				CriticalFail("Initialization failed! Failed to replace WriteFQTo method.");
				return false;
			}
		}
	}
#else
	{
		// InvokeThisCall
		{
			static unsigned char data[] = {
				TODO
			};

			if(!ReplaceMethod((void*)InvokeThisCall, data, sizeof(data)))
			{
				CriticalFail("Initialization failed! Failed to replace InvokeThisCall method.");
				return false;
			}
		}

		// InvokeThisCallF
		{
			static unsigned char data[] = {
				TODO
			};

			if(!ReplaceMethod((void*)InvokeThisCallF, data, sizeof(data)))
			{
				CriticalFail("Initialization failed! Failed to replace InvokeThisCallF method.");
				return false;
			}
		}

		// InvokeCdecl
		{
			static unsigned char data[] = {
				TODO
			};

			if(!ReplaceMethod((void*)InvokeCdecl, data, sizeof(data)))
			{
				CriticalFail("Initialization failed! Failed to replace InvokeCdecl method.");
				return false;
			}
		}

		// InvokeCdeclF
		{
			static unsigned char data[] = {
				TODO
			};

			if(!ReplaceMethod((void*)InvokeCdeclF, data, sizeof(data)))
			{
				CriticalFail("Initialization failed! Failed to replace InvokeCdeclF method.");
				return false;
			}
		}

		// ReadDQFrom
		/*
		mov eax, [esp+4]
		mov ecx, [esp+8]
		movdqu xmm0, [eax]
		movsd [ecx], xmm0
		ret
		*/
		{
			static unsigned char data[] = {
				0x8B, 0x44, 0x24, 0x04, 0x8B, 0x4C, 0x24, 0x08, 0xF3, 0x0F, 0x6F, 0x00, 0xF2, 0x0F, 0x11, 0x01, 0xC3
			};

			if(!ReplaceMethod((void*)ReadDQFrom, data, sizeof(data)))
			{
				CriticalFail("Initialization failed! Failed to replace ReadDQFrom method.");
				return false;
			}
		}

		// WriteDQTo
		/*
		mov eax, [esp+4]
		mov ecx, [esp+8]
		movsd xmm0, [eax]
		movdqu [ecx], xmm0
		ret
		*/
		{
			static unsigned char data[] = {
				0x8B, 0x44, 0x24, 0x04, 0x8B, 0x4C, 0x24, 0x08, 0xF2, 0x0F, 0x10, 0x00, 0xF3, 0x0F, 0x7F, 0x01, 0xC3
			};

			if(!ReplaceMethod((void*)WriteDQTo, data, sizeof(data)))
			{
				CriticalFail("Initialization failed! Failed to replace WriteDQTo method.");
				return false;
			}
		}
	}
#endif

	return true;
}
#pragma managed(pop)

bool handle_crash(EXCEPTION_POINTERS * ep)
{
	if (ManagedHook::_exceptionPtr == nullptr)
		return false;

	auto cpu = NetScriptFramework::Tools::_Internal::RTHandler::_Allocate(System::IntPtr((void*)ep->ContextRecord));

	auto args = gcnew array<System::Object^>(1);
	args[0] = cpu;
	bool try_continue = safe_cast<bool>(ManagedHook::_exceptionPtr->Invoke(nullptr, args));

	NetScriptFramework::Tools::_Internal::RTHandler::_Free(cpu);

	return try_continue;
}

void DEBUG_Write(const char * msg)
{
	auto str = gcnew System::String(msg);
	NetScriptFramework::Main::Log->AppendLine(str);
}

#pragma managed(push, off)
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		if ((dwTlsIndex = TlsAlloc()) == TLS_OUT_OF_INDEXES)
			return FALSE;
		_ThreadStartTLS(false);
		break;

	case DLL_THREAD_ATTACH:
		_ThreadStartTLS(true);
		break;

	case DLL_THREAD_DETACH:
		_ThreadStopTLS(true);
		break;

	case DLL_PROCESS_DETACH:
		// Not allowed to enter CLR here or crash. Instead we now use AppDomain ProcessExit event.
		//ShutdownFramework();

		// This is allowed but it's unnecessary because process is exiting anyway.
		//_ThreadStopTLS(false);
		//TlsFree(dwTlsIndex);
		break;

	default:
		break;
	}

	return TRUE;
}

bool try_handle_crash(EXCEPTION_POINTERS * info)
{
	bool shouldContinue = false;
	//__try
	{
		shouldContinue = handle_crash(info);
	}
	/*__except (1)
	{
		shouldContinue = false;
	}*/

	return shouldContinue;
}

LPTOP_LEVEL_EXCEPTION_FILTER _original_exception_filter = NULL;

LONG WINAPI ExceptionFilter(EXCEPTION_POINTERS * info)
{
	Pointer * depth = GetExceptionDepthPointer();
	
	bool handled = false;
	if (depth != NULL)
	{
		Pointer vdep = *depth;
		if (vdep == 0)
		{
			*depth = *depth + 1;
			handled = try_handle_crash(info);
			*depth = *depth - 1;
		}
	}

	if (handled)
		return EXCEPTION_CONTINUE_EXECUTION;

	if (_original_exception_filter != NULL)
		return _original_exception_filter(info);

	return EXCEPTION_CONTINUE_SEARCH;
}

LONG WINAPI CheckFilter(EXCEPTION_POINTERS * info)
{
	auto prev = SetUnhandledExceptionFilter(ExceptionFilter);
	if (prev == NULL)
		_original_exception_filter = NULL;
	else if (prev != ExceptionFilter)
		_original_exception_filter = prev;

	return EXCEPTION_CONTINUE_SEARCH;
}

extern "C"
{
	EXPORT void __cdecl Initialize()
	{
		// Initialize environment info.
		InitializeEnvironment();

		// Prepare managed code hooking.
		if (!PrepareHook())
			return;

		// Replace invoke methods.
		if (!ReplaceMethods())
			return;

		// Initialize the managed framework.
		if (!InitializeFramework())
			return;

		// Set up exception handler after framework has initialized.
		AddVectoredExceptionHandler(1, CheckFilter);
	}

	EXPORT int __stdcall GetRuntimeVersion()
	{
		return RUNTIME_VERSION;
	}
}
#pragma managed(pop)
