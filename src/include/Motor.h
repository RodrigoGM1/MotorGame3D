#ifndef MOTOR_H
#define MOTOR_H

#include <iostream>
#include <SDL3/SDL.h>

#ifdef SDL_PLATFORM_PSP
    #define ANCHOPANTALLA 480
    #define ALTOPANTALLA  272
#else
    #define ANCHOPANTALLA 1920
    #define ALTOPANTALLA  1080
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

    /* Funciones */
    Motor();
    ~Motor();
    
    void destruirSDL(void);
    void manejarEventos(void);
    void limpiarPantalla(void);
    void actualizarPantalla(int ms);

    // void dibujarRect(int sx, int sy, int ancho, int alto, uint32_t color);
    void dibujarPixel(int x, int y, unsigned int color);

private:
    int iniciarSDL(void);
    void setDeltatime(void);

public:
     /**
     * Funciones de renderizado
    */
    void Configuracion(void);
    void Actualizar(void);
    void Renderizar(void);

    void renderColorBuffer();
    void limpiarColorBuffer(uint32_t color);
    void dibujarGrid(uint32_t color);
};

#endif /* MOTOR_H */