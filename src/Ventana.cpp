#include "Ventana.h"
using namespace std;

Ventana::Ventana(){}

int Ventana::preguntarNumero(int x, int y){
  int validador = 0;
  int numeroRetorno;
  do{
    cin >> numeroRetorno;
    if(numeroRetorno >= x && numeroRetorno <= y){
      validador = 1;
    }
    //en caso de que el usuario ingrese algo que no este en el rango
    else if(std::cin.fail() || (numeroRetorno < x || numeroRetorno > y)){
      //vuelve el failbit a null
      std::cin.clear();
      //elimina lo que estaba escrito en el input y lo deja limpio
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "La opcion ingresada es incorrecta" << endl << "Ingresa una correcta -.-" << endl;
    }
  } while(validador == 0);
  return numeroRetorno;
}

int Ventana::preguntarNumeroUnico(int x)
{
  int validador = 0;
  int numeroRetorno;
  do{
    cin >> numeroRetorno;
    if(numeroRetorno == x ){
      validador = 1;
    }
    //en caso de que el usuario ingrese algo que no este en el rango
    else if(std::cin.fail() || (numeroRetorno != x)){
      //vuelve el failbit a null
      std::cin.clear();
      //elimina lo que estaba escrito en el input y lo deja limpio
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "La opcion ingresada es incorrecta" << endl << "Ingresa una correcta -.-" << endl;
    }
  } while(validador == 0);
  return numeroRetorno;
}

void Ventana::mostrarMensajeConsola(std::string mensaje)
{
  cout << endl << mensaje << endl;
}

void Ventana::mostrarMensajeConsolaConNumero(const char* mensaje, const int numero)
{
  cout << endl << mensaje  << numero << endl;
} 

void Ventana::mostrarCartas(Cartas * mano)
{
	CARTA carta = mano->getCarta();
	switch (carta)
	{
	case 0:
		cout << "1. Ataque Quimico " << mano->getCantidad() << endl;
		break;
	case 1:
		cout << "2. Avion Radar " << mano->getCantidad() << endl;
		break;
	case 2:
		cout << "3. Barco " << mano->getCantidad() << endl;
		break;
	case 3:
		cout << "4. Ataque Aereo " << mano->getCantidad() << endl;
		break;
	case 4:
		cout << "5. Repetir Turno " << mano->getCantidad() << endl;
		break;
	case 5:
		cout << "6. Tres Minas " << mano->getCantidad() << endl;
		break;
	}
}

/*
 *  Post: Devuelve true si la letra es valida
 * */

bool Ventana::PreguntaSiONo(std::string objeto)
{
	bool respuesta;
	int validador = 0;
	char input;
	do
	{
		if (objeto == "Soldado")
		{
			cout << "Desea mover un soldado ?" << endl;
		}
		else if (objeto == "Carta")
		{
			cout << "Desea jugar una carta ?" << endl;
		}
		cout << "[S/N]" << endl;
		cin >> input;
		if(input == 's' || input == 'S')
		{
		  validador = 1;
		  respuesta = true;
		}
		else if (input == 'N' || input == 'n')
		{
			validador = 1;
			respuesta = false;
		}
		//en caso de que el usuario ingrese algo que no este en el rango
		else if(std::cin.fail() || (input != 's' || input != 'S' || input != 'N' || input != 'n'))
		{
		  //vuelve el failbit a null
		  std::cin.clear();
		  //elimina lo que estaba escrito en el input y lo deja limpio
		  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		  std::cout << "La opcion ingresada es incorrecta" << endl << "Ingresa una correcta -.-" << endl;
		}
	}while(validador == 0);

	return respuesta;
}
