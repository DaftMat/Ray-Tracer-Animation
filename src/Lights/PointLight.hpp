//
// Created by mathis on 12/05/19.
//

#ifndef RAY_TRACING_ANIMATION_POINTLIGHT_HPP
#define RAY_TRACING_ANIMATION_POINTLIGHT_HPP

#include "../Shape/Model.hpp"

class PointLight {
    Light m_light;
    Model m_lightModel;

public:

    PointLight(glm::vec3 position, float constant, float linear, float quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

    void Delete() {m_lightModel.Delete();}

    const Light & getLight() const { return m_light; }

    const Model & getLightModel() const { return m_lightModel; }

    ///light setters
    void setPosition(glm::vec3 position)  {m_light.position = position;}
    void setConstant(float constant)      {m_light.constant = constant;}
    void setLinear(float linear)          {m_light.linear   =   linear;}
    void setQuadratic(float quadratic)    {m_light.quadratic=quadratic;}
    void setAmbient(glm::vec3 ambient)    {m_light.ambient  =  ambient;}
    void setDiffuse(glm::vec3 diffuse)    {m_light.diffuse  =  diffuse;}
    void setSpecular(glm::vec3 specular)  {m_light.specular = specular;}
};


#endif //RAY_TRACING_ANIMATION_POINTLIGHT_HPP
