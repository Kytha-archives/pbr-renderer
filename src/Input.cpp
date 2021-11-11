#include "Input.h"
#include "Application.h"

// Input polling implementations
// Interfaces with glfw

bool Input::IsKeyPressed(int keycode)
{
    auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
    auto state = glfwGetKey(window, keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::IsMouseButtonPressed(int button)
{
    auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
    auto state = glfwGetMouseButton(window, button);
    return state == GLFW_PRESS;
}

std::pair<float, float> Input::GetMousePosition()
{
    auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return {(float)xpos, (float)ypos};
}

float Input::GetMouseX()
{
    auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
    return std::get<0>(GetMousePosition());
}

float Input::GetMouseY()
{
    auto window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
    return std::get<1>(GetMousePosition());
}
