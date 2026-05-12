// Matrix4D.h
#ifndef MATRIX4D_H
#define MATRIX4D_H

#include <iostream>
#include <cassert>
#include "Vector3D.h"

#include "Math/MathUtils.h"

namespace linear::math {

    struct Matrix4D {
    private:
        float arr_2D[4][4]{}; // Column-major order for OpenGL

    public:
        Matrix4D() = default;
        
        
        static Matrix4D identity() {
            Matrix4D result;
            for (int i = 0; i < 4; i++)
                result(i, i) = 1.0f; // La diagonal es 1.0f 
            return result;
        }

        inline float& operator()(int i, int j) {
            assert(i >= 0 && i < 4 && j >= 0 && j < 4);
            return arr_2D[j][i]; // Column-major
        }

        inline const float& operator()(int i, int j) const {
            assert(i >= 0 && i < 4 && j >= 0 && j < 4);
            return arr_2D[j][i]; // Column-major
        }

        

        // IMPORTANTE 
        // Esta funcion es importante por que devuelve un puntero al primer elemento del arreglo 
        // OpenGL espera un puntero a 16 floats (matrix 4x4) en orden column-major 
        const float* value_ptr() const {
            return &arr_2D[0][0]; // Referencia al primer elmento del array 
        }


        // Construir una matrix de proyeccion en perspectiva 
        // near -> distancia al plano cercano 
        // far -> distancia al plano lejano 
        
        static Matrix4D perspective(float fov, float aspect, float near, float far) {
            Matrix4D result;
            float tanHalfFOV = tanf(fov / 2.0f);
            
            result(0,0) = 1.0f / (aspect * tanHalfFOV);
            result(1,1) = 1.0f / tanHalfFOV;
            result(2,2) = -(far + near) / (far - near);
            result(3,2) = -1.0f;                          // row3, col2 = -1 -> por que openGL mira en -z
            result(2,3) = -(2.0f * far * near) / (far - near); // row2, col3
            
            return result;
        }

        // Matrix View
        static Matrix4D lookAt(const Vector3D& eye, const Vector3D& center, const Vector3D& up) {
            // Conjunto ortogonal de vectores (mini sistema de referencia de la camara)
            // EYE = CAMERA POSITION IN WORLD SPACE 

            Vector3D direction = Normalize(center - eye); // DIRECTION < - Va a ser negativo por que la camara de OpenGL apunta hacias -Z 
            Vector3D right = Normalize(Cross(direction, up));  // RIGHT 
            Vector3D camera_up = Cross(right, direction);              // Up

            // Matriz de rotacion 
            Matrix4D R = identity();
            R(0,0) = right.x;  R(0,1) = right.y;  R(0,2) = right.z; // Renglon 2
            R(1,0) = camera_up.x;  R(1,1) = camera_up.y;  R(1,2) = camera_up.z; // Renglon 2
            R(2,0) = -direction.x; R(2,1) = -direction.y; R(2,2) = -direction.z; // 

            // Matriz de traslacion
            Matrix4D T = identity();
            T(0,3) = -eye.x;
            T(1,3) = -eye.y;
            T(2,3) = -eye.z;


            Matrix4D result = R * T;

            return result;
        }

        // Translation matrix
        static Matrix4D translate(const Vector3D& v) {
            Matrix4D result = identity();
            result(0,3) = v.x;
            result(1,3) = v.y;
            result(2,3) = v.z;
            return result;
        }

        // X-Rotation
        static Matrix4D rotateX(float angle) {
            Matrix4D result = identity();
            float c = cosf(math::radians(angle));
            float s = sinf(math::radians(angle));
                
            result(1, 1) = c;
            result(2, 1) = -s;
            result(1, 2) = s;
            result(2, 2) = c;
                
            return result;
        }

        // Y-Rotation
        static Matrix4D rotateY(float angle) {
            Matrix4D result = identity();
                float c = cosf(math::radians(angle));
                float s = sinf(math::radians(angle));
                
                result(0, 0) = c;
                result(2, 0) = s;
                result(0, 2) = -s;
                result(2, 2) = c;
                
                return result;
            }

        // Rotation around Z axis
        static Matrix4D rotateZ(float angle) {
            Matrix4D result = identity();
            float c = cosf(math::radians(angle));
            float s = sinf(math::radians(angle));
            
            result(0, 0) = c;
            result(1, 0) = -s;
            result(0, 1) = s;
            result(1, 1) = c;
            
            return result;
        }

        // Scale matrix
        static Matrix4D scale(const Vector3D& v) {
            Matrix4D result;
            result(0, 0) = v.x;
            result(1, 1) = v.y;
            result(2, 2) = v.z;
            result(3, 3) = 1.0f;
            return result;
        }

        friend Matrix4D operator*(const Matrix4D& a, const Matrix4D& b) {
            Matrix4D result;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    float sum = 0;
                    for (int k = 0; k < 4; k++) {
                        sum += a(i, k) * b(k, j);
                    }
                    result(i, j) = sum;
                }
            }
            return result;
        }
    };


    struct Vector4D {
        float x{}, y{}, z{}, w{};
        
        Vector4D() = default;
        Vector4D(float _x, float _y, float _z, float _w = 1.0f) 
            : x(_x), y(_y), z(_z), w(_w) {}
        
        // Convertir a 4D agregando la coordenada homogenea 
        explicit Vector4D(const Vector3D& v, float _w = 1.0f) 
            : x(v.x), y(v.y), z(v.z), w(_w) {}
        
        // Convertir de regreso a 3D usando la coordenada homogenea 
        Vector3D toVector3D() const {
            if (w != 0 && w != 1.0f) {
                return Vector3D(x/w, y/w, z/w);
            }
            return Vector3D(x, y, z);
        }
    };

    
    inline Vector4D operator*(const Matrix4D& m, const Vector4D& v) {
        return Vector4D(
            m(0,0)*v.x + m(1,0)*v.y + m(2,0)*v.z + m(3,0)*v.w,
            m(0,1)*v.x + m(1,1)*v.y + m(2,1)*v.z + m(3,1)*v.w,
            m(0,2)*v.x + m(1,2)*v.y + m(2,2)*v.z + m(3,2)*v.w,
            m(0,3)*v.x + m(1,3)*v.y + m(2,3)*v.z + m(3,3)*v.w
        );
    }

    inline Vector3D operator*(const Matrix4D& m, const Vector3D& v) {
        Vector4D v4(v, 1.0f);
        Vector4D result = m * v4;
        return result.toVector3D(); // usamos la coordenada homogenea 
    }
}

#endif