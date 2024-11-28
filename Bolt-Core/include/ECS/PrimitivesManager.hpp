#pragma once

#include <mutex>
#include "../Core/Enums.hpp"

#include "../Graphic/Buffer/VertexArray.hpp"
#include "Component.hpp"

namespace bolt {
	class PrimitiveManager {
	public:
        u32 addCubePrimitive(const vec3& pos, const vec3& scale, const vec3& rot);

		PrimitiveManager(PrimitiveManager &other) = delete;

		void operator=(const PrimitiveManager &other) = delete;

		/*
		 * Retrieves the instance of the PrimitiveManager if it's not created.
		 * This function is thread safe using a simple `std::mutex`.
		 *
		 * @return `PrimitiveManager` unique object.
		 */
		inline static Shared<PrimitiveManager> instance() {
			std::lock_guard<std::mutex> lock(s_mutex);
			if (s_pointer == nullptr) {
				Shared<PrimitiveManager> copy(new PrimitiveManager());
				copy.swap(s_pointer);
			}

			return s_pointer;
		}

	private:
		inline static Shared<PrimitiveManager> s_pointer = nullptr;
		inline static std::mutex s_mutex{};

		PrimitiveManager();

		Mesh m_square;
		Mesh m_triangle;
		Mesh m_circle;
		Mesh m_cube;
		Mesh m_cone;
		Mesh m_sphere;
	};

} // namespace bolt
