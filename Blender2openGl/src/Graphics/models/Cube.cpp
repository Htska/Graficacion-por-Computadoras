#include "Graphics/models/Cube.h"

// #include "linear_math/Matrix3D.h"
// #include "Vector3D.h"

Cube::~Cube()
{
}

void Cube::initGeometry()
{
    vertices[0] = -0.5f;
    vertices[1] = -0.5f;
    vertices[2] = -0.5f;
    vertices[3] = -1.0f;
    vertices[4] = -1.0f;
    vertices[5] = -1.0f; // v0
    vertices[6] = 0.5f;
    vertices[7] = -0.5f;
    vertices[8] = -0.5f;
    vertices[9] = 1.0f;
    vertices[10] = -1.0f;
    vertices[11] = -1.0f; // v1
    vertices[12] = 0.5f;
    vertices[13] = 0.5f;
    vertices[14] = -0.5f;
    vertices[15] = 1.0f;
    vertices[16] = 1.0f;
    vertices[17] = -1.0f; // v2
    vertices[18] = -0.5f;
    vertices[19] = 0.5f;
    vertices[20] = -0.5f;
    vertices[21] = -1.0f;
    vertices[22] = 1.0f;
    vertices[23] = -1.0f; // v3
    vertices[24] = -0.5f;
    vertices[25] = -0.5f;
    vertices[26] = 0.5f;
    vertices[27] = -1.0f;
    vertices[28] = -1.0f;
    vertices[29] = 1.0f; // v4
    vertices[30] = 0.5f;
    vertices[31] = -0.5f;
    vertices[32] = 0.5f;
    vertices[33] = 1.0f;
    vertices[34] = -1.0f;
    vertices[35] = 1.0f; // v5
    vertices[36] = 0.5f;
    vertices[37] = 0.5f;
    vertices[38] = 0.5f;
    vertices[39] = 1.0f;
    vertices[40] = 1.0f;
    vertices[41] = 1.0f; // v6
    vertices[42] = -0.5f;
    vertices[43] = 0.5f;
    vertices[44] = 0.5f;
    vertices[45] = -1.0f;
    vertices[46] = 1.0f;
    vertices[47] = 1.0f; // v7

    indices[0] = 0;
    indices[1] = 2;
    indices[2] = 1;
    indices[3] = 3;
    indices[4] = 2;
    indices[5] = 0; // Cara trasera
    indices[6] = 4;
    indices[7] = 5;
    indices[8] = 6;
    indices[9] = 6;
    indices[10] = 7;
    indices[11] = 4; // Cara delantera
    indices[12] = 0;
    indices[13] = 1;
    indices[14] = 5;
    indices[15] = 5;
    indices[16] = 4;
    indices[17] = 0; // Cara inferior
    indices[18] = 2;
    indices[19] = 3;
    indices[20] = 7;
    indices[21] = 7;
    indices[22] = 6;
    indices[23] = 2; // Cara superior
    indices[24] = 0;
    indices[25] = 7;
    indices[26] = 3;
    indices[27] = 7;
    indices[28] = 0;
    indices[29] = 4; // Cara izquierda
    indices[30] = 1;
    indices[31] = 2;
    indices[32] = 6;
    indices[33] = 6;
    indices[34] = 5;
    indices[35] = 1; // Cara derecha
}

void Cube::init()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
}
