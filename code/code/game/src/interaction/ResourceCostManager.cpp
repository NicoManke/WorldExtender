#include "ResourceCostManager.h"
#include "engine/rendering/TextureAtlas.h"
#include "engine/Settings.h"

constexpr int ADD = 1;
constexpr int SUB = 2;
constexpr int ACT = 3;
constexpr int CREATE = 0;
constexpr int MINE = 1;
constexpr int USE_PORTAL = 2;

namespace WorldExtender {
	void updateCount(int cost, bool add, shared_ptr<ChunkMapEngine::UI> operatorIcon, shared_ptr<ChunkMapEngine::UI> tensIcon, shared_ptr<ChunkMapEngine::UI> onesIcon) {
		auto tens = (int)cost / 10;
		auto ones = (int)cost % 10;
		if (add) {
			operatorIcon->changeIcon(ChunkMapEngine::Icon{ 3, 2 });
			tensIcon->changeIcon(ChunkMapEngine::Icon{ 2, tens });
			onesIcon->changeIcon(ChunkMapEngine::Icon{ 2, ones });
		}
		else {
			operatorIcon->changeIcon(ChunkMapEngine::Icon{ 5, 1 });
			tensIcon->changeIcon(ChunkMapEngine::Icon{ 4, tens });
			onesIcon->changeIcon(ChunkMapEngine::Icon{ 4, ones });
		}
	}

	ResourceCostManager::ResourceCostManager() {
		canvas = ChunkMapEngine::Canvas();
		auto uiAtlas = ChunkMapEngine::TextureAtlas("ui_atlas.png");
		auto fontAtlas = ChunkMapEngine::TextureAtlas("font_atlas.png");

		auto yDisplacement = -65.0f;
		auto xDisplacement = 100.0f;
		auto scaleCorrection = 1.01f;
		auto scale = 0.66f;
		auto counterScale = 0.8f;
		auto moveDown = (1.0f - scale) * 0.5;
		auto moveTogether = (1.0f - counterScale) * 0.5f;
		auto counterDisplacement = yDisplacement - (moveDown + moveTogether) * ChunkMapEngine::SCALING;
		auto finalScale = scaleCorrection * scale * counterScale * ChunkMapEngine::SCALING;
		auto iconScale = 2 * ChunkMapEngine::SCALING;
		// action icon
		actionIcon = std::make_shared<ChunkMapEngine::UI>(uiAtlas.getTexture(), ChunkMapEngine::Icon{ 3, 3 }, glm::vec2(1, 1), glm::vec3(2 * iconScale + ChunkMapEngine::CENTERING + xDisplacement, yDisplacement - 1.5 * ChunkMapEngine::SCALING, 0), 0, scaleCorrection * iconScale);
		canvas.addUI(actionIcon);
		// resource icons
		stoneIcon = std::make_shared<ChunkMapEngine::UI>(uiAtlas.getTexture(), ChunkMapEngine::Icon{ 1, 0 }, glm::vec2(1, 1), glm::vec3(-1 * iconScale + ChunkMapEngine::CENTERING + xDisplacement, yDisplacement - 1.5 * ChunkMapEngine::SCALING, 0), 0, scaleCorrection * iconScale);
		canvas.addUI(stoneIcon);
		manaIcon = std::make_shared<ChunkMapEngine::UI>(uiAtlas.getTexture(), ChunkMapEngine::Icon{ 1, 1 }, glm::vec2(1, 1), glm::vec3(0 * iconScale + ChunkMapEngine::CENTERING + xDisplacement, yDisplacement - 1.5 * ChunkMapEngine::SCALING, 0), 0, scaleCorrection * iconScale);
		canvas.addUI(manaIcon);
		woodIcon = std::make_shared<ChunkMapEngine::UI>(uiAtlas.getTexture(), ChunkMapEngine::Icon{ 1, 2 }, glm::vec2(1, 1), glm::vec3(1 * iconScale + ChunkMapEngine::CENTERING + xDisplacement, yDisplacement - 1.5 * ChunkMapEngine::SCALING, 0), 0, scaleCorrection * iconScale);
		canvas.addUI(woodIcon);
		// resource cost counts
		stoneOperandIcon = std::make_shared<ChunkMapEngine::UI>(fontAtlas.getTexture(), ChunkMapEngine::Icon{ 3, 1 }, glm::vec2(1, 1), glm::vec3((-2.66 + moveTogether * 1.5f) * ChunkMapEngine::SCALING + ChunkMapEngine::CENTERING + xDisplacement, counterDisplacement, 0), 0, finalScale);
		canvas.addUI(stoneOperandIcon);																																									  
		stoneTensIcon    = std::make_shared<ChunkMapEngine::UI>(fontAtlas.getTexture(), ChunkMapEngine::Icon{ 2, 0 }, glm::vec2(1, 1), glm::vec3((-2.00)				       * ChunkMapEngine::SCALING + ChunkMapEngine::CENTERING + xDisplacement, counterDisplacement, 0), 0,finalScale);
		canvas.addUI(stoneTensIcon);																																									  
		stoneOnesIcon    = std::make_shared<ChunkMapEngine::UI>(fontAtlas.getTexture(), ChunkMapEngine::Icon{ 2, 0 }, glm::vec2(1, 1), glm::vec3((-1.34 - moveTogether * 1.5f) * ChunkMapEngine::SCALING + ChunkMapEngine::CENTERING + xDisplacement, counterDisplacement, 0), 0,finalScale);
		canvas.addUI(stoneOnesIcon);																																									  
																																																		  
		manaOperandIcon = std::make_shared<ChunkMapEngine::UI>(fontAtlas.getTexture(), ChunkMapEngine::Icon{ 3, 1 }, glm::vec2(1, 1), glm::vec3((-0.66 + moveTogether * 1.5f) * ChunkMapEngine::SCALING + ChunkMapEngine::CENTERING + xDisplacement, counterDisplacement, 0), 0, finalScale);
		canvas.addUI(manaOperandIcon);																																									  
		manaTensIcon    = std::make_shared<ChunkMapEngine::UI>(fontAtlas.getTexture(), ChunkMapEngine::Icon{ 2, 0 }, glm::vec2(1, 1), glm::vec3(( 0.00)				          * ChunkMapEngine::SCALING + ChunkMapEngine::CENTERING + xDisplacement, counterDisplacement, 0), 0, finalScale);
		canvas.addUI(manaTensIcon);																																										  
		manaOnesIcon    = std::make_shared<ChunkMapEngine::UI>(fontAtlas.getTexture(), ChunkMapEngine::Icon{ 2, 0 }, glm::vec2(1, 1), glm::vec3(( 0.66 - moveTogether * 1.5f) * ChunkMapEngine::SCALING + ChunkMapEngine::CENTERING + xDisplacement, counterDisplacement, 0), 0, finalScale);
		canvas.addUI(manaOnesIcon);																																										  
																																																		  
		woodOperandIcon = std::make_shared<ChunkMapEngine::UI>(fontAtlas.getTexture(), ChunkMapEngine::Icon{ 3, 1 }, glm::vec2(1, 1), glm::vec3(( 1.34 + moveTogether * 1.5f) * ChunkMapEngine::SCALING + ChunkMapEngine::CENTERING + xDisplacement, counterDisplacement, 0), 0, finalScale);
		canvas.addUI(woodOperandIcon);																																									  
		woodTensIcon    = std::make_shared<ChunkMapEngine::UI>(fontAtlas.getTexture(), ChunkMapEngine::Icon{ 2, 0 }, glm::vec2(1, 1), glm::vec3(( 2.00)				          * ChunkMapEngine::SCALING + ChunkMapEngine::CENTERING + xDisplacement, counterDisplacement, 0), 0, finalScale);
		canvas.addUI(woodTensIcon);																																										  
		woodOnesIcon    = std::make_shared<ChunkMapEngine::UI>(fontAtlas.getTexture(), ChunkMapEngine::Icon{ 2, 0 }, glm::vec2(1, 1), glm::vec3(( 2.66 - moveTogether * 1.5f) * ChunkMapEngine::SCALING + ChunkMapEngine::CENTERING + xDisplacement, counterDisplacement, 0), 0, finalScale);
		canvas.addUI(woodOnesIcon);
	}

	void ResourceCostManager::updateIslandCosts(Costs newCosts) {
		islandCosts = newCosts;
	}

	void ResourceCostManager::updateBridgeCosts(Costs newCosts) {
		bridgeCosts = newCosts;
	}

	void ResourceCostManager::updatePortalCosts(Costs newCosts) {
		portalCosts = newCosts;
	}
	
	void ResourceCostManager::updateStoneCounter(int count, bool add) {
		updateCount(count, add, stoneOperandIcon, stoneTensIcon, stoneOnesIcon);
	}
	void ResourceCostManager::updateManaCounter(int count, bool add) {
		updateCount(count, add, manaOperandIcon, manaTensIcon, manaOnesIcon);
	}
	void ResourceCostManager::updateWoodCounter(int count, bool add) {
		updateCount(count, add, woodOperandIcon, woodTensIcon, woodOnesIcon);
	}

	void ResourceCostManager::displayCosts(Costs costs) {
		auto stoneCosts = costs.stoneCost;
		auto manaCosts = costs.manaCost;
		auto woodCosts = costs.woodCost;

		if (stoneCosts > 0) {
			stoneIcon->changeIcon(ChunkMapEngine::Icon{ SUB, 0 });
			updateStoneCounter(stoneCosts, false);
		}
		else if (stoneCosts == 0) {
			stoneIcon->changeIcon(ChunkMapEngine::Icon{ 0, 3 });
			stoneTensIcon->changeIcon(ChunkMapEngine::Icon{ 0, 0 });
			stoneOnesIcon->changeIcon(ChunkMapEngine::Icon{ 0, 0 });
			stoneOperandIcon->changeIcon(ChunkMapEngine::Icon{ 1, 0 });
		}
		else {
			stoneIcon->changeIcon(ChunkMapEngine::Icon{ ADD, 0 });
			updateStoneCounter(-stoneCosts, true);
		}

		if (manaCosts > 0) {
			manaIcon->changeIcon(ChunkMapEngine::Icon{ SUB, 1 });
			updateManaCounter(manaCosts, false);
		}
		else if (manaCosts == 0) {
			manaIcon->changeIcon(ChunkMapEngine::Icon{ 0, 3 });
			manaTensIcon->changeIcon(ChunkMapEngine::Icon{ 0, 0 });
			manaOnesIcon->changeIcon(ChunkMapEngine::Icon{ 0, 0 });
			manaOperandIcon->changeIcon(ChunkMapEngine::Icon{ 1, 0 });
		}
		else {
			manaIcon->changeIcon(ChunkMapEngine::Icon{ ADD, 1 });
			updateManaCounter(-manaCosts, true);
		}

		if (woodCosts > 0) {
			woodIcon->changeIcon(ChunkMapEngine::Icon{ SUB, 2 });
			updateWoodCounter(woodCosts, false);
		}
		else if (woodCosts == 0) {
			woodIcon->changeIcon(ChunkMapEngine::Icon{ 0, 3 });
			woodTensIcon->changeIcon(ChunkMapEngine::Icon{ 0, 0 });
			woodOnesIcon->changeIcon(ChunkMapEngine::Icon{ 0, 0 });
			woodOperandIcon->changeIcon(ChunkMapEngine::Icon{ 1, 0 });
		}
		else {
			woodIcon->changeIcon(ChunkMapEngine::Icon{ ADD, 2 });
			updateWoodCounter(-woodCosts, true);
		}
	}

	void ResourceCostManager::displayStoneAction() {
		actionIcon->changeIcon(ChunkMapEngine::Icon{ ACT, MINE });
		displayCosts(stoneGain);
	}
	void ResourceCostManager::displayManaAction() {
		actionIcon->changeIcon(ChunkMapEngine::Icon{ ACT, MINE });
		displayCosts(manaGain);
	}
	void ResourceCostManager::displayWoodAction() {
		actionIcon->changeIcon(ChunkMapEngine::Icon{ ACT, MINE });
		displayCosts(woodGain);
	}
	void ResourceCostManager::displayIslandAction() {
		actionIcon->changeIcon(ChunkMapEngine::Icon{ ACT, CREATE });
		displayCosts(islandCosts);
	}
	void ResourceCostManager::displayBridgeAction() {
		actionIcon->changeIcon(ChunkMapEngine::Icon{ ACT, CREATE });
		displayCosts(bridgeCosts);
	}
	void ResourceCostManager::displayPortalAction() {
		actionIcon->changeIcon(ChunkMapEngine::Icon{ ACT, USE_PORTAL });
		displayCosts(portalCosts);
	}

	void ResourceCostManager::resetInfoIcons() {
		actionIcon->changeIcon(ChunkMapEngine::Icon{ 0, 3 });

		stoneIcon->changeIcon(ChunkMapEngine::Icon{ 0, 3 });
		stoneTensIcon->changeIcon(ChunkMapEngine::Icon{ 0, 0 });
		stoneOnesIcon->changeIcon(ChunkMapEngine::Icon{ 0, 0 });
		stoneOperandIcon->changeIcon(ChunkMapEngine::Icon{ 1, 0 });

		manaIcon->changeIcon(ChunkMapEngine::Icon{ 0, 3 });
		manaTensIcon->changeIcon(ChunkMapEngine::Icon{ 0, 0 });
		manaOnesIcon->changeIcon(ChunkMapEngine::Icon{ 0, 0 });
		manaOperandIcon->changeIcon(ChunkMapEngine::Icon{ 1, 0 });

		woodIcon->changeIcon(ChunkMapEngine::Icon{ 0, 3 });
		woodTensIcon->changeIcon(ChunkMapEngine::Icon{ 0, 0 });
		woodOnesIcon->changeIcon(ChunkMapEngine::Icon{ 0, 0 });
		woodOperandIcon->changeIcon(ChunkMapEngine::Icon{ 1, 0 });
	}

	void ResourceCostManager::draw(ChunkMapEngine::BaseGame* game) {
		canvas.draw(game);
	}
}