#pragma once
#include "Timestep.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
public:
    Camera(const glm::mat4 &projectionMatrix);
    void Update(Timestep ts);
    inline void SetProjectionMatrix(const glm::mat4 &projectionMatrix) { m_ProjectionMatrix = projectionMatrix; }
    inline void SetViewportSize(uint32_t width, uint32_t height)
    {
        m_ViewportWidth = width;
        m_ViewportHeight = height;
    }
    const glm::vec3 &GetPosition() const { return m_Position; }
    const glm::mat4 &GetProjectionMatrix() const { return m_ProjectionMatrix; }
    const glm::mat4 &GetViewMatrix() const { return m_ViewMatrix; }

    glm::vec3 m_Position;
    glm::vec3 m_Rotation;

    // Camera basis
    glm::vec3 m_Front;
    glm::vec3 m_Up;
    glm::vec3 m_Right;

    // World constant
    glm::vec3 m_WorldUp;

    float m_Yaw;
    float m_Speed = 2.5f;
    float m_MouseSensitivity = 0.1f;
    float m_Pitch;
    float m_Zoom = 45.0f;

    // Viewport size is required for projection calculation
    uint32_t m_ViewportWidth = 1280, m_ViewportHeight = 720;
    glm::mat4 m_ProjectionMatrix, m_ViewMatrix;

    float m_FirstMouse = true;
    float m_LastX;
    float m_LastY;

    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch);
    void ProcessKeyboard(Camera_Movement direction, Timestep deltaTime);
};