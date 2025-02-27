#pragma once

#include <memory>

#include "Orange.hpp"

class TestProgram {
public:
    TestProgram(const std::string& test_name)
    : m_engine(nullptr)
    {
        m_config.log_file_name = "test_name.log";
        m_config.win_width = 1280;
        m_config.win_height = 720;
        m_config.win_title = "TEST - " + test_name;
        m_config.tim_fps = 60;

        m_engine = std::make_shared<ora::OrangeEngine>(m_config);
    }

    virtual void event() {}

    virtual void update() {}

    virtual void draw() {}

    inline void run() {

        while (!m_engine->event.is_quitting())
        {
            m_engine->event.manage();
            glClear(GL_COLOR_BUFFER_BIT);
            glClear(GL_DEPTH_BUFFER_BIT);

            event();

            update();

            draw();

            m_engine->timer.loop();
        
            m_engine->window.present();
        }
        
    }

protected:
    ora::Configuration m_config;
    std::shared_ptr<ora::OrangeEngine> m_engine;
};