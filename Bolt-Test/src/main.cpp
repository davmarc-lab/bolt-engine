#include "../../Bolt-Core/include/Engine.hpp"
#include "../../Bolt-Core/include/Graphics.hpp"

using namespace bolt;

int main(int argc, char *argv[]) {
	WindowProperties properties{};
	properties.maximized = false;
	properties.vsync = true;
	properties.backgroundColor = vec4(0.3, 0.3, 0.3, 1);
    properties.cull = {true, GL_BACK};
    properties.depth = {true, true, GL_LESS};

	ApplicationSetting settings{};
	settings.type = scene::SCENE_3D;
	settings.name = "Testing";
	settings.dimension = {1600, 900};
	settings.properties = properties;
    settings.defaultCameraMovement = true;

	const auto app = CreateUnique<Application>(settings);
	const auto ls = LayerStack::instance();

	const auto w = CreateShared<Window>(settings);
	ls->addCustomLayer(w);

    Application::enableImGui();
    const auto ig = CreateShared<ImGuiLayer>(w);
    ls->addCustomLayer(ig);

	const auto scene = Scene::instance();
	ls->addCustomLayer(CreateShared<SceneLayer>());

	ls->addCustomLayer(CreateShared<ImGuiDockSpace>());
	ls->addCustomLayer(CreateShared<ImGuiEntityTree>());
	ls->addCustomLayer(CreateShared<ImGuiViewPort>());
	ls->addCustomLayer(CreateShared<ImGuiUtility>());
	ls->addCustomLayer(CreateShared<ImGuiProperties>());

	app->run();
}

