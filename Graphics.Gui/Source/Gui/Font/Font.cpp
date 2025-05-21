#include "../../../Header/Gui/Font/Font.h"
#include <algorithm>
#include <iostream>

Font::Font(ImageBuffer* imageBuffer, const char* characters, int characterWidth, int characterHeight) {
	m_imageBuffer = imageBuffer;

	m_characterCount = 0;
	while (characters[m_characterCount++] != 0);

	m_characters = characters;
	m_characterWidth = characterWidth;
	m_characterHeight = characterHeight;
}

void Font::GetCharacterLocation(char character, int& x, int& y) {
	int index = FindIndex(m_characters, m_characterCount, character);

	if (index < 0) {
		x = -1;
		y = -1;
		return;
	}

	int width = (m_imageBuffer->GetWidth() + 1) / (GetCharacterWidth() + 1);

	x = index % width * (GetCharacterWidth() + 1);
	y = index / width * (GetCharacterHeight() + 1);
}

const char* Font::GetCharacters() {
	return m_characters;
}

int Font::GetCharacterCount() {
	return m_characterCount;
}

int Font::GetCharacterWidth() {
	return m_characterWidth;
}

int Font::GetCharacterHeight() {
	return m_characterHeight;
}

ImageBuffer* Font::GetImageBuffer() {
	return m_imageBuffer;
}

int Font::FindIndex(const char* characters, int length, char c)
{
	const char* end = characters + length;
	const char* match = std::find(characters, end, c);
	return (end == match) ? -1 : (match - characters);
}