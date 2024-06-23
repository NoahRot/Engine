#include "Test/Test.hpp"

namespace eng::test{

TestManager::TestManager()
: m_current(nullptr)
{}

TestManager::~TestManager() {
    for (auto element : m_table_test) {
        delete element.second;
    }
}

TestManager& TestManager::instance() {
    static TestManager s_instance;
    return s_instance;
}

void TestManager::update() {
    if (m_current) {
        m_current->update();
    }
}

void TestManager::draw() {
    if (m_current) {
        m_current->draw();
    }
}

}