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
	std::cout << "Application started\n\n";

	WindowProperties properties{};
	properties.maximized = false;
	properties.vsync = true;
	properties.backgroundColor = vec4(0.3, 0.3, 0.3, 1);
	properties.depth = {true, true, GL_LESS};
	properties.cull = {true, GL_BACK};

	ApplicationSetting settings{};
	settings.type = scene::SCENE_3D;
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

	const auto rd = RenderApi::instance();
	rd->init(config::RenderApiConfig::render_opengl);

	const auto scene = Scene::instance();
	ls->addCustomLayer(CreateShared<SceneLayer>());

	standardCamera.updatePerspProjection(standardCamera.getCameraZoom(), 1600, 900, 0.1f, 100.f);
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
	// auto elem = em->createEntity();
	// helper.vertex = factory::mesh::cubeGeometry;
	// helper.colors = factory::mesh::getColorVector(sizeof(helper.vertex), {1, 0, 0, 1});
	// helper.normals = factory::mesh::cubeNormals;
	// helper.position = {0, 0, -1};
	// helper.scale = {1, 1, 1};
	// factory::mesh::instanceMesh(elem, helper);
	// em->addComponent<Collider>(elem);
	// scene->addEntity(elem);

	// lights
	LightHelper lh{};
	lh.color = {1, 0, 0};
	lh.position = {1, 1, 1};
	lh.type = LightType::LIGHT_POINT;
	lh.caster = true;
	em->createLight(lh);

	// PrimitiveManager::init();
	// auto cube = PrimitiveManager::addCubePrimitive({0, 0, 0}, {1, 1, 1}, {}, {1, 0, 0, 1});
	// {
	// 	auto mesh = em->getEntityComponent<Mesh>(cube);
	// 	// mesh->colorComponent.colors = factory::mesh::getColorVector(mesh->colorComponent.colors.size(), {1, 0, 0, 1});
	// }

	Application::enableImGui();
	const auto ig = CreateShared<ImGuiLayer>(w);
	ls->addCustomLayer(ig);

	auto info = CreateShared<ImGuiInfo>();
	ls->addCustomLayer(info);
	ls->addCustomLayer(CreateShared<ImGuiEntityTree>());

	app->run();
	std::cout << "\nApplication closed\n";
}
