#pragma once
#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../External/stb_image_write.h"
#include <Utilities/ImageBuffer/ImageBuffer.h>
#include <string>

class PngSaver
{
public:
	static void Save(ImageBuffer* buffer, std::string outputPath) {
		char* data = (char*)malloc(buffer->GetWidth() * buffer->GetHeight() * 4);
		
		for (int y = 0; y < buffer->GetHeight(); y++) {
			for (int x = 0; x < buffer->GetWidth(); x++) {
				Vec3f pixel = buffer->GetPixel(x, y);

				data[(y * buffer->GetWidth() + x) * 4] = (unsigned char)(pixel.X * 255);
				data[(y * buffer->GetWidth() + x) * 4 + 1] = (unsigned char)(pixel.Y * 255);
				data[(y * buffer->GetWidth() + x) * 4 + 2] = (unsigned char)(pixel.Z * 255);
				data[(y * buffer->GetWidth() + x) * 4 + 3] = (unsigned char)(255);
			}
		}

		stbi_write_png(outputPath.c_str(), buffer->GetWidth(), buffer->GetHeight(), 4, data, buffer->GetWidth() * 4);
	
		delete data;
	}
};

