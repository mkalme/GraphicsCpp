#include "../../../Header/Gui/Font/FontPainter.h"
#include <vector>

FontPainter::FontPainter(Font* fontToPaint) {
	FontToPaint = fontToPaint;
}

void FontPainter::PaintLine(const std::string characters, int x, int y, ImageBuffer* buffer, FontSettings fontSettings) {
	for (int i = 0; i < characters.size(); i++) {
		PaintCharacter(characters[i], x + i * (FontToPaint->GetCharacterWidth() + fontSettings.CharacterSpacing) * fontSettings.Scale, y, buffer, fontSettings);
	}
}

void FontPainter::Paint(const std::string characters, int x, int y, ImageBuffer* buffer, FontSettings fontSettings) {
	int start = 0;
	for (int i = 0; i < characters.size(); i++) {
		if (characters[i] != '\n') continue;

		std::string substring = characters.substr(start, i - start);
		start = i + 1;

		PaintLine(substring, x, y, buffer, fontSettings);
		y += (FontToPaint->GetCharacterHeight() + fontSettings.LineSpacing) * fontSettings.Scale;
	}

	if (characters.size() - start > 0) {
		std::string substring = characters.substr(start, characters.size() - start);
		PaintLine(substring, x, y, buffer, fontSettings);
	}
}

void FontPainter::PaintRichText(RichText text, int x, int y, ImageBuffer* buffer) {
	int xp = x, yp = y;

	for (int i = 0; i < text.Segments.size(); i++) {
		RichFontSegment segment = text.Segments[i];
		FontSettings settings;
		settings.Foreground = segment.Foreground;
		settings.Background = segment.Background;
		settings.LineSpacing = text.LineSpacing;
		settings.CharacterSpacing = text.CharacterSpacing;
		settings.Scale = text.Scale;

		for (int j = 0; j < segment.Text.size(); j++) {
			char c = segment.Text[j];
			if (c == '\n') {
				xp = x;
				yp += (FontToPaint->GetCharacterHeight() + text.LineSpacing) * text.Scale;

				continue;
			}

			if (!settings.Background.IsEmpty()) {
				int areaX = xp - text.Scale * settings.CharacterSpacing;
				int areaY = yp - text.Scale * settings.LineSpacing;
				int areaW = FontToPaint->GetCharacterWidth() * text.Scale + text.Scale * settings.CharacterSpacing * 2;
				int areaH = FontToPaint->GetCharacterHeight() * text.Scale + text.Scale * settings.LineSpacing * 2;

				PaintArea(buffer, settings.Background, areaX, areaY, areaW, areaH);
			}

			PaintCharacter(c, xp, yp, buffer, settings);
			xp += (FontToPaint->GetCharacterWidth()) * text.Scale;

			xp += settings.CharacterSpacing * text.Scale;
		}
	}
}

void FontPainter::PaintCharacter(char character, int x, int y, ImageBuffer* buffer, FontSettings settings){
	int cx, cy;
	FontToPaint->GetCharacterLocation(character, cx, cy);
	if (cx < 0 || cy < 0) return;

	for (int iy = 0; iy < FontToPaint->GetCharacterHeight(); iy++) {
		for (int ix = 0; ix < FontToPaint->GetCharacterWidth(); ix++) {
			if (FontToPaint->GetImageBuffer()->GetPixel(cx + ix, cy + iy) == MaskColor) continue;

			PaintPixel(buffer, settings.Foreground, x + (ix * settings.Scale), y + (iy * settings.Scale), settings.Scale);
		}
	}
}

void FontPainter::PaintPixel(ImageBuffer* buffer, Vec3f color, int x, int y, int scaling) {
	for (int scaleY = 0; scaleY < scaling; scaleY++) {
		for (int scaleX = 0; scaleX < scaling; scaleX++) {
			int xp = x + scaleX;
			int yp = y + scaleY;

			buffer->SetPixel(xp, yp, color);
		}
	}
}

void FontPainter::PaintArea(ImageBuffer* buffer, Vec3f color, int x, int y, int width, int height) {
	for (int yp = 0; yp < height; yp++) {
		for (int xp = 0; xp < width; xp++) {
			buffer->SetPixel(xp + x, yp + y, color);
		}
	}
}