#pragma once
#include "Font.h"
#include "FontSettings.h"
#include "RichText.h"
#include <string>

class FontPainter
{
public:
	Font* FontToPaint;
	Vec3f MaskColor = Vec3f(1);

	FontPainter(Font* fontToPaint);

	virtual void PaintLine(const std::string characters, int x, int y, ImageBuffer* buffer, FontSettings fontSettings);
	virtual void Paint(const std::string characters, int x, int y, ImageBuffer* buffer, FontSettings fontSettings);
	virtual void PaintRichText(RichText text, int x, int y, ImageBuffer* buffer);
protected:
	virtual void PaintCharacter(char character, int x, int y, ImageBuffer* buffer, FontSettings settings);
	virtual void PaintPixel(ImageBuffer* buffer, Vec3f color, int x, int y, int scaling);
	virtual void PaintArea(ImageBuffer* buffer, Vec3f color, int x, int y, int width, int height);
};

