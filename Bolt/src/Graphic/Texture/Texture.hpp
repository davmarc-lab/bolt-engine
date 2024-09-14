#pragma once

#include <cassert>

#include "../../Core/Utils.hpp"

namespace Bolt {

	namespace texture {
	}

	class Texture {
	protected:
		u32 m_id = 0;
		u16 m_width = 0;
		u16 m_height = 0;
		b8 m_created = false;
        b8 m_customParam = false;
        u32 m_type;

	public:
        Texture() : Texture(0) {}

        Texture(u32 type) : m_type(type) {}

		virtual ~Texture() = default;

		virtual void onAttach() {}

		virtual void onDetach() {}

		virtual void bind() {}

		virtual void unbind() {}

		virtual void setTexParameter(u32 target, u32 pname, u32 pval) {}

		virtual void createTexture2D(
			u32 target,
			i32 level,
			u32 internalFormat,
			i32 width,
			i32 height,
			i32 border,
			u32 format,
			u32 dataType,
			void *data) { this->m_created = true; }

		virtual void generateMipmap(u32 target) { assert(this->m_created); }

		u32 getId() const { return this->m_id; }
	};
} // namespace Bolt
