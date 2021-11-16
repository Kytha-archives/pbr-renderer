#pragma once
#include "Core.h"
#include <glm/glm.hpp>
#include <glad/glad.h>

class Shader
{
public:
    Shader(const std::string &filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    std::string ReadShaderFromFile(const std::string &filepath) const;
    int32_t GetUniformLocation(const std::string &name) const;
    void CompileAndUploadShader();

    // Preprocess single source string into multiple shader sources
    std::unordered_map<GLenum, std::string> PreProcess(const std::string &source);

    // Mapping of strings to shader types. Currently only supports "vertex" and "fragment"
    GLenum ShaderTypeFromString(const std::string &type);

    // These are upload functions to upload uniforms to shader. One for each data type
    void UploadUniformInt(uint32_t location, int32_t value);
    void UploadUniformIntArray(uint32_t location, int32_t *values, int32_t count);
    void UploadUniformFloat(uint32_t location, float value);
    void UploadUniformFloat2(uint32_t location, const glm::vec2 &value);
    void UploadUniformFloat3(uint32_t location, const glm::vec3 &value);
    void UploadUniformFloat4(uint32_t location, const glm::vec4 &value);
    void UploadUniformMat3(uint32_t location, const glm::mat3 &values);
    void UploadUniformMat4(uint32_t location, const glm::mat4 &values);
    void UploadUniformMat4Array(uint32_t location, const glm::mat4 &values, uint32_t count);

    void UploadUniformInt(const std::string &name, int32_t value);
    void UploadUniformIntArray(const std::string &name, int32_t *values, int32_t count);

    void UploadUniformFloat(const std::string &name, float value);
    void UploadUniformFloat2(const std::string &name, const glm::vec2 &value);
    void UploadUniformFloat3(const std::string &name, const glm::vec3 &value);
    void UploadUniformFloat4(const std::string &name, const glm::vec4 &value);

    void UploadUniformMat4(const std::string &name, const glm::mat4 &value);

private:
    uint32_t m_RendererID;
    std::unordered_map<GLenum, std::string> m_ShaderSource;
};