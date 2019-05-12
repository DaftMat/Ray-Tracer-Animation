//
// Created by daftmat on 02/05/19.
//

#ifndef OPENGLTUTO_MODEL_HPP
#define OPENGLTUTO_MODEL_HPP

#include "../Shape/Mesh.hpp"
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
    PYRAMID,
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
    unsigned int m_resolution;        //nb of triangles/lines
    PrimitiveType m_type {COMPLEX};       //not a primitive -> complex

    Material m_material;

    void constructSphere();
    void constructCylinder();
    void constructCube();
    void constructPlane();
    void constructCone();
    void constructPyramid();

    ///general utils
    glm::mat4 transform {glm::mat4(1.f)};
    glm::mat4 localTransform {glm::mat4(1.f)};

public:
    std::vector<Mesh> meshes;

    Model() = default;

    /**
     * Constructor that loads a model from obj file
     * @param path - path to obj file
     */
    explicit Model(char *path) {loadModel(path);}

    /**
     * Constructor that loads a primitive model
     * @param type - type of primitive, see @PrimitiveType
     * @param resolution - number of triangles in a primitive's face (ex : 2 -> 2 triangles per face for a cube)
     */
    Model(PrimitiveType type, unsigned int resolution = 10);

    /**
     * Constructor that loads a line from p1 to p2;
     * @param p1
     * @param p2
     */
    Model(glm::vec3 p1, glm::vec3 p2);

    void addLine(glm::vec3 p1, glm::vec3 p2);

    Model& operator=(const Model &model);

    void Delete();

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
     * Material setter
     * @param material - new material
     */
    void setMaterial(const Material &material) { m_material = material; }

    /**
     * Material getter
     * @return material of the model
     */
    const Material & getMaterial() const { return m_material; }

    /**
     * Draws the model using the specified shader
     * @param shader - shader being used when drawing the model
     */
    void Draw(const Shader &shader) const;
};

#endif //OPENGLTUTO_MODEL_HPP
