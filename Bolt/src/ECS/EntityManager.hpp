#pragma once

#include <Core/Utils.hpp>

#include <map>
#include <memory>
#include <mutex>

#include <ECS/Entity.hpp>

namespace Bolt {
	class EntityManager {
	private:
		inline static std::shared_ptr<EntityManager> s_pointer = nullptr;
		inline static std::mutex s_mutex;

		u64 m_currentId = 0;

		std::pmr::map<u64, std::shared_ptr<Entity>> m_entities;

		EntityManager() = default;

	public:
		EntityManager(EntityManager& other) = delete;

		void operator=(const EntityManager& other) = delete;

		inline static std::shared_ptr<EntityManager> instance() {
			std::lock_guard<std::mutex> lock(s_mutex);
			if (s_pointer == nullptr) {
				std::shared_ptr<EntityManager> copy(new EntityManager());
				copy.swap(s_pointer);
			}

			return s_pointer;
		}

		void addEntity (std::shared_ptr<Entity> ett);

		bool removeEntity (const u64& id);
	};
}
