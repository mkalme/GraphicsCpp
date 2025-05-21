#pragma once
#include <glew.h>
#include <glfw3.h>

class Window
{
public:
	Window(int width, int height);
	
	void Update();
	unsigned char* GetImageBuffer();
	GLFWwindow* GetWindow();

	int GetWidth();
	int GetHeight();

	void Close();
private:
	int _width;
	int _height;
	unsigned char* _imageBuffer;

	void Setup();
	GLuint CreateTexture();
};

