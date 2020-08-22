#pragma once

#include <fstream>
#include <sstream>
#include "CL/cl.h"

std::stringstream ParseKernel(const std::string& kernelFile);