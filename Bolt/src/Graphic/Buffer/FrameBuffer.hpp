#pragma once

#include "../../Core/Utils.hpp"

namespace Bolt {

    // to be changed with texture
	struct TextureAttach {
		u32 id;
		u32 target;
		i32 level;
		u32 internalFormat;
		int width = 0;
		int height = 0;
		i32 border = 0;
		u32 format;
		u32 dataType;
		void *data;
	};

	class FrameBuffer {
	protected:
		u32 m_id = 0;

	public:
		FrameBuffer() = default;

		virtual ~FrameBuffer() = default;

		virtual void onAttach() {}

		virtual void onDetach() {}

		virtual void bind() const {}

		virtual void unbind() const {}

		virtual void attachTexture(const TextureAttach &attach) {}

		const u32 &getId() const { return this->m_id; }
	};
} // namespace Bolt

