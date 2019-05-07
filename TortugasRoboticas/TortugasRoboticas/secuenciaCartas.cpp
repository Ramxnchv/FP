#include"secuenciaCartas.h"
#include"checkML.h"

void crearVacia(tMazo & mazo)
{
	mazo.numcartas = 0;
}
bool sacar(tMazo & mazo, tCarta & carta)
{
	bool quedancartas = mazo.numcartas>0;

	if (quedancartas) 
	{
		carta = *(mazo.lista[0]);

		for (int i = 1; i < mazo.numcartas; i++)
		{
			*(mazo.lista[i - 1]) = *(mazo.lista[i]);
		}
		mazo.numcartas--;
	}

	return quedancartas;
}
void insertar(tMazo & mazo, tCarta carta)
{
	if (mazo.numcartas < MAX_CARTAS_MAZO)
	{
		mazo.lista[mazo.numcartas] = new tCarta;
		*mazo.lista[mazo.numcartas] = carta;
		mazo.numcartas++;
	}
}
void crearMazoAleatorio(tMazo & mazo)
{

	mazo.numcartas = 0;

	while (mazo.numcartas < MAX_CARTAS_AVANZA)
	{
		insertar(mazo, AVANZAR);
	}
	while (mazo.numcartas < (MAX_CARTAS_AVANZA + MAX_CARTAS_DERECHA))
	{
		insertar(mazo, GIRODERECHA);
	}
	while (mazo.numcartas < (MAX_CARTAS_AVANZA + MAX_CARTAS_DERECHA + MAX_CARTAS_IZQUIERDA))
	{
		insertar(mazo, GIROIZQUIERDA);
	}
	while (mazo.numcartas < MAX_CARTAS_MAZO)
	{
		insertar(mazo, LASER);
	}

	random_shuffle(&mazo.lista[0], &mazo.lista[MAX_CARTAS_MAZO - 1]);
}

void liberarCartas(tMazo & mazo) 
{

	for (int i = 0; i < mazo.numcartas; i++) 
	{
		delete mazo.lista[i];
	}
	mazo.numcartas = 0;
}