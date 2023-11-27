#pragma once

#include "glm/vec3.hpp"
#include "engine/rendering/Mesh.h"
#include "engine/rendering/Shader.h"
#include "engine/rendering/Texture.h"
#include "engine/rendering/Animator.h"
#include "engine/physics/Collider.h"
#include "GLFW/glfw3.h"

namespace ChunkMapEngine {
    class BaseGame;

    /// The Entity class represents simple in-game objects that can have a mesh, a (animated) texture and a collider.
    class Entity {
    public:
        Entity(Texture texture, 
            Shader shader,
            Mesh mesh,
            glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
            float zRotation = 0.0f,
            float scale = 1.0f);

        virtual ~Entity();

        /// override this function to define regular updates for an Entity
        virtual void update(BaseGame*game, float deltaTime) {}

        /// override this and call animator.animate() if the Entity has an animator
        virtual void animate(float deltaTime) {}

        /// draws the Entity onto the screen using shader, mesh and texture.
        virtual void draw(BaseGame *game);

        /// override and define behavior caused by collisions
        virtual void startContact() { };
        virtual b2Body* getColliderBody() { return collider.getBody(); };
        /// removes the collider if present. Override if there should be additional behavior.
        virtual void removeCollider(b2World* physicsWorld);
        virtual void activateCollider(bool active);

        [[nodiscard]] const glm::vec3 &getPosition() const { return position; }
        [[nodiscard]] float getZRotation() const { return zRotation; }
        [[nodiscard]] const glm::vec3 &getScale() const { return scale; }
        void setPosition(const glm::vec3 &position) { Entity::position = position; }
        void setZRotation(float zRotation) { Entity::zRotation = zRotation; }
        void setScale(const glm::vec3 &scale) { Entity::scale = scale; }

    protected:
        glm::vec3 position;
        float zRotation;
        glm::vec3 scale;
        Texture texture;
        Shader shader;
        Mesh mesh;
        Animator animator;
        Collider collider {};
        bool hasCollider = false;
    };
}



