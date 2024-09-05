#pragma once

namespace Bolt {
	namespace ecs {
		constexpr u32 max_entities = 512;
		
		enum Components {
			unknown,
			transform,
			render
		};
	}
}
