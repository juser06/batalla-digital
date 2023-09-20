#include "Cartas.h"

Cartas::Cartas(CARTA carta)
{
	this->carta = carta;
	this->cantidad = 0;
}

CARTA Cartas::getCarta()
{
	return this->carta;
}

int Cartas::getCantidad()
{
	return this-> cantidad;
}

void Cartas::setCantidad(int nuevaCantidad)
{
	this->cantidad += nuevaCantidad;
}
