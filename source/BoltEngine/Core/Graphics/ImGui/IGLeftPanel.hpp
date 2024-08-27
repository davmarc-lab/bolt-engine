#pragma once

#include "IGPanel.hpp"

#include <mutex>

class ImGuiLeftPanel : public ImGuiPanel {
  private:
    inline static ImGuiLeftPanel *pointer = nullptr;
    inline static std::mutex mutex;

    ImGuiLeftPanel() {}

  public:
    ImGuiLeftPanel(ImGuiLeftPanel &other) = delete;

    void operator=(const ImGuiLeftPanel &other) = delete;

    inline static ImGuiLeftPanel *instance() {
        std::lock_guard<std::mutex> lock(mutex);
        if (pointer == nullptr)
            pointer = new ImGuiLeftPanel();

        return pointer;
    }

    virtual void init() override {
        this->m_pos = {IG_LEFT_XPOS, IG_LEFT_YPOS};
        this->m_size = {IG_LEFT_WIDTH, WIN_HEIGHT};
    }

    virtual void render() override {
        ImGui::SetNextWindowPos(ImVec2(this->m_pos.x, this->m_pos.y));
        ImGui::SetNextWindowSize(ImVec2(this->m_size.x, this->m_size.y));
        ImGui::Begin("Main");

        ImGui::End();
    }
};
