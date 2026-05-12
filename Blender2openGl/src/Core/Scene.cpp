#include "Core/Scene.h"
#include "Math/MathUtils.h"

Scene::Scene(WindowGL *window)
    : m_window{window}
{
    init();
}

Scene::~Scene()
{
}

void Scene::init()
{
    // El shader si es propiedad de la escena
    // m_shaderProgram = std::make_shared<ShaderProgram>("shaders/vertex_shader.glsl", "shaders/frag_shader.glsl");
    m_shaderProgram = std::make_shared<ShaderProgram>("shaders/vert_texture_shader.glsl", "shaders/frag_texture_shader.glsl");
    // m_shaderProgram->SetVec3("lightPos", glm::vec3(0.0f,8.0f,0.0f));

    m_camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 2.0f));
    m_camera->ComputeProjectionMatrix(m_window->getAspectRation(), 45.0f);
    
    // m_camera->ComputeIsometricProjection(m_window->getAspectRation(), 5.0f);
    // m_camera->SetIsometricView(); 

    // m_models.push_back(m); // Probando
    // m_models.push_back(std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/Car.obj"));
    // m_models.push_back(std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/Cube.obj"));
    m_models.push_back(std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/rose.obj", "assets/textures/Rose_Albedo.jpg"));
    // m_models.push_back(std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/Cube.obj"));

    // m_models.push_back(std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/Teapot.obj"));
    // m_models.push_back(std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/Teapot.obj"));
    // m_models.push_back(std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/Teapot.obj"));
    // m_models.push_back(std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/Teapot.obj"));
    // m_models.push_back(std::make_unique<CustomModel>(m_shaderProgram, "assets/obj/Teapot.obj"));

    // Para el input 
    for (auto &model : m_models)
    {
        //model->Translate(glm::vec3(0.0f, -2.0f, -2.0f));
        //model->Scale(glm::vec3(0.1f, 0.1f, 0.1f));
        //model->Rotate(-90.0f, glm::vec3(1.0f,0.0f,0.0f));
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

}

void Scene::input(float deltaTime){ 

    float cameraSpeed = static_cast<float>(2.5 * deltaTime);

    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_W) == GLFW_PRESS){
        m_camera->MoveForeward(cameraSpeed);
    }
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_S) == GLFW_PRESS){
        m_camera->MoveForeward(-cameraSpeed);
    }


    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_A) == GLFW_PRESS){
        m_camera->MoveRight(-cameraSpeed);
    }
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_D) == GLFW_PRESS){
        m_camera->MoveRight(cameraSpeed);
    }
    

    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_Q) == GLFW_PRESS){
        m_camera->MoveUp(-cameraSpeed);
    }
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_E) == GLFW_PRESS){
        m_camera->MoveUp(cameraSpeed);
    }
}

void Scene::inputIsometricProcess(float deltaTime){
    
    float cameraSpeed = static_cast<float>(2.5 * deltaTime);

    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_A) == GLFW_PRESS){
        m_camera->MoveRight(-cameraSpeed);
    }
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_D) == GLFW_PRESS){
        m_camera->MoveRight(cameraSpeed);
    }
    

    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_W) == GLFW_PRESS){
        m_camera->MoveUp(cameraSpeed);
    }
    if (glfwGetKey(m_window->getWindow(), GLFW_KEY_S) == GLFW_PRESS){
        m_camera->MoveUp(-cameraSpeed);
    }
}   

void Scene::render()
{

    float lastFrame = 0.0f; // Tiempo transcurrido del frame anterior

    glEnable(GL_DEPTH_TEST);
    
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // glPolygonMode(GL_FRONT, GL_LINE);
    while (!glfwWindowShouldClose(m_window->getWindow()))
    {
        // m_camera->ComputeViewMatrix();
        float currentFrame = static_cast<float>(glfwGetTime()); // Obtiene el tiempo desde que inicio la aplicacion
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // float speed = 0.01f;
        input(deltaTime);
        // inputIsometricProcess(deltaTime);

        m_camera->ComputeViewMatrix();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // for (auto &m : m_models)
        // {
        //     m->Move(*m_window, deltaTime);
        // }
        //std::cout<<"("<<m_camera->GetPosition().x<<","<<m_camera->GetPosition().y<<","<<m_camera->GetPosition().z<<")"<<std::endl;
        m_shaderProgram->SetVec3("viewPos", m_camera->GetPosition());
        for (auto &m : m_models)
        {
            m->Render(m_camera->GetViewMatrix(), m_camera->GetProjectionMatrix());
            //m->Rotate(glm::cos(deltaTime), glm::vec3(0.0f, 0.0f, 1.0f));
        }

        glfwSwapBuffers(m_window->getWindow());
        glfwPollEvents();
    }
}