#pragma once

#include <Core/Utils.hpp>
#include <Core/Math.hpp>

namespace Bolt {
	struct WinPos {
		u16 x = 0;
		u16 y = 0;
	};

	struct WinSize {
		u16 width = 0;
		u16 height = 0;
	};

	struct EntityInfo {
		vec3 position = vec3(0);
		vec3 scale = vec3(1);
		vec3 rotation = vec3(0);
		b8 dirty = false;
	};
}
