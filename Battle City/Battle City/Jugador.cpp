#include "Jugador.h"

CJugador::CJugador(short id, int posX, int posY, int vidas)
    : CTanque(id, posX, posY, vidas) {
    puntuacion = 0;
}

void CJugador::setNombre(std::string nombre) {
    this->nombre = nombre;
}

void CJugador::setPuntuacion(int puntuacion) {
    this->puntuacion = puntuacion;
}

std::string CJugador::getNombre() {
    return nombre;
}

int CJugador::getPuntuacion() {
    return puntuacion;
}

void CJugador::dibujar(Graphics^ g, Bitmap^ bmpTanques) {
    int origenY = 0;

    switch (getDireccion()) {
    case arriba: origenY = 0; break;
    case derecha: origenY = 64; break;
    case abajo: origenY = 128; break;
    case izquierda: origenY = 192; break;
    default: origenY = 0; break;
    }

    Rectangle origen(0, origenY, 64, 64);
    Rectangle destino(getX() + 8, getY() + 8, 48, 48);

    g->DrawImage(bmpTanques, destino, origen, GraphicsUnit::Pixel);
}

void CJugador::mover() {
    int paso = getVelocidad();

    switch (getDireccion()) {
    case arriba: setY(getY() - paso); break;
    case abajo: setY(getY() + paso); break;
    case izquierda: setX(getX() - paso); break;
    case derecha: setX(getX() + paso); break;
    default: break;
    }
}