#include "../../Bolt-Core/include/Engine.hpp"

#include "../../Bolt-Core/include/Platform/ImGuiFactory.hpp"
#include "../../Bolt-Core/include/Platform/MeshFactory.hpp"

int main(int argc, char* argv[]) {
	auto app = CreateUnique<bolt::Application>(bolt::ApplicationSetting{bolt::scene::SCENE_2D});
	auto ls = bolt::LayerStack::instance();

	ls->addCustomLayer(CreateShared<bolt::SceneLayer>());
	
	bolt::Application::enableImGui();
	ls->addCustomLayer(CreateShared<bolt::ImGuiDockSpace>());
	ls->addCustomLayer(CreateShared<bolt::ImGuiEntityTree>());
	ls->addCustomLayer(CreateShared<bolt::ImGuiViewPort>());
	ls->addCustomLayer(CreateShared<bolt::ImGuiUtility>());
	ls->addCustomLayer(CreateShared<bolt::ImGuiProperties>());

	app->run();
}
