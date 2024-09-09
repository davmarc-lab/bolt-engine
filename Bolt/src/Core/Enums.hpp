#pragma once

#include "Utils.hpp"

namespace Bolt {
	namespace config {
		enum MeshConfig {
			mesh_colors = 1 << 0,
			mesh_texture = 1 << 1,
			mesh_indices = 1 << 2,
			mesh_normals = 1 << 3,
		};
	}

	namespace ecs {
		BT_CONSTEXPR u32 MAX_ENTITIES = 1024;
	}

} // namespace Bolt
