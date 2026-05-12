#ifndef CAMERA_H
#define CAMERA_H

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:
    /* data */
    glm::vec3 m_position;

    glm::vec3 m_foreward;
    glm::vec3 m_right;
    glm::vec3 m_up;

    glm::mat4 m_view_matrix;
    glm::mat4 m_projection_matrix;

    // float m_sensitivity = 0.1f;

    // float m_yaw = -90.0f;
    // float m_pitch = 0.0f;

    // float m_last_mouseX = 0.0;
    // float m_last_mouseY = 0.0;

    // bool m_first_mouse = true;

    // glm::vec3 m_direction;

    float m_orthoSize = 5.0f; // Para projeccion ortographica 

public:
    Camera(glm::vec3 position);
    ~Camera();

    const glm::mat4 &GetViewMatrix() const;

    const glm::mat4 &GetProjectionMatrix() const;

    const glm::vec3 &GetPosition() const;

    void ComputeViewMatrix();

    void SetIsometricView(); 

    void UpdateOrthoSize(float delta); 

    void ComputeProjectionMatrix(float aspectRatio, float fov);
    
    // Testing 
    void ComputeIsometricProjection(float aspectRatio, float size);

    void MoveForeward(float displacement); 

    void MoveRight(float displacement); 

    void MoveUp(float displacement); 

};

#endif
