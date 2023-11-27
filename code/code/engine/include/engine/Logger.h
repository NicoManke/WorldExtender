#pragma once

#include <string>
#include <exception>
#include <glad/glad.h>

namespace ChunkMapEngine {
	/// Logger provides simple print, log and debug tools.
	class Logger {
	public:
		/// print a message to the console.
		static void print(std::string message);
		/// print an error and its exception to the console.
		static void logError(std::exception exception);
		/// print an error and its id to the console.
		static void logErrorNr(int exception);
		/// check for gl errors. Use __FILE__ and __LINE__ macros.
		static GLenum glCheckError(const char* file, int line, const char* name);
		/// check for gl errors. Use __FILE__ and __LINE__ macros.
		static GLenum glCheckError(const char* file, int line);
	private:
		static int printCounter;
	};
}