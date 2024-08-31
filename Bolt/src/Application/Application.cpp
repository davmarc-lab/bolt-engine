#include <iostream>
#include <Application/Application.hpp>

#include <Platform/GlfwWindow.hpp>
#include <Platform/ImGuiLayer.hpp>
#include <Core/LayerManager.hpp>

#include <Graphic/ImGui/ImGuiWorkspace.hpp>

void Bolt::Application::run() {
	const auto lm = LayerManager::instance();

	// This window is unique.
	const auto w = GlfwWindow::instance();
	lm->addLayer(w);

	// Create a factory for ImGuiLayers
	const auto ig = std::make_shared<ImGuiLayer>();
	lm->addLayer(ig);
	const auto ds = std::make_shared<ImGuiDockSpace>();
	lm->addLayer(ds);

	lm->execute([](const std::shared_ptr<Layer>& l) { l->onAttach(); });

	while (!w->shouldWindowClose()) {
		auto e = Event();
		lm->execute([e](const std::shared_ptr<Layer>& l) { l->onEvent(e); });
		
		lm->execute([](const std::shared_ptr<Layer>& l) { l->onUpdate(); });
		
		// Before rendering operations
		lm->execute([](const std::shared_ptr<Layer>& l) { l->begin(); });
		lm->execute([](const std::shared_ptr<Layer>& l) { l->onRender(); });
		// After rendering operations
		lm->execute([](const std::shared_ptr<Layer>& l) { l->end(); });
	}
	lm->execute([](const std::shared_ptr<Layer>& l) { l->onDetach(); });
}
