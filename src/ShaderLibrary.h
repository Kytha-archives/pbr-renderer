#include "core.h"
#include "Shader.h"

class ShaderLibrary
{
public:
    ShaderLibrary();
    ~ShaderLibrary();

    void Load(const std::string &path, const std::string &name);
    std::shared_ptr<Shader> &Get(const std::string &name);

private:
    std::unordered_map<std::string, std::shared_ptr<Shader>> m_Shaders;
};