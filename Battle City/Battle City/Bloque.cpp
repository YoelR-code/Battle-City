#include "Bloque.h"


CBloque::CBloque(ETipoBloque tipo, int durabilidad) {
    this->tipo = tipo;
    this->durabilidad = durabilidad;
    this->tamano = bloqueCompleto;
    this->posicion = posicionCompleta;
    this->sprite = 0;
}


CBloque::CBloque(
    ETipoBloque tipo,
    int durabilidad,
    ETamanoBloque tamano
) {
    this->tipo = tipo;
    this->durabilidad = durabilidad;
    this->tamano = tamano;
    this->sprite = 0;

    if (tamano == bloqueHorizontal)
        this->posicion = posicionArriba;
    else if (tamano == bloqueVertical)
        this->posicion = posicionIzquierda;
    else
        this->posicion = posicionCompleta;
}

CBloque::CBloque(
    ETipoBloque tipo,
    int durabilidad,
    ETamanoBloque tamano,
    EPosicionBloque posicion
) {
    this->tipo = tipo;
    this->durabilidad = durabilidad;
    this->tamano = tamano;
    this->posicion = posicion;
    this->sprite = 0;
}

CBloque::CBloque(
    ETipoBloque tipo,
    int durabilidad,
    ETamanoBloque tamano,
    EPosicionBloque posicion,
    int sprite
) {
    this->tipo = tipo;
    this->durabilidad = durabilidad;
    this->tamano = tamano;
    this->posicion = posicion;
    this->sprite = sprite;
}

CBloque::~CBloque() {
}

ETipoBloque CBloque::getTipo() {
    return this->tipo;
}

void CBloque::setDurabilidad(short durabilidad) {
    this->durabilidad = durabilidad;
}

short CBloque::getDurabilidad() {
    return this->durabilidad;
}

ETamanoBloque CBloque::getTamano() {
    return this->tamano;
}

EPosicionBloque CBloque::getPosicion() {
    return this->posicion;
}

int CBloque::getSprite() {
    return this->sprite;
}