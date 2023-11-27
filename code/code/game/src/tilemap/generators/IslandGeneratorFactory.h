#pragma once

#include "../../Parameters.h"
#include "IslandGenerator.h"
#include "StartIslandGenerator.h"
#include "PlantIslandGenerator.h"
#include "StoneIslandGenerator.h"
#include "PortalIslandGenerator.h"
#include "ManaIslandGenerator.h"

namespace WorldExtender {
    class IslandGeneratorFactory {
    public:
        static IslandGenerator* createGenerator(int islandType) {
            if (islandType == BASE_I) {
                return new IslandGenerator();
            }
            else if (islandType == START_I) {
                return new StartIslandGenerator();
            }
            else if (islandType == PLANT_I) {
                return new PlantIslandGenerator();
            }
            else if (islandType == STONE_I) {
                return new StoneIslandGenerator();
            }
            else if (islandType == MANA_I) {
                return new ManaIslandGenerator();
            }
            else if (islandType == PORTAL_I) {
                return new PortalIslandGenerator();
            }
            else {
                return new IslandGenerator();
            }
        }
    };
}