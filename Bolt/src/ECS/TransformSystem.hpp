#pragma once

#include "System.hpp"

namespace Bolt {
	class TransformSystem : public System {
	private:

	public:
		TransformSystem() = default;

		~TransformSystem() override = default;

		void onUpdate() override;
	};
}
