
#include "Controladora.h"
#include <cstdlib>
#include <ctime>

// ==========================================
// SINGLETON
// ==========================================

CControladora* CControladora::instancia = nullptr;

CControladora* CControladora::ObtenerInstancia() {
    if (instancia == nullptr) {
        instancia = new CControladora();
    }

    return instancia;
}

// ==========================================
// CONSTRUCTOR Y DESTRUCTOR
// ==========================================

CControladora::CControladora() {
    mapa = new CMapa();
    jugador = nullptr;
    coleccionEnemigos = new CColeccionEnemigos();
}

CControladora::~CControladora() {
    delete jugador;
    jugador = nullptr;

    delete coleccionEnemigos;
    coleccionEnemigos = nullptr;

    delete mapa;
    mapa = nullptr;
}

// ==========================================
// INICIALIZAR JUEGO
// ==========================================

void CControladora::Inicializar() {
    delete jugador;
    jugador = nullptr;

    if (coleccionEnemigos != nullptr)
        coleccionEnemigos->Limpiar();

    mapa->nivel1();

    jugador = new CJugador(0, 384, 64, 3);
    jugador->setDireccion(abajo);
    jugador->setVelocidad(10);

    CEnemigo* enemigo =
        coleccionEnemigos->Crear(1, tipo1, 64, 0, 1);

    if (enemigo != nullptr) {
        enemigo->setDireccion(abajo);
        enemigo->setVelocidad(10);
    }
}

// ==========================================
// OBTENER NIVEL ACTUAL
// ==========================================

int CControladora::getNivel() {
    if (mapa == nullptr)
        return 1;

    return mapa->getNivel();
}

// ==========================================
// IDENTIFICAR OBSTACULOS POR COLOR
// ==========================================

bool CControladora::EsObstaculo(Color pixel) {
    int r = pixel.R;
    int g = pixel.G;
    int b = pixel.B;

    if (r > 125 &&
        r > g * 1.30 &&
        r > b * 1.30 &&
        g < 165) {
        return true;
    }

    int difRG = r - g;
    int difGB = g - b;

    if (difRG < 0) difRG = -difRG;
    if (difGB < 0) difGB = -difGB;

    if (r > 90 &&
        g > 90 &&
        b > 90 &&
        difRG < 35 &&
        difGB < 35) {
        return true;
    }

    if (b > 120 &&
        b > r + 45 &&
        b > g + 45) {
        return true;
    }

    return false;
}

// ==========================================
// COMPROBAR COLISION
// ==========================================

bool CControladora::TieneColision(
    int x,
    int y,
    Bitmap^ bmpFondo
) {
    if (bmpFondo == nullptr)
        return true;

    const int margen = 8;
    const int tamano = 48;

    int tx = x + margen;
    int ty = y + margen;

    if (tx < 0 ||
        ty < 0 ||
        tx + tamano > bmpFondo->Width ||
        ty + tamano > bmpFondo->Height) {
        return true;
    }

    const int pasoMuestra = 3;

    for (int py = ty; py < ty + tamano; py += pasoMuestra) {
        for (int px = tx; px < tx + tamano; px += pasoMuestra) {
            if (EsObstaculo(bmpFondo->GetPixel(px, py)))
                return true;
        }
    }

    for (int i = 0; i < tamano; i += pasoMuestra) {
        Color derecha =
            bmpFondo->GetPixel(tx + tamano - 1, ty + i);

        Color inferior =
            bmpFondo->GetPixel(tx + i, ty + tamano - 1);

        if (EsObstaculo(derecha) || EsObstaculo(inferior))
            return true;
    }

    return false;
}

// ==========================================
// CAMBIAR DE NIVEL
// ==========================================

void CControladora::CambiarNivel(
    int nivel,
    Bitmap^ bmpFondo
) {
    if (mapa == nullptr || bmpFondo == nullptr)
        return;

    switch (nivel) {
    case 1: mapa->nivel1(); break;
    case 2: mapa->nivel2(); break;
    case 3: mapa->nivel3(); break;
    case 4: mapa->nivel4(); break;
    case 5: mapa->nivel5(); break;
    default: return;
    }

    if (jugador != nullptr) {
        bool encontrado = false;

        for (int fila = 0;
            fila < MAX_FILAS && !encontrado; fila++) {

            for (int columna = 0;
                columna < MAX_COLUMNAS; columna++) {

                int x = columna * ANCHO_IMAGEN;
                int y = fila * ALTO_IMAGEN;

                if (!TieneColision(x, y, bmpFondo)) {
                    jugador->setX(x);
                    jugador->setY(y);
                    jugador->setDireccion(abajo);
                    encontrado = true;
                    break;
                }
            }
        }
    }

    if (coleccionEnemigos != nullptr &&
        coleccionEnemigos->Cantidad() > 0) {

        CEnemigo* enemigo = coleccionEnemigos->Obtener(0);

        if (enemigo != nullptr) {
            bool encontrado = false;

            for (int fila = MAX_FILAS - 1;
                fila >= 0 && !encontrado; fila--) {

                for (int columna = MAX_COLUMNAS - 1;
                    columna >= 0; columna--) {

                    int x = columna * ANCHO_IMAGEN;
                    int y = fila * ALTO_IMAGEN;

                    if (TieneColision(x, y, bmpFondo))
                        continue;

                    if (jugador != nullptr) {
                        int dx = x - jugador->getX();
                        int dy = y - jugador->getY();

                        if (dx < 0) dx = -dx;
                        if (dy < 0) dy = -dy;

                        if (dx < 48 && dy < 48)
                            continue;
                    }

                    enemigo->setX(x);
                    enemigo->setY(y);
                    enemigo->setDireccion(arriba);

                    encontrado = true;
                    break;
                }
            }
        }
    }
}

// ==========================================
// MOVER JUGADOR
// ==========================================

void CControladora::MoverJugador(
    EDireccion direccion,
    Bitmap^ bmpFondo
) {
    if (jugador == nullptr || bmpFondo == nullptr)
        return;

    jugador->setDireccion(direccion);

    int nx = jugador->getX();
    int ny = jugador->getY();
    int paso = jugador->getVelocidad();

    switch (direccion) {
    case arriba:    ny -= paso; break;
    case abajo:     ny += paso; break;
    case izquierda: nx -= paso; break;
    case derecha:   nx += paso; break;
    default: return;
    }

    if (!TieneColision(nx, ny, bmpFondo))
        jugador->mover();
}

// ==========================================
// MOVER ENEMIGOS
// ==========================================

void CControladora::MoverEnemigos(Bitmap^ bmpFondo) {
    if (coleccionEnemigos == nullptr || bmpFondo == nullptr)
        return;

    CEnemigo* enemigo = coleccionEnemigos->Obtener(0);

    if (enemigo == nullptr)
        return;

    int x = enemigo->getX();
    int y = enemigo->getY();
    int paso = enemigo->getVelocidad();

    EDireccion actual = enemigo->getDireccion();

    int nx = x;
    int ny = y;

    switch (actual) {
    case arriba:    ny -= paso; break;
    case abajo:     ny += paso; break;
    case izquierda: nx -= paso; break;
    case derecha:   nx += paso; break;
    default: return;
    }

    if (!TieneColision(nx, ny, bmpFondo)) {
        enemigo->setX(nx);
        enemigo->setY(ny);
        return;
    }

    EDireccion opciones[3];

    switch (actual) {
    case arriba:
    case abajo:
        opciones[0] = izquierda;
        opciones[1] = derecha;
        opciones[2] = (actual == arriba) ? abajo : arriba;
        break;

    case izquierda:
    case derecha:
        opciones[0] = arriba;
        opciones[1] = abajo;
        opciones[2] = (actual == izquierda) ? derecha : izquierda;
        break;

    default:
        return;
    }

    static bool inicializado = false;

    if (!inicializado) {
        srand((unsigned int)time(nullptr));
        inicializado = true;
    }

    if (rand() % 2 == 0) {
        EDireccion temporal = opciones[0];
        opciones[0] = opciones[1];
        opciones[1] = temporal;
    }

    for (int i = 0; i < 3; i++) {
        nx = x;
        ny = y;

        switch (opciones[i]) {
        case arriba:    ny -= paso; break;
        case abajo:     ny += paso; break;
        case izquierda: nx -= paso; break;
        case derecha:   nx += paso; break;
        default: break;
        }

        if (!TieneColision(nx, ny, bmpFondo)) {
            enemigo->setDireccion(opciones[i]);
            enemigo->setX(nx);
            enemigo->setY(ny);
            return;
        }
    }
}

// ==========================================
// DIBUJAR MAPA
// ==========================================

void CControladora::DibujarMapa(
    Graphics^ g,
    Bitmap^ bmpPiso,
    Bitmap^ bmpBloques,
    Bitmap^ bmpTrofeo
) {
    if (mapa == nullptr)
        return;

    mapa->DibujarMapa(g, bmpPiso, bmpBloques, bmpTrofeo);
}

// ==========================================
// DIBUJAR FONDO
// ==========================================

void CControladora::DibujarFondo(
    Graphics^ g,
    Bitmap^ bmpFondo
) {
    if (mapa == nullptr || g == nullptr || bmpFondo == nullptr)
        return;

    mapa->DibujarFondo(g, bmpFondo);
}

// ==========================================
// DIBUJAR TANQUES
// ==========================================

void CControladora::DibujarTanques(
    Graphics^ g,
    Bitmap^ bmpTanques
) {
    if (jugador != nullptr)
        jugador->dibujar(g, bmpTanques);

    if (coleccionEnemigos == nullptr)
        return;

    CEnemigo* enemigo = coleccionEnemigos->Obtener(0);

    if (enemigo != nullptr)
        enemigo->dibujar(g, bmpTanques);
}
