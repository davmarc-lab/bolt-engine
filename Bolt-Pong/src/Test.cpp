#include "../../Bolt-Core/include/Engine.hpp"
#include "../../Bolt-Core/include/Graphics.hpp"

#include "Collision.hpp"

using namespace bolt;

constexpr auto plongDim = vec3(12, 75, 0);
constexpr auto plongGap = 30;
constexpr auto plongVel = vec3(0, 5, 0);

constexpr auto ballDim = vec3(20, 20, 0);
auto ballPos = vec3(0);
constexpr auto ballVel = vec3(-5, 0, 0);

struct Score {
	u16 first;
	u16 second;
} score;

int main(int argc, char *argv[]) {
	const auto ls = LayerStack::instance();

	WindowProperties properties{};
	properties.maximized = false;
	properties.vsync = true;
	properties.backgroundColor = vec4(0, 0, 0, 1);

	ApplicationSetting settings{};
	settings.type = scene::SCENE_2D;
	settings.name = "Plin Plin Plon";
	settings.dimension = {1600, 900};
	settings.properties = properties;
	settings.enableCollisions = true;

	const auto app = CreateUnique<Application>(settings);

	const auto w = CreateShared<Window>(settings);
	ls->addCustomLayer(w);

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

	ballPos = vec3(settings.dimension.x / 2, settings.dimension.y / 2, 0);
	const auto ball = em->createEntity();
	factory::mesh::createCustomMesh(ball, config::mesh_colors, config::shape_square);
	const auto ballComp = em->getEntityComponent<Transform>(ball);
	ballComp->setPosition(ballPos);
	ballComp->setScale(ballDim);
	scene->addEntity(ball);
	auto ballPhysic = em->addComponent<PhysicComponent>(ball);
	ballPhysic->velocity = ballVel;
	const auto ballCollider = em->addComponent<Collider>(ball);
	ballCollider->type = ColliderType::AABB;
	ballCollider->points = {vec3(-1, -1, -1), vec3(1, 1, 1)};

	EventDispatcher::instance()->subscribe(events::loop::LoopUpdate, [&ballComp, &ballPhysic, &settings](auto p) {
		i32 xpos = static_cast<i32>(ballComp->getPosition().x);
		i32 ypos = static_cast<i32>(ballComp->getPosition().y);
		if (ypos >= settings.dimension.y || ypos <= 0)
			ballPhysic->velocity *= vec3(1, -1, 0);
		ballComp->addPosition(ballPhysic->velocity);

		if (xpos < 0 || xpos > settings.dimension.x) {
			if (xpos < 0) {
				score.second++;
				ballComp->setPosition(ballPos);
			} else if (xpos > settings.dimension.x) {
				score.first++;
				ballComp->setPosition(ballPos);
			}
			std::cout << "Score-> " << score.first << " : " << score.second << "\n";
			if (score.first == 2) {
				std::cout << "First player win!\n";
                EventDispatcher::instance()->post(events::window::WindowCloseEvent);
			} else if (score.second == 2) {
				std::cout << "Second player win!\n";
                EventDispatcher::instance()->post(events::window::WindowCloseEvent);
			}
		}
	});

	EventDispatcher::instance()->subscribe(events::loop::LoopBeforeRender, [](auto ph1) {
		const auto first = bolt::EntityManager::instance()->getEntityComponent<bolt::Transform>(0);
		const auto second = bolt::EntityManager::instance()->getEntityComponent<bolt::Transform>(1);
		const auto ball = bolt::EntityManager::instance()->getEntityComponent<bolt::Transform>(2);

		const auto firstColl = bolt::EntityManager::instance()->getEntityComponent<bolt::Collider>(0);
		const auto secondColl = bolt::EntityManager::instance()->getEntityComponent<bolt::Collider>(1);
		const auto ballColl = bolt::EntityManager::instance()->getEntityComponent<bolt::Collider>(2);

		const auto firstBot = vec3(first->getModelMatrix() * vec4(firstColl->points[0], 1));
		const auto firstTop = vec3(first->getModelMatrix() * vec4(firstColl->points[1], 1));
		const auto secondBot = vec3(second->getModelMatrix() * vec4(secondColl->points[0], 1));
		const auto secondTop = vec3(second->getModelMatrix() * vec4(secondColl->points[1], 1));
		const auto ballBot = vec3(ball->getModelMatrix() * vec4(ballColl->points[0], 1));
		const auto ballTop = vec3(ball->getModelMatrix() * vec4(ballColl->points[1], 1));

		const auto collf = Collision2D({firstBot, firstTop}, {ballBot, ballTop});
		const auto colls = Collision2D({secondBot, secondTop}, {ballBot, ballTop});

		// ball collision with first player
		if (collf.isColliding()) {
			auto vel = bolt::EntityManager::instance()->getEntityComponent<PhysicComponent>(2);
			auto half = (firstTop.y + firstBot.y) / 2;
			if (vel->velocity.x < 0) {
				if (ball->getPosition().y > half) {
					vel->velocity = {-vel->velocity.x, -5, 0};
				} else {
					vel->velocity = {-vel->velocity.x, 5, 0};
				}
			}
			return;
		}

		// ball collision with second player
		if (colls.isColliding()) {
			auto vel = bolt::EntityManager::instance()->getEntityComponent<PhysicComponent>(2);
			auto half = (secondTop.y + secondBot.y) / 2;
			if (vel->velocity.x > 0) {
				if (ball->getPosition().y > half) {
					vel->velocity = {-vel->velocity.x, -5, 0};
				} else {
					vel->velocity = {-vel->velocity.x, 5, 0};
				}
			}
		}
	});

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
