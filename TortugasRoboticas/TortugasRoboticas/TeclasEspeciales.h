#include<iostream>
#include<string>
#include<conio.h>

using namespace std;

typedef enum { CARTAAVANZA, CARTADERECHA, CARTAIZQUIERDA, CARTALASER, SALIR, NADA } tTecla;

tTecla leerTecla();
void mostrarTecla(tTecla tecla);