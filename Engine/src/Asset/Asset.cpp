#include "Asset/Asset.hpp"

namespace eng {

Asset::Asset(AssetType type)
: m_type(type), m_index()
{}

AssetType Asset::get_type() const {
    return m_type;
}

Index Asset::get_index() {
    return (Index)m_index;
}

}