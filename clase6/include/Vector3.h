#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include <iostream>

/**
 * @brief Clase que representa vectores en 3 dimensiones
 */
class Vector3 
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

        /**
         * @brief Coordenada en z
         */
        float m_z;

    public:

        /**
         * @brief constructor por omisión
         */
        Vector3():m_x{0},m_y{0},m_z{0}{}

        /**
         * @brief Constructor
         * @param x la coordenada en x
         * @param y la coordenada en y
         * @param z la coordenada en z
         */
        Vector3(float x, float y,float z): m_x{x},m_y{y},m_z{z}{}

        /**
         * @brief Operación de suma de vectores, se sobrecarga el operador +
         * @param v el otro vector a ser sumado
         * @returns Vector3 el cual es la suma de los vectores
         */
        Vector3 operator+(const Vector3& v)
        {
            return Vector3(m_x+v.m_x,m_y+v.m_y,m_z+v.m_z);
        }

        /**
         * @brief función que regresa una copia del vector actual
         * @returns Vector2 la copia del vector
         */
        Vector3 clone()
        {
            return Vector3(m_x,m_y,m_z);
        }

        /**
         * @brief fucnión que calcula la distancia entre dos vectores
         * @returns float la distanci
         */
        static float distancia(Vector3 v,Vector3 u)
        {
            //TODO
            return 0.f;
        }

        /**
         * @brief Función que calcula la norma de un vector
         * @returns la norma
         */
        float norm()
        {
            //TODO
            //std::sqrt(m_x*m_x + m_y*m_y+m_z*m_z) 
            return 0.f;  
        }

        /**
         * @brief operación que realiza el producto punto entre dos vectores, sobrecarga el operador *
         * @param v el vector a mutliplicar
         * @returns float el resultado
         */
        float operator*(const Vector3& v)
        {
            return (m_x*v.m_x) + (m_y *v.m_y) + (m_z*v.m_z);
        }

        /**
         * @brief Operación de escalar por un vector
         * @param s el escalar
         * @returns una referencia a si mismo
         */
        Vector3& operator*(float s)
        {
            m_x = m_x*s;
            m_y = m_y*s;
            m_z = m_z*s;
            return *this;
        }

        /**
         * @brief función que compara dos vectores
         * @param v el vector a comparar
         * @returns true si el vector se encuentra en |v-epsilon|, false en otro caso
         */
        bool equals(const Vector3& v)
        {
            float epsilon = 0.00001f;
            bool x1 = m_x<=v.m_x+epsilon && m_x>= v.m_x-epsilon;
            bool y1 = m_y<=v.m_y+epsilon && m_y>= v.m_y-epsilon;
            bool z1 = m_z<=v.m_z+epsilon && m_z>= v.m_z-epsilon;

            return x1 && y1 && z1;
        }

        /**
         * @brief Función que regresa un vector normalizado
         * @returns el vector normalizado
         */
        Vector3 normalize()
        {
            //TODO
            return Vector3{};
        }

        /**
         * @brief función que asigna nuevos valores de coordenadas
         * @param x la nueva coordenada en x
         * @param y la nueva coordenada en y
         */
        void set(float x, float y, float z)
        {
            m_x = x;
            m_y = y;
            m_z = z;
        }

        /**
         * @brief función que realiza la resta de dos vectores, sobrecarga el operador -
         * @param v el vector a ser restado
         * @returns Vector3 el resultado de la resta
         */
        Vector3 operator-(const Vector3& v)
        {
            return Vector3(m_x-v.m_x,
                            m_y-v.m_y,
                            m_z-v.m_z);
        }

        /**
         * @brief función que asigna ceros a las coordenadas
         */
        void zero()
        {
            m_x = 0.f;
            m_y = 0.f;
            m_z = 0.f;
        }

        /**
         * @brief Función que sobrecarga el operador de flujo para poder imprimir el objeto 
         */
        friend std::ostream& operator<<(std::ostream& os,const Vector3& v) {
            os << "(" << v.m_x << ", " << v.m_y<< ", "<< v.m_z<< ")";
            return os;
        }

        /**
         * @brief Función que realiza el producto cruz entre vectores
         * @returns el vector 3 resultado del producto punto
         */
        Vector3 cross(Vector3 v){
            //TODO
            //
            return Vector3{};
        }

        /**
         * @brief Función que convierte el vector 3 en un arreglo de c++
         * @returns apuntador al primer eleemnto del arreglo
         */
        float* toArray(){
            float* arr = new float[3];
            //TODO
            float a = 8;
            return &a;
        }
};

#endif
