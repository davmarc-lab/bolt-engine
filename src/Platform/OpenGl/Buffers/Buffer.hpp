#pragma once

#include "../../../includes/OpenGl.hpp"

struct Buffer {
  public:
    virtual bool init() = 0;

    virtual GLuint bind() const = 0;

    virtual void unbind() const = 0;

    virtual ~Buffer() {}
};
