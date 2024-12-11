#pragma once

#include "../../Bolt-Core/include/Engine.hpp"

inline BT_AUTOCONST ReadMeshDataFromFile = bolt::Event("Read Mesh Data");
inline BT_AUTOCONST SaveMeshDataFromFile = bolt::Event("Save Mesh Data");

class ImGuiConfig : public bolt::Layer {
public:
	ImGuiConfig() : bolt::Layer("Mesh Backup") {}

	~ImGuiConfig() override = default;
	
	virtual void onRender() override;
};
