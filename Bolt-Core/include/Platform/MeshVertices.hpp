#pragma once

#include "../Core/Math.hpp"

#include "../Core/Structs.hpp"

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
				-0.5f, -0.5f,  0.5f};		// bottom-left
            
			inline f32 squareTexCoord[] = {
				0.0f, 0.0f,
				1.0f, 0.0f,
				1.0f, 1.0f,
				1.0f, 1.0f,			
				0.0f, 1.0f,
				0.0f, 0.0f};

			struct MeshVertices {
				std::vector<vec3> vertices;
				std::vector<vec4> colors;
			};

			inline MeshVertices getCircleVertices(const Pair<f32>& center, const Pair<f32>& radius, const u16& numTriangles, const vec4& color = vec4(0, 0, 0, 1)) {
				auto info = MeshVertices{};
				float stepA = (2 * FPI) / numTriangles;
				float t, xx, yy;

				info.vertices.emplace_back(center.x, center.y, 0.0f);
				info.colors.push_back(color);

				for (int i = 0; i <= numTriangles; i++)
				{
					t = (float)i * stepA;
					xx = center.x + radius.x * cos(t);
					yy = center.y + radius.y * sin(t);

					info.vertices.emplace_back(xx, yy, 0.0f);
					info.colors.push_back(color);
				}
				return info;
			}

			inline std::vector<vec4> getColorVector(i32 size, vec4 color) {
				std::vector<vec4> colorVector;
				colorVector.reserve(size);
				for (auto i = 0; i < size; i++)
					colorVector.push_back(color);
				return colorVector;
			}
		} // namespace mesh
	} // namespace factory
} // namespace bolt
