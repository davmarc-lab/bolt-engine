#pragma once

#include "../../Core/Utils.hpp"

namespace bolt {
	namespace rbo {
		struct Config {
			u32 format;
			u32 attachment;
			u16 width;
			u16 height;
		};
	}
	
	class RenderBuffer {
	private:
		u32 m_id = 0;
		rbo::Config m_config{};
		b8 m_ready = false;

	public:
		RenderBuffer() = default;

		explicit RenderBuffer(const rbo::Config config) : m_config(config) { this->m_ready = true; }

		~RenderBuffer() = default;

		void onAttach();
		void onDetach();

        void bind() const;
        void unbind() const;
		
		u32 getAttachmentType() const;

		const u32 &getId() const { return this->m_id; }
	};
} // namespace Bolt
