#include "Application.hpp"

#include "../Core/LayerManager.hpp"
#include "../Graphic/ImGui/ImGuiFactory.hpp"

#include "../ECS/EntityManager.hpp"

#include <iostream>

#include "../ECS/Transform.hpp"

void Bolt::Application::run() {
	const auto lm = LayerManager::instance();

	// This window is unique.
	const auto w = GlfwWindow::instance();
	lm->addLayer(w);

	EntityManager::instance()->createEntity();
	EntityManager::instance()->createEntity();
	std::cout << EntityManager::instance()->addComponent(0, ecs::Components::transform) << "\n";
	std::cout << EntityManager::instance()->addComponent(1, {ecs::Components::transform, ecs::Components::render}) << "\n";

	// Creates ImGui context and create the basic UI
	ImGuiFactory::createBasicUi();

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
