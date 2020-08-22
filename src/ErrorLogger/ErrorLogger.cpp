#include "ErrorLogger.h"
#include <iostream>

bool CLLogCall(const char* function, const char* file, int line, cl_int err){
    if(err != CL_SUCCESS){
        std::cout << "[OpenCL Error] (" << err << "): " << function << " " << file
        << ":" << line << std::endl;
        return false;
    }
    return true;
}