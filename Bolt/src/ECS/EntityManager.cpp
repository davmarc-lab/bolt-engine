#include "EntityManager.hpp"

#include "../Core/Log.hpp"
#include "../Core/Enums.hpp"

namespace Bolt {
    u32 EntityManager::createEntity() {
        if (this->m_currentId >= ecs::MAX_ENTITIES) {
            BT_WARN_CORE("Cannot create another entity (MAX_ENTITIES = {0}).", ecs::MAX_ENTITIES);
            return 0;
        }

        auto [it, res] = this->m_entities.insert(
            std::make_pair(this->m_currentId, std::make_unique<Entity>("Entity " + std::to_string(this->m_currentId))));
        return this->m_currentId++;
    }
    
    b8 EntityManager::removeEntity(const u32& id) {
        const auto ec_res = static_cast<bool>(this->m_ettComponents.erase(id));
        const auto e_res = static_cast<bool>(this->m_entities.erase(id));
        return ec_res && e_res;
    }
}
