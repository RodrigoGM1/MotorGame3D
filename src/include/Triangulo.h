#ifndef TRIANGULO_H
#define TRIANGULO_H

#include <cstdint>

#include "Vector.h"

class Triangulo
{
public:
    Triangulo() = default;
    Triangulo(uint32_t color) : color(color){};
    
    bool culling = false;
    uint32_t color = 0XFFFFFFFF;
    float profundidadPromedio;

    Vector3 vertices[3];
    Vector2 proyecionVertices[3];

    bool operator<(const Triangulo & t) const;

    void ProyectarVertice(int verticeIndice, float fovFactor);
    void RotacionVertice(int verticeIndice, Vector3 rotacion);
    void TrasladarVertice(int verticeIndice, float* distancia);

    void AplicarCulling(float* camara);
    void ProfundidadPromedio();
};

#endif /* TRIANGULO_H */