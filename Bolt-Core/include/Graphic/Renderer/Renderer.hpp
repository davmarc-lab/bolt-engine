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
	};

    struct Tracker {
        u32 cubes = 0;
    };

	class Renderer {
	public:
		Renderer() = default;

		virtual ~Renderer() = default;

		virtual void onAttach();

		virtual void onDetach();

		virtual Shared<ShaderProgram> getDefaultShader() const;

		virtual ShaderProgram *getCastersShader() const;

		virtual void drawCube(const vec3 &pos, const vec3 &scale, const vec3 &rot, const vec4 &color);

		virtual void drawCube(const mat4 &transform, const vec4 &color);

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
