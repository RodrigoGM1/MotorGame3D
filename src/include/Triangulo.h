#ifndef TRIANGULO_H
#define TRIANGULO_H

#include <cstdint>

#include "Vector.h"
#include "Matriz.h"
#include "Luz.h"
#include "Textura.h"

class Triangulo
{
public:
    bool culling = false;
    uint32_t color = 0XFFFFFFFF;
    uint32_t originalColor = color;
    float profundidadPromedio;

    Vector3 vertices[3];
    Vector3 normal;
    // Vector2 proyecionVertices[3];
    Vector4 proyecionVertices[3];
    Textura2 texturaCordenadas[3]{};
    int texturaIndices[3];

    Triangulo() = default;
    // Triangulo(uint32_t color) : color(color){};
    Triangulo(uint32_t color) : color(color), originalColor(color){};
    Triangulo(uint32_t color, Textura2* texturaUVs) : color(color), originalColor(color){
        texturaCordenadas[0] = texturaUVs[0];
        texturaCordenadas[1] = texturaUVs[1];
        texturaCordenadas[2] = texturaUVs[2];
    };

    bool operator<(const Triangulo & t) const;

    // void ProyectarVertice(int verticeIndice, float fovFactor);
    void ProyectarVertice(int verticeIndice, Matriz4 proyecionMatriz);
    // void RotacionVertice(int verticeIndice, Vector3 rotacion);
    void TrasladarVertice(int verticeIndice, float* distancia);

    void EscalaVertice(int verticeIndice, Vector3 escala);
    void RotacionVertice(int verticeIndice, Vector3 rotacion);
    void TrasladarVertice(int verticeIndice, Vector3 traslacion);
    void MundoMatriz(int verticeIndice, Vector3 escala, Vector3 angulo, Vector3 trasladar);

    void CalcularNormal();
    void AplicarCulling(float* camara);
    void AplicarSombreado(Luz luz);
    void ProfundidadPromedio();
};

#endif /* TRIANGULO_H */