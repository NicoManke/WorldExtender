#include "engine/entities/Entity.h"
#include "engine/BaseGame.h"

namespace ChunkMapEngine {
    Entity::Entity(Texture texture, Shader shader, Mesh mesh, glm::vec3 position, float zRotation, float scale
    ) :
            texture(std::move(texture)),
            shader(std::move(shader)),
            mesh(std::move(mesh)),
            position(position),
            zRotation(zRotation),
            scale(scale)
    { }

    void Entity::draw(BaseGame *game) {
        auto mvpMatrix = game->calculateMvpMatrix(position, zRotation, scale);
        shader.use();
        shader.setMatrix("mvp", mvpMatrix);
        texture.bind();
        mesh.draw();
    }
    
    void Entity::removeCollider(b2World* physicsWorld) {
        if (hasCollider) {
            physicsWorld->DestroyBody(collider.destroyBody());
            collider = {};
            hasCollider = false;
        }
    };

    void Entity::activateCollider(bool active) {
        if (hasCollider) {
            collider.setBodyActive(active);
        }
    }

    Entity::~Entity() = default;
}