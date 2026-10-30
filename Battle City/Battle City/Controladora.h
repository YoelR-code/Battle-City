
#pragma once

#include "Mapa.h"
#include "Tanque.h"
#include "Jugador.h"
#include "ColeccionEnemigos.h"

using namespace System::Drawing;

class CControladora {
private:
    static CControladora* instancia;

    CMapa* mapa;
    CJugador* jugador;
    CColeccionEnemigos* coleccionEnemigos;

    bool EsObstaculo(Color pixel);
    bool TieneColision(int x, int y, Bitmap^ bmpFondo);

    CControladora();

public:
    static CControladora* ObtenerInstancia();

    CControladora(const CControladora&) = delete;
    CControladora& operator=(const CControladora&) = delete;

    ~CControladora();

    void Inicializar();
    void CambiarNivel(int nivel, Bitmap^ bmpFondo);
    int getNivel();

    void MoverJugador(EDireccion direccion, Bitmap^ bmpFondo);
    void MoverEnemigos(Bitmap^ bmpFondo);

    void DibujarFondo(Graphics^ g, Bitmap^ bmpFondo);
    void DibujarMapa(
        Graphics^ g,
        Bitmap^ bmpPiso,
        Bitmap^ bmpBloques,
        Bitmap^ bmpTrofeo
    );
    void DibujarTanques(Graphics^ g, Bitmap^ bmpTanques);
};
