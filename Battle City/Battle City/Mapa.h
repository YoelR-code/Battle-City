
#pragma once
#include <iostream>
#include "Bloque.h"

using namespace System::Drawing;

class CMapa {
    CBloque* mapa[MAX_FILAS][MAX_COLUMNAS];
    int nivel;

public:
    CMapa();
    ~CMapa();

    void setNivel(int nivel);
    int getNivel();

    CBloque* getBloque(int i, int j);
    CBloque* (*getMapa())[MAX_COLUMNAS];

    void CargarNivel(int datos[MAX_FILAS][MAX_COLUMNAS]);

    void nivel1();
    void nivel2();
    void nivel3();
    void nivel4();
    void nivel5();

    void DibujarMapa(
        Graphics^ g,
        Bitmap^ bmpPiso,
        Bitmap^ bmpBloques,
        Bitmap^ bmpTrofeo
    );

    // Dibujar el fondo de cada nivel
    void DibujarFondo(Graphics^ g, Bitmap^ bmpFondo);
};
