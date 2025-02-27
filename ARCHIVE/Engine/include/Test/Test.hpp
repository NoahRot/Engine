#pragma once

#include <string>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

namespace eng::test {

class Test {
public:
    virtual ~Test(){}

    virtual void update() = 0;

    virtual void draw() = 0;
    
};

class TestManager {
public:
    TestManager(const TestManager&) = delete;

    TestManager& operator=(const TestManager&) = delete;

    ~TestManager();

    static TestManager& instance();

    void update();

    void draw();

    template<typename T>
    bool create_test() {
        std::type_index type(typeid(T));
        if (m_table_test.find(type) != m_table_test.end()) {
            return false;
        }

        T* test = new T;
        m_table_test[type] = test;

        return true;
    }

    template<typename T>
    void switch_test() {
        m_current = m_table_test[std::type_index(typeid(T))];
    }

    template<typename T>
    T* get_test() {
        return (T*)m_table_test[std::type_index(typeid(T))];
    }

private:
    TestManager();

    std::unordered_map<std::type_index, Test*> m_table_test;

    Test* m_current;


};

}