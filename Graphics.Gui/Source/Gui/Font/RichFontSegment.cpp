#include "../../../Header/Gui/Font/RichFontSegment.h"

RichFontSegment::RichFontSegment(std::string text, Vec3f foreground, Vec3f background) {
	Text = text;
	Foreground = foreground;
	Background = background;
}

RichFontSegment::RichFontSegment(std::string text, Vec3f foreground) {
	Text = text;
	Foreground = foreground;
	Background = Vec3f(0.25);
}