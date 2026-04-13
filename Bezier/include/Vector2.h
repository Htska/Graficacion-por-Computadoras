#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>
#include <iostream>

/**
 * @brief Clase que representa vectores en 2 dimensiones
 */
class Vector2 
{
    private:
        /**
         * @brief Coordenada en x
         */
        float m_x;

        /**
         * @brief Coordenada en y
         */
        float m_y;

    public:

        /**
         * @brief Constructor
         * @param x la coordenada en x
         * @param y la coordenada en y
         */
        Vector2(float x, float y): m_x{x},m_y{y}{}

        /**
         * @brief Operación de suma de vectores, se sobrecarga el operador +
         * @param v el otro vector a ser sumado
         * @returns Vector2 el cual es la suma de los vectores
         */
        Vector2 operator+(const Vector2& v)
        {
            return Vector2(m_x+v.m_x,m_y+v.m_y);
        }

        /**
         * @brief función que regresa una copia del vector actual
         * @returns Vector2 la copia del vector
         */
        Vector2 clone()
        {
            return Vector2(m_x,m_y);
        }

        /**
         * @brief fucnión que calcula la norma, distancia, o magnitud del vector
         * @returns float la norma
         */
        float distancia()
        {
            return std::sqrt(m_x*m_x + m_y*m_y);
        }

        /**
         * @brief operación que realiza el producto punto entre dos vectores, sobrecarga el operador *
         * @param v el vector a mutliplicar
         * @returns float el resultado
         */
        float operator*(const Vector2& v)
        {
            return (m_x*v.m_x) + (m_y *v.m_y);
        }

        /**
         * @brief Operación de escalar por un vector
         * @param s el escalar
         * @returns una referencia a si mismo
         */
        Vector2& operator*(float s)
        {
            m_x = m_x*s;
            m_y = m_y*s;
            return *this;
        }


        Vector2 lerp(const Vector2& v, float t)
        {
            float nuevo_x = t*m_x + (1-t)*v.m_x;
            float nuevo_y = t*m_y + (1-t)*v.m_y;
            return Vector2(nuevo_x,nuevo_y);
        }



        /**
         * @brief función que compara dos vectores
         * @param v el vector a comparar
         * @returns true si el vector se encuentra en |v-epsilon|, false en otro caso
         */
        bool equals(const Vector2& v)
        {
            float epsilon = 0.00001f;
            bool x1 = m_x<=v.m_x+epsilon && m_x>= v.m_x-epsilon;
            bool y1 = m_y<=v.m_y+epsilon && m_y>= v.m_y-epsilon;

            return x1 && y1;
        }

        /**
         * @brief Función que regresa un vector normalizado
         * @returns el vector normalizado
         */
        Vector2 normalize()
        {
            return Vector2(m_x/distancia(),m_y/distancia());
        }

        /**
         * @brief función que asigna nuevos valores de coordenadas
         * @param x la nueva coordenada en x
         * @param y la nueva coordenada en y
         */
        void set(float x, float y)
        {
            m_x = x;
            m_y = y;
        }

        /**
         * @brief funcipon que realiza la resta de dos vectores, sobrecarga el operador -
         * @param v el vector a ser restado
         * @returns Vector2 el resultado de la resta
         */
        Vector2 operator-(const Vector2& v)
        {
            return Vector2(m_x-v.m_x,m_y-v.m_y);
        }

        /**
         * @brief función que asigna ceros a las coordenadas
         */
        void zero()
        {
            m_x = 0.f;
            m_y = 0.f;
        }

        float getX(){
            return m_x;
        }

        float getY(){
            return m_y;
        }

        /**
         * @brief Función que sobrecarga el operador de flujo para poder imprimir el objeto 
         */
        friend std::ostream& operator<<(std::ostream& os,const Vector2& v) {
            os << "(" << v.m_x << ", " << v.m_y<<")";
            return os;
        }
};

#endif
