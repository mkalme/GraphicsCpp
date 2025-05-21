#include "../../Header/Gui/Window.h"
#include <glew.h>
#include <glfw3.h>
#include <iostream>

const char* vertexShaderSource = R"(
    #version 440 core
    layout (location = 0) in vec2 position;
    out vec2 TexCoords;
    void main() {
        TexCoords = position * 0.5 + 0.5;
        gl_Position = vec4(position, 0.0, 1.0);
    }
)";

const char* fragmentShaderSource = R"(
    #version 440 core
    in vec2 TexCoords;
    out vec4 FragColor;
    uniform sampler2D imageTexture;
    void main() {
        FragColor = texture(imageTexture, TexCoords);
    }
)";

GLFWwindow* window;
GLuint shaderProgram;
GLuint quadVAO, quadVBO;
GLuint lastTexture;
GLuint vertexShader, fragmentShader;

Window::Window(int width, int height) {
	_width = width;
	_height = height;
	_imageBuffer = new unsigned char[width * height * 4];

    Setup();
    Update();
}

void Window::Setup() {
    glfwInit();

    int frameBufferWidth = 0, frameBufferHeight = 0;

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    int count;
    int monitorX, monitorY;

    GLFWmonitor** monitors = glfwGetMonitors(&count);
    const GLFWvidmode* videoMode = glfwGetVideoMode(monitors[0]);
    glfwGetMonitorPos(monitors[0], &monitorX, &monitorY);

    window = glfwCreateWindow(_width, _height, "Graphics", NULL, NULL);
    glfwSetWindowPos(window, monitorX + (videoMode->width - _width) / 2, monitorY + (videoMode->height - _height) / 2);

    glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
    glViewport(0, 0, frameBufferWidth, frameBufferHeight);
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        std::cout << "ERROR::MAIN.CPP::GLEW_INIT_FAILED" << "\n";
        glfwTerminate();
    }

    // Vertex Shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Fragment Shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Shader Program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Create a quad
    float quadVertices[] = {
        -1.0f, -1.0f,
         1.0f, -1.0f,
        -1.0f,  1.0f,
         1.0f,  1.0f,
    };

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glBindVertexArray(0);
}

GLuint Window::CreateTexture() {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _imageBuffer);
    glGenerateMipmap(GL_TEXTURE_2D);

    return texture;
}

void Window::Update() {
    glDeleteTextures(1, &lastTexture);
    lastTexture = CreateTexture();

    glUseProgram(shaderProgram);
    glBindVertexArray(quadVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, lastTexture);
    glUniform1i(glGetUniformLocation(shaderProgram, "imageTexture"), 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);

    glfwSwapBuffers(window);

    glfwPollEvents();
}

int Window::GetWidth() {
    return _width;
}

int Window::GetHeight() {
    return _height;
}

unsigned char* Window::GetImageBuffer() {
	return _imageBuffer;
}
GLFWwindow* Window::GetWindow() {
    return window;
}

void Window::Close() {
    delete _imageBuffer;

    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadVBO);
    glDeleteTextures(1, &lastTexture);
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    glfwTerminate();

    delete this;
}
