#pragma once

#include "Utils.hpp"

#include "Event.hpp"

#include <string>

namespace Bolt {

	/*
	 * Interface for implementing a custom `Layer`.
	 *
	 * All the layers are managed by the `LayerManager`.
	 */
	class Layer {
	protected:
		std::string m_layerName;

	public:
		explicit Layer(std::string name = "Layer");

		virtual ~Layer() = default;

		/// Initialize the `Layer` elements before entering the game loop.
		virtual void onAttach() {}

		/// Called before the application is closed.
		/// It's used to free all the `Layer` elements.
		virtual void onDetach() {}

		/// ???
		virtual void onEvent(const Event &e) {}

		/// Updates `Layer` elements in the game loop.
		virtual void onUpdate() {}

		/// Called before `Layer::onRender()`, it should contain all the operations before rendering.
		virtual void begin() {}

		/// Render all `Layer` elements.
		virtual void onRender() {}

		/// Called after `Layer::onRender()`.
		virtual void end() {}
	};

}
