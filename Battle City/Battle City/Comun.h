#pragma once

#define MAX_FILAS 11
#define MAX_COLUMNAS 13

#define ANCHO_IMAGEN 64
#define ALTO_IMAGEN 64

enum ETipoBloque {
    piso = 1,
    destruible,
    noDestruible,
    agua,
    arbol,
    trofeo
};

enum ETamanoBloque {
    bloqueCompleto,
    bloqueHorizontal,
    bloqueVertical
};

enum EDireccion {
    ninguno,
    arriba,
    abajo,
    izquierda,
    derecha
};

enum EPosicionBloque {
    posicionCompleta,
    posicionIzquierda,
    posicionDerecha,
    posicionArriba,
    posicionAbajo
};
class CComun {};