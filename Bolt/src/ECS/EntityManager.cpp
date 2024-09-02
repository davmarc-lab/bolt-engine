#include <ECS/EntityManager.hpp>

namespace Bolt {
	void EntityManager::addEntity(std::shared_ptr<Entity> ett) {
		this->m_entities.insert(std::make_pair(this->m_currentId, ett));
		this->m_currentId++;
	}

	bool EntityManager::removeEntity(const u64& id) { return static_cast<bool>(this->m_entities.erase(id)); }

	template <typename T>
	const std::vector<T>& EntityManager::getComponentsFromType() {
		std::vector<T> result;
		for (const auto l: this->m_entities) {
			result.push_back(l.second->getComponentsOfType<T>());
		}
		return result;
	}

}
