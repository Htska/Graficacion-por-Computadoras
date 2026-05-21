#include "models/QuadNormal.h"

QuadNormal::~QuadNormal()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &m_textureID);
    glDeleteTextures(1, &m_textureNormalID);
}


void QuadNormal::initGeometry()
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
     // calculate tangent/bitangent vectors of both triangles
    glm::vec3 tangent1, bitangent1;
    glm::vec3 tangent2, bitangent2;
    // triangle 1
    // ----------
    glm::vec3 edge1 = pos2 - pos1;
    glm::vec3 edge2 = pos3 - pos1;
    glm::vec2 deltaUV1 = uv2 - uv1;
    glm::vec2 deltaUV2 = uv3 - uv1;

    float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

    bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

    // triangle 2
    // ----------
    edge1 = pos3 - pos1;
    edge2 = pos4 - pos1;
    deltaUV1 = uv3 - uv1;
    deltaUV2 = uv4 - uv1;

    f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);


    bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

    // Vértice 1
    vertices[0] = pos1.x;
    vertices[1] = pos1.y;
    vertices[2] = pos1.z;
    vertices[3] = nm.x;
    vertices[4] = nm.y;
    vertices[5] = nm.z;
    vertices[6] = uv1.x;
    vertices[7] = uv1.y;
    vertices[8] = tangent1.x;
    vertices[9] = tangent1.y;
    vertices[10] = tangent1.z;
    vertices[11] = bitangent1.x;
    vertices[12] = bitangent1.y;
    vertices[13] = bitangent1.z;

    // Vértice 2
    vertices[14] = pos2.x;
    vertices[15] = pos2.y;
    vertices[16] = pos2.z;
    vertices[17] = nm.x;
    vertices[18] = nm.y;
    vertices[19] = nm.z;
    vertices[20] = uv2.x;
    vertices[21] = uv2.y;
    vertices[22] = tangent1.x;
    vertices[23] = tangent1.y;
    vertices[24] = tangent1.z;
    vertices[25] = bitangent1.x;
    vertices[26] = bitangent1.y;
    vertices[27] = bitangent1.z;

    // Vértice 3
    vertices[28] = pos3.x;
    vertices[29] = pos3.y;
    vertices[30] = pos3.z;
    vertices[31] = nm.x;
    vertices[32] = nm.y;
    vertices[33] = nm.z;
    vertices[34] = uv3.x;
    vertices[35] = uv3.y;
    vertices[36] = tangent1.x;
    vertices[37] = tangent1.y;
    vertices[38] = tangent1.z;
    vertices[39] = bitangent1.x;
    vertices[40] = bitangent1.y;
    vertices[41] = bitangent1.z;

    // Vértice 4
    vertices[42] = pos1.x;
    vertices[43] = pos1.y;
    vertices[44] = pos1.z;
    vertices[45] = nm.x;
    vertices[46] = nm.y;
    vertices[47] = nm.z;
    vertices[48] = uv1.x;
    vertices[49] = uv1.y;
    vertices[50] = tangent2.x;
    vertices[51] = tangent2.y;
    vertices[52] = tangent2.z;
    vertices[53] = bitangent2.x;
    vertices[54] = bitangent2.y;
    vertices[55] = bitangent2.z;

    // Vértice 5
    vertices[56] = pos3.x;
    vertices[57] = pos3.y;
    vertices[58] = pos3.z;
    vertices[59] = nm.x;
    vertices[60] = nm.y;
    vertices[61] = nm.z;
    vertices[62] = uv3.x;
    vertices[63] = uv3.y;
    vertices[64] = tangent2.x;
    vertices[65] = tangent2.y;
    vertices[66] = tangent2.z;
    vertices[67] = bitangent2.x;
    vertices[68] = bitangent2.y;
    vertices[69] = bitangent2.z;

    // Vértice 6
    vertices[70] = pos4.x;
    vertices[71] = pos4.y;
    vertices[72] = pos4.z;
    vertices[73] = nm.x;
    vertices[74] = nm.y;
    vertices[75] = nm.z;
    vertices[76] = uv4.x;
    vertices[77] = uv4.y;
    vertices[78] = tangent2.x;
    vertices[79] = tangent2.y;
    vertices[80] = tangent2.z;
    vertices[81] = bitangent2.x;
    vertices[82] = bitangent2.y;
    vertices[83] = bitangent2.z;

}

/**
 * @brief Configura el VAO, VBOs y el EBO en la GPU.
 */
void QuadNormal::init()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float)));
}

void QuadNormal::renderModel(const glm::mat4 &view, const glm::mat4 &projection, Light* light)
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

void QuadNormal::RenderTexture() const {
    glActiveTexture(GL_TEXTURE0); 
    glBindTexture(GL_TEXTURE_2D, m_textureID); 
    m_shaderProgram->setTextureUnit("samp", 0);
    glActiveTexture(GL_TEXTURE1); 
    glBindTexture(GL_TEXTURE_2D, m_textureNormalID); 
    m_shaderProgram->setTextureUnit("normalMap", 1);
}




void QuadNormal::updateModel(float deltaTime)
{

    m_model_mat = glm::rotate(m_model_mat, glm::radians(deltaTime), glm::vec3(0.0f,1.0f,0.0f));
}

void QuadNormal::finish(){}