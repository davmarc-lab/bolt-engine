#include "../../Bolt-Core/include/Engine.hpp"
#include "../../Bolt-Core/include/Graphics.hpp"

#include "../include/MeshParser.hpp"
#include "../include/ImGuiInfo.hpp"
#include "../include/ImGuiConfig.hpp"

#include <iostream>
#include <fstream>

using namespace bolt;

#define WIDTH 1600
#define HEIGHT 900

struct FakeCamera {
	f32 left = 0, right = 0, up = 0, bot = 0;
} cam;

f32 vel = 0.001;

int main(int argc, char *argv[]) {
	std::cout << "Application started\n\n";

	WindowProperties properties{};
	properties.maximized = false;
	properties.vsync = true;
	properties.backgroundColor = vec4(0.3, 0.3, 0.3, 1);
	properties.depth = {true, true, GL_LESS};

	ApplicationSetting settings{};
	settings.type = scene::SCENE_2D;
	settings.name = "Bolt Application";
	settings.dimension = {WIDTH, HEIGHT};
	settings.properties = properties;
	settings.defaultCameraMovement = true;

	const auto app = CreateUnique<Application>(settings);
	const auto ls = LayerStack::instance();

	const auto w = CreateShared<Window>(settings);
	// it needs to be attached due to UniforBuffer usage
	w->onAttach();
	ls->addCustomLayer(w);

	const auto rd = RenderApi::instance();
	rd->init(config::RenderApiConfig::render_opengl);

	const auto scene = Scene::instance();
	ls->addCustomLayer(CreateShared<SceneLayer>());

	standardCamera.updateOrthoProjection(0, WIDTH, 0, HEIGHT);
	UniformBuffer ub = UniformBuffer("Matrices");
	ub.onAttach();
	ub.setup(sizeof(mat4), 0);
	auto VP = standardCamera.getViewProjMatrix();
	ub.update(0, sizeof(mat4), value_ptr(VP));
	EventDispatcher::instance()->subscribe(events::shader::ShaderProjectionChanged, [&ub](auto &&p) {
		auto VP = standardCamera.getViewProjMatrix();
		ub.update(0, sizeof(mat4), value_ptr(VP));
	});
	EventDispatcher::instance()->post(events::shader::ShaderProjectionChanged);

	const auto em = EntityManager::instance();
	em->subscribeEventCallbacks();

	MeshHelper helper{};
	helper.name = "Base";
	helper.renderInfo = {RenderType::render_arrays, GL_TRIANGLES, 0};
	helper.vertex = factory::mesh::squareGeometry;
	helper.colors = factory::mesh::getColorVector(helper.vertex.size(), {1, 0, 0, 1});
	helper.position = {1000, 400, 0};
	helper.scale = {200, 200, 0};
	
	{
		auto id = em->createEntity();
		factory::mesh::instanceMesh(id, helper);
		auto shader = em->addComponent<ShaderComponent>(id);
		shader->shader = CreateUnique<ShaderProgram>("shader/vertexShader.glsl", "shader/fragmentShader.glsl", 0);
		shader->shader->createShaderProgram();
		scene->addEntity(id);
	}

	helper.name = "Eye";
	helper.position = {400, 400, 0};
	helper.colors = factory::mesh::getColorVector(helper.vertex.size(), {0, 1, 0, 1});
	auto id = em->createEntity();
	factory::mesh::instanceMesh(id, helper);
	auto shader = em->addComponent<ShaderComponent>(id);
	shader->shader = CreateUnique<ShaderProgram>("shader/vertexShader.glsl", "shader/fragmentShader.glsl", 0);
	shader->shader->createShaderProgram();
	scene->addEntity(id);

	Application::enableImGui();
	const auto ig = CreateShared<ImGuiLayer>(w);
	ls->addCustomLayer(ig);

	ls->addCustomLayer(CreateShared<ImGuiInfo>());
	ls->addCustomLayer(CreateShared<ImGuiEntityTree>());
	ls->addCustomLayer(CreateShared<ImGuiConfig>());

	EventDispatcher::instance()->subscribe(ReadMeshDataFromFile, [](auto p) {
		MeshParser::readMeshFromFile("config.txt");
	});
	
	EventDispatcher::instance()->subscribe(SaveMeshDataFromFile, [](auto p) {
		MeshParser::saveMeshToFile();
	});

	/*
		rd->getRenderer()->drawCube({0, 0, -4}, {3, 3, 0}, {}, {0, 1, 1, 1});
	
		// STRESS TEST
		EventDispatcher::instance()->subscribe(events::loop::LoopUpdate, [&rd](auto p) {
			rd->getRenderer()->drawCube({vel, 0, -2}, {.1, .1, .1}, {}, {1, 0, 0, 1});
			rd->getRenderer()->drawCube({vel, 0.2, -2}, {.1, .1, .1}, {}, {1, 0, 0, 1});
			rd->getRenderer()->drawCube({vel, 0.4, -2}, {.1, .1, .1}, {}, {1, 0, 0, 1});
			rd->getRenderer()->drawCube({vel, 0.6, -2}, {.1, .1, .1}, {}, {1, 0, 0, 1});
			rd->getRenderer()->drawCube({vel, 0.8, -2}, {.1, .1, .1}, {}, {1, 0, 0, 1});
			rd->getRenderer()->drawCube({vel, 1, -2}, {.1, .1, .1}, {}, {1, 0, 0, 1});
			rd->getRenderer()->drawCube({vel, 1.2, -2}, {.1, .1, .1}, {}, {1, 0, 0, 1});
			rd->getRenderer()->drawCube({vel, 1.4, -2}, {.1, .1, .1}, {}, {1, 0, 0, 1});
			rd->getRenderer()->drawCube({vel, 1.6, -2}, {.1, .1, .1}, {}, {1, 0, 0, 1});
			rd->getRenderer()->drawCube({vel, 1.8, -2}, {.1, .1, .1}, {}, {1, 0, 0, 1});
			rd->getRenderer()->drawCube({vel, 2, -2}, {.1, .1, .1}, {}, {1, 0, 0, 1});
			vel += 0.001f;
		});
	
		for (int i = 0; i < 32; i++) {
			for (int j = 0; j < 18; j++) {
				rd->getRenderer()->drawCube({(i * .3) + .25, (j * .3) + 0.25, 0}, {.1, .1, .1}, {}, {0, 0, 1, 1});
			}
		}
	*/

	app->run();
	std::cout << "\nApplication closed\n";
}
