#pragma once

#include <string>
#include <vector>

namespace ChunkMapEngine {
	/// the Texture class represents OpenGL's texture objects. The image size should be a multiple of 32px.
	class Texture {
	public:
		/// creates a simple Texture based on a image file.
		Texture(std::string fileName);
		/// @brief creates a simple Texture based on a image file. Is meant for animated textures (sprite sheets), therefore recieves information about each animations frame count and duration.
		/// @param animationFrameCounts vector where cell i defines how many frames animation i on the image has.
		/// @param animationDurations vector where cell i defines the duration of animation i.
		Texture(std::string fileName, std::vector<int> animationFrameCounts, std::vector<float> animationDurations);
		Texture() = default;
		~Texture() {};

		/// binds the texture to the current OpenGL process.
		void bind();
		/// returns the texture's ID referencing it in the OpenGL context.
		unsigned int getID() { return ID; }
		int getHeight() { return height; }
		int getWidth() { return width; }
		/// calculates the amount of animations on a sprite sheet texture based on the predefined sprite size (32x32px) and the texture's height.
		int getAnimationCount() { return animationCount; };
		/// gives the frame count of the current animation based on the previously given data.
		int getFrameCount(int animation) { return frameCount.at(animation); }
		/// gives the duration of the current animation based on the previously given data.
		float getAnimationDuration(int animation) { return animationDuration.at(animation); }

	private:
		/// loads and generates a usable texture based on a given image for OpenGL.
		void initTexture(std::string fileName);

		unsigned int ID = 0;
		int height = 0;
		int width = 0;
		int animationCount = 0;
		std::vector<int> frameCount = std::vector<int>();
		std::vector<float> animationDuration = std::vector<float>();
	};
}