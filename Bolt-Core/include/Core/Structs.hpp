#pragma once

#include <vector>
#include "Math.hpp"
#include "Utils.hpp"

namespace bolt {
	template <typename T>
	struct Pair {
		T x, y;
	};

	enum RenderType {
		render_arrays,
		render_elements,
		render_instance // TODO
	};

	struct RenderHelper {
		RenderType type = render_arrays;
		u32 mode = 0;
		u32 first = 0;
	};

	struct MeshHelper {
		std::vector<vec3> vertex{};
		std::vector<u32> index{};
		std::vector<vec4> colors{};
		std::vector<vec2> texCoords{};
		std::vector<vec3> normals{};
		vec3 position{};
		vec3 scale{1, 1, 1};
		vec3 rotation{};
		RenderHelper renderInfo{};
	};
} // namespace bolt
