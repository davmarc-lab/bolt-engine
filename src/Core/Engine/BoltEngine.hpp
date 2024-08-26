#pragma once

#include "Engine.hpp"

#include "../Graphics/Window/OpenGlWindow.hpp"

#include <memory>

class BoltEngine : public Engine {
  private:
    std::shared_ptr<OpenGlWindow> m_Opengl = OpenGlWindow::instance();

    bool m_isRunning;

  public:
    virtual void init() override;

    virtual void prepareLoop() override;

    virtual void handleInput() override;

    virtual void update() override;

    virtual void render() override;

    virtual void stop() override;

    virtual void run() override;

    virtual bool isRunning() const override;

    virtual ~BoltEngine() override;
};
