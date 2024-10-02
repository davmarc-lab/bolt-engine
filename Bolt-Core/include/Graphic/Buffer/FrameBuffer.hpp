#pragma once

#include "../../Core/Utils.hpp"

#include "../../../../Bolt-Graphics/include/glad/glad.h"

#include "../Texture/Texture.hpp"

#include <vector>

#include "RenderBuffer.hpp"

namespace bolt {

	namespace fbo {
			enum Operation : u32 {
				FB_READ = GL_READ_FRAMEBUFFER,
				FB_WRITE = GL_DRAW_FRAMEBUFFER,
				FB_DEFAULT = GL_FRAMEBUFFER
			};

			struct Config {
				Operation operation = FB_DEFAULT;
			} inline defaultConfig;

	} // namespace framebuffer

	class FrameBuffer {
	protected:
		u32 m_id = 0;

		using Config = fbo::Config;

		Config m_config;
		Texture m_textureAttach{};
		RenderBuffer m_renderBuffer{};

	public:
		FrameBuffer() = default;

		FrameBuffer(Config config = {}) : m_config(config) {} 

		~FrameBuffer() = default;

		void onAttach();

		void onDetach();

		void bind() const;

		void unbind() const;

		const u32 &getId() const { return this->m_id; }
	};
} // namespace Bolt

