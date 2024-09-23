#include "../../Bolt/src/Bolt.hpp"

class ImGuiEditor : public Bolt::Application {
public:
	ImGuiEditor() {
        Bolt::Application::enableImGui();
        Bolt::LayerStack::instance()->addCustomLayer(CreateShared<Bolt::ImGuiDockSpace>());
        Bolt::LayerStack::instance()->addCustomLayer(CreateShared<Bolt::ImGuiViewPort>());
        Bolt::LayerStack::instance()->addCustomLayer(CreateShared<Bolt::ImGuiUtility>());
        Bolt::LayerStack::instance()->addCustomLayer(CreateShared<Bolt::ImGuiEntityTree>());
        Bolt::LayerStack::instance()->addCustomLayer(CreateShared<Bolt::ImGuiProperties>());
	}

	~ImGuiEditor() {}
};

Bolt::Application *Bolt::createApplication() { return new ImGuiEditor(); }
