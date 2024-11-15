#include <utility>
#include "../../Bolt-Core/include/Engine.hpp"
#include "../../Bolt-Core/include/Graphic/Text/TextManager.hpp"
#include "../../Bolt-Core/include/Graphics.hpp"

using namespace bolt;

int main(int argc, char *argv[]) {
	std::cout << "Application started\n";

	WindowProperties properties{};
	properties.maximized = false;
	properties.vsync = true;
	properties.backgroundColor = vec4(0.3, 0.3, 0.3, 1);
	properties.depth = {true, true, GL_LESS};

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

	UniformBuffer ub = UniformBuffer();
	ub.onAttach();
	ub.setup(sizeof(mat4), 0);
	auto proj = Application::getProjectionMatrix();
	ub.update(0, sizeof(mat4), value_ptr(proj));
	EventDispatcher::instance()->subscribe(events::shader::ShaderProjectionChanged, [&proj, &ub](auto &&p) {
		ub.update(0, sizeof(mat4), value_ptr(proj));
	});

	const auto em = EntityManager::instance();
	em->subscribeEventCallbacks();

	auto elem = em->createEntity();
	MeshHelper helper{};
	helper.renderInfo = {RenderType::render_arrays, GL_TRIANGLE_FAN, 0};
	auto vec =  factory::mesh::getCircleVertices({0, 0}, {1, 1}, 50);
    helper.vertex = std::move(vec.vertices);
    helper.colors = std::move(vec.colors);
	helper.position = {200, 600, 0};
	helper.scale = {20, 20, 0};
	factory::mesh::instanceMesh(elem, helper);
	em->addComponent<PhysicComponent>(elem);
	em->addComponent<Collider>(elem);
	scene->addEntity(elem);

	const auto pw = CreateShared<PhysicsWorld>();
	ls->addCustomLayer(pw);

	// Application::enableImGui();
	// const auto ig = CreateShared<ImGuiLayer>(w);
	// ls->addCustomLayer(ig);
	//
	// ls->addCustomLayer(CreateShared<ImGuiDockSpace>());
	// ls->addCustomLayer(CreateShared<ImGuiEntityTree>());
	// ls->addCustomLayer(CreateShared<ImGuiViewPort>());
	// ls->addCustomLayer(CreateShared<ImGuiUtility>());
	// ls->addCustomLayer(CreateShared<ImGuiProperties>());

	app->run();
	std::cout << "Application closed\n";
}
