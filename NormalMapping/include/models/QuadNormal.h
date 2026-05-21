#ifndef QUADNORMAL_H
#define QUADNORMAL_H

#include <vector>
#include <iostream>
#include "Model.h"
#include "TextureLoader.h"
#include "Light.h"

#include "WindowGL.h"


class QuadNormal : public Model
{
private:

    GLfloat vertices[84];

    glm::vec3 m_ka;
    glm::vec3 m_kd;
    glm::vec3 m_ks;
    float m_shininess;

    // Texture
    GLuint m_textureID;
    GLuint m_textureNormalID;


    void RenderTexture() const;
     
public:
    /**
     * @brief Constructor: Carga y prepara el modelo para ser renderizado.
     */
    QuadNormal(ShaderProgram* program, const char *texturePath, const char *textureNormalPath, 
        glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, float shininess): 
        Model(program), 
        m_ka{ka},
        m_kd{kd},
        m_ks{ks}, 
        m_shininess{shininess}
    {
        m_model_mat = glm::mat4(1.0f);
        initGeometry(); // Extrae datos del OBJ a los vectores locales
        init();         // Carga los datos a la GPU (VAO, VBO, EBO)
        m_textureID = TextureLoader::LoadTexture(texturePath);
        m_textureNormalID = TextureLoader::LoadTexture(textureNormalPath);
    }

    ~QuadNormal();

    // Funciones de inicialización
    void initGeometry() override;

    void init() override;

    void renderModel(const glm::mat4 &view, const glm::mat4 &projection,Light* light) override;

    void updateModel(float deltaTime) override;

    void finish() override;


};

#endif