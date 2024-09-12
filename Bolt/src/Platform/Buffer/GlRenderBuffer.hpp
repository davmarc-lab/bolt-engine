
#pragma once

#include "../../Graphic/Buffer/RenderBuffer.hpp"

namespace Bolt {

	class GlRenderBuffer : RenderBuffer {
        private:
        public:
            GlRenderBuffer() = default;

            virtual ~GlRenderBuffer() override = default;

            virtual void onAttach() override;
            virtual void onDetach() override;

            virtual void bind() const override;
            virtual void unbind() const override;
	};
} // namespace Bolt
