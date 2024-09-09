#pragma once

#include "../Core/Utils.hpp"

#include <algorithm>
#include <memory>
#include <mutex>
#include <unordered_map>

#include "Component.hpp"
#include "Entity.hpp"

#include "../Core/Log.hpp"

namespace Bolt {
	class EntityManager {
	private:
		inline static std::shared_ptr<EntityManager> s_pointer = nullptr;
		inline static std::mutex s_mutex;

		u32 m_currentId = 0;

		std::map<u32, std::unique_ptr<Entity>> m_entities;
		std::map<u32, std::vector<std::shared_ptr<Component>>> m_ettComponents;

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

		template <typename T>
		std::shared_ptr<T> addComponent(const u32 &id) {
			if (!this->isEntityValid(id)) {
				BT_WARN_CORE("Entity does not exist: id = {0}.", id);
				return nullptr;
			}

			if (this->m_ettComponents.find(id) == this->m_ettComponents.end()) {
				this->m_ettComponents.emplace(id, std::vector<std::shared_ptr<Component>>{});
			}
            auto elem = std::make_shared<T>();
			this->m_ettComponents.at(id).push_back(elem);
            return elem;
		}

		b8 isEntityValid(const u32 &id) {
			return this->m_entities.find(id) != this->m_entities.end();
		}

		template <typename T>
		bool entityHasComponent(const u32 &id) {
			if (!this->isEntityValid(id)) {
				BT_WARN_CORE("Entity does not exist: id = {0}.", id);
				return false;
			}

			auto vec = this->m_ettComponents.at(id);
			return std::find_if(vec.begin(), vec.end(), [](const std::shared_ptr<Component> &c) {
				return std::dynamic_pointer_cast<T>(c) != nullptr;
			}) != vec.end();
		}

		template <typename T>
		std::vector<u32> getEntitiesFromComponent() {
			// use m_compEntities

			std::vector<u32> res = {};

			for (auto [key, val] : this->m_ettComponents) {
				if (this->entityHasComponent<T>(key))
					res.push_back(key);
			}

			return res;
		}

		template <typename T>
		std::shared_ptr<T> getEntityComponent(const u32 &id) {
			if (this->entityHasComponent<T>(id)) {
				for (auto c : this->m_ettComponents.at(id)) {
					if (auto t = std::dynamic_pointer_cast<T>(c); t != nullptr) {
                        return t;
					}
				}
			}
			return nullptr;
		}

		u32 createEntity();

		u32 getEntitiesCount() const { return this->m_entities.size(); }

		std::vector<Entity> getEntities() const {
			std::vector<Entity> res;
			for (const auto &entity : this->m_entities) {
				res.emplace_back(*entity.second);
			}

			return res;
		}

		b8 removeEntity(const u32 &id);
	};
} // namespace Bolt
