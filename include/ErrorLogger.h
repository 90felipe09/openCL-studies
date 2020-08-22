#pragma once
#include "CL/cl.h"

#define ASSERT(x) if(!(x)) __builtin_trap();
#define CLCall(x) cl_int ERROR_CODE = x;\
    ASSERT(CLLogCall(#x, __FILE__, __LINE__, ERROR_CODE))

bool CLLogCall(const char* function, const char* file, int line, cl_int err);