#ifndef LIGHT_H 
#define LIGHT_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
/**
 * @brief Clase que contiene el código necesario para definir los componentes de la luz
 */
class Light
{
    private:

        /** @brief La posición de la cámara */
        glm::vec4 m_pos;

        /** @brief Valor de la luz ambiental */
        glm::vec3 m_La;

        /** @brief Valor de la luz difusa */
        glm::vec3 m_Ld;

        /* @brief Valor de la luz especular*/
        glm::vec3 m_Ls;

    public:

        /**
         * @brief Constructor que recibe los valores de la luz
         */
        Light(glm::vec4 pos, glm::vec3 La, glm::vec3 Ld, glm::vec3 Ls):
        m_pos{pos},
        m_La{La},
        m_Ld{Ld},
        m_Ls{Ls}
        {}

        /** @brief Función para obtener la posición de la cámara */
        glm::vec3 getPos(glm::mat4 view);

        /** @brief Función para obtener el valor de la luz ambiental */
        glm::vec3 getAmbient();

        /** @brief Función para obtener el valor de la luz difusa */
        glm::vec3 getDiffuse();

        /** @brief Función para obtener el valor de la luz especular */
        glm::vec3 getSpecular();
};

#endif