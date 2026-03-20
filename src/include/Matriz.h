#ifndef MATRIZ_H
#define MATRIZ_H

#include "Vector.h"

class Matriz4
{
public:
    float m[4][4];

    static Matriz4 IdentidadMatriz()
    {
        //  |  1  0  0  0 |
        //  |  0  1  0  0 |
        //  |  0  0  1  0 |
        //  |  0  0  0  1 |
        return Matriz4{{
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1},
        }};
    }

    static Matriz4 EscalaMatriz(float x, float y, float z)
    {
        //  | sx  0  0  0 |
        //  |  0 sy  0  0 |
        //  |  0  0 sz  0 |
        //  |  0  0  0  1 |
        Matriz4 m = Matriz4::IdentidadMatriz();
        m.m[0][0] = x;
        m.m[1][1] = y;
        m.m[2][2] = z;
        return m;
    }

    static Matriz4 TrasladarMatriz(float x, float y, float z)
    {
        //  |  1  0  0  tx  |
        //  |  0  1  0  ty  |
        //  |  0  0  1  tz  |
        //  |  0  0  0   1  |
        Matriz4 m = Matriz4::IdentidadMatriz();
        m.m[0][3] = x;
        m.m[1][3] = y;
        m.m[2][3] = z;
        return m;
    }

    static Matriz4 RotarZMatriz(float angulo)
    {
        float c = cos(angulo);
        float s = sin(angulo);
        //  |  c -s  0  0  |
        //  |  s  c  0  0  |
        //  |  0  0  1  0  |
        //  |  0  0  0  1  |
        Matriz4 m = Matriz4::IdentidadMatriz();
        m.m[0][0] = c;
        m.m[0][1] = -s;
        m.m[1][0] = s;
        m.m[1][1] = c;
        return m;
    }

    static Matriz4 RotarXMatriz(float angulo)
    {
        float c = cos(angulo);
        float s = sin(angulo);
        //  |  1  0  0  0  |
        //  |  0  c -s  0  |
        //  |  0  s  c  0  |
        //  |  0  0  0  1  |
        Matriz4 m = Matriz4::IdentidadMatriz();
        m.m[1][1] = c;
        m.m[1][2] = -s;
        m.m[2][1] = s;
        m.m[2][2] = c;
        return m;
    }

    static Matriz4 RotarYMatriz(float angulo)
    {
        float c = cos(angulo);
        float s = sin(angulo);
        //  |  c  0  s  0  |
        //  |  0  1  0  0  |
        //  | -s  0  c  0  |
        //  |  0  0  0  1  |
        Matriz4 m = Matriz4::IdentidadMatriz();
        m.m[0][0] = c;
        m.m[0][2] = s;
        m.m[2][0] = -s;
        m.m[2][2] = c;
        return m;
    }

    Matriz4 operator*(Matriz4 m2) const
    {
        Matriz4 resultado;
        for(size_t i = 0; i < 4; i++){
            for(size_t j = 0; j < 4; j++){
                resultado.m[i][j] = 
                                m[i][0] * m2.m[0][j] +
                                m[i][1] * m2.m[1][j] +
                                m[i][2] * m2.m[2][j] +
                                m[i][3] * m2.m[3][j];
            }
        }
        return resultado;
    }

    static Matriz4 MundoMatriz(Vector3 escala, Vector3 angulo, Vector3 trasladar)
    {
        Matriz4 mundoMatriz = Matriz4::IdentidadMatriz();
        mundoMatriz = Matriz4::EscalaMatriz(escala.x, escala.y, escala.z) * mundoMatriz;
        mundoMatriz = Matriz4::RotarXMatriz(angulo.x) * mundoMatriz;
        mundoMatriz = Matriz4::RotarYMatriz(angulo.y) * mundoMatriz;
        mundoMatriz = Matriz4::RotarZMatriz(angulo.z) * mundoMatriz;
        mundoMatriz = Matriz4::TrasladarMatriz(trasladar.x, trasladar.y, trasladar.z) * mundoMatriz;
        return mundoMatriz;
    }

    static Matriz4 PerspectivaMatriz(float fov, float aspect, float znear, float zfar)
    {
        // | (h/w)*1/tan(fov/2)                0             0                   0 |
        // |                  0     1/tan(fov/2)             0                   0 |
        // |                  0                0    zf/(zf/zn)    (-zf*zn)/(zf-zn) |
        // |                  0                0             1                   0 |
        Matriz4 m = {{{0}}};
        m.m[0][0] = aspect * (1 / tan(fov / 2));
        m.m[1][1] = 1/ tan(fov / 2);
        m.m[2][2] = zfar / (zfar - znear);
        m.m[2][3] = (-zfar * znear) / (zfar - znear);
        m.m[3][2] = 1.0;
        return m;
    }

    static Vector4 ProyecionMatriz(Matriz4 perspectivaMatriz, Vector4 originalVector)
    {
        Vector4 resultado = originalVector * perspectivaMatriz;

        if(resultado.w != 0.0){
            resultado.x /= resultado.w;
            resultado.y /= resultado.w;
            resultado.z /= resultado.w;
        }
        return resultado;
    }
};

#endif /* MATRIZ_H */