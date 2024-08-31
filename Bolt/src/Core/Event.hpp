#pragma once

#include <string>

namespace Bolt {

	class Event {
	private:
		std::string m_name;

	public:
		explicit Event(std::string name = "Basic Event") : m_name(std::move(name)) {}

		~Event() = default;

		const std::string& getName() const { return this->m_name; }
	};

}
