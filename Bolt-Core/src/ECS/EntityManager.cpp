﻿#include "../../include/ECS/EntityManager.hpp"
#include "../../include/ECS/System.hpp"
#include "../../include/Platform/MeshFactory.hpp"

#include "../../include/Platform/MeshVertices.hpp"

#include "../../include/Core/InputManager.hpp"

#include "../../include/Core/Enums.hpp"
#include "../../include/Core/Log.hpp"
#include "../../include/Core/Scene.hpp"

#include "../../include/Application/Application.hpp"

namespace bolt {
	void EntityManager::subscribeEventCallbacks() {
		this->m_initEvents = true;
		auto ed = EventDispatcher::instance();

		ed->subscribe(events::ecs::CreateMeshEvent, [this](auto &&p) {
			auto id = this->createEntity();
			if (Application::getSceneType() == scene::SCENE_3D) {
				MeshHelper helper{};
				helper.vertex = factory::mesh::cubeGeometry;
				helper.position = {0, 0, 0};
				helper.scale = {1, 1, 1};
				helper.renderInfo = {RenderType::render_arrays, GL_TRIANGLES, 0};
				factory::mesh::instanceMesh(id, helper);
				// this->addComponent<PhysicComponent>(id);
			} else {
				MeshHelper helper{};
				helper.vertex = factory::mesh::squareGeometry;
				helper.renderInfo = {RenderType::render_arrays, GL_TRIANGLES, 0};
				factory::mesh::instanceMesh(id, helper);
				auto comp = this->getEntityComponent<Transform>(id);
				this->addComponent<PhysicComponent>(id);
				comp->setPosition(vec3(200, 200, 0));
				comp->setScale(vec3(40, 40, 1));
			}
			Scene::instance()->addEntity(id);
			EventDispatcher::instance()->post(events::loop::LoopGeneric);
		});

		ed->subscribe(events::loop::LoopUpdate, [](auto &&ph1) { systems::transform::updateAllModelMatrix(); });

		const auto im = InputManager::instance();
		ed->subscribe(events::loop::LoopInput, [im](auto &&ph1) {
			auto entities = EntityManager::instance()->getEntitiesFromComponent<InputComponent>();
			for (auto entity : entities) {
				auto comp = EntityManager::instance()->getEntityComponent<InputComponent>(entity);
				for (auto c : comp->getAllKeys()) {
					if (im->isKeyPressed(c))
						comp->call(c);
				}
			}
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

	void EntityManager::setEntityName(const u32& id, const std::string& name) const {
		this->m_entities.at(id)->setName(name);
	}

	u32 EntityManager::createLight(const LightHelper &helper) {
		if (this->m_lightId < ecs::MAX_LIGHTS) {
			this->m_lights.insert(std::make_pair(this->m_lightId, CreateShared<EntityLight>(helper)));
            if (helper.type != LightType::LIGHT_DIRECTIONAL) {
                RenderApi::instance()->getRenderer()->drawCube(helper.position, {0.3, 0.3, 0.3}, {}, vec4(helper.color, 1), false);
            }
			return this->m_lightId++;
		}
		return 0;
	}

	std::map<u32, Shared<EntityLight>> EntityManager::getLights() const {
		return this->m_lights;
	}

	b8 EntityManager::removeEntity(const u32 &id) {
		const auto ec_res = static_cast<bool>(this->m_ettComponents.erase(id));
		const auto e_res = static_cast<bool>(this->m_entities.erase(id));
		return ec_res && e_res;
	}
} // namespace bolt
