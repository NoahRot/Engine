#pragma once

#include <inttypes.h>
#include <array>
#include <vector>
#include <stack>
#include <bitset>
#include <map>
#include <typeindex>
#include <typeinfo>
#include <string>
#include <unordered_map>

#include "Core/UniqueIndex.hpp"

namespace eng {

/// @brief Entity component system class
/// @tparam MAX_COMPONENT Maximum number of components
template<uint32_t MAX_COMPONENT>
class ECS {
public:

    /* ================
       Type definitions 
       ================ */

    /// @brief Index of the component
    typedef uint32_t ComponentID;

    /// @brief Index of the entity
    typedef uint64_t EntityID;

    /// @brief Bitmask that represent the components
    typedef std::bitset<MAX_COMPONENT> Bitmask;

    /// @brief Null mask representing no components (or unvalid Bitmask)
    static constexpr Bitmask NULL_MASK = Bitmask{};

public:

    /// @brief Arena (bump allocator) class to store the components
    struct Arena {
        Bitmask mask;       // Mask of the components in the allocator
        uint32_t chunk;     // Size of a chunk containing entity id and the components
        uint32_t capacity;  // Current maximum capacity of the arena
        uint32_t size;      // Current size of the arena (number of element inside)
        ECS<MAX_COMPONENT>* ecs; // A pointer to the ECS
        std::array<uint32_t, MAX_COMPONENT> offset; // The offset for each component
        void* data;         // Pointer to the allocated data

        /// @brief Constructor
        /// @param mask_ The mask of the arena
        /// @param ecs_ A pointer to the ECS
        /// @param capacity_ The initial capacity of the arena
        Arena(const Bitmask& mask_, ECS<MAX_COMPONENT>* ecs_, uint32_t capacity_ = 0);

        /// @brief Destructor, free the memory
        ~Arena();

        /// @brief Resize the arena, double capacity plus one
        void resize();

        /// @brief Resize the arena, add delta to the capacity
        /// @param delta The amount of memory to add/remove
        void resize(int32_t delta);

        /// @brief Add data
        /// @param ent The entity
        /// @param ptr An array of void pointers to each data
        /// @return The position of the data in the arena
        uint32_t add(EntityID ent, void* ptr[]);

        /// @brief Remove data
        /// @param position The position of the data to remove
        void remove(uint32_t position);

        /// @brief Swap two elements in the arena
        /// @param position1 Position of the first element
        /// @param position2 Position of the second element
        void swap(uint32_t position1, uint32_t position2);

        /// @brief Get the entity index for a given position
        /// @param position The position of the data
        /// @return The entity index
        EntityID get_index(uint32_t position);

        /// @brief Get the data for a given position
        /// @param position The position of the data
        /// @return A void pointer to the data
        void* get(uint32_t position);
        
        /// @brief Get the component for a given position
        /// @param position The position of the data
        /// @param com_id The index of the component
        /// @return A void pointer to the component
        void* get(uint32_t position, ComponentID com_id);

        /// @brief Get a void pointer to the first component in the arena
        /// @param com_id The component index
        /// @return A void pointer to the first component
        void* front(ComponentID com_id);
    };

public:

    /// @brief Contain the bitmask and the position of an entity
    struct EntitySpec {
        Bitmask mask;       // Bitmask of an entity (representing its components)
        uint32_t position;  // Position of the data in the Arena
    };

public:
    /// @brief Constructor of the ECS
    ECS();

    /// @brief Destructor of the ECS
    ~ECS();

    /* =========
       Component
       ========= */

    /// @brief Check if a component is valid
    /// @param type The type of the component
    /// @return True if the component is valid
    bool valid_component(std::type_index type);

    /// @brief Check if a component is valid
    /// @tparam T The component
    /// @return True if the component is valid
    template<typename T>
    bool valid_component();

    /// @brief Get the index of a component
    /// @param type The type of component
    /// @return The index of the component
    /// @warning Does not check if the component is valid
    ComponentID get_component_id(std::type_index type);

    /// @brief Get the index of a component
    /// @tparam T The component
    /// @return The index of the component
    /// @warning Does not check if the component is valid
    template<typename T>
    ComponentID get_component_id();

    /// @brief Get the size of a component
    /// @param index The index of the component
    /// @return The size of the component
    /// @warning Does not check if the component is valid
    uint32_t get_component_size(ComponentID index);

    /// @brief Compute the bitmask of a pack of component
    /// @tparam ...T A pack of component
    /// @return The bitmask
    template<typename... T>
    Bitmask get_bitmask();

    /// @brief Create a string of 0 and 1 representing the bitmask
    /// @param mask The bitmask to represent
    /// @return The string of 0 and 1
    std::string to_string(const Bitmask& mask);

    /// @brief Register a component
    /// @tparam T The component
    /// @return True if the process succeded
    template<typename T>
    bool register_component();

    /// @brief Unregister a component
    /// @tparam T The component
    /// @return True if the process succeded
    template<typename T>
    bool unregister_component();

    /* =====
       Arena
       ===== */

    /// @brief Check if an arena associated to a bitmask exist
    /// @param mask The bitmask
    /// @return True if the arena exist
    bool valid_arena(const Bitmask& mask);

    /// @brief Get an arena
    /// @param mask The bitmask associated to the arena
    /// @return A pointer to the arena
    /// @warning Does not check if the arena is valid
    Arena* get_arena(const Bitmask& mask);

    /// @brief Get a reference to the component of an entity
    /// @tparam T The component
    /// @param ent The entity
    /// @return A reference to the component
    /// @warning Does not check if the component exist or if the entity is valid
    template<typename T>
    T& get(EntityID ent);

    /// @brief Set if the empty arena should be erase
    /// @param erase Does the arena should be erase
    void erase_empty_arena(bool erase);

    /* ======
       Entity
       ====== */

    /// @brief Create an entity without any component
    /// @return The entity
    EntityID create_entity();

    /// @brief Destroy an entity
    /// @param ent The entity
    void destroy_entity(EntityID ent);

    /// @brief Give a component to an entity
    /// @tparam T The component
    /// @param ent The entity
    /// @param com The component data
    /// @warning Does not check if the entity already has the component nor if the component is valid
    template<typename T>
    void give_component(EntityID ent, const T& com);

    /// @brief Remove a component from an entity
    /// @tparam T The component
    /// @param ent The entity
    /// @warning Does not check if the entity really has the component nor if the component is valid
    template<typename T>
    void remove_component(EntityID ent);

    /// @brief Get the specification (bitmask and position) of an entity
    /// @param ent Th entity index
    /// @return An EntitySpec object containing the bitmask and the position
    EntitySpec get_entity_specification(EntityID ent);

    /* =====
       Utils 
       ===== */

    /// @brief Get a list of the entity indices that have the given component
    /// @tparam ...T The components
    /// @return A list of entity indices
    template<typename ...T>
    std::vector<EntityID> list_entity();

    /// @brief Get a list of the mask of the already created arena and the number of entites in each arena
    /// @return A list of mask that have already been created
    std::vector<std::pair<Bitmask,uint32_t>> list_mask();

    /// @brief Get the list of the components with their index
    /// @return A list of pair of component indices and the name of the component
    std::vector<std::pair<ComponentID, std::string>> list_component();

    /// @brief Get the number of free indices for the components
    /// @return The number of free component indices
    uint32_t nbr_free_component();

    /* ======
       System 
       ====== */

    /// @brief Run a function for all entities that have the required component 
    /// @tparam ...T The components used by the system
    /// @param system The system
    template<typename ...T>
    void for_each(void (*system)(T*...));

private:
    friend Arena;

    std::stack<ComponentID> m_component_avaiable;               // Avaiable component indices
    std::map<std::type_index, ComponentID> m_component_map;     // Map the type of component to their index
    std::array<uint32_t, MAX_COMPONENT> m_component_size;       // Table of the size of each component

    std::unordered_map<Bitmask, Arena*> m_arena;                // Map relating the bitmask to their Arena

    std::unordered_map<EntityID, EntitySpec> m_entity_spec;     // Map relating the entities to their specification

    bool m_erase_empty_arena;                                   // Should erase empty arena

    /// @brief Get the void pointer to the first element T of an arena
    /// @tparam T The component
    /// @param arena The arena
    /// @return A void pointer to the first element
    template<typename T>
    void* set_vector_element(Arena* arena);

    /// @brief Get the pointer on the current element and update the pointer to the next element
    /// @tparam T The component
    /// @param map The list of all pointers
    /// @param chunk The chunk size of the arena
    /// @param i The i th element on the pack of component
    /// @return A pointer to the i th component T of the current arena
    template<typename T>
    T* get_vector_element(std::vector<void*>& map, uint32_t chunk, uint32_t& i);

    /// @brief Check if the arena should be erase
    /// @param mask The mask of the arena
    void check_erase_arena(Bitmask mask);
};




/* =========================
   Arena methods definitions
   ========================= */

template<uint32_t MAX_COMPONENT>
ECS<MAX_COMPONENT>::Arena::Arena(const Bitmask& mask_, ECS<MAX_COMPONENT>* ecs_, uint32_t capacity_)
: mask(mask_), chunk(sizeof(EntityID)), capacity(capacity_), size(0), ecs(ecs_), data(nullptr)
{
    // Set component sizes
    for (ComponentID i(0) ; i < MAX_COMPONENT ; ++i) {
        offset[i] = chunk;
        if (mask[i]) {
            chunk += ecs->get_component_size(i);
        }
    }

    // Allocate memory
    data = malloc(chunk*capacity);
    if (data == NULL) {
        std::cout << "ERROR::ECS : MALLOC failed" << std::endl;
    }
}

template<uint32_t MAX_COMPONENT>
ECS<MAX_COMPONENT>::Arena::~Arena() {
    // Free the data
    free(data);
}

template<uint32_t MAX_COMPONENT>
void ECS<MAX_COMPONENT>::Arena::resize() {
    // Resize the arena. Increase the capacity by double plus one
    capacity = 2*capacity+1;
    data = realloc(data, capacity*chunk);
}

template<uint32_t MAX_COMPONENT>
void ECS<MAX_COMPONENT>::Arena::resize(int32_t delta) {
    // If remove more than the capacity the capacity is set to 0
    -delta > capacity ? capacity = 0 : capacity += delta;

    // Reallocate memory
    data = realloc(data, capacity*chunk);
    if (data == NULL) {
        std::cout << "ERROR::ECS : REALLOC failed" << std::endl;
    }
}

template<uint32_t MAX_COMPONENT>
uint32_t ECS<MAX_COMPONENT>::Arena::add(EntityID ent, void* ptr[]) {
    // Check if the arena is full
    if (capacity == size) {
        resize();
    }

    // Copy the entity index
    char* ent_begin((char*)(&ent));
    char* begin = static_cast<char*>(data) + size*chunk;
    std::copy(ent_begin, ent_begin + sizeof(EntityID), begin);

    // Copy the data
    uint32_t current(0);
    uint32_t delta_data(sizeof(EntityID));
    for (ComponentID i(0) ; i < MAX_COMPONENT ; ++i) {
        if (mask[i]) {
            char* ptr_begin(static_cast<char*>(ptr[current]));
            uint32_t current_size = ecs->get_component_size(i);
            std::copy(ptr_begin, ptr_begin + current_size, begin + delta_data);

            current++;
            delta_data += current_size;
        }
    }

    // Increment size
    ++size;

    // Return the data position
    return size - 1;
}

template<uint32_t MAX_COMPONENT>
void ECS<MAX_COMPONENT>::Arena::remove(uint32_t position) {
    // Change size 
    --size;

    // Swap the element to put it outside of the arena
    swap(position, size);
}

template<uint32_t MAX_COMPONENT>
void ECS<MAX_COMPONENT>::Arena::swap(uint32_t position1, uint32_t position2) {
    // Set begining of the data
    char* begin = static_cast<char*>(data);

    // Swap the position in the specification of the entities
    uint32_t& spec1 = ecs->m_entity_spec[get_index(position1)].position;
    uint32_t& spec2 = ecs->m_entity_spec[get_index(position2)].position;
    std::swap(spec1, spec2);

    // Swap the data
    std::vector<char> tmp(chunk); // temporary copy
    std::copy(begin + position1*chunk, begin + (position1+1)*chunk, tmp.begin());
    std::copy(begin + position2*chunk, begin + (position2+1)*chunk, begin + position1*chunk);
    std::copy(tmp.begin(), tmp.end(), begin + position2*chunk);
}

template<uint32_t MAX_COMPONENT>
typename ECS<MAX_COMPONENT>::EntityID ECS<MAX_COMPONENT>::Arena::get_index(uint32_t position) {
    // Get the index of the data
    return *static_cast<EntityID*>(data + position*chunk);
}

template<uint32_t MAX_COMPONENT>
void* ECS<MAX_COMPONENT>::Arena::get(uint32_t position) {
    // Get the void pointer associate position
    return data + position*chunk;
}

template<uint32_t MAX_COMPONENT>
void* ECS<MAX_COMPONENT>::Arena::get(uint32_t position, ComponentID com_id) {
    // Get the void pointer associate position and the component
    return data + position*chunk + offset[com_id];
}

template<uint32_t MAX_COMPONENT>
void* ECS<MAX_COMPONENT>::Arena::front(ComponentID com_id) {
    // Get the first component of the list
    return data + offset[com_id];
}





/* =======================
   ECS methods definitions
   ======================= */

template<uint32_t MAX_COMPONENT>
ECS<MAX_COMPONENT>::ECS()
: m_erase_empty_arena(false)
{
    // Prepare avaiable component
    for (ComponentID i(MAX_COMPONENT-1) ; i != 0 ; --i) {
        m_component_avaiable.push(i);
    }
    m_component_avaiable.push(0);

    // Initialize sizes to 0
    m_component_size.fill(0);

    // Create the arena of null bitmask
    m_arena[NULL_MASK] = new Arena(NULL_MASK, this, 1);
}

template<uint32_t MAX_COMPONENT>
ECS<MAX_COMPONENT>::~ECS() {
    // Free all the arena
    for (auto i : m_arena) {
        if (i.second) {
            delete i.second;
        }
    }
}

template<uint32_t MAX_COMPONENT>
bool ECS<MAX_COMPONENT>::valid_component(std::type_index type) {
    // Check if the component already is in the map
    return m_component_map.find(type) != m_component_map.end();
}

template<uint32_t MAX_COMPONENT>
template<typename T>
bool ECS<MAX_COMPONENT>::valid_component() {
    // Check if the component already is in the map
    return m_component_map.find(std::type_index(typeid(T))) != m_component_map.end();
}

template<uint32_t MAX_COMPONENT>
typename ECS<MAX_COMPONENT>::ComponentID ECS<MAX_COMPONENT>::get_component_id(std::type_index type) {
    return m_component_map[type];
}

template<uint32_t MAX_COMPONENT>
template<typename T>
typename ECS<MAX_COMPONENT>::ComponentID ECS<MAX_COMPONENT>::get_component_id() {
    return m_component_map[std::type_index(typeid(T))];
}

template<uint32_t MAX_COMPONENT>
uint32_t ECS<MAX_COMPONENT>::get_component_size(ComponentID index) {
    return m_component_size[index];
}

template<uint32_t MAX_COMPONENT>
template<typename... T>
typename ECS<MAX_COMPONENT>::Bitmask ECS<MAX_COMPONENT>::get_bitmask() {
    // Check if the component are valid
    std::vector<bool> validity({valid_component<T>()...});
    for (bool i : validity) {
        if (!i) {
            return NULL_MASK;
        }
    }

    // Get the id of each component
    std::vector<ComponentID> index({get_component_id(typeid(T))...});

    // Create the mask and check if a component appear twice
    Bitmask mask;
    for (ComponentID i : index) {
        if (mask[i]) {
            return NULL_MASK;
        }else{
            mask[i] = 1;
        }
    }

    // Return the mask
    return mask;
}

template<uint32_t MAX_COMPONENT>
std::string ECS<MAX_COMPONENT>::to_string(const Bitmask& mask) {
    // Compute the string of 0 and 1 associate to the bitmask
    std::string str("");
    for (uint32_t i(0) ; i < mask.size() ; ++i) {
        mask[i] ? str += "1" : str += "0";
    }
    return str;
}

template<uint32_t MAX_COMPONENT>
template<typename T>
bool ECS<MAX_COMPONENT>::register_component() {
    // Ckeck if there still avaiable id
    if (m_component_avaiable.empty()) {
        return false;
    }

    // Check if the component already exist
    std::type_index type(typeid(T));
    if (valid_component(type)) {
        return false;
    }

    // Register the component
    ComponentID index(m_component_avaiable.top());
    m_component_avaiable.pop();
    m_component_map[type] = index;
    m_component_size[index] = sizeof(T);

    return true;
}

template<uint32_t MAX_COMPONENT>
template<typename T>
bool ECS<MAX_COMPONENT>::unregister_component() {
    // Check if the component exist
    std::type_index type(typeid(T));
    if (!valid_component(type)) {
        return false;
    }

    // Destroy all entity and arena related to the component
    ComponentID index(get_component_id(type));
    typename std::unordered_map<Bitmask, Arena*>::iterator next;
    for (typename std::unordered_map<Bitmask, Arena*>::iterator it(m_arena.begin()) ; it != m_arena.end() ; it = next) {
        if (it->second->mask[index]) {
            delete it->second;
            next = m_arena.erase(it);
        }else{
            ++it;
            next = it;
        }
    }

    // Unregister the component
    m_component_avaiable.push(index);
    m_component_map.erase(type);
    m_component_size[index] = 0;

    return true;
}

template<uint32_t MAX_COMPONENT>
bool ECS<MAX_COMPONENT>::valid_arena(const Bitmask& mask) {
    return m_arena.find(mask) != m_arena.end();
}

template<uint32_t MAX_COMPONENT>
typename ECS<MAX_COMPONENT>::Arena* ECS<MAX_COMPONENT>::get_arena(const Bitmask& mask) {
    return m_arena[mask];
}

template<uint32_t MAX_COMPONENT>
template<typename T>
T& ECS<MAX_COMPONENT>::get(EntityID ent) {
    EntitySpec spec = m_entity_spec[ent];
    return *static_cast<T*>(m_arena[spec.mask]->get(spec.position, get_component_id<T>()));
}

template<uint32_t MAX_COMPONENT>
void ECS<MAX_COMPONENT>::erase_empty_arena(bool erase) {
    // Change erase setting
    m_erase_empty_arena = erase;
    if (erase) {
        // If erase true, check for each arena if empty
        typename std::unordered_map<Bitmask, Arena*>::iterator next;
        for (typename std::unordered_map<Bitmask, Arena*>::iterator it(m_arena.begin()) ; it != m_arena.end() ; it = next) {
            if (it->second->size == 0 && it->second->mask != NULL_MASK) {
                next = m_arena.erase(it);
            }else {
                ++it;
                next = it;
            }
        }
    }
}

template<uint32_t MAX_COMPONENT>
typename ECS<MAX_COMPONENT>::EntityID ECS<MAX_COMPONENT>::create_entity() {
    // Create index, mask and position
    EntityID index = get_unique();
    Bitmask mask = NULL_MASK;
    uint32_t position = 0;

    // Add the entity to the null arena
    m_arena[NULL_MASK]->add(index, {});

    // Set entity specification
    m_entity_spec[index] = EntitySpec{mask, position};

    return index;
}

template<uint32_t MAX_COMPONENT>
void ECS<MAX_COMPONENT>::destroy_entity(EntityID ent) {
    // Get the entity specification
    EntitySpec spec = m_entity_spec[ent];

    // Remove the entity from the arena
    m_arena[spec.mask]->remove(spec.position);

    // Check if the arena should be erase
    check_erase_arena(spec.mask);
}

template<uint32_t MAX_COMPONENT>
template<typename T>
void ECS<MAX_COMPONENT>::give_component(EntityID ent, const T& com) {
    // Get entity spec
    EntitySpec& spec = m_entity_spec[ent];

    // Get the component index
    ComponentID com_id = m_component_map[std::type_index(typeid(T))];

    // Compute new mask and get the old storage
    Bitmask new_mask = spec.mask;
    new_mask[com_id] = 1;
    Arena* old_arena = m_arena[spec.mask];

    // Check if the new storage already exist, otherwise create it
    Arena* new_arena(nullptr);
    if (!valid_arena(new_mask)) {
        m_arena[new_mask] = new Arena(new_mask, this, 1);
    }
    new_arena = m_arena[new_mask];

    // Transfert data
    std::vector<void*> data_ptr;
    for (ComponentID i(0) ; i < MAX_COMPONENT ; ++i) {
        if (i == com_id) {
            data_ptr.push_back((char*)(&com));
        }else if (spec.mask[i]) {
            data_ptr.push_back(old_arena->get(spec.position, i));
        }
    }
    uint32_t new_position = new_arena->add(ent, &(data_ptr[0]));

    // Remove the entity from the old storage
    old_arena->remove(spec.position);

    // Check erase empty arena
    check_erase_arena(spec.mask);

    // Change the entity spec
    spec.position = new_position;
    spec.mask = new_mask;
}

template<uint32_t MAX_COMPONENT>
template<typename T>
void ECS<MAX_COMPONENT>::remove_component(EntityID ent) {
    // Get entity spec
    EntitySpec& spec = m_entity_spec[ent];

    // Get the component index
    ComponentID com_id = m_component_map[std::type_index(typeid(T))];

    // Compute new mask and get the old storage
    Bitmask new_mask = spec.mask;
    new_mask[com_id] = 0;
    Arena* old_arena = m_arena[spec.mask];

    // Check if the new storage already exist, otherwise create it
    Arena* new_arena(nullptr);
    if (!valid_arena(new_mask)) {
        m_arena[new_mask] = new Arena(new_mask, this, 1);
    }
    new_arena = m_arena[new_mask];

    // Transfert data
    std::vector<void*> data_ptr;
    for (ComponentID i(0) ; i < MAX_COMPONENT ; ++i) {
        if (new_mask[i]) {
            data_ptr.push_back(old_arena->get(spec.position, i));
        }
    }
    uint32_t new_position = new_arena->add(ent, &(data_ptr[0]));

    // Remove the entity from the old storage
    old_arena->remove(spec.position);

    // Check erase empty arena
    check_erase_arena(spec.mask);

    // Change the entity spec
    spec.position = new_position;
    spec.mask = new_mask;
}

template<uint32_t MAX_COMPONENT>
typename ECS<MAX_COMPONENT>::EntitySpec ECS<MAX_COMPONENT>::get_entity_specification(EntityID ent) {
    return m_entity_spec[ent];
}

template<uint32_t MAX_COMPONENT>
template<typename ...T>
std::vector<typename ECS<MAX_COMPONENT>::EntityID> ECS<MAX_COMPONENT>::list_entity() {
    // Create the list and compute the bitmask
    std::vector<EntityID> list;
    Bitmask mask = get_bitmask<T...>();

    // Check if the arena exist
    if (valid_arena(mask)) {
        Arena* arena = m_arena[mask];

        // Add all entity from the arena in the list
        for (uint32_t i(0) ; i < arena->size ; ++i) {
            list.push_back(arena->get_index(i));
        }
    }
    
    // Return the list
    return list;
}

template<uint32_t MAX_COMPONENT>
std::vector<std::pair<typename ECS<MAX_COMPONENT>::Bitmask, uint32_t>> ECS<MAX_COMPONENT>::list_mask() {
    // Create the list of bitmask and number of element
    std::vector<std::pair<Bitmask, uint32_t>> list;

    // Add the mask of each arena to the list and the number of element in each arena
    for (auto a : m_arena) {
        list.push_back({a.second->mask, a.second->size});
    }

    // Return the list
    return list;
}

template<uint32_t MAX_COMPONENT>
std::vector<std::pair<typename ECS<MAX_COMPONENT>::ComponentID, std::string>> ECS<MAX_COMPONENT>::list_component() {
    // Create a list of index and the name of the each component
    std::vector<std::pair<ComponentID, std::string>> list;

    // Add each component to the list
    for (auto c : m_component_map) {
        list.push_back({c.second, c.first.name()});
    }

    // Return the list
    return list;
}

template<uint32_t MAX_COMPONENT>
uint32_t ECS<MAX_COMPONENT>::nbr_free_component() {
    return m_component_avaiable.size();
}

template<uint32_t MAX_COMPONENT>
template<typename ...T>
void ECS<MAX_COMPONENT>::for_each(void (*system)(T*...)) {
    // Get the requiered mask and the size of the element
    Bitmask mask = get_bitmask<T...>();
    uint32_t init_para = sizeof...(T)-1;

    // For each arena check if it match the requierment
    for (auto a : m_arena) {
        Arena* arena = a.second;
        if ((arena->mask & mask) == mask) {
            
            // Apply system on all entity that match the requierment
            std::vector<void*> ptr({set_vector_element<T>(arena)...});
            for (uint32_t i(0) ; i < arena->size ; ++i) {
                uint32_t j(init_para);
                system(get_vector_element<T>(ptr, arena->chunk, j)...);
            }

        }
    }
}

template<uint32_t MAX_COMPONENT>
template<typename T>
void* ECS<MAX_COMPONENT>::set_vector_element(Arena* arena) {
    return arena->front(get_component_id<T>());
}

template<uint32_t MAX_COMPONENT>
template<typename T>
T* ECS<MAX_COMPONENT>::get_vector_element(std::vector<void*>& map, uint32_t chunk, uint32_t& i) {
    // Get the current element
    T* current = static_cast<T*>(map[i]);

    // Update the pointer
    map[i] += chunk;

    // Update the index
    --i;

    // Return the current element
    return current;
}

template<uint32_t MAX_COMPONENT>
void ECS<MAX_COMPONENT>::check_erase_arena(Bitmask mask) {
    // Check if an arena should be erase
    if (m_erase_empty_arena && mask != NULL_MASK && m_arena[mask]->size == 0) {
        delete m_arena[mask];
        m_arena.erase(mask);
    }
}

}