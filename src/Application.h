#pragma once
#include "core.h"
#include "Timestep.h"
#include "Window.h"
#include "LayerStack.h"
#include "ImGuiLayer.h"
#include "Event.h"
#include "ApplicationEvent.h"
#include "Profiler.h"

// Application is a singleton object which maintains the window and game loop
class Application
{

public:
    Application();
    virtual ~Application();

    void Run();

    void OnEvent(Event &e);

    void PushLayer(Layer *layer);

    void PushOverlay(Layer *layer);

    // Exposes the window object for input polling
    inline Window &GetWindow() { return *m_Window; }

    inline Profiler &GetProfiler() { return *m_Profiler; }
    inline static Application &Get() { return *s_Instance; }

private:
    bool OnWindowClose(WindowCloseEvent &e);
    bool OnWindowResize(WindowResizeEvent &e);

    // Pointer to the applications window object. An application can only have one window
    std::unique_ptr<Window> m_Window;

    // This is the parent ImGui layer
    ImGuiLayer *m_ImGuiLayer;
    LayerStack m_LayerStack;
    Profiler *m_Profiler;
    bool m_Running = true;
    float m_LastUpdateTime = 0.0f;

private:
    // Pointer to the apps application object
    static Application *s_Instance;
};

// To be defined in client application
// Client defines an Application object to be returned by this function
Application *CreateApplication();
