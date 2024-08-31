#include <Application/Application.hpp>

#include <Platform/GlfwWindow.hpp>

#include <ImGui/ImGuiLayer.hpp>

void Bolt::Application::run() {
	const auto w = GlfwWindow::instance();
	w->init();

	auto ig = ImGuiLayer();
	ig.onAttach();

	while (!w->shouldWindowClose()) {
		w->onEvent(Event());
		w->onUpdate();
		ig.begin();
		w->onRender();
		ig.end();
	}
	
	ig.onDetach();
	w->destroy();
}
