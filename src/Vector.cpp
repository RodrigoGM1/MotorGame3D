#include "include/Vector.h"

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