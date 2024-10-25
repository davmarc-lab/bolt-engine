#pragma once

#include "../../Core/Utils.hpp"
#include "../../Core/Math.hpp"
#include "../../Core/Layer.hpp"

#include <mutex>
#include <map>

namespace bolt {
	struct Character {
		u32 textureId;
		ivec2 size;
		ivec2 bearing;
		i64 advance;
	};

	struct TextSettings {
		std::string fontFace = "./resources/fonts/arial.ttf";
		u32 pixelWidth = 0;
		u32 pixelHeight = 48;
		u32 numChars = 128;
	};

	class TextManager : public Layer {
	public:
		TextManager() = default;
		
		TextManager(TextSettings settings) : m_settings(std::move(settings)) {}

		virtual void onAttach() override;

		virtual void onDetach() override;

		Character getCharacterInfo(const u64 &c) const;

	private:
		TextSettings m_settings{};
		
		std::map<u64, Character> m_characters{};
	};
}
