#pragma once

#include "../../Graphic/Shader/Shader.hpp"

#include <cassert>
#include <iostream>

#include "../../Core/Math.hpp"
#include "../../../dependencies/glad/include/glad/glad.h"

namespace Bolt {
	class GlShader : public Shader {
	public:
		virtual void createShader() override;

		GlShader() = delete;

		GlShader(std::string location, std::string name, shader::ShaderType type) :
			Shader(location, name, type) {}

		GlShader(std::string name, shader::ShaderType type) :
			Shader(res::DEFAULT_LOCATION, name, type) {}

		virtual ~GlShader() override;

	private:
		inline GLenum getShaderTypeValue(shader::ShaderType type) {
			switch (type) {
				case shader::SHADER_VERTEX: return GL_VERTEX_SHADER;
				case shader::SHADER_FRAGMENT: return GL_FRAGMENT_SHADER;
				case shader::SHADER_PROGRAM: /* BT_ERROR_CORE("Cannot find the correct shader type."); */ assert(false);
				default: /* BT_ERROR_CORE("Cannot find the correct shader type."); */ assert(false);
			}
		}

		inline std::string getShaderTypeString(shader::ShaderType type) {
			switch (type) {
				case shader::SHADER_VERTEX: return "VERTEX";
				case shader::SHADER_FRAGMENT: return "FRAGMENT";
				case shader::SHADER_PROGRAM: return "PROGRAM";
				default: return "NONE";
			}
		}

		inline void checkCompileErrors(GLuint shader) {
			std::string strType = this->getShaderTypeString(this->m_type);
			i32 success;
			i8 log[1024];

			if (this->m_type != shader::ShaderType::SHADER_PROGRAM) {
				glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
				if (!success) {
					glGetShaderInfoLog(shader, 1024, NULL, log);
					std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << strType << "\n"
							  << log
							  << "\n-- -------------------------------------------------- --\n";
				}
			}
		}
	};

	class GlShaderProgram {
	public:
		void use() const;

		inline u32 getId() const { return this->m_id; }

		inline b8 isProgramCreated() const { return this->m_id != 0; }

		void setBool(const std::string &name, b8 value);
		void setInt(const std::string &name, i32 value);
		void setFloat(const std::string &name, f32 value);

		void setVec2(const std::string &name, const vec2 &value);
		void setVec2(const std::string &name, f32 x, f32 y);

		void setVec3(const std::string &name, const vec3 &value);
		void setVec3(const std::string &name, f32 x, f32 y, f32 z);

		void setVec4(const std::string &name, const vec4 &value);
		void setVec4(const std::string &name, f32 x, f32 y, f32 z, f32 w);

		void setMat2(const std::string &name, const mat2 &mat);
		void setMat3(const std::string &name, const mat3 &mat);
		void setMat4(const std::string &name, const mat4 &mat);

		GlShaderProgram() = delete;

		GlShaderProgram(const GlShader &vert, const GlShader &frag) :
			GlShaderProgram(vert.getShaderId(), frag.getShaderId()) {}

		GlShaderProgram(u32 vert, u32 frag) :
			m_vert(vert), m_frag(frag) {

			this->m_id = glCreateProgram();
			glAttachShader(this->m_id, this->m_vert);
			glAttachShader(this->m_id, this->m_frag);
			glLinkProgram(this->m_id);
			this->checkLinkingError();

            glDeleteShader(vert);
            glDeleteShader(frag);
		}

		~GlShaderProgram() = default;

	private:
		u32 m_id = 0;
		u32 m_vert;
		u32 m_frag;

		void checkLinkingError() {
			i32 success;
			i8 log[1024];

			glGetProgramiv(this->m_id, GL_LINK_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(this->m_id, 1024, NULL, log);
				std::cout << "ERROR::SHADER_PROGRAM_LINKING_ERROR of type: " << "PROGRAM" << "\n"
						  << log
						  << "\n-- -------------------------------------------------- --\n";
			}
		}
	};

	namespace shader {
		namespace gl {
			static Unique<GlShaderProgram> linkVertFragShaders(const GlShader &vert, const GlShader &frag) {
				// are shaders valid?
				if (vert.getShaderType() != ShaderType::SHADER_VERTEX) {
					// BT_ERROR_CORE("The first parameter is not of type SHADER_VERTEX.");
					return nullptr;
				}
				if (frag.getShaderType() != ShaderType::SHADER_FRAGMENT) {
					// BT_ERROR_CORE("The second parameter is not of type SHADER_FRAGMENT.");
					return nullptr;
				}

				// are shaders loaded?
				if (!vert.isShaderCreated()) {
					return nullptr;
					// BT_ERROR_CORE("Vertex Shader is not created.");
				}
				if (!frag.isShaderCreated()) {
					return nullptr;
					// BT_ERROR_CORE("Fragment Shader is not created.");
				}

				// link shaders and return GlShaderProgram
				return CreateUnique<GlShaderProgram>(vert, frag);
			}
		} // namespace gl
	} // namespace shader
} // namespace Bolt
