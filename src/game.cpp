#include <math.h>

#include "include/Motor.h"

Motor motor;

void dibujarPxieles(void);

int main()
{

    while(motor.estado){
        motor.manejarEventos();
        motor.limpiarPantalla();

        dibujarPxieles();

        motor.actualizarPantalla(16);
    }
    motor.destruirSDL();
    return 0;
}

void dibujarPxieles(void)
{
    // int numPixel = motor.superficie->w * motor.superficie->h;
    Uint32* pixele = (Uint32*)motor.superficie->pixels;
    // for(int i = 0; i < numPixel; i++){
    //     pixeles[i] = (Uint32) rand();
    // }
    SDL_PixelFormat* format = SDL_GetWindowPixelFormat(motor.ventana);
    pixele += 10 * motor.superficie->w + 10;


}