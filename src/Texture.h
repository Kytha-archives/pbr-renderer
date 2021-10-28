#pragma once
#include "Core.h"

class Texture
{
public:
    Texture(const std::string &filePath);
    void Bind(int slot);

    uint32_t m_Width, m_Height;
    std::string m_FilePath;
    uint32_t m_RendererID;
};