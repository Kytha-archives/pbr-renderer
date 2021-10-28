#include "Mesh.h"
#include "Renderer.h"

Mesh::Mesh(aiMesh *mesh)
{
    assert(mesh->HasPositions());
    assert(mesh->HasNormals());
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        vertex.Position = {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};
        vertex.Normal = {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};

        if (mesh->HasTangentsAndBitangents())
        {
            vertex.Tangent = {mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z};
            vertex.Binormal = {mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z};
        }

        if (mesh->HasTextureCoords(0))
            vertex.TexCoords = {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};

        m_Vertices.push_back(vertex);
    }
    // process indices
    for (uint32_t i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (uint32_t j = 0; j < face.mNumIndices; j++)
            m_Indices.push_back(face.mIndices[j]);
    }

    BufferLayout layout = {{ShaderDataType::Float3, "a_Position"}, {ShaderDataType::Float3, "a_Normal"}, {ShaderDataType::Float3, "a_Tangent"}, {ShaderDataType::Float3, "a_Binormal"}, {ShaderDataType::Float2, "a_TexCoords"}};

    m_Vb.reset(new VertexBuffer(m_Vertices.data(), m_Vertices.size() * sizeof(Vertex)));
    m_Vb->SetLayout(layout);

    m_Ib.reset(new IndexBuffer(m_Indices.data(), m_Indices.size()));

    m_Va.reset(new VertexArray());
    m_Va->AddVertexBuffer(m_Vb);
    m_Va->SetIndexBuffer(m_Ib);
}

void Mesh::Render(Timestep ts)
{
    Renderer::Submit(m_Va);
}
