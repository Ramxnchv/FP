//Hecho por Ramón Rosa Pérez

#include<iostream>
#include"Puntuaciones.h"
#include"Juego.h"
#include"checkML.h"

using namespace std;

int menu();

int main() 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	tJuego juego;
	tPuntuaciones puntos;
	int opcion,nuevapuntuacion;
	bool finjuego = false,partidaActiva=false,joya=false;
	inicializar(puntos);
	if (cargarPuntuaciones(puntos)) 
	{
		while (!finjuego) 
		{
			opcion = menu();
			if (opcion == 1) 
			{
				if (cargarJuego(juego))
				{
					partidaActiva = true;
				}
				while (partidaActiva) 
				{
					mostrarJuego(juego);
					joya=ejecutarTurno(juego);

					if (joya) 
					{
						cout << "\nEL JUGADOR " << juego.listaJugadores[juego.turnoActual].nombre << " ES EL GANADOR, ENHORABUENA\n" << endl;
						nuevapuntuacion = juego.numeroJugadores;
						actualizarPuntuacion(puntos, juego.listaJugadores[juego.turnoActual].nombre,nuevapuntuacion);
						partidaActiva = false;
					}
					else 
					{
						cambiarTurno(juego);
						mostrarJuego(juego);
					}
				}
			}
			else if (opcion == 2) 
			{
				int opcion;
				cout << "Introduce una opcion para mostrar las puntuaciones"<<endl<<"(1- Orden por defecto, 2- Orden Alfabetico): ";
				cin >> opcion;
				while (opcion < 1 || opcion > 2) 
				{
					cout << "Opcion incorrecta, introduce una opcion de nuevo"<<endl<<"(1- Orden por defecto, 2- Orden Alfabetico): ";
					cin >> opcion;
				}
				if (opcion == 1) 
				{
					mostrarPuntuaciones(puntos);
				}
				else 
				{
					ordenarAlfabeticamente(puntos);
					mostrarPuntuaciones(puntos);
					ordenarPorPuntos(puntos);
					empatePuntos(puntos);
				}
			}
			else 
			{
				finjuego = true;
				guardarPuntuaciones(puntos);
				liberar(puntos);
				for (int i = 0; i < juego.numeroJugadores; i++) {
					liberarCartas(juego.listaJugadores[i].mazo);
				}
			}
		}
	}

	system("pause");

	return 0;
}

int menu() 
{
	int op;
	cout << "\n---------------------TORTUGAS ROBOTICAS---------------------" << endl;

	cout << "\nElige opcion (1- Jugar, 2- Mostrar Puntuaciones, 0- Salir): ";
	cin >> op;
	while (op < 0 || op>2) 
	{
		cout << "Opcion incorrecta, introduce una opcion entre 0, 1 y 2: ";
		cin >> op;
	}
	return op;
}