#include "../../include/Core/Scene.hpp"

#include "../../include/ECS/System.hpp"

namespace bolt {
    void SceneLayer::onRender() {
        systems::render::drawAllMeshes();
    }
}
