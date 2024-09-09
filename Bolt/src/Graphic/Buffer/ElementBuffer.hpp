#pragma once

#include <vector>

#include "Buffer.hpp"

namespace Bolt {
	class ElementBuffer : public Buffer {
	public:
		ElementBuffer() = default;
		ElementBuffer(const ElementBuffer &other) = delete;
		ElementBuffer(ElementBuffer &&other) noexcept { *this = std::move(other); }
		~ElementBuffer() override;

		ElementBuffer &operator=(const ElementBuffer &other) = delete;
		ElementBuffer &operator=(ElementBuffer &&other) noexcept;

		virtual void onAttach() override;

		virtual void bind() const override;

		virtual void unbind() const override;

		/**
		 * @brief Sets up the data for the buffer.
		 * @param indices A pointer to an array of floats to use as data.
		 * @param size The size in bytes of the data.
		 * @param usage The usage type.
		 */
		void setup(const f32 *indices, const i64 &size, const u32 &usage) const;

		/**
		 * @brief Sets up the data for the buffer.
		 * @tparam T Things stored *contiguously* in memory.
		 * @param indices A pointer to an array of Ts to use as data.
		 * @param size The size in bytes of the data.
		 * @param usage The usage type.
		 */
		template <typename T>
		void setup(const T *indices, const i64 &size, const u32 &usage = buffers::DEFAULT_USAGE);

		/**
		 * @brief Sets up the data for the buffer.
		 * @tparam T You might want this to some numeric, vector, etc type for good result,
		 * @param indices A std::vector of something to use as data.
		 * @param usage The usage type.
		 */
		template <typename T>
		void setup(const std::vector<T> &indices, const u32 &usage = buffers::DEFAULT_USAGE);
	};
}
