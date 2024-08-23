#pragma once

#include "../../../includes/OpenGl.hpp"

struct Buffer {
  public:
    virtual bool init() = 0;

    virtual GLuint bind() = 0;

    virtual void unbind() = 0;

    virtual ~Buffer() {}
};
