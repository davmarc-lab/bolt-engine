#pragma once

class Component {
  public:
    virtual void invoke(const float &dt = 1.f) = 0;
};
