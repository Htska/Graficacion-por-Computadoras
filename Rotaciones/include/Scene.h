#ifndef SCENE_H 
#define SCENE_H

#include <GL/glew.h>  
#include <GLFW/glfw3.h> 
// RECUERDEN NO PUEDEN USAR GLM EN EL PROYECTO!!!! :(
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "WindowGL.h"
#include "ShaderProgram.h"

#include "Model.h"
#include "models/Cubo.h"

/**
 * @class Scene
 * @brief Clase para modelar una escena que contiene una ventana, un shaderprogram y un modelo 
 */
class Scene
{
private:

    /**
     * La ventana donde se crea la escena
     */
    WindowGL* m_window; 

    /**
     * Vector que contiene los shaders para los diferentes modelos
     */
    std::vector<ShaderProgram*>  m_shaderPrograms;

    /**
     * Vector con los diferentes modelos
     */
    std::vector<Model*> m_models;

    /**
     * Matriz de la vista
     */
    // RECUERDEN NO PUEDEN USAR GLM EN EL PROYECTO!!!! :(
    glm::mat4 m_view;

    /**
     * Matriz de proyección
     */
    // RECUERDEN NO PUEDEN USAR GLM EN EL PROYECTO!!!! :(
    glm::mat4 m_projection; 

    /**
     * @brief Inicializacion 
     */
    void init();

public:

    Scene(){
        init();
    }

    ~Scene(){
        delete m_window;
        for (ShaderProgram* sh:m_shaderPrograms)
            delete sh;
    }

    /**
     * @brief Ciclo de renderizado general 
     */
    void render(); 

};
#endif