#pragma once

#include <filesystem>

#define GET_STRING(x) #x
#define GET_DIR(x) GET_STRING(x)

namespace fs = std::filesystem;

namespace ChunkMapEngine {
    inline fs::path resolveAssetPath(const fs::path &relativeAssetPath) {
        auto mergedPath = (GET_DIR(DEBUG_ASSET_ROOT) / relativeAssetPath).make_preferred();
        return fs::canonical(mergedPath);
    }
}