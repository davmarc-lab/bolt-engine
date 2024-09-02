#include <vcruntime_typeinfo.h>
#include <ECS/Entity.hpp>

namespace Bolt {
	void Entity::addComponent(const Component& component) {
		this->m_components.push_back(component);
	}

	template <class T>
	const b8& Entity::removeSingleComponent() { return false; }
}
