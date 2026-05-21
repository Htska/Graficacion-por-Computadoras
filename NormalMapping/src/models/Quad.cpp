#include "models/Quad.h"

Quad::~Quad()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &m_textureID);
}


void Quad::initGeometry()
{
    glm::vec3 pos1(-1.0f,  1.0f, 0.0f);
    glm::vec3 pos2(-1.0f, -1.0f, 0.0f);
    glm::vec3 pos3( 1.0f, -1.0f, 0.0f);
    glm::vec3 pos4( 1.0f,  1.0f, 0.0f);
    // texture coordinates
    glm::vec2 uv1(0.0f, 1.0f);
    glm::vec2 uv2(0.0f, 0.0f);
    glm::vec2 uv3(1.0f, 0.0f);  
    glm::vec2 uv4(1.0f, 1.0f);
    // normal vector
    glm::vec3 nm(0.0f, 0.0f, 1.0f);

    // Vértice 1
    vertices[0] = pos1.x;
    vertices[1] = pos1.y;
    vertices[2] = pos1.z;
    vertices[3] = nm.x;
    vertices[4] = nm.y;
    vertices[5] = nm.z;
    vertices[6] = uv1.x;
    vertices[7] = uv1.y;

    // Vértice 2
    vertices[8] = pos2.x;
    vertices[9] = pos2.y;
    vertices[10] = pos2.z;
    vertices[11] = nm.x;
    vertices[12] = nm.y;
    vertices[13] = nm.z;
    vertices[14] = uv2.x;
    vertices[15] = uv2.y;

    // Vértice 3
    vertices[16] = pos3.x;
    vertices[17] = pos3.y;
    vertices[18] = pos3.z;
    vertices[19] = nm.x;
    vertices[20] = nm.y;
    vertices[21] = nm.z;
    vertices[22] = uv3.x;
    vertices[23] = uv3.y;

    // Vértice 4 (pos1, nm, uv1)
    vertices[24] = pos1.x;
    vertices[25] = pos1.y;
    vertices[26] = pos1.z;
    vertices[27] = nm.x;
    vertices[28] = nm.y;
    vertices[29] = nm.z;
    vertices[30] = uv1.x;
    vertices[31] = uv1.y;

    // Vértice 5 (pos3, nm, uv3)
    vertices[32] = pos3.x;
    vertices[33] = pos3.y;
    vertices[34] = pos3.z;
    vertices[35] = nm.x;
    vertices[36] = nm.y;
    vertices[37] = nm.z;
    vertices[38] = uv3.x;
    vertices[39] = uv3.y;

    // Vértice 6 (pos4, nm, uv4)
    vertices[40] = pos4.x;
    vertices[41] = pos4.y;
    vertices[42] = pos4.z;
    vertices[43] = nm.x;
    vertices[44] = nm.y;
    vertices[45] = nm.z;
    vertices[46] = uv4.x;
    vertices[47] = uv4.y;

}

/**
 * @brief Configura el VAO, VBOs y el EBO en la GPU.
 */
void Quad::init()
{
    // configure plane VAO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

}

void Quad::renderModel(const glm::mat4 &view, const glm::mat4 &projection, Light* light)
{

    m_shaderProgram->use();

    m_shaderProgram->setMat4x4("model", m_model_mat);
    m_shaderProgram->setMat4x4("view", view);
    m_shaderProgram->setMat4x4("projection", projection);
    m_shaderProgram->setVec3("lightPos",light->getPos(view));
    m_shaderProgram->setVec3("La",light->getAmbient());
    m_shaderProgram->setVec3("Ld",light->getDiffuse());
    m_shaderProgram->setVec3("Ls",light->getSpecular());
    m_shaderProgram->setVec3("ka",m_ka);
    m_shaderProgram->setVec3("kd",m_kd);
    m_shaderProgram->setVec3("ks",m_ks);
    m_shaderProgram->setFloat("shininess",m_shininess);
    RenderTexture(); 

    // Al usar VAOs configurados en el init, solo bindeamos y dibujamos
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Quad::RenderTexture() const {
    glActiveTexture(GL_TEXTURE0); 
    glBindTexture(GL_TEXTURE_2D, m_textureID); 
    m_shaderProgram->setTextureUnit("samp", 0);
}




void Quad::updateModel(float deltaTime)
{

    m_model_mat = glm::rotate(m_model_mat, glm::radians(deltaTime), glm::vec3(0.0f,1.0f,0.0f));
}

void Quad::finish(){}