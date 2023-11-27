#pragma once

#include "engine/BaseGame.h"
#include "interaction/InteractionManager.h"
#include "interaction/ResourceCostManager.h"
#include "engine/ui/Canvas.h"
#include "entities/Player.h"
#include "tilemap/IslandTileMap.h"
#include "engine/rendering/TextureAtlas.h"

namespace WorldExtender {
    enum GameState {
        Start,
        Play,
        End
    };

    class Game : public ChunkMapEngine::BaseGame{
    public:
        Game(int width, int height, const std::string &title);
        ~Game() { }

        void run() override;
        void endGame();

        Player *getPlayer() { return player; }

        IslandTileMap* getTileMap() { return tileMap; }
        ChunkMapEngine::TextureAtlas* getTextureAtlas() { return &textureAtlas; }
        ChunkMapEngine::TextureAtlas* getTextureAtlasRed() { return &textureAtlasRed; }
        ChunkMapEngine::TextureAtlas* getTextureAtlasSnow() { return &textureAtlasSnow; }
        ChunkMapEngine::TextureAtlas* getTextureAtlasStone() { return &textureAtlasStone; }
        ChunkMapEngine::TextureAtlas* getTextureAtlasMana() { return &textureAtlasMana; }
        ChunkMapEngine::TextureAtlas* getTextureAtlasPortal() { return &textureAtlasPortal; }
        ChunkMapEngine::TextureAtlas* getCharSpriteSheet() { return &charSpriteSheet; }
        SoLoud::Soloud* getAudioSystem() { return &audio; }

    private:
        void update() override;
        void physics() override;
        void animate() override;
        void draw() override;

        std::string title;
        GameState currentGameState;

        Player *player = nullptr;

        InteractionManager interactionManager;
        ResourceCostManager resourceCostManager;
        ChunkMapEngine::Canvas screenCanvas;
        ChunkMapEngine::Canvas worldCanvas;
        IslandTileMap* tileMap = nullptr;
        ChunkMapEngine::TextureAtlas startScreen;
        ChunkMapEngine::TextureAtlas endScreen;
        ChunkMapEngine::TextureAtlas textureAtlas;
        ChunkMapEngine::TextureAtlas textureAtlasRed;
        ChunkMapEngine::TextureAtlas textureAtlasSnow;
        ChunkMapEngine::TextureAtlas textureAtlasStone;
        ChunkMapEngine::TextureAtlas textureAtlasMana;
        ChunkMapEngine::TextureAtlas textureAtlasPortal;
        ChunkMapEngine::TextureAtlas charSpriteSheet;
        ChunkMapEngine::TextureAtlas uiAtlas;
        ChunkMapEngine::Shader tileShader;
        ChunkMapEngine::Shader playerShader;
    };
}



