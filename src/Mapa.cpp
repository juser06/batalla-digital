/*
 * Mapa.cpp
 *
 *  Created on: Jun 15, 2023
 *      Author: user
 */

#include "Mapa.h"

Mapa::Mapa()
{
	this->base = new BMP();
	this->imagenCasillero = new BMP();
	this->mapaGenerado = new BMP();
}

Mapa::~Mapa() {
	delete this->base;
	delete this->imagenCasillero;
	delete this->mapaGenerado;
}

void Mapa::crearBaseMapa(int tamanio)
{
	this->base->SetSize(tamanio*64,tamanio*64);
	for (int x = 0; x < tamanio; x++)
	{
		for (int y = 0; y < tamanio; y++)
		{
			if (x <= tamanio - ((tamanio / 4) + 1))
			{
				imagenCasillero->ReadFromFile("../tileset/tierra.bmp");
				RangedPixelToPixelCopy(*imagenCasillero,0,imagenCasillero->TellWidth()-1,imagenCasillero->TellHeight()-1,0
						,*base,x*64,y*64);
			}
			else
			{
				imagenCasillero->ReadFromFile("../tileset/agua.bmp");
				RangedPixelToPixelCopy(*imagenCasillero,0,imagenCasillero->TellWidth()-1,imagenCasillero->TellHeight()-1,0
						,*base,x*64,y*64);
			}
		}
	}
	this->base->WriteToFile("../tileset/MapaBase.bmp");
}

void Mapa::limpiarMapa()
{
	this->mapaGenerado->ReadFromFile("../tileset/MapaBase.bmp");
}


void Mapa::imprimirMapa(JugadorDeBatallaDigital * jugador)
{
	if(jugador->getJugador()->getID() == 1)
	{
		mapaGenerado->WriteToFile("Mapa_Jugador_1.bmp");
	}
	else if(jugador->getJugador()->getID() == 2)
	{
		mapaGenerado->WriteToFile("Mapa_Jugador_2.bmp");
	}
	else if(jugador->getJugador()->getID() == 3)
	{
		mapaGenerado->WriteToFile("Mapa_Jugador_3.bmp");
	}
	else if(jugador->getJugador()->getID() == 4)
	{
		mapaGenerado->WriteToFile("Mapa_Jugador_4.bmp");
	}
}

void Mapa::mapa(Casillero * casillero, JugadorDeBatallaDigital * jugador)
{
	if (casillero->getFicha()->getTipoDeFicha() == VACIA && casillero->getEstado() == INACTIVO)
	{
		imagenCasillero->ReadFromFile("../tileset/inactivo.bmp");
		RangedPixelToPixelCopy(*imagenCasillero,0,imagenCasillero->TellWidth()-1,imagenCasillero->TellHeight()-1,0
								,*mapaGenerado,casillero->getCoordenadaX()*64,casillero->getCoordenadaY()*64);
	}
	else if (casillero->getFicha()->getTipoDeFicha() == VACIA && casillero->getEstado() == CONTAMINADO && casillero->getTipoDeCasillero() == TIERRA)
	{
		imagenCasillero->ReadFromFile("../tileset/toxic.bmp");
		RangedPixelToPixelCopy(*imagenCasillero,0,imagenCasillero->TellWidth()-1,imagenCasillero->TellHeight()-1,0
								,*mapaGenerado,casillero->getCoordenadaX()*64,casillero->getCoordenadaY()*64);
	}
	else if (casillero->getFicha()->getTipoDeFicha() == VACIA && casillero->getEstado() == CONTAMINADO && casillero->getTipoDeCasillero() == AGUA)
	{
		imagenCasillero->ReadFromFile("../tileset/aguaToxica.bmp");
		RangedPixelToPixelCopy(*imagenCasillero,0,imagenCasillero->TellWidth()-1,imagenCasillero->TellHeight()-1,0
								,*mapaGenerado,casillero->getCoordenadaX()*64,casillero->getCoordenadaY()*64);
	}
	else if (casillero->getFicha()->getTipoDeFicha() == SOLDADO && casillero->getFicha()->getJugadorDeBatallaDigital()->getJugador()->getID() == jugador->getJugador()->getID())
	{
		imagenCasillero->ReadFromFile("../tileset/soldado.bmp");
		RangedPixelToPixelCopy(*imagenCasillero,0,imagenCasillero->TellWidth()-1,imagenCasillero->TellHeight()-1,0
									,*mapaGenerado,casillero->getCoordenadaX()*64,casillero->getCoordenadaY()*64);
	}
	else if (casillero->getFicha()->getTipoDeFicha() == MINA && casillero->getFicha()->getJugadorDeBatallaDigital()->getJugador()->getID() == jugador->getJugador()->getID())
	{
		imagenCasillero->ReadFromFile("../tileset/mina.bmp");
		RangedPixelToPixelCopy(*imagenCasillero,0,imagenCasillero->TellWidth()-1,imagenCasillero->TellHeight()-1,0
									,*mapaGenerado,casillero->getCoordenadaX()*64,casillero->getCoordenadaY()*64);
	}

}
