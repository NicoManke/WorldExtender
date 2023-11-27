#include "Inventory.h"
#include "../Game.h"
#include "../Parameters.h"
#include "engine/rendering/TextureAtlas.h"

namespace WorldExtender {
	void updateCount(int count, shared_ptr<ChunkMapEngine::UI> tensIcon, shared_ptr<ChunkMapEngine::UI> onesIcon) {
		if (count > 99) {
			count = 99;
		}
		auto tens = (int)count / 10;
		auto ones = (int)count % 10;
		tensIcon->changeIcon(ChunkMapEngine::Icon{ DIGIT_ROW, tens });
		onesIcon->changeIcon(ChunkMapEngine::Icon{ DIGIT_ROW, ones });
	}

	Inventory::Inventory() {
		canvas = ChunkMapEngine::Canvas();
		auto uiAtlas = ChunkMapEngine::TextureAtlas("ui_atlas.png");
		auto fontAtlas = ChunkMapEngine::TextureAtlas("font_atlas.png");

		auto scaleCorrection = 1.01f;
		auto counterScale = 0.8f;
		auto moveTogether = (1.0f - counterScale) * 0.5f;
		auto iconScale = 2 * ChunkMapEngine::SCALING;
		auto displacement = -65.0f;
		// item icons
		stoneIcon = std::make_shared<ChunkMapEngine::UI>(uiAtlas.getTexture(), ChunkMapEngine::Icon{ 0, 0 }, glm::vec2(1, 1), glm::vec3(-1 * iconScale + ChunkMapEngine::CENTERING, displacement - 1.5 * ChunkMapEngine::SCALING, 0), 0, scaleCorrection * iconScale);
		canvas.addUI(stoneIcon);
		manaIcon  = std::make_shared<ChunkMapEngine::UI>(uiAtlas.getTexture(), ChunkMapEngine::Icon{ 0, 1 }, glm::vec2(1, 1), glm::vec3( 0 * iconScale + ChunkMapEngine::CENTERING, displacement - 1.5 * ChunkMapEngine::SCALING, 0), 0, scaleCorrection * iconScale);
		canvas.addUI(manaIcon);
		woodIcon  = std::make_shared<ChunkMapEngine::UI>(uiAtlas.getTexture(), ChunkMapEngine::Icon{ 0, 2 }, glm::vec2(1, 1), glm::vec3( 1 * iconScale + ChunkMapEngine::CENTERING, displacement - 1.5 * ChunkMapEngine::SCALING, 0), 0, scaleCorrection * iconScale);
		canvas.addUI(woodIcon);
		// item counts
		auto counterDisplacement = displacement - moveTogether * ChunkMapEngine::SCALING;
		stoneTensIcon = std::make_shared<ChunkMapEngine::UI>(fontAtlas.getTexture(), ChunkMapEngine::Icon{ 0, 0 }, glm::vec2(1, 1), glm::vec3((-2.5 + moveTogether) * ChunkMapEngine::SCALING + ChunkMapEngine::CENTERING, counterDisplacement, 0), 0, scaleCorrection * counterScale * ChunkMapEngine::SCALING);
		canvas.addUI(stoneTensIcon);																						  									    
		stoneOnesIcon = std::make_shared<ChunkMapEngine::UI>(fontAtlas.getTexture(), ChunkMapEngine::Icon{ 0, 0 }, glm::vec2(1, 1), glm::vec3((-1.5 - moveTogether) * ChunkMapEngine::SCALING + ChunkMapEngine::CENTERING, counterDisplacement, 0), 0, scaleCorrection * counterScale * ChunkMapEngine::SCALING);
		canvas.addUI(stoneOnesIcon);																						  									    
		manaTensIcon  = std::make_shared<ChunkMapEngine::UI>(fontAtlas.getTexture(), ChunkMapEngine::Icon{ 0, 0 }, glm::vec2(1, 1), glm::vec3((-0.5 + moveTogether) * ChunkMapEngine::SCALING + ChunkMapEngine::CENTERING, counterDisplacement, 0), 0, scaleCorrection * counterScale * ChunkMapEngine::SCALING);
		canvas.addUI(manaTensIcon);																							  									    
		manaOnesIcon  = std::make_shared<ChunkMapEngine::UI>(fontAtlas.getTexture(), ChunkMapEngine::Icon{ 0, 0 }, glm::vec2(1, 1), glm::vec3(( 0.5 - moveTogether) * ChunkMapEngine::SCALING + ChunkMapEngine::CENTERING, counterDisplacement, 0), 0, scaleCorrection * counterScale * ChunkMapEngine::SCALING);
		canvas.addUI(manaOnesIcon);																							  									    
		woodTensIcon  = std::make_shared<ChunkMapEngine::UI>(fontAtlas.getTexture(), ChunkMapEngine::Icon{ 0, 0 }, glm::vec2(1, 1), glm::vec3(( 1.5 + moveTogether) * ChunkMapEngine::SCALING + ChunkMapEngine::CENTERING, counterDisplacement, 0), 0, scaleCorrection * counterScale * ChunkMapEngine::SCALING);
		canvas.addUI(woodTensIcon);																							  									    
		woodOnesIcon  = std::make_shared<ChunkMapEngine::UI>(fontAtlas.getTexture(), ChunkMapEngine::Icon{ 0, 0 }, glm::vec2(1, 1), glm::vec3(( 2.5 - moveTogether) * ChunkMapEngine::SCALING + ChunkMapEngine::CENTERING, counterDisplacement, 0), 0, scaleCorrection * counterScale * ChunkMapEngine::SCALING);
		canvas.addUI(woodOnesIcon);
	}

	Inventory::~Inventory() {

	}

	void Inventory::updateStoneCounter(int count) {
		updateCount(count, stoneTensIcon, stoneOnesIcon);
	}
	void Inventory::updateManaCounter(int count) {
		updateCount(count, manaTensIcon, manaOnesIcon);
	}
	void Inventory::updateWoodCounter(int count) {
		updateCount(count, woodTensIcon, woodOnesIcon);
	}

	void Inventory::increaseStoneCount() {
		stoneCount++;
		updateStoneCounter(stoneCount);
	}

	void Inventory::increaseManaCount() {
		manaCount++;
		updateManaCounter(manaCount);
	}

	void Inventory::increaseWoodCount() {
		woodCount++;
		updateWoodCounter(woodCount);
	}

	void Inventory::decreaseStoneCount(int deficit){
		stoneCount -= deficit;
		updateStoneCounter(stoneCount);
	}

	void Inventory::decreaseManaCount(int deficit){
		manaCount -= deficit;
		updateManaCounter(manaCount);
	}

	void Inventory::decreaseWoodCount(int deficit){
		woodCount -= deficit;
		updateWoodCounter(woodCount);
	}

	void Inventory::draw(ChunkMapEngine::BaseGame* game) {
		canvas.draw(game);
	}
}