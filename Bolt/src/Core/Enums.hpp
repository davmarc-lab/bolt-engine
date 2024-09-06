#pragma once

#include "Utils.hpp"

namespace Bolt {
	namespace ecs {
		BT_CONSTEXPR u32 MAX_ENTITIES = 1024;
		
		enum Components {
			unknown,
			transform,
			render,
			normals,
		};
	}
}
