#pragma once

#include "../../../includes/Const.hpp"
#include "../../../includes/ImGui.hpp"
#include "../../../includes/Structs.hpp"

class ImGuiPanel {
  protected:
    WinPos m_pos;

    WinSize m_size;

  public:
    virtual void init() = 0;

    virtual void render() = 0;
};
