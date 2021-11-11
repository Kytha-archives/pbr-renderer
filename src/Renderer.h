#pragma once
#include <glm/glm.hpp>
#include "Shader.h"
#include "VertexArray.h"
#include "Camera.h"
#include "ShaderLibrary.h"

class Renderer
{
public:
    static void Init();
    static void BeginScene(Camera &camera);
    static void EndScene();
    static void Clear();
    static void Submit(const std::shared_ptr<VertexArray> &vertexArray);
    static ShaderLibrary &GetShaderLibrary();

private:
    struct SceneData
    {
        glm::mat4 ViewProjectionMatrix;
    };

    static SceneData *m_SceneData;
    static ShaderLibrary *s_ShaderLibrary;
};
