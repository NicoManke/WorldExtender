#include "PreBridgeTile.h"

namespace WorldExtender {
	PreBridgeTile::PreBridgeTile(ChunkMapEngine::BaseGame* game, ChunkMapEngine::Texture texture, tile_type type, int version, glm::vec3 position, float size, int orientation) : Tile(game, texture, type, version, position, size, orientation) {
		interactable = true;
	}

	void PreBridgeTile::reset() {

	}

	void PreBridgeTile::interact() {
		interactable = false;
	}
}