#include "../include/ImGuiConfig.hpp"

void ImGuiConfig::onRender() {
	ImGui::Begin("Mesh Save");

	if (ImGui::Button("Save Data")) {
		bolt::EventDispatcher::instance()->post(SaveMeshDataFromFile);
	}
	if (ImGui::Button("Read Data")) {
		bolt::EventDispatcher::instance()->post(ReadMeshDataFromFile);
	}

	ImGui::End();
}
