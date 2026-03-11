#include "include/Cubo.h"
#include "include/Motor.h"

Cubo::Cubo(Motor* motor, int nPunots)
{
    this->motor = motor;

    if(nPunots % 2 == 0){
        nPunots++;
    }

    puntos = std::make_unique<Vector3[]>(nPunots * nPunots * nPunots);
    proyecionPunto = std::make_unique<Vector2[]>(nPunots * nPunots * nPunots);

    float porcion = 1.0f / (nPunots / 2);

    for(float x = -1; x <= 1; x += porcion){
        for(float y = -1; y <= 1; y += porcion){
            for(float z = -1; z <= 1; z += porcion){
                puntos[puntosConteo++] = Vector3{x, y, z};
            }
        }
    }
}
    
void Cubo::SetRotacion(float x, float y, float z)
{
    rotacionActual = {x, y, z};
}

void Cubo::Actualizar()
{
    rotacion.x += rotacionActual.x;
    rotacion.y += rotacionActual.y;
    rotacion.z += rotacionActual.z;

    for(size_t i = 0; i < puntosConteo; i++){
        Vector3 punto = puntos[i];

        punto.Rotacion(rotacion);

        punto.z -= motor->camaraPosision[2];

        proyecionPunto[i] = punto.PerspectivaProyecion(motor->fovFactor);
    }
}

void Cubo::Renderizado()
{
    for(size_t i = 0; i < puntosConteo; i++){
        motor->dibujarPixel(
            proyecionPunto[i].x + ANCHOPANTALLA / 2,
            proyecionPunto[i].y + ALTOPANTALLA / 2,
            0xFF00FFFF
        );
    }
}