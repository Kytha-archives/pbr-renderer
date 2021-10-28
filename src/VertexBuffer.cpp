
#include "VertexBuffer.h"
#include "glad.h"

VertexBuffer::VertexBuffer(void *vertices, uint32_t size)
{
    glCreateBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

const BufferLayout &VertexBuffer::GetLayout()
{
    return m_Layout;
}

void VertexBuffer::SetLayout(const BufferLayout &layout)
{
    m_Layout = layout;
}
