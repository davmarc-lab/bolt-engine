#include "../Graphic/ImGui/ImGuiFactory.hpp"

#include <iostream>

#include "../../dependencies/imgui/imgui.h"

#include "ImGuiLayer.hpp"
#include "Texture/GlTexture.hpp"

namespace Bolt {
	void ImGuiDockSpace::onEvent(const Event &e) {}

	void ImGuiDockSpace::onAttach() {}

	void ImGuiDockSpace::onRender() {
		ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;

		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		const ImGuiViewport *viewport = ImGui::GetMainViewport();

		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		if (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
			windowFlags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace", &this->m_open, windowFlags);

		// Submit the DockSpace
		if (const ImGuiIO &io = ImGui::GetIO(); io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
			const ImGuiID &dockspaceId = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), dockspaceFlags);
		}

		ImGui::End();

		ImGui::PopStyleVar();
		ImGui::PopStyleVar(2);
	}

	ImGuiEntityTree::ImGuiEntityTree() :
		m_entities(EntityManager::instance()->getEntitiesCount()) {

		if (!Application::isImGuiEnabled()) // PUT LOG HERE
			throw std::runtime_error("ImGui is disabled.");
	}

	void ImGuiEntityTree::onEvent(const Event &e) {}

	void ImGuiEntityTree::onRender() {
		ImGui::Begin(this->m_name.c_str());
		if (this->m_entities != EntityManager::instance()->getEntitiesCount()) {
			this->m_entities = EntityManager::instance()->getEntitiesCount();
		}
		for (auto ett : EntityManager::instance()->getEntities()) {
			if (ImGui::TreeNode(ett.getName().c_str())) {
				ImGui::PushID(&ett);
				ImGui::Text("Name: %s", ett.getName().c_str());
				ImGui::PopID();
				ImGui::TreePop();
			}
		}
		ImGui::End();
	}

	void ImGuiViewPort::onAttach() {
		// preparing framebuffer
		this->m_fbo.onAttach();
	}

	void ImGuiViewPort::onEvent(const Event &e) {}

	void ImGuiViewPort::onRender() {
		ImGui::Begin(this->m_name.c_str());
		if (!this->m_fboAttached) {
			this->m_fboAttached = true;
			const ImVec2 size = ImGui::GetWindowContentRegionMax();
			this->m_fbo.attachTexture({0, texture::opengl::target::TEXTURE_2D, 0, texture::opengl::format::RGB, static_cast<i32>(size.x), static_cast<i32>(size.y), 0, texture::opengl::format::RGB, texture::opengl::dataType::UNSIGNED_BYTE, NULL});
			ImGui::End();
			return;
		}

		ImGui::End();
	}

	void ImGuiUtility::onEvent(const Event &e) {}

	void ImGuiUtility::onRender() {
		ImGui::Begin(this->m_name.c_str());
		if (ImGui::Button("New Entity")) {
			EntityManager::instance()->createEntity();
		}
		ImGui::End();
	}

	void ImGuiProperties::onEvent(const Event &e) {}

	void ImGuiProperties::onRender() {
		ImGui::Begin(this->m_name.c_str());

		ImGui::End();
	}

	void ImGuiFactory::createBasicUi(Shared<GlfwWindow> window) {
		LayerManager::instance()->addLayer(CreateShared<ImGuiLayer>(window));

		LayerManager::instance()->addLayer(CreateShared<ImGuiDockSpace>());
		LayerManager::instance()->addLayer(CreateShared<ImGuiEntityTree>());
		LayerManager::instance()->addLayer(CreateShared<ImGuiViewPort>());
		LayerManager::instance()->addLayer(CreateShared<ImGuiUtility>());
		LayerManager::instance()->addLayer(CreateShared<ImGuiProperties>());
	}
} // namespace Bolt
