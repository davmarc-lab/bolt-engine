#pragma once

#include <string>

class Layer {
  private:
    std::string m_name;

  public:
    Layer(const std::string& name) : m_name(name) {}

    virtual void attach() {}

    virtual void detach() {}

    virtual void update() {}

    virtual void render() {}

    const std::string& getName() const { return this->m_name; }

    virtual ~Layer() = default;
};
