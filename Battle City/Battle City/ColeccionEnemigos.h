
#pragma once

#include "Enemigo.h"
#include <vector>

class CColeccionEnemigos {
private:
    // Prototipo utilizado para crear enemigos.
    CEnemigo* prototipo;

    // Coleccion de enemigos creados.
    std::vector<CEnemigo*> enemigos;

public:
    CColeccionEnemigos() {
        prototipo = new CEnemigo(1, tipo1, 0, 0, 1);

        prototipo->setDireccion(abajo);
        prototipo->setVelocidad(10);
    }

    ~CColeccionEnemigos() {
        Limpiar();

        delete prototipo;
        prototipo = nullptr;
    }

    // Patron Prototype: crear enemigos clonando el prototipo.
    CEnemigo* Crear(
        short id,
        ETipoTanque tipo,
        int x,
        int y,
        int vidas
    ) {
        if (prototipo == nullptr)
            return nullptr;

        CEnemigo* nuevo =
            prototipo->Clonar(id, x, y, vidas);

        if (nuevo == nullptr)
            return nullptr;

        nuevo->setTipo(tipo);
        enemigos.push_back(nuevo);

        return nuevo;
    }

    // Devolver la cantidad de enemigos.
    int Cantidad() {
        return (int)enemigos.size();
    }

    // Obtener un enemigo por indice.
    CEnemigo* Obtener(int indice) {
        if (indice < 0 ||
            indice >= (int)enemigos.size()) {
            return nullptr;
        }

        return enemigos[indice];
    }

    // Liberar la memoria de todos los enemigos.
    void Limpiar() {
        for (size_t i = 0; i < enemigos.size(); i++) {
            delete enemigos[i];
        }

        enemigos.clear();
    }
};
