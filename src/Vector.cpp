#include "include/Vector.h"

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