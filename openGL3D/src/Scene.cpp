#include "Scene.h"

void Scene::init(){
    //Inicializacion de ventana 
    m_window = new WindowGL();
    //Inicializacion de ProgramShader 
    ShaderProgram* m_shaderProgram = new ShaderProgram("shaders/vertex_shader.glsl","shaders/frag_shader.glsl");
    m_shaderPrograms.push_back(m_shaderProgram);

    //Se inicializan todos los modelos a usar
    Model* cubo = new Cubo(m_shaderPrograms[0]);
    m_models.push_back(cubo);

    //Matriz de vista View Matrix
    //Posicion de la camara, centro de atencion, vector perpendicular de la Cámara
    // RECUERDEN NO PUEDEN USAR GLM EN EL PROYECTO!!!! :(
    m_view =  glm::lookAt(glm::vec3(3.0f,1.0f,3.0f), glm::vec3(0.0f,0.5f,0.0f), glm::vec3(0.0,1.0,0.0));
    //Matriz de projeccion
    // RECUERDEN NO PUEDEN USAR GLM EN EL PROYECTO!!!! :(
    m_projection = glm::perspective(glm::radians(45.0f), m_window->getAspectRation(), 0.1f, 100.0f);
}

void Scene::render()  {

    Model* m_model = m_models[0];

    //Ciclo de Renderizado
    glEnable(GL_DEPTH_TEST);  // Prueba de profundidad
    glEnable(GL_CULL_FACE);   // Habilitar culling de caras
    glCullFace(GL_BACK);      // Culling de caras traseras
    glFrontFace(GL_CCW);      // Las caras frontales son las que tienen vértices en sentido antihorario


    while(!glfwWindowShouldClose(m_window->getWindow())){
        // Compute time  
        if (glfwGetKey(m_window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(m_window->getWindow(), true);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        // se dibujan los modelos
        m_model->renderModel(m_view, m_projection);

        // update models 
        glfwSwapBuffers(m_window->getWindow());
        glfwPollEvents();

        m_model->updateModel(0.7f);  
    }

}