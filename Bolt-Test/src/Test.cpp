#include "../../Bolt-Core/include/Engine.hpp"
#include "../../Bolt-Core/include/Graphics.hpp"

#include "Collision.hpp"

using namespace bolt;

constexpr auto plongDim = vec3(12, 75, 0);
constexpr auto plongGap = 30;
constexpr auto plongVel = vec3(0, 5, 0);

constexpr auto ballDim = vec3(20, 20, 0);

int main(int argc, char *argv[]) {
	WindowProperties properties{};
	properties.maximized = false;
	properties.vsync = true;
	properties.backgroundColor = vec4(0, 0, 0, 1);

	ApplicationSetting settings{};
	settings.type = scene::SCENE_2D;
	settings.name = "Plin Plin Plon";
	settings.dimension = {1600, 900};
	settings.baseWindowProperties = properties;

	const auto app = CreateUnique<Application>(settings);

	const auto ls = LayerStack::instance();
	const auto em = EntityManager::instance();
	const auto scene = Scene::instance();

	ls->addCustomLayer(CreateShared<SceneLayer>());

	const auto first = em->createEntity();
	factory::mesh::createCustomMesh(first, config::mesh_colors, config::shape_square);
	const auto comp = em->getEntityComponent<Transform>(first);
	comp->setPosition(vec3(plongGap, settings.dimension.y / 2, 0));
	comp->setScale(plongDim);
	scene->addEntity(first);
	em->addComponent<PhysicComponent>(first);
	const auto colliderFirst = em->addComponent<Collider>(first);
	colliderFirst->type = ColliderType::AABB;
	colliderFirst->points = {vec3(-1, -1, -1), vec3(1, 1, 1)};
	const auto firstInput = em->addComponent<InputComponent>(first);

	firstInput->registerAction(GLFW_KEY_W, [&comp]() {
		comp->addPosition(plongVel);
	});
	firstInput->registerAction(GLFW_KEY_S, [&comp]() {
		comp->addPosition(-plongVel);
	});

	firstInput->registerAction(GLFW_KEY_D, [&comp]() {
		comp->addPosition(vec3(5, 0, 0));
	});
	firstInput->registerAction(GLFW_KEY_A, [&comp]() {
		comp->addPosition(vec3(-5, 0, 0));
	});

	const auto second = em->createEntity();
	factory::mesh::createCustomMesh(second, config::mesh_colors, config::shape_square);
	const auto other = em->getEntityComponent<Transform>(second);
	other->setPosition(vec3(settings.dimension.x - plongGap, settings.dimension.y / 2, 0));
	other->setScale(plongDim);
	scene->addEntity(second);
	em->addComponent<PhysicComponent>(second);
	const auto colliderSecond = em->addComponent<Collider>(second);
	colliderSecond->type = ColliderType::AABB;
	colliderSecond->points = {vec3(-1, -1, -1), vec3(1, 1, 1)};
	const auto secondInput = em->addComponent<InputComponent>(second);

	secondInput->registerAction(GLFW_KEY_UP, [&other]() {
		other->addPosition(plongVel);
	});
	secondInput->registerAction(GLFW_KEY_DOWN, [&other]() {
		other->addPosition(-plongVel);
	});

	const auto ball = em->createEntity();
	factory::mesh::createCustomMesh(ball, config::mesh_colors, config::shape_square);
	const auto ballComp = em->getEntityComponent<Transform>(ball);
	ballComp->setPosition(vec3(settings.dimension.x / 2, settings.dimension.y / 2, 0));
	ballComp->setScale(ballDim);
	scene->addEntity(ball);
	em->addComponent<PhysicComponent>(ball);

	// EventDispatcher::instance()->subscribe(events::loop::LoopGeneric, [](auto ph1) {
	// 	auto first = bolt::EntityManager::instance()->getEntityComponent<bolt::Transform>(0);
	// 	auto ball = bolt::EntityManager::instance()->getEntityComponent<bolt::Transform>(2);
	//
	// 	auto firstColl = bolt::EntityManager::instance()->getEntityComponent<bolt::Collider>(0);
	// 	auto ballColl = bolt::EntityManager::instance()->getEntityComponent<bolt::Collider>(2);
	//
	// 	auto coll = Collision2D({first->getPosition() * firstColl->points[0], first->getPosition() * firstColl->points[1]},
	// 	                        {ball->getPosition() * ballColl->points[0], ball->getPosition() * ballColl->points[1]});
	//
	// 	std::cout << coll.isColliding() << "\n";
	// });

	if constexpr (false) {
		Application::enableImGui();
		ls->addCustomLayer(CreateShared<ImGuiDockSpace>());
		ls->addCustomLayer(CreateShared<ImGuiEntityTree>());
		ls->addCustomLayer(CreateShared<ImGuiViewPort>());
		ls->addCustomLayer(CreateShared<ImGuiUtility>());
		ls->addCustomLayer(CreateShared<ImGuiProperties>());
	}

	app->run();
}
