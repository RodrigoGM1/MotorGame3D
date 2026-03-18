#include "include/Vector.h"
#include "include/Matriz.h"

Vector2 Vector2::operator+(const Vector2 &v) const
{
    return Vector2(
        x + v.x,
        y + v.y
    );
}

Vector2 Vector2::operator-(const Vector2 &v) const
{
    return Vector2(
        x - v.x,
        y - v.y
    );
}

Vector2 Vector2::operator*(float fovFactor) const
{
    return Vector2(
        x * fovFactor,
        y * fovFactor
    );
}

Vector2 Vector2::operator/(float fovFactor) const
{
    return Vector2(
        x / fovFactor,
        y / fovFactor
    );
}

float Vector2::Longitud()
{
    return sqrt(x * x + y * y);
}

float Vector2::ProductoPunto(const Vector2 &v) const
{
    return (x * v.x) + (y * v.y);
}

void Vector2::Normalizar()
{
    float longitud = Longitud();
    x = x / longitud;
    y = y / longitud;
}

Vector3 Vector3::operator+(const Vector3 &v) const
{
    return Vector3(
        x + v.x,
        y + v.y,
        z + v.z
    );
}

Vector3 Vector3::operator-(const Vector3 &v) const
{
    return Vector3(
        x - v.x,
        y - v.y,
        z - v.z
    );
}

Vector3 Vector3::operator*(float fovFactor) const
{
    return Vector3(
        x * fovFactor,
        y * fovFactor,
        z * fovFactor
    );
}

Vector3 Vector3::operator/(float fovFactor) const
{
    return Vector3(
        x / fovFactor,
        y / fovFactor,
        z / fovFactor
    );
}

float Vector3::Longitud()
{
    return sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::ProductoCruzado(const Vector3 &v) const
{
    return Vector3(
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
    );
}

float Vector3::ProductoPunto(const Vector3 &v) const
{
    return (x * v.x) + (y * v.y) + (z * v.z);
}

void Vector3::Normalizar()
{
    float longitud = Longitud();
    x = x / longitud;
    y = y / longitud;
    z = z / longitud;
}

Vector2 Vector3::OrtogonalProyecion(float fovFactor)
{
    return Vector2{
        fovFactor * x,
        fovFactor * y
    };
}

Vector2 Vector3::PerspectivaProyecion(float fovFactor)
{
    return Vector2{
        (fovFactor * x) / z,
        (fovFactor * y) / z
    };
}

void Vector3::Rotacion(Vector3 angulos)
{
    if(angulos.x != 0){
        RotacionX(angulos.x);
    }
    if(angulos.y != 0){
        RotacionY(angulos.y);
    }
    if(angulos.z != 0){
        RotacionZ(angulos.z);
    }
}

void Vector3::RotacionX(float angulo)
{
    double nuevoY = y * cos(angulo) - z * sin(angulo);
    double nuevoZ = y * sin(angulo) + z * cos(angulo);

    y = nuevoY;
    z = nuevoZ;
}

void Vector3::RotacionY(float angulo)
{
    double nuevoX = x * cos(angulo) - z * sin(angulo);
    double nuevoZ = x * sin(angulo) + z * cos(angulo);

    x = nuevoX;
    z = nuevoZ;
}

void Vector3::RotacionZ(float angulo)
{
    double nuevoX = x * cos(angulo) - y * sin(angulo);
    double nuevoY = x * sin(angulo) + y * cos(angulo);

    x = nuevoX;
    y = nuevoY;
}

Vector3 Vector4::ToVector3()
{
    return Vector3(x, y, z);
}

Vector4 Vector4::operator*(Matriz4 m) const
{
    Vector4 resultado;
    resultado.x = m.m[0][0] * x + m.m[0][1] * y + m.m[0][2] * z + m.m[0][3] * w;
    resultado.y = m.m[1][0] * x + m.m[1][1] * y + m.m[1][2] * z + m.m[1][3] * w;
    resultado.z = m.m[2][0] * x + m.m[2][1] * y + m.m[2][2] * z + m.m[2][3] * w;
    resultado.w = m.m[3][0] * x + m.m[3][1] * y + m.m[3][2] * z + m.m[3][3] * w;
    return resultado;
}