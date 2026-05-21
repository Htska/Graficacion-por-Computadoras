#include "models/CustomModel.h"
#include "Utils/obj_helpers/ObjLoader.h"

CustomModel::~CustomModel()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(NUM_VBOS, m_VBO);
    glDeleteBuffers(1, &m_EBO);
    glDeleteTextures(1, &m_textureID);
}

/**
 * @brief Carga los datos desde el archivo OBJ y los prepara para la indexación.
 */
void CustomModel::initGeometry()
{
    ObjLoader obj_loader;
    obj_loader.parseOBJ(m_filePath);

    // Obtenemos los vectores procesados por el loader (ya sin duplicados)
    std::vector<float> verts = obj_loader.getVertices();
    std::vector<float> tcs = obj_loader.getTextureCoordinates();
    std::vector<float> normals = obj_loader.getNormals();
    m_indices = obj_loader.getIndices(); // Asegúrate de que ObjLoader tenga este getter

    max = obj_loader.getMax();
    min = obj_loader.getMin();
    // Pasamos los datos a los miembros de la clase
    m_vertices = verts;
    m_textCoords = tcs;
    m_normalVecs = normals;

    // Guardamos la cantidad de índices para el draw call
    m_numIndices = static_cast<int>(m_indices.size());

    //Cálculos para el bounding box
    glm::vec3 centro = glm::vec3((max[0]+min[0])*0.5f,(max[1]+min[1])*0.5f,(max[2]+min[2])*0.5f);
    glm::vec3 dimension = glm::vec3((max[0]-min[0]),(max[1]-min[1]),(max[2]-min[2]));
    float escalaFactor = 1.0f/(float)(std::max({dimension.x,dimension.y,dimension.z}));
    glm::mat4 escalamiento = glm::scale(glm::mat4(1.0f),glm::vec3(escalaFactor*3.0f));

    m_model_mat = glm::translate(escalamiento, -centro);
}

/**
 * @brief Configura el VAO, VBOs y el EBO en la GPU.
 */
void CustomModel::init()
{
    // 1. Generar objetos
    glGenVertexArrays(1, &VAO);
    glGenBuffers(NUM_VBOS, m_VBO);
    glGenBuffers(1, &m_EBO);

    // 2. Atar el VAO para empezar a grabar la configuración
    glBindVertexArray(VAO);

    // --- POSICIONES (Atributo 0) ---
    if (!m_vertices.empty())
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO[0]);
        glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), m_vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(0);
    }

    // --- TEXTURAS (Atributo 1) ---
    if (!m_textCoords.empty())
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO[1]);
        glBufferData(GL_ARRAY_BUFFER, m_textCoords.size() * sizeof(float), m_textCoords.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(1);
    }

    // --- NORMALES (Atributo 2) ---
    if (!m_normalVecs.empty())
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO[2]);
        glBufferData(GL_ARRAY_BUFFER, m_normalVecs.size() * sizeof(float), m_normalVecs.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(2);
    }

    // --- ELEMENT BUFFER (EBO) ---
    if (!m_indices.empty())
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);
    }
    else
    {
        std::cerr << "CUSTOM_MODEL_ERROR: No se pudieron cargar los índices para: " << m_filePath << std::endl;
    }

    // Desatamos el VAO
    glBindVertexArray(0);
}

void CustomModel::renderModel(const glm::mat4 &view, const glm::mat4 &projection, Light* light)
{

    if (m_numIndices == 0)
        return;

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
    glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void CustomModel::RenderTexture() const {
    glActiveTexture(GL_TEXTURE0); // Activamos unidad de textura 0 
    glBindTexture(GL_TEXTURE_2D, m_textureID); // asignamos una textura a esa unidad 
    // Le pasamos 0 por que es la unidad de textura que definimos en el fragment shader 
    m_shaderProgram->setTextureUnit("samp", 0);
}




void CustomModel::updateModel(float deltaTime)
{

    m_model_mat = glm::rotate(m_model_mat, glm::radians(deltaTime), glm::vec3(0.0f,1.0f,0.0f));
}

void CustomModel::finish(){}