#ifndef VEC3H
#define VEC3H

#include <math.h>
#include <iostream>

class vec3 {
    public:
        double e[3];
        
        vec3() : e{0, 0, 0} {}
        vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}
        inline double x() const { return e[0]; }
        inline double y() const { return e[1]; }
        inline double z() const { return e[2]; }
        inline double r() const { return e[0]; }
        inline double g() const { return e[1]; }
        inline double b() const { return e[2]; }
        
        //unary operator overloading
        inline const vec3& operator+() const { return *this; }
        inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
        inline double operator[](int i) const { return e[i]; }
        inline double& operator[](int i) { return e[i]; }

        //binary operator overloading
        inline vec3& operator+=(const vec3 &v){
            e[0] += v.e[0];
            e[1] += v.e[1];
            e[2] += v.e[2];
            return *this;
        }
        inline vec3& operator-=(const vec3 &v){
            e[0] -= v.e[0];
            e[1] -= v.e[1];
            e[2] -= v.e[2];
            return *this;
        }
        inline vec3& operator*=(const vec3 &v){
            e[0] *= v.e[0];
            e[1] *= v.e[1];
            e[2] *= v.e[2];
            return *this;
        }

        inline vec3& operator*=(const double t){
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        } 
        inline vec3& operator/=(const double t){
            return *this *= 1/t;
        }
        
        //magnitude vector operations
        inline double length() const { 
            return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]); 
        }

        inline double squared_length() const { 
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2]; 
        }
};

using point3 = vec3; //essentially a glorified typedef but for the whole class
using color3 = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}
//Vector Utility Functions

inline vec3 operator+(const vec3& v1, const vec3& v2) {
    return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
} 
inline vec3 operator-(const vec3& v1, const vec3& v2) {
    return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}
inline vec3 operator*(const vec3& v1, const vec3& v2) {
    return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}
inline vec3 operator*(const double& d, const vec3& v) {
    return vec3(d * v.e[0], d * v.e[1], d * v.e[2]);
}
inline vec3 operator*(const vec3& v, const double& d) {
    return vec3(d * v.e[0], d * v.e[1], d * v.e[2]);
}
inline vec3 operator/(const vec3& v, const double& d) {
    return v * (1/d);
}

//other common operations
inline double dot(const vec3& v1, const vec3& v2) {
    return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}
inline vec3 cross(const vec3& v1, const vec3& v2) {
    return vec3(
        v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
        v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],  
        v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]
    );
}
inline vec3 unit_vector(const vec3& v){
    return v / v.length();
}
#endif
