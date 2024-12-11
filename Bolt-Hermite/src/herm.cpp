#include "../../Bolt-Core/include/Engine.hpp"
#include "../../Bolt-Core/include/Graphics.hpp"

#include "../include/HermiteFactory.hpp"

#include <GL/gl.h>
#include <iostream>

using namespace bolt;

#define WIDTH 900
#define HEIGHT 900

std::vector<vec3> axisPoints{
	{0, -1, 0},
	{0, 1, 0},
	{-1, 0, 0},
	{1, 0, 0},
};
std::vector<vec4> axisColors{
	{0, 0, 0, 1},
	{0, 0, 0, 1},
	{0, 0, 0, 1},
	{0, 0, 0, 1},
};

std::vector<vec3> pointsPos{};
std::vector<vec4> pointsCol{};
vec4 pointColor = {0, 0, 0, 1};

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

	standardCamera.updateOrthoProjection(-1, 1, -1, 1);
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
		auto mesh = em->addComponent<Mesh>(axis);
		mesh->vertices = axisPoints;
		mesh->colorComponent.colors = axisColors;

		mesh->vao.onAttach();
		mesh->vao.bind();
		mesh->vbo_g.onAttach();
		mesh->vbo_g.setup(mesh->vertices, 0);
		mesh->vao.linkAttribFast(SHADER_VERTEX_LOCATION, 3, GL_FLOAT, false, 0, (void *)0);

		mesh->colorComponent.vbo_c.onAttach();
		mesh->colorComponent.vbo_c.setup(mesh->colorComponent.colors, 0);
		mesh->vao.linkAttribFast(SHADER_COLORS_LOCATION, 4, GL_FLOAT, false, 0, (void *)0);

		auto shader = em->addComponent<ShaderComponent>(axis);
		shader->shader = CreateUnique<ShaderProgram>("shader/vertexShader.glsl", "shader/fragmentShader.glsl", 0);
		shader->shader->createShaderProgram();

		auto t = em->addComponent<Transform>(axis);

		auto render = em->addComponent<RenderComponent>(axis);

		auto vao = mesh->vao;
		mesh->render.setCall([&vao]() {
			glLineWidth(1.f);
			RenderApi::instance()->getRenderer()->drawArrays(vao, GL_LINES, 0, axisPoints.size());
		});
		mesh->instanced = true;
		scene->addEntity(axis);
	}

	{
		auto points = em->createEntity();
		auto mesh = em->addComponent<Mesh>(points);
		mesh->vertices = pointsPos;
		mesh->colorComponent.colors = pointsCol;

		mesh->vao.onAttach();
		mesh->vao.bind();
		mesh->vbo_g.onAttach();
		mesh->vbo_g.setup(mesh->vertices, 0);
		mesh->vao.linkAttribFast(SHADER_VERTEX_LOCATION, 3, GL_FLOAT, false, 0, (void *)0);

		mesh->colorComponent.vbo_c.onAttach();
		mesh->colorComponent.vbo_c.setup(mesh->colorComponent.colors, 0);
		mesh->vao.linkAttribFast(SHADER_COLORS_LOCATION, 4, GL_FLOAT, false, 0, (void *)0);

		auto shader = em->addComponent<ShaderComponent>(points);
		// maybe change into another shader but I think is expensive
		shader->shader = CreateUnique<ShaderProgram>("shader/vertexShader.glsl", "shader/fragmentShader.glsl", 0);
		shader->shader->createShaderProgram();

		// default vals -> pos = {0, 0, 0}, scale = {1, 1, 1}, rot = {0, 0, 0}
		auto t = em->addComponent<Transform>(points);

		auto render = em->addComponent<RenderComponent>(points);

		auto vao = mesh->vao;
		mesh->render.setCall([&vao]() {
			glPointSize(4.f);
			glLineWidth(2.f);
			RenderApi::instance()->getRenderer()->drawArrays(vao, GL_POINTS, 0, pointsPos.size());
			// if (pointsPos.size() > 2) {
			// 	auto herm = 0;
			// } else {
			// RenderApi::instance()->getRenderer()->drawArrays(vao, GL_LINE_STRIP, 0, pointsPos.size());
			// }
		});
		mesh->instanced = true;
		scene->addEntity(points);

		w->setKeyboardCallback([&mesh](auto window, auto key, auto code, auto action, auto mod) {
			if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
				f64 x, y;
				glfwGetCursorPos((GLFWwindow *)window, &x, &y);
				y = bolt::abs(y - HEIGHT);

				// work but maybe could be better with projection???? (MAYBE NOT)
				x = x / (WIDTH / 2) - 1;
				y = y / (HEIGHT / 2) - 1;

				mesh->vertices.emplace_back(x, y, 0);
				mesh->colorComponent.colors.push_back(pointColor);
				// update vbo
				mesh->vao.bind();
				mesh->vbo_g.setup(mesh->vertices, 0);
				mesh->vao.linkAttribFast(SHADER_VERTEX_LOCATION, 3, GL_FLOAT, false, 0, (void *)0);
				mesh->colorComponent.vbo_c.setup(mesh->colorComponent.colors, 0);
				mesh->vao.linkAttribFast(SHADER_COLORS_LOCATION, 4, GL_FLOAT, false, 0, (void *)0);
			}
		});
	}

	Application::enableImGui();
	const auto ig = CreateShared<ImGuiLayer>(w);
	ls->addCustomLayer(ig);

	// Start application
	app->run();

	std::cout << "Application closed\n";
	return 0;
}
