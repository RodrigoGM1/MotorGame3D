#include "include/Triangulo.h"

bool Triangulo::operator<(const Triangulo & t) const
{
    return profundidadPromedio < t.profundidadPromedio;
}

// void Triangulo::ProyectarVertice(int verticeIndice, float fovFactor)
// {
//     proyecionVertices[verticeIndice] = vertices[verticeIndice].PerspectivaProyecion(fovFactor);
// }

void Triangulo::ProyectarVertice(int verticeIndice, Matriz4 proyecionMatriz)
{
    Vector4 trasformarVertice{vertices[verticeIndice]};
    proyecionVertices[verticeIndice] = Matriz4::ProyecionMatriz(proyecionMatriz, trasformarVertice);
}

// void Triangulo::RotacionVertice(int verticeIndice, Vector3 rotacion)
// {
//     vertices[verticeIndice].Rotacion(rotacion);
// }

void Triangulo::TrasladarVertice(int verticeIndice, float* distancia)
{
    vertices[verticeIndice].x -= distancia[0];
    vertices[verticeIndice].y -= distancia[1];
    vertices[verticeIndice].z -= distancia[2];
}

void Triangulo::EscalaVertice(int verticeIndice, Vector3 escala)
{
    Vector4 trasformarVertice{vertices[verticeIndice]};
    trasformarVertice = trasformarVertice * Matriz4::EscalaMatriz(escala.x, escala.y, escala.z);
    vertices[verticeIndice] = trasformarVertice.ToVector3();
}

void Triangulo::RotacionVertice(int verticeIndice, Vector3 rotacion)
{
    Vector4 trasformarVertice{vertices[verticeIndice]};
    trasformarVertice = trasformarVertice * Matriz4::RotarXMatriz(rotacion.x);
    trasformarVertice = trasformarVertice * Matriz4::RotarYMatriz(rotacion.y);
    trasformarVertice = trasformarVertice * Matriz4::RotarZMatriz(rotacion.z);
    vertices[verticeIndice] = trasformarVertice.ToVector3();
}

void Triangulo::TrasladarVertice(int verticeIndice, Vector3 traslacion)
{
    Vector4 trasformarVertice{vertices[verticeIndice]};
    trasformarVertice = trasformarVertice * Matriz4::TrasladarMatriz(traslacion.x, traslacion.y, traslacion.z);
    vertices[verticeIndice] = trasformarVertice.ToVector3();
}

void Triangulo::MundoMatriz(int verticeIndice, Vector3 escala, Vector3 angulo, Vector3 trasladar)
{
    Vector4 trasformarVertice{vertices[verticeIndice]};
    trasformarVertice = trasformarVertice * Matriz4::MundoMatriz(escala, angulo, trasladar);
    vertices[verticeIndice] = trasformarVertice.ToVector3();
}

void Triangulo::CalcularNormal()
{
    Vector3 vectorAB = this->vertices[1] - this->vertices[0];
    Vector3 vectorAC = this->vertices[2] - this->vertices[0];
    vectorAB.Normalizar();
    vectorAC.Normalizar();

    normal = vectorAB.ProductoCruzado(vectorAC);
    normal.Normalizar();
}

void Triangulo::AplicarCulling(float* camara)
{
    // Vector3 vectorAB = this->vertices[1] - this->vertices[0];
    // Vector3 vectorAC = this->vertices[2] - this->vertices[0];
    // vectorAB.Normalizar();
    // vectorAC.Normalizar();

    // Vector3 normal = vectorAB.ProductoCruzado(vectorAC);
    // normal.Normalizar();

    Vector3 camaraRay = Vector3(camara[0], camara[1], camara[2]) - this->vertices[0];

    float normalCamara = normal.ProductoPunto(camaraRay);

    this->culling = (normalCamara < 0);
}

void Triangulo::AplicarSombreado(Luz luz)
{
    float luzIntencidadFactro = normal.ProductoPunto(luz.direcion);
    color = Luz::AplicarIntensidad(originalColor, luzIntencidadFactro);
}

void Triangulo::ProfundidadPromedio()
{
    profundidadPromedio = (vertices[0].z + vertices[1].z + vertices[2].z) / 3;
}