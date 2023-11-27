#include "engine/rendering/TextureAtlas.h"

namespace ChunkMapEngine {
	TextureAtlas::TextureAtlas(std::string fileName) {
		texture = Texture(fileName);
	}

	TextureAtlas::TextureAtlas(std::string fileName, std::vector<int> animationFrameCounts, std::vector<float> animationDurations) {
		texture = Texture(fileName, animationFrameCounts, animationDurations);
	}

	Texture TextureAtlas::getTexture() {
		return texture;
	}

	unsigned int TextureAtlas::getTextureID() {
		return texture.getID();
	}

	void TextureAtlas::bindTexture() {
		texture.bind();
	}
}