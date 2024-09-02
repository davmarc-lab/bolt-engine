#pragma once

#define GLM_ENABLE_EXPERIMENTAL

// glm library has a problem with absolute patterns
#include "../dependencies/glm/glm/glm.hpp"
#include "../dependencies/glm/glm/gtc/quaternion.hpp"
#include "../dependencies/glm/glm/gtx/quaternion.hpp"
// #include "../dependencies/glm/glm/gtc/matrix_access.hpp"
// #include "../dependencies/glm/glm/gtc/matrix_transform.hpp"
// #include "../dependencies/glm/glm/gtc/type_ptr.hpp"
#include "../dependencies/glm/glm/gtx/string_cast.hpp"

namespace Bolt {
	using glm::vec2;
	using glm::vec3;
	using glm::vec4;

	using glm::ivec2;
	using glm::ivec3;
	using glm::ivec4;

	using glm::mat4;

	using glm::quat;

	using glm::ortho;
	using glm::perspective;
	
	using glm::lookAt;
	using glm::quatLookAt;
	
	using glm::translate;
	using glm::scale;
	using glm::rotate;
	using glm::toMat4;

	using glm::radians;
	using glm::degrees;

	using glm::abs;
	using glm::clamp;
	using glm::lerp;
	
	using glm::pi;
	using glm::sin;
	using glm::asin;
	using glm::cos;
	using glm::acos;
	using glm::tan;
	using glm::atan;
	
	using glm::inverse;
	using glm::normalize;
	using glm::cross;
	using glm::dot;
	
	using glm::to_string;

	constexpr auto identity = mat4(1);
}
