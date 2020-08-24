#pragma once
#include "CL/cl.h"

#define ASSERT(x) if(!(x)) __builtin_trap();
#define CLCall(x) ASSERT(CLLogCall(#x, __FILE__, __LINE__, x));

bool CLLogCall(const char* function, const char* file, int line, cl_int err);
