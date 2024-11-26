#pragma once

#include "../../Bolt-Core/include/Engine.hpp"

class ImGuiInfo : public bolt::Layer {
public:

	virtual void onRender() override;
	
	ImGuiInfo() :
		bolt::Layer("Demo UI") {}

	virtual ~ImGuiInfo() override = default;

private:
};
