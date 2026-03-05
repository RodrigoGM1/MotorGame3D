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

    /* Funciones */
    Motor();
    ~Motor();
    
    void destruirSDL(void);
    void manejarEventos(void);
    void limpiarPantalla(void);
    void actualizarPantalla(int ms);

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
};

#endif /* MOTOR_H */