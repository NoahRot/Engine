#pragma once

#include <string>

#include "Event/Event.hpp"

#include "Asset/AssetManager.hpp"

#include "Core/CoreFnc.hpp"

#include "Tools/Test.hpp"

#include "Audio/Music.hpp"
#include "Audio/Sound.hpp"

namespace eng::test {

class TestAudio : public eng::test::Test {
public:
    TestAudio()
    : m_asset_manager(eng::AssetManager::instance()), m_keyboard(eng::Keyboard::instance()), m_music(nullptr)
    {}

    void load(const std::string& music_path, const std::string& sound_path) {
        // Load music
        m_music_id = m_asset_manager.load_music(music_path);
        if (m_music_id == UNVALID) {
            get_logger().error("TestAudio", "Can't load music : " + music_path);
        }else{
            m_music = m_asset_manager.get_music(m_music_id);
            m_music->volume(0.5f);
        }

        // Load sound
        m_sound_id = m_asset_manager.load_sound(sound_path);
        if (m_sound_id == UNVALID) {
            get_logger().error("TestAudio", "Can't load sound : " + sound_path);
        }else{
            m_sound = m_asset_manager.get_sound(m_sound_id);
            m_sound->volume(0.2f);
        }
    }

    virtual void update() override {
        if (m_keyboard.key_press(SDL_SCANCODE_SPACE) and m_music) {
            m_music->play();            
        }

        if (m_keyboard.key_press(SDL_SCANCODE_LSHIFT) and m_sound) {
            m_sound->play();
        }
    }

    virtual void draw() override {}

private:
    AssetManager& m_asset_manager;

    Keyboard& m_keyboard;

    Index m_music_id;
    Music m_music;

    Index m_sound_id;
    Sound m_sound;
};

}