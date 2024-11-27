#pragma once

#include "../Core/Utils.hpp"

#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>

#include "Component.hpp"
#include "Entity.hpp"

#include "../Core/Enums.hpp"
#include "../Core/Event.hpp"
#include "../Core/Log.hpp"

namespace bolt {
	class EntityManager {
	private:
		inline static Shared<EntityManager> s_pointer = nullptr;
		inline static std::mutex s_mutex;

		b8 m_initEvents = false;
		u32 m_currentId = 0;
		u32 m_lightId = 0;

		std::map<u32, Unique<Entity>> m_entities;
        // it should be a vector
		std::map<LightType, Shared<EntityLight>> m_lights;
		std::map<u32, std::vector<Shared<Component>>> m_ettComponents;

		// std::unordered_map<Component, std::vector<u32>> m_compEntities;

		EntityManager() = default;

	public:
		EntityManager(EntityManager &other) = delete;

		void operator=(const EntityManager &other) = delete;

		inline static Shared<EntityManager> instance() {
			std::lock_guard<std::mutex> lock(s_mutex);
			if (s_pointer == nullptr) {
				Shared<EntityManager> copy(new EntityManager());
				copy.swap(s_pointer);
			}

			return s_pointer;
		}

		void subscribeEventCallbacks();

		template <typename T>
		inline Shared<T> addComponent(const u32 &id) {
			if (!this->isEntityValid(id)) {
				// BT_WARN_CORE("Entity does not exist: id = {0}.", id);
				return nullptr;
			}

			auto elem = CreateShared<T>();
			this->m_ettComponents.at(id).push_back(elem);
			return elem;
		}

		inline b8 isEntityValid(const u32 &id) const {
			return this->m_entities.contains(id);
		}

		template <typename T>
		bool entityHasComponent(const u32 &id) {
			if (!this->isEntityValid(id)) {
				// BT_WARN_CORE("Entity does not exist: id = {0}.", id);
				return false;
			}

			auto vec = this->m_ettComponents.at(id);
			return std::find_if(vec.begin(), vec.end(), [](const Shared<Component> &c) {
					   return std::dynamic_pointer_cast<T>(c) != nullptr;
				   }) != vec.end();
		}

		template <typename T>
		inline std::vector<u32> getEntitiesFromComponent() {
			// use m_compEntities

			std::vector<u32> res = {};

			for (auto [key, _] : this->m_ettComponents) {
				if (this->entityHasComponent<T>(key))
					res.push_back(key);
			}

			return res;
		}

		template <typename T>
		inline Shared<T> getEntityComponent(const u32 &id) {
			if (this->entityHasComponent<T>(id)) {
				for (auto it = this->m_ettComponents.at(id).begin(); it != this->m_ettComponents.at(id).end(); it++) {
					if (auto t = std::dynamic_pointer_cast<T>(*it); t != nullptr) {
						return t;
					}
				}
			}
			return nullptr;
		}

		u32 createEntity();

		inline u32 createLight(const LightHelper &helper) {
			if (this->m_lightId < ecs::MAX_LIGHTS) {
				this->m_lights.insert(std::make_pair(helper.type, CreateShared<EntityLight>(helper)));
				return this->m_lightId++;
			}
			return 0;
		}

		inline Shared<EntityLight> getLights(const u32 &id) const {
			std::vector<Shared<EntityLight>> res;
			for (auto v: std::views::values(this->m_lights)) {
                std::cout << v << "\n";
            }
            return nullptr;
		}

		inline u32 getEntitiesCount() const { return static_cast<u32>(this->m_entities.size()); }

		inline u32 getCurrentId() const { return this->m_currentId; }

		inline std::vector<Entity> getEntities() const {
			std::vector<Entity> res;
			res.reserve(this->m_entities.size());
			for (const auto &entity : this->m_entities) {
				res.emplace_back(*entity.second);
			}

			return res;
		}

		inline std::vector<u32> getEntitiesId() const {
			std::vector<u32> res;
			res.reserve(this->m_entities.size());
			for (const auto &entity : this->m_entities) {
				res.push_back(entity.first);
			}
			return res;
		}

		inline std::string getEntityName(const u32 &id) const { return this->m_entities.at(id)->getName(); }

		b8 removeEntity(const u32 &id);
	};
} // namespace bolt
