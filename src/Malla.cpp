#include "include/Malla.h"
#include "include/Motor.h"

Malla::Malla(Motor* motor, Vector3* vertices, int nVertices, Vector3* caras, int nCaras)
{
    this->motor = motor;

    for(int i = 0; i < nVertices; i++){
        this->vertices.push_back(vertices[i]);
    }
    for(int i = 0; i < nCaras; i++){
        this->caras.push_back(caras[i]);
        this->triangulos.push_back(Triangulo());
    }
}

void Malla::SetRotacion(float x, float y, float z)
{
    rotacionActual = {x, y, z};
}

void Malla::Actualizar(float deltaTime)
{
    rotacion.x += rotacionActual.x * deltaTime;
    rotacion.y += rotacionActual.y * deltaTime;
    rotacion.z += rotacionActual.z * deltaTime;

    for(size_t i = 0; i < triangulos.size(); i++){
        triangulos[i].vertices[0] = vertices[static_cast<int>(caras[i].x)];
        triangulos[i].vertices[1] = vertices[static_cast<int>(caras[i].y)];
        triangulos[i].vertices[2] = vertices[static_cast<int>(caras[i].z)];

        for(size_t j = 0; j < 3; j++){
            triangulos[i].RotacionVertice(j, rotacion);
            
            triangulos[i].TrasladarVertice(j, motor->camaraPosision);

            triangulos[i].ProyecionVertice(j, motor->fovFactor);

            triangulos[i].proyecionVertices[j].x += ANCHOPANTALLA / 2;
            triangulos[i].proyecionVertices[j].y += ALTOPANTALLA / 2;
        }
    }
}

void Malla::Renderizar()
{
    for(size_t i = 0; i < triangulos.size(); i++){
        motor->dibujarTriangulo(
            triangulos[i].proyecionVertices[0].x,
            triangulos[i].proyecionVertices[0].y,
            triangulos[i].proyecionVertices[1].x,
            triangulos[i].proyecionVertices[1].y,
            triangulos[i].proyecionVertices[2].x,
            triangulos[i].proyecionVertices[2].y,
            0xFF00FFFF
        );
    }
}