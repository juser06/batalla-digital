#ifndef VENTANA_H_
#define VENTANA_H_
#include <iostream>
#include <string>
#include <limits>
#include "Cartas.h"

class Ventana {
public:
  //constructor

  //post:crea un TDA ventana
  Ventana();

  //post toma el numero pasado por consola y lo devuelve
  int preguntarNumero(int x, int y);

  int preguntarNumeroUnico(int x);

  void mostrarMensajeConsola(std::string mensaje);

  /*
   * Post: Imprime primero el mensaje y luego el numero.
   * */
  void mostrarMensajeConsolaConNumero(const char* mensaje, const int numero);

  void mostrarCartas(Cartas * mano);

  /*
   * Post: Le pide al usuario una letra que este dentro de la validacion y devuelve la letra ingresada por el usuario
   * */
  char preguntarLetra(const char validacionLetraUno, const char validacionLetraDos, const char validacionLetraTres, const char validacionLetraCuatro);

  bool PreguntaSiONo(std::string);
};

#endif /* VENTANA_H_ */
