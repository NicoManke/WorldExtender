#include "engine/Camera.h"

namespace ChunkMapEngine {
    glm::mat4 Camera::getViewMatrix() const {
        glm::mat4 view = glm::lookAt(position,
            lookAtPos,
            glm::vec3(0.0, 1.0, 0.0));
        return view;
    }

    glm::mat4 Camera::calculateMvpMatrix(glm::vec3 position, float zRotationInDegrees, glm::vec3 scale, glm::vec3 cameraPosition) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::scale(model, scale);
        model = glm::rotate(model, glm::radians(zRotationInDegrees), glm::vec3(0.0f, 0.0f, 1.0f));

        glm::mat4 view = getViewMatrix();

        glm::mat4 projection = glm::perspective(glm::radians(FOV), 1000.0f / 600.0f, 0.1f, 100.0f);

        return projection * view * model;
    }

    void Camera::updateCamPos(glm::vec3 newPosition) { 
        this->position = { newPosition.x, newPosition.y, 90.0f }; 
        this->lookAtPos = { newPosition.x, newPosition.y, 0.0f };
    }
}