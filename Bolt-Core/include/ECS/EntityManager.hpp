﻿#pragma once

#include "../Core/Utils.hpp"

#include <algorithm>
#include <map>
#include <memory>
#include <mutex>

#include "Component.hpp"
#include "Entity.hpp"

#include "../Core/Event.hpp"
#include "../Core/Log.hpp"

namespace bolt {
	class EntityManager {
	private:
		inline static Shared<EntityManager> s_pointer = nullptr;
		inline static std::mutex s_mutex;

		b8 m_initEvents = false;
		u32 m_currentId = 0;

		std::map<u32, Unique<Entity>> m_entities;
		std::map<u32, std::vector<Shared<Component>>> m_ettComponents;

		// std::unordered_map<Component, std::vector<u32>> m_compEntities;

		EntityManager() {}

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
		Shared<T> addComponent(const u32 &id) {
			if (!this->isEntityValid(id)) {
				// BT_WARN_CORE("Entity does not exist: id = {0}.", id);
				return nullptr;
			}

			auto elem = CreateShared<T>();
			this->m_ettComponents.at(id).push_back(elem);
			return elem;
		}

		b8 isEntityValid(const u32 &id) {
			return this->m_entities.find(id) != this->m_entities.end();
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
		Shared<T> getEntityComponent(const u32 &id) {
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

		u32 getEntitiesCount() const { return static_cast<u32>(this->m_entities.size()); }

		std::vector<Entity> getEntities() const {
			std::vector<Entity> res;
			for (const auto &entity : this->m_entities) {
				res.emplace_back(*entity.second);
			}

			return res;
		}

		b8 removeEntity(const u32 &id);
	};
} // namespace bolt