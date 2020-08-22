#include <iostream>
#include "CL/cl.h"

#include "KernelParser.h"
#include "ErrorLogger.h"

#define DATA_SIZE 10

int main(void){
    cl_uint numOfPlatforms = 0;
    cl_platform_id platformId;
    cl_device_id deviceId;
    cl_uint numOfDevices = 0;

    CLCall(clGetPlatformIDs(1, &platformId, &numOfPlatforms));
    std::cout << "platformId is: " << platformId << std::endl;
    std::cout << "numOfPlatforms is: " << numOfPlatforms << std::endl;

    CLCall(clGetDeviceIDs(platformId, CL_DEVICE_TYPE_GPU, 1, &deviceId, &numOfDevices));
    std::cout << "deviceId is: " << deviceId << std::endl;
    std::cout << "numOfDevices is: " << numOfDevices << std::endl;
    
}