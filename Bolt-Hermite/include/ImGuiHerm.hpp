#pragma once

#include "../../Bolt-Core/include/Engine.hpp"

enum MouseMode {
	INSERT,
	MOVE,
	REMOVE
};

BT_AUTOCONST HermCloseMesh = bolt::Event("Close Herm Mesh");
BT_AUTOCONST HermMergeFirstLast = bolt::Event("Merge First Last Points");
BT_AUTOCONST HermClearPoints = bolt::Event("Clear Mesh Points");
BT_AUTOCONST HermSaveMesh = bolt::Event("Save Herm Mesh");
BT_AUTOCONST HermOpenMesh = bolt::Event("Open Herm Mesh");

BT_AUTOCONST defaultFile = "resources/hermite/hermite.txt";

class ImGuiHerm : public bolt::Layer {
public:
	virtual void onRender() override;

	MouseMode getMouseMode() const { return this->m_mode; }

	b8 isShowTangentsEnabled() const { return this->m_showTangents; }

	b8 isEditTangentsEnabled() const { return this->m_editTangents; }

	ImGuiHerm() = delete;

	ImGuiHerm(const Shared<bolt::Window>& window, const u32 &id) :
		m_window(window), m_id(id) {}

	virtual ~ImGuiHerm() override = default;

private:
	Shared<bolt::Window> m_window;
	u32 m_id;
	MouseMode m_mode = INSERT;
	b8 m_showTangents = false;
	b8 m_editTangents = false;
};
