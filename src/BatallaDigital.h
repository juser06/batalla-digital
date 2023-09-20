/*
 * BatallaDigital.h
 *
 *  Created on: May 14, 2023
 *      Author: user
 */

#ifndef BATALLADIGITAL_H_
#define BATALLADIGITAL_H_
#include "Ventana.h"
#include "Tablero.h"
#include "JugadorDeBatallaDigital.h"
#include "Cartas.h"
#include "Mapa.h"
#include <string>

class BatallaDigital {

private:

  Ventana* ventana;   //es la funcion que muestra por consola y pide los datos
  Tablero* tablero;   //es el tablero del juego
  Lista<JugadorDeBatallaDigital*>* jugadores;  //lista de los jugadores de batalla digital
  Lista<Ficha*>* fichas;   //lista de las fichas activas
  JugadorDeBatallaDigital* jugadorAlTurno;   //jugador que esta activo en este turno
  int turno;   //turno en el que se esta jugando
  Mapa * mapa;

public:
  //------------------------- CONSTRUCTOR --------------------------------------

  //post: inicializa la clase BatallaDigital con parametros predefinidos
  BatallaDigital();

  //-------------------------- DESTRUCTOR ---------------------------------------

  ~BatallaDigital();

  //------------------------- METODOS -------------------------------------------



  //-------------------------- METODOS DE INICIO -------------------------------
  //intentar que los metodos queden acomodados como va el programa para una mejor lectura y entendimiento


  /*
   * post: Se inicia el "juego" BatallaDigital, con sus jugadores y el tablero correspondiente.
   * Se muestra el estado del juego. - (Por ahora como prueba de funcionamiento)
   */
   void Inicio();

   /*
  * Post: Se le pregunta al usuario cuantos jugadores van a jugar
  * 	  Se retorna la cantidad de jugadores en el juego, en un rango de 2 a 4 jugadores.
   */
   int preguntarCantidadDeJugadores();

   /*
  * Pre: Los jugadores ya debem de estar inicializados (La lista de jugadores no debe de estar vacia)
  * Post: Les agregara los soldados a cada jugador del juego
  * 	   Recorre la lista de jugadores, y por cada jugador le va agregando sus respectivos soldados.
  * 	   Basicamente agrega los soldados a cada jugador de la lista de jugadores
  * */
   void agregarSoldadosAJugadores();


   //--------------------------------------- HASTA ACA ESTAN LOS METODOS DE INICIO ---------------------------




   //--------------------------------------- METODOS DE LA PARTIDA -------------------------------------------
  /*
   * Post: Realiza las acciones que se van a realizar en un turno.
   */
   void partida();
   
   /*
    * Post: Verifica si el casillero ya puede volver a la normalidad, despues de estar inactivo o contaminado.
    *       Es decir; si el turno a desaparecer es igual o mayor que el turno actual del juego, el casillero pasa de estar CONTAMINADO o INACTIVO a ACTIVO
    * */
   void reaparecerCasillero();

   void mostrarCantidadDeSoldadosPorJugador();


//---------------------------------------- METODOS DE CAMBIO DE JUGADOR ------------------------------------


   /*
    * Post: Recorre la lista de jugadores, si encuentra el jugador al turno, entonces cambia el jugador al turno al sig jugador de la lista.
    * 	   Si el siguiente es NULL (llego al final de la lista), el jugador al turno sera el primero de la lista.
    * 	   El jugadorAlTurno se debe de cambiar cuando finaliza el turno;
    * */
   void cambiarJugadorAlTurno();

   /*
     * Pre: El jugadorAlTurno debe ser distinto de NULL
     * Post: Devuelve el jugador al turno.
     * */
    JugadorDeBatallaDigital* getJugadorAlTurno();

    /*
       * Pre: El jugadorAlTurnoNuevo debe ser distinto de NULL
       * Post: Modifica el jugador al turno.
       * */
      void setJugadorAlTurno(JugadorDeBatallaDigital* jugadorAlTurnoNuevo);

/*


  //pre:  capa inicial tiene que ser > 0 
  //      cantidadCapasMaxima no puede ser mayor que (tamanioTablero - capaInicial)
  //post: Muestra el estado del tablero al momento de invocar el metodo.
  // para futuro: implementar segun jugadorEnTurno
  void mostrarEstadoJuego(unsigned int capaInicial, int cantidadCapasMaxima);
*/


  // --------------------------------- METODOS MINA -----------------------------------

  /*
   * Pre: 
   * Post: Le pide las coordenadas de la mina al jugador, coloca la mina en el casillero, cambiando la ficha del casillero.
   * */
  void ponerMina();




// --------------------------------- SOLDADOS ----------------------------------
/* FUNCION PRIVADA
Post: Muestra los soldados (Sus ids y su posicion en el mapa) que tiene disponible el jugador al turno para mover. 
*/
void  mostrarSoldadosDisponibles();

/* FUNCION PRIVADA
Post: Recorre la lista de Fichas. Devuelve true si la id pertenece a un soldado y ademas si el jugador de la ficha le pertenece al jugadorAlTurno
*/
bool validarIdDelSoldadoAMover(int idSoldadoAValidar);

/* FUNCION PRIVADA
Post: Se le mostrara los soldados a mover al jugador, y le pedira la id del soldado que quiere mover. Si coloca una id incorrecta, le vuelve a pedir la id al usuario. 
*/
int elegirIdDelSoldadoAMover();

/* FUNCION PRIVADA
Post: Te Devuelve el casillero con la id de ficha recibida por parametro
*/
Casillero * casilleroConLaIdFicha(int idFicha);

/* FUNCION PRIVADA
Post: Le pregunta al usuario en que coordenadas del plano de la tierra quiere colocar el soldado.
	  Y mientras el usuario lo quiera colocar en el agua, se le volvera a preguntar las coordenadas.
*/
Casillero* casilleroAMoverSoldado();

/* FUNCION PUBLICA
Post: Le pide al usuario que coloque la id del soldado a mover, la coordenada del casillero a donde lo quiere mover.
	  Obtengo el casilleroViejo (Es el casillero donde estaba el soldado ANTES de moverse)
	  Obtengo el casilleroNuevo (Es el casillero donde se quiere mover el soldado)
	  Si el casilleroNuevo esta activo y ademas esta vacio, entonces el soldado se mueve. Cambiando la ficha del nuevo casillero  SOLDADO y eliminando la ficha del casillero viejo de la lista de fichas
	  Si el casilleroNuevo esta activo y ademas hay una mina O el casilleroNuevo esta contaminado, el soldado se muere, y se elimina de la lista de ficha
	  Si el casilleroNuevo esta inactivo, el soldado se queda en el casilleroViejo (No se mueve)
*/
void moverSoldado();





//---------------------------------- CARTAS ------------------------------------
  //post: de forma random elige un numero y devuelve la CARTA
  CARTA levantarCarta();

  //post: con la carta que devuelve levantarCarta la agrega al mazo
  void agregarCartaALaMano();

  //post: recorre la lista de cartas y muestra por consola las que tenga cantidad != de 0
  void mostrarCartasPorConsola();

  //post: devuelve la carta despues de preguntar al jugador cual quiere jugar
  CARTA elegirCarta();

  //pre: llama desde dentro a elegirCarta
  //post: lama a la accion de la carta
  void jugarCarta();

//-------------------------------- CARTA AVION RADAR -----------------------------------------
  /*
   * Post: Le pide las coordenadas al usuario, agrega el barco a la lista de ficha y en el jugadorActual se modifica el sejugoCartaAvion a true, para que pueda detectar las minas del avion en cada turno
   * */
  void cartaAvionRadar();

  /*
   * Post: Si el jugador jugo una carta de avion radar enconces
           Recorre el plano donde se ubican los aviones, y si el avion pertenece al jugadorAlTurno, entonces va a recorrer
           un rango de 5x5 en el plano donde se encuentran las minas, y si dectecta una mina, imprime por consola la coordenada de la mina detectada. 
   * */
  void detectarMinasPorAvion();

  /*
  * Post: Recorre el rango del radar en el plano de la tierra y verifica si hay una mina. Si hay una mina imprime por pantalla las coordenadas de las minas detectadas
  * */
  void recorrerRadarAvion(Casillero * casillero);


//-------------------------------- CARTA ATAQUE QUIMICO -----------------------------------------
  /*
   * Post: Le pide las coordenadas del ataque quimico al jugador. Hace el ataque quimico tomando la coordenada ingresada por el usuario como el centro de la contaminacion
   *       Los priemros 3 turnos 5x5x5 casilleros contaminado.
   *       Los priemros 6 turnos 3x3x3 casilleros contaminado.
   *       Los priemros 9 turnos 1x1x1 casilleros contaminado.
   * */
  void cartaAtaqueQuimico();

//-------------------------------- CARTA REPETIR TURNO -----------------------------------------
  /* Esta carta repite el turno al jugador pero sin agregar otra carta a su mano, es decir va a poder colocar una mina, y mover un soldado 
   * Post: El jugador al turno va a repetir turno.
   * */
  void cartaRepetirTurno();

//----------------------------------- CARTA BARCO ---------------------------------------------

  /*
   *  Post: Le pedira al usuario las coordenadas donde quiere colocar el barco en el agua, agregara a la lista de fichas el barco colocado
            y cambiara del jugadorAlTurno el jugoCartaBarco a true (para que pueda disparar un misil cada turno)
   * */
  void cartaBarco();

  /*
   *  Post: Si el jugador jugo la carta del barco, va a recorrer la lista de fichas y por cada barco que le pertenezca va a disparar un misil
   * */
  void disparoDelBarco();

  /*
   *  Post: Le va a pedir al usuario las coordenadas donde quiere tirar el misil, si en esas coordenadas hay un barco o un soldado, entonces lo eliminara de la
   *        lista de fichas (colocara la ficha del casillero en VACIA y el jugador en NULL)
   * */
  void dispararMisil();


//-------------------------------- CARTA ATAQUE AEREO -----------------------------------------

/* FUNCION PUBLICA
Post: REaliza la accion de la carta ataque aereo, Le pregunta al usuario las coordenadas del centro del ataque.
	    Recorre un rango den la superficie, y si en ese rango hay un soldado lo elimina.
*/
void cartaAtaqueAereo();

//-------------------------------- CARTA TRES MINAS -----------------------------------------
/*
Esta carta le da la posibilidad al jugador de colocar 3 minas mas aparte de la que lanzo en el turno
Post: Le pide las coordenadas de la mina al jugador, coloca la mina en el casillero, cambiando la ficha del casillero.
      Hace esto 3 veces.
*/
void cartaTresMinas();

//------------------------------------ METODOS GENERALES ---------------------------------------

  /*
   * Post: Devuelve true si el jugador tiene el tipo de ficha (recibido por parametro) en la lista de fichas, false si no.
   * */
  bool jugadorTieneFicha(TIPODEFICHA tipoDeFicha, JugadorDeBatallaDigital * Jugador);

  /*
   * Pre: El jugadorAlTurno debe ser distinto de NULL
   * Post: Devuelve el jugador al turno.
   * */
  int getTurno();

  /*
   * Pre: El jugadorAlTurnoNuevo debe ser distinto de NULL
   * Post: Modifica el jugador al turno.
   * */
  void setTurno(int turnoNuevo);

  Tablero* getTablero();

   Lista<Ficha*>* getFichas();

   Casillero * obtenerCasilleroEnTierra(int x, int y);

/*
Post: Elimina de la lista de fichas la ficha con la id recibida
	  y coloca la ficha que se elimino en VACIA y el jugador en NULL
*/
void eliminarFicha(int idFicha);



// ----------------------------------------------------- ESTADO DEL JUEGO ---------------------------------------------------------------
/* FUNCION PRIVADA
Post: Devuelve la cantidad de soldados que tiene el jugador recibido por parametro.
*/
int cantidadDeSoldadosDelJugador(JugadorDeBatallaDigital * jugador);

/* FUNCION PRIVADA
Post: Recorre la lista de jugadores y Elimina un jugador de la lista de jugdores si se quedo con 0 Soldados.
*/
void eliminarJugador();

/* FUNCION PUBLICA
Post: Me va a indicar si el juego se esta jugando o si ya a acabado
	  Devolvera 0 si el juego se esta jugando
	  Devolvera -1 si el juego ya se a acabado
    Si se acabo, imprime un mensaje con el jugador ganador
*/
int estadoDelJuego();

void creacionDelMapa();

// ------------------------------------ METODOS PRIVADOS ---------------------------------------
private:

  //pre: cantidadDeJugadores no puede ser menor que 2
  //post: Se inicializan los jugadores junto a sus soldados correspondientes y seteados de forma correcta en el tablero.
  //      Se agregan a la lista de jugadores del tablero
  //	  Se va a inicializar el jugadorAlTurno y sera igual al primer jugador de la lista.
  void inicializarJugadores(int cantidadDeJugadores);

  /* Pre: Los jugadores ya debem de estar inicializados (La lista de jugadores no debe de estar vacia)
   * Post: Devuelve la cantidad de soldados dependiendo del numero de jugadores que juegen.
   * 		5 soldados si juegan 2 jugadores.
   * 		7 soldados si juegan 3 o 4 jugadores.
   * */
  int cantidadDeSoldadosPorJugador();

  /*
   * Pre:
   * Post: Se inicializan los soldados del jugador que recibe por parametro.
   * 	   Se crean los 4 soldados, y los 4 soldados se
   * 	   Se los agrega a la lista de fichas.
   * */
  void inicializarSoldadosPorJugador(JugadorDeBatallaDigital* jugador);

  void coordenadasFueraDeRango(int &coordenada);
};


#endif /* BATALLADIGITAL_H_ */

