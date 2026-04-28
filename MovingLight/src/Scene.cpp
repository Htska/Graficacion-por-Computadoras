#include "Scene.h"

void Scene::mouseCallback(GLFWwindow *window, int button,int action,int mods)
{
    Scene* instance = static_cast<Scene*>(glfwGetWindowUserPointer(window));
    mods = 0;
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double currX,currY = mods;
        glfwGetCursorPos(window,&currX,&currY);
        instance->m_last = glm::vec2((float)currX,(float)currY);
        instance->m_cameraMovement = true;
    }
    
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        instance->m_cameraMovement = false;
    }
}

void Scene::init(){
    //Inicializacion de ventana 
    m_window = new WindowGL();
    glfwSetWindowUserPointer(m_window->getWindow(), this);
    glfwSetMouseButtonCallback(m_window->getWindow(),Scene::mouseCallback);
    //Inicializacion de ProgramShader 
    ShaderProgram* m_shaderProgram = new ShaderProgram("shaders/vertex_shader.glsl","shaders/frag_shader.glsl");
    ShaderProgram* m_shaderProgram2 = new ShaderProgram("shaders/vertex_shader.glsl","shaders/frag_shader2.glsl");
    ShaderProgram* m_shaderProgram3 = new ShaderProgram("shaders/vertex_shader.glsl","shaders/frag_shader3.glsl");
    m_shaderPrograms.push_back(m_shaderProgram);
    m_shaderPrograms.push_back(m_shaderProgram2);
    m_shaderPrograms.push_back(m_shaderProgram3);



    //Coeficientes de la luz
    glm::vec3 ka = glm::vec3(0.1f,0.1f,0.1f);
    glm::vec3 kd = glm::vec3(0.0f,1.0f,0.0f);
    glm::vec3 ks = glm::vec3(1.0f,1.0f,1.0f);

    glm::vec3 kd2 = glm::vec3(1.0f,0.0f,0.0f);
    

    //Se inicializan todos los modelos a usar
    Model* cubo = new Cubo(m_shaderPrograms[1],0,ka,kd,ks,1.0f);
    m_models.push_back(cubo);

    Model* cubo2 = new Cubo(m_shaderPrograms[0],2,ka,kd2,ks,1.0f);
    m_models.push_back(cubo2);



    //Matriz de vista View Matrix
    //Posicion de la camara, centro de atencion, vector perpendicular de la Cámara
    // RECUERDEN NO PUEDEN USAR GLM EN EL PROYECTO!!!! :(
    m_camera = new OrbitCamera(glm::vec3(7.0f,4.0f,7.0f), glm::vec3(0.0f,0.5f,0.0f), glm::vec3(0.0,1.0,0.0));
    m_view =  m_camera->getMatrix();
    m_light = new Light(glm::vec4(4.0f,4.0f,0.0f,1.0f),glm::vec3(1.0f,1.0f,1.0f),glm::vec3(1.0f,1.0f,1.0f),glm::vec3(1.0f,1.0f,1.0f));
    //Matriz de projeccion
    // RECUERDEN NO PUEDEN USAR GLM EN EL PROYECTO!!!! :(
    m_projection = glm::perspective(glm::radians(45.0f), m_window->getAspectRation(), 0.1f, 100.0f);
}

void Scene::render()  {

    Model* model1 = m_models[0];
    Model* model2 = m_models[1];

    glm::vec4 pos(4.0f,4.0f,0.0f,1.0f);

    //Ciclo de Renderizado
    glEnable(GL_DEPTH_TEST);  // Prueba de profundidad
    glEnable(GL_CULL_FACE);   // Habilitar culling de caras
    glCullFace(GL_BACK);      // Culling de caras traseras
    glFrontFace(GL_CCW);      // Las caras frontales son las que tienen vértices en sentido antihorario

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  


    while(!glfwWindowShouldClose(m_window->getWindow())){
        // Compute time  
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(m_window->getWindow(), true);

        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_ENTER) == GLFW_PRESS)
        {
            delete m_camera;
            m_camera = new OrbitCamera(glm::vec3(7.0f,4.0f,7.0f), glm::vec3(0.0f,0.5f,0.0f), glm::vec3(0.0,1.0,0.0));
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        // se dibujan los modelos
        model2->renderModel(m_view, m_projection,m_light);
        model1->renderModel(m_view, m_projection,m_light);
        //model2->renderModel(m_view, m_projection,m_light);

        model1->updateModel(0.7f);

        // update models 
        glfwSwapBuffers(m_window->getWindow());
        glfwPollEvents();

        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
        {
            pos = glm::vec4(pos.x,pos.y+0.1f, pos.z, 1.0f);
        }
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
        {
            pos = glm::vec4(pos.x,pos.y-0.1f, pos.z, 1.0f);
        }
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            pos = glm::vec4(pos.x+0.1f,pos.y, pos.z, 1.0f);
        }
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            pos = glm::vec4(pos.x-0.1f,pos.y, pos.z, 1.0f);
        }if (glfwGetKey(m_window->getWindow(), GLFW_KEY_UP) == GLFW_PRESS)
        {
            pos = glm::vec4(pos.x,pos.y, pos.z+0.1f, 1.0f);
        }
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            pos = glm::vec4(pos.x,pos.y,pos.z-0.1f, 1.0f);
        }

        if (m_cameraMovement)
        {
            double currX,currY = 0;
            glfwGetCursorPos(m_window->getWindow(),&currX,&currY);
            m_current = glm::vec2((float)currX,(float)currY);
            m_camera->rotate(m_last,m_current);
            m_camera->setPos(m_last,m_current);

        }
        m_view = m_camera->getMatrix();
        m_light->setPos(pos);
    }

}