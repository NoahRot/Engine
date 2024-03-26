#pragma once

#include <External/glad/glad.h>

#include "Core/Core.hpp"
#include "Core/Window.hpp"
#include "Core/Timer.hpp"
#include "Core/UniqueIndex.hpp"

#include "Logger/Logger.hpp"

#include "Event/Event.hpp"

#include "Graphic/Renderer.hpp"

namespace eng {

struct Configuration;
class Window;
class Timer;
class Keyboard;
class Mouse;
class Renderer;
class Audio;

namespace log {
class Logger;
}



// === Core functions === //

/// @brief Configuration of the engine
/// @warning If the configuration has already been set, the new configuration won't replace the old one.
/// @param config The configuration of the engine.
void configure(const Configuration& config);

/// @brief Get the configuration of the engine
/// @return The configuration of the engine
Configuration get_configuration();

/// @brief Quit the application
void quit();

/// @brief Function to know if the engine is configure
/// @return If the engine is configure
bool is_configure();

/// @brief Function to know if the application is running
/// @return If the application is running
bool is_running();

/// @brief Function to know if an index is valid
/// @param id The index
/// @return If the index is valid
bool is_valid(Index id);



// === OpenGL informations === //

std::string info_vendor();

std::string info_renderer();

std::string info_version();

std::string info_shading_language();

int get_max_texture_slots();

int get_max_vertex_attributes();



// === Getter functions === //

/// @brief Function to get the instance of Window
/// @return The instance of Window
Window& get_window();

/// @brief Function to get the instance of Timer
/// @return The instance of Timer
Timer& get_timer();

/// @brief Function to get the instance of Logger
/// @return The instance of Logger
eng::log::Logger& get_logger();

/// @brief Function to get the instance of Event
/// @return The instance of Event
Event& get_event();

/// @brief Function to get the instance of Keyboard
/// @return The instance of Keyboard
Keyboard& get_keyboard();

/// @brief Function to get the instance of Mouse
/// @return The instance of Mouse
Mouse& get_mouse();

/// @brief Function to get the instance of Renderer
/// @return The instance of Renderer
Renderer& get_renderer();

}