#include "../../include/Application/Application.hpp"

#include "../../include/Core/LayerManager.hpp"
#include "../../include/Core/RenderApi.hpp"

#include "../../include/Platform/ImGuiFactory.hpp"

#include "../../include/Core/Scene.hpp"
#include "../../include/ECS/EntityManager.hpp"
#include "../../include/ECS/System.hpp"

#include "../../include/Graphic/ImGuiLayer.hpp"
#include "../../include/Platform/MeshFactory.hpp"

#include "../../include/Graphic/Camera/Camera.hpp"
#include "../../include/Graphic/Buffer/UniformBuffer.hpp"

#include <iostream>

void bolt::Application::run() {
	const auto lm = LayerManager::instance();

	scene::perspectiveProjection = perspective(45.0f, 1 / 1.0f, 0.1f, 100.f);
	scene::orthoProjection = ortho(0, 1, 0, 1);

	// This window is unique.
	Shared<Window> w = CreateShared<Window>(Window());
	lm->addLayer(w);

	if (Application::isImGuiEnabled()) {
		Shared<ImGuiLayer> ig = CreateShared<ImGuiLayer>(w);
		lm->addLayer(ig);
	}

	const auto rd = RenderApi::instance();
	rd->init(config::RenderApiConfig::render_opengl);

	auto ed = EventDispatcher::instance();

	EntityManager::instance()->subscribeEventCallbacks();

	lm->addLayersFromStack();

	ed->subscribe(events::loop::LoopUpdate, [](auto &&ph1) { systems::transform::updateAllModelMatrix(); });
	auto c = bolt::EntityManager::instance()->getEntityComponent<bolt::Transform>(0);

	while (!w->shouldWindowClose()) {
		auto e = Event();
		lm->execute([e](const Shared<Layer> &l) { l->onEvent(e); });
		lm->execute([](const Shared<Layer> &l) { l->onUpdate(); });

		// Before rendering operations
		lm->execute([](const Shared<Layer> &l) { l->begin(); });
		lm->execute([](const Shared<Layer> &l) { l->onRender(); });
		lm->execute([](const Shared<Layer> &l) { l->end(); });
		// After rendering operations

		ed->post(events::loop::LoopUpdate);
	}
	lm->execute([](const Shared<Layer> &l) { l->onDetach(); });
}
