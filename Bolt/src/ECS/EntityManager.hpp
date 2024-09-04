#pragma once

#include <Core/Utils.hpp>

#include <memory>
#include <mutex>
#include <unordered_map>

#include <ECS/Entity.hpp>

namespace Bolt {
	class EntityManager {
	private:
		inline static std::shared_ptr<EntityManager> s_pointer = nullptr;
		inline static std::mutex s_mutex;

		u32 m_currentId = 0;

		std::unordered_map<u32, Entity> m_entities;
		std::unordered_map<u32, std::vector<Component>> m_ettComponents;

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

		void addEntity (const Entity& ett);

		bool removeEntity (const u32& id);
	};
}
