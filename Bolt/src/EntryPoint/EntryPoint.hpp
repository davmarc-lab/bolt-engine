#pragma once

#ifdef BT_WINDOWS

extern Bolt::Application* Bolt::createApplication();

int main(int argc, char** argv) {
	Bolt::Log::init();

	auto app = Bolt::createApplication();
	app->run();
	delete app;
}

#endif
