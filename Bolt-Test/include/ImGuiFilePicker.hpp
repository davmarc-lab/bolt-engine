#pragma once

#include <functional>
#include <string>
#include "../../Bolt-Core/include/Engine.hpp"

class ImGuiFilePicker {
public:
	void open() { this->m_open = true; }
	void close() { this->m_open = false; }

	void render();

	b8 isOpened() const { return this->m_open; }

	ImGuiFilePicker(const std::string& extension, std::function<void(const std::string&)> &&action) :
		m_extension(std::move(extension)), m_action(action) {}

	~ImGuiFilePicker() = default;

private:
	b8 m_open = false;
    std::string m_extension{};

	std::function<void(const std::string&)> m_action;
};
