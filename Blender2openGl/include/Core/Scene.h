#ifndef SCENE_H
#define SCENE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "WindowGL.h"
#include "Camera.h"
#include "Graphics/ShaderProgram.h"

#include "Graphics/Model.h"
#include "Graphics/models/Cube.h"
#include "Graphics/models/CustomModel.h" // En teoria solo necesitamos este

/**
 * @class Scene
 * @brief Clase para modelar una escena que contiene una ventana, un shaderprogram y un modelo
 */
class Scene
{
private:
    /**
     * Por que la ventana se queda como un RAW Pointer?
     * Por que la escena es un observador, no una propietaria de la ventana.
     */
    WindowGL *m_window;

    std::shared_ptr<ShaderProgram> m_shaderProgram; // This could be a std::vector of shader programs
    std::unique_ptr<Camera> m_camera;
    std::vector<std::unique_ptr<CustomModel>> m_models;

    /**
     * @brief Inicializacion
     */
    void init();

public:
    Scene(WindowGL *window);
    ~Scene();

    
    void input(float deltaTime); 

    void inputIsometricProcess(float deltaTime); 

    /**
     * @brief Ciclo de renderizado general
     */
    void render();
};

#endif