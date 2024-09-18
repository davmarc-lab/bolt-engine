#include "Application.hpp"

#include "../Core/LayerManager.hpp"
#include "../Core/RenderApi.hpp"
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
			std::cout << to_string(EntityManager::instance()->getEntityComponent<Transform>(0)->position) << std::endl;
		}
	};

	const auto lm = LayerManager::instance();

	// This window is unique.
	Shared<GlfwWindow> w = CreateShared<GlfwWindow>(GlfwWindow());
	lm->addLayer(w);

	const auto rd = RenderApi::instance();
	rd->init(config::RenderApiConfig::render_opengl);

	auto ed = EventDispatcher::instance();
	auto f = Foo();

	ed->subscribe(events::Update, [&f](auto &&ph1) { f.handle(ph1); });

	EntityManager::instance()->createEntity();

	factory::mesh::createEmptyCubeMesh(0);

    auto mesh = EntityManager::instance()->getEntityComponent<Mesh>(0);

	// Creates ImGui context and create the basic UI
	ImGuiFactory::createBasicUi(w);

	while (!w->shouldWindowClose()) {
		auto e = Event();
		lm->execute([e](const Shared<Layer> &l) { l->onEvent(e); });

		lm->execute([](const Shared<Layer> &l) { l->onUpdate(); });

		// Before rendering operations
		lm->execute([](const Shared<Layer> &l) { l->begin(); });
        lm->execute([](const Shared<Layer> &l) { l->onRender(); });
		// systems::render::drawElement(0);
		lm->execute([](const Shared<Layer> &l) { l->end(); });

		// After rendering operations
	}
	lm->execute([](const Shared<Layer> &l) { l->onDetach(); });
}
