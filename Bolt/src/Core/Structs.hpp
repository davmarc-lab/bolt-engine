#pragma once

#include <Core/Utils.hpp>

struct WinPos {
	u16 x = 0;
	u16 y = 0;
};

struct WinSize {
	u16 width = 0;
	u16 height = 0;
};

// math.hpp
struct EntityPosition {
	f32 x = 0.f;
	f32 y = 0.f;
	f32 z = 0.f;
};