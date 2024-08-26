#pragma once

#include "IGPanel.hpp"

#include "../../../Platform/OpenGl/Buffers/FrameBuffer.hpp"

#include <memory>
#include <mutex>

class ImGuiFramePanel : public ImGuiPanel {
  private:
    inline static std::shared_ptr<ImGuiFramePanel> pointer = nullptr;
    inline static std::mutex mutex;

    ImGuiFramePanel() {}

  public:
    ImGuiFramePanel(ImGuiFramePanel &other) = delete;

    void operator=(const ImGuiFramePanel &other) = delete;

    inline static std::shared_ptr<ImGuiFramePanel> instance() {
        std::lock_guard<std::mutex> lock(mutex);
        if (pointer == nullptr) {
            std::shared_ptr<ImGuiFramePanel> copy(new ImGuiFramePanel());
            copy.swap(pointer);
        }

        return pointer;
    }

    virtual void init() override {
        this->m_pos = {IG_FRAME_XPOS, IG_FRAME_YPOS};
        this->m_size = {IG_FRAME_WIDTH, IG_FRAME_HEIGHT};
    }

    virtual void render() override {
        ImGui::SetNextWindowPos(ImVec2(this->m_pos.x, this->m_pos.y));
        ImGui::SetNextWindowSize(ImVec2(this->m_size.x, this->m_size.y));

        mainFrameBuffer->bind();

        ImGui::Begin("Vieport");
        ImGui::BeginChild("Render");

        mainFrameBuffer->setWidth(ImGui::GetContentRegionAvail().x);
        mainFrameBuffer->setHeight(ImGui::GetContentRegionAvail().y);

        ImGui::Image((void *)(intptr_t)mainFrameBuffer->getTextureId(), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));

        ImGui::EndChild();
        ImGui::End();

        mainFrameBuffer->unbind();
    }
};
