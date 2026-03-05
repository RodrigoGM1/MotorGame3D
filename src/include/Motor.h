#ifndef MOTOR_H
#define MOTOR_H

#include <iostream>
#include <SDL3/SDL.h>

#include "Vector.h"
#include "Cubo.h"
#include "Triangulo.h"
#include "Malla.h"

#ifdef SDL_PLATFORM_PSP
    #define ANCHOPANTALLA 480
    #define ALTOPANTALLA  272
#else
    #define ANCHOPANTALLA 900
    #define ALTOPANTALLA  600
#endif

using namespace std;

class Motor
{
public:
    /* Variables */    
    SDL_Renderer* renderizado;
    SDL_Window* ventana;
    SDL_Event eventos;
    int estado;

    unsigned int lastTime = 0, currentTime;
    float deltaTime;
    
    uint32_t* colorBuffer;
    SDL_Texture* colorBufferTextura;

    float fovFactor = 200;
    Vector3 camaraPosision{0, 0, -5};

    /* Funciones */
    Motor();
    ~Motor();
    
    void destruirSDL(void);
    void manejarEventos(void);
    void limpiarPantalla();
    void actualizarPantalla(int ms);

    void dibujarPixel(int x, int y, unsigned int color);
    void dibujarLinea(int x0, int y0, int x1, int y1, unsigned int color);
    void dibujarTriangulo(int x0, int y0, int x1, int y1, int x2, int y2, unsigned int color);

    /**
     * Funciones de renderizado
    */
    // Cubo cubo;
    Malla malla;

    void Configuracion();
    void Actualizar();
    void Renderizar();

private:
    int iniciarSDL(void);
    void setDeltatime(void);

    void renderColorBuffer();
    void limpiarColorBuffer(uint32_t color);
    void dibujarGrid(uint32_t color);
};

#endif /* MOTOR_H */