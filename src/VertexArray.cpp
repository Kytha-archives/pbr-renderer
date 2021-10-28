#include "VertexArray.h"
#include "VertexBuffer.h"
#include "glad.h"

// Helper function which will convert from custom shader data types to appropriate GL types
static GLenum ShaderDataTypeToOpenGlBaseType(ShaderDataType type)
{
    switch (type)
    {
    case (ShaderDataType::Float):
        return GL_FLOAT;
    case (ShaderDataType::Float2):
        return GL_FLOAT;
    case (ShaderDataType::Float3):
        return GL_FLOAT;
    case (ShaderDataType::Float4):
        return GL_FLOAT;
    case (ShaderDataType::Mat3):
        return GL_FLOAT;
    case (ShaderDataType::Mat4):
        return GL_FLOAT;
    case (ShaderDataType::Int):
        return GL_INT;
    case (ShaderDataType::Int2):
        return GL_INT;
    case (ShaderDataType::Int3):
        return GL_INT;
    case (ShaderDataType::Int4):
        return GL_INT;
    case (ShaderDataType::Bool):
        return GL_BOOL;
    }
    return 0;
}

VertexArray::VertexArray()
{
    glCreateVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind()
{
    glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind()
{
    glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> &vertexBuffer)
{
    if (!vertexBuffer->GetLayout().GetElements().size())
        std::cout << "VertexBuffer has no layout!";
    glBindVertexArray(m_RendererID);
    vertexBuffer->Bind();
    uint32_t index = 0;
    const auto &layout = vertexBuffer->GetLayout();

    // Auto layout mapping
    for (const auto &element : layout)
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index,
                              element.GetComponentCount(),
                              ShaderDataTypeToOpenGlBaseType(element.Type),
                              element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(),
                              (const void *)element.Offset);
        index++;
    }
    m_VertexBuffers.push_back(vertexBuffer);
}

void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> &indexBuffer)
{
    glBindVertexArray(m_RendererID);
    indexBuffer->Bind();
    m_IndexBuffer = indexBuffer;
}

const std::vector<std::shared_ptr<VertexBuffer>> &VertexArray::GetVertexBuffers() { return m_VertexBuffers; }
const std::shared_ptr<IndexBuffer> &VertexArray::GetIndexBuffer() { return m_IndexBuffer; }