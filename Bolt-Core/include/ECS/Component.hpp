#pragma once

#include <functional>
#include <ios>
#include <iostream>
#include <ranges>
#include <vector>

#include "../Core/Math.hpp"
#include "../Core/Structs.hpp"

#include "../Graphic/Buffer/ElementBuffer.hpp"
#include "../Graphic/Buffer/VertexArray.hpp"
#include "../Graphic/Buffer/VertexBuffer.hpp"

#include "../Graphic/Shader/Shader.hpp"

namespace bolt {
	struct Component {
	public:
		Component() = default;

		virtual ~Component() = default;
	};

	struct Transform : public Component {
	private:
		vec3 position = vec3(0);
		vec3 scale = vec3(1);
		vec3 rotation = vec3(0);
		quat quaternion{};
		mat4 modelMatrix = mat4(1);
		b8 enableModel = true;
		b8 dirty = false;

	public:
		Transform() = default;

		~Transform() override = default;

		inline b8 isModelMatrixEnable() const { return this->enableModel; }

		inline void enableModelMatrix(b8 flag) { this->enableModel = flag; }

		inline const b8 &isDirty() const { return this->dirty; }

		inline void setDirty(const b8 &dirty) { this->dirty = true; }

		inline const mat4 &getModelMatrix() const { return this->modelMatrix; }

		inline void setModelMatrix(mat4 matrix) {
			this->modelMatrix = matrix;
			this->dirty = false;
		}

		inline const vec3 &getPosition() const { return this->position; }

		inline void setPosition(vec3 pos) {
			this->position = pos;
			this->dirty = true;
		}

		inline void addPosition(vec3 pos) {
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

		inline const quat &getQuaternion() const { return this->quaternion; }

		inline void setQuaternion(quat quaternion) {
			this->quaternion = quaternion;
			this->dirty = true;
		}
	};

	struct Color : public Component {
	public:
		VertexBuffer vbo_c;
		std::vector<vec4> colors;

		Color() = default;

		~Color() override = default;
	};

	// Default Black plastic
	struct Material : public Component {
	public:
		vec3 ambient{0.32, 0.22, 0.027};
		vec3 diffuse{.78, .56, .11};
		vec3 specular{.99, .94, .80};
		f32 shininess = 27.f;

		Material() = default;
		~Material() override = default;
	};

	struct PBRMaterial : public Component {
	public:
		vec3 albedo{};
		f32 metallic{}, roughness{}, ao{};

		PBRMaterial() = default;
		~PBRMaterial() override = default;
	};

	struct Light : public Component {
	public:
		vec3 color{1, 1, 1};
		f32 intensity{};
		LightType type;
        LightVectors vectors;

		b8 showCaster = true;

		Light(const LightHelper &helper) :
			type(helper.type), vectors(helper.vectors), color(helper.color), intensity(helper.intensity) {}

		Light() = default;
		virtual ~Light() override = default;
	};

	struct DirectionalLight : public Light {
	public:
		vec3 direction{};

		DirectionalLight(const LightHelper &helper) :
			Light(helper), direction(helper.direction) {}

		DirectionalLight() = default;
		~DirectionalLight() override = default;
	};

	struct PointLight : public Light {
	public:
		vec3 position{};
		LightConstraint info{};

		PointLight(const LightHelper &helper) :
			Light(helper), position(helper.position), info(helper.info) {}

		PointLight() = default;
		~PointLight() override = default;
	};

	struct SpotLight : public Light {
	public:
		vec3 position{}, direction{};
		LightConstraint info{};
		f32 cutoff = 12.5f, outerCutoff = 17.5f;

		SpotLight(const LightHelper &helper) :
			Light(helper), position(helper.position), direction(helper.direction), info(helper.info), cutoff(helper.cutoff), outerCutoff(helper.outerCutoff) {}

		SpotLight() = default;
		~SpotLight() override = default;
	};

	struct RenderComponent : public Component {
	public:
		std::function<void()> draw;

		void setCall(std::function<void()> &&func) { this->draw = std::move(func); }

		void call() {
			this->draw();
		}

		RenderComponent() = default;

		~RenderComponent() override = default;
	};

	struct ShaderComponent : public Component {
	public:
		Unique<ShaderProgram> shader;

		ShaderComponent() = default;

		~ShaderComponent() override = default;
	};

	struct InputComponent : public Component {
	public:
		std::unordered_map<u32, std::function<void()>> callbacks;

		inline void registerAction(const u32 &key, std::function<void()> &&callback) {
			this->callbacks.emplace(key, std::move(callback));
		}

		inline void call(const u32 &key) {
			this->callbacks.at(key)();
		}

		inline std::vector<u32> getAllKeys() const {
			auto kv = std::views::keys(this->callbacks);
			return std::vector<u32>{kv.begin(), kv.end()};
		}

		InputComponent() = default;

		~InputComponent() override = default;
	};

	struct NormalsComponent : public Component {
	public:
		VertexBuffer vbo_n;
		std::vector<vec3> normals{};

		NormalsComponent() = default;

		~NormalsComponent() = default;
	};

	struct Mesh : public Component {
	public:
		VertexArray vao;
		VertexBuffer vbo_g;
		VertexBuffer vbo_t;
		ElementBuffer ebo;

		RenderComponent render{};

		std::vector<vec3> vertices;
		std::vector<u32> indices{};
		Color colorComponent;
		std::vector<vec2> texCoord;

		b8 instanced = false;

		Mesh() = default;

		~Mesh() override = default;
	};

	struct PhysicComponent : public Component {
	public:
		b8 isStatic = false;
		f32 mass = 1.f;
		vec3 velocity = vec3(0);
		vec3 acceleration = vec3(0);
		vec3 force = vec3(0);

		PhysicComponent() = default;

		~PhysicComponent() override = default;
	};
} // namespace bolt
