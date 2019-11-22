// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#include <Windows.h>
#include <DbgHelp.h>
#include <vector>
#include <fstream>
#include <unordered_map>

typedef long long int64;
#ifdef _WIN64
typedef int64 Pointer;
#else
typedef int Pointer;
#endif

#include "ReplaceImport.h"
