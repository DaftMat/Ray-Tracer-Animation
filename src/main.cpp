#include <iostream>

#define STB_IMAGE_IMPLEMENTATION

#include "Application/Application.hpp"

Application app(1080, 1080);

int main() {
    app.Run();
    return 0;
}

void Application::m_mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    app.mouse_callback(xpos, ypos);
}