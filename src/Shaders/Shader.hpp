//
// Created by daftmat on 30/04/19.
//

#ifndef OPENGLTUTO_SHADER_HPP
#define OPENGLTUTO_SHADER_HPP

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/gtc/type_ptr.hpp>

struct Material {
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    bool diffTex;
    bool specTex;
    bool pngTex;
};

struct Light {
    glm::vec3 position;

    float constant;
    float linear;
    float quadratic;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

class Shader {
public:
    //program ID
    unsigned int ID;

    //constructor
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

    /**
     * Deletes the program shader
     */
    void Delete();

    /**
     * activate the shader
     */
    void use() const;

    ///utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4f(const std::string &name, const glm::mat4 &value) const;
    void setVec3f(const std::string &name, const glm::vec3 &value) const;
    void setVec3f(const std::string &name, float x, float y, float z) const;
    void setMaterial(const std::string&name, const Material &material) const;
    void addPointLight(const Light &light, unsigned int numLight) const;

    bool isWireframe() const { return wireframe; }
    void setWireframe(bool w) { wireframe = w; }
private:
    bool wireframe;

    ///utility function for checking errors
    void checkCompileErrors(unsigned int shader, std::string type);
};


#endif //OPENGLTUTO_SHADER_HPP
