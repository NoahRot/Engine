#pragma once

#include "Core/UniqueIndex.hpp"
#include "Core/CoreFnc.hpp"

#include "Asset/Asset.hpp"

#include "Audio/Music.hpp"
#include "Audio/Sound.hpp"

#include <map>
#include <iostream>

namespace eng {

class AssetManager {
public:
    AssetManager(const AssetManager&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;

    ~AssetManager();

    static AssetManager& instance();

    Index load_asset(const std::string& path, AssetType type);

    void unload_asset(Index index);

    template<typename T>
    T* get_asset(Index index);

    Music_* get_music(Index index);

    Sound_* get_sound(Index index);

private:
    AssetManager();

    std::map<Index, Asset*> m_table_asset;
};

template<typename T>
T* AssetManager::get_asset(Index index) {
    return static_cast<T*>(m_table_asset[index]);
}

}