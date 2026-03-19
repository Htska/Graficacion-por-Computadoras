#include "Scene.h"

void Scene::init(){
    //Inicializacion de ventana 
    m_window = new WindowGL();
    //Inicializacion de ProgramShader 
    ShaderProgram* m_shaderProgram = new ShaderProgram("shaders/vertex_shader.glsl","shaders/frag_shader.glsl");
    m_shaderPrograms.push_back(m_shaderProgram);

    //Se inicializan todos los modelos a usar
    Model* cubo = new Cubo(m_shaderPrograms[0],0);
    m_models.push_back(cubo);

    Model* cubo2 = new Cubo(m_shaderPrograms[0],1);
    m_models.push_back(cubo2);

    Model* cubo3 = new Cubo(m_shaderPrograms[0],2);
    m_models.push_back(cubo3);

    //Matriz de vista View Matrix
    //Posicion de la camara, centro de atencion, vector perpendicular de la Cámara
    // RECUERDEN NO PUEDEN USAR GLM EN EL PROYECTO!!!! :(
    m_view =  glm::lookAt(glm::vec3(7.0f,4.0f,7.0f), glm::vec3(0.0f,0.5f,0.0f), glm::vec3(0.0,1.0,0.0));
    //Matriz de projeccion
    // RECUERDEN NO PUEDEN USAR GLM EN EL PROYECTO!!!! :(
    m_projection = glm::perspective(glm::radians(45.0f), m_window->getAspectRation(), 0.1f, 100.0f);
}

void Scene::render()  {

    Model* model1 = m_models[0];
    Model* model2 = m_models[1];
    Model* model3 = m_models[2];



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
        model1->renderModel(m_view, m_projection);
        model2->renderModel(m_view, m_projection);
        model3->renderModel(m_view, m_projection);
        


        // update models 
        glfwSwapBuffers(m_window->getWindow());
        glfwPollEvents();

        model1->updateModel(0.7f);
        model2->updateModel(0.7f);
        model3->updateModel(0.7f);  
    }

}