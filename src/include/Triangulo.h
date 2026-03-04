#ifndef TRIANGULO_H
#define TRIANGULO_H

#include "Vector.h"

class Triangulo
{
public:
    Vector3 vertices[3];
    Vector2 proyecionVertices[3];

    void ProyecionVertice(int vertexIndice, float fovFactor);
    void RotacionVertice(int vertexIndice, Vector3 rotacion);
    void TrasladarVertice(int vertexIndice, Vector3 distancia);
};


#endif /* TRIANGULO_H */