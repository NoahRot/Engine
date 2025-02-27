#include "Asset/AssetManager.hpp"

// Using stb_image
#define STB_IMAGE_IMPLEMENTATION
#include "External/stb_image/stb_image.h"

namespace eng {

AssetManager::AssetManager() {
    // Check if the core is configure
    if (!is_configure()) {
        get_logger().fatal("Asset Manager", "Engine is not configure");
        exit(EXIT_FAILURE);
    }

    std::cout << "DEBUG : AssetManager created" << std::endl;
}

AssetManager::~AssetManager() {
    for (auto asset : m_table_asset) {
        std::cout << "DEBUG : AssetManager => Asset destroyed" << std::endl;
        delete asset.second;
    }
    std::cout << "DEBUG : AssetManager destroyed" << std::endl;
}

AssetManager& AssetManager::instance() {
    static AssetManager s_instance;
    return s_instance;
}

Index AssetManager::load_music(const std::string& path) {
    // Load the music
    Mix_Music* music_data = Mix_LoadMUS(path.c_str());

    // Check if the music has been loaded successfully
    if (!music_data) {
        get_logger().error("Asset Manager", "Can't load music. Path : " + path);
        return UNVALID;
    }

    // Create and add the music
    Music_* music = new Music_(music_data);
    m_table_asset[music->get_index()] = music;
    return music->get_index();
}

Index AssetManager::load_sound(const std::string& path) {
    // Load the sound
    Mix_Chunk* sound_data = Mix_LoadWAV(path.c_str());

    // Check if the sound has been loaded successfully
    if (!sound_data) {
        get_logger().error("Asset Manager", "Can't load sound. Path : " + path);
        return UNVALID;
    }

        // Create and add the sound
    Sound_* sound = new Sound_(sound_data);
    m_table_asset[sound->get_index()] = sound;
    return sound->get_index();
}

Index AssetManager::load_texture(const std::string& path, bool pixel_art) {
    // Read the file from top to bottom
    stbi_set_flip_vertically_on_load(true);

    // Load the image
    int width, height, bpp;
    unsigned char* buffer = stbi_load(path.c_str(), &width, &height, &bpp, 4); // 4 because RGBA

    // Generate the texture and bind it
    uint32_t texture_index;
    glGenTextures(1, &texture_index);
    glBindTexture(GL_TEXTURE_2D, texture_index);

    // Set the parameters of the texture
    if (pixel_art) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }else{
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,  GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_CLAMP_TO_EDGE);

    // Send the texture to openGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Check if the buffer contains data
    if (buffer) {
        stbi_image_free(buffer);
    }else{
        get_logger().error("Asset Manager", "Can't load texture : " + path);
        glDeleteTextures(1, &texture_index);
        return UNVALID;
    }

    // Create and add the texture
    Texture_* texture = new Texture_(texture_index, width, height, bpp);
    m_table_asset[texture->get_index()] = texture;
    get_logger().debug("Asset Manager", "BPP = " + std::to_string(bpp));

    return texture->get_index();
}

Index AssetManager::create_texture(uint32_t width, uint32_t height, ColorBit color, bool pixel_art) {
    std::vector<std::array<unsigned char, 4>> data(width * height, std::array<unsigned char,4>{color.r, color.g, color.b, color.a});

    // Generate the texture and bind it
    uint32_t texture_index;
    glGenTextures(1, &texture_index);
    glBindTexture(GL_TEXTURE_2D, texture_index);

    // Set the parameters of the texture
    if (pixel_art) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }else{
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,  GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_CLAMP_TO_EDGE);

    // Send the texture to openGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data[0]);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Create and add the texture
    Texture_* texture = new Texture_(texture_index, width, height, 3);
    m_table_asset[texture->get_index()] = texture;

    return texture->get_index();
}

Index AssetManager::load_shader(const std::string& vertex_path, const std::string& fragment_path) {
    // Load shaders source code
    std::string vertex_source_code;
    std::string fragment_source_code;
    if (!eng::_intern_::shader_load_source(fragment_path, fragment_source_code)) {
        return UNVALID;
    }
    if (!eng::_intern_::shader_load_source(vertex_path, vertex_source_code)) {
        return UNVALID;
    }
    
    // Create shaders
    uint32_t vertex_shader;
    uint32_t fragment_shader;
    if (!eng::_intern_::shader_create_shader(GL_VERTEX_SHADER, vertex_shader, vertex_source_code)) {
        glDeleteShader(vertex_shader);
        return UNVALID;
    }
    if (!eng::_intern_::shader_create_shader(GL_FRAGMENT_SHADER, fragment_shader, fragment_source_code)) {
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        return UNVALID;
    }

    // Create shader program
    uint32_t shader_program;
    if (!eng::_intern_::shader_create_program(vertex_shader, fragment_shader, shader_program)) {
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        return UNVALID;
    } 

    // Delete shaders
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // Create and put the shader in the table
    eng::Shader_* shader = new eng::Shader_(shader_program);
    m_table_asset[shader->get_index()] = shader;
    return shader->get_index();
}

Index AssetManager::load_font(const std::string& path, uint32_t size) {
    // Load font
    FT_Face face;
    if (FT_New_Face(Font_::s_ft_lib, path.c_str(), 0, &face))
    {
        get_logger().error("Asset Manager", "Can't load font : " + path);
        return UNVALID;
    }

    // Set police size
    FT_Set_Pixel_Sizes(face, 0, size);

    // Prepare the size
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Create characters map
    std::map<char, Character> table_character;
    uint32_t atlas_w(0), atlas_h(0);

    for (unsigned char c = 0 ; c < 128 ; ++c) {
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            get_logger().error("Asset Manager", "Can't load character" + std::to_string((char)c) + " from font " + path);
        }

        // Create Character
        table_character[c] = Character{
            0.0f, 0.0f, 0.0f, 0.0f,     // u, v, w, h of the texture
            face->glyph->bitmap.width,  // width
            face->glyph->bitmap.rows,   // rows
            face->glyph->bitmap_left,   // Bearing left
            face->glyph->bitmap_top,    // Bearing right
            face->glyph->advance.x      // Advance
        };

        // Update texture atlas dimensions
        atlas_h = std::max(atlas_h, (uint32_t)face->glyph->bitmap.rows);
        atlas_w += face->glyph->bitmap.width;
    }

    // Create altas texture
    Index texutre_id = create_texture(atlas_w, atlas_h, ColorBit{0, 0, 0, 0});
    get_texture(texutre_id)->bind();

    int x_progression(0);
    for (auto& c : table_character) {
        FT_Load_Char(face, c.first, FT_LOAD_RENDER);
        glTexSubImage2D(GL_TEXTURE_2D, 0, x_progression, 0, c.second.bw, c.second.bh, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

        // Set the position and dimension on the texture atlas
        c.second.u = x_progression/(float)atlas_w;
        c.second.w = c.second.bw/(float)atlas_w;
        c.second.h = c.second.bh/(float)atlas_h;

        // Progress
        x_progression += c.second.bw;
    }

    // Create the font
    Font_* font = new Font_(table_character, texutre_id, size);
    m_table_asset[font->get_index()] = font;
    
    return font->get_index();
}

void AssetManager::unload_asset(Index index) {
    delete m_table_asset[index];
    m_table_asset.erase(index);
}

Music_* AssetManager::get_music(Index index) {
    return static_cast<Music_*>(m_table_asset[index]);
}

Sound_* AssetManager::get_sound(Index index) {
    return static_cast<Sound_*>(m_table_asset[index]);
}

Texture_* AssetManager::get_texture(Index index) {
    return static_cast<Texture_*>(m_table_asset[index]);
}

Shader_* AssetManager::get_shader(Index index) {
    return static_cast<Shader_*>(m_table_asset[index]);
}

Font_* AssetManager::get_font(Index index) {
    return static_cast<Font_*>(m_table_asset[index]);
}

}