#include "Application.hpp"

#include "../Core/LayerManager.hpp"
#include "../Graphic/ImGui/ImGuiFactory.hpp"

#include "../ECS/EntityManager.hpp"
#include "../ECS/System.hpp"

#include "../Platform/MeshFactory.hpp"

#include <iostream>

void Bolt::Application::run() {
	class Foo {
	public:
		Foo() = default;

		void handle(Bolt::Event e) {
			systems::transform::updateEntityPosition(0, vec3(1, 0, 0));
		}
	};

	const auto lm = LayerManager::instance();

	// This window is unique.
	const auto w = GlfwWindow::instance();
	lm->addLayer(w);

	auto ed = EventDispatcher::instance();
	auto f = Foo();

	ed->subscribe(events::Update, [&f](auto &&ph1) { f.handle(ph1); });
	ed->post(events::input::KeyPressedEvent);

	EntityManager::instance()->createEntity();
	EntityManager::instance()->addComponent<Transform>(0);
	EntityManager::instance()->addComponent<Mesh>(0);

	factory::mesh::createEmptyCubeMesh(0);

	for (auto e : EntityManager::instance()->getEntitiesFromComponent<Transform>()) {
		systems::transform::updateEntityPosition(e, vec3(1, 0, 0));
	}

	for (auto e : EntityManager::instance()->getEntitiesFromComponent<Transform>()) {
		std::cout << to_string(EntityManager::instance()->getEntityComponent<Transform>(e)->position) << std::endl;
	}

	// Creates ImGui context and create the basic UI
	ImGuiFactory::createBasicUi();

	while (!w->shouldWindowClose()) {
		auto e = Event();
		lm->execute([e](const std::shared_ptr<Layer> &l) { l->onEvent(e); });

		lm->execute([](const std::shared_ptr<Layer> &l) { l->onUpdate(); });

		// Before rendering operations
		lm->execute([](const std::shared_ptr<Layer> &l) { l->begin(); });
		lm->execute([](const std::shared_ptr<Layer> &l) { l->onRender(); });
		lm->execute([](const std::shared_ptr<Layer> &l) { l->end(); });
		// After rendering operations
	}
	lm->execute([](const std::shared_ptr<Layer> &l) { l->onDetach(); });
}
