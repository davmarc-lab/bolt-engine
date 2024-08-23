#pragma once

class Engine {
  public:
    virtual void init() = 0;

    virtual void prepareLoop() = 0;

    virtual void handleInput() = 0;

    virtual void update() = 0;

    virtual void render() = 0;

    virtual void stop() = 0;

    virtual void run() = 0;

    virtual bool isRunning() = 0;

    virtual ~Engine() {}
};
