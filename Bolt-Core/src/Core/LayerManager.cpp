﻿#include "../../include/Core/LayerManager.hpp"
#include <iostream>
#include "../../include/Core/Layer.hpp"

namespace bolt {
	void LayerManager::addLayer(const Shared<Layer> &layer) {
		this->m_layers.push_back(layer);
		layer->onAttach();
	}

    void LayerManager::addLayersFromStack() {
        for (auto l: LayerStack::instance()->getLayers()) {
            this->addLayer(l);
        }
    }

	void LayerManager::execute(const std::function<void(Shared<Layer>)> &action) {
		for (const auto &l : this->m_layers) {
			action(l);
		}
	}
} // namespace Bolt