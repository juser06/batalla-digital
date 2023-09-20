#include "BatallaDigital.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>

using namespace std;

//constantes para la creacion del juego
int const MAX_NIVEL_TIERRA = 2;
int const MAX_SOLDADOS = 7;
int const MIN_SOLDADOS = 5;

//CONSTANTES RELACIONADAS CON ESTADO DEL JUEGO
int const JUGANDO = 0;
int const TERMINADO = -1;

//CONSTANTES DEL RADIO EN ATAQUE AEREO Y QUIMICO
int const RADIO_ATAQUE = 2;

//constructor
BatallaDigital::BatallaDigital()
{
  this->ventana = new Ventana();
  this->tablero = NULL;
  this->jugadores = new Lista<JugadorDeBatallaDigital*>();
  this->jugadorAlTurno = NULL;
  this->fichas = new Lista<Ficha*>();
  this->turno = 0;
  this->mapa = new Mapa();
}

//destructor
BatallaDigital::~BatallaDigital()
{
	this->jugadores->reiniciarCursor();
	while(this->jugadores->avanzarCursor()){
		delete this->jugadores->getCursor();
	}
	delete this->jugadores;

	delete this->ventana;

	delete this->tablero;

	delete this->fichas;

	delete this->mapa;

}








//------------------------------------------------------- METODOS ------------------------------------------------------------------------------------------




//------------------------------------------ METODO DE PUESTA EN MARCHA DE LA PARTIDA -----------------------


//metodo con el que arranca el juego, pregunta cantidad de jugadores, inicializa el mapa con el tamanio de segun
//los jugadores e inicia a los jugadores y sus soldados se llama desde main
void BatallaDigital::Inicio()
{
  tiposTableros tamanioMapa = INVALIDO;
  int cantidadDeJugadores = 0;
  do{
    cantidadDeJugadores = this->preguntarCantidadDeJugadores();
    switch(cantidadDeJugadores)
    {
    case 1:
      this->ventana->mostrarMensajeConsola("Para Jugar solo abri el solitario");
      break;
    case 2:
      tamanioMapa = CHICO;
      break;
    case 3:
      tamanioMapa = MEDIO;
      break;
    case 4:
      tamanioMapa = GRANDE;
      break;
    }
  } while(tamanioMapa == INVALIDO);
  this->tablero = new Tablero(tamanioMapa);
  this->mapa->crearBaseMapa(tamanioMapa);
  this->inicializarJugadores(cantidadDeJugadores);
  this->agregarSoldadosAJugadores();
}

// ---------------------------------------------------METODOS DEL INICIO----------------------------------------------------------------------

//aca van en secuencia todas las funciones que tienen que ver con el Inicio(), las ordeno en orden de como van apareciendo para que sea facil seguirlas

//post: devuelve el numero de jugadores ingresados por el jugador, despues de prguntar por consola cuantos van a ser y de comprobar que el numero es valido
int BatallaDigital::preguntarCantidadDeJugadores()
{
  this->ventana->mostrarMensajeConsola("Cuantos jugadores van a ser ?");
  int cantidadDeJugadores = this->ventana->preguntarNumero(1, 4);
  return cantidadDeJugadores;
}

//metodo privado
//pre: se le pasa el int de la cantidad de jugadores que van a jugar
//post: da de alta la cantidad de jugadores de batalla digital y los agrega a una lista de jugadores de batalla digital
//La Post-Condicion de la funcion "inicializarJugadores" le aggregue que se va a inicializar el jugadorAlTurno
void BatallaDigital::inicializarJugadores(int cantidadDeJugadores)
{
	for (int x = 0; x < cantidadDeJugadores; x++)
	{
		JugadorDeBatallaDigital * jugador = new JugadorDeBatallaDigital();
		this->jugadores->add(jugador);
		ventana->mostrarMensajeConsola(jugador->getJugador()->getNombre() + " Creado");
		if(x==0)
		{
			this->jugadorAlTurno = jugador;
		}
	}
}

//metodo privado
//post:recorre la lista de los jugadores de batalla digital inicializando los soldados
void BatallaDigital::agregarSoldadosAJugadores()
{
	this->jugadores->reiniciarCursor();
	while(this->jugadores->avanzarCursor())
	{
		JugadorDeBatallaDigital* jugador = this->jugadores->getCursor();
		inicializarSoldadosPorJugador(jugador);
	}
}


//pre:toma al jugador al turno, este tiene que ser valido y != NULL
//post: con el jugador al turno va pidiendo las coordenadas donde quiere poner sus soldados y se va dando de alta un soldado con esas coordenadas, despues se agrega esa ficha a la lista de fichas.
void BatallaDigital::inicializarSoldadosPorJugador(JugadorDeBatallaDigital* jugador)
{
	if(!jugador)
	{
		throw "Jugador nulo";
	}
	int x = -1;
	int y = -1;
	int z = MAX_NIVEL_TIERRA;
	int contador = 0;
	int cantidadDeSoldados = this->cantidadDeSoldadosPorJugador();
	Casillero *casillero = NULL;
	while(contador < cantidadDeSoldados)
	{
		this->ventana->mostrarMensajeConsola(jugador->getJugador()->getNombre());
		do
		{

			this->ventana->mostrarMensajeConsola("Ingrese la coordenada X del soldado.");
			x = ventana->preguntarNumero(1,this->tablero->getTamanio()) - 1;
			this->ventana->mostrarMensajeConsola("Ingrese la coordenada Y del soldado.");
			y = ventana->preguntarNumero(1,this->tablero->getTamanio()) - 1;
			casillero = this->tablero->getCasilleroEnCoordenadas(x, y, MAX_NIVEL_TIERRA);
			if (casillero->getTipoDeCasillero() == AGUA || casillero->getFicha()->getTipoDeFicha() == SOLDADO)
			{
				this->ventana->mostrarMensajeConsola("casillero invalido");
			}
		}while((casillero->getTipoDeCasillero() == AGUA || casillero->getFicha()->getTipoDeFicha() == SOLDADO));
		this->ventana->mostrarMensajeConsola("Soldado desplegado");
		Ficha* ficha = this->tablero->getCasilleroEnCoordenadas(x, y, z)->getFicha();
		ficha->setFicha(SOLDADO, jugador);
		this->fichas->add(ficha);
		contador++;
	}
}

//metodo privado
/* Pre: Los jugadores ya debem de estar inicializados (La lista de jugadores no debe de estar vacia)
  * Post: Devuelve la cantidad de soldados dependiendo del numero de jugadores que juegen.
  * 		5 soldados si juegan 2 jugadores.
  * 		7 soldados si juegan 3 o 4 jugadores.
  * */
int BatallaDigital::cantidadDeSoldadosPorJugador()
{
	int cantidadDeJugadores = this->jugadores->contarElementos();
	if(cantidadDeJugadores == 2){
		return MIN_SOLDADOS;
	} else{
		return MAX_SOLDADOS;
	}
}

//--------------------------- HASTA ACA ESTAN LOS METODOS DE INICIO -----------------------------








//------------------------------------ PARTIDA --------------------------------------------------
void BatallaDigital::partida()
{
	do
	{
		string mensaje = "Turno del " + this->jugadorAlTurno->getJugador()->getNombre();
		ventana->mostrarMensajeConsola(mensaje);
		if (this->jugadorAlTurno->getJugador()->getID() == 1)
		{
			this->turno += 1;
		}
		this->mostrarCantidadDeSoldadosPorJugador();
		//this->ventana->mostrarMensajeConsola("antes de reaparecerCasillero()");
		this->reaparecerCasillero();
		//this->ventana->mostrarMensajeConsola("antes de agregarCartaALaMano()");
		this->agregarCartaALaMano();
		//this->ventana->mostrarMensajeConsola("antes de detectarMinasPorAvion()");				
		this->detectarMinasPorAvion();//<----ACA VE SI EL JUGADOR YA USO LA CARTA AVION RADAR Y TIENE UN AVION RADAR EL LA LISTA DE FICHAS, ENTONCES; RECORRER EL RANGO DEL AVION RADAR PARA QUE RADEE OTRA VEZ LA ZONA A VER SI HAY NUEVAS MINAS
		//this->ventana->mostrarMensajeConsola("antes de ponerMina()");
		this->ponerMina();
		this->ventana->mostrarMensajeConsola("despues de poner mina:");
		this->mostrarCantidadDeSoldadosPorJugador();
		//this->ventana->mostrarMensajeConsola("antes de preguntarMoverSoldado()");						
		this->disparoDelBarco();//<----ACA VE SI EL JUGADOR YA USO LA CARTA BARCO Y SI TIENE UN BARCO EN LA LISTA DE FICHAS, ENTONCES; VA A TENER Q DISPARAR
		if(ventana->PreguntaSiONo("Soldado"))
		{
			this->moverSoldado();						
		}
		//this->ventana->mostrarMensajeConsola("antes de preguntarJugarCarta()");	
		if(ventana->PreguntaSiONo("Carta"))
		{
			this->jugarCarta();							
		}
		this->creacionDelMapa();
		//this->ventana->mostrarMensajeConsola("antes de this->cambiarJugadorAlTurno()");
		this->cambiarJugadorAlTurno();
	}while(this->estadoDelJuego() == JUGANDO);
}

//METODOS DE PARTIDA
void BatallaDigital::mostrarCantidadDeSoldadosPorJugador()
{
	this->jugadores->reiniciarCursor();
	while(this->jugadores->avanzarCursor())
	{
		this->ventana->mostrarMensajeConsolaConNumero("Cantidad de soldados del jugador con la id: ", this->jugadores->getCursor()->getJugador()->getID());
		this->ventana->mostrarMensajeConsolaConNumero("",this->cantidadDeSoldadosDelJugador(this->jugadores->getCursor()));
	}
}

void BatallaDigital::reaparecerCasillero()
{
	for(int x = 0; x<this->tablero->getTamanio(); x++)
	{
		for(int y = 0; y<this->tablero->getTamanio(); y++)
		{
			for(int z = MAX_NIVEL_TIERRA-RADIO_ATAQUE; z<=MAX_NIVEL_TIERRA+RADIO_ATAQUE; z++)
			{
				Casillero * casillero = this->tablero->getCasilleroEnCoordenadas(x,y,z);
				if (casillero->getTurnoAActivarse() != TURNO_NO_USADO && casillero->getTurnoAActivarse() >= this->turno)
				{
					casillero->setEstado(ACTIVO);
				}
			}
		}
	}
}





//---------------------------------------------- METODOS DE CAMBIO DE JUGADOR -------------------------------------------------------


void BatallaDigital::setJugadorAlTurno(JugadorDeBatallaDigital* jugadorAlTurnoNuevo)
{
  this->jugadorAlTurno = jugadorAlTurnoNuevo;
}

void BatallaDigital::cambiarJugadorAlTurno()
{
	this->jugadores->reiniciarCursor();
	while(this->jugadores->avanzarCursor())
	{

		if(this->jugadores->getCursor()->getJugador()->getID() == this->jugadorAlTurno->getJugador()->getID())
		{

			if(this->jugadores->avanzarCursor())
			{	//El cursor es distinto de NULL
				setJugadorAlTurno(this->jugadores->getCursor());
			}
			else
			{	//El cursor es igual a NULL, es decir, llegue a final de la lista. Ahora el jugador es el primero de la lista.
				this->jugadores->reiniciarCursor();
				this->jugadores->avanzarCursor();
				setJugadorAlTurno(this->jugadores->getCursor());
			}
		}
	}
}

JugadorDeBatallaDigital* BatallaDigital::getJugadorAlTurno(){
  return this->jugadorAlTurno;
}


//-------------------------------------------------- METODOS DE LA MINA ---------------------------------------------------------------
void BatallaDigital::ponerMina()
{
	Casillero *casillero = NULL;
	do
	{
		ventana->mostrarMensajeConsola("Donde queres poner la mina ?");
		int x = ventana->preguntarNumero(1,this->tablero->getTamanio()) - 1;
		int y = ventana->preguntarNumero(1,this->tablero->getTamanio()) - 1;
		casillero = this->tablero->getCasilleroEnCoordenadas(x, y, MAX_NIVEL_TIERRA);
		if (casillero->getTipoDeCasillero() == AGUA)
		{
			ventana->mostrarMensajeConsola("Eso es agua, si la polvora se moja no sirve");
			ventana->mostrarMensajeConsola("Por favor elegir otro par de coordenadas");
		}
	}while(casillero->getTipoDeCasillero() == AGUA);

	Ficha* ficha = casillero->getFicha();
	  if(ficha->getTipoDeFicha() == VACIA)
	  {
		  ficha->setFicha(MINA, this->jugadorAlTurno);
		  this->fichas->add(ficha);	//Agg la ficha mina a la lista de fichas
	  }
	  else if(ficha->getTipoDeFicha() == SOLDADO)
	  {
		this->ventana->mostrarMensajeConsola("LE DIO A UN SOLDADO");
		  ficha->setFicha(MINA, this->jugadorAlTurno);
		  casillero->setEstado(INACTIVO);
		  srand(time(NULL));
		  int random = rand() % 6 + 3; //4 tipos de minas
		  casillero->setTurnoAActivarse(this->turno+random);
	  }
}

string intToString(int numero){
	ostringstream oss;
	oss << numero;
	return oss.str();
}

// ----------------------------------------------------- METODOS DEL SOLDADO ---------------------------------------------------------------
/*FUNCION PRIVADA
Post: Muestra los soldados (Sus ids y su posicion en el mapa) que tiene disponible el jugador al turno para mover. 
*/
void  BatallaDigital::mostrarSoldadosDisponibles()
{
	this->ventana->mostrarMensajeConsola("Soldados Disponibles");
	Casillero * casilleroTierra;
	for(int x = 0; x < this->tablero->getTamanio(); x++)
	{
		for(int y = 0; y < this->tablero->getTamanio(); y++)
		{
			casilleroTierra = obtenerCasilleroEnTierra(x,y);

			if (casilleroTierra->getFicha()->getTipoDeFicha() != VACIA && (casilleroTierra->getFicha()->getJugadorDeBatallaDigital()->getJugador()->getID() == this->jugadorAlTurno->getJugador()->getID()) &&
					(casilleroTierra->getFicha()->getTipoDeFicha() == SOLDADO ))
			{
				int idSoldado = casilleroTierra->getFicha()->getIdFicha();
				string id = intToString(idSoldado);
				string coodenadaX = intToString(x+1);
				string coodenadaY = intToString(y+1);
				string mensaje = "Soldado ID: " + id +  " Posicion en x: " +coodenadaX + ". Posicion en Y: " + coodenadaY+ "." ;
				ventana->mostrarMensajeConsola(mensaje);
			}
		}
	}
}

/*FUNCION PRIVADA
Post: Recorre la lista de Fichas. Devuelve true si la id pertenece a un soldado y ademas si el jugador de la ficha le pertenece al jugadorAlTurno
*/
bool BatallaDigital::validarIdDelSoldadoAMover(int idSoldadoAValidar)
{
	bool esValido = false;
	this->fichas->reiniciarCursor();
	while(this->fichas->avanzarCursor() && !esValido)
	{
		Ficha * ficha = this->fichas->getCursor();
		if(ficha->getIdFicha() == idSoldadoAValidar && ficha->getTipoDeFicha() == SOLDADO && 
		   ficha->getJugadorDeBatallaDigital()->getJugador()->getID() == this->jugadorAlTurno->getJugador()->getID()){
			esValido = true;
		}
	}
	return esValido;
}

/*FUNCION PRIVADA
Post: Se le mostrara los soldados a mover al jugador, y le pedira la id del soldado que quiere mover. Si coloca una id incorrecta, le vuelve a pedir la id al usuario. 
*/
int BatallaDigital::elegirIdDelSoldadoAMover()
{
	this->mostrarSoldadosDisponibles();
	ventana->mostrarMensajeConsola("Ingresa el ID del soldado que queres mover:");
	int idSoldadoAMover = this->ventana->preguntarNumero(1, this->fichas->get(1)->GetIdUltimaFicha());
	while(!this->validarIdDelSoldadoAMover(idSoldadoAMover))
	{
		this->ventana->mostrarMensajeConsola("La id que ingreso no corresponde a un soldado en su poder. Porfavor ingrese denuevo");
		this->mostrarSoldadosDisponibles();
		idSoldadoAMover = this->ventana->preguntarNumero(1, this->fichas->contarElementos());
	}
	return idSoldadoAMover;
}

/*FUNCION PRIVADA
Post: Te Devuelve el casillero con la id de ficha recibida por parametro
*/
Casillero * BatallaDigital::casilleroConLaIdFicha(int idFicha)
{
	Casillero* casillero = NULL;
	bool encontrado = false;
	int x = 0;
	int y = 0;
	while(x < this->tablero->getTamanio() && !encontrado){
		while(y < this->tablero->getTamanio() && !encontrado){
			casillero = this->tablero->getCasilleroEnCoordenadas(x, y, MAX_NIVEL_TIERRA);
			if(casillero->getFicha()->getIdFicha() == idFicha){
				encontrado = true;
			}
			y++;
		}
		x++;
	}
	return casillero;
}

/*FUNCION PRIVADA
Post: Le pregunta al usuario en que coordenadas del plano de la tierra quiere colocar el soldado.
	  Y mientras el usuario lo quiera colocar en el agua, se le volvera a preguntar las coordenadas.
*/
Casillero* BatallaDigital::casilleroAMoverSoldado()
{
	this->ventana->mostrarMensajeConsola("Coloque la coordenada X donde quiera mover al soldado.");
	int x = ventana->preguntarNumero(1,this->tablero->getTamanio()) - 1;
	this->ventana->mostrarMensajeConsola("Coloque la coordenada Y donde quiera mover al soldado.");
	int y = ventana->preguntarNumero(1,this->tablero->getTamanio()) - 1;
	Casillero * casilleroEnTierra = this->obtenerCasilleroEnTierra(x,y);
	while(casilleroEnTierra->getTipoDeCasillero() == AGUA || casilleroEnTierra->getEstado() == INACTIVO)
	{
		this->ventana->mostrarMensajeConsola("No se puede colocar soldados en el agua ni en un lugar inactivo.");
		this->ventana->mostrarMensajeConsola("Porfavor coloque el soldado en tierra y en un lugar activo.");
		this->ventana->mostrarMensajeConsola("Coloque la coordenada X donde quiera mover al soldado.");
		int x = ventana->preguntarNumero(1,this->tablero->getTamanio()) - 1;
		this->ventana->mostrarMensajeConsola("Coloque la coordenada Y donde quiera mover al soldado.");
		int y = ventana->preguntarNumero(1,this->tablero->getTamanio()) - 1;
		casilleroEnTierra = this->obtenerCasilleroEnTierra(x,y);
	}
	return casilleroEnTierra;
}

/* FUNCION PUBLICA
Post: Le pide al usuario que coloque la id del soldado a mover, la coordenada del casillero a donde lo quiere mover.
	  Obtengo el casilleroViejo (Es el casillero donde estaba el soldado ANTES de moverse)
	  Obtengo el casilleroNuevo (Es el casillero donde se quiere mover el soldado)
	  Si el casilleroNuevo esta activo y ademas esta vacio, entonces el soldado se mueve. Cambiando la ficha del nuevo casillero  SOLDADO y eliminando la ficha del casillero viejo de la lista de fichas
	  Si el casilleroNuevo esta activo y ademas hay una mina O el casilleroNuevo esta contaminado, el soldado se muere, y se elimina de la lista de ficha
	  Si el casilleroNuevo esta inactivo, el soldado se queda en el casilleroViejo (No se mueve)
*/
void BatallaDigital::moverSoldado(){
	int idSoldadoAMover = this->elegirIdDelSoldadoAMover();
	Casillero* casilleroViejo = casilleroConLaIdFicha(idSoldadoAMover);
	Casillero * casilleroNuevo = this->casilleroAMoverSoldado();

	if(casilleroNuevo->getFicha()->getTipoDeFicha() == VACIA && casilleroNuevo->getEstado() == ACTIVO){
		this->eliminarFicha(idSoldadoAMover);
		casilleroNuevo->getFicha()->setFicha(SOLDADO, jugadorAlTurno);
		this->fichas->add(casilleroNuevo->getFicha());
	}
	else if((casilleroNuevo->getFicha()->getTipoDeFicha() == MINA && casilleroNuevo->getEstado() == ACTIVO)){
		this->eliminarFicha(idSoldadoAMover);
		this->eliminarFicha(casilleroNuevo->getFicha()->getIdFicha());
		casilleroNuevo->setEstado(INACTIVO);
	}
	else if(casilleroNuevo->getEstado() == CONTAMINADO){
		this->eliminarFicha(idSoldadoAMover);
	}
}


// -------------------------------------------------- CARTAS  --------------------------------------------------------------

CARTA BatallaDigital::levantarCarta()
{
	CARTA cartaLevantada = REPITETURNO;
	srand(time(NULL));
	int random = 1 + rand() % (90 - 1) ;
	if (random >= 1 && random <= 15)
	{
		cartaLevantada = TRESMINAS;
	}
	else if (random > 15 && random <= 30)
	{
		cartaLevantada = REPITETURNO;
	}
	else if (random > 30 && random <= 45)
	{
		cartaLevantada = ATAQUEAEREO;
	}
	else if (random > 45 && random <= 60)
	{
		cartaLevantada = CARTABARCO;
	}
	else if (random > 60 && random <= 75)
	{
		cartaLevantada = AVIONRADAR;
	}
	else if (random > 75 && random <= 90)
	{
		cartaLevantada = ATAQUEQUIMICO;
	}
	return cartaLevantada;
}

void BatallaDigital::agregarCartaALaMano()
{
	CARTA cartaAAgregar = levantarCarta();
	this->jugadorAlTurno->getListaDeCartas()->reiniciarCursor();
	while(this->jugadorAlTurno->getListaDeCartas()->avanzarCursor())
	{
		Cartas * carta = this->jugadorAlTurno->getListaDeCartas()->getCursor();
		if (carta->getCarta() == cartaAAgregar)
		{
			carta->setCantidad(1);
		}
	}

}

void BatallaDigital::mostrarCartasPorConsola()
{
	ventana->mostrarMensajeConsola("Estas son las cartas que tenes en la mano");
	this->jugadorAlTurno->getListaDeCartas()->reiniciarCursor();
		while(this->jugadorAlTurno->getListaDeCartas()->avanzarCursor())
		{
			Cartas * carta = this->jugadorAlTurno->getListaDeCartas()->getCursor();
			if (carta->getCantidad() != 0)
			{
				this->ventana->mostrarCartas(carta);
			}
		}
}

//me olvide de poner el mensaje si la carta elegida no es correcta
CARTA BatallaDigital::elegirCarta()
{
	CARTA cartaElegida = REPITETURNO;
	bool salida = false;
	mostrarCartasPorConsola();
	do
	{
	ventana->mostrarMensajeConsola("Elegi el numero de carta que quieras jugar");
	CARTA eleccionDeCarta = static_cast<CARTA>(ventana->preguntarNumero(1,6) - 1);
	this->jugadorAlTurno->getListaDeCartas()->reiniciarCursor();
		while(this->jugadorAlTurno->getListaDeCartas()->avanzarCursor())
		{
			Cartas * carta = this->jugadorAlTurno->getListaDeCartas()->getCursor();
			if (carta->getCarta() == eleccionDeCarta && carta->getCantidad() != 0)
			{
				cartaElegida = carta->getCarta();
				carta->setCantidad(-1);
				salida = true;
			}
		}
		if (salida == false)
		{
			ventana->mostrarMensajeConsola("carta invalida");
		}
	}while(salida == false);
	return cartaElegida;
}

void BatallaDigital::jugarCarta()
{
	CARTA cartaElegida = elegirCarta();
	switch(cartaElegida)
	{
	case 0:
		cartaAtaqueQuimico();
		break;
	case 1:
		cartaAvionRadar();
		break;
	case 2:
		cartaBarco();
		break;
	case 3:
		cartaAtaqueAereo();
		break;
	case 4:
		cartaRepetirTurno();
		break;
	case 5:
		cartaTresMinas();
		break;
	default:
		throw "no encontro carta";
	}
}

//-------------------------------- CARTA AVION RADAR -----------------------------------------
int const POSICION_Z_AVION_RADAR = 4;

/*
 * Post: Recorre el rango del radar en el plano de la tierra y verifica si hay una mina. Si hay una mina imprime por pantalla las coordenadas de las minas detectadas
 * */
void BatallaDigital::recorrerRadarAvion(Casillero * casillero){
	for(int i = casillero->getCoordenadaX()-RADIO_ATAQUE; i<=casillero->getCoordenadaX()+RADIO_ATAQUE; i++)
	{
		for(int j = casillero->getCoordenadaY()-RADIO_ATAQUE; j<=casillero->getCoordenadaY()+RADIO_ATAQUE; j++)
		{
			coordenadasFueraDeRango(i);
			coordenadasFueraDeRango(j);
			Casillero * casilleroAux = this->tablero->getCasilleroEnCoordenadas(i,j,MAX_NIVEL_TIERRA);
			if(casilleroAux->getFicha()->getTipoDeFicha() == MINA)
			{
				this->ventana->mostrarMensajeConsola("Se detecto una mina en: ");
				this->ventana->mostrarMensajeConsolaConNumero("X=", i+1);
				this->ventana->mostrarMensajeConsolaConNumero("Y=", j+1);
			}
		}
	}
}



void BatallaDigital::detectarMinasPorAvion(){
	if(this->jugadorTieneFicha(AVION, this->jugadorAlTurno) && this->jugadorAlTurno->getJugoCartaAvionRadar()){
		for(int x = 0; x<this->tablero->getTamanio(); x++){
			for(int y = 0; y<this->tablero->getTamanio(); y++){
				Casillero * casillero = this->tablero->getCasilleroEnCoordenadas(x,y,POSICION_Z_AVION_RADAR);
				if(casillero->getFicha()->getTipoDeFicha() == AVION && 
				   casillero->getFicha()->getJugadorDeBatallaDigital() == this->jugadorAlTurno){
					recorrerRadarAvion(casillero);
				}
			}	
		}
	}
}

void BatallaDigital::cartaAvionRadar(){
	this->ventana->mostrarMensajeConsola("Coloque la coordenada X del avion radar.");
	int x = this->ventana->preguntarNumero(1, this->tablero->getTamanio()) - 1;
	this->ventana->mostrarMensajeConsola("Coloque la coordenada Y del avion radar.");
	int y = this->ventana->preguntarNumero(1, this->tablero->getTamanio()) - 1;
	
	Casillero* casillero = this->tablero->getCasilleroEnCoordenadas(x,y,POSICION_Z_AVION_RADAR);
	Ficha * ficha = casillero->getFicha();
	ficha->setFicha(AVION, this->jugadorAlTurno);
	this->fichas->add(ficha);
	this->jugadorAlTurno->setJugoCartaAvionRadar();
}

//-------------------------------- CARTA ATAQUE QUIMICO -----------------------------------------
void BatallaDigital::cartaAtaqueQuimico(){
	this->ventana->mostrarMensajeConsola("Coloque la coordenada X del centro del ataque quimico.");
	int x = this->ventana->preguntarNumero(1, this->tablero->getTamanio()) - 1;
	this->ventana->mostrarMensajeConsola("Coloque la coordenada Y del centro del ataque quimico.");
	int y = this->ventana->preguntarNumero(1, this->tablero->getTamanio()) - 1;
	int z = MAX_NIVEL_TIERRA;
	
	for(int i = x-RADIO_ATAQUE; i<=x+RADIO_ATAQUE; i++)
	{
		for(int j = y-RADIO_ATAQUE; j<=y+RADIO_ATAQUE; j++)
		{
			for(int k = z-RADIO_ATAQUE; k<=z+RADIO_ATAQUE; k++)
			{
				coordenadasFueraDeRango(i);
				coordenadasFueraDeRango(j);
				coordenadasFueraDeRango(k);
				Casillero* casillero = this->tablero->getCasilleroEnCoordenadas(i,j,k);
				casillero->setEstado(CONTAMINADO);
				if( i == x-RADIO_ATAQUE || j == y-RADIO_ATAQUE || k == y-RADIO_ATAQUE ||
					i == x+RADIO_ATAQUE || j == y+RADIO_ATAQUE || k == y+RADIO_ATAQUE){
						casillero->setTurnoAActivarse(this->turno+3);
				}
				else if( i == x-RADIO_ATAQUE+1 || j == y-RADIO_ATAQUE+1 || k == y-RADIO_ATAQUE+1 ||
					i == x+RADIO_ATAQUE+1 || j == y+RADIO_ATAQUE+1 || k == y+RADIO_ATAQUE+1){
						casillero->setTurnoAActivarse(this->turno+6);
				}
				else if( i == RADIO_ATAQUE || j == RADIO_ATAQUE || k == RADIO_ATAQUE){
						casillero->setTurnoAActivarse(this->turno+9);
				}
				//MATAR SOLDADO O ELIMINAR AVION
				if(casillero->getFicha()->getTipoDeFicha() == SOLDADO || casillero->getFicha()->getTipoDeFicha() == AVION){
					this->eliminarFicha(casillero->getFicha()->getIdFicha());

				}
			}
		}
	}
}

//-------------------------------- CARTA REPETIR TURNO -----------------------------------------
void BatallaDigital::cartaRepetirTurno(){
		this->detectarMinasPorAvion();
		this->ponerMina();							
		this->disparoDelBarco();
		if(ventana->PreguntaSiONo("Soldado"))
		{
			this->moverSoldado();						
		}
}

//-------------------------------- CARTA TRES MINAS -----------------------------------------
void BatallaDigital::cartaTresMinas(){
	for(int i = 0; i < 3; i++){
		this->ponerMina();
	}
}

//-------------------------------- CARTA BARCO -----------------------------------------
void BatallaDigital::cartaBarco()
{
	this->ventana->mostrarMensajeConsola("Ingrese las coordenadas para colocar el barco:");
	Casillero *casillero = NULL;
	do
	{
		int x = ventana->preguntarNumero(1,this->tablero->getTamanio()) - 1;
		int y = ventana->preguntarNumero(1,this->tablero->getTamanio()) - 1;
		casillero = this->tablero->getCasilleroEnCoordenadas(x, y, MAX_NIVEL_TIERRA);
		if (casillero->getTipoDeCasillero() == TIERRA)
		{
			ventana->mostrarMensajeConsola("Eso es tierra, y veo dificil que un barco flote ahi.");
			ventana->mostrarMensajeConsola("Por favor elegir otro par de coordenadas");
		}
	}while(casillero->getTipoDeCasillero() == TIERRA);
	casillero->getFicha()->setFicha(BARCO, jugadorAlTurno);
	this->fichas->add(casillero->getFicha());
	this->jugadorAlTurno->setJugoCartaBarco();
}

void BatallaDigital::dispararMisil(){
	this->ventana->mostrarMensajeConsola("Coloque la coordenada X del misil del barco.");
	int x = this->ventana->preguntarNumero(1, this->tablero->getTamanio()) - 1;
	this->ventana->mostrarMensajeConsola("Coloque la coordenada Y del misil del barco.");
	int y = this->ventana->preguntarNumero(1, this->tablero->getTamanio()) - 1;
	
	Casillero* casillero = this->tablero->getCasilleroEnCoordenadas(x,y,MAX_NIVEL_TIERRA);
	Ficha* ficha = casillero->getFicha();
	if(ficha->getTipoDeFicha() == SOLDADO || ficha->getTipoDeFicha() == BARCO){
		this->eliminarFicha(ficha->getIdFicha());
	}
}

void BatallaDigital::disparoDelBarco(){
	if(this->jugadorAlTurno->getJugoCartaBarco()){
		this->fichas->reiniciarCursor();
		while(this->fichas->avanzarCursor()){
			Ficha* ficha = this->fichas->getCursor();
			if(ficha->getTipoDeFicha() == BARCO && ficha->getJugadorDeBatallaDigital() == this->jugadorAlTurno){
				this->dispararMisil();
			}
		}
	}
}

//-------------------------------- CARTA ATAQUE AEREO -----------------------------------------
/*
Post: REaliza la accion de la carta ataque aereo, Le pregunta al usuario las coordenadas del centro del ataque.
	  Recorre un rango den la superficie, y si en ese rango hay un soldado lo elimina.
*/
void BatallaDigital::cartaAtaqueAereo()
{
	this->ventana->mostrarMensajeConsola("Ingrese las coordenadas central X del ataque: ");
	int x = ventana->preguntarNumero(1,this->tablero->getTamanio()) - 1;
	this->ventana->mostrarMensajeConsola("Ingrese las coordenadas central Y del ataque: ");
	int y = ventana->preguntarNumero(1,this->tablero->getTamanio()) - 1;

	int xMax = x + RADIO_ATAQUE;
	int yMax = y + RADIO_ATAQUE;
	x = x - RADIO_ATAQUE;
	y = y - RADIO_ATAQUE;
	coordenadasFueraDeRango(x);
	coordenadasFueraDeRango(y);
	for (int i = x; i <= xMax; i++)
	{
		for(int j = y; j <= yMax; j++)
		{
			Casillero * casillero = this->obtenerCasilleroEnTierra(i,j);
			if(casillero->getFicha()->getTipoDeFicha() == SOLDADO){
				int idSoldadoAEliminar = casillero->getFicha()->getIdFicha();
				this->eliminarFicha(idSoldadoAEliminar);
			}
		}
	}
}


// ----------------------------------------------------- ESTADO DEL JUEGO ---------------------------------------------------------------
/*
 * FUNCION PRIVADA
 * Post: Devuelve la cantidad de soldados que tiene el jugador recibido por parametro.
*/
int  BatallaDigital::cantidadDeSoldadosDelJugador(JugadorDeBatallaDigital* jugador)
{
	int cantidad = 0;
	Casillero * casilleroTierra;
	for(int x = 0; x < this->tablero->getTamanio(); x++)
	{
		for(int y = 0; y < this->tablero->getTamanio(); y++)
		{
			casilleroTierra = obtenerCasilleroEnTierra(x,y);
			if (casilleroTierra->getFicha()->getTipoDeFicha() != VACIA && (casilleroTierra->getFicha()->getJugadorDeBatallaDigital()->getJugador()->getID() == jugador->getJugador()->getID()) &&
			(casilleroTierra->getFicha()->getTipoDeFicha() == SOLDADO ))
			{
				cantidad++;
			}
		}
	}
	return cantidad;
}

/* FUNCION PRIVADA
Post: Recorre la lista de jugadores y Elimina un jugador de la lista de jugdores si se quedo con 0 Soldados.
*/
void BatallaDigital::eliminarJugador()
{
	int posicion = 1;
	this->jugadores->reiniciarCursor();
	while(this->jugadores->avanzarCursor())
	{
		JugadorDeBatallaDigital* jugador = this->jugadores->getCursor();
		if(this->cantidadDeSoldadosDelJugador(jugador) == 0){
			delete jugador;
			this->jugadores->remover(posicion);
		}
		posicion++;
	}
}

/* FUNCION PUBLICA
Post: Me va a indicar si el juego se esta jugando o si ya a acabado
	  Devolvera 0 si el juego se esta jugando
	  Devolvera -1 si el juego ya se a acabado
	  Si se acabo, imprime un mensaje con el jugador ganador
*/
int BatallaDigital::estadoDelJuego(){
	this->eliminarJugador();
	int estado = JUGANDO;
	int cantidadDeJugadoresJugando = this->jugadores->contarElementos();
	if(cantidadDeJugadoresJugando == 1){
		JugadorDeBatallaDigital* jugadorGanador = this->jugadores->get(1); //Te devuelve el unico jugador de la lista, que esta en la posicion 0.
		string id = intToString(jugadorGanador->getJugador()->getID());
		this->ventana->mostrarMensajeConsola("El jugador con la ID "+ id + " HA GANADO.");
		estado = TERMINADO;
	}

	return estado;
}


// ---------------------------------------------------------- METODOS GENERALES ----------------------------------------------------------
/*
 * Post: Devuelve true si el jugador tiene el tipo de ficha (recibido por parametro) en la lista de fichas, false si no.
 * */
bool BatallaDigital::jugadorTieneFicha(TIPODEFICHA tipoDeFicha, JugadorDeBatallaDigital * jugador){
	this->fichas->reiniciarCursor();
	bool siTiene = false;
	while(this->fichas->avanzarCursor() && !siTiene){
		Ficha* ficha = this->fichas->getCursor();
		if(ficha->getTipoDeFicha() == tipoDeFicha && ficha->getJugadorDeBatallaDigital() == jugador){
			siTiene = true;
		}
	}
	return siTiene;
}

int BatallaDigital::getTurno()
{
  return this->turno;
}

void BatallaDigital::setTurno(int turnoNuevo)
{
  this->turno = turnoNuevo;
}

Tablero* BatallaDigital::getTablero()
{
	return this->tablero;
}

Lista<Ficha*>* BatallaDigital::getFichas()
{
	return this->fichas;
}

Casillero * BatallaDigital::obtenerCasilleroEnTierra(int x, int y)
{
	Casillero * casilleroTierra = NULL;
	casilleroTierra = this->tablero->getCasilleroEnCoordenadas(x,y,MAX_NIVEL_TIERRA);
	return casilleroTierra;
}

/*
Post: Elimina de la lista de fichas la ficha con la id recibida
	  y coloca la ficha que se elimino en VACIA y el jugador en NULL
*/
void BatallaDigital::eliminarFicha(int idFicha){
	this->fichas->reiniciarCursor();
	int posicion = 0;
	while(this->fichas->avanzarCursor()){
		Ficha* ficha = this->fichas->getCursor();
		if(ficha->getIdFicha() == idFicha){
			fichas->remover(posicion);
			ficha->setFicha(VACIA, NULL);
		}
		posicion++;
	}
}

void BatallaDigital::coordenadasFueraDeRango(int &coordenada)
{
	if (coordenada < 0)
	{
		coordenada = 0;
	}
	if (coordenada > this->tablero->getTamanio() - 1)
	{
		coordenada = this->tablero->getTamanio() - 1;
	}
}

void BatallaDigital::creacionDelMapa()
{
	Casillero * casillero = NULL;
	this->mapa->limpiarMapa();
	for(int x = 0; x < this->tablero->getTamanio();x++)
	{
		for(int y = 0; y < this->tablero->getTamanio(); y++)
		{
			casillero = this->tablero->getCasilleroEnCoordenadas(x, y, 2);
			this->mapa->mapa(casillero, this->jugadorAlTurno);
		}
	}
	this->mapa->imprimirMapa(this->jugadorAlTurno);
}


