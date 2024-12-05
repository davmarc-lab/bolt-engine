#pragma once

#include <mutex>
#include "../Core/Enums.hpp"

#include "../Graphic/Buffer/VertexArray.hpp"
#include "Component.hpp"

namespace bolt {

	BT_CONSTEXPR f32 LIGHT_CASTER_DIM = 0.3f;
	
	class PrimitiveManager {
	public:
        static u32 addCubePrimitive(const vec3& pos, const vec3& scale, const vec3& rot, const vec4& color);

		PrimitiveManager(PrimitiveManager &other) = delete;

		void operator=(const PrimitiveManager &other) = delete;

		/*
		 * Retrieves the instance of the PrimitiveManager if it's not created.
		 * This function is thread safe using a simple `std::mutex`.
		 *
		 * @return `PrimitiveManager` unique object.
		 */
		inline static void init() {
			std::lock_guard<std::mutex> lock(s_mutex);
			if (s_pointer == nullptr) {
				Shared<PrimitiveManager> copy(new PrimitiveManager());
				copy.swap(s_pointer);
			}
		}

	private:
		inline static Shared<PrimitiveManager> s_pointer = nullptr;
		inline static std::mutex s_mutex{};

		PrimitiveManager();

		inline static Mesh s_square{};
		inline static Mesh s_triangle{};
		inline static Mesh s_circle{};
		inline static Mesh s_cube{};
		inline static Mesh s_cone{};
		inline static Mesh s_sphere{};
	};

} // namespace bolt
