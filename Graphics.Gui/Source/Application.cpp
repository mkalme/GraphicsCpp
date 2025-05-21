#include "../Header/Application.h"
#include "../Header/Renderer/Renderer.h"
#include "../Header/Gui/Window.h"
#include "../Header/Gui/FirstPerson/DirectionalInertia.h"
#include "../Header/Gui/FirstPerson/Inertia.h"
#include "../Header/Scene/Scene.h"
#include "../Header/Math/Vec3f.h"
#include "../Header/Math/Rotation.h"
#include "../Header/Utilities/ImageBuffer/GlfwImageBuffer.h"
#include "../Header/Utilities/ImageBuffer/StbImageBuffer.h"
#include "../Header/Utilities/ImageBuffer/ScaledImageBuffer.h"
#include <chrono>
#include <iomanip>
#include <map>
#include <sstream>
#include <iostream>
#include <fstream>
#include "../Header/Gui/Font/Font.h"
#include "../Header/Gui/Font/FontPainter.h"
#include "../Header/Gui/Font/RichText.h"
#include "../Header/External/json.hpp"
#include "Serializer/SerializerCatalog.h"
#include <Serializer/Scene/SceneSerializer.h>
#include <random>
#include "../Header/Gui/PngSaver.h"

static void CheckKeys(std::chrono::duration<double> deltaTime);
static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
void SetCursorToMiddle(GLFWwindow* window);
Vec3f GetAverageColor(ImageBuffer* buffer);
void DrawCross(ImageBuffer* buffer, int size);

Window* window;
Scene* scene;
Renderer* renderer;

ImageBuffer* renderBuffer;

Rotation rightRotation = Rotation::FromDegrees(90);
Rotation leftRotation = Rotation::FromDegrees(-90);

Vec3f newPos, newDir;
Inertia inertia;

std::map<int, int> pressedKeyMap = {};
bool initialized = false;

std::string lastScreenshot;

void Application::Start() {
	std::ifstream t("scene_path.txt");
	std::stringstream buffer;
	buffer << t.rdbuf();

	std::string directory;
	const size_t last_slash_idx = buffer.str().rfind('\\');
	if (std::string::npos != last_slash_idx)
	{
		directory = buffer.str().substr(0, last_slash_idx);
	}

	window = new Window(1000, 1000);
	std::ifstream ifs(buffer.str());
	nlohmann::json jf = nlohmann::json::parse(ifs);

	SerializerCatalog* catalog = new SerializerCatalog();
	SceneSerializer serializer = SceneSerializer(catalog);
	catalog->CurrentDirectory->Item = std::string(directory);
	scene = serializer.Deserialize(jf);

	Font* font = new Font(new StbImageBuffer("Assets\\Font\\G.png"), "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-+/\\.,():;%=!? <>", 5, 7);
	FontPainter fontPainter = FontPainter(font);

	renderBuffer = new GlfwImageBuffer(window->GetWidth(), window->GetHeight(), window->GetImageBuffer());
	ImageBuffer* fontBuffer = renderBuffer;

	RenderSettings settings = RenderSettings();

	scene->CameraObj->SetDimensions(renderBuffer->GetWidth(), renderBuffer->GetHeight());
    renderer = new Renderer(scene, renderBuffer, settings);
	renderer->StartAsync();

	glfwSetCursorPos(window->GetWindow(), window->GetWidth() / 2, window->GetHeight() / 2);
	glfwSetInputMode(window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetKeyCallback(window->GetWindow(), KeyCallback);
	glfwSetCursorPosCallback(window->GetWindow(), MouseCallback);

	auto lastTimeFps = std::chrono::system_clock::now();
	auto lastTime = std::chrono::system_clock::now();
	int count = 0, lastCount = 0;
	double _seconds = 0, totalFps = 0;
	initialized = true;

	newPos = scene->CameraObj->Origin;
	newDir = scene->CameraObj->Direction;

	while (!glfwWindowShouldClose(window->GetWindow())) {
		renderer->Render();

		if (renderer->GetSettings().Vignette.Enabled) {
			Vec3f yellow = FontSettings().Foreground;
			Vec3f white = Vec3f(1);

			RichText info = RichText();
			info.Add(RichFontSegment(std::string("FPS: "), yellow));
			info.Add(RichFontSegment(std::to_string(lastCount), white));
			info.Add(RichFontSegment(std::string("  AVERAGE FPS: "), yellow));
			info.Add(RichFontSegment(std::to_string((int)(_seconds == 0 ? 0 : totalFps / _seconds)), white));
			info.Add(RichFontSegment(std::string("  SECONDS: "), yellow));
			info.AddLine(RichFontSegment(std::to_string((int)_seconds), white));

			info.Add(RichFontSegment(std::string("SCALE: "), yellow));
			info.AddLine(RichFontSegment(std::to_string(renderer->GetSettings().Scale), white));

			info.Add(RichFontSegment(std::string("X"), Vec3f(1, 0, 0)));
			info.Add(RichFontSegment(std::string("Y"), Vec3f(0, 1, 0)));
			info.Add(RichFontSegment(std::string("Z"), Vec3f(0.03125, 0.6, 0.9375)));
			info.Add(RichFontSegment(std::string(": "), yellow));
			std::string coords = std::string("<").append(std::to_string(scene->CameraObj->Origin.X)).append("; ")
				.append(std::to_string(scene->CameraObj->Origin.Y)).append("; ")
				.append(std::to_string(scene->CameraObj->Origin.Z)).append(">");
			info.AddLine(RichFontSegment(coords, white));

			fontPainter.PaintRichText(info, 20, 20, fontBuffer);

			if (!lastScreenshot.empty()) {
				RichText chat = RichText();
				chat.Add(RichFontSegment(std::string("SCREENSHOT SAVED AS: "), Vec3f(0, 204 / 255.0, 204 / 255.0)));

				std::transform(lastScreenshot.begin(), lastScreenshot.end(), lastScreenshot.begin(), ::toupper);
				chat.Add(RichFontSegment(lastScreenshot, white));

				fontPainter.PaintRichText(chat, 20, renderBuffer->GetHeight() - 20 - fontPainter.FontToPaint->GetCharacterHeight() * chat.Scale, fontBuffer);
			}

			DrawCross(renderBuffer, 36);
		}

		window->Update();

		glfwPollEvents();

		std::chrono::system_clock::time_point currentTime = std::chrono::system_clock::now();
		std::chrono::duration<double> deltaTime = (currentTime - lastTime);

		CheckKeys(deltaTime);
		lastTime = currentTime;

		scene->CameraObj->Origin = newPos;
		scene->CameraObj->Direction = newDir;

		count++;
		if ((currentTime - lastTimeFps).count() >= 2000000) {
			double seconds = (currentTime - lastTimeFps).count() / 10000000.0;

			lastCount = count / seconds;
			lastTimeFps = currentTime;

			_seconds += seconds;
			totalFps += count;

			count = 0;
		}
	}
}

static void CheckKeys(std::chrono::duration<double> deltaTime) {
	if (pressedKeyMap[GLFW_KEY_ESCAPE] != GLFW_RELEASE) {
		glfwSetWindowShouldClose(window->GetWindow(), GL_TRUE);
		return;
	}

	bool turbo = pressedKeyMap[GLFW_KEY_LEFT_CONTROL] != GLFW_RELEASE;
	float coefficient = turbo ? 2.5 : 1;
	inertia.SetCoefficients(coefficient);

	Vec3f dir = 0;

	Vec3f horizontalDirection = Vec3f(0);
	bool pressedHorizontal = false;

	Vec3f forwardDir = scene->CameraObj->Direction;
	forwardDir.Y = 0;
	forwardDir = forwardDir.Normal();
	if (pressedKeyMap[GLFW_KEY_W] != GLFW_RELEASE) {
		horizontalDirection = horizontalDirection + forwardDir;
		pressedHorizontal = true;
	}

	Vec3f backwardDir = scene->CameraObj->Direction * -1;
	backwardDir.Y = 0;
	backwardDir = backwardDir.Normal();
	if (pressedKeyMap[GLFW_KEY_S] != GLFW_RELEASE){
		horizontalDirection = horizontalDirection + backwardDir;
		pressedHorizontal = true;
	}

	Vec3f leftDir = Vec3f(scene->CameraObj->Direction.X, 0, scene->CameraObj->Direction.Z).Normal();
	leftRotation.Rotate(leftDir.X, leftDir.Z);
	if (pressedKeyMap[GLFW_KEY_A] != GLFW_RELEASE){
		horizontalDirection = horizontalDirection + leftDir;
		pressedHorizontal = true;
	}

	Vec3f rightDir = Vec3f(scene->CameraObj->Direction.X, 0, scene->CameraObj->Direction.Z).Normal();
	rightRotation.Rotate(rightDir.X, rightDir.Z);
	if (pressedKeyMap[GLFW_KEY_D] != GLFW_RELEASE){
		horizontalDirection = horizontalDirection + rightDir;
		pressedHorizontal = true;
	}

	if (pressedHorizontal && horizontalDirection.Length() > 0.001) {
		inertia.Horizontal.SpeedUp(deltaTime.count(), horizontalDirection.Normal());
	}else {
		inertia.Horizontal.SlowDown();
	}

	Vec3f verticalDirection = Vec3f(0);
	bool pressedVertical = false;

	Vec3f upDir = Vec3f(0, 1, 0);
	if (pressedKeyMap[GLFW_KEY_SPACE] != GLFW_RELEASE){
		verticalDirection = verticalDirection + upDir;
		pressedVertical = true;
	}

	Vec3f downDir = Vec3f(0, -1, 0);
	if (pressedKeyMap[GLFW_KEY_LEFT_SHIFT] != GLFW_RELEASE){
		verticalDirection = verticalDirection + downDir;
		pressedVertical = true;
	}

	if (pressedVertical && verticalDirection.Length() > 0.001) {
		inertia.Vertical.SpeedUp(deltaTime.count(), verticalDirection.Normal());
	}
	else {
		inertia.Vertical.SlowDown();
	}

	Vec3f velocity = inertia.GetTotalVelocity(deltaTime.count());
	newPos = scene->CameraObj->Origin.Add(velocity);
}

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	pressedKeyMap[key] = action;

	if (pressedKeyMap[GLFW_KEY_LEFT_CONTROL] != GLFW_RELEASE && key == GLFW_KEY_EQUAL && action == GLFW_RELEASE) {
		RenderSettings settings = renderer->GetSettings();
		settings.Scale++;
		renderer->SetSettings(settings);
	}

	if (pressedKeyMap[GLFW_KEY_LEFT_CONTROL] != GLFW_RELEASE && key == GLFW_KEY_MINUS && action == GLFW_RELEASE) {		
		RenderSettings settings = renderer->GetSettings();
		if (settings.Scale <= 1) return;

		settings.Scale--;
		renderer->SetSettings(settings);
	}

	if (pressedKeyMap[GLFW_KEY_F1] != GLFW_RELEASE) {
		RenderSettings settings = renderer->GetSettings();
		settings.Vignette.Enabled = !settings.Vignette.Enabled;
		renderer->SetSettings(settings);
	}

	if (pressedKeyMap[GLFW_KEY_F2] != GLFW_RELEASE) {
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		time_t tt = std::chrono::system_clock::to_time_t(now);
		tm local_tm = *localtime(&tt);

		std::stringstream ss;
		ss << std::to_string(local_tm.tm_year + 1900) << "-";
		ss << std::setfill('0') << std::setw(2);
		ss << std::to_string(local_tm.tm_mon + 1) << "-";
		ss << std::setfill('0') << std::setw(2);
		ss << std::to_string(local_tm.tm_mday) << "_";
		ss << std::setfill('0') << std::setw(2);
		ss << std::to_string(local_tm.tm_hour) << ".";
		ss << std::setfill('0') << std::setw(2);
		ss << std::to_string(local_tm.tm_min) << ".";
		ss << std::setfill('0') << std::setw(2);
		ss << std::to_string(local_tm.tm_sec) << ".png";

		std::string fileName("Screenshots/");
		fileName.append(ss.str());

		PngSaver::Save(renderBuffer, fileName);
		lastScreenshot = ss.str();
	}
}

static void MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	if (initialized) {
		double k = 500.0;

		double movedX = xpos - width / 2;
		double movedY = ypos - height / 2;

		Vec3f dir = scene->CameraObj->Direction;

		double hl = sqrt(dir.X * dir.X + dir.Z * dir.Z);
		double angle = atan2(hl, dir.Y);
		double vAngle = -movedY / k;

		if (angle - vAngle >= Rotation::PI()) {
			const double eps = -(Rotation::PI() * 0.99999);
			vAngle = eps + angle;
		}else if (angle - vAngle <= 0.0000001) {
			vAngle = 0;
		}

		Rotation hRotation = Rotation(movedX / k);
		Rotation vRotation = Rotation(vAngle);

		Rotation::RotateVector(dir, hRotation, vRotation);

		newDir = dir.Normal();
	}

	SetCursorToMiddle(window);
}

void SetCursorToMiddle(GLFWwindow* window) {
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	glfwSetCursorPos(window, width / 2, height / 2);
}

Vec3f GetAverageColor(ImageBuffer* buffer) {
	Vec3f output = Vec3f(0);
	
	for (int y = 0; y < buffer->GetHeight(); y++) {
		for (int x = 0; x < buffer->GetWidth(); x++) {
			output = output.Add(buffer->GetPixel(x, y));
		}
	}

	return output / (buffer->GetWidth() * buffer->GetHeight());
}

void DrawCross(ImageBuffer* buffer, int size) {
	const int thickness = 4;

	int xO = (buffer->GetWidth() - size) / 2;
	int yO = (buffer->GetHeight() - size) / 2;

	for (int y = 0; y < size; y++) {
		for (int x = 0; x < thickness; x++) {
			Vec2f xz = Vec2f(xO + x + size / 2 - thickness / 2, yO + y);

			Vec3f p = buffer->GetPixel(xz.X, xz.Y);
			p = Vec3f(1 - p.X, 1 - p.Y, 1 - p.Z);
			buffer->SetPixel(xz.X, xz.Y, p);
		}
	}

	for (int x = 0; x < size; x++) {
		for (int y = 0; y < thickness; y++) {
			Vec2f xz = Vec2f(xO + x, yO + y - thickness / 2 + size / 2);

			int v0 = xO + size / 2 - thickness / 2, v1 = v0 + thickness;
			if (xz.X >= v0 && xz.X < v1) continue;

			Vec3f p = buffer->GetPixel(xz.X, xz.Y);
			p = Vec3f(1 - p.X, 1 - p.Y, 1 - p.Z);
			buffer->SetPixel(xz.X, xz.Y, p);
		}
	}
}

void Application::End() {
	window->Close();

	delete this;
}