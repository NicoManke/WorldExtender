#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "engine/Settings.h"

namespace ChunkMapEngine {
    /// Camera represents an artificial and movable camera object. Also providing virtual functions that can be overridden to add additional and uique behavior.
    class Camera {
    public:
        Camera() {
            position = glm::vec3(0, 0, 90.0f);
            lookAtPos = glm::vec3(0.0, 0.0, 0.0);
        };

        Camera(const glm::vec3& position, const glm::vec3 lookAtPos) : position(position), lookAtPos(lookAtPos) { }

        glm::mat4 getViewMatrix() const;
        /// returns a mvpMatrix based on the camera's position.
        glm::mat4 calculateMvpMatrix(glm::vec3 position, float zRotationInDegrees, glm::vec3 scale, glm::vec3 cameraPosition = glm::vec3(0.0, 0.0, 90.0f));
        /// updates the camera's position based on the given position. Taking a 3D vector for utility reasons.
        void updateCamPos(glm::vec3 newPosition);
        /// returns the camera's position in 2D space.
        glm::vec2 getCamPos() { return glm::vec2(position.x, position.y); };

        /// override to define unique shaking behavior of the camera.
        virtual void shake() {};
        /// override to define a unique yaw rotation.
        virtual void rotateYaw() {};
        /// override to define a unique pitch rotation.
        virtual void rotatePitch() {};
        /// override to define a unique roll rotation.
        virtual void rotateRoll() {};
        /// override to define FOV-changing behavior.
        virtual void changeFOV() {};
        /// override to define a fixed reset of the FOV.
        virtual void resetFOV() {};
    private:
        glm::vec3 position = glm::vec3(0.0, 0.0, 90.0f);
        glm::vec3 lookAtPos = glm::vec3(0.0, 0.0, 0.0);
    };
}