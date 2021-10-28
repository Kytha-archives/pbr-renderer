#pragma once
#include "Core.h"
#include "Texture.h"
#include "Shader.h"

class Material
{
public:
    Material(std::shared_ptr<Shader> shader);
    void Set(const std::string &name, std::shared_ptr<Texture> texture);
    void Bind();
    void SetViewProjection(glm::mat4 viewProjectionMatrix);

private:
    std::vector<std::shared_ptr<Texture>> m_Textures;
    std::shared_ptr<Shader> m_Shader;
    glm::mat4 *m_ViewProjectionMatrix;
};