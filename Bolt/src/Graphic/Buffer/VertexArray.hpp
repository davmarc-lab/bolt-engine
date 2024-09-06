#pragma once

#include "Buffer.hpp"
#include "VertexBuffer.hpp"

#include "../../Core/Utils.hpp"

namespace Bolt {
	class VertexArray : public Buffer {
	public:
		explicit VertexArray() = default;

		virtual ~VertexArray() override = default;

		virtual void onAttach() override;

		virtual void onDetach() override;

		virtual void bind() const override;

		virtual void unbind() const override;

		void linkVertexBuffer(const VertexBuffer &vbo, const u32 &layout, const i32 &size, const u32& &type, const i32 &stride, void *offset, const b8 &normalize = false) const;

		void linkAttribFast(const u32 &layout, const i32 &size, const u32 &type, const i32 &stride, void *offset, const b8 &normalize = false) const;

	};
}
