#pragma once

#include <vector>
#include "../../Graphic/Buffer/FrameBuffer.hpp"
#include "../Texture/GlTexture.hpp"

#include "../../../dependencies/glad/include/glad/glad.h"

namespace Bolt {
	namespace framebuffer {
		namespace opengl {
			enum Operation : u32 {
				FB_READ = GL_READ_FRAMEBUFFER,
				FB_WRITE = GL_DRAW_FRAMEBUFFER,
				FB_DEFAULT = GL_FRAMEBUFFER
			};

			struct Config {
				Operation operation = FB_DEFAULT;
			} inline defaultConfig;

			inline const TextureAttach defaultTextureAttach = {
				0,
				texture::opengl::target::TEXTURE_2D,
				0,
				texture::opengl::format::RGB,
				0, 0,
				0,
				texture::opengl::format::RGB,
				texture::opengl::dataType::UNSIGNED_BYTE,
				NULL};
		} // namespace opengl

	} // namespace framebuffer

	class GlFrameBuffer : FrameBuffer {
	private:
		using Config = framebuffer::opengl::Config;

		Config m_config;
		std::vector<TextureAttach> m_texturesAttachement;
		// std::vector<RenderBuffer> m_renderBuffers;

	public:
		GlFrameBuffer(const Config &config = framebuffer::opengl::defaultConfig) :
			m_config(config) {}

		virtual ~GlFrameBuffer() override = default;

		virtual void onAttach() override;
		virtual void onDetach() override;

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void attachTexture(const TextureAttach &attach) override;
	};
} // namespace Bolt
