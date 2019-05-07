#include<iostream>
#include<algorithm>

using namespace std;

const int MAX_CARTAS_MAZO = 38;
const int MAX_CARTAS_AVANZA = 18;
const int MAX_CARTAS_IZQUIERDA = 8;
const int MAX_CARTAS_DERECHA = 8;
const int MAX_CARTAS_LASER = 4;
const int NUM_TIPOS_CARTAS = 4;

typedef enum { AVANZAR, GIROIZQUIERDA, GIRODERECHA, LASER } tCarta;

typedef tCarta *tPtrCarta;
typedef tCarta *tArrayPtrCartas[MAX_CARTAS_MAZO];

typedef struct
{
	tArrayPtrCartas lista;
	int numcartas;
} tMazo;

void crearVacia(tMazo & mazo);
bool sacar(tMazo & mazo, tCarta& carta);
void insertar(tMazo & mazo, tCarta carta);
void crearMazoAleatorio(tMazo & mazo);
void liberarCartas(tMazo & mazo);