#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

class Vector2
{
public:
    double x;
    double y;
};

class Vector3
{
public:
    double x;
    double y;
    double z;

    Vector2 OrtogonalProyecion(float fovFactor);
    Vector2 PerspectivaProyecion(float fovFactor);

    void Rotacion(Vector3 angulos);

private:
    void rotacionX(float angulo);
    void rotacionY(float angulo);
    void rotacionZ(float angulo);
};

#endif /* VECTOR_H */