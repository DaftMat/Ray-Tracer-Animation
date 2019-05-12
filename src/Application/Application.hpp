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
#include "../Cameras/Camera.hpp"
#include "../Lights/PointLight.hpp"

#include <vector>

struct RenderObject {
    unsigned int shader;    //shader index in the application
    unsigned int model;     //model that is printed
};

class Application {
    float screenWidth;
    float screenHeight;

    float m_deltaTime {0.f};
    float m_lastFrame {0.f};
    float m_refreshTime {0.f};

    bool m_firstMouse {true};

    float lastX;
    float lastY;

    unsigned int lightShader;

    GLFWwindow *m_window;

    std::vector<Shader> shaders;
    std::vector<Model> models;
    std::vector<PointLight> pointLights;
    std::vector<RenderObject> objects;

    Camera camera;

    bool error {false};

    //callbacks
    void processInput();
    void mouse_callback(double xpos, double ypos);

    static void m_mouse_callback(GLFWwindow *window, double xpos, double ypos);

public:
    Application(float screenWidth, float screenHeight);
    ~Application();

    void addShader(Shader &shader) {shaders.emplace_back(shader);}
    void addModel(Model &model, unsigned int shaderIndex);
    void addPointLight(PointLight &light);

    void setLightShaderIndex(unsigned int index)    {lightShader = index;}

    void Run();
};



#endif //RAY_TRACING_ANIMATION_APPLICATION_HPP
