﻿#include <Graphic/ImGui/ImGuiFactory.hpp>

#include <imgui.h>
#include <Platform/ImGuiLayer.hpp>

namespace Bolt {
	void ImGuiDockSpace::onEvent(const Event& e) {}

	void ImGuiDockSpace::onRender() {
		ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

		if (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode) windowFlags |= ImGuiWindowFlags_NoBackground;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace", &this->m_open, windowFlags);
		ImGui::PopStyleVar();

		ImGui::PopStyleVar(2);

		// Submit the DockSpace
		if (const ImGuiIO& io = ImGui::GetIO(); io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
			const ImGuiID& dockspaceId = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), dockspaceFlags);
		}

		ImGui::End();
	}

	void ImGuiEntityTree::onEvent(const Event& e) {}

	void ImGuiEntityTree::onRender() {
		ImGui::Begin(this->m_name.c_str());

		ImGui::End();
	}

	void ImGuiViewPort::onEvent(const Event& e) {}

	void ImGuiViewPort::onRender() {
		ImGui::Begin(this->m_name.c_str());

		ImGui::End();
	}

	void ImGuiUtility::onEvent(const Event& e) {}

	void ImGuiUtility::onRender() {
		ImGui::Begin(this->m_name.c_str());

		ImGui::End();
	}

	void ImGuiProperties::onEvent(const Event& e) {}

	void ImGuiProperties::onRender() {
		ImGui::Begin(this->m_name.c_str());

		ImGui::End();
	}

	void ImGuiFactory::createBasicUi() {
		LayerManager::instance()->addLayer(std::make_shared<ImGuiLayer>());

		LayerManager::instance()->addLayer(std::make_shared<ImGuiDockSpace>());
		LayerManager::instance()->addLayer(std::make_shared<ImGuiEntityTree>());
		LayerManager::instance()->addLayer(std::make_shared<ImGuiViewPort>());
		LayerManager::instance()->addLayer(std::make_shared<ImGuiUtility>());
		LayerManager::instance()->addLayer(std::make_shared<ImGuiProperties>());
	}
}