#ifndef MOTOR_H
#define MOTOR_H

#include <iostream>
#include <SDL3/SDL.h>

#define ANCHOPANTALLA 900
#define ALTOPANTALLA  600

using namespace std;

class Motor
{
public:
    /* Variables */
    SDL_Renderer* renderizado;
    SDL_Window* ventana;
    SDL_Surface* superficie;
    SDL_Event eventos;
    int estado;

    unsigned int lastTime = 0, currentTime;
    float deltaTime;
    int anchoPantalla, altoPantalla;
    
    /* Funciones */
    Motor();
    ~Motor();
    
    void destruirSDL(void);
    void manejarEventos(void);
    void limpiarPantalla();
    void actualizarPantalla(int ms);

private:
    int iniciarSDL(void);
    void setDeltatime(void);

    void dibujarGrid();
};

#endif /* MOTOR_H */