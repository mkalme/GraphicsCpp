#pragma once
#include "../Header/Utilities/ImageBuffer/ImageBuffer.h"
#include <string>

class Font
{
public:
	Font(ImageBuffer* imageBuffer, const char* characters, int characterWidth, int characterHeight);

	const char* GetCharacters();
	int GetCharacterCount();
	int GetCharacterWidth();
	int GetCharacterHeight();
	ImageBuffer* GetImageBuffer();

	void GetCharacterLocation(char character, int &x, int &y);
private:
	const char* m_characters;
	int m_characterCount;
	int m_characterWidth;
	int m_characterHeight;
	ImageBuffer* m_imageBuffer;

	int FindIndex(const char* characters, int length, char c);
};

