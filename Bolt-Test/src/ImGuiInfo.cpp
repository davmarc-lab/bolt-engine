#include "../include/ImGuiInfo.hpp"

#include "../../Bolt-Core/include/Graphics.hpp"

void ImGuiInfo::onRender() {
	ImGui::Begin("Statistics");
    ImGui::Text("FPS: %f", ImGui::GetIO().Framerate);
    ImGui::Text("Delta Time: %f", ImGui::GetIO().DeltaTime);
    ImGui::Text("Entities Count: %d", bolt::EntityManager::instance()->getEntitiesCount());
	ImGui::End();
}
