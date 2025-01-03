#pragma once

#include <string>
#include <glm/glm.hpp>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class Shader {
public:
    // Shader ID
    unsigned int ID;

    virtual ~Shader();


    Shader();

    /**
     *  Aktivira shader - program za izvrsavanje na grafickoj kartici
     */
    void use() const;

    // Uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string &name, bool value) const;

    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const;

    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) const;

    // ------------------------------------------------------------------------
    void setVec2(const std::string &name, const glm::vec2 &value) const;

    void setVec2(const std::string &name, float x, float y) const;


    // ------------------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value) const;

    void setVec3(const std::string &name, float x, float y, float z) const;

    // ------------------------------------------------------------------------
    void setVec4(const std::string &name, const glm::vec4 &value) const;

    void setVec4(const std::string &name, float x, float y, float z, float w) const;

    // ------------------------------------------------------------------------
    void setMat2(const std::string &name, const glm::mat2 &mat) const;

    // ------------------------------------------------------------------------
    void setMat3(const std::string &name, const glm::mat3 &mat) const;

    // ------------------------------------------------------------------------
    void setMat4(const std::string &name, const glm::mat4 &mat) const;

protected:
    /**
    * Proverava da li je doslo do gresaka u linkovanju
    *
    * @param shader Shader object.
    * @param type The type of the shader object ("VERTEX", "FRAGMENT", "PROGRAM", etc.) to use in the error messages.
    */
    void checkCompileErrors(unsigned int shader, std::string &&type);

    /**
    * This function fixes path separators in the given string to be compatible with the current operating system.
    * On Windows, it replaces forward slashes with backslashes.
    * @param path The path to fix the separators of.
    */
    std::string fixPathSeparators(const std::string &path);


    /**
    * This function compiles a shader of the specified type with the given code.
    * @param shaderType The type of shader (e.g., GL_VERTEX_SHADER, GL_COMPUTE_SHADER).
    * @param code The source code of the shader.
    * @return The ID of the compiled shader.
    */
    unsigned int compileShader(GLuint shaderType, const std::string &code);

    /**
    * Reads a file and returns its contents as a string.
    *
    * @param filePath the path to the file to be read.
    * @return the contents of the file as a string.
    */
    std::string readFileToString(std::string &filePath);
};
