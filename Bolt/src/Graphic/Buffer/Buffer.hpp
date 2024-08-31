#pragma once

#include <cstdint>

class Buffer {
protected:
	const uint32_t m_id;
public:
	Buffer() = delete;

	Buffer(const uint32_t& id) : m_id(id) {}

	virtual ~Buffer() = default;
	
	virtual void bind() = 0;

	virtual void unbind() = 0;

	const uint32_t& getId() const { return this->m_id; }
};
