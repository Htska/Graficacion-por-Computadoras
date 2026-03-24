#include "models/Cubo.h"

void Cubo::initGeometry(){
    vertices[0] = -0.5f; vertices[1]  = -0.5f; vertices[2]  = -0.5f; vertices[3]  = 0.0f; vertices[4]  = 1.0f; vertices[5]  = 0.0f; // v0     
    vertices[6]  = 0.5f; vertices[7]  = -0.5f; vertices[8]  = -0.5f; vertices[9]  =  0.0f; vertices[10] = 1.0f; vertices[11] = 0.0f; // v1
    vertices[12] = 0.5f; vertices[13] =  0.5f; vertices[14] = -0.5f; vertices[15] =  0.0f; vertices[16] = 1.0f; vertices[17] = 0.0f; // v2
    vertices[18] =-0.5f; vertices[19] =  0.5f; vertices[20] = -0.5f; vertices[21] = 0.0f; vertices[22] = 1.0f; vertices[23] = 0.0f; // v3
    vertices[24] =-0.5f; vertices[25] = -0.5f; vertices[26] =  0.5f; vertices[27] = 0.0f; vertices[28] = 1.0f; vertices[29] = 0.0f; // v4
    vertices[30] = 0.5f; vertices[31] = -0.5f; vertices[32] =  0.5f; vertices[33] =  0.0f; vertices[34] = 1.0f; vertices[35] = 0.0f; // v5
    vertices[36] = 0.5f; vertices[37] =  0.5f; vertices[38] =  0.5f; vertices[39] =  0.0f; vertices[40] = 1.0f; vertices[41] = 0.0f; // v6
    vertices[42] =-0.5f; vertices[43] =  0.5f; vertices[44] =  0.5f; vertices[45] =  0.0f; vertices[46] = 1.0f; vertices[47] = 0.0f; // v7

    indices[0] = 0;indices[1] = 2;indices[2] = 1;indices[3] = 3;indices[4] = 2;indices[5] = 0; // Cara trasera
    indices[6] = 4;indices[7] = 5;indices[8] = 6;indices[9] = 6;indices[10] = 7;indices[11] = 4; // Cara delantera
    indices[12] = 0;indices[13] = 1;indices[14] = 5;indices[15] = 5;indices[16] = 4;indices[17] = 0; // Cara inferior
    indices[18] =2;indices[19] = 3;indices[20] = 7;indices[21] = 7;indices[22] = 6;indices[23] = 2; // Cara superior
    indices[24] =0;indices[25] = 7;indices[26] = 3;indices[27] = 7;indices[28] = 0;indices[29] = 4; // Cara izquierda
    indices[30] =1;indices[31] = 2;indices[32] = 6;indices[33] = 6;indices[34] = 5;indices[35] = 1; // Cara derecha
 
    aristas[0] = -0.5f; aristas[1]  = -0.5f; aristas[2]  = -0.5f; aristas[3]  = 0.0f; aristas[4]  = 0.0f; aristas[5]  = 0.0f; // v0     
    aristas[6]  = 0.5f; aristas[7]  = -0.5f; aristas[8]  = -0.5f; aristas[9]  =  0.0f; aristas[10] = 0.0f; aristas[11] = 0.0f; // v1
    aristas[12] = 0.5f; aristas[13] =  0.5f; aristas[14] = -0.5f; aristas[15] =  0.0f; aristas[16] = 0.0f; aristas[17] = 0.0f; // v2
    aristas[18] =-0.5f; aristas[19] =  0.5f; aristas[20] = -0.5f; aristas[21] = 0.0f; aristas[22] = 0.0f; aristas[23] = 0.0f; // v3
    aristas[24] =-0.5f; aristas[25] = -0.5f; aristas[26] =  0.5f; aristas[27] = 0.0f; aristas[28] = 0.0f; aristas[29] = 0.0f; // v4
    aristas[30] = 0.5f; aristas[31] = -0.5f; aristas[32] =  0.5f; aristas[33] =  0.0f; aristas[34] = 0.0f; aristas[35] = 0.0f; // v5
    aristas[36] = 0.5f; aristas[37] =  0.5f; aristas[38] =  0.5f; aristas[39] =  0.0f; aristas[40] = 0.0f; aristas[41] = 0.0f; // v6
    aristas[42] =-0.5f; aristas[43] =  0.5f; aristas[44] =  0.5f; aristas[45] =  0.0f; aristas[46] = 0.0f; aristas[47] = 0.0f; // v7

    indices2[0] = 0; indices2[1] = 1;
    indices2[2] = 1; indices2[3] = 2;
    indices2[4] = 2; indices2[5] = 3;
    indices2[6] = 3; indices2[7] = 0;
    indices2[8] = 0; indices2[9] = 4;
    indices2[10] = 1; indices2[11] = 5;
    indices2[12] = 2; indices2[13] = 6;
    indices2[14] = 3; indices2[15] = 7;
    indices2[16] = 4; indices2[17] = 5;
    indices2[18] = 5; indices2[19] = 6;
    indices2[20] = 6; indices2[21] = 7;
    indices2[22] = 7; indices2[23] = 4;
}

void Cubo::init(){
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);


    glGenVertexArrays(1,&VAO2);
    glGenBuffers(1, &VBO2);
    glGenBuffers(1, &EBO2);
    glBindVertexArray(VAO2);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(aristas), aristas, GL_STATIC_DRAW); 

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);


}


void Cubo::renderModel(const glm::mat4& view, const glm::mat4& projection){
    m_shaderProgram->use();

    m_shaderProgram->setMat4x4("model", m_model_mat);
    m_shaderProgram->setMat4x4("view", view);
    m_shaderProgram->setMat4x4("projection", projection);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glBindVertexArray(VAO2);
    glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
}

void Cubo::updateModel(float deltaTime ){
    // RECUERDEN NO PUEDEN USAR GLM EN EL PROYECTO!!!! :(
    if (m_option == 1)
    {
        m_angulo += deltaTime *1.0;
        //std::cout<<m_option<<std::endl;
        m_model_mat = glm::mat4(1.0f);
        //m_model_mat = glm::translate(m_model_mat,glm::vec3(2.0f,0.0f,2.0f));
        m_model_mat= glm::rotate(m_model_mat,glm::radians(m_angulo),glm::vec3(0.0f,1.0f,0.0f));
        m_model_mat = glm::translate(m_model_mat,glm::vec3(2.0f,0.0f,2.0f));
    } else if (m_option == 2)
    {
        m_model_mat=glm::rotate(m_model_mat,glm::radians(deltaTime),glm::vec3(0.0f,1.0f,0.0f));
    } else 
    {
        m_model_mat=glm::rotate(m_model_mat,glm::radians(deltaTime),glm::vec3(0.0f,1.0f,0.0f));
    }
    
}

void Cubo::finish(){
}