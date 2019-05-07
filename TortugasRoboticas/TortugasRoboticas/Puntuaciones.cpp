#include"Puntuaciones.h"
#include"checkML.h"

void inicializar(tPuntuaciones & puntos) {
	puntos.numjugadores = 0;
	puntos.capacidad = JUGADORES_INICIALES;
	puntos.puntuaciones = new tPuntuacionJugador[puntos.capacidad];
}

bool cargarPuntuaciones(tPuntuaciones & puntos)
{
	ifstream entrada;
	bool abierto = false;
	tPuntuacionJugador nuevapuntuacion;
	entrada.open("puntuaciones.txt");

	if (entrada.is_open())
	{
		abierto = true;

		while (!entrada.eof())
		{
			entrada >> nuevapuntuacion.nombre;
			entrada >> nuevapuntuacion.puntuacion;
			insertar(puntos, nuevapuntuacion);
		}

		entrada.close();
	}
	return abierto;
}

void guardarPuntuaciones(const tPuntuaciones & puntos)
{
	ofstream salida;
	salida.open("puntuaciones.txt");

	if (!salida.is_open())
	{
		cout << "No se pudo abrir el archivo de puntuaciones" << endl;
	}
	else
	{
		for (int i = 0; i < puntos.numjugadores; i++)
		{
			salida << puntos.puntuaciones[i].nombre;
			salida << " ";
			salida << puntos.puntuaciones[i].puntuacion;
			if (i < puntos.numjugadores - 1) {
				salida << endl;
			}
		}

		salida.close();
	}
}

void mostrarPuntuaciones(const tPuntuaciones & puntos)
{
	for (int i = 0; i < puntos.numjugadores; i++)
	{
		cout << puntos.puntuaciones[i].nombre << " " << puntos.puntuaciones[i].puntuacion << endl;
	}

}

bool actualizarPuntuacion(tPuntuaciones & puntos, const string & nombre, int nuevos)
{
	bool actualizada;
	tPuntuacionJugador nuevapuntuacion;

	if (existeJugador(puntos, nombre))
	{
		nuevapuntuacion.puntuacion = puntos.puntuaciones[posJugador(puntos, nombre)].puntuacion + nuevos;
		nuevapuntuacion.nombre = puntos.puntuaciones[posJugador(puntos, nombre)].nombre;
		for (int i = posJugador(puntos, nombre) + 1; i < puntos.numjugadores; i++) {
			puntos.puntuaciones[i - 1] = puntos.puntuaciones[i];
		}
		puntos.numjugadores--;
		insertar(puntos, nuevapuntuacion);
		actualizada = true;
	}
	else
	{
		if (puntos.numjugadores == puntos.capacidad)
		{
			redimensionar(puntos);
		}
		nuevapuntuacion.puntuacion = nuevos;
		nuevapuntuacion.nombre = nombre;
		insertar(puntos, nuevapuntuacion);
		actualizada = true;
	}
	return actualizada;
}

bool existeJugador(tPuntuaciones & puntos, string nombre)
{
	int i = 0;
	while ((i < puntos.numjugadores) && (nombre != puntos.puntuaciones[i].nombre))
	{
		i++;
	}
	return puntos.puntuaciones[i].nombre == nombre;
}

int posJugador(const tPuntuaciones & puntos, string nombre)
{
	int i;
	i = 0;
	while ((i < puntos.numjugadores) && (puntos.puntuaciones[i].nombre != nombre))
	{
		i++;
	}
	return i;
}

void redimensionar(tPuntuaciones & puntos)
{

	tPuntuacionJugador* aux = new tPuntuacionJugador[puntos.capacidad + 4];
	for (int i = 0; i < puntos.numjugadores; i++)
	{
		aux[i] = puntos.puntuaciones[i];
	}
	delete[] puntos.puntuaciones;
	puntos.puntuaciones = aux;
	puntos.capacidad += 4;
	aux = nullptr;
}

void liberar(tPuntuaciones & puntos)
{
	delete[] puntos.puntuaciones;
	puntos.puntuaciones = nullptr;
	puntos.numjugadores = 0;
	puntos.capacidad = 0;
}

void ordenarPorPuntos(tPuntuaciones & puntos)
{
	tPuntuacionJugador aux;
	int j;
	for (int i = 1; i < puntos.numjugadores; i++)
	{
		aux = puntos.puntuaciones[i];
		j = i;
		while ((j > 0) && (aux.puntuacion > puntos.puntuaciones[j - 1].puntuacion))
		{
			puntos.puntuaciones[j] = puntos.puntuaciones[j - 1];
			j--;
		}
		puntos.puntuaciones[j] = aux;
	}
}

void ordenarAlfabeticamente(tPuntuaciones & puntos)
{
	tPuntuacionJugador aux;
	int j;
	for (int i = 1; i < puntos.numjugadores; i++)
	{
		aux = puntos.puntuaciones[i];
		j = i;
		while ((j > 0) && (aux.nombre < puntos.puntuaciones[j - 1].nombre))
		{
			puntos.puntuaciones[j] = puntos.puntuaciones[j - 1];
			j--;
		}
		puntos.puntuaciones[j] = aux;
	}
}

void empatePuntos(tPuntuaciones & puntos)
{
	tPuntuacionJugador aux;
	int j;
	for (int i = 1; i < puntos.numjugadores; i++)
	{
		if (puntos.puntuaciones[i - 1].puntuacion == puntos.puntuaciones[i].puntuacion)
		{
			aux = puntos.puntuaciones[i];
			j = i;
			while ((j > 0) && (aux.nombre < puntos.puntuaciones[j - 1].nombre))
			{
				puntos.puntuaciones[j] = puntos.puntuaciones[j - 1];
				j--;
			}
			puntos.puntuaciones[j] = aux;
		}
	}
}

bool operator< (const tPuntuacionJugador & p1, const tPuntuacionJugador & p2)
{
	bool menor = false;
	if (p1.puntuacion < p2.puntuacion)
	{
		menor = true;
	}
	else if (p1.puntuacion == p2.puntuacion)
	{
		if (p2.nombre < p1.nombre)
		{
			menor = true;
		}
	}
	return menor;
}

void insertar(tPuntuaciones & puntos, tPuntuacionJugador nuevapuntuacion)
{
	if (puntos.numjugadores == puntos.capacidad)
	{
		redimensionar(puntos);
	}
	int pos = puntos.numjugadores;
	while ((pos > 0) && (puntos.puntuaciones[pos - 1] < nuevapuntuacion))
	{
		puntos.puntuaciones[pos] = puntos.puntuaciones[pos - 1];
		pos--;
	}
	puntos.puntuaciones[pos] = nuevapuntuacion;
	puntos.numjugadores++;
}