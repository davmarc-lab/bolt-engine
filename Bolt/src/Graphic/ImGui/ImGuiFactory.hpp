#pragma once

#include <stdexcept>
#include "../../Core/Utils.hpp"

#include "../../Core/LayerManager.hpp"
#include "../../ECS/EntityManager.hpp"

#include "../Buffer/FrameBuffer.hpp"

#include "../../Application/Application.hpp"

namespace Bolt {
	class ImGuiDockSpace final : public Layer {
	private:
		std::string m_name = "DockSpace";
		b8 m_open = true;

	public:
		ImGuiDockSpace() {
			if (!Application::isImGuiEnabled()) // PUT LOG HERE
				throw std::runtime_error("ImGui is disabled.");
		}

		virtual ~ImGuiDockSpace() override = default;

		virtual void onAttach() override;

		virtual void onEvent(const Event &e) override;

		virtual void onRender() override;
	};

	class ImGuiEntityTree : public Layer {
	private:
		std::string m_name = "Entities";
		u32 m_entities;

	public:
		ImGuiEntityTree();

		~ImGuiEntityTree() override = default;

		virtual void onEvent(const Event &e) override;

		virtual void onRender() override;
	};

	class ImGuiViewPort : public Layer {
	private:
		std::string m_name = "Viewport";
		FrameBuffer m_fbo;
		WinSize size;
		b8 m_fboAttached = false;

	public:
		ImGuiViewPort() {
			if (!Application::isImGuiEnabled()) // PUT LOG HERE
				throw std::runtime_error("ImGui is disabled.");
		}

		~ImGuiViewPort() override = default;

		virtual void onAttach() override;

		virtual void onEvent(const Event &e) override;

		virtual void onRender() override;
	};

	class ImGuiUtility : public Layer {
	private:
		std::string m_name = "Utility";

	public:
		ImGuiUtility() {
			if (!Application::isImGuiEnabled()) // PUT LOG HERE
				throw std::runtime_error("ImGui is disabled.");
		}

		~ImGuiUtility() override = default;

		virtual void onEvent(const Event &e) override;

		virtual void onRender() override;
	};

	class ImGuiProperties : public Layer {
	private:
		std::string m_name = "Property";

	public:
		ImGuiProperties() {
			if (!Application::isImGuiEnabled()) // PUT LOG HERE
				throw std::runtime_error("ImGui is disabled.");
		}

		~ImGuiProperties() override = default;

		virtual void onEvent(const Event &e) override;

		virtual void onRender() override;
	};

	class ImGuiFactory {
		ImGuiFactory() = delete;

	public:
		static void createBasicUi(Shared<GlfwWindow> window);
	};
} // namespace Bolt
