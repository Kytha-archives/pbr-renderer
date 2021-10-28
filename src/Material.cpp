#include "Material.h"

Material::Material(std::shared_ptr<Shader> shader) : m_Shader(shader)
{
}

void Material::Set(const std::string &name, std::shared_ptr<Texture> texture)
{
    m_Textures.push_back(texture);
    int32_t location = m_Shader->GetUniformLocation(name);
    glUniform1i(location, 0);
    m_Shader->UploadUniformInt(location, m_Textures.size() - 1);
}

void Material::SetViewProjection(glm::mat4 viewProjectionMatrix)
{
    m_ViewProjectionMatrix = &viewProjectionMatrix;
}

void Material::Bind()
{
    m_Shader->Bind();
    m_Shader->UploadUniformMat4("u_ViewProjection", *m_ViewProjectionMatrix);

    for (int i = 0; i < m_Textures.size(); i++)
    {
        m_Textures[i]->Bind(i);
    }
}