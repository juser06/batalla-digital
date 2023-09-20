/*
 * Ficha.cpp
 *
 *  Created on: May 13, 2023
 *      Author: user
 */

#include "Ficha.h"

int iDUltimaFicha=0;

Ficha::Ficha(TIPODEFICHA tipoDeFicha, JugadorDeBatallaDigital* jugador){
  this->tipoDeFicha = tipoDeFicha;
  this->jugador = NULL;
  this->idFicha = NULL;
}

//metodos
TIPODEFICHA Ficha::getTipoDeFicha(){
  return this->tipoDeFicha;
}

void Ficha::setFicha(TIPODEFICHA fichaNueva, JugadorDeBatallaDigital* jugador){
  this->tipoDeFicha = fichaNueva;
  this->jugador = jugador;
  if (this->idFicha == NULL)
  {
	  this->idFicha = iDUltimaFicha + 1;
	  iDUltimaFicha++;
  }
}

int Ficha::getIdFicha(){
  return this->idFicha;
}

JugadorDeBatallaDigital* Ficha::getJugadorDeBatallaDigital(){
  return this->jugador;
}

int Ficha::GetIdUltimaFicha()
{
	return iDUltimaFicha;
}