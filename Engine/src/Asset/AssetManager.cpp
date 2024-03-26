#include "Asset/AssetManager.hpp"

namespace eng {

AssetManager::AssetManager() {
    // Check if the core is configure
    if (!is_configure()) {
        get_logger().fatal("Asset Manager", "Engine is not configure");
        exit(EXIT_FAILURE);
    }

    std::cout << "DEBUG : AssetManager created" << std::endl;
}

AssetManager::~AssetManager() {
    for (auto asset : m_table_asset) {
        std::cout << "DEBUG : AssetManager => Asset destroyed" << std::endl;
        delete asset.second;
    }
    std::cout << "DEBUG : AssetManager destroyed" << std::endl;
}

AssetManager& AssetManager::instance() {
    static AssetManager s_instance;
    return s_instance;
}

Index AssetManager::load_asset(const std::string& path, AssetType type) {
    log::Logger& logger = get_logger();
    switch(type) {
        case AssetType::None:
            logger.error("Asset Manager", "Can't load asset. Type None.");
            return UNVALID;

        case AssetType::Music:
            {// Load the music
            Mix_Music* music_data = Mix_LoadMUS(path.c_str());

            // Check if the music has been loaded successfully
            if (!music_data) {
                logger.error("Asset Manager", "Can't load music. Path : " + path);
                return UNVALID;
            }

            // Create and add the music
            Music_* music = new Music_(music_data);
            m_table_asset[music->get_index()] = music;
            return music->get_index();}

        case AssetType::Sound:
            {// Load the sound
            Mix_Chunk* sound_data = Mix_LoadWAV(path.c_str());

            // Check if the sound has been loaded successfully
            if (!sound_data) {
                logger.error("Asset Manager", "Can't load sound. Path : " + path);
                return UNVALID;
            }

             // Create and add the sound
            Sound_* sound = new Sound_(sound_data);
            m_table_asset[sound->get_index()] = sound;
            return sound->get_index();}     
    }
    logger.error("Asset Manager", "Can't load asset. Type unknown. Type : " + std::to_string((int)type));
    return UNVALID;
}

void AssetManager::unload_asset(Index index) {
    delete m_table_asset[index];
    m_table_asset.erase(index);
}

Music_* AssetManager::get_music(Index index) {
    return static_cast<Music_*>(m_table_asset[index]);
}

Sound_* AssetManager::get_sound(Index index) {
    return static_cast<Sound_*>(m_table_asset[index]);
}

}