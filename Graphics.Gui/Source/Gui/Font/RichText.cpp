#include "../../../Header/Gui/Font/RichText.h"

RichText& RichText::Add(RichFontSegment text) {
	Segments.push_back(text);
	return *this;
}

RichText& RichText::AddLine(RichFontSegment text) {
	text.Text = std::string(text.Text).append("\n");
	
	Segments.push_back(text);
	return *this;
}