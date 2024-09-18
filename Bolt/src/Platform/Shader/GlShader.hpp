#pragma once

#include <cassert>
#include <iostream>
#include "../../Graphic/Shader/Shader.hpp"

#include "../../../dependencies/glad/include/glad/glad.h"
#include "../../../dependencies/glfw/include/GLFW/glfw3.h"

namespace Bolt {
	class GlShader : public Shader {
	public:
		GlShader() = delete;

		GlShader(std::string location, std::string name, shader::ShaderType type) :
			Shader(location, name, type) {}

		GlShader(std::string name, shader::ShaderType type) :
			Shader(res::DEFAULT_LOCATION, name, type) {}

		virtual ~GlShader() override;

		virtual void createShader() override;

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
			std::string type = this->getShaderTypeString(this->m_type);

			GLint success;
			GLchar log[1024];

			if (this->m_type != shader::ShaderType::SHADER_PROGRAM) {
				glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
				if (!success) {
					glGetShaderInfoLog(shader, 1024, NULL, log);
					std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
							  << log
							  << "\n-- -------------------------------------------------- --\n";
				}
				else {
					glGetProgramiv(shader, GL_LINK_STATUS, &success);
					if (!success) {
						glGetShaderInfoLog(shader, 1024, NULL, log);
						std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
								  << log
								  << "\n-- -------------------------------------------------- --\n";
					}
				}
			}
		}
	};
} // namespace Bolt
