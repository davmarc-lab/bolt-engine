#pragma once

#include "../../Graphic/Buffer/VertexArray.hpp"
#include "../../Graphic/Buffer/VertexBuffer.hpp"

#include "../../Core/Utils.hpp"

namespace Bolt {
	class GlVertexArray : public VertexArray {
	public:
		GlVertexArray() = default;

		virtual ~GlVertexArray() = default;

		virtual void onAttach() override;

		virtual void onDetach() override;

		virtual void bind() const override;

		virtual void unbind() const override;

		virtual void linkVertexBuffer(const VertexBuffer &vbo, const u32 &layout, const i32 &size, const u32 &type, const i32 &stride, void *offset, const b8 &normalize = false) const override;

		virtual void linkAttribFast(const u32 &layout, const i32 &size, const u32 &type, const i32 &stride, void *offset, const b8 &normalize = false) const override;
	};
} // namespace Bolt
