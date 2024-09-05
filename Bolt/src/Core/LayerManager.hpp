#pragma once

#include <memory>
#include <mutex>
#include <vector>

#include "Layer.hpp"
#include "../Platform/GlfwWindow.hpp"

namespace Bolt {

	class LayerManager {
	private:
		inline static std::shared_ptr<LayerManager> s_pointer = nullptr;
		inline static std::mutex s_mutex;

		std::vector<std::shared_ptr<Layer>> m_layers;

		LayerManager() {}

	public:
		LayerManager(LayerManager& other) = delete;

		void operator=(const LayerManager& other) = delete;

		inline static std::shared_ptr<LayerManager> instance() {
			std::lock_guard<std::mutex> lock(s_mutex);
			if (s_pointer == nullptr) {
				std::shared_ptr<LayerManager> copy(new LayerManager());
				copy.swap(s_pointer);
			}

			return s_pointer;
		}

		void addLayer(const std::shared_ptr<Layer>& layer);

		template <class T>
		inline void getLayerFromType() const { BT_WARN_CORE("{0} method not implemented.", __FILE__); }

		void execute(const std::function<void(const std::shared_ptr<Layer>&)>& action);

	};

}
