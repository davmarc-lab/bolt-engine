#pragma once

#include "../../Core/Utils.hpp"

#include "../../../dependencies/glad/include/glad/glad.h"
#include "../../Graphic/Texture/Texture.hpp"

namespace Bolt {
	namespace texture {
		namespace opengl {
			enum target : u32 {
				TEXTURE_1D = GL_TEXTURE_1D,
				TEXTURE_2D = GL_TEXTURE_2D,
				TEXTURE_3D = GL_TEXTURE_3D,
				TEXTURE_RECTANGLE = GL_TEXTURE_RECTANGLE,
				TEXTURE_BUFFER = GL_TEXTURE_BUFFER,
				TEXTURE_CUBE_MAP = GL_TEXTURE_CUBE_MAP,
				TEXTURE_1D_ARRAY = GL_TEXTURE_1D_ARRAY,
				TEXTURE_2D_ARRAY = GL_TEXTURE_2D_ARRAY,
				TEXTURE_CUBE_MAP_ARRAY = GL_TEXTURE_CUBE_MAP_ARRAY,
				TEXTURE_2D_MULTISAMPLE = GL_TEXTURE_2D_MULTISAMPLE,
				TEXTURE_2D_MULTISAMPLE_ARRAY = GL_TEXTURE_2D_MULTISAMPLE_ARRAY,
			};

			enum pname : u32 {
				// filters
				TEXTURE_MIN_FILTER = GL_TEXTURE_MIN_FILTER,
				TEXTURE_MAG_FILTER = GL_TEXTURE_MAG_FILTER,
				DEPTH_STENCIL_TEXTURE_MODE = GL_DEPTH_STENCIL_TEXTURE_MODE,
				// wrap
				TEXTURE_WRAP_S = GL_TEXTURE_WRAP_S,
				TEXTURE_WRAP_T = GL_TEXTURE_WRAP_T,
				TEXTURE_WRAP_R = GL_TEXTURE_WRAP_R,
				// border color (float[4])
				TEXTURE_BORDER_COLOR = GL_TEXTURE_BORDER_COLOR,
			};

			enum pvalue : u32 {
				// filters
				// bilinear
				LINEAR = GL_LINEAR,
				// no filtering, no mipmaps
				NEAREST = GL_NEAREST,
				// bilinear with mipmaps
				LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
				NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
				NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
				// trilinear
				LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
				DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
				STENCIL_INDEX = GL_STENCIL_INDEX,
				// wrap
				WRAP_REPEAT = GL_REPEAT,
				WRAP_MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
				WRAP_CLAMP_EDGE = GL_CLAMP_TO_EDGE,
				WRAP_CLAMP_BORDER = GL_CLAMP_TO_BORDER,
			};

			enum format : u32 {
				RED = GL_RED,
				RG = GL_RG,
				RGB = GL_RGB,
				RGBA = GL_RGBA,
				DEDPTH_COMPONENT = GL_DEPTH_COMPONENT,
				DEDPTH_STENCIL = GL_DEPTH_STENCIL,
			};

			enum dataType : u32 {
				UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
				BYTE = GL_BYTE,
				INT = GL_INT,
				UNSIGNED_INT = GL_UNSIGNED_INT,
				FLOAT = GL_FLOAT,
			};
		} // namespace opengl
	} // namespace texture

	class GlTexture : Texture {
	public:
		GlTexture() : Texture(texture::opengl::target::TEXTURE_2D) {}

		virtual ~GlTexture() override = default;

		virtual void onAttach() override;
		virtual void onDetach() override;

		virtual void bind() override;
		virtual void unbind() override;

		virtual void setTexParameter(u32 target, u32 pname, u32 pval) override;
		virtual void createTexture2D(
			u32 target,
			i32 level,
			u32 internalFormat,
			i32 width,
			i32 height,
			i32 border,
			u32 format,
			u32 dataType,
			void *data) override;

		virtual void generateMipmap(u32 target) override;
	};
} // namespace Bolt
