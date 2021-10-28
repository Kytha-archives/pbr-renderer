#pragma once
#include <glm/glm.hpp>
#include "Core.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Material.h"
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec3 Tangent;
    glm::vec3 Binormal;
    glm::vec2 TexCoords;
};

class Mesh
{
public:
    Mesh(aiMesh *mesh);
    void Render(Timestep ts);
    std::vector<Texture> m_Textures;

private:
    std::shared_ptr<IndexBuffer> m_Ib;
    std::shared_ptr<VertexBuffer> m_Vb;
    std::shared_ptr<VertexArray> m_Va;
    std::vector<Vertex> m_Vertices;
    std::vector<uint32_t> m_Indices;
};