#include "include/Motor.h"

/**
 * Declaraciones de funciones de la clase motor
*/
Motor::Motor()
{
    this->renderizado = nullptr;
    this->ventana = nullptr;
    this->superficie = nullptr;
    SDL_zero(this->eventos);
    this->estado = 0;
    this->lastTime = SDL_GetTicks();
    
    if(iniciarSDL()){
        cout<<"No se pudo iniciar SDL3"<<endl;
        destruirSDL();
    }
}

Motor::~Motor()
{
    destruirSDL();
}

void Motor::destruirSDL()
{
    SDL_DestroySurface(this->superficie);
    SDL_DestroyRenderer(this->renderizado);
    SDL_DestroyWindow(this->ventana);
}

void Motor::manejarEventos()
{
    while(SDL_PollEvent(&this->eventos)){
        switch(this->eventos.type){
            case SDL_EVENT_QUIT:
                estado = 0;
                break;
        }
    }
}

void Motor::limpiarPantalla()
{
    this->superficie = SDL_GetWindowSurface(ventana);
    SDL_SetRenderDrawColor(renderizado, 63, 63, 63, 0);
    SDL_RenderClear(renderizado);
    SDL_GetRenderOutputSize(renderizado, &this->anchoPantalla, &this->altoPantalla);
    
    setDeltatime();
    dibujarGrid();
}

void Motor::actualizarPantalla(int ms)
{
    SDL_UpdateWindowSurface(ventana);
    SDL_SetRenderVSync(renderizado, false);
    SDL_SetRenderClipRect(renderizado, NULL);
    SDL_RenderPresent(renderizado);

    SDL_Delay(ms);
}

/**
 * Funciones privadas
*/
int Motor::iniciarSDL()
{
    SDL_InitFlags banderasInicio = SDL_INIT_VIDEO;
    SDL_WindowFlags banderasVentana = SDL_WINDOW_RESIZABLE;
    if(!SDL_Init(banderasInicio)){
        SDL_Log("No se pudo iniciar SDL3");
        return 1;
    }
    if(!SDL_CreateWindowAndRenderer("Game", ANCHOPANTALLA, ALTOPANTALLA, banderasVentana, &this->ventana, &renderizado)){
        SDL_Log("No se pudo crear la ventana SDL3");
        return 1;
    }
    this->estado = 1;
    return 0;
}

void Motor::setDeltatime(void)
{
    currentTime = SDL_GetTicks();
    deltaTime = (float)(currentTime - lastTime) / 100.0f;
    lastTime = currentTime;
}

void Motor::dibujarGrid()
{
    int intervalo = 50;
    for(int x = 0; x < anchoPantalla; x += intervalo){
        for(int y = 0; y < altoPantalla; y += intervalo){
            SDL_SetRenderDrawColor(renderizado, 90, 90, 90, 0);
            SDL_RenderLine(renderizado, x, 0, x, altoPantalla);
            SDL_RenderLine(renderizado, 0, y, anchoPantalla, y);
        }
    }
}