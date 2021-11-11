#include "ShaderLibrary.h"

ShaderLibrary::ShaderLibrary()
{
}

ShaderLibrary::~ShaderLibrary()
{
}

std::shared_ptr<Shader> &ShaderLibrary::Get(const std::string &name)
{
    if (!(m_Shaders.find(name) == m_Shaders.end()))
        return m_Shaders[name];
}

void ShaderLibrary::Load(const std::string &path, const std::string &name)
{
    auto shader = std::shared_ptr<Shader>(new Shader(path));
    if ((m_Shaders.find(name) == m_Shaders.end()))
        m_Shaders[name] = shader;
}