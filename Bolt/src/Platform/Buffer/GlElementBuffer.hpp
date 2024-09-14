#pragma once

#include "../../Graphic/Buffer/ElementBuffer.hpp"

#include <vector>

#include "../../Core/Utils.hpp"

namespace Bolt {
	class GlElementBuffer : public ElementBuffer {
	public:
		GlElementBuffer() = default;

		virtual ~GlElementBuffer() override;

		virtual void onAttach() override;

		virtual void onDetach() override;

		virtual void bind() const override;

		virtual void unbind() const override;

		virtual void setup(const f32 *indices, const i64 &size, const u32 &usage) const override;

		template <typename T>
		void setup(const T *indices, const i64 &size, const u32 &usage = 0);

		template <typename T>
		void setup(const std::vector<T> &indices, const u32 &usage = 0);
	};
} // namespace Bolt
