﻿#pragma once

#include "../../Graphic/Buffer/VertexBuffer.hpp"

#include "../../Core/Utils.hpp"

#include <vector>

namespace Bolt {
	class GlVertexBuffer : public VertexBuffer {
    protected:
        u32 m_id;
	public:
		GlVertexBuffer() = default;
		virtual ~GlVertexBuffer();

		virtual void onAttach() override;
		virtual void onDetach() override;

		virtual void bind() const override;

		virtual void unbind() const override;

		/**
		 * @brief Sets up the data for the buffer.
		 * @param vertices A pointer to an array of floats to use as data.
		 * @param size The size in bytes of the data.
		 * @param usage The usage type, default GL_STATIC_DRAW.
		 */
		virtual void setup(const f32 *vertices, const i64 &size, const u32 &usage) override;

		/**
		 * @brief Sets up the data for the buffer.
		 * @tparam T Things stored *contiguously* in memory.
		 * @param vertices A pointer to an array of Ts to use as data.
		 * @param size The size in bytes of the data.
		 * @param usage The usage type.
		 */
		template <typename T>
		void setup(const T *vertices, const i64 &size, const u32 &usage);

		/**
		 * @brief Sets up the data for the buffer.
		 * @tparam T You might want this to some numeric, vector, etc type for good result,
		 * @param vertices A std::vector of something to use as data.
		 * @param usage The usage type.
		 */
		template <typename T>
		void setup(const std::vector<T> &vertices, const u32 &usage);

		/**
		 * @brief Sets up the data for the buffer avoiding the cost of reallocating
		 *  the data store.
		 * @tparam T Things stored *contiguously* in memory.
		 * @param vertices A pointer to an array of Ts to use as data.
		 * @param size The size in bytes of the data.
		 * @param offset The offset into the buffer object's data store where data
		 *  replacement will begin, measured in bytes.
		 */
		template <typename T>
		void setupSubData(const T *vertices, const i64 &size, const i64 &offset);

		/**
		 * @brief Sets up the data for the buffer avoiding the cost of reallocating
		 *  the data store.
		 * @tparam T You might want this to some numeric, vector, etc type for good result,
		 * @param vertices A std::vector of floats to use as data.
		 * @param offset The offset into the buffer object's data store where data
		 *  replacement will begin, measured in bytes.
		 */
		template <typename T>
		void setupSubData(const std::vector<T> &vertices, const i64 &offset);
	};
} // namespace Bolt