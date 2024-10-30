#include "../../Bolt-Core/include/Engine.hpp"
#include "../../Bolt-Core/include/Graphics.hpp"
#include "../../Bolt-Core/include/Graphic/Text/TextManager.hpp"

using namespace bolt;

int main(int argc, char *argv[]) {
	std::cout << "Application started\n";

	WindowProperties properties{};
	properties.maximized = false;
	properties.vsync = true;
	properties.backgroundColor = vec4(0.3, 0.3, 0.3, 1);
	properties.cull = {true, GL_BACK};
	properties.depth = {true, true, GL_LESS};

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

	UniformBuffer ub = UniformBuffer();
	ub.onAttach();
	ub.setup(sizeof(mat4), 0);
	auto proj = Application::getProjectionMatrix();
	ub.update(0, sizeof(mat4), value_ptr(proj));
	EventDispatcher::instance()->subscribe(events::shader::ShaderProjectionChanged, [&proj, &ub](auto &&p) {
		ub.update(0, sizeof(mat4), value_ptr(proj));
	});

	EntityManager::instance()->subscribeEventCallbacks();

    auto tm = CreateShared<TextManager>();
    ls->addCustomLayer(tm);
    tm->onAttach();

    auto helper = TextHelper{};
    helper.text = "Hello";
    helper.position = {100, 100};
    helper.scale = 1.f;
    helper.color = vec3(1, 0, 0);
    auto t = Text(helper);

    tm->addText(t);

    Application::enableImGui();
    const auto ig = CreateShared<ImGuiLayer>(w);
    ls->addCustomLayer(ig);
    
    ls->addCustomLayer(CreateShared<ImGuiDockSpace>());
    ls->addCustomLayer(CreateShared<ImGuiEntityTree>());
    ls->addCustomLayer(CreateShared<ImGuiViewPort>());
    ls->addCustomLayer(CreateShared<ImGuiUtility>());
    ls->addCustomLayer(CreateShared<ImGuiProperties>());

	app->run();
	std::cout << "Application closed\n";
}
