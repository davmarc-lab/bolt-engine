#pragma once

#define WIN_WIDTH 1910
#define WIN_HEIGHT 1060

// Left ImGui Panel
#define IG_LEFT_XPOS 0
#define IG_LEFT_YPOS 0
#define IG_LEFT_WIDTH 400

// ImGui FrameBuffer
const int IG_FRAME_XPOS = IG_LEFT_XPOS + IG_LEFT_WIDTH;
const int IG_FRAME_YPOS = 0;
const int IG_FRAME_WIDTH = 1024;
const int IG_FRAME_HEIGHT = 768;
