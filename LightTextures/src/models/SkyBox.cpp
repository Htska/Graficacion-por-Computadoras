#include "models/SkyBox.h"

void SkyBox::initGeometry(){
   
	vertices[0] = -1.0f;
    vertices[1] = -1.0f;
    vertices[2] =  1.0f;
	vertices[3] =  1.0f;
    vertices[4] = -1.0f;
    vertices[5] =  1.0f;
    vertices[6] =  1.0f;
    vertices[7] = -1.0f; 
    vertices[8] = -1.0f;
	vertices[9] = -1.0f;
    vertices[10] = -1.0f; 
    vertices[11] = -1.0f;
	vertices[12] = -1.0f;  
    vertices[13] = 1.0f;
    vertices[14] = 1.0f;
	vertices[15] = 1.0f;
    vertices[16] = 1.0f;
    vertices[17] = 1.0f;
	vertices[18] = 1.0f;
    vertices[19] = 1.0f;
    vertices[20] = -1.0f;
	vertices[21] = -1.0f;
    vertices[22] = 1.0f;
    vertices[23] = -1.0f;


	indices[0] = 1; 
    indices[1] = 2; 
    indices[2] = 6;
	indices[3] = 6; 
    indices[4] = 5; 
    indices[5] = 1;
	indices[6] = 0; 
    indices[7] = 4; 
    indices[8] = 7;
    indices[9] = 7; 
    indices[10] = 3; 
    indices[11] = 0;
	indices[12] = 4; 
    indices[13] = 5;
    indices[14] = 6;
	indices[15] = 6; 
    indices[16] = 7;
    indices[17] = 4;
	indices[18] = 0; 
    indices[19] = 3; 
    indices[20] = 2;
	indices[21] = 2;
    indices[22] = 1;
    indices[23] = 0;
	indices[24] = 0;
    indices[25] = 1;
    indices[26] = 5;
	indices[27] = 5;
    indices[28] = 4;
    indices[29] = 0;
	indices[30] = 3; 
    indices[31] = 7;
    indices[32] = 6;
    indices[33] = 6;
    indices[34] = 2;
    indices[35] = 3;
}

void SkyBox::init(){

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	std::string facesCubemap[6] =
	{
		"assets/skybox/right.jpg",
		"assets/skybox/left.jpg",
		"assets/skybox/top.jpg",
		"assets/skybox/bottom.jpg",
	    "assets/skybox/front.jpg",
		"assets/skybox/back.jpg"
	};

	glGenTextures(1, &cubemapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	// Cycles through all the textures and attaches them to the cubemap object
	for (unsigned int i = 0; i < 6; i++)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load(facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D
			(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB,
				width,
				height,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to load texture: " << facesCubemap[i] << std::endl;
			stbi_image_free(data);
		}
	}
    m_shaderProgram->use();
    m_shaderProgram->setTextureUnit("skybox",0);
}


void SkyBox::renderModel(const glm::mat4& view, const glm::mat4& projection, Light* light){
    glDepthFunc(GL_LEQUAL);
    m_shaderProgram->use();

    m_shaderProgram->setMat4x4("model", m_model_mat);
    m_shaderProgram->setMat4x4("view", glm::mat4(glm::mat3(view)));
    m_shaderProgram->setMat4x4("projection", projection);

    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glDepthFunc(GL_LESS);
}

void SkyBox::updateModel(float deltaTime ){}

void SkyBox::finish(){}