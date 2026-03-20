#ifndef MOTOR_H
#define MOTOR_H

#include <iostream>
#include <SDL3/SDL.h>

#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_sdl3.h"
#include "../imgui/backends/imgui_impl_sdlrenderer3.h"

#include "Vector.h"
#include "Cubo.h"
#include "Triangulo.h"
#include "Malla.h"

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
    const bool* tecla;

    unsigned int lastTime = 0, currentTime;
    float deltaTime;

    uint32_t* colorBuffer;
    SDL_Texture* colorBufferTextura;

    // float fovFactor = 200;
    // Vector3 camaraPosision{0, 0, 0};

    /**
     * Variables para Imgui
    */
    bool activarInterface = true;
    
    bool dibujarMalla = false;
    bool dibujarVertices = true;
    bool dibujarLineas = true;
    bool rellenarTriangulos = true;

    float escaladoModelo[3] = {1, 1, 1};
    float rotacionModelo[3] = {0, 0, 0};
    float posisionModelo[3] = {0, 0, -5};

    float camaraPosision[3] = {0, 0, 0};
    // int fovFactor = 200;

    float fovFactor = M_PI / 3.0;
    float fovFactorGradiens = (180.0 / M_PI) * fovFactor;
    float aspectRatio = ALTOPANTALLA / static_cast<float>(ANCHOPANTALLA);
    float zNear = 0.1, zFar = 20.0;
    Matriz4 proyecionMatriz;

    /* Funciones */
    Motor();
    ~Motor();
    
    void destruirSDL(void);
    void manejarEventos(void);
    void limpiarPantalla(void);
    void actualizarPantalla(int ms);

    void dibujarPixel(int x, int y, unsigned int color);
    void dibujarLinea(int x0, int y0, int x1, int y1, uint32_t color);
    void dibujarTriangulo(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
    void DibujarTrinaguloRelleno(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
    void RellenoTrianguloArriba(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
    void RellenoTrianguloAbajo(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);

    void IntercambioInt(int* a, int* b);

private:
    int iniciarSDL(void);
    void setDeltatime(void);

public:
     /**
     * Funciones de renderizado
    */
    // Cubo cubo;
    Malla malla;

    void Configuracion(void);
    void Actualizar(void);
    void Renderizar(void);

    void renderColorBuffer();
    void limpiarColorBuffer(uint32_t color);
    void dibujarGrid(uint32_t color);
};

#endif /* MOTOR_H */