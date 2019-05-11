//
// Created by daftmat on 02/05/19.
//

#ifndef OPENGLTUTO_MODEL_HPP
#define OPENGLTUTO_MODEL_HPP

#include "../../src/Shape/Mesh.hpp"
#include <stb_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

unsigned int TextureFromFile(char const * path, const std::string &directory, bool gamma = false);
unsigned int TextureFromFile(const std::string &path, bool gamma = false);

enum PrimitiveType {
                //Parameters :
    SPHERE,     //center, radius, resolution
    CYLINDER,   //center1, center2, radius, resolution
    CUBE,       //center, resolution
    PLANE,      //center,
    CONE,
    COMPLEX
};

class Model {
    ///utils for loaded models
    std::string directory {""};
    std::vector<Texture> textures_loaded;

    void loadModel(const std::string &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

    ///Primitive utils
    unsigned int resolution {2};        //nb of triangles/lines
    PrimitiveType type {COMPLEX};       //not a primitive -> complex

    ///general utils
    glm::mat4 transform {glm::mat4(1.f)};

public:
    std::vector<Mesh> meshes;

    Model() = default;

    /**
     * Constructor that loads a model from obj file
     * @param path - path to obj file
     */
    Model(char *path) {loadModel(path);}

    /**
     * Constructor that loads a primitive model
     * @param type - type of primitive, see @PrimitiveType
     * @param resolution - number of triangles in a primitive's face (ex : 2 -> 2 triangles per face for a cube)
     */
    Model(PrimitiveType type, unsigned int resolution);

    Model& operator=(const Model &model);

    ~Model();

    /**
     * Transformation matrix setter
     * @param t - new matrix
     */
    void setTransform(const glm::mat4 &t) { transform=t; }

    /**
     * Transformation matrix getter
     * @return model's transformation
     */
    const glm::mat4 & getTransform() const { return transform; }

    /**
     * Draws the model using the specified shader
     * @param shader - shader being used when drawing the model
     */
    void Draw(const Shader &shader) const;
};

#endif //OPENGLTUTO_MODEL_HPP
