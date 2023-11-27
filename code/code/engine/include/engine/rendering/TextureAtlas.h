#pragma once

#include "Texture.h"

namespace ChunkMapEngine {
	/// the TextureAtlas class functions as a wrapper for the Texture class.
	class TextureAtlas {
	public:
		TextureAtlas(std::string fileName);
		TextureAtlas(std::string fileName, std::vector<int> animationFrameCounts, std::vector<float> animationDurations);
		TextureAtlas() = default;
		/// returns a copy of the safed Texture.
		Texture getTexture();
		/// refrences the Texture based on its ID. 
		unsigned int getTextureID();
		/// binds the Texture to the current OpenGL process.
		void bindTexture();
	private:
		Texture texture;
	};
}