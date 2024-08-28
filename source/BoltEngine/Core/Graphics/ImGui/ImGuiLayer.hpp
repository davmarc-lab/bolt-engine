#pragma once

#include "../../Layer/Layer.hpp"
#include <cstdint>

class ImGuiLayer : public Layer {
  public:
    ImGuiLayer();

    ~ImGuiLayer() = default;

    virtual void attach() override;

    virtual void detach() override;

    void begin();

    void end();

    uint32_t getActiveWidgetId() const;
};
