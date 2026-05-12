#include "Core/Camera.h"

Camera::Camera(glm::vec3 position)
    :     m_position{position}
        , m_foreward{glm::vec3(0.0f, 0.0f, -1.0f)}
        , m_right{glm::vec3(1.0f, 0.0f, 0.0f)}
        , m_up{glm::vec3(0.0f, 1.0f, 0.0f)}
{
}

Camera::~Camera()
{
}

const glm::mat4 &Camera::GetViewMatrix() const
{
    return m_view_matrix;
}

const glm::mat4 &Camera::GetProjectionMatrix() const
{
    return m_projection_matrix;
}

const glm::vec3 &Camera::GetPosition() const
{
    return m_position;
}

void Camera::SetIsometricView()
{
    // Una posición alejada que mantenga el ángulo de 45 grados
    // La distancia (10, 10, 10) es arbitraria, lo importante es la dirección
    glm::vec3 isoPosition = glm::vec3(10.0f, 10.0f, 10.0f);
    glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
    
    m_position = isoPosition;
    m_foreward = glm::normalize(target - isoPosition);
    
    // Recalcular los vectores derecha y arriba para que el movimiento sea coherente
    m_right = glm::normalize(glm::cross(m_foreward, glm::vec3(0, 1, 0)));
    m_up    = glm::normalize(glm::cross(m_right, m_foreward));

    m_view_matrix = glm::lookAt(m_position, target, glm::vec3(0, 1, 0));
}

void Camera::UpdateOrthoSize(float delta){
    m_orthoSize = glm::max(1.0f, m_orthoSize + delta);
}

void Camera::ComputeViewMatrix()
{
    m_view_matrix = glm::lookAt(m_position, m_position + m_foreward, m_up);

    //Aqui podriamos mandar la posicion 
}

void Camera::ComputeProjectionMatrix(float aspectRatio, float fov)
{
    m_projection_matrix = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 1000.0f);
}

void Camera::ComputeIsometricProjection(float aspectRatio, float size)
{
    float left   = -size * aspectRatio;
    float right  =  size * aspectRatio;
    float bottom = -size;
    float top    =  size;

    // glm::ortho(left, right, bottom, top, zNear, zFar)
    m_projection_matrix = glm::ortho(left, right, bottom, top, -100.0f, 1000.0f);
}

void Camera::MoveForeward(float displacement){
    m_position+= m_foreward*displacement; 
}

void Camera::MoveRight(float displacement){
    m_position+= m_right*displacement; 
}

void Camera::MoveUp(float displacement){
    m_position+= m_up*displacement; 
}