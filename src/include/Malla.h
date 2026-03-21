#ifndef MALLA_H
#define MALLA_H

#include <iostream>
#include <deque>
#include <fstream>
#include <algorithm>

#include "Vector.h"
#include "Triangulo.h"
#include "Textura.h"
#include "upng.h"

class Motor;

class Malla
{
private:
    int texturaAncho{0};
    int texturaAlto{0};
    upng_t* pngTexture{nullptr};
    uint32_t* mallaTextura{nullptr};

    Motor* motor;
    // Vector3 rotacion{0, 0, 0};
    Vector3 rotacionActual;
    std::deque<Vector3> caras;
    std::deque<Vector3> vertices;
    std::deque<Triangulo> triangulos;
    std::deque<Textura2> cordenadas;

public:
    Vector3 escala{1, 1, 1};
    Vector3 rotacion{0, 0, 0};
    Vector3 traslacion{0, 0, -2};

    Malla() = default;
    Malla(Motor* motor, Vector3* vertices, int nVertices, Vector3* caras, int nCaras);
    Malla(Motor* motor, Vector3* vertices, int nVertices, Vector3* caras, int nCaras, uint32_t* colores);
    Malla(Motor* motor, Vector3* vertices, int nVertices, Vector3* caras, int nCaras, uint32_t* colores, Textura2* texturaUV);
    Malla(Motor* motor, std::string direccion);
    Malla(Motor* motor, std::string direccion, std::string direccionTex);
    
    void SetRotacion(float x, float y, float z);
    void SetEscala(float* escala);
    void SetTraslacion(float* traslacion);

    void Actualizar(float deltaTime);
    void Renderizar();

    void Liberar();
};

#endif /* MALLA_H */