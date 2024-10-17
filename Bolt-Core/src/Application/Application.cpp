#include "../../include/Application/Application.hpp"

#include "../../include/Core/LayerManager.hpp"
#include "../../include/Core/RenderApi.hpp"

#include "../../include/ECS/EntityManager.hpp"
#include "../../include/ECS/System.hpp"

#include "../../include/Graphic/ImGuiLayer.hpp"

#include "../../include/Graphic/Buffer/UniformBuffer.hpp"

#include "../../include/Core/Physics.hpp"

void bolt::Application::run() {
	const auto lm = LayerManager::instance();

	// This window is unique.
	Shared<Window> w = CreateShared<Window>(Window());
	lm->addLayer(w);

	if (Application::isImGuiEnabled()) {
		Shared<ImGuiLayer> ig = CreateShared<ImGuiLayer>(w);
		lm->addLayer(ig);
	}

	using namespace bmath;

	const auto rd = RenderApi::instance();
	rd->init(config::RenderApiConfig::render_opengl);

	auto ed = EventDispatcher::instance();

	EntityManager::instance()->subscribeEventCallbacks();

	lm->addLayersFromStack();

	ed->subscribe(events::loop::LoopUpdate, [](auto &&ph1) { systems::transform::updateAllModelMatrix(); });

	UniformBuffer ub = UniformBuffer();
	ub.onAttach();
	ub.setup(sizeof(mat4), 0);
	ub.update(0, sizeof(mat4), value_ptr(s_projection));
	ed->subscribe(events::shader::ShaderProjectionChanged, [this, &ub](auto &&p) {
		ub.update(0, sizeof(mat4), value_ptr(s_projection));
	});

	Timer::instance()->start();

	// TEST START
	/*
		{
			bmat2 a = bmat2({1, 2}, {3, 4});
			bmat2 b = bmat2({7, 5}, {6, 8});

			auto main = Timer::instance()->getTime();
			for (int i = 0; i < 10; i++) {
				auto start = Timer::instance()->getTime();
				std::cout << dump(a * b) << "\n";
				std::cout << Timer::instance()->getTime() - start << "\n";
			}
			std::cout << "FINAL: " << Timer::instance()->getTime() - main << "\n";

		}

		{
			std::cout << "\n\n\n\n";
			mat2 a = mat2({1, 3}, {2, 4});
			mat2 b = mat2({7, 6}, {5, 8});

			auto main = Timer::instance()->getTime();
			for (int i = 0; i < 10; i++) {
				auto start = Timer::instance()->getTime();
				std::cout << to_string(a * b) << "\n";
				std::cout << Timer::instance()->getTime() - start << "\n";
			}
			std::cout << "FINAL: " << Timer::instance()->getTime() - main << "\n";
		}
	*/
	// auto pw = CreateShared<PhysicsWorld>();
	// lm->addLayer(pw);
	//
	// // using a loop generic event to add entities to the physic world
	// ed->subscribe(events::loop::LoopGeneric, [&pw](auto &&p) {
	// 	pw->addEntity(EntityManager::instance()->getCurrentId() - 1);
	// });

	// TEST END

	while (!w->shouldWindowClose()) {
		auto e = Event();
		lm->execute([e](const Shared<Layer> &l) { l->onEvent(e); });
		lm->execute([](const Shared<Layer> &l) { l->onUpdate(); });

		ed->post(events::loop::LoopUpdate);

		// Before rendering operations
		lm->execute([](const Shared<Layer> &l) { l->begin(); });
		lm->execute([](const Shared<Layer> &l) { l->onRender(); });

		lm->execute([](const Shared<Layer> &l) { l->end(); });
		// After rendering operations
	}
	lm->execute([](const Shared<Layer> &l) { l->onDetach(); });
}
