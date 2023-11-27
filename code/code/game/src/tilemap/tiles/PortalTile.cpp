#include "PortalTile.h"

namespace WorldExtender {
	PortalTile::PortalTile(ChunkMapEngine::BaseGame* game, ChunkMapEngine::Texture texture, tile_type type, int version, glm::vec3 position, float size, int orientation) : Tile(game, texture, type, version, position, size, orientation) {
		collider = ChunkMapEngine::Collider(createBody(game, { position.x, position.y }, size * 0.55, this));
		hasCollider = true;
		interactable = true;
	}

	void PortalTile::reset() {

	}

	void PortalTile::interact() {

	}
}