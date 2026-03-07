#ifndef MALLA_H
#define MALLA_H

#include <iostream>
#include <deque>
#include <fstream>
#include <algorithm>

#include "Vector.h"
#include "Triangulo.h"

class Motor;

class Malla
{
private:
    Motor* motor;
    Vector3 rotacion{0, 0, 0};
    Vector3 rotacionActual;
    std::deque<Vector3> caras;
    std::deque<Vector3> vertices;
    std::deque<Triangulo> triangulos;

public:
    Malla() = default;
    Malla(Motor* motor, Vector3* vertices, int nVertices, Vector3* caras, int nCaras);
    Malla(Motor* motor, std::string direccion);
    
    void SetRotacion(float x, float y, float z);

    void Actualizar(float deltaTime);
    void Renderizar();
};

#endif /* MALLA_H */