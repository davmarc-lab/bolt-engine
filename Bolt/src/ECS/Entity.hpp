#pragma once

#include <Core/Utils.hpp>

#include <vector>

#include <ECS/Component.hpp>


namespace Bolt {
	class Entity {
	private:
		std::vector<Component> m_components;
	public:
		explicit Entity() {}

		~Entity() = default;

		void addComponent(const Component& component);

		template <class T>
		// check if Component is_base_of_v T
		b8 removeSingleComponent();

		template <class T>
		// check if Component is_base_of_v T
		const std::vector<T>& getComponentsOfType();
	};
}
