#ifndef FICHA_H_
#define FICHA_H_

#include "Jugador.h"
#include "JugadorDeBatallaDigital.h"

enum TIPODEFICHA
{
  VACIA,
  SOLDADO,
  MINA,
  BARCO,
  AVION
};

class Ficha
{
private:
  TIPODEFICHA tipoDeFicha;
  JugadorDeBatallaDigital* jugador;
  int idFicha;

public:
  //constructor
  //pre: se le pasa un tipo de ficha y un puntero a jugador para crear, cuando se da de alta el mapa ya se crea con tipo vacia y jugador en nulo
  //     El idFicha se tiene que inicializar en el main con un idFicha=0.
  //post: crea una ficha
  Ficha(TIPODEFICHA tipoDeFicha, JugadorDeBatallaDigital* jugador);

  //metodos

  //post: devuelve el tipo de ficha como enum
  TIPODEFICHA getTipoDeFicha();

  /*
   * Post: Devuelve el id de la ficha.
   * */
  int getIdFicha();

  //Devuelve el jugador para luego entrar a la id
  JugadorDeBatallaDigital* getJugadorDeBatallaDigital();

  //pre: se le pasa un TIPODEFICHA valido y el puntero al jugador due;o de dicha ficha, y se pasa la id que va a tener la ficha.
  //post: como cuando se crea el mapa todas las fichas ya existen esto solo cambia el tipo y se lo asigna a un jugador,
  //      Y al momento ded usar las fichas, se les colocara una id.
  void setFicha(TIPODEFICHA fichaNueva, JugadorDeBatallaDigital* jugador);

  /*
  Post: Te devuelve la ID de la ultima ficha.
  */
  int GetIdUltimaFicha();
};

#endif /* FICHA_H_ */
