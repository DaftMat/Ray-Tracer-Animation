#include <iostream>

#define STB_IMAGE_IMPLEMENTATION

#include "Application/Application.hpp"

Application app(1080, 1080);

int main() {
    //Configure shaders
    Shader lightingShader("../src/Shaders/shaders/lighting.vertex", "../src/Shaders/shaders/lighting.fragment");
    lightingShader.use();

    lightingShader.setWireframe(false);

    app.addShader(lightingShader);


    Shader borderShader("../src/Shaders/shaders/border.vertex", "../src/Shaders/shaders/border.fragment");
    borderShader.use();

    borderShader.setVec3f("color", .8f, .8f, .8f);
    borderShader.setWireframe(true);

    app.addShader(borderShader);

    //Configure light
    app.setLightShaderIndex(1);

    PointLight light(glm::vec3(0.0f, 1.f, 1.f), .2f, .2f, .2f, glm::vec3(.2f, .2f, .2f), glm::vec3(1.f, 1.f, 1.f), glm::vec3(.6f, .6f, .6f));
    app.addPointLight(light);

    Model pyramid(PYRAMID, 10);
    pyramid.setTransform(glm::translate(pyramid.getTransform(), glm::vec3(0.f, 0.2f, .0f)));
    pyramid.setTransform(glm::rotate(pyramid.getTransform(), glm::radians(45.f), glm::vec3(0.f, 0.f, 1.f)));
    pyramid.setTransform(glm::translate(pyramid.getTransform(), glm::vec3(0.f, 1.f, .0f)));
    pyramid.setTransform(glm::scale(pyramid.getTransform(), glm::vec3(.1f, .4f, .2f)));

    Model sphere(SPHERE, 26);
    sphere.setTransform(glm::scale(sphere.getTransform(), glm::vec3(.2f, .2f, .2f)));
    sphere.setTransform(glm::translate(sphere.getTransform(), glm::vec3(0.f, 1.f, .0f)));
    Material matSphere;
    matSphere.pngTex = false;
    matSphere.specTex = false;
    matSphere.diffTex = false;
    matSphere.diffuse = glm::vec3(.4f, .4f, .4f);
    matSphere.specular = glm::vec3(.6f, .6f, .6f);

    Model line(glm::normalize(glm::vec3(-1.f, 1.f, 0.f)) + glm::normalize(glm::vec3(-1.f, 1.f, 0.f)) * 0.4f + glm::vec3(0.f, .2f, 0.f), glm::vec3(0.f, .2f, 0.f) + glm::normalize(glm::vec3(-1.f, 1.f, 0.f)) * 0.2f);
    Model line2(glm::vec3(0.f, .2f, 0.f) + glm::normalize(glm::vec3(-1.f, 1.f, 0.f)) * 0.2f, light.getLight().position);

    app.addModel(sphere, 0);
    app.addModel(pyramid, 1);
    app.addModel(line, 1);
    app.addModel(line2, 1);


    //run animation
    app.Run();

    return 0;
}

void Application::m_mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    app.mouse_callback(xpos, ypos);
}