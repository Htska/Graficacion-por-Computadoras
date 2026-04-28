#include "Light.h"

glm::vec3 Light::getPos(glm::mat4 view){
    glm::vec4 temp = view*m_pos;
    return glm::vec3(temp.x,temp.y,temp.z);
}


glm::vec3 Light::getAmbient(){
    return m_La;
}


glm::vec3 Light::getDiffuse(){
    return m_Ld;
}


glm::vec3 Light::getSpecular(){
    return m_Ls;
}

void Light::setPos(glm::vec4 pos){
    m_pos = pos;
}