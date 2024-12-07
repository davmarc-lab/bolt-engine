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

	ImGui::Begin("Lights");
	for (auto [id, l] : bolt::EntityManager::instance()->getLights()) {
		switch (l->getLight()->type) {
			case bolt::LIGHT_DIRECTIONAL: {
                auto cast = std::static_pointer_cast<bolt::DirectionalLight>(l->getLight());
                auto dir = cast->direction;
                if (ImGui::SliderFloat3("Dir", &dir.x, -1, 1)) {
                    cast->direction = dir;
                }
				break;
			}
			case bolt::LIGHT_POINT: {
                auto cast = std::static_pointer_cast<bolt::PointLight>(l->getLight());
                auto pos = cast->position;
                if (ImGui::DragFloat3("Pos", &pos.x)) {
                	bolt::systems::transform::updateLightPosition(id, pos);
                }
				break;
			}
			case bolt::LIGHT_SPOT: {
				break;
			}
		}
	}
	ImGui::End();
}
