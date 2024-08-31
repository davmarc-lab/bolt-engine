#pragma once

#include <cstdint>
#include <vector>

#include <ECS/Component.hpp>

namespace Bolt {
	class Entity final {
	private:
		const uint32_t m_id;

		std::vector<Component> m_components;
	public:
		explicit Entity(const uint32_t& id) : m_id(id) {}

		~Entity() = default;

		inline const uint32_t& getId() const { return this->m_id; }

		void addComponent(const Component& component);

		template <class T>
		// check if Component is_base_of_v T
		bool removeSingleComponent();

		template <class T>
		const std::vector<T>& getComponentsOfType();
	};
}
