#pragma once

#include "Utils.hpp"

#define GLM_ENABLE_EXPERIMENTAL

// glm library has a problem with absolute patterns
#include "../../../Bolt-Vendor/include/glm/gtc/quaternion.hpp"
#include "../../../Bolt-Vendor/include/glm/gtc/type_ptr.hpp"
#include "../../../Bolt-Vendor/include/glm/gtx/quaternion.hpp"
#include "../../../Bolt-Vendor/include/glm/gtx/string_cast.hpp"

namespace bolt {
	using glm::vec2;
	using glm::vec3;
	using glm::vec4;

	using glm::ivec2;
	using glm::ivec3;
	using glm::ivec4;

	using glm::mat2;
	using glm::mat3;
	using glm::mat4;

	using glm::quat;

	using glm::ortho;
	using glm::perspective;

	using glm::lookAt;
	using glm::quatLookAt;

	using glm::rotate;
	using glm::scale;
	using glm::toMat4;
	using glm::translate;

	using glm::degrees;
	using glm::radians;

	using glm::abs;
	using glm::clamp;
	using glm::lerp;

	using glm::acos;
	using glm::asin;
	using glm::atan;
	using glm::cos;
	using glm::pi;
	using glm::sin;
	using glm::tan;

	using glm::cross;
	using glm::dot;
	using glm::inverse;
	using glm::normalize;

	using glm::to_string;
	using glm::value_ptr;

	BT_CONSTEXPR auto identity = mat4(1);
} // namespace bolt

namespace bmath {
	struct bvec2 {
		f32 x = 0, y = 0;
	};

	struct bvec3 {
		f32 x = 0, y = 0, z = 0;
	};

	struct bvec4 {
		f32 r = 0, g = 0, b = 0, a = 0;
	};
} // namespace bmath
