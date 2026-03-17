#ifndef CUBO_H
#define CUBO_H
// RECUERDEN NO PUEDEN USAR GLM EN EL PROYECTO!!!! :(
#include <glm/glm.hpp>
#include "Model.h"

class Cubo: public Model
{
private:
    GLfloat vertices[48];
    GLuint indices[36];
public: 

    Cubo(ShaderProgram* program) : Model(program){

        initGeometry();
        
        init();

    }

    void initGeometry() override;

    void init() override;

    // RECUERDEN NO PUEDEN USAR GLM EN EL PROYECTO!!!! :(
    void renderModel(const glm::mat4& view, const glm::mat4& projection) override;

    void updateModel(float deltaTime) override;

    void finish() override;

}; 

#endif
