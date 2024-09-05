#pragma once

#include "../Core/Utils.hpp"
#include "Component.hpp"

#include <iostream>
#include <vector>


namespace Bolt {
	class Entity {
	private:
		std::string m_name;
		std::vector<Component> m_components;

	public:
		explicit Entity(std::string name = "Entity") : m_name(std::move(name)) {
		}

		~Entity() = default;

		inline void addComponent(const Component& comp) { this->m_components.push_back(comp); }

		inline std::vector<Component> getComponents() const { return this->m_components; }

		template <class T>
		// check if Component is_base_of_v T
		const b8& removeSingleComponent();

		std::string getName() const { return this->m_name; }
		
		void setName(const std::string& name) { this->m_name = name; }

		// // TODO : To implement this function, before you have to implement a way to filter Components without giving a class name (Notes.md)
		// template <class T>
		// // check if Component is_base_of_v T
		// inline std::vector<T> getComponentsOfType() const {
		// 	std::vector<T> result;
		// 	for (auto c : this->m_components) {
		// 		// same class
		// 		// std::cout << dynamic_cast<T*>(c.get()) << "\n";
		// 	}
		// 	return result;
		// }
	};
}
