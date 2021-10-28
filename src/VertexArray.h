#pragma once
#include "Core.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class VertexArray {
public:
    VertexArray();
    ~VertexArray() {};

    void Bind();
    void Unbind();

    void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
    void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

    const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers();
    const std::shared_ptr<IndexBuffer>& GetIndexBuffer();
private:
    uint32_t m_RendererID;
    std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
    std::shared_ptr<IndexBuffer> m_IndexBuffer;
};