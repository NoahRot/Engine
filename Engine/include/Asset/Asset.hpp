#pragma once

#include "Core/UniqueIndex.hpp"

namespace eng {

enum struct AssetType {
    None,
    Music,
    Sound
    // Texture, Font, Shader
};

class Asset {
public:
    Asset(AssetType type = AssetType::None);

    AssetType get_type() const;

    Index get_index();

protected:
    AssetType m_type;

    UniqueIndex m_index;
};

}