#pragma once

#include <vector>
#include <stack>

namespace ora {

template<typename T>
class VectorContinuous {
public:
    typedef T* iterator;
    typedef const T* const_iterator;

public:
    VectorContinuous(uint32_t reserve = 0);

    uint32_t add(T data);

    void remove(uint32_t id);

    bool is_valid(uint32_t id) const;

    uint32_t size() const;

    T& operator[](uint32_t id);

    iterator begin();

    iterator end();

    const_iterator begin() const;

    const_iterator end() const;

private:
    std::vector<T> m_data;
    std::vector<bool> m_used;
    std::stack<uint32_t> m_free_id;
};

template<typename T>
VectorContinuous<T>::VectorContinuous(uint32_t reserve) {
    m_data.reserve(reserve);
    m_used.reserve(reserve);
}

template<typename T>
uint32_t VectorContinuous<T>::add(T data) {
    uint32_t id;

    if (m_free_id.empty()) {
        id = m_data.size();
        m_data.push_back(data);
        m_used.push_back(true);
    }else{
        id = m_free_id.top();
        m_free_id.pop();
        m_data[id] = data;
        m_used[id] = true;
    }

    return id;
}

template<typename T>
void VectorContinuous<T>::remove(uint32_t id) {
    m_free_id.push(id);
    m_used[id] = false;
}

template<typename T>
bool VectorContinuous<T>::is_valid(uint32_t id) const {
    if (id >= m_data.size()) {
        return false;
    }else{
        return m_used[id];
    }
}

template<typename T>
uint32_t VectorContinuous<T>::size() const {
    return m_data.size();
}

template<typename T>
T& VectorContinuous<T>::operator[](uint32_t id) {
    return m_data[id];
}

template<typename T>
VectorContinuous<T>::iterator VectorContinuous<T>::begin() {
    return &m_data[0];
}

template<typename T>
VectorContinuous<T>::iterator VectorContinuous<T>::end() {
    return &m_data[0]+m_data.size();
}

template<typename T>
VectorContinuous<T>::const_iterator VectorContinuous<T>::begin() const {
    return &m_data[0];
}

template<typename T>
VectorContinuous<T>::const_iterator VectorContinuous<T>::end() const {
    return &m_data[0]+m_data.size();
}

}