#pragma once

#include "../../Core/Utils.hpp"

namespace Bolt {
	class Buffer {
	protected:
		const u32 m_id;

	public:
		Buffer() = delete;

		Buffer(const u32& id) : m_id(id) {}

		virtual ~Buffer() = default;

		virtual void bind() = 0;

		virtual void unbind() = 0;

		const u32& getId() const { return this->m_id; }
	};
}
