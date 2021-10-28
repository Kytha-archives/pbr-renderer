#include "Core.h"
#include "glad.h"
#include "stb_image.h"
#include "Texture.h"
#include "Mesh.h"
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

class Model
{
public:
    Model(const std::string &filepath);
    void Render(Timestep ts);
    inline std::shared_ptr<Material> getMaterial() { return m_Material; }

private:
    std::vector<Mesh> m_Meshes;
    std::string m_Directory;
    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<Material> m_Material;

    void processNode(aiNode *node, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};