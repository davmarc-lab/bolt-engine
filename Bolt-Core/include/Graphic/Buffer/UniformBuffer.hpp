#pragma once

#include <string>
#include "../../Core/Utils.hpp"

namespace bolt {
	class UniformBuffer {
	public:
		virtual void onAttach();

		virtual void onDetach();

		virtual void bind() const;

		virtual void unbind() const;

		virtual void setup(const u32 &size, const u32 &binding, const u32 &offset = 0, const u32 &rangeSize = 0);

		virtual void fastSetup(const u32 &size, const u32 &binding, const u32 &offset = 0, const u32 &rangeSize = 0);

		virtual void update(const u32 &offset, const u32 &size, void *data);

		virtual void fastUpdate(const u32 &offset, const u32 &size, void *data);

		u32 getId() const { return this->m_id; }

		UniformBuffer() = delete;

		UniformBuffer(const std::string &variable) :
			m_variable(std::move(variable)) {}

		virtual ~UniformBuffer() = default;

	protected:
		u32 m_id = 0;
		u32 m_memAllocated = 0;
		std::string m_variable;
	};
} // namespace bolt
