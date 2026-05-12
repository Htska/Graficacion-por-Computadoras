#ifndef CUBE_H
#define CUBE_H

#include "Graphics/Model.h"

class Cube : public Model
{
private:
    GLfloat vertices[48];
    GLuint indices[36];

public:
    Cube(std::shared_ptr<ShaderProgram> program) : Model(program)
    {

        initGeometry();

        init();
    }

    ~Cube() override;

    void initGeometry() override;

    void init() override;
};

#endif