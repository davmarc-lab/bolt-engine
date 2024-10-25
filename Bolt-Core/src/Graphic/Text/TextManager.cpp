#include "../../../include/Graphic/Text/TextManager.hpp"

#include "../../../include/Graphics.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>

#include "../../../include/Graphic/Texture/Texture.hpp"

namespace bolt {
	void TextManager::onAttach() {
		FT_Library ft;
		if (FT_Init_FreeType(&ft)) {
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library\n";
			exit(EXIT_FAILURE);
		}

		FT_Face face;
		if (FT_New_Face(ft, this->m_settings.fontFace.c_str(), 0, &face)) {
			std::cout << "ERROR::FREETYPE: Failed to load font\n";
			exit(EXIT_FAILURE);
		}

		FT_Set_Pixel_Sizes(face, this->m_settings.pixelWidth, this->m_settings.pixelHeight);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		texture::Parameters param{};
		param.target = GL_TEXTURE_2D;
		param.internalFormat = GL_RED;
		param.border = 0;
		param.format = GL_RED;
		param.dataType = GL_UNSIGNED_BYTE;

		for (unsigned char c = 0; c < this->m_settings.numChars; c++) {
			if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph\n";
				continue;
			}

			Texture texture = Texture(param, face->glyph->bitmap.width, face->glyph->bitmap.rows);
			texture.onAttach();
			texture.setTexParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			texture.setTexParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			texture.setTexParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			texture.setTexParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			texture.createTexture2D(face->glyph->bitmap.buffer);

			this->m_characters.insert_or_assign(c, Character{texture.getId(), ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows), ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top), face->glyph->advance.x});
		}
		FT_Done_Face(face);
		FT_Done_FreeType(ft);
	}

	void TextManager::onDetach() {}

	Character TextManager::getCharacterInfo(const u64 &c) const {
		return this->m_characters.at(c);
	}

} // namespace bolt
