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

class Shader {
public:
    //program ID
    unsigned int ID;

    //constructor
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

    ~Shader();

    /**
     * activate the shader
     */
    void use();

    ///utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4f(const std::string &name, const glm::mat4 &value) const;
    void setVec3f(const std::string &name, const glm::vec3 &value) const;
    void setVec3f(const std::string &name, float x, float y, float z);

private:

    ///utility function for checking errors
    void checkCompileErrors(unsigned int shader, std::string type);
};


#endif //OPENGLTUTO_SHADER_HPP
