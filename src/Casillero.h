/*
 * Casillero.h
 *
 *  Created on: May 13, 2023
 *      Author: user
 */

#ifndef CASILLERO_H_
#define CASILLERO_H_
#include "Ficha.h"
#include "Lista.h"

const int TURNO_NO_USADO = -1;

enum TIPODECASILLERO
{
  VACIO,
  TIERRA,
  AIRE,
  AGUA,
};

enum ESTADO
{
  ACTIVO,
  INACTIVO,
  CONTAMINADO,
};

class Casillero
{
private:
  //properties
  ESTADO estadoDelCasillero;
  TIPODECASILLERO tipoDeCasillero;
  Ficha* ficha;
  int coordenadaX;
  int coordenadaY;
  int coordenadaZ;
  int turnoAActivarse;

public:
  //constructor
  //pre:se le pasa un ESTADO, TIPODECASILLERO de los enum y enteros validos entre 0 y el tamaño del mapa
  //post: crea el casillero con esos datos y un puntero ficha con jugador nulo y ficha vacia
  Casillero(ESTADO estadoDelCasillero, TIPODECASILLERO tipoDeCasillero, int coordenadaX, int coordenadaY, int coordenadaZ);

  //metodos

  //post: devuelve el estado como enum
  ESTADO getEstado();

  //pre: se le pasa un estado nuevo de los del enum
  //post: modifica el estado por el nuevo
  void setEstado(ESTADO estadoNuevo);

  //post: devuelve el tipo de casillero
  TIPODECASILLERO getTipoDeCasillero();

  //pre: se le pasa un tipo de casillero valido de los del enum
  //post: cambia el tipo de casillero
  void setTipoDeCasillero(TIPODECASILLERO tipoDeCasilleroNuevo);

  //post: devuelve el puntero a la ficha vinculada con el casillero
  Ficha* getFicha();

  //post: devuelve la coordenada x del casillero
  int getCoordenadaX();

  //post: devuelve la coordenada y del casillero
  int getCoordenadaY();

  //post: devuelve la coordenada z del casillero
  int getCoordenadaZ();

  //Post: Cambia el turnoAActivarse;
  //Pre: Debe de recibir un turno positivo.
  void setTurnoAActivarse(int turnoAActivarse);

  //Post: Devuelve el turno a desaparecer.
  int getTurnoAActivarse();

  virtual ~Casillero();
};

#endif /* CASILLERO_H_ */
