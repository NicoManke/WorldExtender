#pragma once

#include <string>
#include <filesystem>
#include "glad/glad.h"
#include "glm/glm.hpp"

namespace fs = std::filesystem;

namespace ChunkMapEngine {
    /// Shader represents a shader programm running on the GPU that is used to modify the rendering process of drawn objects.
    class Shader {
    public:
        Shader() { };
        Shader(const fs::path &vertexShaderPath, const fs::path &fragmentShaderPath);
        virtual ~Shader();

        Shader(const Shader& shader) = default;

        Shader(Shader && shader) noexcept {
            std::swap(this->shaderProgram, shader.shaderProgram);
            std::swap(this->vertexShader, shader.vertexShader);
            std::swap(this->fragmentShader, shader.fragmentShader);
        }

        Shader& operator=(Shader& shader) = default;

        /// modifies a shader programm's uniform of type Float.
        void setFloat(const std::string& uniformName, float value, bool useShader = false);
        /// modifies a shader programm's uniform of type Integer.
        void setInteger(const std::string& uniformName, int value, bool useShader = false);
        /// modifies a shader programm's uniform of type Vector2.
        void setVector2(const std::string& uniformName, float x, float y, bool useShader = false);
        /// modifies a shader programm's uniform of type Vector2.
        void setVector2(const std::string& uniformName, const glm::vec2& value, bool useShader = false);
        /// modifies a shader programm's uniform of type Vector3.
        void setVector3(const std::string& uniformName, float x, float y, float z, bool useShader = false);
        /// modifies a shader programm's uniform of type Vector3.
        void setVector3(const std::string& uniformName, const glm::vec3& value, bool useShader = false);
        /// modifies a shader programm's uniform of type Vector4.
        void setVector4(const std::string& uniformName, float x, float y, float z, float w, bool useShader = false);
        /// modifies a shader programm's uniform of type Vector4.
        void setVector4(const std::string& uniformName, glm::vec4 vector, bool useShader = false);
        /// modifies a shader programm's uniform of type Matrix.
        void setMatrix(const std::string& uniformName, glm::mat4 matrix, bool useShader = false);
        /// modifies a shader programm's uniform of type Texture.
        void setTexture(const std::string& uniformName, unsigned int id, bool useShader = false);
        ///  activates the shader programm for usage and returns an optional reference of the Shader object.
        Shader& use();

    private:
        unsigned int loadAndCompileShader(GLuint shaderType, const fs::path &shaderPath);
        std::string readText(const fs::path &filePath);

        unsigned int shaderProgram = 0;
        unsigned int vertexShader = 0;
        unsigned int fragmentShader = 0;
    };
}


