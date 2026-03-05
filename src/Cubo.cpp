#include "include/Cubo.h"
#include "include/Motor.h"

Cubo::Cubo(Motor* motor, int longuitud)
{
    this->motor = motor;

    if(longuitud % 2 == 0){
        longuitud++;
    }

    puntos = std::make_unique<Vector3[]>(longuitud * longuitud * longuitud);
    proyecionPuntos = std::make_unique<Vector2[]>(longuitud * longuitud * longuitud);

    float porcion = 1.0f / (longuitud / 2);

    for(float x = -1.0; x <= 1; x += porcion){
        for(float y = -1.0; y <= 1; y += porcion){
            for(float z = -1.0; z <= 1; z += porcion){
                puntos[conteoPuntos++] = Vector3{x, y, z};
            }
        }
    }
}

void Cubo::SetRotacion(float x, float y, float z)
{
    rotacionActual = {x, y, z};
}

void Cubo::Actualizar(float deltaTime)
{
    rotacion.x += rotacionActual.x * deltaTime;
    rotacion.y += rotacionActual.y * deltaTime;
    rotacion.z += rotacionActual.z * deltaTime;

    for(size_t i = 0; i < conteoPuntos; i++){
        Vector3 punto = puntos[i];

        punto.Rotacion(rotacion);

        punto.z -= motor->camaraPosision.z;

        proyecionPuntos[i] = punto.PerspectivaProyecion(motor->fovFactor);
    }
}

void Cubo::Renderizar()
{
    /*
    for(size_t i = 0; i < conteoPuntos; i++){
        motor->dibujarPixel(
            proyecionPuntos[i].x + ANCHOPANTALLA / 2,
            proyecionPuntos[i].y + ALTOPANTALLA / 2,
            0xFF00FFFF
        );
    }
    */
}