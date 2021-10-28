#include "core.h"
#include "Engine.h"
#include "Console.h"

class ExampleLayer : public Layer
{
public:
    ExampleLayer()
        : Layer("Test"){};
    void OnAttach() override
    {
        m_Camera = new Camera(glm::perspectiveFov(glm::radians(45.0f), 1280.0f, 720.0f, 0.1f, 10000.0f));
        m_Texture.reset(new Texture("./assets/textures/marble_bust_01_diff_4k.jpg"));
        m_NormalTexture.reset(new Texture("./assets/textures/marble_bust_01_nor_gl_4k.jpg"));
        m_Model.reset(new Model("./assets/models/marble_bust_01_4k.gltf"));
    }
    void OnUpdate(Timestep ts) override
    {
        auto viewProjection = m_Camera->GetProjectionMatrix() * m_Camera->GetViewMatrix();
        m_Model->getMaterial()->SetViewProjection(viewProjection);
        m_Model->getMaterial()->Set("u_AlbedoTexture", m_Texture);

        Renderer::BeginScene(*m_Camera);
        Renderer::Clear();
        m_Camera->Update(ts);
        m_Model->Render(ts);
        Renderer::EndScene();
    }
    void OnEvent(Event &e) override
    {

        if (e.GetEventType() == EventType::AppLog)
        {
            AppLogEvent &event = (AppLogEvent &)e;
            m_console.AddLog(event.m_msg.c_str());
        }
    }
    virtual void OnImGuiRender() override
    {

        static bool p_open = true;
        m_console.Draw("Console", &p_open);

        Profiler::Stats stats = Application::Get().GetProfiler().GetStats();
        ImGui::Begin("Stats");
        ImGui::Text("Renderer: %s", stats.renderer.c_str());
        ImGui::Text("FPS: %d", stats.fps);
        ImGui::Text("Draw Calls: %d", stats.drawCalls);
        ImGui::End();
    }

private:
    Console m_console;
    std::shared_ptr<Texture> m_Texture;
    std::shared_ptr<Texture> m_NormalTexture;
    std::shared_ptr<Model> m_Model;
    Camera *m_Camera;
};

class Game : public Application
{
public:
    Game()
    {
        PushLayer(new ExampleLayer());
    }
    ~Game()
    {
    }
};

Application *CreateApplication()
{
    return new Game();
}