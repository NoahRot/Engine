#pragma once

#include "Logger/Logger.hpp"
#include "Core/Configuration.hpp"

namespace eng {
    
namespace _intern_ {

class _Core {
public:
    /// @brief Destructor
    ~_Core();

    _Core(const _Core&) = delete;
    _Core& operator=(const _Core&) = delete;

    /// @brief Get the instance of the class
    /// @return The instance of the class
    static _Core& Instance();

    /// @brief Set the configuration. Sent a warning if the configuration has already been set.
    /// @param config The configuration that will be set
    void Configure(const Configuration& config);

    /// @brief Quit the application
    void Quit();

    /// @brief Getter method to obtain the configuration of the engine
    /// @return The configuration of the engine
    Configuration GetConfiguration() const;

    /// @brief To know if the engine has been configured
    /// @return True if the engine has been configured, False otherwise
    bool IsConfigure() const;

    /// @brief Method to know if the application is running
    /// @return If the application is running
    bool IsRunning() const;

private:
    /// @brief Constructor
    _Core();

    /// @brief If the configuration has been made
    bool m_isConfigure;

    /// @brief If the application is running
    bool m_isRunning;

    /// @brief The configuration of the engine
    Configuration m_config;
};

}

}