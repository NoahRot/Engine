#include "Engine/Configuration.hpp"

namespace ora {

Configuration load_config(const std::string& path) {

    // Load configuration from a data file
    Configuration config;
    DataFile data_file;
    if (!data_file.load_txt(path)) {
        return config;
    }

    // Get the reference to the root
    DataNode& node = data_file.get();

    // Logger parameters

    config.log_file_name = node["engine"]["logger"]["file_name"].content;
    config.log_state = (int)node["engine"]["logger"]["state"];

    // Window parameters

    config.win_width = node["engine"]["window"]["width"];
    config.win_height = node["engine"]["window"]["height"];
    config.win_title = node["engine"]["window"]["title"].content;
    config.win_sdl_flags = node["engine"]["window"]["sdl_flags"];
    config.win_win_flags = node["engine"]["window"]["win_flags"];

    // Timer parameter

    config.tim_fps = node["engine"]["timer"]["fps"];

    // Audio parameters

    config.aud_mix_flags = node["engine"]["audio"]["mix_flags"];
    config.aud_frequency = node["engine"]["audio"]["frequency"];
    config.aud_format = (int)node["engine"]["audio"]["format"];
    config.aud_channels = node["engine"]["audio"]["channels"];
    config.aud_chunksize = node["engine"]["audio"]["chunksize"];

    // Texture parameters

    config.tex_pixel_perfect = (int)node["engine"]["texture"]["pixel_perfect"];

    // Return configuration
    return config;
}

void save_config(const Configuration& config, const std::string& path){

    // Create data file
    DataFile data_file;

    // Create root node
    DataNode& node = data_file.get();

    // Logger parameters

    node["engine"]["logger"]["file_name"] = config.log_file_name;
    node["engine"]["logger"]["state"] = config.log_state;

    // Window parameters

    node["engine"]["window"]["width"] = config.win_width;
    node["engine"]["window"]["height"] = config.win_height;
    node["engine"]["window"]["title"] = config.win_title;
    node["engine"]["window"]["sdl_flags"] = config.win_sdl_flags;
    node["engine"]["window"]["win_flags"] = config.win_win_flags;

    // Timer parameter

    node["engine"]["timer"]["fps"] = config.tim_fps;

    // Audio parameters

    node["engine"]["audio"]["mix_flags"] = config.aud_mix_flags;
    node["engine"]["audio"]["frequency"] = config.aud_frequency;
    node["engine"]["audio"]["format"] = config.aud_format;
    node["engine"]["audio"]["channels"] = config.aud_channels;
    node["engine"]["audio"]["chunksize"] = config.aud_chunksize;

    // Texture parameters

    node["engine"]["texture"]["pixel_perfect"] = config.tex_pixel_perfect;

    // Save in file
    
    data_file.save_txt(path);
}

}