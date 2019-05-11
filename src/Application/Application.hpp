//
// Created by mathis on 12/05/19.
//

#ifndef RAY_TRACING_ANIMATION_APPLICATION_HPP
#define RAY_TRACING_ANIMATION_APPLICATION_HPP

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Shaders/Shader.hpp"
#include "../Shape/Model.hpp"
#include "../Cameras/OrthoCamera.hpp"

#include <vector>

struct RenderObject {
    unsigned int index; //shader index in the application
    Model model;        //model that is printed
};

class Application {
    float m_deltaTime {0.f};
    float m_lastFrame {0.f};
    float m_refreshTime {0.f};

    bool m_firstMouse {true};

    float lastX;
    float lastY;

    GLFWwindow *m_window;

    std::vector<Shader> shaders;
    std::vector<RenderObject> objects;

    OrthoCamera camera;

    bool error {false};

    //callbacks
    void processInput();
    void mouse_callback(double xpos, double ypos);

    static void m_mouse_callback(GLFWwindow *window, double xpos, double ypos);

public:
    Application(float screenWidth, float screenHeight);

    void addShader(Shader shader) {shaders.emplace_back(shader);}
    void addModel(const Model &model, unsigned int shaderIndex);

    void Run();
};



#endif //RAY_TRACING_ANIMATION_APPLICATION_HPP
