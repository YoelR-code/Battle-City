#pragma once
#include "Comun.h"

class CBloque {
    int posX;
    int posY;

    ETipoBloque tipo;
    short durabilidad;
    ETamanoBloque tamano;
    EPosicionBloque posicion;
    int sprite;

public:
    CBloque(ETipoBloque tipo, int dureza);
    CBloque(ETipoBloque tipo, int dureza, ETamanoBloque tamano);
    CBloque(ETipoBloque tipo, int dureza, ETamanoBloque tamano, EPosicionBloque posicion);
    CBloque(
        ETipoBloque tipo,
        int dureza,
        ETamanoBloque tamano,
        EPosicionBloque posicion,
        int sprite
    );

    ~CBloque();

    ETipoBloque getTipo();

    void setDurabilidad(short durabilidad);
    short getDurabilidad();

    ETamanoBloque getTamano();

    EPosicionBloque getPosicion();

    int getSprite();
};