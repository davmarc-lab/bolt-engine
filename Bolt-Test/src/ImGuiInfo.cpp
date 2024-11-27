#include "../include/ImGuiInfo.hpp"
#include <memory>

#include "../../Bolt-Core/include/Graphics.hpp"

void ImGuiInfo::onRender() {
	ImGui::Begin("Statistics");
	ImGui::Text("FPS: %f", ImGui::GetIO().Framerate);
	ImGui::Text("Delta Time: %f", ImGui::GetIO().DeltaTime);
	ImGui::Text("Entities Count: %d", bolt::EntityManager::instance()->getEntitiesCount());
	ImGui::End();

	ImGui::Begin("Lights");
	for (auto l : bolt::EntityManager::instance()->getLights()) {
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
				break;
			}
			case bolt::LIGHT_SPOT: {
				break;
			}
		}
	}
	ImGui::End();
}
