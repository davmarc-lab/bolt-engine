#include <Core/LayerManager.hpp>

#include <Core/Log.hpp>
#include <Platform/GlfwWindow.hpp>

namespace Bolt {
	void LayerManager::addLayer(const std::shared_ptr<Layer>& layer) {
		this->m_layers.push_back(layer);
		layer->onAttach();
	}

	void LayerManager::execute(const std::function<void(const std::shared_ptr<Layer>&)>& action) { for (const auto& l : this->m_layers) { action(l); } }
}
