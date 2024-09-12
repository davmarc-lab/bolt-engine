#pragma once

#include "../../Core/Utils.hpp"

#include "../../../dependencies/glad/include/glad/glad.h"
#include "../../Graphic/Texture/Texture.hpp"

namespace Bolt {
	namespace texture {
		namespace opengl {
			enum pname : u32 {
				TEXTURE_MIN_FILTER = GL_TEXTURE_MIN_FILTER,
				TEXTURE_MAX_FILTER = GL_TEXTURE_MAG_FILTER,
			};

			enum pvalue : u32 {
				LINEAR = GL_LINEAR,
				NEARES = GL_NEAREST,
			};

			enum target : u32 {
				TEXTURE_1D = GL_TEXTURE_1D,
				TEXTURE_2D = GL_TEXTURE_2D,
				TEXTURE_3D = GL_TEXTURE_3D,
			};

			enum format : u32 {
				DEDPTH_COMPONENT = GL_DEPTH_COMPONENT,
				DEDPTH_STENCIL = GL_DEPTH_STENCIL,
				RED = GL_RED,
				RG = GL_RG,
				RGB = GL_RGB,
				RGBA = GL_RGBA,
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
		virtual ~GlTexture() override = default;
	};
} // namespace Bolt
