#pragma once

#include <memory>

#include "Component.hpp"

#include "../Core/Math.hpp"

namespace Bolt {
	class Render : public Component {
	public:
		std::unique_ptr<std::vector<vec3>> vertices;
		std::unique_ptr<std::vector<vec4>> colors;
		std::unique_ptr<std::vector<u32>> indices;

		Render() = default;

		~Render() override = default;
	};
}
