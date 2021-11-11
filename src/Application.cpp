#include "core.h"
#include "Application.h"
#include <GLFW/glfw3.h>
#include "Renderer.h"

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application *Application::s_Instance = nullptr;

Application::Application()
{

    // Enforcing a single instance of application
    if (s_Instance != nullptr)
    {
        std::cout << "Application already exists!";
    }
    s_Instance = this;
    m_Profiler = new Profiler();
    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
    m_Window->Init();
    Renderer::Init();

    // Parent ImGui Layer to wrap all ImGui rendering
    m_ImGuiLayer = new ImGuiLayer();
    PushOverlay(m_ImGuiLayer);
}

Application::~Application()
{
}

void Application::OnEvent(Event &e)
{
    // Handle WindowClose event first
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

    // Propagate events through layers starting with the uppermost layer
    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
    {
        (*--it)->OnEvent(e);
        if (e.Handled)
            break;
    }
}

void Application::Run()
{
    // MAIN APP LOOP
    while (m_Running)
    {

        // Calculate Frame time and frame rate
        float time = (float)glfwGetTime();
        Timestep timestep = time - m_LastUpdateTime;
        m_LastUpdateTime = time;

        m_Profiler->Update(time, timestep);
        // Update all layers
        for (Layer *layer : m_LayerStack)
            layer->OnUpdate(timestep);
        m_ImGuiLayer->Begin();
        for (Layer *layer : m_LayerStack)
            layer->OnImGuiRender();
        m_ImGuiLayer->End();

        m_Window->OnUpdate();
    }
}

void Application::PushLayer(Layer *layer)
{
    m_LayerStack.PushLayer(layer);
    layer->OnAttach();
}

void Application::PushOverlay(Layer *layer)
{
    m_LayerStack.PushOverlay(layer);
    layer->OnAttach();
}

bool Application::OnWindowClose(WindowCloseEvent &e)
{
    m_Running = false;
    return true;
}
