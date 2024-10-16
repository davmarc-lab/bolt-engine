#pragma once

#include "../Core/Math.hpp"

#include "../Core/Enums.hpp"

namespace bolt {
    namespace factory {
        namespace mesh {
            void createCustomMesh(const u32&, config::MeshConfig, config::MeshShape);

            void initCustomMesh(const u32&, config::MeshConfig, config::MeshShape);
            
            void createEmptySquare(const u32&, config::MeshConfig = {});
        	
            void initSquareMesh(const u32& id, config::MeshConfig config = {});
        }
    }
}
