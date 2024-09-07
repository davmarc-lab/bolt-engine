#pragma once

#include "../Core/Enums.hpp"

namespace Bolt {
	class Component {
	protected:
		ecs::Components m_type;

	public:
		Component(const ecs::Components& t) : m_type(t) {}

        Component() : Component(ecs::unknown) {}

		virtual ~Component() = default;

		const ecs::Components& getType() const { return this->m_type; }
	};
}
