#include <iostream>

#define STB_IMAGE_IMPLEMENTATION

#include "Application/Application.hpp"

Application app(1080, 1080);

int main() {
    Shader lightingShader("../src/Shaders/shaders/lighting.vertex", "../src/Shaders/shaders/lighting.fragment");
    //Edit shader
    lightingShader.use();

    //add dir light
    lightingShader.setVec3f("pointLights[0].position", 0.0f, 1.f, 1.0f);
    lightingShader.setVec3f("pointLights[0].ambient", 0.2f, 0.2f, 0.2f);
    lightingShader.setVec3f("pointLights[0].diffuse", 1.0f, 1.0f, 1.0f);
    lightingShader.setVec3f("pointLights[0].specular", 1.f, 1.0f, 1.0f);
    lightingShader.setFloat("pointLights[0].constant", .2f);
    lightingShader.setFloat("pointLights[0].linear", .2f);
    lightingShader.setFloat("pointLights[0].quadratic", .2f);
    lightingShader.setWireframe(false);

    app.addShader(lightingShader);

    Shader borderShader("../src/Shaders/shaders/border.vertex", "../src/Shaders/shaders/border.fragment");
    borderShader.use();
    borderShader.setVec3f("color", .8f, .8f, .8f);
    borderShader.setWireframe(true);

    app.addShader(borderShader);

    Model pyramid(PYRAMID, 10);
    pyramid.setTransform(glm::translate(pyramid.getTransform(), glm::vec3(0.f, 0.2f, .0f)));
    pyramid.setTransform(glm::rotate(pyramid.getTransform(), glm::radians(45.f), glm::vec3(0.f, 0.f, 1.f)));
    pyramid.setTransform(glm::translate(pyramid.getTransform(), glm::vec3(0.f, 1.f, .0f)));
    pyramid.setTransform(glm::scale(pyramid.getTransform(), glm::vec3(.1f, .4f, .2f)));

    Model sphere(SPHERE, 26);
    sphere.setTransform(glm::scale(sphere.getTransform(), glm::vec3(.2f, .2f, .2f)));
    sphere.setTransform(glm::translate(sphere.getTransform(), glm::vec3(0.f, 1.f, .0f)));

    Model sphere2(SPHERE, 26);
    sphere2.setTransform(glm::scale(sphere2.getTransform(), glm::vec3(.2f, .2f, .2f)));
    sphere2.setTransform(glm::translate(sphere2.getTransform(), glm::vec3(0.f, 1.f, 2.2f)));

    app.addModel(sphere, 0);
    app.addModel(sphere2, 0);
    app.addModel(pyramid, 1);

    //run animation
    app.Run();

    return 0;
}

void Application::m_mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    app.mouse_callback(xpos, ypos);
}