#pragma once

#include <memory>
#include <string>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "engine/Assets.h"
#include "physics/ContactListener.h"
#include "entities/Entity.h"
#include <box2d/box2d.h>
#include <soloud.h>
#include <soloud_wav.h>

namespace ChunkMapEngine {
    /// BaseGame functions as the base class for the individual games created using the ChunkMapEngine
    class BaseGame {
    public:
        glm::mat4 calculateMvpMatrix(glm::vec3 position, float zRotationInDegrees, glm::vec3 scale);
        /// moves the camera to the given position.
        void updateCamPos(glm::vec3 newPosition);
        /// returns the camera's position in 2D space.
        glm::vec2 getCamPos();
        GLFWwindow* getWindow() { return window; }
        b2World* getPhysicsWorld() { return &physicsWorld; }
        SoLoud::Soloud* getAudioSystem() { return &audio; }

    protected:
        BaseGame(int width, int height, const std::string& title);
        virtual ~BaseGame();
        /// override to include all functionalities that define the loop of the game.
        virtual void run() {};
        /// override to define what part of the game need constant updates.
        virtual void update() {};
        /// override to define which entities needs to be animated.
        virtual void animate() {};
        /// override to define what needs to be drawn by the game,
        virtual void draw() {};
        /// override to define physics-based behavior inside the game.
        virtual void physics() {};
        /// clears the render buffers. Effectively sets the background's color.
        void clearBuffer(double r, double g, double b, double a = 1);
        /// updates the delta time to enable processes running based on real time.
        void updateDeltaTime();
        /// loads and changes the background music.
        void loadBackgroundMusic(std::string path);

        GLFWwindow* window = nullptr;
        float deltaTime = 1.0f / 60;

        b2Vec2 gravity{ 0.0f, 0.0f };
        b2World physicsWorld{ gravity };
        ContactListener contactListenerInstance;

        SoLoud::Soloud audio;
        std::unique_ptr<SoLoud::Wav> backgroundMusic;

        std::vector<std::shared_ptr<Entity>> entities;
    private:
        float lastFrameTime = 1.0f / 60;
        Camera camera;
    };
}