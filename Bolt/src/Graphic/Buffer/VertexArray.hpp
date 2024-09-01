#pragma once
#include <Graphic/Buffer/Buffer.hpp>

#include <Core/Utils.hpp>

namespace Bolt {
	class VertexArray : public Buffer {
	public:
		VertexArray(const u32& id) : Buffer(id) {}

		virtual void bind() override {}

		virtual void unbind() override {}
	};
}
