#include "../Core/Event.hpp"

namespace Bolt {
	void EventDispatcher::subscribe(const Event &event, EventCallback &&callback) {
		if (this->m_observers.find(event.getType()) == this->m_observers.end())
			this->m_observers.emplace(event.getType(), std::vector<EventCallback>{});
		this->m_observers.at(event.getType()).emplace_back(std::move(callback));
	}

	void EventDispatcher::post(const Event &e) const {
		if (this->m_observers.find(e.getType()) == this->m_observers.end()) { return; }

		auto&& observers = this->m_observers.at(e.getType());
		for (auto&& o: observers) {
			o(e);
		}
	}
}
