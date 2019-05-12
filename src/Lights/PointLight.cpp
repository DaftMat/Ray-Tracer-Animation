//
// Created by mathis on 12/05/19.
//

#include "PointLight.hpp"

PointLight::PointLight(glm::vec3 position, float constant, float linear, float quadratic, glm::vec3 ambient,
                       glm::vec3 diffuse, glm::vec3 specular) {
    m_light.position  = position;
    m_light.constant  = constant;
    m_light.linear    =   linear;
    m_light.quadratic =quadratic;
    m_light.ambient   =  ambient;
    m_light.diffuse   =  diffuse;
    m_light.specular  = specular;

    glm::vec3 front(0.f, 0.f, .05f);
    glm::vec3    up(0.f, .05f, 0.f);
    glm::vec3 right(.05f, 0.f, 0.f);

    m_lightModel =       Model(position + up, position - up);
    m_lightModel.addLine(position + front, position - front);
    m_lightModel.addLine(position + right, position - right);
}