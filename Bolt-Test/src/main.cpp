#include <utility>
#include "../../Bolt-Core/include/Engine.hpp"
#include "../../Bolt-Core/include/Graphics.hpp"
#include "../include/ImGuiInfo.hpp"

using namespace bolt;

int main(int argc, char *argv[]) {
	std::cout << "Application started\n";

	WindowProperties properties{};
	properties.maximized = false;
	properties.vsync = true;
	properties.backgroundColor = vec4(0.3, 0.3, 0.3, 1);
	properties.depth = {true, true, GL_LESS};
	properties.cull = {true, GL_BACK};
	properties.projection = CreateShared<InfoPersp>(45.f, 1600, 900, 0.1, 100);

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

	const auto scene = Scene::instance();
	ls->addCustomLayer(CreateShared<SceneLayer>());

	UniformBuffer ub = UniformBuffer("Matrices");
	ub.onAttach();
	ub.setup(sizeof(mat4), 0);
	auto proj = Application::getProjectionMatrix();
	ub.update(0, sizeof(mat4), value_ptr(proj));
	EventDispatcher::instance()->subscribe(events::shader::ShaderProjectionChanged, [&ub](auto &&p) {
        auto proj = Application::getProjectionMatrix();
		ub.update(0, sizeof(mat4), value_ptr(proj));
	});
    EventDispatcher::instance()->post(events::shader::ShaderProjectionChanged);

    UniformBuffer lights = UniformBuffer("Lights");
    lights.onAttach();
    lights.setup(sizeof(ShaderLightBlock), 1);
    ShaderLightBlock slb{};
    lights.update(0, sizeof(ShaderLightBlock), &slb);

	const auto em = EntityManager::instance();
	em->subscribeEventCallbacks();

	MeshHelper helper{};
	helper.renderInfo = {RenderType::render_arrays, GL_TRIANGLE_FAN, 0};

    // meshes
    auto elem = em->createEntity();
	auto vec = factory::mesh::getCircleVertices({0, 0}, {1, 1}, 50);
	helper.vertex = std::move(vec.vertices);
	helper.colors = std::move(vec.colors);
	helper.position = {0, 0, 0};
	helper.scale = {1, 1, 0};
	factory::mesh::instanceMesh(elem, helper);
	em->addComponent<Collider>(elem);
	scene->addEntity(elem);

    // lights
    auto l = em->createEntity();
    auto light = em->addComponent<SpotLight>(l);

	Application::enableImGui();
	const auto ig = CreateShared<ImGuiLayer>(w);
	ls->addCustomLayer(ig);

    auto info = CreateShared<ImGuiInfo>();
    ls->addCustomLayer(info);

	app->run();
	std::cout << "Application closed\n";
}
