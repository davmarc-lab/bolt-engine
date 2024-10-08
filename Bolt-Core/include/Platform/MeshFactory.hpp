#pragma once

#include "../Core/Math.hpp"

#include "../Core/Enums.hpp"

namespace bolt {
    namespace factory {
        namespace mesh {
            void createEmptySquare(const u32&, config::MeshConfig = {});
        	
            void initSquareMesh(const u32& id, config::MeshConfig config = {});

            void createEmptyCubeMesh(const u32&, config::MeshConfig = {}, const vec4& color = vec4(0, 0, 0, 1));

            void initCubeMesh(u32 id, config::MeshConfig config = {});
        }
    }
}
