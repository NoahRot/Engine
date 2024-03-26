#include "Core/CoreFnc.hpp"

namespace eng {

// === Core functions === //

void configure(const Configuration& config) {
    eng::_intern_::_Core::instance().configure(config);
}

Configuration get_configuration() {
    return eng::_intern_::_Core::instance().get_configuration();
}

void quit() {
    eng::_intern_::_Core::instance().quit();
}

bool is_configure() {
    return eng::_intern_::_Core::instance().is_configure();
}

bool is_running() {
    return eng::_intern_::_Core::instance().is_running();
}

bool is_valid(Index id) {
    return id != UNVALID;
}

// === OpenGL functions === //

std::string info_vendor(){
    return (const char*)glGetString(GL_VENDOR);
}

std::string info_renderer(){
    return (const char*)glGetString(GL_RENDERER);
}

std::string info_version(){
    return (const char*)glGetString(GL_VERSION);
}

std::string info_shading_language(){
    return (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
}

int get_max_texture_slots() {
    int nbrTexUnits;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &nbrTexUnits);
    return nbrTexUnits;
}

int get_max_vertex_attributes() {
    int maxVertex;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertex);
    return maxVertex;
}


// === Getter functions === //

Window& get_window() {
    return Window::instance();
}

Timer& get_timer() {
    return Timer::instance();
}

log::Logger& get_logger() {
    return log::Logger::instance();
}

Event& get_event() {
    return Event::instance();
}

Keyboard& get_keyboard() {
    return Keyboard::instance();
}

Mouse& get_mouse() {
    return Mouse::instance();
}

Renderer& get_renderer() {
    return Renderer::Instance();
}

}