#include <Application/Application.hpp>

#include <Platform/GlfwWindow.hpp>

void Bolt::Application::run() {
	const auto w = GlfwWindow::instance();
	w->init();

	while (!w->shouldWindowClose()) {
		w->onUpdate();
		w->onRender();
	}
	w->destroy();
}
