/*
 * JugadorDeBatallaDigital.h
 *
 *  Created on: May 20, 2023
 *      Author: user
 */
#include "Cartas.h"
#include "Jugador.h"
#include "Ficha.h"

#ifndef JUGADORDEBATALLADIGITAL_H_
#define JUGADORDEBATALLADIGITAL_H_


class JugadorDeBatallaDigital {
	//properties
private:
	Jugador * jugador;
	Lista<Cartas*> * cartasDelJugador;
	bool jugoCartaAvionRadar;
	bool jugoCartaBarco;

public:
	//constructor
	JugadorDeBatallaDigital(std::string nombre);

	JugadorDeBatallaDigital();

	//destructor
	virtual ~JugadorDeBatallaDigital();


	//--------------------------------- metodos ----------------------------------

	//post: devuelve el puntero de jugador
	Jugador* getJugador();

	/*
	* Post: Devuelve la lista de cartas del jugador.
	* */
	Lista<Cartas*> *getListaDeCartas();

	/*
	 *	Post: Cambia la propiedad jugoCartaAvionRadar a true.
	 * */
	void setJugoCartaAvionRadar();

	/*
	 *	Post: Devuelve true si el jugador ya jugo una carta de avion radar, y false sino.
	 * */
	bool getJugoCartaAvionRadar();

	/*
	 *	Post: Cambia la propiedad jugoCartaBarco a true.
	 * */
	void setJugoCartaBarco();

	/*
	 *	Post: Devuelve true si el jugador ya jugo una carta de avion radar, y false sino.
	 * */
	bool getJugoCartaBarco();

};


#endif /* JUGADORDEBATALLADIGITAL_H_ */
