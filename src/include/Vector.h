#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

class Vector2
{
public:
    double x;
    double y;

    Vector2() = default;
    Vector2(double x, double y) : x(x), y(y){};
    
    Vector2 operator+(const Vector2 &v) const;
    Vector2 operator-(const Vector2 &v) const;
    Vector2 operator*(float fovFactor) const;
    Vector2 operator/(float fovFactor) const;

    float Longitud();
    float ProductoPunto(const Vector2 &v) const;
    void Normalizar();
};

class Vector3
{
public:
    double x;
    double y;
    double z;

    Vector3() = default;
    Vector3(double x, double y, double z) : x(x), y(y), z(z){};

    Vector3 operator+(const Vector3 &v) const;
    Vector3 operator-(const Vector3 &v) const;
    Vector3 operator*(float fovFactor) const;
    Vector3 operator/(float fovFactor) const;

    float Longitud();
    Vector3 ProductoCruzado(const Vector3 &v) const;
    float ProductoPunto(const Vector3 &v) const;
    void Normalizar();

    Vector2 OrtogonalProyecion(float fovFactor);
    Vector2 PerspectivaProyecion(float fovFactor);
    void Rotacion(Vector3 angulos);

private:
    void RotacionX(float angulo);
    void RotacionY(float angulo);
    void RotacionZ(float angulo);
};

class Matriz4;
class Vector4
{
public:
    double x{0};
    double y{0};
    double z{0};
    double w{0};

    Vector4() = default;
    Vector4(Vector3 v) : x(v.x), y(v.y), z(v.z), w(1){};

    Vector3 ToVector3();

    Vector4 operator*(Matriz4 m) const;
};

#endif /* VECTOR_H */