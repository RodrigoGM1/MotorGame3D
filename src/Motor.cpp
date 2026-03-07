#include "include/Motor.h"

/**
 * Declaraciones de funciones de la clase motor
*/
Motor::Motor()
{
    this->renderizado = nullptr;
    this->ventana = nullptr;
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
    SDL_DestroyRenderer(renderizado);
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
    SDL_SetRenderDrawColor(renderizado, 0, 0, 0, 255);
    SDL_RenderClear(renderizado);

    setDeltatime();
    limpiarColorBuffer(0xFF000000);
    // dibujarGrid(0xFFEEEEEE);
}

void Motor::actualizarPantalla(int ms)
{
    renderColorBuffer();

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

    colorBuffer = static_cast<uint32_t*>(malloc(sizeof(uint32_t) * ANCHOPANTALLA * ALTOPANTALLA));
    colorBufferTextura = SDL_CreateTexture(renderizado, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, ANCHOPANTALLA , ALTOPANTALLA);

    return 0;
}

void Motor::setDeltatime(void)
{
    currentTime = SDL_GetTicks();
    deltaTime = (float)(currentTime - lastTime) / 100.0f;
    lastTime = currentTime;
}

void Motor::renderColorBuffer()
{
    SDL_UpdateTexture(colorBufferTextura, NULL, colorBuffer, ANCHOPANTALLA * sizeof(uint32_t));
    SDL_RenderTexture(renderizado, colorBufferTextura, NULL, NULL);
}

void Motor::limpiarColorBuffer(uint32_t color)
{
    for(size_t y = 0; y < ALTOPANTALLA; y++){
        for(size_t x = 0; x < ANCHOPANTALLA; x++){
            colorBuffer[(ANCHOPANTALLA * y) + x] = color;
        }
    }
}

void Motor::dibujarGrid(uint32_t color)
{
    for(size_t y = 0; y < ALTOPANTALLA; y += 20){
        for(size_t x = 0; x < ANCHOPANTALLA; x += 20){
            colorBuffer[(ANCHOPANTALLA * y) + x] = color;
        }
    }
}

void Motor::dibujarPixel(int x, int y, unsigned int color)
{
    if(x >= 0 && x <ANCHOPANTALLA && y >= 0 && ALTOPANTALLA){
        colorBuffer[(ANCHOPANTALLA * y) + x] = static_cast<uint32_t>(color);
    }
}

void Motor::dibujarLinea(int x0, int y0, int x1, int y1, uint32_t color)
{
    float dX = x1 - x0;
    float dY = y1 - y0;

    int longuitud = abs(dY / dX) < 1 ? abs(dX) : abs(dY);

    float xInc = dX / longuitud;
    float yInc = dY / longuitud;

    for(int i = 0; i < longuitud; i++){
        dibujarPixel(
            round(x0 + (xInc * i)),
            round(y0 + (yInc * i)),
            color
        );
    }
}

void Motor::dibujarTriangulo(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
    dibujarLinea(x0, y0, x1, y1, color);
    dibujarLinea(x1, y1, x2, y2, color);
    dibujarLinea(x2, y2, x0, y0, color);
}

/**
 * Funciones de renderizado
*/
Vector3 vertices[8] = {
    {-1.0, -1.0, -1.0},  // 0
    { 1, -1, -1},  // 1
    {-1,  1, -1},  // 2
    { 1,  1, -1},  // 3
    {-1, -1,  1},  // 4
    { 1, -1,  1},  // 5
    {-1,  1,  1},  // 6
    { 1,  1,  1}   // 7
};

Vector3 caras[12] = {
    // front    ->
    {1, 0, 2},
    {1, 2, 3},
    // back     <-
    {4, 5, 7},
    {4, 7, 6},
    // right    ->
    {1, 7, 5},
    {1, 3, 7},
    // left     <-
    {4, 2, 0}, 
    {4, 6, 2},
    // top      ->
    {2, 7, 3}, 
    {2, 6, 7},
    // bottom   <- 
    {1, 5, 4}, 
    {1, 4, 0} 
};
Triangulo triangulosProyectados[12];
Vector3 rotacion;

void Motor::Configuracion()
{
    // malla = Malla(this, vertices, 8, caras, 12);
    malla = Malla(this, "./modelos3D/Toroide.obj");
    malla.SetRotacion(0.01, 0.01, 0.01);
}

void Motor::Actualizar()
{
   malla.Actualizar(deltaTime);
}

void Motor::Renderizar()
{
    malla.Renderizar();
}