#pragma once

#include <string>

#include "Shader.h"

class VertexFragmentShader : public Shader {
    VertexFragmentShader(std::string &vertexShaderPath, std::string &fragmentShaderPath);
};



