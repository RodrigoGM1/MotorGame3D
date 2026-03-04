#ifndef CUBO_H
#define CUBO_H

#include <iostream>
#include <memory>

#include "Vector.h"

class Motor;

class Cubo
{
public:
    size_t conteoPuntos{0};
    std::unique_ptr<Vector2[]> proyecionPuntos;

private:
    Motor* motor;
    Vector3 rotacion;
    Vector3 rotacionActual;
    std::unique_ptr<Vector3[]> puntos;

public:
    Cubo() = default;
    Cubo(Motor* motor, int longuitud);

    void SetRotacion(float x, float y, float z);
    void Actualizar(float deltaTime);
    void Renderizar();
};

#endif /* CUBO_H */