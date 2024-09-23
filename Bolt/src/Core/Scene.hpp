#pragma once

#include "Layer.hpp"
#include "Utils.hpp"

#include "../ECS/EntityManager.hpp"
#include "../ECS/System.hpp"

#include <mutex>
#include <vector>

#include "../Platform/Shader/GlShader.hpp"

namespace Bolt {
	class Scene {
	private:
		inline static Shared<Scene> s_pointer = nullptr;
		inline static std::mutex s_mutex;

		std::vector<u32> m_entities;
		Scene() = default;

	public:
		Scene(Scene &other) = delete;

		void operator=(const Scene &other) = delete;

		inline static Shared<Scene> instance() {
			std::lock_guard<std::mutex> lock(s_mutex);
			if (s_pointer == nullptr) {
				Shared<Scene> copy(new Scene());
				copy.swap(s_pointer);
			}

			return s_pointer;
		}

		inline u32 getEntitiesCount() const { return static_cast<u32>(this->m_entities.size()); }

		inline std::vector<u32> getEntities() const { return this->m_entities; }

		inline void addEntity(u32 entity) { this->m_entities.push_back(entity); }

		inline void destroy() { this->m_entities.clear(); }
	};

	class SceneLayer : public Layer {
	private:
	public:
		SceneLayer() = default;

		virtual ~SceneLayer() override = default;

		inline virtual void onDetach() override {
			Scene::instance()->destroy();
		}

		inline virtual void onRender() override {
			for (const auto &id : EntityManager::instance()->getEntitiesFromComponent<Mesh>()) {
				systems::render::drawElement(id);
			}
		}
	};
} // namespace Bolt
