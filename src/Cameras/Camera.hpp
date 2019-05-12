//
// Created by daftmat on 01/05/19.
//

#ifndef OPENGLTUTO_CAMERA_HPP
#define OPENGLTUTO_CAMERA_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

//Camera movement options
enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

//Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.f;

class Camera {
    //Camera attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    //Euler angles
    float yaw;
    float pitch;

    //Camera options
    float moveSpeed;
    float mouseSensitivity;
    float zoom;

    ///Calculates the front vector from the camera's (updated) euler angles
    void updateCameraVectors();

public:
    ///constructor with vedtors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

    ///constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    /**
     * applies lookAt function
     * @return view matrix
     */
    glm::mat4 getView();

    /**
     * Processes input received from any key associated with the CameraMovement's value
     * @param direction direction to move
     * @param deltaTime time between the last and the current frame
     */
    void processKeyboard(CameraMovement direction, float deltaTime);

    /**
     * Processes input received from the mouse
     * @param xoffset offset of the mouse's X position from the last position after it moved
     * @param yoffset offset of the mouse's Y position from the last position after it moved
     * @param constrainPitch stop pitching when 90 or -90 degrees are reached if set to true
     */
    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

    /**
     * Processes input received from the scroll
     * @param yoffset offset of the scroll after its movement;
     */
    void processMouseScroll(float yoffset);

    float getFov();
    glm::vec3 getPos();
    glm::vec3 getDir();
};


#endif //OPENGLTUTO_CAMERA_HPP
