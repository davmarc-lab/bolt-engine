#include "../include/ImGuiInfo.hpp"
#include <memory>

#include "../../Bolt-Core/include/Graphics.hpp"

void ImGuiInfo::onRender() {
	ImGui::Begin("Statistics");
	
	ImGui::Text("FPS: %f", ImGui::GetIO().Framerate);
	ImGui::Text("Delta Time: %f", ImGui::GetIO().DeltaTime);
	ImGui::Text("(ECS) Entities Count: %d", bolt::EntityManager::instance()->getEntitiesCount());
	ImGui::Text("(GL) Entities Count: %d", bolt::RenderApi::instance()->getRenderer()->getTrackerTotal());
	ImGui::Text("Render Calls: %d", bolt::RenderApi::instance()->getRenderer()->getRenderCallCount());
	
	ImGui::End();
}
