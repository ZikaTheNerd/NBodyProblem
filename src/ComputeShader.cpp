#include "ComputeShader.h"

ComputeShader::ComputeShader(std::string &computeShaderPath) {
    std::string computeShaderCode = readFileToString(computeShaderPath);
    unsigned int shaderId = compileShader(GL_COMPUTE_SHADER, computeShaderCode);

    ID = glCreateProgram();
    glAttachShader(ID, shaderId);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    glDeleteShader(shaderId);
}

