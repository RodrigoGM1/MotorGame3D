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
#include "Luz.h"
#include "Textura.h"

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
    bool dibujarTextura = false;

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

    Luz luz{.direcion{0, 0, 1}};

    /**
     * Variables de textura
    */
    int texturaAncho;
    int texturaAlto;
    uint32_t* mallaTextura{nullptr};
    uint8_t* REDRICK_TEXTURE{nullptr};

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
    // void DibujarTexturaTriangulo(int x0, int y0, Textura2 t0, int x1, int y1, Textura2 t1, int x2, int y2, Textura2 t2, uint32_t* textura);
    void DibujarTexturaTriangulo(int x0, int y0, float z0, float w0, Textura2 uv0, int x1, int y1, float z1, float w1, Textura2 uv1, int x2, int y2, float z2, float w2, Textura2 uv2, uint32_t* textura, int texturaAncho, int texturaAlto);
    // void DibujarTexel(int x, int y, Vector2 a, Vector2 b, Vector2 c, Textura2 t0, Textura2 t1, Textura2 t2, uint32_t *texture, Motor* motor);
    void DibujarTexel(int x, int y, Vector4 a, Vector4 b, Vector4 c, Textura2 t0, Textura2 t1, Textura2 t2, float* uDivW, float* vDivW, float* oneDivw, uint32_t *texture, int texturaAncho, int texturaAlto);

    void IntercambioInt(int* a, int* b);
    void IntercambioFloat(float* a, float* b);
    void IntercambioTexturea(Textura2* a, Textura2* b);

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