#include "../../Bolt-Core/include/Engine.hpp"
#include "../../Bolt-Core/include/Graphics.hpp"

#include "../include/HermiteFactory.hpp"

#include <GL/gl.h>
#include <iostream>

using namespace bolt;

#define WIDTH 900
#define HEIGHT 900

std::vector<vec3> linePoints{
	{0, -1, 0},
	{0, 1, 0},
	{-1, 0, 0},
	{1, 0, 0},
};
std::vector<vec4> lineColors{
	{0, 0, 0, 1},
	{0, 0, 0, 1},
	{0, 0, 0, 1},
	{0, 0, 0, 1},
};

int main(int argc, char *argv[]) {
	std::cout << "Application started\n";

	WindowProperties properties{};
	properties.maximized = false;
	properties.vsync = true;
	properties.backgroundColor = vec4(0.3, 0.3, 0.3, 1);
	properties.depth = {true, true, GL_LESS};

	ApplicationSetting settings{};
	settings.type = scene::SCENE_2D;
	settings.name = "Bolt Kart";
	settings.dimension = {WIDTH, HEIGHT};
	settings.properties = properties;

	const auto app = CreateUnique<Application>(settings);
	const auto ls = LayerStack::instance();

	const auto w = CreateShared<Window>(settings);
	// it needs to be attached due to UniforBuffer usage
	w->onAttach();
	ls->addCustomLayer(w);

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

	{
		auto axis = em->createEntity();
		auto m = em->addComponent<Mesh>(axis);
		m->vertices = linePoints;
		m->colorComponent.colors = lineColors;

		m->vao.onAttach();
		m->vao.bind();
		m->vbo_g.onAttach();
		m->vbo_g.setup(m->vertices, 0);
		m->vao.linkAttribFast(SHADER_VERTEX_LOCATION, 3, GL_FLOAT, false, 0, (void *)0);

		m->colorComponent.vbo_c.onAttach();
		m->colorComponent.vbo_c.setup(m->colorComponent.colors, 0);
		m->vao.linkAttribFast(SHADER_COLORS_LOCATION, 4, GL_FLOAT, false, 0, (void *)0);

		auto shader = em->addComponent<ShaderComponent>(axis);
		shader->shader = CreateUnique<ShaderProgram>("shader/vertexShader.glsl", "shader/fragmentShader.glsl", 0);
		shader->shader->createShaderProgram();

		auto t = em->addComponent<Transform>(axis);
        t->setPosition({WIDTH / 2, HEIGHT / 2, 0});
        t->setScale({WIDTH / 2, HEIGHT / 2, 0});

		auto render = em->addComponent<RenderComponent>(axis);

		auto vao = m->vao;
		m->render.setCall([&vao]() {
			vao.bind();
			glLineWidth(1.f);
			glDrawArrays(GL_LINES, 0, linePoints.size());
		});
		m->instanced = true;
		scene->addEntity(axis);
	}

	// Start application
	app->run();

	std::cout << "Application closed\n";
	return 0;
}
