﻿#pragma once

#include "Utils.hpp"

namespace bolt {
	namespace config {
		/// Configs for mesh creation.
		enum MeshConfig {
			mesh_colors = 1 << 0,
			mesh_texture = 1 << 1,
			mesh_indices = 1 << 2,
			mesh_normals = 1 << 3,
			mesh_default_shader = 1 << 4,
		};

        /// Congfigs for rrender api.
		enum RenderApiConfig {
			render_unknonw = 0,
			render_opengl = 1 << 0,
		};
	} // namespace config

	namespace ecs {
		BT_CONSTEXPR u32 MAX_ENTITIES = 1024;
	}

} // namespace Bolt