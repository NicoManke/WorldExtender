#include "engine/rendering/Texture.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "engine/Assets.h"
#include "engine/rendering/stbimage/load_stb_image.h"
#include <iostream>
#include "engine/Logger.h"
#include "engine/Settings.h"

namespace ChunkMapEngine {
	Texture::Texture(std::string fileName) {
        initTexture(fileName);
	}

    Texture::Texture(std::string fileName, std::vector<int> animationFrameCounts, std::vector<float> animationDurations) {
        initTexture(fileName);
        this->frameCount = animationFrameCounts;
        this->animationDuration = animationDurations;
        auto animCount = height / SPRITE_SIZE;
        if (animCount != frameCount.size()) {
            std::cout << "Error: texture height doesn't match the length of the given parameter vectors." << std::endl;
        }
        this->animationCount = animCount;
    }
    
    void Texture::initTexture(std::string fileName) {
        width = height = 0;
        int width, height, nrChannels;
        unsigned char* data = nullptr;

        auto texFileName = "textures/" + fileName;
        stbi_set_flip_vertically_on_load(true);
        data = stbi_load(resolveAssetPath(texFileName).string().c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            this->height = height;
            this->width = width;
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }

        // generating textures
        glGenTextures(1, &ID);
        Logger::glCheckError(__FILE__, __LINE__, fileName.c_str());

        // texture loading
        glBindTexture(GL_TEXTURE_2D, ID);
        Logger::glCheckError(__FILE__, __LINE__, fileName.c_str());

        // avoid skewed textures by changing to OpenGL's default Pixel Store alignment of 4 to 1
        glPixelStorei(GL_UNPACK_ROW_LENGTH, this->width);
        Logger::glCheckError(__FILE__, __LINE__, fileName.c_str());
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        Logger::glCheckError(__FILE__, __LINE__, fileName.c_str());
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        Logger::glCheckError(__FILE__, __LINE__, fileName.c_str());

        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        Logger::glCheckError(__FILE__, __LINE__, fileName.c_str());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        Logger::glCheckError(__FILE__, __LINE__, fileName.c_str());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        Logger::glCheckError(__FILE__, __LINE__, fileName.c_str());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        Logger::glCheckError(__FILE__, __LINE__, fileName.c_str());

        // generate the texture
        if (data)
        {
            // handle transparency (rgb + alpha channel = 4)
            if (nrChannels == 4)
            {
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                Logger::glCheckError(__FILE__, __LINE__, fileName.c_str());
                glEnable(GL_BLEND);
                Logger::glCheckError(__FILE__, __LINE__, fileName.c_str());
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                Logger::glCheckError(__FILE__, __LINE__, fileName.c_str());
            }
            else {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                Logger::glCheckError(__FILE__, __LINE__, fileName.c_str());
            }
            glGenerateMipmap(GL_TEXTURE_2D);
            Logger::glCheckError(__FILE__, __LINE__, fileName.c_str());
        }
        stbi_image_free(data);
    }

    void Texture::bind() {
        glActiveTexture(GL_TEXTURE0);
        Logger::glCheckError(__FILE__, __LINE__);
        glBindTexture(GL_TEXTURE_2D, ID);
        Logger::glCheckError(__FILE__, __LINE__);
    }
}