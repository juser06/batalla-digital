/*
 * Tablero.cpp
 *
 *  Created on: May 13, 2023
 *      Author: user
 */

#include "Tablero.h"
#include <iostream>

using namespace std;
//------------------------------- CONSTRUCTORES Y DESTRUCTORES --------------------------------------

//constructor
Tablero::Tablero(tiposTableros tamanio){
  this->tamanio = tamanio;
  this->tablero = new Lista<Lista<Lista<Casillero*>*>*>();
  for(int x = 0; x < this->tamanio; x++){
    Lista<Lista<Casillero*>*>* ejeY = new Lista<Lista<Casillero*>*>();
    for(int y = 0; y < tamanio; y++){
      Lista<Casillero*>* ejeZ = new Lista<Casillero*>();
      for(int z = 0; z < 5; z++){
        Casillero* casillero;
        if((x <= tamanio - ((tamanio / 4) + 1)) && z < 3){
          casillero = new Casillero(ACTIVO, TIERRA, x, y, z);
        }
        else if((x > tamanio - ((tamanio / 4) + 1)) && z < 3){
          casillero = new Casillero(ACTIVO, AGUA, x, y, z);
        }
        else{
          casillero = new Casillero(ACTIVO, AIRE, x, y, z);
        }
        ejeZ->add(casillero);
      }
      ejeY->add(ejeZ);
    }
    tablero->add(ejeY);
  }
  this->cantidadDeCasilleros = tamanio * tamanio * 5;
}

//desctructor
Tablero::~Tablero(){
  this->tablero->reiniciarCursor();
  while(tablero->avanzarCursor()){
    Lista<Lista<Casillero*>*>* ejeY = tablero->getCursor();

    ejeY->reiniciarCursor();
    while(ejeY->avanzarCursor()){
      Lista<Casillero*>* ejeZ = ejeY->getCursor();

      ejeZ->reiniciarCursor();
      while(ejeZ->avanzarCursor()){
        Casillero* casillero = ejeZ->getCursor();
        delete casillero;
      }
      delete ejeZ;
    }
    delete ejeY;
  }
  delete tablero;
}




// --------------------------------------- METODOS ----------------------------------------


//metodos publicos
Casillero* Tablero::getCasilleroEnCoordenadas(int x, int y, int z)
{
  Casillero* casillero = NULL;
  this->tablero->reiniciarCursor();
  while(this->tablero->avanzarCursor()){
    casillero = getCasilleroEnCoordenadasY(tablero->getCursor(), x, y, z);
    if(casillero != NULL){
      return casillero;
    }
  }
  return casillero;
}

int Tablero::getTamanio()
{
  return this->tamanio;
}

int Tablero::GetCantidadDeCasilleros()
{
	return this->cantidadDeCasilleros;
}

// ---------------------------------------- PRIVADO ------------------------------------------------

Casillero* Tablero::getCasilleroEnCoordenadasY(Lista<Lista<Casillero*>*>* ejeY, int x, int y, int z)
{
  Casillero* casilleroAux = NULL;
  ejeY->reiniciarCursor();
  while(ejeY->avanzarCursor()){
    casilleroAux = getCasilleroEnCoordenadasEjeZ(ejeY->getCursor(), x, y, z);
    if(casilleroAux != NULL){
      return casilleroAux;
    }
  }
  return casilleroAux;
}

Casillero* Tablero::getCasilleroEnCoordenadasEjeZ(Lista<Casillero*>* ejeZ, int x, int y, int z)
{
  Casillero* casilleroAux = NULL;
  ejeZ->reiniciarCursor();
  while(ejeZ->avanzarCursor()){
    if(ejeZ->getCursor()->getCoordenadaX() == x && ejeZ->getCursor()->getCoordenadaY() == y && ejeZ->getCursor()->getCoordenadaZ() == z){
      casilleroAux = ejeZ->getCursor();
      return casilleroAux;
    }
  }
  return casilleroAux;
}
