#define SDL_PLATFORM_PSP 1

#include "include/Motor.h"
#include <SDL3/SDL_main.h>

int main(int argc, char *argv[])
{
    Motor motor;

    motor.Configuracion();

    while(motor.estado){
        motor.manejarEventos();
        motor.limpiarPantalla();

        motor.Actualizar();
        motor.Renderizar();

        motor.actualizarPantalla(16);
    }
    motor.destruirSDL();
    return 0;
}