﻿#include "../../include/ECS/EntityManager.hpp"
#include "../../include/Platform/MeshFactory.hpp"

#include "../../include/Core/Enums.hpp"
#include "../../include/Core/Log.hpp"
#include "../../include/Core/Scene.hpp"

#include "../../include/Application/Application.hpp"

namespace bolt {
	void EntityManager::subscribeEventCallbacks() {
		this->m_initEvents = true;
		auto ed = EventDispatcher::instance();

		ed->subscribe(events::ecs::CreateMeshEvent, [this](auto&& p) {
			auto id = this->createEntity();
			if (Application::getSceneType() == scene::SCENE_3D) {
				factory::mesh::createCustomMesh(id, config::cubeConfig, {});
				factory::mesh::initCustomMesh(id, config::cubeConfig, {});
				this->addComponent<PhysicComponent>(id);
			} else {
				factory::mesh::createEmptySquare(id);
				factory::mesh::initSquareMesh(id);
				auto comp = this->getEntityComponent<Transform>(id);
				this->addComponent<PhysicComponent>(id);
				comp->setPosition(vec3(400, 400, 0));
				comp->setScale(vec3(200, 200, 1));
			}
			Scene::instance()->addEntity(id);
			EventDispatcher::instance()->post(events::loop::LoopGeneric);
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

	b8 EntityManager::removeEntity(const u32& id) {
		const auto ec_res = static_cast<bool>(this->m_ettComponents.erase(id));
		const auto e_res = static_cast<bool>(this->m_entities.erase(id));
		return ec_res && e_res;
	}
} // namespace bolt
