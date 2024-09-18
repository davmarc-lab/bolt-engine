#include "GlShader.hpp"

#include <cassert>

namespace Bolt {
	namespace shader {
		static Unique<GlShader> linkVertFragShaders(GlShader vert, GlShader frag) {
			if (vert.getShaderType() != ShaderType::SHADER_VERTEX) {
				// BT_ERROR_CORE("The first parameter is not of type SHADER_VERTEX.");
				return nullptr;
			}

			if (frag.getShaderType() != ShaderType::SHADER_FRAGMENT) {
				// BT_ERROR_CORE("The second parameter is not of type SHADER_FRAGMENT.");
				return nullptr;
			}
			return nullptr;
		}
	} // namespace shader

	void GlShader::createShader() {
		this->m_resource->loadResource();
		assert(this->isShaderCodeLoaded());

		assert(this->m_type != shader::ShaderType::SHADER_NONE);
		assert(this->m_type != shader::ShaderType::SHADER_PROGRAM);

		auto shaderType = this->getShaderTypeValue(this->m_type);
		GLuint shaderId = glCreateShader(shaderType);

        // ????
		const char *code = this->m_resource->getResourceContent().c_str();
		glShaderSource(shaderId, 1, &code, NULL);
		glCompileShader(shaderId);
        this->checkCompileErrors(shaderId);
        this->setShaderId(shaderId);
	}

	GlShader::~GlShader() {
		this->m_resource->unloadResource();
	}
} // namespace Bolt
