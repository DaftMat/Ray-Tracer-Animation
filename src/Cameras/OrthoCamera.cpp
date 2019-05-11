//
// Created by mathis on 12/05/19.
//

#include "OrthoCamera.hpp"

OrthoCamera::OrthoCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : m_front(glm::vec3(0.0f, 0.0f, -1.0f)), m_mouseSensitivity(SENSITIVITY) {
    m_position = position;
    m_worldUp = up;
    m_yaw = yaw;
    m_pitch = pitch;
    updateCameraVectors();
}

OrthoCamera::OrthoCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : m_front(glm::vec3(0.0f, 0.0f, -1.0f)), m_mouseSensitivity(SENSITIVITY) {
    m_position = glm::vec3(posX, posY, posZ);
    m_worldUp = glm::vec3(upX, upY, upZ);
    m_yaw = yaw;
    m_pitch = pitch;
    updateCameraVectors();
}

glm::mat4 OrthoCamera::getView() {
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

void OrthoCamera::processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
    xoffset *= m_mouseSensitivity;
    yoffset *= m_mouseSensitivity;

    m_yaw += xoffset;
    m_pitch += yoffset;

    if (constrainPitch) {
        if (m_pitch >  89.f)    m_pitch =  89.f;
        if (m_pitch < -89.f)    m_pitch = -89.f;
    }

    updateCameraVectors();
}

void OrthoCamera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = front;
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}