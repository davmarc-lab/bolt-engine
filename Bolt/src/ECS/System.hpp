#pragma once

namespace Bolt {
	class System {
	public:
		System() = default;

		virtual ~System() = default;
		
		inline virtual void onUpdate() {}
	};
}
