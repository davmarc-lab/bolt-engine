#pragma once

#include "../Core/Utils.hpp"

#include "../Core/Enums.hpp"

namespace Bolt {
    namespace factory {
        namespace mesh {
            void createEmptySquare(const u32&, config::MeshConfig = {});

            void createEmptyCubeMesh(const u32&, config::MeshConfig = {});
        }
    }
}
