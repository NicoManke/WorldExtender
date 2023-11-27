#include "Game.h"
#include <stdexcept>
#include <random>
#include <iostream>
#include <format>
#include <memory>
#include "engine/Assets.h"
#include "engine/tilemap/Tile.h"
#include "engine/Logger.h"

namespace WorldExtender {
    void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    Game::Game(int width, int height, const std::string &title) : ChunkMapEngine::BaseGame(width, height, title) {
        
        this->title = title;
        currentGameState = Start;

        screenCanvas = ChunkMapEngine::Canvas();
        worldCanvas = ChunkMapEngine::Canvas();
        tileMap = new IslandTileMap();

        auto idleDur = 3.0f;
        auto moveDur = 1.0f;
        auto actDur = 1.0f;

        startScreen = ChunkMapEngine::TextureAtlas("start_screen.png");
        endScreen = ChunkMapEngine::TextureAtlas("end_screen.png");
        charSpriteSheet = ChunkMapEngine::TextureAtlas("timmy_sheet_anim.png",
            { 8,
            4, 4, 4, 4, 4, 4, 4, 4 ,
            3, 3, 3, 3 },
            { idleDur,
            moveDur, moveDur, moveDur, moveDur, moveDur, moveDur, moveDur, moveDur,
            actDur, actDur, actDur, actDur });
        textureAtlas = ChunkMapEngine::TextureAtlas("tile_atlas_variants_new.png");
        textureAtlasRed = ChunkMapEngine::TextureAtlas("tile_atlas_variants_red.png");
        textureAtlasSnow = ChunkMapEngine::TextureAtlas("tile_atlas_variants_snow.png");
        textureAtlasStone = ChunkMapEngine::TextureAtlas("tile_atlas_variants_stone.png");
        textureAtlasMana = ChunkMapEngine::TextureAtlas("tile_atlas_variants_mana.png");
        textureAtlasPortal = ChunkMapEngine::TextureAtlas("tile_atlas_variants_portal.png");
        uiAtlas = ChunkMapEngine::TextureAtlas("ui_atlas.png");

        glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, width, height, GLFW_DONT_CARE);
    }

    void Game::run() {
        unsigned int VAO;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glfwSetTime(1.0 / 60);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        auto startScreenUI = std::make_shared<ChunkMapEngine::UI>(startScreen.getTexture(), ChunkMapEngine::Icon{ 0, 0 }, glm::vec2( 16, 9), glm::vec3( 0, 0, 1 ), 0.0f, ChunkMapEngine::SCALING * 18.0f, true);
        screenCanvas.addUI(startScreenUI);
        loadBackgroundMusic("audio/music/a_new_beginning.mp3");

        auto isPressedSPACE = false;
        while (!glfwWindowShouldClose(window) && currentGameState == Start) {
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                glfwSetWindowShouldClose(window, true);
            }

            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && isPressedSPACE == false) {
                currentGameState = Play;
                screenCanvas.clearUI();
                startScreenUI.reset();
                isPressedSPACE = true;
            }
            else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
                isPressedSPACE = false;
            }

            clearBuffer(0, 0, 0);
            screenCanvas.draw(this);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        if (!glfwWindowShouldClose(window)) {
            loadBackgroundMusic("audio/music/music_churches_in_antioquia.mp3");

            auto playerCharacter = std::make_shared<Player>(this, charSpriteSheet.getTexture(), glm::vec3(0, 0, 0), ChunkMapEngine::SCALING);
            player = playerCharacter.get();
            entities.emplace_back(playerCharacter);

            tileMap->initializeStartingRegion(this, player, START_I);

            auto tileMarkerUI = std::make_shared<ChunkMapEngine::UI>(uiAtlas.getTexture(), ChunkMapEngine::Icon{ 4, 0 }, glm::vec2(1, 1), glm::vec3(0, 0, 100), 0, ChunkMapEngine::SCALING);
            worldCanvas.addUI(tileMarkerUI);

            resourceCostManager = ResourceCostManager();
            interactionManager = InteractionManager(this, &resourceCostManager, tileMap, player, tileMarkerUI);

            auto lastTime = glfwGetTime();
        }

        while(!glfwWindowShouldClose(window) && currentGameState == Play) {
            update();
            physics();
            clearBuffer(0.1686, 0.5843, 0.8588);
            animate();
            draw();

            updateDeltaTime();
            glfwPollEvents();
        }

        if (!glfwWindowShouldClose(window)) {
            loadBackgroundMusic("audio/music/medieval.mp3");
            auto endScreenPos = getCamPos();
            auto endScreenUI = std::make_shared<ChunkMapEngine::UI>(endScreen.getTexture(), ChunkMapEngine::Icon{ 0, 0 }, glm::vec2(16, 9), glm::vec3(endScreenPos.x, endScreenPos.y, 2), 0.0f, ChunkMapEngine::SCALING * 18.0f, true);
            screenCanvas.addUI(endScreenUI);
        }

        while (!glfwWindowShouldClose(window) && currentGameState == End) {
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                glfwSetWindowShouldClose(window, true);
            }
            clearBuffer(0, 0, 0);
            screenCanvas.draw(this);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        std::cout << std::endl << "Thank you for playing!" << std::endl;
    }

    void Game::endGame() {
        currentGameState = End;
    }

    void Game::update() {
        interactionManager.manageInteractions(this);

        tileMap->updateChunks();
        tileMap->updateTiles();

        for(auto &entity: entities) {
            entity->update(this, deltaTime);
        }

        player->getIventory()->getCanvas()->moveUI(getCamPos());
        resourceCostManager.getCanvas()->moveUI(getCamPos());
    }

    void Game::physics() {
        const int32_t velocityIterations = 10;
        const int32_t positionIterations = 8;
        const float timeStep = 1.0f/60.0f;
        physicsWorld.Step(timeStep, velocityIterations, positionIterations);
        physicsWorld.ClearForces();
    }

    void Game::animate() {
        player->animate(deltaTime);
    }

    void Game::draw() {
        tileMap->drawChunks(this);

        worldCanvas.draw(this);

        for(auto &entity: entities) {
            entity->draw(this);
        }

        resourceCostManager.draw(this);

        glfwSwapBuffers(window);
    }
}
