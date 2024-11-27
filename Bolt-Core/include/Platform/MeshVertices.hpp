#pragma once

#include <vector>
#include "../Core/Math.hpp"

#include "../Core/Structs.hpp"

namespace bolt {
	namespace factory {
		namespace mesh {
			inline std::vector<vec3> cubeGeometry{
				// vertex pos
				{-1.0f, -1.0f, -1.0f},
				{1.0f, 1.0f, -1.0f},
				{1.0f, -1.0f, -1.0f},
				{1.0f, 1.0f, -1.0f},
				{-1.0f, -1.0f, -1.0f},
				{-1.0f, 1.0f, -1.0f},

				{-1.0f, -1.0f, 1.0f},
				{1.0f, -1.0f, 1.0f},
				{1.0f, 1.0f, 1.0f},
				{1.0f, 1.0f, 1.0f},
				{-1.0f, 1.0f, 1.0f},
				{-1.0f, -1.0f, 1.0f},

				{-1.0f, 1.0f, 1.0f},
				{-1.0f, 1.0f, -1.0f},
				{-1.0f, -1.0f, -1.0f},
				{-1.0f, -1.0f, -1.0f},
				{-1.0f, -1.0f, 1.0f},
				{-1.0f, 1.0f, 1.0f},

				{1.0f, 1.0f, 1.0f},
				{1.0f, -1.0f, -1.0f},
				{1.0f, 1.0f, -1.0f},
				{1.0f, -1.0f, -1.0f},
				{1.0f, 1.0f, 1.0f},
				{1.0f, -1.0f, 1.0f},

				{-1.0f, -1.0f, -1.0f},
				{1.0f, -1.0f, -1.0f},
				{1.0f, -1.0f, 1.0f},
				{1.0f, -1.0f, 1.0f},
				{-1.0f, -1.0f, 1.0f},
				{-1.0f, -1.0f, -1.0f},

				{-1.0f, 1.0f, -1.0f},
				{1.0f, 1.0f, 1.0f},
				{1.0f, 1.0f, -1.0f},
				{1.0f, 1.0f, 1.0f},
				{-1.0f, 1.0f, -1.0f},
				{-1.0f, 1.0f, 1.0f}};

			inline std::vector<vec2> cubeTexCoord{
				// texCoord
				{0.0f, 0.0f},
				{1.0f, 1.0f},
				{1.0f, 0.0f},
				{1.0f, 1.0f},
				{0.0f, 0.0f},
				{0.0f, 1.0f},

				{0.0f, 0.0f},
				{1.0f, 0.0f},
				{1.0f, 1.0f},
				{1.0f, 1.0f},
				{0.0f, 1.0f},
				{0.0f, 0.0f},

				{1.0f, 0.0f},
				{1.0f, 1.0f},
				{0.0f, 1.0f},
				{0.0f, 1.0f},
				{0.0f, 0.0f},
				{1.0f, 0.0f},

				{1.0f, 0.0f},
				{0.0f, 1.0f},
				{1.0f, 1.0f},
				{0.0f, 1.0f},
				{1.0f, 0.0f},
				{0.0f, 0.0f},

				{0.0f, 1.0f},
				{1.0f, 1.0f},
				{1.0f, 0.0f},
				{1.0f, 0.0f},
				{0.0f, 0.0f},
				{0.0f, 1.0f},

				{0.0f, 1.0f},
				{1.0f, 0.0f},
				{1.0f, 1.0f},
				{1.0f, 0.0f},
				{0.0f, 1.0f},
				{0.0f, 0.0f}};

			inline std::vector<vec3> cubeNormals{
				{0.f, 0.f, -1.f},
				{0.f, 0.f, -1.f},
				{0.f, 0.f, -1.f},
				{0.f, 0.f, -1.f},
				{0.f, 0.f, -1.f},
				{0.f, 0.f, -1.f},

				{0.f, 0.f, 1.f},
				{0.f, 0.f, 1.f},
				{0.f, 0.f, 1.f},
				{0.f, 0.f, 1.f},
				{0.f, 0.f, 1.f},
				{0.f, 0.f, 1.f},

				{-1.f, 0.f, 0.f},
				{-1.f, 0.f, 0.f},
				{-1.f, 0.f, 0.f},
				{-1.f, 0.f, 0.f},
				{-1.f, 0.f, 0.f},
				{-1.f, 0.f, 0.f},

				{1.f, 0.f, 0.f},
				{1.f, 0.f, 0.f},
				{1.f, 0.f, 0.f},
				{1.f, 0.f, 0.f},
				{1.f, 0.f, 0.f},
				{1.f, 0.f, 0.f},

				{0.f, -1.f, 0.f},
				{0.f, -1.f, 0.f},
				{0.f, -1.f, 0.f},
				{0.f, -1.f, 0.f},
				{0.f, -1.f, 0.f},
				{0.f, -1.f, 0.f},

				{0.f, 1.f, 0.f},
				{0.f, 1.f, 0.f},
				{0.f, 1.f, 0.f},
				{0.f, 1.f, 0.f},
				{0.f, 1.f, 0.f},
				{0.f, 1.f, 0.f},
			};

			inline std::vector<vec3> squareGeometry{
				// bottom-le}t
				{-1.0f, -1.0f, 1.0f},
				// bottom-rig}t
				{1.0f, -1.0f, 1.0f},
				// top-rig}t
				{1.0f, 1.0f, 1.0f},
				// top-rig}t
				{1.0f, 1.0f, 1.0f},
				// top-le}t
				{-1.0f, 1.0f, 1.0f},
				// bottom-left
				{-1.0f, -1.0f, 1.0f}};

			inline std::vector<vec2> squareTexCoord{
				{0.0f, 0.0f},
				{1.0f, 0.0f},
				{1.0f, 1.0f},
				{1.0f, 1.0f},
				{0.0f, 1.0f},
				{0.0f, 0.0f}};

			inline std::vector<vec3> squareNormals{
				{0.f, 0.f, -1.f},
				{0.f, 0.f, -1.f},
				{0.f, 0.f, -1.f},
				{0.f, 0.f, -1.f},
				{0.f, 0.f, -1.f},
				{0.f, 0.f, -1.f},
			};

			struct MeshVertices {
				std::vector<vec3> vertices;
				std::vector<vec4> colors;
				std::vector<vec3> normals;
			};

			inline MeshVertices getCircleVertices(const Pair<f32> &center, const Pair<f32> &radius, const u16 &numTriangles, const vec4 &mid = vec4(0, 0, 0, 1), const vec4 &out = vec4(0, 0, 0, 1)) {
				auto info = MeshVertices{};
				float stepA = (2 * FPI) / static_cast<f32>(numTriangles);
				float t, xx, yy;

				info.vertices.emplace_back(center.x, center.y, 0.0f);
				info.colors.push_back(mid);
				info.normals.push_back({0.f, 0.f, -1.f});

				for (int i = 0; i <= numTriangles; i++) {
					t = (float)i * stepA;
					xx = center.x + radius.x * cos(t);
					yy = center.y + radius.y * sin(t);

					info.vertices.emplace_back(xx, yy, 0.0f);
					info.colors.push_back(vec4(1, 0, 0, 1));
					info.normals.push_back({0.f, 0.f, -1.f});
				}
				return info;
			}

			inline std::vector<vec4> getColorVector(const size_t &size, const vec4 &color) {
				std::vector<vec4> colorVector;
				colorVector.reserve(size);
				for (size_t i = 0; i < size; i++)
					colorVector.push_back(color);
				return colorVector;
			}
		} // namespace mesh
	} // namespace factory
} // namespace bolt
