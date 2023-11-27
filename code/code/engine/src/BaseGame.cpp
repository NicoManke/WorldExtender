#include <stdexcept>
#include "engine/BaseGame.h"
#include "engine/Logger.h"
#include "engine/Settings.h"

namespace ChunkMapEngine {

    void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height); 
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
    }

    BaseGame::BaseGame(int width, int height, const std::string& title) {
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize glfw");
        }
        
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        
        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (window == nullptr) {
            throw std::runtime_error("Failed to create window");
        }
        
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        camera = Camera();

        entities = std::vector<std::shared_ptr<Entity>>();

        audio.init();
        audio.setGlobalVolume(0.15f);

        physicsWorld.SetContactListener(&contactListenerInstance);
    }

    void BaseGame::clearBuffer(double r, double g, double b, double a) {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    glm::mat4 BaseGame::calculateMvpMatrix(glm::vec3 position, float zRotationInDegrees, glm::vec3 scale) {
        return camera.calculateMvpMatrix(position, zRotationInDegrees, scale);
    }

    void BaseGame::updateCamPos(glm::vec3 newPosition) { 
        camera.updateCamPos(newPosition); 
    }

    glm::vec2 BaseGame::getCamPos() {
        return camera.getCamPos();
    }

    void BaseGame::updateDeltaTime() {
        float frameTime = glfwGetTime();
        deltaTime = frameTime - lastFrameTime;
        lastFrameTime = frameTime;
    }

    void BaseGame::loadBackgroundMusic(std::string path) {
        backgroundMusic = std::make_unique<SoLoud::Wav>();
        backgroundMusic->load(ChunkMapEngine::resolveAssetPath(path).string().c_str());
        backgroundMusic->setLooping(true);
        audio.playBackground(*backgroundMusic);
    }

    BaseGame::~BaseGame() {
        glfwTerminate();
        for (auto &collider: entities) {
            physicsWorld.DestroyBody(collider->getColliderBody());
        }
        backgroundMusic.reset();
    }
}