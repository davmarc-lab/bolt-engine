#pragma once

#include "Component.hpp"

#include "../Core/Math.hpp"
#include "../Core/Utils.hpp"

namespace Bolt {
	class Transform : public Component {
	public:
		vec3 position = vec3(0);
		vec3 scale = vec3(1);
		vec3 rotation = vec3(0);
		b8 dirty = false;
		mat4 modelMatrix = mat4(1);

		Transform() = default;

		~Transform() override = default;

		inline const b8 &isDirty() const { return this->dirty; }

		inline void setDirty(const b8 &dirty) { this->dirty = true; }

		inline const vec3 &getPosition() const { return this->position; }

		inline void setPosition(const vec3 &pos) {
			this->position = pos;
			this->dirty = true;
		}

		inline void addPosition(const vec3 &pos) {
			this->setPosition(this->position += pos);
		}

		inline const vec3 &getScale() const { return this->scale; }

		inline void setScale(const vec3 &scale) {
			this->scale = scale;
			this->dirty = true;
		}

		inline const vec3 &getRotation() const { return this->rotation; }

		inline void setRotation(const vec3 &rotation) {
			this->rotation = rotation;
			this->dirty = true;
		}
	};

	// inline const mat4& getModelMatrix() {
	// 	if (this->m_info.dirty) {
	// 		this->updateModelMatrix();
	// 		this->m_info.dirty = false;
	// 	}
	// 	return this->m_modelMatrix;
	// }

	// inline void setModelMatrix(const mat4& mat) { this->m_modelMatrix = mat; }
} // namespace Bolt
