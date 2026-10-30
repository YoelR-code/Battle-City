#pragma once
#include "Comun.h"

class CTanque {
	short id;
	short vidas;
	EDireccion direccion;
	short velocidad;
	int posX;
	int posY;
	short powerups[99];
public:
	CTanque(short id, int posX, int posY, int vidas);
	~CTanque();
	void setId(short id);
	void setVidas(short vidas);
	void setDireccion(EDireccion direccion);
	void setVelocidad(short velocidad);
	void setX(int posX);
	void setY(int posY);

	short getId();
	short getVidas();
	EDireccion getDireccion();
	short getVelocidad();
	int getX();
	int getY();
};

