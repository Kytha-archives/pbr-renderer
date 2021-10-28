#pragma once
#include <glm/glm.hpp>
#include "Shader.h"
#include "VertexArray.h"
#include "Camera.h"

class Renderer
{
public:
    static void BeginScene(Camera &camera);
    static void EndScene();
    static void Clear();
    static void Submit(const std::shared_ptr<VertexArray> &vertexArray);

private:
    struct SceneData
    {
        glm::mat4 ViewProjectionMatrix;
    };

    static SceneData *m_SceneData;
};
