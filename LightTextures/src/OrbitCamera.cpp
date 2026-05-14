#include "OrbitCamera.h"

glm::vec2 OrbitCamera::getAngles(glm::vec2 mouseInit,glm::vec2 mouseCurr)
{
    float epsilon = 0.01f;
    float theta = m_theta + ((mouseCurr.x - mouseInit.x)/10000.0f);
    float phi = std::min(std::max(m_phi+((mouseCurr.y-mouseInit.y)/10000.0f),-2.0f*(float)std::atan(1.0)+epsilon),2.0f*(float)std::atan(1.0)-epsilon);
    return glm::vec2(theta,phi);
}

glm::mat4 OrbitCamera::getMatrix()
{
    return glm::lookAt(m_pos,m_coi,m_up);
}

void OrbitCamera::setPos(glm::vec2 mouseInit, glm::vec2 mouseCurr)
{
    glm::vec2 angles = getAngles(mouseInit,mouseCurr);
    m_theta = angles.x;
    m_phi = angles.y;
}

void OrbitCamera::rotate(glm::vec2 mouseInit, glm::vec2 mouseCurr)
{
    glm::vec2 angles = getAngles(mouseInit,mouseCurr);
    m_pos = glm::vec3(m_coi.x+m_radius*(float)std::cos(angles.y)*(float)std::cos(angles.x),
                      m_coi.y+m_radius*(float)std::sin(angles.y),
                      m_coi.z+m_radius*(float)std::cos(angles.y)*(float)std::sin(angles.x));
}
