#ifndef LUZ_H
#define LUZ_H

#include <stdint.h>

#include "Vector.h"

class Luz
{
public:
    Vector3 direcion;

    static uint32_t AplicarIntensidad(uint32_t color, float factorPorcentaje)
    {
        uint32_t a = (color & 0xFF000000);
        uint32_t r = (color & 0x00FF0000) * factorPorcentaje;
        uint32_t g = (color & 0x0000FF00) * factorPorcentaje;
        uint32_t b = (color & 0x000000FF) * factorPorcentaje;

        uint32_t nuevoColor = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);
        return nuevoColor;
    }
};

#endif