//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif

#include "../../Bolt-Core/include/Engine.hpp"

#include "../../Bolt-Core/include/Platform/ImGuiFactory.hpp"
#include "../../Bolt-Core/include/Platform/MeshFactory.hpp"

int main(int argc, char* argv[]) {
	auto app = CreateUnique<bolt::Application>();
	auto ls = bolt::LayerStack::instance();

	bolt::EntityManager::instance()->createEntity();
	bolt::factory::mesh::createEmptyCubeMesh(0, {}, bolt::vec4(1));
	bolt::Scene::instance()->addEntity(0);

    auto c = bolt::EntityManager::instance()->getEntityComponent<bolt::Transform>(0);
    c->setPosition(bolt::vec3(0.8));
    c->setScale(bolt::vec3(0.5));

	//bolt::Application::enableImGui();

	//ls->addCustomLayer(CreateShared<bolt::ImGuiDockSpace>());
	//ls->addCustomLayer(CreateShared<bolt::ImGuiEntityTree>());
	//ls->addCustomLayer(CreateShared<bolt::ImGuiViewPort>());
	//ls->addCustomLayer(CreateShared<bolt::ImGuiUtility>());
	//ls->addCustomLayer(CreateShared<bolt::ImGuiProperties>());

	app->run();
}
