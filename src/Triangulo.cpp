#include "include/Triangulo.h"

bool Triangulo::operator<(const Triangulo & t) const
{
    return profundidadPromedio < t.profundidadPromedio;
}

void Triangulo::ProyectarVertice(int verticeIndice, float fovFactor)
{
    proyecionVertices[verticeIndice] = vertices[verticeIndice].PerspectivaProyecion(fovFactor);
}

void Triangulo::RotacionVertice(int verticeIndice, Vector3 rotacion)
{
    vertices[verticeIndice].Rotacion(rotacion);
}

void Triangulo::TrasladarVertice(int verticeIndice, float* distancia)
{
    vertices[verticeIndice].x -= distancia[0];
    vertices[verticeIndice].y -= distancia[1];
    vertices[verticeIndice].z -= distancia[2];
}

void Triangulo::AplicarCulling(float* camara)
{
    Vector3 vectorAB = this->vertices[1] - this->vertices[0];
    Vector3 vectorAC = this->vertices[2] - this->vertices[0];
    vectorAB.Normalizar();
    vectorAC.Normalizar();

    Vector3 normal = vectorAB.ProductoCruzado(vectorAC);
    normal.Normalizar();

    Vector3 camaraRay = Vector3(camara[0], camara[1], camara[2]) - this->vertices[0];

    float normalCamara = normal.ProductoPunto(camaraRay);

    this->culling = (normalCamara < 0);
}

void Triangulo::ProfundidadPromedio()
{
    profundidadPromedio = (vertices[0].z + vertices[1].z + vertices[2].z) / 3;
}