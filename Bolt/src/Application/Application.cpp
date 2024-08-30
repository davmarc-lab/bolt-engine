#include <Application/Application.hpp>

#include <iostream>

#include <Platform/GlfwWindow.hpp>

void Bolt::Application::run() {
	auto w = GlfwWindow::instance();

	while(!w->shouldWindowClose()) {
		w->onUpdate();
		w->onRender();
	}
	w->destroy();
}
