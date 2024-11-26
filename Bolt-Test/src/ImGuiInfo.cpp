#include "../include/ImGuiInfo.hpp"

#include "../../Bolt-Core/include/Graphics.hpp"

void ImGuiInfo::onRender() {
	ImGui::Begin("Physic");
	ImGui::Button("HELLO");
	ImGui::End();
}
