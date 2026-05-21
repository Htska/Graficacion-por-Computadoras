#ifndef CUSTOMMODEL_H
#define CUSTOMMODEL_H

#include <vector>
#include <iostream>
#include "Model.h"
#include "TextureLoader.h"
#include "Light.h"

#include "WindowGL.h"

// Definimos el número de Vertex Buffer Objects: Posición, Textura, Normales
#define NUM_VBOS 3

class CustomModel : public Model
{
private:
    // Configuración del modelo
    const char *m_filePath;

    // IDs de OpenGL
    GLuint m_VBO[NUM_VBOS];
    GLuint m_EBO; // Element Buffer Object para indexación

    // Datos de la malla (CPU)
    std::vector<float> m_vertices;
    std::vector<float> m_textCoords;
    std::vector<float> m_normalVecs;
    std::vector<unsigned int> m_indices; // Índices para glDrawElements

    // Arreglos para la boundix box
    std::vector<float> max;
    std::vector<float> min;
    glm::vec3 m_ka;
    glm::vec3 m_kd;
    glm::vec3 m_ks;
    float m_shininess;
    
    // Contadores para el renderizado
    int m_numIndices;

    // Texture
    GLuint m_textureID; // NUEVO IDENTIFICADOR PARA TEXTURA

    void RenderTexture() const;
     
public:
    /**
     * @brief Constructor: Carga y prepara el modelo para ser renderizado.
     */
    CustomModel(ShaderProgram* program, const char *filePath, const char *texturePath,
        glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, float shininess): 
        Model(program), 
        m_filePath(filePath), 
        m_ka{ka},
        m_kd{kd},
        m_ks{ks}, 
        m_shininess{shininess},
        m_numIndices(0)
    {
        m_model_mat = glm::mat4(1.0f);
        initGeometry(); // Extrae datos del OBJ a los vectores locales
        init();         // Carga los datos a la GPU (VAO, VBO, EBO)
        m_textureID = TextureLoader::LoadTexture(texturePath);
    }

    ~CustomModel();

    // Funciones de inicialización
    void initGeometry() override;

    void init() override;

    void renderModel(const glm::mat4 &view, const glm::mat4 &projection,Light* light) override;

    void updateModel(float deltaTime) override;

    void finish() override;

    int getNumIndices() const { return m_numIndices; }

};

#endif