#include "../include/ImGuiHerm.hpp"

#include "../../Bolt-Core/include/Graphics.hpp"

void ImGuiHerm::onRender() {
	ImGui::Begin("Editor");
	auto col = this->m_window->getClearColor();
	if (ImGui::ColorEdit4("Background Color", &col.x)) {
		this->m_window->setClearColor(col);
	}

	ImGui::Text("Mouse mode");
	if (ImGui::RadioButton("Insert", this->m_mode == MouseMode::INSERT)) { this->m_mode = MouseMode::INSERT; }
	ImGui::SameLine();
	if (ImGui::RadioButton("Move", this->m_mode == MouseMode::MOVE)) { this->m_mode = MouseMode::MOVE; }
	ImGui::SameLine();
	if (ImGui::RadioButton("Remove", this->m_mode == MouseMode::REMOVE)) { this->m_mode = MouseMode::REMOVE; }

	if (ImGui::Button("Close Mesh")) {
		bolt::EventDispatcher::instance()->post(HermCloseMesh);
	}
	ImGui::SameLine();
	if (ImGui::Button("Merge First/Last")) {
		bolt::EventDispatcher::instance()->post(HermMergeFirstLast);
	}

	if (ImGui::Button("Clear Points")) {
		bolt::EventDispatcher::instance()->post(HermClearPoints);
	}

	ImGui::Text("Tangents");
	ImGui::Checkbox("Show Tangents", &this->m_showTangents);
	ImGui::Checkbox("Modify Tangents", &this->m_editTangents);

	ImGui::Text("File");
	if (ImGui::Button("Save")) {
		bolt::EventDispatcher::instance()->post(HermSaveMesh);
	}
	ImGui::SameLine();
	if (ImGui::Button("Open")) {
		bolt::EventDispatcher::instance()->post(HermOpenMesh);
	}

	ImGui::End();
}
