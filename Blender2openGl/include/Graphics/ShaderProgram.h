#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/**
 * @class ShaderProgram
 * @brief Clase que modela un ShaderProgram que compila y verifica vertex y fragment shader
 */
class ShaderProgram
{
private:
    /**
     * @brief Identificador del shader program
     */
    GLuint m_id{};

    /**
     * @brief Genera una cadena a partir de una ruta de un shader
     * @param filePath ruta del archivo del shader
     * @return cadena con codigo fuente del shader
     */
    static std::string readShaderSource(const char *filePath);

    /**
     * @brief Muestra informacion sobre el estado de compilacion del shader
     * @param shader_id Identificador del shader
     */
    void shaderLog(GLuint shader_id) const;

    /**
     * @brief Muestra informacion sobre el estado de compilacion del programa
     */
    void programLog() const;

    /**
     * @brief Genera id de un shader
     * @param type tipo del shader
     * @param src codigo fuente del shader
     * @return identificador del shader compilado
     */
    GLuint compileShader(GLenum type, const std::string &src);

    /**
     * @brief Compila los dos shaders en un programa
     * @param vertex_shader identificador del vertex shader
     * @param fragment_shader identificador del fragment_shader
     */
    void compileProgram(GLuint vertex_shader, GLuint fragment_shader);

public:
    ShaderProgram(const char *vertexPath, const char *fragmentPath)
    {
        std::string vsrc = readShaderSource(vertexPath);
        std::string fsrc = readShaderSource(fragmentPath);
        GLuint vs = compileShader(GL_VERTEX_SHADER, vsrc);
        GLuint fs = compileShader(GL_FRAGMENT_SHADER, fsrc);
        compileProgram(vs, fs);
    }

    ~ShaderProgram()
    {
        if (m_id)
            glDeleteProgram(m_id);
    }

    GLuint getId() const { return m_id; }

    void use() const { glUseProgram(m_id); }

    void setVec3(const std::string &name, float x, float y, float z) const;

    // GLM

    void SetVec3(const std::string &name, glm::vec3 vector) const;

    void SetMat4x4(const std::string &name, const glm::mat4 &value) const;

    void SetTextureUnit(const std::string &name, int unit) const;
};

#endif
