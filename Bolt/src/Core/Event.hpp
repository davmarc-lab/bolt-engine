#pragma once

#include <mutex>
#include <functional>
#include <memory>
#include <map>
#include <string>

#include "Utils.hpp"

namespace Bolt {
	class Event {
	public:
		using EventType = std::string;

		explicit Event(std::string name = "Basic Event") :
			m_name(std::move(name)) {}

		b8 operator==(const Event &other) const { return this->m_name == other.getType(); }

		~Event() = default;

		const EventType &getType() const { return this->m_name; }

	private:
		EventType m_name;
	};

	namespace events {
		namespace window {
			// Window events
			BT_AUTOCONST WindowCreatedEvent = Event("Window Created");
			BT_AUTOCONST WindowDestroyedEvent = Event("Window Destroyed");
			BT_AUTOCONST WindowCloseEvent = Event("Window Close");
		}

		namespace input {
			// Input events
			BT_AUTOCONST KeyPressedEvent = Event("Key Pressed");
			BT_AUTOCONST KeyReleasedEvent = Event("Key Released");
			BT_AUTOCONST KeyModPressedEvent = Event("Mod Key Pressed");
			BT_AUTOCONST KeyModReleasedEvent = Event("Mod Key Released");

			BT_AUTOCONST MouseMoveEvent = Event("Mouse Moved");
			BT_AUTOCONST MouseStopEvent = Event("Mouse Stopped");
			BT_AUTOCONST MouseScrollUpEvent = Event("Mouse Scroll Up");
			BT_AUTOCONST MouseScrollDownEvent = Event("Mouse Scroll Down");

			BT_AUTOCONST MouseLeftButtonPressedEvent = Event("Mouse LButton Pressed");
			BT_AUTOCONST MouseLeftButtonReleasedEvent = Event("Mouse LButton Pressed");
			BT_AUTOCONST MouseRightButtonPressedEvent = Event("Mouse RButton Pressed");
			BT_AUTOCONST MouseRightButtonReleasedEvent = Event("Mouse RButton Pressed");
			BT_AUTOCONST MouseMiddleButtonPressedEvent = Event("Mouse MButton Pressed");
			BT_AUTOCONST MouseMiddleButtonReleasedEvent = Event("Mouse MButton Pressed");
		}

		namespace ecs {
			BT_AUTOCONST EntityCreatedEvent = Event("Entity Created");
			BT_AUTOCONST EntityRemovedEvent = Event("Entity Removed");

			BT_AUTOCONST ComponentAttachedToEntityEvent = Event("Component Attached");
			BT_AUTOCONST ComponentDetachFromEntityEvent = Event("Component Detached");
		}

		namespace loop {
			BT_AUTOCONST LoopPauseEvent = Event("Loop Pause");
			BT_AUTOCONST LoopResumeEvent = Event("Loop Resume");
			BT_AUTOCONST LoopStopEvent = Event("Loop Stop");
		}

        BT_AUTOCONST Update = Event("Update");
	};

	class EventDispatcher {
	public:
		using EventCallback = std::function<void(const Event &)>;

		EventDispatcher(EventDispatcher &other) = delete;

		void operator=(const EventDispatcher &other) = delete;

		inline static std::shared_ptr<EventDispatcher> instance() {
			std::lock_guard<std::mutex> lock(s_mutex);
			if (s_pointer == nullptr) {
				std::shared_ptr<EventDispatcher> copy(new EventDispatcher());
				copy.swap(s_pointer);
			}

			return s_pointer;
		}

		void subscribe(const Event& type, EventCallback&& callback);

		void post(const Event &e) const;

	private:
		inline static std::shared_ptr<EventDispatcher> s_pointer = nullptr;
		inline static std::mutex s_mutex;

		std::map<Event::EventType, std::vector<EventCallback>> m_observers;

		EventDispatcher() = default;
	};
}
