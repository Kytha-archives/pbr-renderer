#include "Texture.h"
#include "stb_image.h"
#include <glad/glad.h>

Texture::Texture(const std::string &filePath)
{
    int width, height, nrChannels;
    unsigned char *data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
    GLenum format = GL_RGB;
    switch (nrChannels)
    {
    case STBI_grey:
        format = GL_RED;
        break;
    case STBI_grey_alpha:
        format = GL_RG;
        break;
    case STBI_rgb:
        format = GL_RGB;
        break;
    case STBI_rgb_alpha:
        format = GL_RGBA;
        break;
    }
    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    m_Height = height;
    m_Width = width;
    m_FilePath = filePath;

    stbi_image_free(data);
}

void Texture::Bind(int slot)
{
    glBindTextureUnit(slot, m_RendererID);
}