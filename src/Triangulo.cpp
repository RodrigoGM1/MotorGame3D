#include "include/Triangulo.h"

void Triangulo::ProyectarVertice(int verticeIndice, float fovFactor)
{
    proyecionVertices[verticeIndice] = vertices[verticeIndice].PerspectivaProyecion(fovFactor);
}

void Triangulo::RotacionVertice(int verticeIndice, Vector3 rotacion)
{
    vertices[verticeIndice].Rotacion(rotacion);
}

void Triangulo::TrasladarVertice(int verticeIndice, Vector3 distancia)
{
    vertices[verticeIndice].x -= distancia.x;
    vertices[verticeIndice].y -= distancia.y;
    vertices[verticeIndice].z -= distancia.z;
}

void Triangulo::AplicarCulling(Vector3 camara)
{
    Vector3 vectorAB = this->vertices[1] - this->vertices[0];
    Vector3 vectorAC = this->vertices[2] - this->vertices[0];
    vectorAB.Normalizar();
    vectorAC.Normalizar();

    Vector3 normal = vectorAB.ProductoCruzado(vectorAC);
    normal.Normalizar();

    Vector3 camaraRay = camara - this->vertices[0];

    float normalCamara = normal.ProductoPunto(camaraRay);

    this->culling = (normalCamara < 0);
}