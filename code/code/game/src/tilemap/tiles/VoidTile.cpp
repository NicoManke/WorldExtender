#include "VoidTile.h"

namespace WorldExtender {
	VoidTile::VoidTile(ChunkMapEngine::BaseGame* game, ChunkMapEngine::Texture texture, tile_type type, int version, glm::vec3 position, float size, int orientation) : ChunkMapEngine::Tile(game, texture, type, version, position, size, orientation) {
		collider = ChunkMapEngine::Collider(createBody(game, { position.x, position.y }, size * 0.55, this));
		hasCollider = true;
	}

	void VoidTile::reset() {
		type = GRASS;
		mesh.updateMesh(getTileVertices(GRASS, version, &texture).vertices);
	}

	void VoidTile::interact() {

	}
}