#include <ECS/Entity.hpp>

namespace Bolt {
	 void Entity::addComponent(const Component& component) {  }

	template <class T>
	bool Entity::removeSingleComponent() { return false; }

	template <class T>
	const std::vector<T>& Entity::getComponentsOfType() { return nullptr; }

}
