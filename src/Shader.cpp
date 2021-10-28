#include "core.h"
#include "Shader.h"

#include "glad.h"
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string &filepath)
{
    std::string source = ReadShaderFromFile(filepath);
    m_ShaderSource = PreProcess(source);
    CompileAndUploadShader();
}

std::string Shader::ReadShaderFromFile(const std::string &filepath) const
{
    std::string code;
    std::stringstream ss;
    std::ifstream in;

    in.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        in.open(filepath);
        ss << in.rdbuf();
        in.close();
        code = ss.str();
        return code;
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        return code;
    }
}

void Shader::CompileAndUploadShader()
{
    std::vector<GLuint> shaderRendererIDs;

    GLuint program = glCreateProgram();
    for (auto &kv : m_ShaderSource)
    {
        GLenum type = kv.first;
        std::string &source = kv.second;
        GLuint shaderRendererID = glCreateShader(type);
        const GLchar *sourceCstr = (const GLchar *)source.c_str();
        glShaderSource(shaderRendererID, 1, &sourceCstr, 0);

        glCompileShader(shaderRendererID);

        GLint isCompiled = 0;
        glGetShaderiv(shaderRendererID, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(shaderRendererID, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shaderRendererID, maxLength, &maxLength, &infoLog[0]);

            std::cout << "ERROR::SHADER::SHADER COMPILATION FAILED" << &infoLog[0] << std::endl;

            // We don't need the shader anymore.
            glDeleteShader(shaderRendererID);
        }

        shaderRendererIDs.push_back(shaderRendererID);
        glAttachShader(program, shaderRendererID);
    }
    // Link our program
    glLinkProgram(program);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
        std::cout << "ERROR::SHADER::SHADER LINKING FAIL" << std::endl;

        // We don't need the program anymore.
        glDeleteProgram(program);
        // Don't leak shaders either.
        for (auto id : shaderRendererIDs)
            glDeleteShader(id);
    }

    // Always detach shaders after a successful link.
    for (auto id : shaderRendererIDs)
        glDetachShader(program, id);

    m_RendererID = program;
}

GLenum Shader::ShaderTypeFromString(const std::string &type)
{
    if (type == "vertex")
        return GL_VERTEX_SHADER;
    if (type == "fragment" || type == "pixel")
        return GL_FRAGMENT_SHADER;

    return GL_NONE;
}

std::unordered_map<GLenum, std::string> Shader::PreProcess(const std::string &source)
{
    std::unordered_map<GLenum, std::string> shaderSources;
    const char *typeToken = "#type";
    size_t typeTokenLength = strlen(typeToken);
    size_t pos = source.find(typeToken, 0);
    while (pos != std::string::npos)
    {
        size_t eol = source.find_first_of("\r\n", pos);
        size_t begin = pos + typeTokenLength + 1;
        std::string type = source.substr(begin, eol - begin);
        size_t nextLinePos = source.find_first_not_of("\r\n", eol);
        pos = source.find(typeToken, nextLinePos);
        shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
    }
    return shaderSources;
}

int32_t Shader::GetUniformLocation(const std::string &name) const
{
    int32_t result = glGetUniformLocation(m_RendererID, name.c_str());
    if (result == -1)
        std::cout << "Could not find uniform " + name + " in shader";
    return result;
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::UploadUniformInt(uint32_t location, int32_t value)
{
    glUniform1i(location, value);
}

void Shader::UploadUniformIntArray(uint32_t location, int32_t *values, int32_t count)
{
    glUniform1iv(location, count, values);
}

void Shader::UploadUniformFloat(uint32_t location, float value)
{
    glUniform1f(location, value);
}

void Shader::UploadUniformFloat2(uint32_t location, const glm::vec2 &value)
{
    glUniform2f(location, value.x, value.y);
}

void Shader::UploadUniformFloat3(uint32_t location, const glm::vec3 &value)
{
    glUniform3f(location, value.x, value.y, value.z);
}

void Shader::UploadUniformFloat4(uint32_t location, const glm::vec4 &value)
{
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::UploadUniformMat3(uint32_t location, const glm::mat3 &value)
{
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::UploadUniformMat4(uint32_t location, const glm::mat4 &value)
{
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::UploadUniformMat4Array(uint32_t location, const glm::mat4 &values, uint32_t count)
{
    glUniformMatrix4fv(location, count, GL_FALSE, glm::value_ptr(values));
}

void Shader::UploadUniformFloat(const std::string &name, float value)
{
    glUseProgram(m_RendererID);
    auto location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location != -1)
        glUniform1f(location, value);
}

void Shader::UploadUniformFloat3(const std::string &name, const glm::vec3 &values)
{
    glUseProgram(m_RendererID);
    auto location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location != -1)
        glUniform3f(location, values.x, values.y, values.z);
}

void Shader::UploadUniformFloat4(const std::string &name, const glm::vec4 &values)
{
    glUseProgram(m_RendererID);
    auto location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location != -1)
        glUniform4f(location, values.x, values.y, values.z, values.w);
}

void Shader::UploadUniformMat4(const std::string &name, const glm::mat4 &values)
{
    glUseProgram(m_RendererID);
    auto location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location != -1)
        glUniformMatrix4fv(location, 1, GL_FALSE, (const float *)&values);
}
