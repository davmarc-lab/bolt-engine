#pragma once

#include "../Core/Math.hpp"
#include <memory>

#include "../Graphic/Buffer/VertexArray.hpp"
#include "../Graphic/Buffer/VertexBuffer.hpp"

namespace Bolt {
	class Component {
	public:

        Component() = default;

		virtual ~Component() = default;
	};

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

	class Mesh : public Component {
	public:
        VertexArray vao;
        VertexBuffer vbo_g;
		std::unique_ptr<std::vector<vec3>> vertices;
        b8 instanced = false;

		Mesh() = default;

		~Mesh() override = default;
	};
}
