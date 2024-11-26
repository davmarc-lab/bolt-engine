#pragma once

#include <vector>
#include "Math.hpp"
#include "Utils.hpp"

namespace bolt {
	template <typename T>
	struct Pair {
		T x, y;
	};

	enum LightType {
		LIGHT_DIRECTIONAL,
		LIGHT_POINT,
		LIGHT_SPOT,
	};

	struct LightConstraint {
		f32 constant = 1.f, linear = .09f, quadratic = .032f;
	};

	struct ShaderLightBlock {
		int type = LightType::LIGHT_DIRECTIONAL;
		float intensity = 1;
		vec3 color{1, 1, 1};

		vec3 position{};
		vec3 direction{};

		vec3 ambient{};
		vec3 diffuse{};
		vec3 specular{};

		float constant = 1;
		float linear = .09f;
		float quadratic = .032f;

		float cutoff = 12.5f;
		float outerCutoff = 17.5f;

		bool isSmooth = false;
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
