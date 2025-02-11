#include <fstream>

#include "../../Bolt-Core/include/Engine.hpp"
#include "../../Bolt-Core/include/Graphics.hpp"

#include "../include/HermiteFactory.hpp"

#include <GL/gl.h>
#include <iostream>

#include "../include/ImGuiHerm.hpp"

using namespace bolt;

#define WIDTH 900
#define HEIGHT 900

BT_AUTOCONST UpdateHermite = Event("Update Hermite Curve");

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
vec4 curveColor = {1, 0, 0, 1};

i32 currentPointIndex = -1;

int main(int argc, char *argv[]) {
	std::cout << "Application started\n";

	WindowProperties properties{};
	properties.maximized = false;
	properties.vsync = true;
	properties.backgroundColor = vec4(0.3, 0.3, 0.3, 1);

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

	// prepare camera info
	standardCamera.updateOrthoProjection(-1, 1, -1, 1);
	UniformBuffer ub = UniformBuffer("Matrices");
	ub.onAttach();
	ub.setup(sizeof(mat4), 0);
	auto VP = standardCamera.getViewProjMatrix();
	ub.update(0, sizeof(mat4), value_ptr(VP));
	EventDispatcher::instance()->subscribe(events::shader::ShaderProjectionChanged, [&w, &ub](auto p) {
		auto VP = standardCamera.getViewProjMatrix();
		ub.update(0, sizeof(mat4), value_ptr(VP));
		scene::updateTextProj(-1, 1, -1, 1);
	});
	EventDispatcher::instance()->post(events::shader::ShaderProjectionChanged);

	const auto em = EntityManager::instance();

	// axis creation
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
		mesh->render.setCall([vao]() {
			glLineWidth(1.f);
			RenderApi::instance()->getRenderer()->drawArrays(vao, GL_LINES, 0, axisPoints.size());
		});
		mesh->instanced = true;
		scene->addEntity(axis);
	}

	// points and lines logic
	auto controlPoints = em->createEntity();
	auto curve = em->createEntity();
	{
		auto points = em->addComponent<Mesh>(controlPoints);

		points->vao.onAttach();
		points->vao.bind();
		points->vbo_g.onAttach();
		points->vbo_g.setup(points->vertices, 0);
		points->vao.linkAttribFast(SHADER_VERTEX_LOCATION, 3, GL_FLOAT, false, 0, (void *)0);

		points->colorComponent.vbo_c.onAttach();
		points->colorComponent.vbo_c.setup(points->colorComponent.colors, 0);
		points->vao.linkAttribFast(SHADER_COLORS_LOCATION, 4, GL_FLOAT, false, 0, (void *)0);

		auto shader = em->addComponent<ShaderComponent>(controlPoints);
		// maybe change into another shader but I think is expensive
		shader->shader = CreateUnique<ShaderProgram>("shader/vertexShader.glsl", "shader/fragmentShader.glsl", 0);
		shader->shader->createShaderProgram();

		// default vals -> pos = {0, 0, 0}, scale = {1, 1, 1}, rot = {0, 0, 0}
		auto t = em->addComponent<Transform>(controlPoints);

		points->render.setCall([points]() {
			glLineWidth(2.f);
			glPointSize(4.f);
			RenderApi::instance()->getRenderer()->drawArrays(points->vao, GL_POINTS, 0, points->vertices.size());
			RenderApi::instance()->getRenderer()->drawArrays(points->vao, GL_LINE_STRIP, 0, points->vertices.size());
		});
		points->instanced = true;
		scene->addEntity(controlPoints);

		auto herm = em->addComponent<Mesh>(curve);
		auto foo = em->addComponent<Transform>(curve);

		herm->vertices = points->vertices;
		herm->colorComponent.colors = points->colorComponent.colors;

		herm->vao.onAttach();
		herm->vao.bind();
		herm->vbo_g.onAttach();
		herm->vbo_g.setup(herm->vertices, 0);
		herm->vao.linkAttribFast(SHADER_VERTEX_LOCATION, 3, GL_FLOAT, false, 0, (void *)0);

		herm->colorComponent.vbo_c.onAttach();
		herm->colorComponent.vbo_c.setup(herm->colorComponent.colors, 0);
		herm->vao.linkAttribFast(SHADER_COLORS_LOCATION, 4, GL_FLOAT, false, 0, (void *)0);

		auto s = em->addComponent<ShaderComponent>(controlPoints);
		// maybe change into another shader but I think is expensive
		s->shader = CreateUnique<ShaderProgram>("shader/vertexShader.glsl", "shader/fragmentShader.glsl", 0);
		s->shader->createShaderProgram();

		herm->render.setCall([herm]() {
			glLineWidth(2.f);
			RenderApi::instance()->getRenderer()->drawArrays(herm->vao, GL_LINE_STRIP, 0, herm->vertices.size());
		});

		herm->instanced = true;
		scene->addEntity(curve);

		// custom events initialization
		EventDispatcher::instance()->subscribe(UpdateHermite, [points, herm](auto p) {
			// update control points
			points->vao.bind();
			points->vbo_g.setup(points->vertices, 0);
			points->vao.linkAttribFast(SHADER_VERTEX_LOCATION, 3, GL_FLOAT, false, 0, (void *)0);
			points->colorComponent.vbo_c.setup(points->colorComponent.colors, 0);
			points->vao.linkAttribFast(SHADER_COLORS_LOCATION, 4, GL_FLOAT, false, 0, (void *)0);

			// update curve
			if (points->vertices.size() > 2) {
				Curve c{};
				c.CP = points->vertices;
				c.colCP = points->colorComponent.colors;
				buildHermite(curveColor, curveColor, &c);
				herm->vertices = c.vertex;
				herm->colorComponent.colors = c.colors;
			} else {
				herm->vertices = points->vertices;
				herm->colorComponent.colors = points->colorComponent.colors;
			}

			herm->vao.bind();
			herm->vbo_g.setup(herm->vertices, 0);
			herm->vao.linkAttribFast(SHADER_VERTEX_LOCATION, 3, GL_FLOAT, false, 0, (void *)0);
			herm->colorComponent.vbo_c.setup(herm->colorComponent.colors, 0);
			herm->vao.linkAttribFast(SHADER_COLORS_LOCATION, 4, GL_FLOAT, false, 0, (void *)0);
		});
		EventDispatcher::instance()->subscribe(HermClearPoints, [points, herm](auto p) {
			points->vertices.clear();
			points->colorComponent.colors.clear();
			herm->vertices.clear();
			herm->colorComponent.colors.clear();

			// clear buffers
			points->vao.bind();
			points->vbo_g.setup(points->vertices, 0);
			points->vao.linkAttribFast(SHADER_VERTEX_LOCATION, 3, GL_FLOAT, false, 0, (void *)0);
			points->colorComponent.vbo_c.setup(points->colorComponent.colors, 0);
			points->vao.linkAttribFast(SHADER_COLORS_LOCATION, 4, GL_FLOAT, false, 0, (void *)0);

			herm->vao.bind();
			herm->vbo_g.setup(herm->vertices, 0);
			herm->vao.linkAttribFast(SHADER_VERTEX_LOCATION, 3, GL_FLOAT, false, 0, (void *)0);
			herm->colorComponent.vbo_c.setup(herm->colorComponent.colors, 0);
			herm->vao.linkAttribFast(SHADER_COLORS_LOCATION, 4, GL_FLOAT, false, 0, (void *)0);
		});
		EventDispatcher::instance()->subscribe(HermCloseMesh, [points](auto p) {
			// close only with at least 3 vertices
			if (points->vertices.size() > 2) {
				if (points->vertices[0] != points->vertices[points->vertices.size() - 1]) {
					points->vertices.push_back(points->vertices[0]);
					points->colorComponent.colors.push_back(points->colorComponent.colors[0]);

					EventDispatcher::instance()->post(UpdateHermite);
				}
			}
		});
		EventDispatcher::instance()->subscribe(HermMergeFirstLast, [points](auto p) {
			if (points->vertices.size() > 3) {
				points->vertices[points->vertices.size() - 1] = points->vertices[0];
				EventDispatcher::instance()->post(UpdateHermite);
			}
		});
		EventDispatcher::instance()->subscribe(HermSaveMesh, [points](auto p) {
			// write to file (defaultFile)
			std::ofstream file(defaultFile);
			for (auto v : points->vertices) {
				file << v.x << " " << v.y << " " << v.z << "\n";
			}
            std::cout << "Done\n";
			file.close();
		});
		EventDispatcher::instance()->subscribe(HermOpenMesh, [points](auto p) {
			// read from file (defaultFile) and load
			Shared<Curve> fromFile = readDataFromFile(defaultFile);
			points->vertices = fromFile->CP;
			points->colorComponent.colors = factory::mesh::getColorVector(points->vertices.size(), pointColor);

			EventDispatcher::instance()->post(UpdateHermite);
		});
	}

	auto tm = CreateShared<TextManager>();
	tm->onAttach();
	ls->addCustomLayer(tm);

	Application::enableImGui();
	const auto ig = CreateShared<ImGuiLayer>(w);
	ls->addCustomLayer(ig);

	const auto he = CreateShared<ImGuiHerm>(w, controlPoints);
	ls->addCustomLayer(he);

	auto points = em->getEntityComponent<Mesh>(controlPoints);
	// set the mouse buttons callback
	w->setMouseButtonCallback([&points, &he](auto window, auto button, auto action, auto mods) {
		// calc mouse pos
		f64 x, y;
		glfwGetCursorPos(static_cast<GLFWwindow *>(window), &x, &y);
		y = bolt::abs(y - HEIGHT);
		// calc position int mesh local space
		x = x / (WIDTH / 2) - 1;
		y = y / (HEIGHT / 2) - 1;
		vec3 pos{x, y, 0};
		// selection tolerance
		vec3 tol{0.01f};

		switch (he->getMouseMode()) {
			case INSERT: {
				if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS) {
					points->vertices.emplace_back(x, y, 0);
					points->colorComponent.colors.push_back(pointColor);

					EventDispatcher::instance()->post(UpdateHermite);
				}
				break;
			}
			case MOVE: {
				if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS) {
					auto res = std::find_if(points->vertices.begin(), points->vertices.end(), [&pos, &tol](auto v) {
						auto diff = glm::abs(pos - v);
						return diff.x < tol.x && diff.y < tol.y;
					});
					if (res != points->vertices.end()) {
						currentPointIndex = res - points->vertices.begin();
					} else {
						currentPointIndex = -1;
					}
				}
				if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_RELEASE) {
					// reset selected point
					currentPointIndex = -1;
				}
				break;
			}
			case REMOVE: {
				if (button == GLFW_MOUSE_BUTTON_1 && action == GLFW_PRESS) {
					auto res = std::find_if(points->vertices.begin(), points->vertices.end(), [&pos, &tol](auto v) {
						auto diff = glm::abs(pos - v);
						return diff.x < tol.x && diff.y < tol.y;
					});
					if (res != points->vertices.end()) {
						auto index = res - points->vertices.begin();
						auto oldSize = static_cast<i32>(points->vertices.size());
						// remove the current point
						points->vertices.erase(res);
						if (index == 0 || index == oldSize - 1) {
							// merge the points
							EventDispatcher::instance()->post(HermMergeFirstLast);
						}
						EventDispatcher::instance()->post(UpdateHermite);
					}
				}
				break;
			}
		}
	});
	// set the mouse movement callback
	w->setCursorPosCallback([points, he](auto window, auto xpos, auto ypos) {
		xpos = xpos / (WIDTH / 2) - 1;
		ypos = (std::abs(ypos - HEIGHT)) / (HEIGHT / 2) - 1;
		if (he->getMouseMode() == MouseMode::MOVE) {
			if (currentPointIndex >= 0 && currentPointIndex < static_cast<i32>(points->vertices.size())) {
				points->vertices.at(currentPointIndex) = {xpos, ypos, 0};
				// merge the first and the last points
				if (currentPointIndex == 0 || currentPointIndex == static_cast<i32>(points->vertices.size()) - 1) {
					EventDispatcher::instance()->post(HermMergeFirstLast);
				}
				EventDispatcher::instance()->post(UpdateHermite);
			}
			// if some point is selected
			if (currentPointIndex != -1) {
				points->vertices[currentPointIndex] = {xpos, ypos, 0};
				EventDispatcher::instance()->post(UpdateHermite);
			}
		}
	});
	
	TextHelper h{};
	h.position = {0, 0};
	h.color = {1, 0, 0};
	h.text = "AAA";
	auto t = CreateShared<Text>(h);
	tm->addText(t);

	// Start application
	app->run();

	std::cout << "Application closed\n";
	return 0;
}
