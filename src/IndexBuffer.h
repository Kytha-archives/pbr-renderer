#pragma once
#include "Core.h"

class IndexBuffer
{
public:
    IndexBuffer(void *indices, uint32_t size);
    ~IndexBuffer();
    void Bind();
    void Unbind();
    uint32_t getCount() const { return m_Count; };

private:
    uint32_t m_RendererID;
    uint32_t m_Count;
};