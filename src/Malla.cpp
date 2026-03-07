#include "include/Malla.h"
#include "include/Motor.h"

Malla::Malla(Motor* motor, Vector3* vertices, int nVertices, Vector3* caras, int nCaras)
{
    this->motor = motor;

    for(int i = 0; i < nVertices; i++){
        this->vertices.push_back(vertices[i]);
    }
    for(int i = 0; i < nCaras; i++){
        this->caras.push_back(caras[i]);
        this->triangulos.push_back(Triangulo());
    }
}

Malla::Malla(Motor* motor, std::string direccion)
{
    this->motor = motor;

    std::ifstream archivo(direccion);
    if(!archivo.is_open()){
        std::cerr<<"No se pudo encontrar el archivo: "<<direccion<<std::endl;
        return;
    }

    std::string linea;
    while(std::getline(archivo, linea)){
        if(linea.rfind("v ", 0) == 0){
            Vector3 vertex;
            sscanf(linea.c_str(), "v %lf %lf %lf", &vertex.x, &vertex.y, &vertex.z);
            this->vertices.push_back(vertex);
        }
        else if(linea.rfind("f ", 0) == 0){
            int vertexIndices[3];
            int texturaIndices[3];
            int normalIndices[3];
            sscanf(linea.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d",
                &vertexIndices[0], &texturaIndices[0], &normalIndices[0],
                &vertexIndices[1], &texturaIndices[1], &normalIndices[1],
                &vertexIndices[2], &texturaIndices[2], &normalIndices[2]
                );
            Vector3 cara;
            cara.x = vertexIndices[0] - 1;
            cara.y = vertexIndices[1] - 1;
            cara.z = vertexIndices[2] - 1;
            this->caras.push_back(cara);
            this->triangulos.push_back(Triangulo());
        }
    }
}

void Malla::SetRotacion(float x, float y, float z)
{
    rotacionActual = {x, y, z};
}

void Malla::Actualizar(float deltaTime)
{
    rotacion.x += rotacionActual.x;
    rotacion.y += rotacionActual.y;
    rotacion.z += rotacionActual.z;

    for(size_t i = 0; i < triangulos.size(); i++){
        triangulos[i].vertices[0] = vertices[static_cast<int>(caras[i].x)];
        triangulos[i].vertices[1] = vertices[static_cast<int>(caras[i].y)];
        triangulos[i].vertices[2] = vertices[static_cast<int>(caras[i].z)];

        for(int j = 0; j < 3; j++){
            triangulos[i].RotacionVertice(j, rotacion);
            
            triangulos[i].TrasladarVertice(j, motor->camaraPosision);
        }

        triangulos[i].AplicarCulling(motor->camaraPosision);

        if(triangulos[i].culling){
            continue;
        }

        for(int j = 0; j < 3; j++){    
            triangulos[i].ProyectarVertice(j, motor->fovFactor);
            
            triangulos[i].proyecionVertices[j].x += (ANCHOPANTALLA / 2);
            triangulos[i].proyecionVertices[j].y += (ALTOPANTALLA / 2);
        }
    }
}

void Malla::Renderizar()
{    
    for(size_t i = 0; i < triangulos.size(); i++){
        if(triangulos[i].culling)
            continue;
        /*    
        for(int j = 0; j < 3; j++){
            motor->dibujarPixel(
                triangulos[i].proyecionVertices[j].x,
                triangulos[i].proyecionVertices[j].y,
                0xFF00FFFF
           );
        }
        */
        
        motor->dibujarTriangulo(
            triangulos[i].proyecionVertices[0].x,
            triangulos[i].proyecionVertices[0].y,
            triangulos[i].proyecionVertices[1].x,
            triangulos[i].proyecionVertices[1].y,
            triangulos[i].proyecionVertices[2].x,
            triangulos[i].proyecionVertices[2].y,
            0xFF00FFFF
        );
        
        motor->DibujarTrinaguloRelleno(
            triangulos[i].proyecionVertices[0].x,
            triangulos[i].proyecionVertices[0].y,
            triangulos[i].proyecionVertices[1].x,
            triangulos[i].proyecionVertices[1].y,
            triangulos[i].proyecionVertices[2].x,
            triangulos[i].proyecionVertices[2].y,
            0xFFFFFFFF
        );
    }
}