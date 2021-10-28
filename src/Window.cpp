#include "core.h"
#include "Window.h"
#include "KeyEvent.h"
#include "MouseEvent.h"
#include "ApplicationEvent.h"
#include "Application.h"

static void GLFWErrorCallback(int error, const char* description)
{
    std::cout << "GLFW Error: " << error << " Description: " << description;
}

Window* Window::Create(const WindowProps& props)
{
    return new Window(props);
}

Window::Window(const WindowProps& props)
{
    m_Data.Title = props.Title;
    m_Data.Width = props.Width;
    m_Data.Height = props.Height;
}

Window::~Window()
{
    
}

void Window::Init()
{
    if (!s_GLFWInitialized)
    {
        s_GLFWInitialized = glfwInit();
        glfwSetErrorCallback(GLFWErrorCallback);
    }
    
    // Create glfw window 
    m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(m_Window);
    glfwSetWindowUserPointer(m_Window, &m_Data);

    if(!s_GLADInitialized) {
        s_GLADInitialized = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    }

    SetVSync(false);
    
    Profiler& profiler = Application::Get().GetProfiler();
    std::stringstream ss;
    ss << glGetString(GL_RENDERER);
    profiler.SetRenderer(ss.str());


    // Set GLFW callbacks
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        data.Width = width;
        data.Height = height;

        WindowResizeEvent event(width, height);
        data.EventCallback(event);
    });
    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) 
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        data.EventCallback(event);
    });
    glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mods) 
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        switch (action)
        {
            case GLFW_PRESS:
            {
                KeyPressedEvent event(key, 0);
                data.EventCallback(event);
                break;
            }
            case GLFW_REPEAT:
            {
                KeyPressedEvent event(key, 1);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                KeyReleasedEvent event(key);
                data.EventCallback(event);
                break;
            }
        }
    });

    glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        KeyTypedEvent event(keycode);
        data.EventCallback(event);
    });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        switch (action)
        {
            case GLFW_PRESS:
            {
                MouseButtonPressedEvent event(button);
                data.EventCallback(event);
                break;
            }

            case GLFW_RELEASE:
            {
                MouseButtonReleasedEvent event(button);
                data.EventCallback(event);
                break;
            }
        }
    });
    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        MouseScrolledEvent event((float)xOffset, (float)yOffset);
        data.EventCallback(event);
    });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPose) 
    {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        MouseMovedEvent event((float)xPos, (float)yPose);
        data.EventCallback(event);
    });
}

void Window::Shutdown()
{
    glfwDestroyWindow(m_Window);
}

void Window::OnUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_Window);

}

void Window::SetVSync(bool enabled)
{
    if (enabled)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);

    m_Data.VSync = enabled;
}

bool Window::IsVSync() const
{
    return m_Data.VSync;
}
