#pragma once

namespace Bolt {
	class Renderer {
	public:
		Renderer() = default;

		virtual ~Renderer() = default;
		
		virtual void onAttach() {}

		virtual void onDetach() {}
	};
}
