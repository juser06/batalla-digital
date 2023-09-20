/*
 * Tablero.h
 *
 *  Created on: May 13, 2023
 *      Author: user
 */

#ifndef TABLERO_H_
#define TABLERO_H_
#include "Lista.h"
#include "Casillero.h"

enum tiposTableros{
  CHICO = 20,
  MEDIO = 28,
  GRANDE = 36,
  INVALIDO = 0
};

class Tablero {
private:
  //propiedades
  tiposTableros tamanio;
  Lista<Lista<Lista<Casillero*>*>*>* tablero;
  int cantidadDeCasilleros;

public:
  //constructor
  //constructor de 3 dimesiones
  //pre: pasar un entero positivo que va a funcionar como base de la matriz
  //post: crea el tablero con 3 listas a puntero casillero, el z esta seteado en 20
  Tablero(tiposTableros tamanio);

  //metodos
  //pre: se le pasan 3 enteros positivos entre 0 y el maximo del tablero - 1
  //post: devulve un puntero al casillero con esa direccion
  Casillero* getCasilleroEnCoordenadas(int x, int y, int z);

  //pre: -
  //post: devuelve el tamanio del tablero
  int getTamanio();

  //post:devuelve la cantidad de casilleros
  int GetCantidadDeCasilleros();


  //Lo pongo aca mientras para que prueben el tablero
  //Todavia no está implementado tema de casilleros/ficha segun jugador dueño
  //Imprime la capa del eje Z recibida vista desde arriba
  void mostrarTablero(unsigned int capaEjeZ);

  virtual ~Tablero();

private:
  //estas dos funciones son complementarias y solo sirven para modularizar la busqueda de casilleros por el mapa, por eso estan como privadas

  //pre: se le pasa un puntero Lista<Lista<Casillero*>*> y tres enteros dentro del rango 0 y tama;o del mapa -1
  //post: devuelve un puntero a casillero
  Casillero* getCasilleroEnCoordenadasY(Lista<Lista<Casillero*>*>* ejeY, int x, int y, int z);

  //pre: se le pasa un puntero Lista<Casillero*> y tres enteros dentro del rango 0 y tamaño del mapa - 1
  //post: devuelve un puntero a casillero
  Casillero* getCasilleroEnCoordenadasEjeZ(Lista<Casillero*>* ejeZ, int x, int y, int z);

};

#endif /* TABLERO_H_ */
