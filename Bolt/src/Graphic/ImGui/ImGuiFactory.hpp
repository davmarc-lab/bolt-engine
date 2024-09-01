#pragma once

#include <Core/Utils.hpp>

#include <Core/LayerManager.hpp>

namespace Bolt {
	class ImGuiDockSpace final : public Layer {
	private:
		std::string m_name = "DockSpace";
		b8 m_open = true;

	public:
		ImGuiDockSpace() = default;

		virtual ~ImGuiDockSpace() override = default;

		virtual void onEvent(const Event& e) override;

		virtual void onRender() override;
	};

	class ImGuiEntityTree : public Layer {
	private:
		std::string m_name = "Entities";

	public:
		ImGuiEntityTree() = default;

		~ImGuiEntityTree() override = default;

		virtual void onEvent(const Event& e) override;

		virtual void onRender() override;
	};

	class ImGuiViewPort : public Layer {
	private:
		std::string m_name = "Viewport";

	public:
		ImGuiViewPort() = default;

		~ImGuiViewPort() override = default;

		virtual void onEvent(const Event& e) override;

		virtual void onRender() override;
	};

	class ImGuiUtility : public Layer {
	private:
		std::string m_name = "Utility";

	public:
		ImGuiUtility() = default;

		~ImGuiUtility() override = default;

		virtual void onEvent(const Event& e) override;

		virtual void onRender() override;
	};

	class ImGuiProperties : public Layer {
	private:
		std::string m_name = "Property";

	public:
		ImGuiProperties() = default;

		~ImGuiProperties() override = default;

		virtual void onEvent(const Event& e) override;

		virtual void onRender() override;
	};

	class ImGuiFactory {
		ImGuiFactory() = delete ;

	public:
		static void createBasicUi();
	};
}
