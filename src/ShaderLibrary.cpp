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
    else
        // Shader does not exist. Halt program
        assert(false);
}

void ShaderLibrary::Load(const std::string &path, const std::string &name)
{
    auto shader = std::shared_ptr<Shader>(new Shader(path));
    // Check shader doesn't already exist
    if ((m_Shaders.find(name) == m_Shaders.end()))
        m_Shaders[name] = shader;
}