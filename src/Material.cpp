#include "Material.h"
#include "DirectionalLight.h"

Material::Material(std::shared_ptr<Shader> shader) : m_Shader(shader)
{
}

void Material::Set(const std::string &name, std::shared_ptr<Texture> texture)
{
    // Find where the texture is located and upload location and size info to shader
    m_Textures.push_back(texture);
    int32_t location = m_Shader->GetUniformLocation(name);
    glUniform1i(location, 0);
    m_Shader->Bind();
    m_Shader->UploadUniformInt(location, m_Textures.size() - 1);
}

void Material::Set(DirectionalLight light)
{
    // Uploads light data to shader
    m_Shader->Bind();
    m_Shader->UploadUniformFloat3("dirLight.direction", light.direction);
    m_Shader->UploadUniformFloat3("dirLight.ambient", light.ambient);
    m_Shader->UploadUniformFloat3("dirLight.diffuse", light.diffuse);
    m_Shader->UploadUniformFloat3("dirLight.specular", light.specular);
}

void Material::SetViewProjection(glm::mat4 viewProjectionMatrix)
{
    m_ViewProjectionMatrix = &viewProjectionMatrix;
}

void Material::SetView(const glm::vec3 &view)
{
    m_View = view;
}

void Material::Bind()
{
    m_Shader->Bind();
    m_Shader->UploadUniformMat4("u_ViewProjection", *m_ViewProjectionMatrix);
    m_Shader->UploadUniformFloat3("u_View", m_View);
    for (int i = 0; i < m_Textures.size(); i++)
    {
        m_Textures[i]->Bind(i);
    }
}