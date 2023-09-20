#include "JugadorDeBatallaDigital.h"
#include <iostream>
using namespace std;

//------------------------- CONSTRUCTOR -------------------------
JugadorDeBatallaDigital::JugadorDeBatallaDigital()
{
	this-> jugador = new Jugador();
	this->cartasDelJugador = new Lista<Cartas*>;
	this->cartasDelJugador->add(new Cartas(ATAQUEQUIMICO));
	this->cartasDelJugador->add(new Cartas(AVIONRADAR));
	this->cartasDelJugador->add(new Cartas(CARTABARCO));
	this->cartasDelJugador->add(new Cartas(ATAQUEAEREO));
	this->cartasDelJugador->add(new Cartas(REPITETURNO));
	this->cartasDelJugador->add(new Cartas(TRESMINAS));
	this->jugoCartaAvionRadar = false;
	this->jugoCartaBarco = false;
}

JugadorDeBatallaDigital::~JugadorDeBatallaDigital(){
	delete this->jugador;
	this->cartasDelJugador->reiniciarCursor();
	while(this->cartasDelJugador->avanzarCursor()){
		delete this->cartasDelJugador->getCursor();
	}
	delete this->cartasDelJugador;
}


// ---------------------------- METODO ---------------------------
Jugador* JugadorDeBatallaDigital::getJugador()
{
	return this->jugador;
}

Lista<Cartas*> *JugadorDeBatallaDigital::getListaDeCartas()
{
	return this->cartasDelJugador;
}
/*
Lista<Ficha*>* JugadorDeBatallaDigital::getMinasDetectadasPorAvion(){
	return this->minasDetectadasPorAvion;
}*/

void JugadorDeBatallaDigital::setJugoCartaAvionRadar(){
	this->jugoCartaAvionRadar = true;
}

bool JugadorDeBatallaDigital::getJugoCartaAvionRadar(){
	return this->jugoCartaAvionRadar;
}

void JugadorDeBatallaDigital::setJugoCartaBarco(){
	this->jugoCartaBarco = true;
}

bool JugadorDeBatallaDigital::getJugoCartaBarco(){
	return this->jugoCartaBarco;
}


