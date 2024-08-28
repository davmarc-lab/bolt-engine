#pragma once

#include "IGPanel.hpp"

class ImGuiMainPanel : public ImGuiPanel {
  private:
    inline static ImGuiMainPanel *pointer = nullptr;
    inline static std::mutex mutex;

    ImGuiMainPanel() {}

  public:
    ImGuiMainPanel(ImGuiMainPanel &other) = delete;

    void operator=(const ImGuiMainPanel &other) = delete;

    inline static ImGuiMainPanel *instance() {
        std::lock_guard<std::mutex> lock(mutex);
        if (pointer == nullptr)
            pointer = new ImGuiMainPanel();

        return pointer;
    }

    virtual void init() override {
        this->m_pos = {IG_LEFT_XPOS, IG_LEFT_YPOS};
        this->m_size = {IG_LEFT_WIDTH, WIN_HEIGHT};
    }

    virtual void render() override {
        ImGui::Begin("Base");

        ImGui::End();
    }
};
