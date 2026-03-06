#ifndef CUBO_H
#define CUBO_H

#include <iostream>
#include <memory>

#include "Vector.h"

class Motor;

class Cubo
{
public:
    size_t puntosConteo{0};
    std::unique_ptr<Vector2[]> proyecionPunto;

private:
    Motor* motor;
    Vector3 rotacion;
    Vector3 rotacionActual;
    std::unique_ptr<Vector3[]> puntos;

public:
    Cubo() = default;
    Cubo(Motor* motor, int nPunots);
    
    void SetRotacion(float x, float y, float z);
    void Actualizar();
    void Renderizado();
};

#endif