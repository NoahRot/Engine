#include "Engine/Configuration.hpp"

int main(int argc, char* argv[]) {
    
    ora::Configuration config = ora::load_config_xml("test/config.xml");

    ora::_init_logger(config.log_state, config.log_file_name);

    ora::save_config_xml(config, "test/config.xml");

    return 0;
}