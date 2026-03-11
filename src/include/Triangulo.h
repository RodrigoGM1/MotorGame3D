#ifndef TRIANGULO_H
#define TRIANGULO_H

#include "Vector.h"

class Triangulo
{
public:
    Triangulo() = default;

    bool culling = false;

    Vector3 vertices[3];
    Vector2 proyecionVertices[3];

    void ProyectarVertice(int verticeIndice, float fovFactor);
    void RotacionVertice(int verticeIndice, Vector3 rotacion);
    void TrasladarVertice(int verticeIndice, float* distancia);

    void AplicarCulling(float* camara);
};

#endif /* TRIANGULO_H */