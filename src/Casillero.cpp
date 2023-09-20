#include "Casillero.h"
#include "Ficha.h"

Casillero::Casillero(ESTADO estadoDelCasillero, TIPODECASILLERO tipoDeCasillero, int coordenadaX, int coordenadaY, int coordenadaZ){
  this->tipoDeCasillero = tipoDeCasillero;
  this->estadoDelCasillero = estadoDelCasillero;
  this->coordenadaX = coordenadaX;
  this->coordenadaY = coordenadaY;
  this->coordenadaZ = coordenadaZ;
  this->ficha = new Ficha(VACIA, NULL);
  this->turnoAActivarse = TURNO_NO_USADO;
}
//metodos

ESTADO Casillero::getEstado(){
  return estadoDelCasillero;
}

void Casillero::setEstado(ESTADO estadoNuevo){
  estadoDelCasillero = estadoNuevo;
}

TIPODECASILLERO Casillero::getTipoDeCasillero(){
  return tipoDeCasillero;
}

void Casillero::setTipoDeCasillero(TIPODECASILLERO tipoDeCasilleroNuevo){
  tipoDeCasillero = tipoDeCasilleroNuevo;
}

int Casillero::getCoordenadaX(){
  return coordenadaX;
}

int Casillero::getCoordenadaY(){
  return coordenadaY;
}

int Casillero::getCoordenadaZ(){
  return coordenadaZ;
}
Ficha* Casillero::getFicha(){
  return this->ficha;
}

void Casillero::setTurnoAActivarse(int turnoAActivarse){
    this->turnoAActivarse = turnoAActivarse;
  }

int Casillero::getTurnoAActivarse(){
  return this->turnoAActivarse;
}

Casillero::~Casillero(){
  delete ficha;
}


