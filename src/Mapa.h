/*
 * Mapa.h
 *
 *  Created on: Jun 15, 2023
 *      Author: user
 */
#include "EasyBMP.h"
#include "BatallaDigital.h"


#ifndef MAPA_H_
#define MAPA_H_

class Mapa {
private:
	BMP * base;
	BMP * imagenCasillero;
	BMP * mapaGenerado;
public:
	Mapa();
	virtual ~Mapa();

	void crearBaseMapa(int tamanio);
	void limpiarMapa();
	void imprimirMapa(JugadorDeBatallaDigital * jugador);
	void mapa(Casillero * casillero, JugadorDeBatallaDigital * jugador);
};

#endif /* MAPA_H_ */
