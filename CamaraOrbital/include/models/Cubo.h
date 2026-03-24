#ifndef CUBO_H
#define CUBO_H
// RECUERDEN NO PUEDEN USAR GLM EN EL PROYECTO!!!! :(
#include <glm/glm.hpp>
#include "Model.h"

class Cubo: public Model
{
private:
    GLfloat vertices[48];
    GLuint indices[36];
    GLfloat aristas[48];
    GLuint VAO2;
    GLuint VBO2;
    GLuint EBO2;
    GLuint indices2[24];
    int m_option;
    float m_angulo;
public: 

    Cubo(ShaderProgram* program,int option) : Model(program),m_option{option}{
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
    void renderModel(const glm::mat4& view, const glm::mat4& projection) override;

    void updateModel(float deltaTime) override;

    void finish() override;

}; 

#endif
