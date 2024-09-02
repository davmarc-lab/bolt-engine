#pragma once

#include <iostream>

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
		const b8& removeSingleComponent();

		// TODO : To implement this function, before you have to implement a way to filter Components without giving a class name (Notes.md)
		template <class T>
		// check if Component is_base_of_v T
		inline std::vector<T> getComponentsOfType() const {
			std::vector<T> result;
			for (auto c : this->m_components) {
				// same class
			}
			return result;
		}
	};
}
