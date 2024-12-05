#pragma once

#include <vector>
#include "Math.hpp"
#include "Utils.hpp"

namespace bolt {
	template <typename T>
	struct Pair {
		T x, y;
	};

	struct Axis {
		vec3 x{1, 0, 0}, y{0, 1, 0}, z{0, 0, 1};
	};

	enum LightType {
		LIGHT_DIRECTIONAL,
		LIGHT_POINT,
		LIGHT_SPOT,
	};

	struct LightVectors {
		vec3 ambient{.1f, .1f, .1f};
		vec3 diffuse{.8f, .8f, .8f};
		vec3 specular{1, 1, 1};
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

		vec3 ambient{.1f, .1f, .1f};
		vec3 diffuse{.8f, .8f, .8f};
		vec3 specular{1, 1, 1};

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

	struct LightHelper {
		std::string name = "Light";
		LightType type;
		LightVectors vectors{};
		vec3 color{1, 1, 1};
		f32 intensity = 1;
		b8 caster = false;
		vec3 position{};
		vec3 direction{};
		LightConstraint info{};
		f32 cutoff = 12.5f, outerCutoff = 17.5f;
	};

	namespace camera {
		inline const f32 YAW = -90.f;
		inline const f32 PITCH = 0.f;
		inline const f32 SPEED = 0.2f;
		inline const f32 SENSITIVITY = 0.02f;
		inline const f32 ZOOM = 45.f;
		inline const vec3 POSITION = vec3(0, 0, 3);
		// f32 tbSpeed = 20.f;

		struct CameraVectors {
			vec3 cameraPos = POSITION;
			vec3 cameraFront = vec3(0, 0, -1);
			vec3 cameraUp = vec3(0, 1, 0);
			vec3 cameraRight = vec3(1, 0, 0);
			vec3 cameraDirection = vec3(0);
			vec3 cameraTarget = vec3(0);
		};

		struct CameraInfo {
			f32 speed = SPEED;
			f32 sensitivity = SENSITIVITY;
			f32 zoom = ZOOM;
			// f32 tbSpeed = speed;
		};

		struct CameraRotation {
			f32 yaw = YAW;
			f32 pitch = PITCH;
		};
	}; // namespace camera

	enum ProjectionType {
        PROJ_NONE,
		PROJ_ORTHO,
		PROJ_PERSP
	};

	struct CameraHelper {
		ProjectionType projectionType = ProjectionType::PROJ_NONE;
		// Ortho info
		f32 left = 0, right = 0, top = 0, bottom = 0;
		// Persp info
		f32 fov = 45.f, width = 0, height = 0;
		// Camera info
		vec3 pos{};
		vec3 target{};
	};

} // namespace bolt
