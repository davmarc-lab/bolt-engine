#include "EntityManager.hpp"

void EntityManager::addEntity(Entity *entity) {
    this->m_entities.insert(std::pair(this->m_currentId++, entity));
}

bool EntityManager::removeEntity(const unsigned int &id) {
    return this->m_entities.erase(id);
}

