#include "Graphics/ShaderProgram.h"

std::string ShaderProgram::readShaderSource(const char *filePath)
{
    std::ifstream fileStream(filePath, std::ios::in);
    if (!fileStream)
    {
        std::cerr << "ERROR: Cannot open shader file: " << filePath << std::endl;
        return "";
    }

    std::string content((std::istreambuf_iterator<char>(fileStream)),
                        std::istreambuf_iterator<char>());
    return content;
}

void ShaderProgram::shaderLog(GLuint shader_id) const
{
    GLint len = 0;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &len);
    if (len > 0)
    {
        std::vector<char> log(len);
        glGetShaderInfoLog(shader_id, len, nullptr, log.data());
        std::cerr << "SHADER INFO LOG: " << log.data() << std::endl;
    }
}

void ShaderProgram::programLog() const
{
    GLint len = 0;
    glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &len);
    if (len > 0)
    {
        std::vector<char> log(len);
        glGetProgramInfoLog(m_id, len, nullptr, log.data());
        std::cerr << "PROGRAM INFO LOG: " << log.data() << std::endl;
    }
}

GLuint ShaderProgram::compileShader(GLenum type, const std::string &src)
{
    GLuint id = glCreateShader(type);
    const char *c = src.c_str();
    glShaderSource(id, 1, &c, nullptr);
    glCompileShader(id);

    GLint status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        std::string kind = (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");
        std::cerr << kind << " SHADER ERROR" << std::endl;
        shaderLog(id);
    }

    return id;
}

void ShaderProgram::compileProgram(GLuint vertex_shader, GLuint fragment_shader)
{
    m_id = glCreateProgram();

    glAttachShader(m_id, vertex_shader);
    glAttachShader(m_id, fragment_shader);

    glLinkProgram(m_id);

    GLint linked;
    glGetProgramiv(m_id, GL_LINK_STATUS, &linked);
    if (linked != GL_TRUE)
    {
        std::cerr << "PROGRAM LINKING FAILED" << std::endl;
        programLog();
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void ShaderProgram::setVec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(m_id, name.c_str()), x, y, z);
}

// FOR GLM

void ShaderProgram::SetVec3(const std::string &name, glm::vec3 vector) const
{
    glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, &vector[0]);
}

void ShaderProgram::SetMat4x4(const std::string &name, const glm::mat4 &value) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

/**
 * Nueva Funcion para textura
 * @brief Busca la variable uniforme para textura
 *
 */
void ShaderProgram::SetTextureUnit(const std::string &name, int unit) const
{
    /**
     * Internamente los samplers se comportan como variables uniformes de tipo entero
     * 
     */
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), unit);
}