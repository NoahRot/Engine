#include "Engine/Engine.hpp"

namespace ora {

OrangeEngine::OrangeEngine(const Configuration& init)
:   logger(_init_logger(init.log_state, init.log_file_name)), 
    window(init.win_width, init.win_height, init.win_title, init.win_sdl_flags, init.win_win_flags),
    event(&window),
    timer(init.tim_fps),
    audio_manager(init.aud_mix_flags, init.aud_frequency, init.aud_format, init.aud_channels, init.aud_chunksize),
    texture_manager(init.tex_pixel_perfect), 
    font_manager(&texture_manager)
{
    logger.log(ora::Info, " ====== Engine created ====== ");
}

OrangeEngine::~OrangeEngine() {
    logger.log(ora::Info, " ====== Engine destroyed ====== ");
}

}