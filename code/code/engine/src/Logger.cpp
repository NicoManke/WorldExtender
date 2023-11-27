#include "engine/Logger.h"
#include <iostream>
#include <iomanip>
using namespace std;

int ChunkMapEngine::Logger::printCounter = 0;

void ChunkMapEngine::Logger::logError(exception exception) {
	cout << "ERROR: " << exception.what() << endl;
}

void ChunkMapEngine::Logger::logErrorNr(int exception) {
	cout << "ERROR: Exception[" << exception << "]" << endl;
}

void ChunkMapEngine::Logger::print(string message) {
	auto currentCount = printCounter <= 99999 ? printCounter : 99999;
	cout << "Logger[" << setfill('0') << setw(4) << currentCount << "]: " << message << endl;
	printCounter++;
}

GLenum ChunkMapEngine::Logger::glCheckError(const char* file, int line) {
    return ChunkMapEngine::Logger::glCheckError(file, line, nullptr);
}

GLenum ChunkMapEngine::Logger::glCheckError(const char* file, int line, const char* name)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
        case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
        case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
        case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
        case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
        case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
        case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        if (name) {
            std::cout << error << " : " << file << " (" << line << ") [" << name << "]" << std::endl;
        }
        else {
            std::cout << error << " : " << file << " (" << line << ")" << std::endl;
        }
    }
    return errorCode;
}