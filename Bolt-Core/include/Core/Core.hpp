#pragma once

// asserts
/*
* Basic runtime assert.
*/
#define BT_ASSERT(exp) assert(exp)

#define SHADER_VERTEX_LOCATION 0
#define SHADER_COLORS_LOCATION 1
#define SHADER_TEXCOORDS_LOCATION 2
#define SHADER_NORMAL_LOCATION 3
// instanced rendering
#define SHADER_POS_OFFSET_LOCATION 4
#define SHADER_COLOR_OFFSET_LOCATION 5

#define SHADER_LIGHT_BLOCK_NAME "Lights"
#define SHADER_LIGHT_BLOCK_BIND 1
