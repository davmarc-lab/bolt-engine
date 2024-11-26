#pragma once

#include <memory>
#include "../Core/Scene.hpp"
#include "../Core/Structs.hpp"

namespace bolt {
	struct CullFace {
		b8 enabled = false;
		u32 mode = 0;
	};

	struct DepthTest {
		b8 enabled = false;
		b8 mask = true;
		u32 func = 0;
	};

	enum ProjectionType {
		PROJ_AUTO,
		PROJ_ORTHO,
		PROJ_PERSP
	};

	struct Projection {
	public:
		inline ProjectionType getType() const { return this->m_type; }

		virtual mat4 getMatrix() { return mat4(0); }

		Projection() :
			m_type(ProjectionType::PROJ_AUTO) {}

		Projection(const ProjectionType &type) :
			m_type(type) {}

		mat4 m_matrix{};
		b8 m_dirty = true;
		ProjectionType m_type = ProjectionType::PROJ_AUTO;
	};

	struct InfoOrtho : Projection {
	public:
		inline virtual mat4 getMatrix() override {
			if (this->m_dirty) {
				this->m_dirty = false;
				this->generateMatrix();
			}
			return this->m_matrix;
		}

		inline f32 getLeft() { return this->left; }
		inline void setLeft(const f32 &val) {
			if (this->left == val)
				return;
			this->m_dirty = true;
			this->left = val;
		}
		inline f32 getRight() { return this->right; }
		inline void setRight(const f32 &val) {
			if (this->right == val)
				return;
			this->m_dirty = true;
			this->right = val;
		}
		inline f32 getBottom() { return this->bottom; }
		inline void setBottom(const f32 &val) {
			if (this->bottom == val)
				return;
			this->m_dirty = true;
			this->bottom = val;
		}
		inline f32 getUp() { return this->up; }
		inline void setUp(const f32 &val) {
			if (this->up == val)
				return;
			this->m_dirty = true;
			this->up = val;
		}

		InfoOrtho() = delete;
		InfoOrtho(const f32 &left, const f32 &right, const f32 &bottom, const f32 &up) :
			Projection(ProjectionType::PROJ_ORTHO), left(left), right(right), bottom(bottom), up(up) {}
		~InfoOrtho() = default;

	private:
		f32 left{}, right{}, bottom{}, up{};

		inline void generateMatrix() {
			this->m_matrix = ortho(this->left, this->right, this->bottom, this->up);
		}
	};

	struct InfoPersp : Projection {
	public:
		inline f32 getFov() { return this->fov; }
		inline void setFov(const f32 &val) {
			if (this->fov == val)
				return;
			this->m_dirty = true;
			this->fov = val;
		}
		inline f32 getWidth() { return this->width; }
		inline void setWidth(const f32 &val) {
			if (this->width == val)
				return;
			this->m_dirty = true;
			this->width = val;
		}
		inline f32 getHeight() { return this->height; }
		inline void setHeight(const f32 &val) {
			if (this->height == val)
				return;
			this->m_dirty = true;
			this->height = val;
		}
		inline f32 getNear() { return this->near; }
		inline void setNear(const f32 &val) {
			if (this->near == val)
				return;
			this->m_dirty = true;
			this->near = val;
		}
		inline f32 getFar() { return this->far; }
		inline void setFar(const f32 &val) {
			if (this->far == val)
				return;
			this->m_dirty = true;
			this->far = val;
		}

		inline virtual mat4 getMatrix() override {
			if (this->m_dirty) {
				this->m_dirty = false;
				this->generateMatrix();
			}
			return this->m_matrix;
		}

		InfoPersp() = delete;
		InfoPersp(const f32 &fov, const f32 &width, const f32 &height, const f32 &near, const f32 &far) :
			Projection(ProjectionType::PROJ_PERSP), fov(fov), width(width), height(height), near(near), far(far) {}
		~InfoPersp() = default;

	private:
		f32 fov{}, width{}, height{}, near{}, far{};

		inline void generateMatrix() {
			this->m_matrix = perspective(this->fov, this->width / this->height, this->near, this->far);
		}
	};

	struct WindowProperties {
		b8 maximized = false;
		b8 vsync = false;
		vec4 backgroundColor = vec4(0.3f, 0.3f, 0.3f, 1.0f);
		CullFace cull = {};
		DepthTest depth = {};
		Shared<Projection> projection = CreateShared<Projection>();
	};

	struct ApplicationSetting {
		scene::SceneType type;
		std::string name = "Bolt App";
		Pair<u16> dimension = {1600, 900};
		Pair<u16> position = {};
		WindowProperties properties{};
		b8 defaultCameraMovement = false;
	};

	/*
	 * Basic entry point to use the engine.
	 */
	class Application {
	private:
		inline static b8 s_enableImGui = false;

		inline static b8 s_close = false;

		inline static ApplicationSetting s_settings{};

		inline static mat4 s_textProjection{};

	public:
		Application() :
			Application({scene::SceneType::SCENE_3D}) {}

		Application(const ApplicationSetting &settings) {
			s_settings = settings;
		}

		/*
		 * Starts the aplication, and enters in the loop.
		 */
		void run();

		inline static void enableImGui() { s_enableImGui = true; }

		inline static bool isImGuiEnabled() { return s_enableImGui; }

		inline static scene::SceneType getSceneType() { return s_settings.type; }

		inline static Shared<Projection> getProjection() { return s_settings.properties.projection; }

		inline static mat4 getProjectionMatrix() {
			switch (s_settings.properties.projection->getType()) {
				case PROJ_ORTHO: {
					return std::static_pointer_cast<InfoOrtho>(s_settings.properties.projection)->getMatrix();
					break;
				}
				case PROJ_PERSP: {
					return std::static_pointer_cast<InfoPersp>(s_settings.properties.projection)->getMatrix();
					break;
				}
				default:
                    return mat4(0);
					break;
			}
		}

		inline static mat4 getTextProjMatrix() { return s_textProjection; }

		inline static void setTextProjMatrix(const mat4 &proj) { s_textProjection = proj; }

		inline void closeApplication() { s_close = true; }

		inline b8 shouldClose() const { return s_close; }

		~Application() = default;
	};
} // namespace bolt
