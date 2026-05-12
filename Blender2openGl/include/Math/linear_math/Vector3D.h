#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>
#include <cmath>
#include <cassert>
namespace linear::math{

    struct Vector3D{
        float x{},y{},z{}; 

        Vector3D()=default;

        Vector3D(float a, float b, float c)
            : x{a}, y{b}, z{c}
            {};
        
        inline float& operator[](int i){
            assert(0<=i && i<=2 ); 
            return *(&x+i); 
        }

        inline Vector3D& operator=(const Vector3D& other) {
        // Verificación de auto-asignación (v = v)
        if (this != &other) {
            x = other.x;
            y = other.y;
            z = other.z;
        }
        return *this;
        }

        // const inline Vector3D& operator=(const Vector3D& other) {
        // // Verificación de auto-asignación (v = v)
        // if (this != &other) {
        //     x = other.x;
        //     y = other.y;
        //     z = other.z;
        // }
        // return *this;
        // }

        inline const float& operator[](int i)const{
            assert(0<=i && i<=2 ); 
            return *(&x+i); 
        }

        inline void operator+=(float s){
            x+=s;
            y+=s;
            z+=s;
        }
        
        inline void operator-=(float s){
            x-=s;
            y-=s;
            z-=s;
        }

        inline void operator*=(float s){
            x*=s;
            y*=s;
            z*=s;
        }

        inline void operator/=(float s){
            x/=s;
            y/=s;
            z/=s;
        }

        inline friend std::ostream& operator<<(std::ostream& os,const Vector3D& v){
            os  << "[ " << v.x << "\n" 
                << "  " << v.y << "\n"
                << "  " << v.z <<" ]";
            return os;
        }

    };

    inline Vector3D operator * (const Vector3D& v, float s){
        return Vector3D{v.x*s,v.y*s,v.z*s};
    }

    inline Vector3D operator / (const Vector3D& v, float s){
        return Vector3D{v.x/s,v.y/s,v.z/s};
    }

    inline Vector3D operator+(const Vector3D& v, const Vector3D& u){
        return Vector3D{v.x+u.x, v.y+u.y, v.z+u.z};
    }

    inline Vector3D operator-(const Vector3D& v, const Vector3D& u){
        return Vector3D{v.x-u.x, v.y-u.y, v.z-u.z};
    }

    // Magnitude 
    inline float Magnitude(const Vector3D& v){
        return std::sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
    }

    inline Vector3D Normalize(const Vector3D& v){
        float mag {Magnitude(v)};
        if(mag==0) return Vector3D{}; 
        return v/mag;
    }

    inline float Dot(const Vector3D& v, const Vector3D& u){
        return v.x*u.x + v.y*u.y + v.z*u.z; 
    }

    inline Vector3D Cross(const Vector3D& v, const Vector3D& u){
        return Vector3D{v.y*u.z - v.z*u.y, v.z*u.x - v.x*u.z, v.x*u.y - v.y*u.x};
    }
};


#endif