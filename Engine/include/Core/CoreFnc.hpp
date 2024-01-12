#pragma once

#include <External/glad/glad.h>

#include "Core/Core.hpp"
#include "Core/Window.hpp"
#include "Core/Timer.hpp"

#include "Logger/Logger.hpp"

#include "Event/Event.hpp"

namespace eng {

struct Configuration;
class Window;
class Timer;
class Keyboard;
class Mouse;

namespace log {
class Logger;
}



// === Core functions === //

/// @brief Configuration of the engine
/// @warning If the configuration has already been set, the new configuration won't be set.
/// @param config The configuration of the engine.
void Configure(const Configuration& config);

/// @brief Get the configuration of the engine
/// @return The configuration of the engine
Configuration GetConfiguration();

/// @brief Quit the application
void Quit();

/// @brief Function to know if the engine is configure
/// @return If the engine is configure
bool IsConfigure();

/// @brief Function to know if the application is running
/// @return If the application is running
bool IsRunning();



// === OpenGL informations === //

std::string InfoVendor();

std::string InfoRenderer();

std::string InfoVersion();

std::string InfoShadingLanguage();

int GetMaxTextureSlots();



// === Getter functions === //

/// @brief Function to get the instance of Window
/// @return The instance of Window
Window& GetWindow();

/// @brief Function to get the instance of Timer
/// @return The instance of Timer
Timer& GetTimer();

/// @brief Function to get the instance of Logger
/// @return The instance of Logger
eng::log::Logger& GetLogger();

/// @brief Function to get the instance of Event
/// @return The instance of Event
Event& GetEvent();

/// @brief Function to get the instance of Keyboard
/// @return The instance of Keyboard
Keyboard& GetKeyboard();

/// @brief Function to get the instance of Mouse
/// @return The instance of Mouse
Mouse& GetMouse();


}