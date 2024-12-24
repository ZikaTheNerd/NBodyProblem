#include "VertexFragmentShader.h"

VertexFragmentShader::VertexFragmentShader(std::string &vertexShaderPath, std::string &fragmentShaderPath) {
    const std::string vertexShaderCode = readFileToString(vertexShaderPath);
    const std::string fragmentShaderCode = readFileToString(fragmentShaderPath);

    const unsigned int vertexShaderId = compileShader(GL_VERTEX_SHADER, vertexShaderCode);
    const unsigned int fragmentShaderId = compileShader(GL_FRAGMENT_SHADER, fragmentShaderCode);

    ID = glCreateProgram();
    glAttachShader(ID, vertexShaderId);
    glAttachShader(ID, fragmentShaderId);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
}

