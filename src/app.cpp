#include <iostream>
#include <time.h>

#include "KernelParser.h"
#include "ErrorLogger.h"

#define DATA_SIZE 1000
#define PROBLEM_DIMENSION 1

int main(void){
    // Resources Aquisition
    cl_uint numOfPlatforms = 0;
    cl_platform_id platformId;

    cl_uint numOfDevices = 0;
    cl_device_id deviceId;
    
    CLCall(clGetPlatformIDs(1, &platformId, &numOfPlatforms));
    std::cout << "platformId is: " << platformId << std::endl;
    std::cout << "numOfPlatforms is: " << numOfPlatforms << std::endl;

    CLCall(clGetDeviceIDs(platformId, CL_DEVICE_TYPE_GPU, 1, &deviceId, &numOfDevices));
    std::cout << "deviceId is: " << deviceId << std::endl;
    std::cout << "numOfDevices is: " << numOfDevices << std::endl;
    
    // Context creation
    cl_int execution_error_code;
    cl_context context;
    cl_context_properties properties[3];

    properties[0] = CL_CONTEXT_PLATFORM;
    properties[1] = (cl_context_properties) platformId;
    properties[2] = 0;

    context = clCreateContext(properties, numOfDevices, &deviceId, NULL, NULL, &execution_error_code);
    std::cout << "context is: " << context << std::endl;
    std::cout << "execution_error_code is: " << execution_error_code << std::endl;


    // Program Objects creation
    cl_program program;
    cl_kernel kernel;
    const std::string kernelSource = ParseKernel("../assets/addVector.kernel");
    std::cout << "kernelSource is: \n" << kernelSource << std::endl;

    program = clCreateProgramWithSource(context, 1, (const char **) &kernelSource, NULL, &execution_error_code);
    std::cout << "program is: " << program << std::endl;
    std::cout << "execution_error_code is: " << execution_error_code << std::endl;

    CLCall(clBuildProgram(program, 0, NULL, NULL, NULL, NULL));

    kernel = clCreateKernel(program, "addVector", &execution_error_code);
    std::cout << "kernel is: " << kernel << std::endl;
    std::cout << "execution_error_code is: " << execution_error_code << std::endl;

    // Memory Objects creation
    cl_mem vectorA, vectorB, outputVector;
    cl_command_queue command_queue = clCreateCommandQueue(context, deviceId, 0, &execution_error_code);

    float inputData[DATA_SIZE] = {0};
    float results[DATA_SIZE] = {0};

    for(int index = 0; index < DATA_SIZE; index++){
        inputData[index] = index + 1;
    }

    vectorA = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(float) * DATA_SIZE, NULL, NULL);
    vectorB = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(float) * DATA_SIZE, NULL, NULL);
    outputVector = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * DATA_SIZE, NULL, NULL);

    CLCall(clEnqueueWriteBuffer(command_queue, vectorA, CL_TRUE, 0, sizeof(float) * DATA_SIZE, inputData, 0, NULL, NULL));
    CLCall(clEnqueueWriteBuffer(command_queue, vectorB, CL_TRUE, 0, sizeof(float) * DATA_SIZE, inputData, 0, NULL, NULL));

    CLCall(clSetKernelArg(kernel, 0, sizeof(cl_mem), &vectorA));
    CLCall(clSetKernelArg(kernel, 1, sizeof(cl_mem), &vectorB));
    CLCall(clSetKernelArg(kernel, 2, sizeof(cl_mem), &outputVector));

    // Execution, tests and memory releases
    clock_t timeToGPU, timeToCPU;

    size_t global = DATA_SIZE;
    CLCall(clEnqueueNDRangeKernel(command_queue, kernel, PROBLEM_DIMENSION, NULL, &global, NULL, 0, NULL, NULL));
    
    timeToGPU = clock();
    CLCall(clFinish(command_queue));
    timeToGPU = clock() - timeToGPU;
    double timeTakenGPU = ((double) timeToGPU)/CLOCKS_PER_SEC;

    CLCall(clEnqueueReadBuffer(command_queue, outputVector, CL_TRUE, 0, sizeof(float) * DATA_SIZE, results, 0, NULL, NULL));

    std::cout << "GPU Output:" << std::endl;
    for(int i = 0; i < DATA_SIZE; i++){
        std::cout << results[i] << std::endl;
    }
    std::cout << "GPU time taken:" << timeTakenGPU << std::endl;

    clReleaseMemObject(vectorA);
    clReleaseMemObject(vectorB);
    clReleaseMemObject(outputVector);

    clReleaseProgram(program);
    
    clReleaseKernel(kernel);

    clReleaseCommandQueue(command_queue);

    clReleaseContext(context);
    return 0;
}