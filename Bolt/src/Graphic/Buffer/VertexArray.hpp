#pragma once

#include "VertexBuffer.hpp"

#include "../../Core/Utils.hpp"

namespace Bolt {
	class VertexArray {
	protected:
		u32 m_id;

	public:
		VertexArray() = default;

		virtual ~VertexArray() = default;

		virtual void onAttach() {}

		virtual void onDetach() {}

		virtual void bind() const {}

		virtual void unbind() const {}

		virtual void linkVertexBuffer(const VertexBuffer &vbo, const u32 &layout, const i32 &size, const u32 &type, const i32 &stride, void *offset, const b8 &normalize = false) const { /* BT_WARN_CORE("Put an assert here {0}.", __FILE__); */ }

		virtual void linkAttribFast(const u32 &layout, const i32 &size, const u32 &type, const i32 &stride, void *offset, const b8 &normalize = false) const { /* BT_WARN_CORE("Put an assert here {0}.", __FILE__); */ }
	};
} // namespace Bolt
