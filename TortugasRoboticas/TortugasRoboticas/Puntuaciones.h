#include<iostream>
#include<fstream>
#include<string>

using namespace std;

const int JUGADORES_INICIALES = 4;

typedef struct 
{
	string nombre;
	int puntuacion;
} tPuntuacionJugador;

typedef struct 
{
	tPuntuacionJugador* puntuaciones;
	int numjugadores;
	int capacidad;
} tPuntuaciones;

void inicializar(tPuntuaciones & puntos);
bool cargarPuntuaciones(tPuntuaciones & puntos);
void guardarPuntuaciones(const tPuntuaciones & puntos);
void mostrarPuntuaciones(const tPuntuaciones & puntos);
bool actualizarPuntuacion(tPuntuaciones & puntos, const string & nombre, int nuevos);
bool existeJugador(tPuntuaciones & puntos, string nombre);
int posJugador(const tPuntuaciones & puntos, string nombre);
void redimensionar(tPuntuaciones & puntos);
void liberar(tPuntuaciones & puntos);
void empatePuntos(tPuntuaciones & puntos);
bool operator<(const tPuntuacionJugador & p1, const tPuntuacionJugador & p2);
void ordenarAlfabeticamente(tPuntuaciones & puntos);
void insertar(tPuntuaciones & puntos, tPuntuacionJugador nuevapuntuacion);

//solo utilizada para reordenar tras mostrar alfabéticamente
void ordenarPorPuntos(tPuntuaciones & puntos);