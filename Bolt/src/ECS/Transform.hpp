#pragma once

#include <ECS/Component.hpp>

#include <Core/Utils.hpp>
#include <Core/Math.hpp>

namespace Bolt {
	class Transform : public Component {
	public:
		vec3 position = vec3(0);
		vec3 scale = vec3(1);
		vec3 rotation = vec3(0);
		b8 dirty = false;
		mat4 modelMatrix = mat4(1);

		Transform() : Component(ecs::Components::transform) {}

		~Transform() override = default;
	};

	// inline const b8& isDirty() const { return this->m_info.dirty; }

	// inline void setDirty(const b8& dirty) { this->m_info.dirty = true; }

	// inline const vec3& getPosition() const { return this->m_info.position; }

	// inline void setPosition(const vec3& pos) {
	// 	this->m_info.position = pos;
	// 	this->m_info.dirty = true;
	// }

	// inline const vec3& getScale() const { return this->m_info.scale; }

	// inline void setScale(const vec3& scale) {
	// 	this->m_info.scale = scale;
	// 	this->m_info.dirty = true;
	// }

	// inline const vec3& getRotation() const { return this->m_info.rotation; }

	// inline void setRotation(const vec3& rotation) {
	// 	this->m_info.rotation = rotation;
	// 	this->m_info.dirty = true;
	// }

	// inline const mat4& getModelMatrix() {
	// 	if (this->m_info.dirty) {
	// 		this->updateModelMatrix();
	// 		this->m_info.dirty = false;
	// 	}
	// 	return this->m_modelMatrix;
	// }

	// inline void setModelMatrix(const mat4& mat) { this->m_modelMatrix = mat; }
}
