#pragma once

#include "../../Core/Resource.hpp"
#include "../../Core/Utils.hpp"

#include <string>

namespace Bolt {
	namespace shader {
		enum ShaderType {
			SHADER_VERTEX,
			SHADER_FRAGMENT,
            SHADER_PROGRAM,
			SHADER_NONE,
		};
	}

	class Shader {
	protected:
		shader::ShaderType m_type = shader::SHADER_NONE;
		Unique<Resource> m_resource;
		u32 m_id = 0;

	public:
		virtual void createShader() {}

		inline u32 getShaderId() const { return this->m_id; }

		inline void setShaderId(u32 id) { this->m_id = id; }

		inline shader::ShaderType getShaderType() const { return this->m_type; }

		inline std::string getShaderPath() const { return this->m_resource->getResourceLocation().append(this->m_resource->getResourceName()).c_str(); }

		inline b8 isShaderCodeLoaded() const { return this->m_resource->isResourceLoaded(); }

		inline b8 isShaderCreated() const { return this->m_id != 0; }

		Shader() = delete;

		Shader(std::string location, std::string name, shader::ShaderType type) :
			m_type(type) {
			this->m_resource = CreateUnique<Resource>(location, name);
		}

		Shader(std::string name, shader::ShaderType type) :
			Shader(res::DEFAULT_LOCATION, name, type) {}

		virtual ~Shader() = default;
	};
} // namespace Bolt
