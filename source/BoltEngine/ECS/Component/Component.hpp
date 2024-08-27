#pragma once

class Component {
  public:
    virtual ~Component() = default;
    
    virtual void invoke(const float &dt = 1.f) = 0;
};
