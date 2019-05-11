//
// Created by mathis on 12/05/19.
//

#ifndef RAY_TRACING_ANIMATION_ORTHOCAMERA_HPP
#define RAY_TRACING_ANIMATION_ORTHOCAMERA_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

const float YAW = -90.f;
const float PITCH = 0.0f;
const float SENSITIVITY = 0.1f;

class OrthoCamera {
    ///Camera settings
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;

    ///Euler angles
    float m_yaw;
    float m_pitch;

    float m_mouseSensitivity;

    void updateCameraVectors();

public:
    ///Default constructor
    OrthoCamera(glm::vec3 position = glm::vec3(0.f, 0.f, 3.f), glm::vec3 up = glm::vec3(0.f, 1.f, 0.f), float yaw = YAW, float pitch = PITCH);

    ///Settable constructor
    OrthoCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    /**
     * Applies lookAt function
     * @return view matrix
     */
    glm::mat4 getView();

    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

    glm::vec3 getPos() {return m_position;}
    glm::vec3 getDir() {return m_front; }
};


#endif //RAY_TRACING_ANIMATION_ORTHOCAMERA_HPP
