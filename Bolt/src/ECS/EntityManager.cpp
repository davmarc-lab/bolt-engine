#include <ECS/EntityManager.hpp>

namespace Bolt {
	void EntityManager::addEntity(const Entity& ett) {
		// created new element
		if (const auto [fst, snd] = this->m_entities.insert(std::make_pair(this->m_currentId, ett)); snd) {
			// add all components that an entity could have
			auto [id, comps] = this->m_ettComponents.emplace(this->m_currentId, std::vector<Component>(ett.getComponents()));
			// const auto& elem = this->m_ettComponents.find(this->m_currentId);
			// for (const auto& e : elem->second) { std::cout << e.getType() << "\n"; }
			this->m_currentId++;
		}
	}

	bool EntityManager::removeEntity(const u32& id) {
		auto ec_res = static_cast<bool>(this->m_ettComponents.erase(id));
		auto e_res = static_cast<bool>(this->m_entities.erase(id));
		return ec_res && e_res;
	}
}
