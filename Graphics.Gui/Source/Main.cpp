#include "../Header/Application.h"

int main() {
    Application* application = new Application();
    application->Start();
    application->End();

	return 0;
}
