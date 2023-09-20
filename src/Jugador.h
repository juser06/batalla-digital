//jugador solo da de alta un jugador con un string y un ID, tiene que tener mas de un constructor que todavia no hice
#ifndef JUGADOR_H_
#define JUGADOR_H_

#include <string>
#include "Lista.h"


class Jugador {
private:
  std::string nombre;
  int ID;
public:
  /*
   * Post: Construye el TDA Jugador.
   * */
  Jugador(std::string nombre);

  /*
   * Post: Construye el TDA Jugador.
   * */
  Jugador();

  /*
   * Post: Devuelve el nombre del jugador.
   * */
  std::string getNombre();

  /*
   * Post: Devuelve el numero del jugador.
   * */
  int getID();

};

#endif /* JUGADOR_H_ */
