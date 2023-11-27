#include "engine/rendering/Shader.h"
#include "engine/Assets.h"
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>


namespace ChunkMapEngine {
    struct glStatusData {
        int success;
        const char *shaderName;
        char infoLog[GL_INFO_LOG_LENGTH];
    };

    Shader::Shader(const fs::path &vertexShaderPath, const fs::path &fragmentShaderPath) {
        vertexShader = loadAndCompileShader(GL_VERTEX_SHADER, vertexShaderPath);
        fragmentShader = loadAndCompileShader(GL_FRAGMENT_SHADER, fragmentShaderPath);
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        glDetachShader(shaderProgram, vertexShader);
        glDetachShader(shaderProgram, fragmentShader);
    }

    unsigned int Shader::loadAndCompileShader(GLuint shaderType, const fs::path &shaderPath) {
        auto shaderSource = readText(shaderPath);
        auto source = shaderSource.c_str();
        auto shaderID = glCreateShader(shaderType);
        glShaderSource(shaderID, 1, &source, nullptr);
        glCompileShader(shaderID);

        glStatusData compilationStatus{};
        compilationStatus.shaderName = shaderType == GL_VERTEX_SHADER ? "Vertex" : "Fragment";
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compilationStatus.success);
        if(compilationStatus.success == GL_FALSE) {
            glGetShaderInfoLog(shaderID, GL_INFO_LOG_LENGTH, nullptr, compilationStatus.infoLog);
            throw std::runtime_error("ERROR: " + std::string(compilationStatus.shaderName) + " shader compilation failed.\n" +
                                     std::string(compilationStatus.infoLog));
        }

        return shaderID;
    }

    std::string Shader::readText(const fs::path &filePath) {
        std::ifstream sourceFile(resolveAssetPath(filePath));
        std::stringstream buffer;
        buffer << sourceFile.rdbuf();
        return buffer.str();
    }
    
    void Shader::setFloat(const std::string& uniformName, float value, bool useShader)
    {
        if (useShader)
            this->use();
        glUniform1f(glGetUniformLocation(this->shaderProgram, uniformName.c_str()), value);
    }

    void Shader::setInteger(const std::string& uniformName, int value, bool useShader)
    {
        if (useShader)
            this->use();
        glUniform1i(glGetUniformLocation(this->shaderProgram, uniformName.c_str()), value);
    }

    void Shader::setVector2(const std::string& uniformName, float x, float y, bool useShader)
    {
        if (useShader)
            this->use();
        glUniform2f(glGetUniformLocation(this->shaderProgram, uniformName.c_str()), x, y);
    }

    void Shader::setVector2(const std::string& uniformName, const glm::vec2& value, bool useShader)
    {
        if (useShader)
            this->use();
        glUniform2f(glGetUniformLocation(this->shaderProgram, uniformName.c_str()), value.x, value.y);
    }

    void Shader::setVector3(const std::string& uniformName, float x, float y, float z, bool useShader)
    {
        if (useShader)
            this->use();
        glUniform3f(glGetUniformLocation(this->shaderProgram, uniformName.c_str()), x, y, z);
    }

    void Shader::setVector3(const std::string& uniformName, const glm::vec3& value, bool useShader)
    {
        if (useShader)
            this->use();
        glUniform3f(glGetUniformLocation(this->shaderProgram, uniformName.c_str()), value.x, value.y, value.z);
    }

    void Shader::setVector4(const std::string& uniformName, float x, float y, float z, float w, bool useShader)
    {
        if (useShader)
            this->use();
        glUniform4f(glGetUniformLocation(this->shaderProgram, uniformName.c_str()), x, y, z, w);
    }

    void Shader::setVector4(const std::string& uniformName, glm::vec4 vector, bool useShader) 
    {
        if (useShader)
            this->use();
        glUniform4fv(glGetUniformLocation(shaderProgram, uniformName.c_str()), 1, glm::value_ptr(vector));
    }

    void Shader::setMatrix(const std::string &uniformName, glm::mat4 matrix, bool useShader)
    {
        if (useShader)
            this->use();
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, uniformName.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Shader::setTexture(const std::string& uniformName, unsigned int id, bool useShader)
    {
        if (useShader)
            this->use();
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, id);
        //glUniform1i(glGetUniformLocation(shaderProgram, uniformName.c_str()), id);
    }

    Shader &Shader::use() {
        glUseProgram(shaderProgram);
        return *this;
    }

    Shader::~Shader() {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
}
