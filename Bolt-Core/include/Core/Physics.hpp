#pragma once

#include "Layer.hpp"
#include "Timestep.hpp"
#include "Utils.hpp"

#include <set>

namespace bolt {
	class PhysicsWorld : public Layer {
	public:
		PhysicsWorld() :
			Layer("Physic World") {
			this->m_entities = CreateUnique<std::set<u32>>();
		}

		inline void addEntity(const u32 &entity) { this->m_entities->insert(entity); }

		inline b8 removeEntity(const u32 &entity) {
            return this->m_entities->erase(entity);
		}

        inline u16 Count() const { return this->m_entities->size(); }

		virtual void onAttach() override;

		virtual void onDetach() override;

		virtual void onUpdate() override;

		virtual ~PhysicsWorld() {}

	private:
        void step();

		Unique<std::set<u32>> m_entities;
        Timestep m_time{};
        f32 m_accumulator = 0.f;
        f32 m_prevTime = 0.f;
        f32 m_currTime = 0.f;
        f32 m_frameTime = 0.f;
	};

} // namespace bolt
