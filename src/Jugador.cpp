#include "Jugador.h"
#include <sstream>
#include <iostream>
int contador = 1;//comprobar que se pueda hacer esto

Jugador::Jugador(std::string nombre){
  this->nombre = nombre;
  this->ID = contador;
  contador++;
}

Jugador::Jugador()
{
	this->ID = contador;
	switch (ID)
	{
	case 1:
		this->nombre = "Jugador 1";
		break;
	case 2:
		this->nombre = "Jugador 2";
		break;
	case 3:
		this->nombre = "Jugador 3";
		break;
	case 4:
		this->nombre = "Jugador 4";
		break;
	}
	contador++;
}

std::string Jugador::getNombre(){
  return this->nombre;
}
int Jugador::getID(){
  return this->ID;
}
