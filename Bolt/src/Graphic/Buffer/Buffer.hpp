#pragma once

#include "../../Core/Utils.hpp"

namespace Bolt {
    namespace buffers {
        BT_AUTOCONST DEFAULT_USAGE = 0;
        BT_AUTOCONST DEFAULT_TYPE = 0;
    }

	class Buffer {
	protected:
		u32 m_id = 0;

	public:
		Buffer() = default;

		virtual ~Buffer() = default;

		virtual void onAttach() {}

		virtual void onDetach() {}

		virtual void bind() const {}

		virtual void unbind() const {}

		const u32& getId() const { return this->m_id; }
	};
}
