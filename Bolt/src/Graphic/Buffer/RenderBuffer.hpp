#pragma once

#include "../../Core/Utils.hpp"

namespace Bolt {
	class RenderBuffer {
	protected:
		u32 m_id = 0;

	public:
		RenderBuffer() = default;

		virtual ~RenderBuffer() = default;

        virtual void onAttach() {}
        virtual void onDetach() {}

        virtual void bind() const {}
        virtual void unbind() const {}

		const u32 &getId() const { return this->m_id; }
	};
} // namespace Bolt
