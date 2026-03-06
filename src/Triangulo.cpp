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