#include "Engine/Configuration.hpp"

namespace ora {

Configuration load_config_xml(const std::string& path) {

    // Create XML file and configuration
    XML_Manager xml;
    Configuration config;

    // Read XML file
    if (!xml.read(path)) {
        Logger::instance().log(LogLevel::Error, xml.get_error());
        return config;
    }

    // Create a mapping of the XML file
    XML_Mapping mapping = xml.get_map();

    // Check if engine field exist
    if (!mapping.validity("engine")) {
        Logger::instance().log(LogLevel::Error, "No 'engine' found int xml configuration file");
        return config;
    }

    XML_Mapping& map_eng = mapping["engine"];

    // Logger parameters

    if (!map_eng.validity("logger")) {
        Logger::instance().log(LogLevel::Error, "No 'logger' found int xml configuration file");
    }else{
        XML_Mapping& current_map = map_eng["logger"];
        if (current_map.validity("file_name")) {
            config.log_file_name = current_map["file_name"].get_string();
        }
        if (current_map.validity("state")) {
            config.log_state = current_map["state"].get_int();
        }
    }

    // Window parameters

    if (!map_eng.validity("window")) {
        Logger::instance().log(LogLevel::Error, "No 'window' found int xml configuration file");
    }else{
        XML_Mapping& current_map = map_eng["window"];
        if (current_map.validity("width")) {
            config.win_width = current_map["width"].get_uint32();
        }
        if (current_map.validity("height")) {
            config.win_height = current_map["height"].get_uint32();
        }
        if (current_map.validity("title")) {
            config.win_title = current_map["title"].get_string();
        }
        if (current_map.validity("sdl_flags")) {
            config.win_sdl_flags = current_map["sdl_flags"].get_uint32();
        }
        if (current_map.validity("win_flags")) {
            config.win_win_flags = current_map["win_flags"].get_uint32();
        }
    }

    // Timer parameter

    if (!map_eng.validity("timer")) {
        Logger::instance().log(LogLevel::Error, "No 'timer' found int xml configuration file");
    }else{
        XML_Mapping& current_map = map_eng["timer"];
        if (current_map.validity("fps")) {
            config.tim_fps = current_map["fps"].get_uint32();
        }
    }

    // Audio parameters

    if (!map_eng.validity("audio")) {
        Logger::instance().log(LogLevel::Error, "No 'audio' found int xml configuration file");
    }else{
        XML_Mapping& current_map = map_eng["audio"];
        if (current_map.validity("mix_flags")) {
            config.aud_mix_flags = current_map["mix_flags"].get_int();
        }
        if (current_map.validity("frequency")) {
            config.aud_frequency = current_map["frequency"].get_int();
        }
        if (current_map.validity("format")) {
            config.aud_format = current_map["format"].get_int();
        }
        if (current_map.validity("channels")) {
            config.aud_channels = current_map["channels"].get_int();
        }
        if (current_map.validity("chunksize")) {
            config.aud_chunksize = current_map["chunksize"].get_int();
        }
    }

    // Texture parameters

    if (!map_eng.validity("texture")) {
        Logger::instance().log(LogLevel::Error, "No 'timer' found int xml configuration file");
    }else{
        XML_Mapping& current_map = map_eng["texture"];
        if (current_map.validity("pixel_perfect")) {
            config.tex_pixel_perfect = current_map["pixel_perfect"].get_bool();
        }
    }

    // Return configuration
    return config;
}

void save_config_xml(const Configuration& config, const std::string& path){

    // Create the XML node system
    XML_Node initial;
    initial.title = "engine";
    initial.parent = nullptr;

    // Logger parameters

    XML_Node log_node;
    log_node.title = "logger";
    log_node.parent = &initial;

    log_node.children.push_back(XML_Node("file_name", config.log_file_name, &log_node));
    log_node.children.push_back(XML_Node("state", std::to_string(config.log_state), &log_node));

    initial.children.push_back(log_node);

    // Window parameters

    XML_Node win_node;
    win_node.title = "window";
    win_node.parent = &initial;

    win_node.children.push_back(XML_Node("width", std::to_string(config.win_width), &win_node));
    win_node.children.push_back(XML_Node("height", std::to_string(config.win_height), &win_node));
    win_node.children.push_back(XML_Node("title", config.win_title, &win_node));
    win_node.children.push_back(XML_Node("sdl_flags", std::to_string(config.win_sdl_flags), &win_node));
    win_node.children.push_back(XML_Node("win_flags", std::to_string(config.win_win_flags), &win_node));

    initial.children.push_back(win_node);

    // Timer parameter

    XML_Node tim_node;
    tim_node.title = "timer";
    tim_node.parent = &initial;

    tim_node.children.push_back(XML_Node("fps", std::to_string(config.tim_fps), &tim_node));

    initial.children.push_back(tim_node);

    // Audio parameters

    XML_Node aud_node;
    aud_node.title = "audio";
    aud_node.parent = &initial;

    aud_node.children.push_back(XML_Node("mix_flags", std::to_string(config.aud_mix_flags), &aud_node));
    aud_node.children.push_back(XML_Node("frequency", std::to_string(config.aud_frequency), &aud_node));
    aud_node.children.push_back(XML_Node("format", std::to_string(config.aud_format), &aud_node));
    aud_node.children.push_back(XML_Node("channels", std::to_string(config.aud_channels), &aud_node));
    aud_node.children.push_back(XML_Node("chunksize", std::to_string(config.aud_chunksize), &aud_node));

    initial.children.push_back(aud_node);

    // Texture parameters

    XML_Node tex_node;
    tex_node.title = "texture";
    tex_node.parent = &initial;

    tex_node.children.push_back(XML_Node("pixel_perfect", std::to_string(config.tex_pixel_perfect), &tex_node));

    initial.children.push_back(tex_node);

    // Save in xml file
    XML_Manager xml;
    xml.push_root_node(initial);
    xml.save(path);
}

}