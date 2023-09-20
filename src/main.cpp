#include "BatallaDigital.h"
#include <iostream>
#include "EasyBMP.h"
using namespace std;


int main(int argc, char const* argv[]){

  BatallaDigital* batalla = new BatallaDigital();
  batalla->Inicio();
  batalla->partida();
  delete batalla;

  return 0;
}
