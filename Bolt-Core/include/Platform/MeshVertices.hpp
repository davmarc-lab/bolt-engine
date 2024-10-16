#pragma once

#include "../Core/Math.hpp"

#include <cstddef>

namespace bolt {
	namespace factory {
		namespace mesh {
			inline float cubeGeometry[] = {
				// vertex pos
				-0.5f, -0.5f, -0.5f,
				0.5f, 0.5f, -0.5f,
				0.5f, -0.5f, -0.5f,
				0.5f, 0.5f, -0.5f,
				-0.5f, -0.5f, -0.5f,
				-0.5f, 0.5f, -0.5f,

				-0.5f, -0.5f, 0.5f,
				0.5f, -0.5f, 0.5f,
				0.5f, 0.5f, 0.5f,
				0.5f, 0.5f, 0.5f,
				-0.5f, 0.5f, 0.5f,
				-0.5f, -0.5f, 0.5f,

				-0.5f, 0.5f, 0.5f,
				-0.5f, 0.5f, -0.5f,
				-0.5f, -0.5f, -0.5f,
				-0.5f, -0.5f, -0.5f,
				-0.5f, -0.5f, 0.5f,
				-0.5f, 0.5f, 0.5f,

				0.5f, 0.5f, 0.5f,
				0.5f, -0.5f, -0.5f,
				0.5f, 0.5f, -0.5f,
				0.5f, -0.5f, -0.5f,
				0.5f, 0.5f, 0.5f,
				0.5f, -0.5f, 0.5f,

				-0.5f, -0.5f, -0.5f,
				0.5f, -0.5f, -0.5f,
				0.5f, -0.5f, 0.5f,
				0.5f, -0.5f, 0.5f,
				-0.5f, -0.5f, 0.5f,
				-0.5f, -0.5f, -0.5f,

				-0.5f, 0.5f, -0.5f,
				0.5f, 0.5f, 0.5f,
				0.5f, 0.5f, -0.5f,
				0.5f, 0.5f, 0.5f,
				-0.5f, 0.5f, -0.5f,
				-0.5f, 0.5f, 0.5f};

			inline float cubeTexCoord[] = {
				// texCoord
				0.0f, 0.0f,
				1.0f, 1.0f,
				1.0f, 0.0f,
				1.0f, 1.0f,
				0.0f, 0.0f,
				0.0f, 1.0f,

				0.0f, 0.0f,
				1.0f, 0.0f,
				1.0f, 1.0f,
				1.0f, 1.0f,
				0.0f, 1.0f,
				0.0f, 0.0f,

				1.0f, 0.0f,
				1.0f, 1.0f,
				0.0f, 1.0f,
				0.0f, 1.0f,
				0.0f, 0.0f,
				1.0f, 0.0f,

				1.0f, 0.0f,
				0.0f, 1.0f,
				1.0f, 1.0f,
				0.0f, 1.0f,
				1.0f, 0.0f,
				0.0f, 0.0f,

				0.0f, 1.0f,
				1.0f, 1.0f,
				1.0f, 0.0f,
				1.0f, 0.0f,
				0.0f, 0.0f,
				0.0f, 1.0f,

				0.0f, 1.0f,
				1.0f, 0.0f,
				1.0f, 1.0f,
				1.0f, 0.0f,
				0.0f, 1.0f,
				0.0f, 0.0f};

			inline f32 squareGeometry[] = {
				-0.5f, -0.5f,  0.5f,		// bottom-left
				 0.5f, -0.5f,  0.5f,		// bottom-right
				 0.5f,  0.5f,  0.5f,		// top-right
				 0.5f,  0.5f,  0.5f,		// top-right
				-0.5f,  0.5f,  0.5f,		// top-left
				-0.5f, -0.5f,  0.5f,};		// bottom-left
            
			inline f32 squareTexCoord[] = {
				0.0f, 0.0f,
				1.0f, 0.0f,
				1.0f, 1.0f,
				1.0f, 1.0f,			
				0.0f, 1.0f,
				0.0f, 0.0f};

			inline std::vector<vec4> getColorVector(i32 size, vec4 color) {
				std::vector<vec4> colorVector;
				for (auto i = 0; i < size; i++)
					colorVector.push_back(color);
				return colorVector;
			}
		} // namespace mesh
	} // namespace factory
} // namespace bolt
