#pragma once

#include "../Core/Utils.hpp"

#include <memory>
#include <mutex>
#include <unordered_map>

#include "Component.hpp"
#include "Entity.hpp"

#include "../Core/Log.hpp"
#include "Render.hpp"
#include "Transform.hpp"

namespace Bolt {
	class EntityManager {
	private:
		inline static std::shared_ptr<EntityManager> s_pointer = nullptr;
		inline static std::mutex s_mutex;

		u32 m_currentId = 0;

		std::map<u32, std::unique_ptr<Entity>> m_entities;
		std::map<u32, std::vector<std::unique_ptr<Component>>> m_ettComponents;
        // std::unordered_map<Component, std::vector<u32>> m_compEntities;

		EntityManager() {}

	public:
		EntityManager(EntityManager &other) = delete;

		void operator=(const EntityManager &other) = delete;

		inline static std::shared_ptr<EntityManager> instance() {
			std::lock_guard<std::mutex> lock(s_mutex);
			if (s_pointer == nullptr) {
				std::shared_ptr<EntityManager> copy(new EntityManager());
				copy.swap(s_pointer);
			}

			return s_pointer;
		}

		u32 getEntitiesCount() const { return this->m_currentId; }

		std::vector<Entity> getEntities() const {
			std::vector<Entity> res;
			for (const auto &entity : this->m_entities) {
				res.emplace_back(*entity.second);
			}

			return res;
		}

		u32 createEntity();

		b8 addComponent(const u32 &id, const ecs::Components &type) {
			if (this->m_entities.find(id) == this->m_entities.end()) {
				BT_WARN_CORE("Entity does not exist: id = {0}.", id);
				return false;
			}
			switch (type) {
				case ecs::Components::transform: {
					if (this->m_ettComponents.find(id) == this->m_ettComponents.end()) {
						this->m_ettComponents.emplace(id, std::vector<std::unique_ptr<Component>>{});
					}
					this->m_ettComponents.at(id).push_back(std::unique_ptr<Transform>());
					return true;
				}
				case ecs::Components::render: {
					if (this->m_ettComponents.find(id) == this->m_ettComponents.end()) {
						this->m_ettComponents.emplace(id, std::vector<std::unique_ptr<Component>>{});
					}
					this->m_ettComponents.at(id).push_back(std::unique_ptr<Render>());
					return true;
				}
				default:
					return false;
			}
		}

		b8 addComponent(const u32 &id, const std::vector<ecs::Components> &types) {
			b8 success = true;
			for (const auto &type : types) {
				success &= this->addComponent(id, type);
			}
			return success;
		}

		b8 removeEntity(const u32 &id);
	};
} // namespace Bolt
