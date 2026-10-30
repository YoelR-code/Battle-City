
#pragma once

#include "Tanque.h"

using namespace System::Drawing;

enum ETipoTanque {
    tipo1,
    tipo2,
    tipo3,
    tipo4,
    tipo5
};

class CEnemigo : public CTanque {
private:
    ETipoTanque tipo;

public:
    CEnemigo(
        short id,
        short tipo,
        int posx,
        int posy,
        int vidas
    );

    void setTipo(ETipoTanque tipo);
    ETipoTanque getTipo();

    void dibujar(
        Graphics^ g,
        Bitmap^ bmpTanques
    );

    // Patron creacional Prototype:
    // crear un enemigo nuevo copiando este prototipo.
    CEnemigo* Clonar(
        short id,
        int posx,
        int posy,
        int vidas
    );
};
