#include "BoltEngine.hpp"

#include "../Event/KeyboardEvent.hpp"
#include "../Input/KeyboardManager.hpp"

auto km = KeyboardManager::instance();

void BoltEngine::init() {
    // Init model

    // Init Main Window
    this->m_Opengl->init();
}

void BoltEngine::handleInput() {
    // Process all key pressed in this frame.
    KeyboardEvent::instance()->handle(KeyboardManager::instance()->getLastKey());
}

void BoltEngine::update() {}

void BoltEngine::render() {
    // OpenGL render
    this->m_Opengl->render();

    // ImGui render
    this->m_Opengl->renderImGui();

    // Create ImGui backup if needed
    this->m_Opengl->makeGlfwContextBackup();

    // Swap buffer
    this->m_Opengl->swapBuffers();
}

void BoltEngine::prepareLoop() {
    this->m_Opengl->pollEvents();
    this->m_Opengl->prepareImGuiRender();
}

void BoltEngine::run() {
    this->m_isRunning = true;

    // Start Game Loop
    while (this->isRunning()) {
        this->prepareLoop();
        this->handleInput();
        this->update();
        this->render();
    }

    this->m_Opengl->destroy();
}

void BoltEngine::stop() { this->m_isRunning = false; }

bool BoltEngine::isRunning() { return (this->m_isRunning && !this->m_Opengl->shouldWindowClose()); }

BoltEngine::~BoltEngine() {
    std::cout << "Closing Engine!\n";
}
