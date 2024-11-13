#pragma once

#include "../Core/Math.hpp"

#include "../Core/Enums.hpp"
#include "../Core/Structs.hpp"

namespace bolt {
	namespace factory {
		namespace mesh {
			void createCustomMesh(const u32&, config::MeshConfig, config::MeshShape);

			void initCustomMesh(const u32&, config::MeshConfig, config::MeshShape);

            void instanceMesh(const u32& id, const MeshHelper& helper);
		}
	}
}
