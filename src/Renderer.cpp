#include "Renderer.h"
#include "Camera.h"
#include "Application.h"

Renderer::SceneData *Renderer::m_SceneData = new SceneData();

void Renderer::BeginScene(Camera &camera)
{
    glEnable(GL_DEPTH_TEST);
    m_SceneData->ViewProjectionMatrix = camera.GetProjectionMatrix() * camera.GetViewMatrix();
}

void Renderer::EndScene()
{
}

void Renderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Submit(const std::shared_ptr<VertexArray> &vertexArray)
{
    vertexArray->Bind();
    Profiler &profiler = Application::Get().GetProfiler();
    profiler.DrawCall();
    glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);
    vertexArray->Unbind();
}