//
// Created by daftmat on 02/05/19.
//

#ifndef OPENGLTUTO_MESH_HPP
#define OPENGLTUTO_MESH_HPP

#include <string>
#include <iostream>

#include <glm/glm.hpp>
#include <vector>
#include "../Shaders/Shader.hpp"

enum TexType {
    DIFFUSE,
    SPECULAR,
    NORMAL,
};

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
    unsigned int VAO, VBO, EBO;

public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh() = default;
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

    void Delete();

    void Draw(const Shader &shader) const;
    void setupMesh();
};


#endif //OPENGLTUTO_MESH_HPP
