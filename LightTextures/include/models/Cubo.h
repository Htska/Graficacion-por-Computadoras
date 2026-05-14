#ifndef CUBO_H
#define CUBO_H
// RECUERDEN NO PUEDEN USAR GLM EN EL PROYECTO!!!! :(
#include <glm/glm.hpp>
#include "Model.h"

class Cubo: public Model
{
private:
    GLfloat vertices[24];
    GLuint indices[36];
    GLfloat normalsVerts[36*6];
    GLfloat aristas[48];
    GLuint VAO2;
    GLuint VBO2;
    GLuint EBO2;
    GLuint indices2[24];
    int m_option;
    float m_angulo;
    glm::vec3 m_ka;
    glm::vec3 m_kd;
    glm::vec3 m_ks;
    float m_shininess;
    
public: 

    Cubo(ShaderProgram* program,int option,glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, float shininess) : 
    Model(program),
    m_option{option},
    m_ka{ka},
    m_kd{kd},
    m_ks{ks}, 
    m_shininess{shininess}{
        initGeometry();
        
        init();
        m_model_mat = glm::mat4(1.0f);
        if (option == 2)
            m_model_mat = glm::translate(m_model_mat,glm::vec3(-2.0f,0.0f,-2.0f));
        if (option == 1)
            m_model_mat = glm::translate(m_model_mat,glm::vec3(2.0f,0.0f,2.0f));
    }

    void initGeometry() override;

    void init() override;

    // RECUERDEN NO PUEDEN USAR GLM EN EL PROYECTO!!!! :(
    void renderModel(const glm::mat4& view, const glm::mat4& projection, Light* light) override;

    void updateModel(float deltaTime) override;

    void finish() override;

}; 

#endif
