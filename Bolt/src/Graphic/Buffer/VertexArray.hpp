#pragma once
#include <Graphic/Buffer/Buffer.hpp>

class VertexArray : public Buffer {
public:
	VertexArray(const uint32_t& id) : Buffer(id) {}

	virtual void bind() override {}
	
	virtual void unbind() override {}
};
