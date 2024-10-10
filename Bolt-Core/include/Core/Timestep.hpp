#pragma once

#include "../../../Bolt-Vendor/include/glfw/include/GLFW/glfw3.h"

#include "Utils.hpp"

namespace bolt {
	class Timestep final {
	public:
		void setTime(const f32 &time) { this->m_time = time; }

		f32 getTime() const { return static_cast<f32>(glfwGetTime()); }

        const f32& getTimeStep() const { return this->m_timeStep; }

		Timestep(const f32 &timeStep = 1 / 60.f) :
			m_timeStep(timeStep) {}

		~Timestep() = default;

	private:
		f32 m_time = 0.f;
		f32 m_timeStep;
	};
}; // namespace bolt
