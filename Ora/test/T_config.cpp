#include "Engine/Configuration.hpp"

int main(int argc, char* argv[]) {
    
    //ora::Configuration config = ora::load_config("test/log/config.xml");
    ora::Configuration config;
    config.win_title = "Config test";
    config.win_width = 800;
    config.win_height = 600;
    config.log_file_name = "test/log/Log_config.log";
    config.tim_fps = 120;

    config = ora::load_config("test/test.config");

    ora::_init_logger(config.log_state, config.log_file_name);

    ora::save_config(config, "test/test.config");

    return 0;
}