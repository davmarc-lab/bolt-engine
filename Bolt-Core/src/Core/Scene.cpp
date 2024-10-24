#include "../../include/Core/Scene.hpp"
#include "../../include/Application/Application.hpp"

#include "../../include/ECS/System.hpp"

namespace bolt {
	namespace scene {
		void updatePerspective(const f32& fov, const f32& ratio, const f32& near, const f32& far) {
			Application::setProjectionMatrix(perspective(fov, ratio, near, far));
		}

		void updateOrtho(const f32& left, const f32& right, const f32& bottom, const f32& up) {
			Application::setProjectionMatrix(ortho(left, right, bottom, up));
		}
	} // namespace scene

	void SceneLayer::onAttach() {
		for (auto id : Scene::instance()->getEntities()) {
			if (Application::getSceneType() == scene::SCENE_3D) {
				factory::mesh::initCustomMesh(id, config::cubeConfig, config::shape_cube);
			} else
				factory::mesh::initCustomMesh(id, config::squareConfig, config::shape_square);
		}
        this->m_attached = true;
	}

	void SceneLayer::onRender() {
		systems::render::drawAllMeshes();
	}
} // namespace bolt
