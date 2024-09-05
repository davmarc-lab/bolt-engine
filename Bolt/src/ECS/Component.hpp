#pragma once

#include "../Core/Enums.hpp"

namespace Bolt {
	class Component {
	protected:
		ecs::Components m_type;

	public:
		Component(const ecs::Components& t = ecs::unknown) : m_type(t) {}

		virtual ~Component() = default;

		const ecs::Components& getType() const { return this->m_type; }
	};

	class Render : public Component {
	public:
		Render() : Component(ecs::render) {}

		~Render() override = default;
	};
}
