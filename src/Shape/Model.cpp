//
// Created by daftmat on 02/05/19.
//

#include "Model.hpp"

Model::Model(glm::vec3 p1, glm::vec3 p2) {
    addLine(p1, p2);
}

Model::Model(PrimitiveType type, unsigned int resolution) : m_type(type), m_resolution(resolution) {
    switch (type) {
        case SPHERE:
            constructSphere();
            break;
        case PYRAMID:
            constructPyramid();
            break;
        default:
            break;
    }
}

void Model::constructSphere() {
    std::vector<glm::vec3> directions = {
            glm::vec3(0.f, 0.f, 1.f),   //front
            glm::vec3(0.f, 0.f,-1.f),   //back
            glm::vec3(0.f, 1.f, 0.f),   //up
            glm::vec3(0.f,-1.f, 0.f),   //bottom
            glm::vec3(1.f, 0.f, 0.f),   //left
            glm::vec3(-1.f,0.f, 0.f)    //right
    };

    std::vector<Vertex> vertices;
    std::vector<unsigned int> triangles;
    std::vector<Texture> textures; //still empty in this function
    m_material.diffuse = glm::vec3(.3f, .3f, .3f);
    m_material.specular = glm::vec3(.8f, .8f, .8f);
    m_material.shininess = 1.f;
    m_material.diffTex = false;
    m_material.specTex = false;
    m_material.pngTex = false;
    glm::vec3 axisA;
    glm::vec3 axisB;

    for (int i = 0 ; i < 6 ; ++i) {
        axisA = glm::vec3(directions[i].y, directions[i].z, directions[i].x);
        axisB = glm::cross(directions[i], axisA);

        for (int y = 0 ; y < m_resolution ; ++y) {
            for (int x = 0 ; x < m_resolution ; ++x) {
                unsigned int index = x + y * m_resolution;
                glm::vec2 percent = glm::vec2(x, y) / (m_resolution - 1.f);
                glm::vec3 pointOnUnitCube = directions[i] + (percent.x - .5f) * 2 * axisA + (percent.y - .5f) * 2 * axisB;
                glm::vec3 pointOnUnitSphere = glm::normalize(pointOnUnitCube);

                Vertex vertex;
                vertex.Position = pointOnUnitSphere;
                vertex.Normal = pointOnUnitSphere;
                vertex.TexCoords = percent;
                vertex.Tangent = glm::normalize(glm::cross(axisB, pointOnUnitSphere));
                vertex.Bitangent = glm::normalize(glm::cross(vertex.Tangent, pointOnUnitSphere));
                vertices.emplace_back(vertex);

                if (x != m_resolution - 1 && y != m_resolution - 1) {
                    triangles.emplace_back(index);
                    triangles.emplace_back(index + m_resolution + 1);
                    triangles.emplace_back(index + m_resolution);

                    triangles.emplace_back(index);
                    triangles.emplace_back(index + 1);
                    triangles.emplace_back(index + m_resolution + 1);
                }
            }
        }

        meshes.emplace_back(Mesh(vertices, triangles, textures));

        vertices.clear();
        triangles.clear();
    }
}

void Model::constructPyramid() {
    glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
    glm::vec3 axisA = glm::vec3(up.y, up.z, up.x);
    glm::vec3 axisB = glm::cross(up, axisA);
    std::vector<glm::vec3> directions = {
            glm::vec3(0.f, 0.f, 1.f),   //front
            glm::vec3(0.f, 0.f,-1.f),   //back
            glm::vec3(1.f, 0.f, 0.f),   //left
            glm::vec3(-1.f,0.f, 0.f)
    };

    std::vector<Vertex> vertices;
    std::vector<unsigned int> triangles;
    std::vector<Texture> textures;
    m_material.diffuse = glm::vec3(.3f, .3f, .3f);
    m_material.specular = glm::vec3(.8f, .8f, .8f);
    m_material.shininess = 1.f;
    m_material.diffTex = false;
    m_material.specTex = false;
    m_material.pngTex = false;

    for (int y = 0 ; y < m_resolution ; ++y) {
        for (int x = 0 ; x < m_resolution ; ++x) {
            unsigned int index = x + y * m_resolution;
            glm::vec2 percent = glm::vec2(x, y) / (m_resolution - 1.f);
            glm::vec3 pointOnUnitPlane = (percent.x - .5f) * 2 * axisA + (percent.y - .5f) * 2 * axisB;

            Vertex vertex;
            vertex.Position = pointOnUnitPlane;
            vertex.Normal = -up;
            vertex.TexCoords = percent;
            vertex.Tangent = axisA;
            vertex.Bitangent = axisB;
            vertices.emplace_back(vertex);

            if (x != m_resolution - 1 && y != m_resolution - 1) {
                triangles.emplace_back(index);
                triangles.emplace_back(index + m_resolution + 1);
                triangles.emplace_back(index + m_resolution);

                triangles.emplace_back(index);
                triangles.emplace_back(index + 1);
                triangles.emplace_back(index + m_resolution + 1);
            }
        }
    }

    meshes.emplace_back(Mesh(vertices, triangles, textures));
    vertices.clear();
    triangles.clear();

    for (int i = 0 ; i < 4 ; ++i) {
        Vertex vertex;
        vertex.Position = up;
        vertex.Normal = glm::normalize(up + directions[i]);
        vertex.TexCoords = glm::vec2(0.f, 0.f);
        vertex.Tangent = glm::cross(vertex.Normal, up);
        vertex.Bitangent = glm::cross(vertex.Normal, vertex.Tangent);
        vertices.emplace_back(vertex);

        if (i < 2) {
            vertex.Position = directions[i] + directions[2];
            vertices.emplace_back(vertex);
            vertex.Position = directions[i] + directions[3];
            vertices.emplace_back(vertex);
        } else {
            vertex.Position = directions[i] + directions[0];
            vertices.emplace_back(vertex);
            vertex.Position = directions[i] + directions[1];
            vertices.emplace_back(vertex);
        }

        triangles.emplace_back(0);
        triangles.emplace_back(1);
        triangles.emplace_back(2);

        meshes.emplace_back(Mesh(vertices, triangles, textures));
        vertices.clear();
        triangles.clear();
    }
}

void Model::addLine(glm::vec3 p1, glm::vec3 p2) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> triangles;
    std::vector<Texture> textures;

    Vertex vertex;
    vertex.Position = p1;
    vertex.Normal = glm::vec3(0.f, 0.f, 0.f);
    vertex.TexCoords = glm::vec2(0.f, 0.f);
    vertex.Tangent = glm::vec3(0.f, 0.f, 0.f);
    vertex.Bitangent = glm::vec3(0.f, 0.f, 0.f);

    vertices.emplace_back(vertex);

    vertex.Position = p2;

    vertices.emplace_back(vertex);

    triangles.emplace_back(0);
    triangles.emplace_back(1);
    triangles.emplace_back(0);

    meshes.emplace_back(Mesh(vertices, triangles, textures));
}

Model& Model::operator=(const Model &model) {
    directory = model.directory;
    m_type = model.m_type;
    m_resolution = model.m_resolution;
    transform = model.transform;
    textures_loaded = model.textures_loaded;
    meshes = model.meshes;
    return *this;
}

void Model::Delete() {
    for (auto &texture : textures_loaded)
        glDeleteTextures(1, &texture.id);
    for (auto &mesh : meshes)
        mesh.Delete();
}

void Model::Draw(const Shader &shader) const {
    for (const auto &mesh : meshes) {
        mesh.Draw(shader);
    }
}

void Model::loadModel(const std::string &path) {
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }

    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    for (unsigned int i = 0 ; i < node->mNumMeshes ; ++i) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }

    for (unsigned int i = 0 ; i < node->mNumChildren ; ++i) {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    // data to fill
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    // Walk through each of the mesh's vertices
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        // normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;
        // texture coordinates
        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        // tangent
        vector.x = mesh->mTangents[i].x;
        vector.y = mesh->mTangents[i].y;
        vector.z = mesh->mTangents[i].z;
        vertex.Tangent = vector;
        // bitangent
        vector.x = mesh->mBitangents[i].x;
        vector.y = mesh->mBitangents[i].y;
        vector.z = mesh->mBitangents[i].z;
        vertex.Bitangent = vector;
        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN

    // 1. diffuse maps
    std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    m_material.diffuse = glm::vec3(.3f, .3f, .3f);
    m_material.specular = glm::vec3(.8f, .8f, .8f);
    m_material.shininess = 1.f;
    m_material.diffTex = false;
    m_material.specTex = false;
    m_material.pngTex = false;

    // return a mesh object created from the extracted mesh data
    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
{
    std::vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for(unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }
        if(!skip)
        {   // if texture hasn't been loaded already, load it
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture); // add to loaded textures
        }
    }
    return textures;
}

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    return TextureFromFile(filename, gamma);
}

unsigned int TextureFromFile(const std::string &path, bool gamma) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}