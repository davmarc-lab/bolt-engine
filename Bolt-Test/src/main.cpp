#include <iostream>
#include <utility>
#include "../../Bolt-Core/include/Engine.hpp"
#include "../../Bolt-Core/include/Graphics.hpp"
#include "../include/ImGuiInfo.hpp"

using namespace bolt;

struct FakeCamera {
	f32 left = 0, right = 0, up = 0, bot = 0;
} cam;

int main(int argc, char *argv[]) {
	std::cout << "Application started\n";

	WindowProperties properties{};
	properties.maximized = false;
	properties.vsync = true;
	properties.backgroundColor = vec4(0.3, 0.3, 0.3, 1);

	ApplicationSetting settings{};
	settings.type = scene::SCENE_2D;
	settings.name = "Bolt Application";
	settings.dimension = {1600, 900};
	settings.properties = properties;
	settings.defaultCameraMovement = true;

	const auto app = CreateUnique<Application>(settings);
	const auto ls = LayerStack::instance();

	const auto w = CreateShared<Window>(settings);
	// it needs to be attached due to UniforBuffer usage
	w->onAttach();
	ls->addCustomLayer(w);

	const auto scene = Scene::instance();
	ls->addCustomLayer(CreateShared<SceneLayer>());

    standardCamera.updateOrthoProjection(0, 1600, 0, 900);
	UniformBuffer ub = UniformBuffer("Matrices");
	ub.onAttach();
	ub.setup(sizeof(mat4), 0);
	auto VP = standardCamera.getViewProjMatrix();
	ub.update(0, sizeof(mat4), value_ptr(VP));
	EventDispatcher::instance()->subscribe(events::shader::ShaderProjectionChanged, [&ub](auto &&p) {
		auto VP = standardCamera.getViewProjMatrix();
		ub.update(0, sizeof(mat4), value_ptr(VP));
	});
	EventDispatcher::instance()->post(events::shader::ShaderProjectionChanged);

	const auto em = EntityManager::instance();
	em->subscribeEventCallbacks();

	MeshHelper helper{};
	helper.renderInfo = {RenderType::render_arrays, GL_TRIANGLES, 0};

	// meshes
	auto elem = em->createEntity();
	helper.vertex = factory::mesh::cubeGeometry;
	helper.colors = factory::mesh::getColorVector(sizeof(helper.vertex), {1, 0, 0, 1});
	helper.normals = factory::mesh::cubeNormals;
	helper.position = {200, 200, 0};
	helper.scale = {100, 100, 0};
	factory::mesh::instanceMesh(elem, helper);
	em->addComponent<Collider>(elem);
	scene->addEntity(elem);

	// lights
	LightHelper lh{};
	lh.color = {1, 0, 0};
	lh.direction = vec4(0, 0, -1, 0);
	lh.type = LightType::LIGHT_DIRECTIONAL;
	lh.caster = true;
	em->createLight(lh);

	Application::enableImGui();
	const auto ig = CreateShared<ImGuiLayer>(w);
	ls->addCustomLayer(ig);

	auto info = CreateShared<ImGuiInfo>();
	ls->addCustomLayer(info);
	ls->addCustomLayer(CreateShared<ImGuiEntityTree>());

	app->run();
	std::cout << "Application closed\n";
}
