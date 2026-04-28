#ifndef ORBITCAMERA_H 
#define ORBITCAMERA_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include <algorithm>
/**
 * @brief Clase que contiene el código necesario para implementar una cámara orbital
 */
class OrbitCamera
{
    private:
        /** @brief la posiicón de la cámara en coordenadas rectangulares */
        glm::vec3 m_pos;

        /** @brief el centro de atención */
        glm::vec3 m_coi;

        /** @brief Vector perpendicular a la cámara */
        glm::vec3 m_up;

        /** @brief el radio en coordenadas esféricas */
        float m_radius;

        /** @brief el angulo del azimutal */
        float m_theta;

        /** @brief anguulo en el plano */
        float m_phi;

        /**
         * @brief función auxiliar para calcular los ángulo
         */
        glm::vec2 getAngles(glm::vec2 mouseInit,glm::vec2 mouseCurr);

    public:

        /**
         * @brief Constructor que recibe las coordenadas cartesianas y las convierte a esféricas
         */
        OrbitCamera(glm::vec3 pos, glm::vec3 coi, glm::vec3 up):
        m_pos{pos},
        m_coi{coi},
        m_up{up}
        {
            m_radius = glm::distance(m_pos,m_coi);
            glm::vec3 direction = m_pos - m_coi;
            m_theta = std::atan2(direction.z,direction.x);
            m_phi = std::atan2(direction.y,direction.z);
        }

        /**
         * @brief función que devuelve la matriz de la vista
         */
        glm::mat4 getMatrix();

        /**
         * @brief Función para definir los angulos una vez se terminó de mover el mouse
         */
        void setPos(glm::vec2 mouseInit, glm::vec2 mouseCurr);

        /**
         * @brief Función que dtermina la posiicón final de la cámara
         */
        void rotate(glm::vec2 mouseInit, glm::vec2 mouseCurr);
};

#endif