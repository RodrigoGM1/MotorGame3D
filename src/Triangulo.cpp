#include "include/Triangulo.h"

void Triangulo::ProyecionVertice(int vertexIndice, float fovFactor)
{
    proyecionVertices[vertexIndice] = vertices[vertexIndice].PerspectivaProyecion(fovFactor);
}

void Triangulo::RotacionVertice(int vertexIndice, Vector3 rotacion)
{
    vertices[vertexIndice].Rotacion(rotacion);
}

void Triangulo::TrasladarVertice(int vertexIndice, Vector3 distancia)
{
    vertices[vertexIndice].x -= distancia.x;
    vertices[vertexIndice].y -= distancia.y;
    vertices[vertexIndice].z -= distancia.z;
}