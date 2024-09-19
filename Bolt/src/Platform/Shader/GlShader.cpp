#include "GlShader.hpp"

#include <cassert>

namespace Bolt {
	void GlShader::createShader() {
		this->m_resource->loadResource();
		assert(this->isShaderCodeLoaded());

		assert(this->m_type != shader::ShaderType::SHADER_NONE);
		assert(this->m_type != shader::ShaderType::SHADER_PROGRAM);

		auto shaderType = this->getShaderTypeValue(this->m_type);
		GLuint shaderId = glCreateShader(shaderType);

		std::string strCode = this->m_resource->getResourceContent();
		i32 lenght = strCode.length();
		const char *code = strCode.c_str();

		glShaderSource(shaderId, 1, &code, &lenght);
		glCompileShader(shaderId);
		this->checkCompileErrors(shaderId);
		this->setShaderId(shaderId);
	}

	GlShader::~GlShader() {
		this->m_resource->unloadResource();
	}

    void GlShaderProgram::use() const {
        glUseProgram(this->m_id);
    }

	void GlShaderProgram::setBool(const std::string &name, b8 value) {
		glUniform1i(glGetUniformLocation(this->getId(), name.c_str()), (int)value);
	}

	void GlShaderProgram::setInt(const std::string &name, i32 value) {
		glUniform1i(glGetUniformLocation(this->getId(), name.c_str()), value);
	}

	void GlShaderProgram::setFloat(const std::string &name, f32 value) {
		glUniform1f(glGetUniformLocation(this->getId(), name.c_str()), value);
	}

	void GlShaderProgram::setVec2(const std::string &name, const vec2 &value) {
		glUniform2fv(glGetUniformLocation(this->getId(), name.c_str()), 1, &value[0]);
	}

	void GlShaderProgram::setVec2(const std::string &name, f32 x, f32 y) {
		glUniform2f(glGetUniformLocation(this->getId(), name.c_str()), x, y);
	}

	void GlShaderProgram::setVec3(const std::string &name, const vec3 &value) {

		glUniform3fv(glGetUniformLocation(this->getId(), name.c_str()), 1, &value[0]);
	}

	void GlShaderProgram::setVec3(const std::string &name, f32 x, f32 y, f32 z) {
		glUniform3f(glGetUniformLocation(this->getId(), name.c_str()), x, y, z);
	}

	void GlShaderProgram::setVec4(const std::string &name, const vec4 &value) {
		glUniform4fv(glGetUniformLocation(this->getId(), name.c_str()), 1, &value[0]);
	}

	void GlShaderProgram::setVec4(const std::string &name, f32 x, f32 y, f32 z, f32 w) {
		glUniform4f(glGetUniformLocation(this->getId(), name.c_str()), x, y, z, w);
	}

	void GlShaderProgram::setMat2(const std::string &name, const mat2 &mat) {
		glUniformMatrix2fv(glGetUniformLocation(this->getId(), name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void GlShaderProgram::setMat3(const std::string &name, const mat3 &mat) {
		glUniformMatrix3fv(glGetUniformLocation(this->getId(), name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}

	void GlShaderProgram::setMat4(const std::string &name, const mat4 &mat) {
		glUniformMatrix4fv(glGetUniformLocation(this->getId(), name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
} // namespace Bolt
