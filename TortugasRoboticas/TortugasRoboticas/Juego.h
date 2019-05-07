#include<iostream>
#include<string>
#include<fstream>
#include<Windows.h>
#include"secuenciaCartas.h"
#include"TeclasEspeciales.h"

using namespace std;

const int MAX_JUGADORES = 4;
const int NUM_FILAS = 8;
const int NUM_COLUMNAS = 8;
const int NUM_TIPOS_CASILLAS = 6;
const int NUM_CARTAS_INICIALES_MANO = 3;

typedef enum  { NORTE, SUR, ESTE, OESTE } tDir;
typedef enum  { VACIA, HIELO, MURO, CAJA, JOYA, TORTUGA } tEstadoCasilla;
typedef enum { robarCarta, ejecutarSecuencia,ninguna } tAccion;

typedef struct 
{ int numero; 
  tDir direccion;
} tTortuga;

typedef struct 
{ tEstadoCasilla estado; 
  tTortuga tortuga; 
} tCasilla;

typedef tCasilla tTablero [NUM_FILAS][NUM_COLUMNAS];

typedef struct 
{ int cartasMano;
  int mano[NUM_TIPOS_CARTAS];
} tMano;

typedef struct 
{ int fila;
  int columna;
} tCoordenada;

typedef struct
{ string nombre;
  tMazo mazo;
  tMano mano;
  tCoordenada posActual;
} tJugador;

typedef struct
{ int numeroJugadores;
  int turnoActual;
  tJugador listaJugadores[MAX_JUGADORES];
  tTablero tablero;
} tJuego;


bool cargarJuego(tJuego & juego);
void mostrarJuego(const tJuego & juego);
bool ejecutarTurno(tJuego & juego);
bool accionRobar(tJuego & juego);
bool accionSecuencia(tJuego & juego, tMazo & secuencia);
void cambiarTurno(tJuego & juego);
void incluirCarta(tMano & mano, tCarta carta);

tCasilla char2Casilla(char c,int & tortugasencontradas);
string casilla2String(tCasilla casilla, int & colorfondo);
void colorFondo(int color);
int asignarColorATortuga(tCasilla casilla);
void contarCartaPorTipo(tJugador jugador, int & avanza, int & izquierda, int & derecha, int & laser);
tAccion caracterAccion(char c);
tCarta tecla2Carta(tTecla tecla);
bool comprobaryActualizarMano(tMano & mano, tCarta carta);
void girarIzquierda(tJuego & juego);
void girarDerecha(tJuego & juego);
bool avanzarTortuga(tJuego & juego);
void dispararLaser(tJuego & juego);