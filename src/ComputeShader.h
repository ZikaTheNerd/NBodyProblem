#pragma once
#include <string>

#include "Shader.h"

class ComputeShader : public Shader {
public:
    ComputeShader(std::string &computeShaderPath);
};
