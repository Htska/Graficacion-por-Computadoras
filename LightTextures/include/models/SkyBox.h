#ifndef SKYBOX_H
#define SKYBOX_H
#include <glm/glm.hpp>
#include "Model.h"
#include "Utils/stb_image.h"

class SkyBox: public Model
{
private:
    GLfloat vertices[24];

    GLuint indices[36];

    unsigned int cubemapTexture; 
    
public: 

    SkyBox(ShaderProgram* program) : Model(program){
        initGeometry();
        
        init();
        m_model_mat = glm::mat4(1.0f);
    }

    void initGeometry() override;

    void init() override;

    void renderModel(const glm::mat4& view, const glm::mat4& projection, Light* light) override;

    void updateModel(float deltaTime) override;

    void finish() override;

}; 

#endif
