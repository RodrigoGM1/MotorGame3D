#include "include/Motor.h"

const int FPS = 30;
const int drameDelay = 1000 / FPS;
Uint32 frameStart;
int frameTime;

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
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    malla.Liberar();
    delete[] REDRICK_TEXTURE;

    destruirSDL();
}

void Motor::destruirSDL()
{
    SDL_CaptureMouse(false);
    SDL_DestroyRenderer(renderizado);
    SDL_DestroyWindow(this->ventana);
}

void Motor::manejarEventos()
{
    while(SDL_PollEvent(&this->eventos)){
        ImGui_ImplSDL3_ProcessEvent(&eventos);
        switch(this->eventos.type){
            case SDL_EVENT_QUIT:
                estado = 0;
                break;
            case SDL_EVENT_KEY_DOWN:
                tecla = SDL_GetKeyboardState(NULL);
                if(tecla[SDL_SCANCODE_I]) (activarInterface) ? this-> activarInterface = false : this->activarInterface = true;
                break;
            
            case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
                if(eventos.gbutton.button == SDL_GAMEPAD_BUTTON_START){
                    (activarInterface) ? this-> activarInterface = false : this->activarInterface = true;    
                }
                break;
        }
    }
}

void Motor::limpiarPantalla()
{
    frameStart = SDL_GetTicks();

    SDL_SetRenderDrawColor(renderizado, 0, 0, 0, 255);
    SDL_RenderClear(renderizado);

    setDeltatime();
    limpiarColorBuffer(0xFF000000);

    if(dibujarMalla) dibujarGrid(0xFFEEEEEE);

    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();

    if(activarInterface){
        ImGui::Begin("CPU 3D Renderizdo");
        ImGui::Separator();

        ImGui::Text(" %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        ImGui::Checkbox("Dibujar Malla", &this->dibujarMalla);
        ImGui::Checkbox("Dibujar Vertices", &this->dibujarVertices);
        ImGui::Checkbox("Dibujar Lineas", &this->dibujarLineas);
        ImGui::Checkbox("Rellenar Triangulos", &this->rellenarTriangulos);
        ImGui::Checkbox("Dibujar Textura", &this->dibujarTextura);

        ImGui::Separator();
        ImGui::Text("Rotacion modelo (X,Y,Z)");
        ImGui::SliderFloat3("Rot", rotacionModelo, 0, 0.05f);

        ImGui::Separator();
        ImGui::Text("Posision modelo (X,Y,Z)");
        ImGui::SliderFloat3("Pos", posisionModelo, -5,  5);

        ImGui::Separator();
        ImGui::Text("Escalado del modelo (X,Y,Z)");
        ImGui::SliderFloat3("Escala", escaladoModelo, 0,  5);

        ImGui::Text("Campo de visión");
        ImGui::SliderFloat("Fov", &this->fovFactorGradiens, 30, 120);
        
        ImGui::End();
    }
    proyecionMatriz = Matriz4::PerspectivaMatriz((this->fovFactorGradiens / 180.0) * M_PI, aspectRatio, zNear, zFar);
}

void Motor::actualizarPantalla(int ms)
{
    renderColorBuffer();
    
    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderizado);

    SDL_SetRenderVSync(renderizado, 1);
    SDL_RenderPresent(renderizado);

    if(drameDelay > frameTime){
        SDL_Delay(drameDelay - frameTime);
    }
    // SDL_Delay(ms);
}

/**
 * Funciones privadas
*/

int Motor::iniciarSDL()
{
    SDL_InitFlags banderasInicio = SDL_INIT_VIDEO | SDL_INIT_GAMEPAD | SDL_INIT_JOYSTICK;
    SDL_WindowFlags banderasVentana = SDL_WINDOW_RESIZABLE;
    if(!SDL_Init(banderasInicio)){
        SDL_Log("No se pudo iniciar SDL3");
        return 1;
    }
    if(!SDL_CreateWindowAndRenderer("Game", ANCHOPANTALLA, ALTOPANTALLA, banderasVentana, &this->ventana, &renderizado)){
        SDL_Log("No se pudo crear la ventana SDL3");
        return 1;
    }
    if(!SDL_SetRenderVSync(renderizado, 1)){
        SDL_Log("No se pudo inciar SDL_SetRenderVSync");
        return 1;
    }
    this->estado = 1;

    colorBuffer = static_cast<uint32_t*>(malloc(sizeof(uint32_t) * ANCHOPANTALLA * ALTOPANTALLA));
    colorBufferTextura = SDL_CreateTexture(renderizado, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, ANCHOPANTALLA , ALTOPANTALLA);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    ImGui::StyleColorsDark();

    if(!ImGui_ImplSDL3_InitForSDLRenderer(ventana, renderizado)){
        SDL_Log("No se pudo inciar el renderizado ImGui");
        return 1;
    }
    if(!ImGui_ImplSDLRenderer3_Init(renderizado)){
        SDL_Log("No se pudo inciar ImGui");
        return 1;
    }

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

    for(int i = 0; i < longuitud + 1; i++){
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

void Motor::DibujarTrinaguloRelleno(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
    if(y0 > y1){
        IntercambioInt(&y0, &y1);
        IntercambioInt(&x0, &x1);
    }
    if(y1 > y2){
        IntercambioInt(&y1, &y2);
        IntercambioInt(&x1, &x2);
    }
    if(y0 > y1){
        IntercambioInt(&y0, &y1);
        IntercambioInt(&x0, &x1);
    }

    int Mx = (((x2 - x0) * (y1 - y0)) / static_cast<float>((y2 - y0))) + x0;
    int My = y1;

    if(y1 == y2){
        RellenoTrianguloArriba(x0, y0, x1, y1, x2, y2, color);
    }
    else if(y1 == y2){
        RellenoTrianguloAbajo(x0, y0, x1, y1, x2, y2, color);
    }
    else{
        RellenoTrianguloArriba(x0, y0, x1, y1, Mx, My, color);
        RellenoTrianguloAbajo(x1, y1, Mx, My, x2, y2, color);
    }
}

void Motor::RellenoTrianguloArriba(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
    float m1 = -((y1 - y0) / static_cast<float>((x0 - x1)));
    float m2 = (y2 - y0) / static_cast<float>((x2 - x0));

    for(int i = 0; i < (y1 - y0); i++){
        dibujarLinea(x0 + (i / m1), y0 + i, x0 + (i / m2), y0 + i, color);
    }
}

void Motor::RellenoTrianguloAbajo(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
    float m1 = -((y2 - y0) / static_cast<float>((x2 - x0)));
    float m2 = -((y2 - y1) / static_cast<float>((x2 - x1)));

    for(int i = 0; i <= (y2 - y1); i++){
        dibujarLinea(x2 + (i / m1), y2 - i, x2 + (i /m2), y2 - i, color);
    }
}

void Motor::DibujarTexturaTriangulo(int x0, int y0, float z0, float w0, Textura2 uv0, int x1, int y1, float z1, float w1, Textura2 uv1, int x2, int y2, float z2, float w2, Textura2 uv2, uint32_t* textura, int texturaAncho, int texturaAlto)
{
    if(y0 > y1){
        IntercambioInt(&y0, &y1);
        IntercambioInt(&x0, &x1);
        IntercambioFloat(&z0, &z1);
        IntercambioFloat(&w0, &w1);
        // IntercambioTexturea(&t0, &t1);
        IntercambioTexturea(&uv0, &uv1);
    }
    if(y1 > y2){
        IntercambioInt(&y1, &y2);
        IntercambioInt(&x1, &x2);
        IntercambioFloat(&z1, &z2);
        IntercambioFloat(&w1, &w2);
        // IntercambioTexturea(&t1, &t2);
        IntercambioTexturea(&uv1, &uv2);
    }
    if(y0 > y1){
        IntercambioInt(&y0, &y1);
        IntercambioInt(&x0, &x1);
        IntercambioFloat(&z0, &z1);
        IntercambioFloat(&w0, &w1);
        // IntercambioTexturea(&t0, &t1);
        IntercambioTexturea(&uv0, &uv1);
    }

    uv0.v = 1 - uv0.v;
    uv1.v = 1 - uv1.v;
    uv2.v = 1 - uv2.v;
    // Vector2 pA{static_cast<double>(x0), static_cast<double>(y0)};
    // Vector2 pB{static_cast<double>(x1), static_cast<double>(y1)};
    // Vector2 pC{static_cast<double>(x2), static_cast<double>(y2)};
    Vector4 pA{(double)x0, (double)y0, (double)z0, (double)w0};
    Vector4 pB{(double)x1, (double)y1, (double)z1, (double)w1};
    Vector4 pC{(double)x2, (double)y2, (double)z2, (double)w2};

    float uDivW[3] = {(float)uv0.u / (float)pA.w, (float)uv1.u / (float)pB.w, (float)uv2.u / (float)pC.w};
    float vDivW[3] = {(float)uv0.v / (float)pA.w, (float)uv1.v / (float)pB.w, (float)uv2.v / (float)pC.w};
    float oneDviW[3] = {1 / (float)pA.w, 1 / (float)pB.w, 1 / (float)pC.w};

    {
        float m1 = 0;
        float m2 = 0;

        if (y1 - y0 != 0) m1 = -((y1 - y0) / static_cast<float>((x0 - x1)));
        if (y2 - y0 != 0) m2 = (y2 - y0) / static_cast<float>((x2 - x0));
        if (y1 - y0 != 0){
            for(int i = 0; i  < (y1 - y0); i++){
                int xInicio = x0 + (i / m1);
                int xFin = x0 + (i / m2);
                int y = y0 + i;

                if(xFin < xInicio) IntercambioInt(&xFin, &xInicio);

                for(int x = xInicio; x < xFin; x++){
                    // dibujarPixel(x, y, (x % 2 == 0) ? 0xFFFFF00FF : 0xFF000000);
                    // DibujarTexel(x, y, pA, pB, pC, uv0, uv1, uv2, textura, this);
                    DibujarTexel(x, y, pA, pB, pC, uv0, uv1, uv2, uDivW, vDivW, oneDviW, textura, texturaAncho, texturaAlto);
                }
            }
        }
    }
    
    {
        float m1 = 0;
        float m2 = 0;

        if(y2 - y1 != 0) m1 = -((y2 - y1) / static_cast<float>((x2 - x1)));
        if(y2 - y0 != 0) m2 = -((y2 - y0) / static_cast<float>((x2 - x0)));
        if(y2 - y1 != 0){
            for(int i = 0; i <= (y2 - y1); i++){
                int xInicio = x2 + (i / m1);
                int xFin = x2 + (i / m2);
                int y = y2 - i;

                if(xFin < xInicio) IntercambioInt(&xFin, &xInicio);

                for(int x = xInicio; x < xFin; x++){
                    // dibujarPixel(x, y, (x % 2 == 0) ? 0xFFFFF00FF : 0xFF000000);
                    // DibujarTexel(x, y, pA, pB, pC, uv0, uv1, uv2, textura, this);
                    DibujarTexel(x, y, pA, pB, pC, uv0, uv1, uv2, uDivW, vDivW, oneDviW, textura, texturaAncho, texturaAlto);
                }
            }
        }
    }
}

void Motor::DibujarTexel(int x, int y, Vector4 a, Vector4 b, Vector4 c, Textura2 t0, Textura2 t1, Textura2 t2, float* uDivW, float* vDivW, float* oneDivw, uint32_t *texture, int texturaAncho, int texturaAlto)
{
    Vector2 p{static_cast<double>(x), static_cast<double>(y)};
    Vector3 peso = Vector3::PesoBaricentrico(a.ToVector2(), b.ToVector2(), c.ToVector2(), p);
    float alfa = peso.x;
    float beta = peso.y;
    float gamma = peso.z;

    // float interpolacionU = (t0.u / a.w) * alfa + (t1.u / b.w) * beta + (t2.u / c.w) * gamma;
    // float interpolacionV = (t0.v / a.w) * alfa + (t1.v / b.w) * beta + (t2.v / c.w) * gamma;
    // float interpolacionRecW = (1 / a.w) * alfa + (1 / b.w) * beta + (1 / c.w) * gamma;

    float interpolacionU = uDivW[0] * alfa + uDivW[1] * beta + uDivW[2] * gamma;
    float interpolacionV = vDivW[0] * alfa + vDivW[1] * beta + vDivW[2] * gamma;
    float interpolacionRecW = oneDivw[0] * alfa + oneDivw[1] * beta + oneDivw[2] * gamma;

    interpolacionU /= interpolacionRecW;
    interpolacionV /= interpolacionRecW;

    // int texelX = abs(static_cast<int>(interpolacionU * motor->texturaAncho));
    // int texelY = abs(static_cast<int>(interpolacionV * motor->texturaAlto));

    int texelX = abs(static_cast<int>(interpolacionU * texturaAncho));
    int texelY = abs(static_cast<int>(interpolacionV * texturaAlto));

    // dibujarPixel(x, y, texture[(motor->texturaAncho * texelY) + texelX]);
    dibujarPixel(x, y, texture[(texturaAncho * texelY) + texelX]);
}

void Motor::IntercambioInt(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void Motor::IntercambioFloat(float* a, float* b)
{
    float temp = *a;
    *a = *b;
    *b = temp;
}

void Motor::IntercambioTexturea(Textura2* a, Textura2* b)
{
    Textura2 temp = *a;
    *a = *b;
    *b = temp;
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

uint32_t mallaColor[]{
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF, 
    0xFFFFFFFF
};

Triangulo triangulosProyectados[12];
Vector3 rotacion;

void Motor::Configuracion()
{
    texturaAlto = 64;
    texturaAncho = 64;

    // Textura2 mallaTexturaUVs[]{ 
    //     {0,0},{0,1},{1,1},{0,0},{1,1},{1,0},
    //     {0,0},{0,1},{1,1},{0,0},{1,1},{1,0},  
    //     {0,0},{1,1},{1,0},{0,0},{0,1},{1,1},  
    //     {0,0},{1,1},{1,0},{0,0},{0,1},{1,1},
    //     {0,0},{1,1},{1,0},{0,0},{0,1},{1,1},
    //     {0,0},{0,1},{1,1},{0,0},{1,1},{1,0}
    // };

    // malla = Malla(this, vertices, 8, caras, 12);
    // malla = Malla(this, vertices, 8, caras, 12, mallaColor, mallaTexturaUVs);
    // malla = Malla(this, "./modelos3D/Esfera.obj");
    malla = Malla(this, "./modelos3D/Cubo.obj", "./modelos3D/cuboI.png");

    // REDRICK_TEXTURE = new (std::nothrow) uint8_t[16400]{};
    /*
    REDRICK_TEXTURE = new (std::nothrow) uint8_t[16400]{
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, // ...
    };
    mallaTextura = (uint32_t*)REDRICK_TEXTURE;
    */
    colorBufferTextura = SDL_CreateTexture(renderizado, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, ANCHOPANTALLA, ALTOPANTALLA);
}

void Motor::Actualizar()
{
    malla.SetRotacion(rotacionModelo[0], rotacionModelo[1], rotacionModelo[2]);
    malla.SetTraslacion(posisionModelo);
    malla.SetEscala(escaladoModelo);
    malla.Actualizar(deltaTime);
}

void Motor::Renderizar()
{
    malla.Renderizar();
}