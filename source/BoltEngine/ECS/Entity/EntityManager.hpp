#pragma once

#include "Entity.hpp"

#include <iostream>
#include <map>
#include <memory>
#include <mutex>

class EntityManager {
private:
    inline static std::shared_ptr<EntityManager> pointer = nullptr;
    inline static std::mutex mutex;

    unsigned int m_currentId = 0;

    std::map<unsigned int, Entity *> m_entities;

    EntityManager() {
        std::cout << "This class need to be tested yet.\n";
    }

public:
    EntityManager(EntityManager &other) = delete;

    void operator=(const EntityManager &other) = delete;

    ~EntityManager() = default;

    inline static std::shared_ptr<EntityManager> instance() {
        std::lock_guard<std::mutex> lock(mutex);
        if (pointer == nullptr) {
            std::shared_ptr<EntityManager> copy(new EntityManager());
            copy.swap(pointer);
        }

        return pointer;
    }

    void addEntity(Entity *entity);

    bool removeEntity(const unsigned int &id);

    template <typename T, std::enable_if_t<std::is_base_of_v<Component, T>> * = nullptr>
    inline void filterEntitiesFromComponent() {
        std::cout << "Not implemented\n";
    }
};
