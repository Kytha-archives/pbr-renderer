#include "Model.h"
#include "Renderer.h"

Model::Model(const std::string &filepath)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // check for errors when loading asset
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }

    m_Directory = filepath.substr(0, filepath.find_last_of('/'));

    // Default shader for models
    m_Shader = Renderer::GetShaderLibrary().Get("pbr_shader");

    m_Material.reset(new Material(m_Shader));
    processNode(scene->mRootNode, scene);
}

void Model::Render(Timestep ts)
{
    m_Material->Bind();
    for (unsigned int i = 0; i < m_Meshes.size(); i++)
    {
        m_Meshes[i].Render(ts);
    }
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        m_Meshes.push_back(Mesh(mesh));
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}
