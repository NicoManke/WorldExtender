#pragma once

#include "engine/entities/Entity.h"
#include "engine/physics/Collider.h"
#include "../inventory/Inventory.h"
#include "../Parameters.h"
#include "engine/Settings.h"
#include <soloud.h>
#include <soloud_wav.h>

namespace WorldExtender {
    class Player : public ChunkMapEngine::Entity {
    public:
        explicit Player(ChunkMapEngine::BaseGame* game,
            ChunkMapEngine::Texture texture,
            glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
            float scale = 1.0f
        );
        ~Player();
        void update(ChunkMapEngine::BaseGame* game, float deltaTime) override;
        void draw(ChunkMapEngine::BaseGame* game) override;
        void animate(float deltaTime) override;
        void startContact() override;

        void interact(bool isInteractableTile, int type);
        bool IsInteracting() { return isInteracting; }
        void setInteracting(bool state);
        void startInteractionAnimation();
        int getTurnDirection() { return turnDirection; }
        Inventory* getIventory() { return &inventory; }

    private:
        Inventory inventory;
        shared_ptr<SoLoud::Wav> walkingSound;
        SoLoud::handle walkingSoundHandle;
        float translationSpeed = 200.0f * ChunkMapEngine::SCALING;
        int turnDirection = -1;
        bool isInteracting = false;
        bool isInteractKeyPressed = false;

        b2Vec2 defineDirection(float xVelocity, float yVelocity, int turnDirection, int animation);
    };
}


