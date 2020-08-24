#include "KernelParser.h"

std::string ParseKernel(const std::string& kernelFile){
    std::ifstream stream(kernelFile);
    std::string line;
    std::stringstream ss;

    while(getline(stream, line)){
        ss << line << "\n";
    }

    return ss.str();
}
