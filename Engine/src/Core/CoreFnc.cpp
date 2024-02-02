#include "Core/CoreFnc.hpp"

namespace eng {

// === Core functions === //

void Configure(const Configuration& config) {
    eng::_intern_::_Core::Instance().Configure(config);
}

Configuration GetConfiguration() {
    return eng::_intern_::_Core::Instance().GetConfiguration();
}

void Quit() {
    eng::_intern_::_Core::Instance().Quit();
}

bool IsConfigure() {
    return eng::_intern_::_Core::Instance().IsConfigure();
}

bool IsRunning() {
    return eng::_intern_::_Core::Instance().IsRunning();
}

bool IsValid(Index id) {
    return id != UNVALID;
}

// === OpenGL functions === //

std::string InfoVendor(){
    return (const char*)glGetString(GL_VENDOR);
}

std::string InfoRenderer(){
    return (const char*)glGetString(GL_RENDERER);
}

std::string InfoVersion(){
    return (const char*)glGetString(GL_VERSION);
}

std::string InfoShadingLanguage(){
    return (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
}

int GetMaxTextureSlots() {
    int nbrTexUnits;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &nbrTexUnits);
    return nbrTexUnits;
}

int GetMaxVertexAttributes() {
    int maxVertex;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertex);
    return maxVertex;
}


// === Getter functions === //

Window& GetWindow() {
    return Window::Instance();
}

Timer& GetTimer() {
    return Timer::Instance();
}

log::Logger& GetLogger() {
    return log::Logger::Instance();
}

Event& GetEvent() {
    return Event::Instance();
}

Keyboard& GetKeyboard() {
    return Keyboard::Instance();
}

Mouse& GetMouse() {
    return Mouse::Instance();
}

Renderer& GetRenderer() {
    return Renderer::Instance();
}

Audio& GetAudio() {
    return Audio::Instance();
}

}