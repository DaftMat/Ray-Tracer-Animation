//
// Created by mathis on 12/05/19.
//

#include "Application.hpp"

Application::Application(float screenWidth, float screenHeight) : lastX(screenWidth), lastY(screenHeight) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 32);

    //Window initialization
    m_window = glfwCreateWindow(unsigned(screenWidth), unsigned(screenHeight), "Learn OpenGL", NULL, NULL);
    if (m_window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        error = true;
    }
    glfwMakeContextCurrent(m_window);

    //GLAD initialization
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "failed to initialize GLAD" << std::endl;
        error = true;
    }

    glViewport(0,0,(int)screenWidth,(int)screenHeight);

    //lock mouse
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //set mouse move event
    glfwSetCursorPosCallback(m_window, m_mouse_callback);

    glEnable(GL_MULTISAMPLE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);
}

void Application::addModel(const Model &model, unsigned int shaderIndex) {
    RenderObject ro;
    ro.index = shaderIndex;
    ro.model = model;
    objects.emplace_back(ro);
}

void Application::Run() {
    while (!error && !glfwWindowShouldClose(m_window)) {
        ///deltatime update
        float currentFrame = glfwGetTime();
        m_deltaTime = currentFrame - m_lastFrame;
        m_lastFrame = currentFrame;

        ///fps counter update
        if (m_refreshTime >= 1.f)   {
            glfwSetWindowTitle(m_window, ("FPS : " + std::to_string(int(1.f / m_deltaTime))).c_str());
            m_refreshTime = 0.f;
        }
        m_refreshTime += m_deltaTime;

        processInput();

        glClearColor(.2f, .2f, .2f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ///Draw all objects :
        for (auto & ro : objects) {
            shaders[ro.index].use();

            shaders[ro.index].setMat4f("view", camera.getView());
            shaders[ro.index].setMat4f("model", ro.model.getTransform());

            ro.model.Draw(shaders[ro.index]);
        }

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    glfwTerminate();
}

void Application::processInput() {
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, true);
}

void Application::mouse_callback(double xpos, double ypos) {
    if (m_firstMouse) {
        lastX = xpos;
        lastY = ypos;
        m_firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.processMouseMovement(xoffset, yoffset);
}