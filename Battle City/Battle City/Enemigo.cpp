
#include "Enemigo.h"

// ==========================================
// CONSTRUCTOR
// ==========================================

CEnemigo::CEnemigo(
    short id,
    short tipo,
    int posx,
    int posy,
    int vidas
) : CTanque(id, posx, posy, vidas) {
    this->tipo = (ETipoTanque)tipo;
}

// ==========================================
// GETTERS Y SETTERS
// ==========================================

void CEnemigo::setTipo(ETipoTanque tipo) {
    this->tipo = tipo;
}

ETipoTanque CEnemigo::getTipo() {
    return this->tipo;
}

// ==========================================
// PATRON CREACIONAL PROTOTYPE
// CLONAR UN ENEMIGO MODELO
// ==========================================

CEnemigo* CEnemigo::Clonar(
    short id,
    int posx,
    int posy,
    int vidas
) {
    CEnemigo* copia = new CEnemigo(
        id,
        (short)this->getTipo(),
        posx,
        posy,
        vidas
    );

    // Conservar la configuracion del prototipo.
    copia->setDireccion(this->getDireccion());
    copia->setVelocidad(this->getVelocidad());

    return copia;
}

// ==========================================
// DIBUJAR ENEMIGO
// ==========================================

void CEnemigo::dibujar(
    Graphics^ g,
    Bitmap^ bmpTanques
) {
    int origenX = 0;

    switch (getTipo()) {
    case tipo1:
        origenX = 64;
        break;

    case tipo2:
        origenX = 128;
        break;

    case tipo3:
        origenX = 192;
        break;

    case tipo4:
        origenX = 256;
        break;

    case tipo5:
        origenX = 320;
        break;
    }

    int origenY = 0;

    switch (getDireccion()) {
    case arriba:
        origenY = 0;
        break;

    case derecha:
        origenY = 64;
        break;

    case abajo:
        origenY = 128;
        break;

    case izquierda:
        origenY = 192;
        break;

    default:
        origenY = 0;
        break;
    }

    Rectangle origen(
        origenX,
        origenY,
        64,
        64
    );

    Rectangle destino(
        getX() + 8,
        getY() + 8,
        48,
        48
    );

    g->DrawImage(
        bmpTanques,
        destino,
        origen,
        GraphicsUnit::Pixel
    );
}
