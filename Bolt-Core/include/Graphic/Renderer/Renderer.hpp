#pragma once

#include "../Buffer/VertexArray.hpp"
#include "../Shader/Shader.hpp"
#include "../../ECS/Component.hpp"

namespace bolt {
	struct Primitive {
		VertexArray vao;
		VertexBuffer vbo_g;
		VertexBuffer vbo_t;
		NormalsComponent normals;
		VertexBuffer vbo_mi;
		std::vector<mat4> modelInstance{};
		VertexBuffer vbo_co;
		std::vector<vec4> colorOffset{};
		b8 skipLights = false;
	};

	struct Tracker {
		u32 drawCalls = 0;
		u32 triangles = 0;
		u32 squares = 0;
		u32 circles = 0;
		u32 cones = 0;
		u32 cubes = 0;
		u32 spheres = 0;
	};

	class Renderer {
	public:
		Renderer() = default;

		virtual ~Renderer() = default;

		virtual void onAttach();

		virtual void onDetach();

		virtual Shared<ShaderProgram> getDefaultShader() const;

		virtual ShaderProgram *getCastersShader() const;

		inline u32 getTrackerTotal() const {
			return this->m_tracker.triangles + this->m_tracker.squares + this->m_tracker.circles + this->m_tracker.cones + this->m_tracker.cubes + this->m_tracker.spheres;
		}

		inline u32 getRenderCallCount() const { return this->m_tracker.drawCalls; }

		virtual void drawCube(const vec3 &pos, const vec3 &scale, const vec3 &rot, const vec4 &color, const b8& lights = true);

		virtual void drawCube(const mat4 &transform, const vec4 &color, const b8& lights = true);

		// GPU Draw calls
		virtual void drawArrays(const VertexArray &vao, const u32 &mode, const i32 &first, const size_t &count);

		virtual void drawElements(const VertexArray &vao, const u32 &mode, const size_t &count, const u32 &type, const void *indices = nullptr);

		virtual void drawArraysLines(const VertexArray &vao, const size_t &count, const i32 &first = 0);

		virtual void drawElementsLines(const VertexArray &vao, const size_t &count);

		virtual void drawArraysTriangles(const VertexArray &vao, const size_t &count, const i32 &first = 0);

		virtual void drawArraysTriangleFan(const VertexArray &vao, const size_t &count, const i32 &first = 0);

		virtual void drawElementsTriangles(const VertexArray &vao, const size_t &count);

		virtual void drawIndexed();

	private:
		Shared<ShaderProgram> m_shader = nullptr;
		Unique<ShaderProgram> m_casterShader = nullptr;
		Unique<ShaderProgram> m_instancedShader = nullptr;

		Tracker m_tracker{};
		Primitive m_cube{};
	};
} // namespace bolt
