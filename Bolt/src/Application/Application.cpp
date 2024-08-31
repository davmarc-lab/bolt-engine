#include <Application/Application.hpp>

#include <Platform/GlfwWindow.hpp>
#include <Platform/ImGuiLayer.hpp>
#include <Core/LayerManager.hpp>

void Bolt::Application::run() {
	const auto lm = LayerManager::instance();
	
	const auto w = GlfwWindow::instance();
	lm->addLayer(w);

	const auto ig = std::make_shared<ImGuiLayer>();
	lm->addLayer(ig);

	lm->execute([](const std::shared_ptr<Layer>& l) { l->onAttach(); });

	while (!w->shouldWindowClose()) {
		auto e = Event("BLABLA");
		lm->execute([&e](const std::shared_ptr<Layer>& l) { l->onEvent(e); });
		
		lm->execute([](const std::shared_ptr<Layer>& l) { l->onUpdate(); });
		
		ig->begin();
		lm->execute([](const std::shared_ptr<Layer>& l) { l->onRender(); });
		ig->end();
	}
	lm->execute([](const std::shared_ptr<Layer>& l) { l->onDetach(); });
}
