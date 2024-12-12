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

		mesh->render.setCall([&mesh]() {
			glLineWidth(2.f);
			glPointSize(4.f);
			RenderApi::instance()->getRenderer()->drawArrays(mesh->vao, GL_POINTS, 0, mesh->vertices.size());
			RenderApi::instance()->getRenderer()->drawArrays(mesh->vao, GL_LINE_STRIP, 0, mesh->vertices.size());
		});
		mesh->instanced = true;
		scene->addEntity(points);

		auto lines = em->createEntity();
		auto ml = em->addComponent<Mesh>(lines);
		auto foo = em->addComponent<Transform>(lines);

		ml->vertices = mesh->vertices;
		ml->colorComponent.colors = mesh->colorComponent.colors;

		ml->vao.onAttach();
		ml->vao.bind();
		ml->vbo_g.onAttach();
		ml->vbo_g.setup(ml->vertices, 0);
		ml->vao.linkAttribFast(SHADER_VERTEX_LOCATION, 3, GL_FLOAT, false, 0, (void *)0);

		ml->colorComponent.vbo_c.onAttach();
		ml->colorComponent.vbo_c.setup(ml->colorComponent.colors, 0);
		ml->vao.linkAttribFast(SHADER_COLORS_LOCATION, 4, GL_FLOAT, false, 0, (void *)0);

		auto s = em->addComponent<ShaderComponent>(points);
		// maybe change into another shader but I think is expensive
		s->shader = CreateUnique<ShaderProgram>("shader/vertexShader.glsl", "shader/fragmentShader.glsl", 0);
		s->shader->createShaderProgram();

		ml->render.setCall([&ml]() {
			glLineWidth(2.f);
			RenderApi::instance()->getRenderer()->drawArrays(ml->vao, GL_LINE_STRIP, 0, ml->vertices.size());
		});

		ml->instanced = true;
		scene->addEntity(lines);

		w->setMousebuttonCallback([&mesh, &ml](auto window, auto button, auto action, auto mods) {
			if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS) {
				f64 x, y;
				glfwGetCursorPos((GLFWwindow *)window, &x, &y);
				y = bolt::abs(y - HEIGHT);

				// work but maybe could be better with projection???? (MAYBE NOT)
				x = x / (WIDTH / 2) - 1;
				y = y / (HEIGHT / 2) - 1;

				// update points
				mesh->vertices.emplace_back(x, y, 0);
				mesh->colorComponent.colors.push_back(pointColor);

				mesh->vao.bind();
				mesh->vbo_g.setup(mesh->vertices, 0);
				mesh->vao.linkAttribFast(SHADER_VERTEX_LOCATION, 3, GL_FLOAT, false, 0, (void *)0);
				mesh->colorComponent.vbo_c.setup(mesh->colorComponent.colors, 0);
				mesh->vao.linkAttribFast(SHADER_COLORS_LOCATION, 4, GL_FLOAT, false, 0, (void *)0);

				// update HERMITE curve
				if (mesh->vertices.size() > 2) {
					Curve c{};
					c.CP = mesh->vertices;
					c.colCP = mesh->colorComponent.colors;
					buildHermite({1, 0, 0, 1}, {1, 0, 0, 1}, &c);
					ml->vertices = c.vertex;
					ml->colorComponent.colors = c.colors;
				} else {
					ml->vertices = mesh->vertices;
					ml->colorComponent.colors = mesh->colorComponent.colors;
				}

				ml->vao.bind();
				ml->vbo_g.setup(ml->vertices, 0);
				ml->vao.linkAttribFast(SHADER_VERTEX_LOCATION, 3, GL_FLOAT, false, 0, (void *)0);
				ml->colorComponent.vbo_c.setup(ml->colorComponent.colors, 0);
				ml->vao.linkAttribFast(SHADER_COLORS_LOCATION, 4, GL_FLOAT, false, 0, (void *)0);
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
