
#include "Mapa.h"

CMapa::CMapa() {
    nivel = 1;

    for (int i = 0; i < MAX_FILAS; i++) {
        for (int j = 0; j < MAX_COLUMNAS; j++) {
            mapa[i][j] = nullptr;
        }
    }
}

CMapa::~CMapa() {
    for (int i = 0; i < MAX_FILAS; i++) {
        for (int j = 0; j < MAX_COLUMNAS; j++) {
            delete mapa[i][j];
            mapa[i][j] = nullptr;
        }
    }
}

void CMapa::setNivel(int nivel) {
    this->nivel = nivel;
}

int CMapa::getNivel() {
    return nivel;
}

CBloque* CMapa::getBloque(int i, int j) {
    if (i < 0 || i >= MAX_FILAS ||
        j < 0 || j >= MAX_COLUMNAS) {
        return nullptr;
    }

    return mapa[i][j];
}

CBloque* (*CMapa::getMapa())[MAX_COLUMNAS] {
    return mapa;
}

void CMapa::CargarNivel(int datos[MAX_FILAS][MAX_COLUMNAS]) {
    for (int i = 0; i < MAX_FILAS; i++) {
        for (int j = 0; j < MAX_COLUMNAS; j++) {
            delete mapa[i][j];
            mapa[i][j] = nullptr;

            if (datos[i][j] == 1) {
                mapa[i][j] = new CBloque(
                    ETipoBloque::piso, 0
                );
            }
            else if (datos[i][j] == 2) {
                mapa[i][j] = new CBloque(
                    ETipoBloque::destruible, 2,
                    bloqueCompleto, posicionCompleta, 0
                );
            }
            else if (datos[i][j] == 3) {
                mapa[i][j] = new CBloque(
                    ETipoBloque::noDestruible, -1,
                    bloqueCompleto, posicionCompleta, 0
                );
            }
            else if (datos[i][j] == 4) {
                mapa[i][j] = new CBloque(
                    ETipoBloque::agua, 0,
                    bloqueCompleto, posicionCompleta, 0
                );
            }
            else if (datos[i][j] == 5) {
                mapa[i][j] = new CBloque(
                    ETipoBloque::arbol, 0,
                    bloqueCompleto, posicionCompleta, 0
                );
            }
            else if (datos[i][j] == 6) {
                mapa[i][j] = new CBloque(
                    ETipoBloque::destruible, 2,
                    bloqueHorizontal, posicionArriba, 0
                );
            }
            else if (datos[i][j] == 7) {
                mapa[i][j] = new CBloque(
                    ETipoBloque::destruible, 2,
                    bloqueVertical, posicionIzquierda, 0
                );
            }
            else if (datos[i][j] == 8) {
                mapa[i][j] = new CBloque(
                    ETipoBloque::noDestruible, -1,
                    bloqueHorizontal, posicionArriba, 0
                );
            }
            else if (datos[i][j] == 9) {
                mapa[i][j] = new CBloque(
                    ETipoBloque::trofeo, 1
                );
            }
            else if (datos[i][j] == 10) {
                mapa[i][j] = new CBloque(
                    ETipoBloque::noDestruible, -1,
                    bloqueVertical, posicionIzquierda, 0
                );
            }
            else if (datos[i][j] == 11) {
                mapa[i][j] = new CBloque(
                    ETipoBloque::destruible, 2,
                    bloqueHorizontal, posicionAbajo, 0
                );
            }
            else if (datos[i][j] == 12) {
                mapa[i][j] = new CBloque(
                    ETipoBloque::destruible, 2,
                    bloqueVertical, posicionDerecha, 0
                );
            }
            else if (datos[i][j] == 13) {
                mapa[i][j] = new CBloque(
                    ETipoBloque::noDestruible, -1,
                    bloqueHorizontal, posicionAbajo, 0
                );
            }
            else if (datos[i][j] == 14) {
                mapa[i][j] = new CBloque(
                    ETipoBloque::noDestruible, -1,
                    bloqueVertical, posicionDerecha, 0
                );
            }
        }
    }
}

// NIVEL 1
void CMapa::nivel1() {
    int tmpNivel1[MAX_FILAS][MAX_COLUMNAS] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,2,1,2,1,2,1,1,1,2,1,2,1},
        {1,2,1,2,1,3,1,2,1,2,1,2,1},
        {1,2,1,2,1,2,1,2,1,2,1,2,1},
        {1,2,1,2,1,2,1,2,1,2,1,2,1},
        {1,1,1,1,1,1,1,1,1,1,1,2,1},
        {1,1,2,2,2,1,2,1,1,1,1,2,1},
        {1,1,3,1,1,1,2,1,1,2,1,3,1},
        {1,1,2,1,1,1,1,1,1,3,1,1,1},
        {1,1,1,1,1,2,2,2,1,3,1,1,1},
        {1,1,1,1,1,2,9,2,1,1,1,1,1}
    };

    setNivel(1);
    std::cout << "Inicializando nivel 1\n";
    CargarNivel(tmpNivel1);
}

// NIVEL 2
void CMapa::nivel2() {
    int tmpNivel2[MAX_FILAS][MAX_COLUMNAS] = {
        {1,1,1,1,2,2,1,1,1,1,1,1,1},
        {13,1,11,1,2,1,1,1,8,8,3,1,1},
        {3,1,2,1,1,1,2,1,1,4,4,1,4},
        {2,1,2,1,1,1,2,2,1,4,1,1,1},
        {6,1,1,1,4,4,1,4,4,4,1,2,2},
        {1,1,11,1,4,2,1,2,7,1,1,1,1},
        {2,2,1,1,4,1,1,1,1,1,14,10,1},
        {1,1,1,1,4,1,3,1,2,1,14,1,1},
        {4,4,4,1,1,1,1,1,1,1,14,2,2},
        {1,1,1,11,1,2,2,2,1,1,1,1,1},
        {1,1,1,1,1,2,9,2,1,1,2,1,1}
    };

    setNivel(2);
    std::cout << "Inicializando nivel 2\n";
    CargarNivel(tmpNivel2);
}

// NIVEL 3
void CMapa::nivel3() {
    int tmpNivel3[MAX_FILAS][MAX_COLUMNAS] = {
        {1,1,1,1,1,1,1,1,1,1,1},
        {5,5,1,2,2,2,2,2,1,5,5},
        {1,1,2,2,5,2,5,2,2,1,1},
        {1,1,2,5,5,2,5,5,2,1,1},
        {1,1,2,2,2,2,2,2,2,1,1},
        {1,1,2,5,5,2,5,5,2,1,1},
        {5,5,2,2,5,2,5,2,2,5,5},
        {4,4,1,2,2,2,2,2,1,4,4},
        {3,3,1,1,1,1,1,1,1,3,3},
        {2,2,1,1,11,11,11,1,1,2,2},
        {1,1,1,1,2,9,2,1,1,1,1}
    };

    setNivel(3);
    std::cout << "Inicializando nivel 3\n";
    CargarNivel(tmpNivel3);
}

// NIVEL 4
void CMapa::nivel4() {
    int tmpNivel4[MAX_FILAS][MAX_COLUMNAS] = {
        {5,5,1,1,1,1,1,1,1,5,5},
        {1,1,1,2,2,2,2,2,1,1,1},
        {1,1,2,2,2,2,2,2,2,2,1},
        {1,1,2,2,2,2,2,2,2,2,2},
        {1,2,2,1,1,1,2,2,2,1,2},
        {1,2,1,3,1,3,1,2,2,1,1},
        {4,2,1,2,2,1,1,2,2,1,4},
        {1,2,2,2,2,2,2,2,2,1,1},
        {6,2,2,2,2,2,2,2,2,6,1},
        {1,1,1,6,2,2,2,6,1,1,1},
        {3,5,1,1,2,9,2,1,1,5,3}
    };

    setNivel(4);
    std::cout << "Inicializando nivel 4\n";
    CargarNivel(tmpNivel4);
}

// NIVEL 5
void CMapa::nivel5() {
    int tmpNivel5[MAX_FILAS][MAX_COLUMNAS] = {
        {1,1,1,1,1,1,1,1,1,3,1,1,1},
        {4,4,2,2,2,4,4,4,1,3,1,4,4},
        {4,4,2,2,2,4,4,4,1,3,1,4,4},
        {1,1,1,1,1,1,1,3,1,2,1,1,1},
        {2,2,1,2,2,7,1,2,2,2,2,2,2},
        {2,2,1,2,2,7,1,1,2,1,1,1,1},
        {1,1,1,1,1,1,12,2,2,1,2,2,2},
        {1,2,2,2,3,1,1,2,1,1,2,2,3},
        {1,1,3,1,1,1,1,1,1,1,1,1,1},
        {1,1,1,1,1,2,2,2,1,1,1,2,1},
        {1,1,2,1,1,2,9,2,1,2,1,2,1}
    };

    setNivel(5);
    std::cout << "Inicializando nivel 5\n";
    CargarNivel(tmpNivel5);
}

// DIBUJAR MAPA CON BLOQUES Y TROFEO
void CMapa::DibujarMapa(
    Graphics^ g,
    Bitmap^ bmpPiso,
    Bitmap^ bmpBloques,
    Bitmap^ bmpTrofeo
) {
    int X = 0;
    int Y = 0;

    for (int i = 0; i < MAX_FILAS; i++) {
        X = 0;

        for (int j = 0; j < MAX_COLUMNAS; j++) {
            CBloque* bloque = getBloque(i, j);

            if (bloque == nullptr) {
                X += ANCHO_IMAGEN;
                continue;
            }

            int ancho = 64;
            int alto = 64;

            if (bloque->getTamano() == bloqueHorizontal) {
                ancho = 64;
                alto = 32;
            }
            else if (bloque->getTamano() == bloqueVertical) {
                ancho = 32;
                alto = 64;
            }

            int destinoX = X;
            int destinoY = Y;

            if (bloque->getTamano() == bloqueHorizontal) {
                if (bloque->getPosicion() == posicionArriba)
                    destinoY = Y;
                else if (bloque->getPosicion() == posicionAbajo)
                    destinoY = Y + 32;
            }
            else if (bloque->getTamano() == bloqueVertical) {
                if (bloque->getPosicion() == posicionIzquierda)
                    destinoX = X;
                else if (bloque->getPosicion() == posicionDerecha)
                    destinoX = X + 32;
            }

            if (bloque->getTipo() == piso) {
                Rectangle origen(0, 0, 64, 64);
                Rectangle destino(destinoX, destinoY, ancho, alto);

                g->DrawImage(
                    bmpPiso, destino, origen, GraphicsUnit::Pixel
                );
            }
            else if (bloque->getTipo() == destruible) {
                int origenX = 0;
                int origenY = 0;
                int sprite = bloque->getSprite();

                if (sprite == 1)
                    origenX = 64;

                Rectangle origen;

                if (bloque->getTamano() == bloqueCompleto)
                    origen = Rectangle(origenX, origenY, 64, 64);
                else if (bloque->getTamano() == bloqueHorizontal)
                    origen = Rectangle(origenX, origenY, 64, 32);
                else
                    origen = Rectangle(origenX, origenY, 32, 64);

                Rectangle destino(destinoX, destinoY, ancho, alto);

                g->DrawImage(
                    bmpBloques, destino, origen, GraphicsUnit::Pixel
                );
            }
            else if (bloque->getTipo() == noDestruible) {
                int sprite = bloque->getSprite();
                int origenX = 0;
                int origenY = 64;

                if (sprite == 1)
                    origenX = 128;
                else if (sprite == 2)
                    origenX = 192;

                Rectangle origen;

                if (bloque->getTamano() == bloqueCompleto)
                    origen = Rectangle(origenX, origenY, 64, 64);
                else if (bloque->getTamano() == bloqueHorizontal)
                    origen = Rectangle(origenX, origenY, 64, 32);
                else
                    origen = Rectangle(origenX, origenY, 32, 64);

                Rectangle destino(destinoX, destinoY, ancho, alto);

                g->DrawImage(
                    bmpBloques, destino, origen, GraphicsUnit::Pixel
                );
            }
            else if (bloque->getTipo() == agua) {
                int origenX = (bloque->getSprite() == 0) ? 128 : 192;

                Rectangle origen(origenX, 0, 64, 64);
                Rectangle destino(destinoX, destinoY, ancho, alto);

                g->DrawImage(
                    bmpBloques, destino, origen, GraphicsUnit::Pixel
                );
            }
            else if (bloque->getTipo() == arbol) {
                Rectangle origen(64, 64, 64, 64);
                Rectangle destino(destinoX, destinoY, ancho, alto);

                g->DrawImage(
                    bmpBloques, destino, origen, GraphicsUnit::Pixel
                );
            }
            else if (bloque->getTipo() == trofeo) {
                Rectangle origen(0, 0, 64, 64);
                Rectangle destino(destinoX, destinoY, ancho, alto);

                g->DrawImage(
                    bmpTrofeo, destino, origen, GraphicsUnit::Pixel
                );
            }

            X += ANCHO_IMAGEN;
        }

        Y += ALTO_IMAGEN;
    }
}

// DIBUJAR EL FONDO DEL NIVEL
void CMapa::DibujarFondo(Graphics^ g, Bitmap^ bmpFondo) {
    if (g == nullptr || bmpFondo == nullptr)
        return;

    g->DrawImage(
        bmpFondo,
        0,
        0,
        bmpFondo->Width,
        bmpFondo->Height
    );
}
