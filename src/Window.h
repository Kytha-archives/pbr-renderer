#pragma once
#include "Core.h"
#include "Event.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

static bool s_GLFWInitialized;
static bool s_GLADInitialized;

struct WindowProps
{
    std::string Title;
    unsigned int Width;
    unsigned int Height;

    // DEFAULT WINDOW PROPERTIES
    WindowProps(const std::string &title = "PBR Renderer",
                unsigned int width = 1280,
                unsigned int height = 720)
        : Title(title), Width(width), Height(height)
    {
    }
};

// Windows platform specific implementation of the window class
class Window
{
public:
    using EventCallbackFn = std::function<void(Event &)>;

    Window(const WindowProps &props);
    ~Window();

    void OnUpdate();

    inline unsigned int GetWidth() const { return m_Data.Width; }
    inline unsigned int GetHeight() const { return m_Data.Height; }

    // Window Attributes

    inline void SetEventCallback(const EventCallbackFn &callback) { m_Data.EventCallback = callback; }
    void SetVSync(bool enabled);
    bool IsVSync() const;

    inline void *GetNativeWindow() const { return m_Window; }

    void Init();
    void Shutdown();

    static Window *Create(const WindowProps &props = WindowProps());

private:
    GLFWwindow *m_Window;

    struct WindowData
    {
        std::string Title;
        unsigned int Width, Height;
        bool VSync;

        EventCallbackFn EventCallback;
    };

    WindowData m_Data;
};
