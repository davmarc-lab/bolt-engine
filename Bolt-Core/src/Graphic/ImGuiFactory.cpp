﻿#include "../../include/Platform/ImGuiFactory.hpp"

#include "../../../Bolt-Vendor/include/glfw/include/GLFW/glfw3.h"

#include "../../../Bolt-imgui/include/imgui/imgui.h"

#include "../../include/Graphic/ImGuiLayer.hpp"
#include "../../include/Graphic/Texture/Texture.hpp"

#include <iostream>

namespace bolt {
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
		// scene::perspectiveProjection = perspective(45.0f, static_cast<f32>(this->m_size.width) / this->m_size.height, 0.1f, 100.f);;
		// scene::orthoProjection = ortho(0.f, static_cast<f32>(this->m_size.width), 0.f, static_cast<f32>(this->m_size.height));
	}

	void ImGuiViewPort::onEvent(const Event &e) {}

	void ImGuiViewPort::rescaleViewport(const u16 &width, const u16 &height) {
	}

	void ImGuiViewPort::bindFBO() {
		this->m_fbo.bind();
	}

	void ImGuiViewPort::unbindFBO() {
		this->m_fbo.unbind();
	}

	void ImGuiViewPort::onRender() {
		if (!this->m_fboReady) {
			ImGui::Begin(this->m_name.c_str());

			this->m_fboReady = true;
			auto dim = ImGui::GetContentRegionAvail();
			this->m_size.width = dim.x;
			this->m_size.height = dim.y;

			scene::perspectiveProjection = perspective(45.0f, static_cast<f32>(this->m_size.width) / this->m_size.height, 0.1f, 100.f);
			scene::orthoProjection = ortho(0.f, static_cast<f32>(this->m_size.width), 0.f, static_cast<f32>(this->m_size.height));

			this->m_fbo = FrameBuffer({{this->m_size}, fbo::Operation::FB_DEFAULT});
			this->m_fbo.onAttach();

			ImGui::End();
			return;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);
		ImGui::Begin(this->m_name.c_str());
		ImGui::BeginChild("Render");

		auto dim = ImGui::GetContentRegionAvail();
		if (dim.x != this->m_size.width || dim.y != this->m_size.height) {
			this->m_fbo.rescaleFrameBuffer(static_cast<u16>(dim.x), static_cast<u16>(dim.y));
			this->m_size.width = dim.x;
			this->m_size.height = dim.y;
		}

		ImGui::Image((void *)(intptr_t)this->m_fbo.getTextureId(), ImVec2(this->m_size.width, this->m_size.height), ImVec2(0, 1), ImVec2(1, 0));

		ImGui::EndChild();
		ImGui::End();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void ImGuiUtility::onEvent(const Event &e) {}

	void ImGuiUtility::onRender() {
		ImGui::Begin(this->m_name.c_str());
		if (ImGui::Button("New Entity")) {
			EventDispatcher::instance()->post(events::ecs::CreateMeshEvent);
		}
		ImGui::End();
	}

	void ImGuiProperties::onEvent(const Event &e) {}

	void ImGuiProperties::onRender() {
		ImGui::Begin(this->m_name.c_str());

		ImGui::End();
	}

	void ImGuiFactory::createBasicUi() {
		LayerManager::instance()->addLayer(CreateShared<ImGuiDockSpace>());
		LayerManager::instance()->addLayer(CreateShared<ImGuiEntityTree>());
		LayerManager::instance()->addLayer(CreateShared<ImGuiViewPort>());
		LayerManager::instance()->addLayer(CreateShared<ImGuiUtility>());
		LayerManager::instance()->addLayer(CreateShared<ImGuiProperties>());
	}
} // namespace bolt