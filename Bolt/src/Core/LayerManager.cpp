#include "LayerManager.hpp"

namespace Bolt {
	void LayerManager::addLayer(const Shared<Layer> &layer) {
		this->m_layers.push_back(layer);
		layer->onAttach();
	}

	void LayerManager::execute(const std::function<void(Shared<Layer>)> &action) {
		for (const auto &l : this->m_layers) {
			action(l);
		}
	}
} // namespace Bolt
