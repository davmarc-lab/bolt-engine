#pragma once

#include "../Graphic/Renderer/Renderer.hpp"

#include "../Graphic/Buffer/VertexArray.hpp"

namespace Bolt {
	class GlRenderer : public Renderer {
	public:
		GlRenderer() = default;

		virtual ~GlRenderer() override = default;

		virtual void onAttach() override;

		void setPolygonMode();

		static void drawArrays(const VertexArray& vao, const u32& mode, const i32& first, const i32& count);
		
		void drawElements(const VertexArray& vao, const u32& mode, const i32& count, const u32& type, const void* indices = nullptr);

		void drawArraysLines(const VertexArray& vao, const i32& count, const i32& first = 0);

		void drawElementsLines(const VertexArray& vao, const i32& count);
		
		void drawArraysTriangles(const VertexArray& vao, const i32& count, const i32& first = 0);

		void drawElementsTriangles(const VertexArray& vao, const i32& count);
	};
}
