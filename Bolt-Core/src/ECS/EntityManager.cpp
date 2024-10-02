#include "../../include/ECS/EntityManager.hpp"
#include "../../include/Platform/MeshFactory.hpp"

#include "../../include/Core/Enums.hpp"
#include "../../include/Core/Log.hpp"
#include "../../include/Core/SCene.hpp"
#include <iostream>

namespace bolt {
	void EntityManager::subscribeEventCallbacks() {
		this->m_initEvents = true;
		auto ed = EventDispatcher::instance();

		ed->subscribe(events::ecs::CreateMeshEvent, [this](auto &&p) {
			auto id = this->createEntity();
			factory::mesh::createEmptyCubeMesh(id);
			factory::mesh::initMesh(id);
			Scene::instance()->addEntity(id);
		});
	}

	u32 EntityManager::createEntity() {
		if (this->m_currentId >= ecs::MAX_ENTITIES) {
			// BT_WARN_CORE("Cannot create another entity (MAX_ENTITIES = {0}).", ecs::MAX_ENTITIES);
			return 0;
		}

		auto [it, res] = this->m_entities.insert(
			std::make_pair(this->m_currentId, CreateUnique<Entity>("Entity " + std::to_string(this->m_currentId))));

		this->m_ettComponents.emplace(this->m_currentId, std::vector<Shared<Component>>{});

		return this->m_currentId++;
	}

	b8 EntityManager::removeEntity(const u32 &id) {
		const auto ec_res = static_cast<bool>(this->m_ettComponents.erase(id));
		const auto e_res = static_cast<bool>(this->m_entities.erase(id));
		return ec_res && e_res;
	}
} // namespace Bolt
