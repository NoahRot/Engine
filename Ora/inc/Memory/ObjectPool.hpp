#pragma once

#include <inttypes.h>
#include <array>
#include <stack>
#include <optional>

#include "Engine/Constant.hpp"

namespace ora {

/// @brief Container of objects
/// @tparam T Type of the objects
/// @tparam MAX_ELEMENTS Maximum number of elements
template<typename T, uint32_t MAX_ELEMENTS>
class ObjectPool {

public:

    /// @brief Constructor
    ObjectPool();

    /// @brief Get an element
    /// @param index Index of the element
    /// @return A reference to the element
    /// @warning Do not check if the object exist. 
    /// Use validity method to ensure the existance of the object
    T& get(int32_t index);

    /// @brief Get an element
    /// @param index Index of the element
    /// @return A constant reference to the element
    /// @warning Do not check if the object exist. 
    /// Use validity method to ensure the existance of the object
    const T& get(int32_t index) const;

    /// @brief Add an element to the pool
    /// @tparam ...ARGS Type of the argument to build the object
    /// @param ...args The arguments to build the object
    /// @return The index of the object. Return -1 if an error has occure
    template<typename... ARGS>
    int32_t add(ARGS&&... args);

    /// @brief Remove an object from the pool
    /// @param index The index of the object
    /// @return True if the object has been removed, false otherwise
    bool remove(int32_t index);

    /// @brief Check the validity of an index
    /// @param index The index that will be checked
    /// @return True if it is valid, false otherwise
    bool validity(int32_t index) const;

private:
    std::array<std::optional<T>, MAX_ELEMENTS> m_data;  // Container of the objects
    std::stack<uint32_t> m_available_index;             // Available indices
};

template<typename T, uint32_t MAX_ELEMENTS>
ObjectPool<T, MAX_ELEMENTS>::ObjectPool()
{
    // Populate the available indices
    for (uint32_t i(MAX_ELEMENTS - 1) ; i != 0 ; --i) {
        m_available_index.push(i);
    }
    m_available_index.push(0);
}

template<typename T, uint32_t MAX_ELEMENTS>
T& ObjectPool<T, MAX_ELEMENTS>::get(int32_t index) {
    return m_data[index].value();
}

template<typename T, uint32_t MAX_ELEMENTS>
const T& ObjectPool<T, MAX_ELEMENTS>::get(int32_t index) const {
    return m_data[index].value();
}

template<typename T, uint32_t MAX_ELEMENTS>
template<typename... ARGS>
int32_t ObjectPool<T, MAX_ELEMENTS>::add(ARGS&&... args) {
    // Check if there still available indices
    if (m_available_index.empty()) {
        return -1;
    }

    // Create the object
    int32_t index = m_available_index.top();
    m_available_index.pop();
    m_data[index].emplace(std::forward<ARGS>(args)...);

    return index;
}

template<typename T, uint32_t MAX_ELEMENTS>
bool ObjectPool<T, MAX_ELEMENTS>::remove(int32_t index) {
    // Check if the index refer to an existing object
    if (index < 0 || (uint32_t)index >= MAX_ELEMENTS || !m_data[index].has_value()) {
        return false;
    }

    // Remove the object
    m_available_index.push(index);
    m_data[index].reset();  

    return true;
}

template<typename T, uint32_t MAX_ELEMENTS>
bool ObjectPool<T, MAX_ELEMENTS>::validity(int32_t index) const {
    return index >= 0 && (uint32_t)index < MAX_ELEMENTS && m_data[index].has_value();
}

}