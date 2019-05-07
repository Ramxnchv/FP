
#include"Juego.h"
#include"checkML.h"

bool cargarJuego(tJuego & juego) 
{
	int numjugadores;
	bool juegocargado = false;
	string lineaextraida;

	cout << "Introduce el numero de jugadores(entre 1 y 4): ";
	cin >> numjugadores;
	while ((numjugadores < 1) || (numjugadores > MAX_JUGADORES) ) 
	{
		cout << "Error, mas jugadores de los permitidos" << endl;
		cout << "Introduce el numero de jugadores(entre 1 y 4): " << endl;
		cin >> numjugadores;
	}

	juego.numeroJugadores = numjugadores;
	
	//lectura tablero

	ifstream entrada;
	entrada.open("tableros.txt");
	if (!entrada.is_open()) 
	{
		cout << "Error, no se pudo abrir el fichero de tableros" << endl;
	}
	else {
		//la variable numtablero hace referencia al numero extraído del fichero para compararlo con el numero de jugadores y extraer el tablero correspondiente
		int numtablero, tortugasencontradas = 0;
		tCoordenada coordenada;
		entrada >> numtablero;
		entrada.ignore();
		while (numtablero != juego.numeroJugadores)
		{
			for (int i = 0; i < NUM_FILAS; i++) 
			{
				getline(entrada, lineaextraida);
			}
			entrada >> numtablero;
			entrada.ignore();
		}

		for (int i = 0; i < NUM_FILAS; i++) 
		{
			getline(entrada, lineaextraida);
			for (int j = 0; j < NUM_COLUMNAS; j++) 
			{
				juego.tablero[i][j] = char2Casilla(lineaextraida.at(j),tortugasencontradas);
				if(juego.tablero[i][j].estado==TORTUGA)
				{
				coordenada.fila = i;
				coordenada.columna = j;
				juego.listaJugadores[tortugasencontradas-1].posActual = coordenada;
				}
			}
		}
		juegocargado = true;
	}
	juego.turnoActual = 0;

	//Pedir nombres jugadores, inicializar mazos y manos
	tCarta carta;
	bool quedancartas=true;

	for (int i = 0; i < juego.numeroJugadores; i++) 
	{
		cout << "Introduce un nombre para el jugador " <<i+1<< " : ";
		cin>>juego.listaJugadores[i].nombre;

		crearMazoAleatorio(juego.listaJugadores[i].mazo);

			//Inicializar las cartas de la mano a 0
			juego.listaJugadores[i].mano.cartasMano = 0;
			for (int t = 0; t < NUM_TIPOS_CARTAS; t++) 
			{
				juego.listaJugadores[i].mano.mano[t] = 0;
			}

			//Incluir 3 cartas en la mano
		for (int j = 0; j < NUM_CARTAS_INICIALES_MANO; j++) 
		{
			if(quedancartas)
			{
				quedancartas=sacar(juego.listaJugadores[i].mazo, carta);
				incluirCarta(juego.listaJugadores[i].mano, carta);
			}
		}
	}

	return juegocargado;
}

void mostrarJuego(const tJuego & juego) 
{
	int colorfondo;
	string casillaAMostrar;
	system("cls");
	//mostrar tablero
	cout << "\n";
	for (int i = 0; i < NUM_FILAS; i++) 
	{
		for (int j = 0; j < NUM_COLUMNAS; j++) 
		{
			casillaAMostrar = casilla2String(juego.tablero[i][j], colorfondo);
			colorFondo(colorfondo);
			cout << casillaAMostrar;
		}
		cout << endl;
	}
	colorFondo(0);

	//mostrar jugadores y cartas
	tCasilla casilla;
	int cartasAvanza = 0;
	int cartasIzda = 0;
	int cartasDcha = 0;
	int cartasLaser = 0;

	cout << "\n" << endl;

	for (int i = 0; i < juego.numeroJugadores; i++) 
	{
		casilla.tortuga.numero = i+1;
		colorFondo(asignarColorATortuga(casilla));
		
		if (juego.turnoActual == i) 
		{
			cout << "> ";
		}
		cout << i + 1 << ". " << juego.listaJugadores[i].nombre << ":";
		colorFondo(0);
		for (int j = 0; j < juego.listaJugadores[i].mano.cartasMano; j++)
		{
			contarCartaPorTipo(juego.listaJugadores[i], cartasAvanza, cartasIzda, cartasDcha, cartasLaser);
		}
		cout << " " << cartasAvanza;
		colorFondo(3);
		cout << "^";
		colorFondo(0);
		cout << " " << cartasIzda;
		colorFondo(3);
		cout << "<";
		colorFondo(0);
		cout << " " << cartasDcha;
		colorFondo(3);
		cout << ">";
		colorFondo(0);
		cout << " " << cartasLaser;
		colorFondo(3);
		cout << "~";
		colorFondo(0);
		cout << endl;
	}
}

bool ejecutarTurno(tJuego & juego) 
{
	bool joya = false,poderRobar=false;
	tAccion accion;
	tMazo secuencia;
	tTecla tecla;
	char c;
	cout << "Introduce una accion a realizar (R para robar o E para crear secuencia): ";
	cin >> c;
	accion=caracterAccion(c);
	while (accion == ninguna) 
	{
		cout << "Error, debe introducir una accion valida (R para robar o E para crear secuencia): ";
		cin >> c;
		accion = caracterAccion(c);
	}
		if (accion == robarCarta) 
		{
			poderRobar = accionRobar(juego);
			if (poderRobar == false) 
			{
				cout << "Has agotado las cartas para robar" << endl;
			}
		}
		else if (accion == ejecutarSecuencia) 
		{
			crearVacia(secuencia);
			cout << "Introduce una secuencia de cartas: ";
			tecla=leerTecla();
			mostrarTecla(tecla);
			while (tecla != SALIR) 
			{
				if ((tecla != NADA)&&(comprobaryActualizarMano(juego.listaJugadores[juego.turnoActual].mano, tecla2Carta(tecla))))
				{
					secuencia.lista[secuencia.numcartas] = new tCarta;
					*(secuencia.lista[secuencia.numcartas]) = tecla2Carta(tecla);
					secuencia.numcartas++;
				}
				tecla=leerTecla();
				mostrarTecla(tecla);
			}
			mostrarJuego(juego);
			joya = accionSecuencia(juego, secuencia);
			for (int i = 0; i < secuencia.numcartas; i++) 
			{
				delete secuencia.lista[i];
			}
			secuencia.numcartas = 0;
		}
	return joya;
}

bool accionRobar(tJuego & juego) 
{
	bool poderRobar=false;
	tCarta carta;
	if (sacar(juego.listaJugadores[juego.turnoActual].mazo, carta)) 
	{
		incluirCarta(juego.listaJugadores[juego.turnoActual].mano, carta);
		poderRobar = true;
	}
	return poderRobar;
}

bool accionSecuencia(tJuego & juego, tMazo & secuencia) 
{
	int i = 0;
	bool hayGanador = false;
	while((i<secuencia.numcartas)&&(!hayGanador))
	{
		switch (*(secuencia.lista[i])) 
		{
		case AVANZAR:
			hayGanador=avanzarTortuga(juego);
			insertar(juego.listaJugadores[juego.turnoActual].mazo, AVANZAR);
			break;
		case GIROIZQUIERDA:
			girarIzquierda(juego);
			insertar(juego.listaJugadores[juego.turnoActual].mazo, GIROIZQUIERDA);
			break;
		case GIRODERECHA:
			girarDerecha(juego);
			insertar(juego.listaJugadores[juego.turnoActual].mazo, GIRODERECHA);
			break;
		case LASER:
			dispararLaser(juego);
			insertar(juego.listaJugadores[juego.turnoActual].mazo, LASER);
			break;
		}
		i++;
	}
		return hayGanador;
	
}

void cambiarTurno(tJuego & juego) 
{
		if (juego.turnoActual < juego.numeroJugadores-1) 
		{
			juego.turnoActual++;
		}
		else 
		{
			juego.turnoActual = 0;
		}
	}

void incluirCarta(tMano & mano, tCarta carta) 
{
		if (carta == AVANZAR) 
		{
			mano.mano[0]++;
		}
		else if (carta == GIROIZQUIERDA) 
		{
			mano.mano[1]++;
		}
		else if (carta == GIRODERECHA) 
		{
			mano.mano[2]++;
		}
		else if (carta == LASER)
		{
			mano.mano[3]++;
		}
		mano.cartasMano++;
	}

tCasilla char2Casilla(char c, int & tortugasencontradas) 
{
		tCasilla casilla;

		if (c == '#') 
		{
			casilla.estado = MURO;
		}
		else if (c == '@') 
		{
			casilla.estado = HIELO;
		}
		else if (c == ' ') 
		{
			casilla.estado = VACIA;
		}
		else if (c == '$') 
		{
			casilla.estado = JOYA;
		}
		else if (c == 'C') 
		{
			casilla.estado = CAJA;
		}
		else if (c == 'U') 
		{
			casilla.estado = TORTUGA;
			casilla.tortuga.direccion = NORTE;
			tortugasencontradas++;
			casilla.tortuga.numero = tortugasencontradas;
		}
		else if (c == 'D') 
		{
			casilla.estado = TORTUGA;
			casilla.tortuga.direccion = SUR;
			tortugasencontradas++;
			casilla.tortuga.numero = tortugasencontradas;
		}
		else if (c == 'R') 
		{
			casilla.estado = TORTUGA;
			casilla.tortuga.direccion = ESTE;
			tortugasencontradas++;
			casilla.tortuga.numero = tortugasencontradas;
		}
		else if (c == 'L') 
		{
			casilla.estado = TORTUGA;
			casilla.tortuga.direccion = OESTE;
			tortugasencontradas++;
			casilla.tortuga.numero = tortugasencontradas;
		}
		return casilla;
	}

string casilla2String(tCasilla casilla, int & colorfondo) {

		string dibujo;

		if (casilla.estado == CAJA) 
		{
			colorfondo = 4;
			dibujo = "[]";
		}
		else if (casilla.estado == HIELO) 
		{
			colorfondo = 11;
			dibujo = "**";
		}
		else if (casilla.estado == MURO) 
		{
			colorfondo = 7;
			dibujo = "||";
		}
		else if (casilla.estado == JOYA) 
		{
			colorfondo = 12;
			dibujo = "00";
		}
		else if (casilla.estado == VACIA) 
		{
			colorfondo = 1;
			dibujo = "  ";
		}
		else if (casilla.estado == TORTUGA) 
		{
			if (casilla.tortuga.direccion == NORTE) 
			{
				dibujo = "^^";
				colorfondo = asignarColorATortuga(casilla);
			}
			else if (casilla.tortuga.direccion == ESTE) 
			{
				dibujo = ">>";
				colorfondo = asignarColorATortuga(casilla);
			}
			else if (casilla.tortuga.direccion == OESTE) 
			{
				dibujo = "<<";
				colorfondo = asignarColorATortuga(casilla);
			}
			else if (casilla.tortuga.direccion == SUR) 
			{
				dibujo = "VV";
				colorfondo = asignarColorATortuga(casilla);
			}
		}

		return dibujo;
	}

void colorFondo(int color) 
{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, 15 | (color << 4));
	}

int asignarColorATortuga(tCasilla casilla) 
{
		int colorfondo = 5;

		if (casilla.tortuga.numero == 1) 
		{
			colorfondo = 5;
		}
		else if (casilla.tortuga.numero == 2)
		{
			colorfondo = 13;
		}
		else if (casilla.tortuga.numero == 3) 
		{
			colorfondo = 9;
		}
		else if (casilla.tortuga.numero == 4) 
		{
			colorfondo = 10;
		}
		return colorfondo;
	}

void contarCartaPorTipo(tJugador jugador, int & avanza, int & izquierda, int & derecha, int & laser) 
{
		avanza = jugador.mano.mano[0];
		izquierda = jugador.mano.mano[1];
		derecha = jugador.mano.mano[2];
		laser = jugador.mano.mano[3];
	}

tAccion caracterAccion(char c)
{
		tAccion acc;
		if (c == 'R' || c == 'r') 
		{
			acc = robarCarta;
		}
		else if (c == 'E' || c == 'e')
		{
			acc = ejecutarSecuencia;
		}
		else
		{
			acc = ninguna;
		}
		return acc;
	}

bool comprobaryActualizarMano(tMano & mano, tCarta carta) 
{
		bool compruebacartaexiste = false;
		switch (carta) 
		{
		case AVANZAR:
			if (mano.mano[0] != 0)
			{
				mano.mano[0]--;
				compruebacartaexiste = true;
			}
			else 
			{
				cout << "No te quedan cartas del tipo avanzar";
			}
			break;
		case GIROIZQUIERDA:
			if (mano.mano[1] != 0) 
			{
				mano.mano[1]--;
				compruebacartaexiste = true;
			}
			else 
			{
				cout << "No te quedan cartas del tipo giro izquierda";
			} 
			break;
		case GIRODERECHA:
			if (mano.mano[2] != 0) 
			{
				mano.mano[2]--;
				compruebacartaexiste = true;
			}
			else 
			{
				cout << "No te quedan cartas del tipo giro derecha";
			} 
			break;
		case LASER:
			if (mano.mano[3] != 0)
			{
				mano.mano[3]--;
				compruebacartaexiste = true;
			}
			else
			{
				cout << "No te quedan cartas del tipo laser";
			} 
			break;
		}
		return compruebacartaexiste;
}

tCarta tecla2Carta(tTecla tecla) 
{
	tCarta carta;
	switch (tecla) 
	{
	case CARTAAVANZA:
		carta = AVANZAR;
		break;
	case CARTAIZQUIERDA:
		carta = GIROIZQUIERDA;
		break;
	case CARTADERECHA:
		carta = GIRODERECHA;
		break;
	case CARTALASER:
		carta = LASER;
		break;
	}
	return carta;
}

void girarIzquierda(tJuego & juego) 
{
	if (juego.tablero[juego.listaJugadores[juego.turnoActual].posActual.fila][juego.listaJugadores[juego.turnoActual].posActual.columna].tortuga.direccion == NORTE) 
	{
		juego.tablero[juego.listaJugadores[juego.turnoActual].posActual.fila][juego.listaJugadores[juego.turnoActual].posActual.columna].tortuga.direccion = OESTE;
	}
	else if (juego.tablero[juego.listaJugadores[juego.turnoActual].posActual.fila][juego.listaJugadores[juego.turnoActual].posActual.columna].tortuga.direccion == SUR)
	{
		juego.tablero[juego.listaJugadores[juego.turnoActual].posActual.fila][juego.listaJugadores[juego.turnoActual].posActual.columna].tortuga.direccion = ESTE;
	}
	else if (juego.tablero[juego.listaJugadores[juego.turnoActual].posActual.fila][juego.listaJugadores[juego.turnoActual].posActual.columna].tortuga.direccion == OESTE) 
	{
		juego.tablero[juego.listaJugadores[juego.turnoActual].posActual.fila][juego.listaJugadores[juego.turnoActual].posActual.columna].tortuga.direccion = SUR;
	}
	else 
	{
		juego.tablero[juego.listaJugadores[juego.turnoActual].posActual.fila][juego.listaJugadores[juego.turnoActual].posActual.columna].tortuga.direccion = NORTE;
	}
	mostrarJuego(juego);
}

void girarDerecha(tJuego & juego) {
	if (juego.tablero[juego.listaJugadores[juego.turnoActual].posActual.fila][juego.listaJugadores[juego.turnoActual].posActual.columna].tortuga.direccion == NORTE) 
	{
		juego.tablero[juego.listaJugadores[juego.turnoActual].posActual.fila][juego.listaJugadores[juego.turnoActual].posActual.columna].tortuga.direccion = ESTE;
	}
	else if (juego.tablero[juego.listaJugadores[juego.turnoActual].posActual.fila][juego.listaJugadores[juego.turnoActual].posActual.columna].tortuga.direccion == SUR) 
	{
		juego.tablero[juego.listaJugadores[juego.turnoActual].posActual.fila][juego.listaJugadores[juego.turnoActual].posActual.columna].tortuga.direccion = OESTE;
	}
	else if (juego.tablero[juego.listaJugadores[juego.turnoActual].posActual.fila][juego.listaJugadores[juego.turnoActual].posActual.columna].tortuga.direccion == OESTE) 
	{
		juego.tablero[juego.listaJugadores[juego.turnoActual].posActual.fila][juego.listaJugadores[juego.turnoActual].posActual.columna].tortuga.direccion = NORTE;
	}
	else 
	{
		juego.tablero[juego.listaJugadores[juego.turnoActual].posActual.fila][juego.listaJugadores[juego.turnoActual].posActual.columna].tortuga.direccion = SUR;
	}
	mostrarJuego(juego);
}

bool avanzarTortuga(tJuego & juego) 
{
	bool joya = false;
	tCoordenada destino, destinocaja;
	destino.columna = juego.listaJugadores[juego.turnoActual].posActual.columna;
	destino.fila = juego.listaJugadores[juego.turnoActual].posActual.fila;
	switch (juego.tablero[juego.listaJugadores[juego.turnoActual].posActual.fila][juego.listaJugadores[juego.turnoActual].posActual.columna].tortuga.direccion)
	{
	case NORTE:
		destino.fila--;
		break;
	case SUR:
		destino.fila++;
		break;
	case ESTE:
		destino.columna++;
		break;
	case OESTE:
		destino.columna--;
		break;
	}

	if (!(destino.columna<0 || destino.columna>NUM_COLUMNAS - 1 || destino.fila<0 || destino.fila>NUM_FILAS - 1)) 
	{

		if (juego.tablero[destino.fila][destino.columna].estado == VACIA) 
		{
			juego.tablero[juego.listaJugadores[juego.turnoActual].posActual.fila][juego.listaJugadores[juego.turnoActual].posActual.columna].estado = VACIA;
			juego.tablero[destino.fila][destino.columna].estado = TORTUGA;
			juego.tablero[destino.fila][destino.columna].tortuga.direccion = juego.tablero[juego.listaJugadores[juego.turnoActual].posActual.fila][juego.listaJugadores[juego.turnoActual].posActual.columna].tortuga.direccion;
			juego.tablero[destino.fila][destino.columna].tortuga.numero = juego.tablero[juego.listaJugadores[juego.turnoActual].posActual.fila][juego.listaJugadores[juego.turnoActual].posActual.columna].tortuga.numero;
			juego.listaJugadores[juego.turnoActual].posActual.columna = destino.columna;
			juego.listaJugadores[juego.turnoActual].posActual.fila = destino.fila;
			mostrarJuego(juego);
		}

		else if (juego.tablero[destino.fila][destino.columna].estado == CAJA) 
		{
			destinocaja.columna = destino.columna;
			destinocaja.fila = destino.fila;
			switch (juego.tablero[juego.listaJugadores[juego.turnoActual].posActual.fila][juego.listaJugadores[juego.turnoActual].posActual.columna].tortuga.direccion) 
			{
			case NORTE:
				destinocaja.fila--;
				break;
			case SUR:
				destinocaja.fila++;
				break;
			case ESTE:
				destinocaja.columna++;
				break;
			case OESTE:
				destinocaja.columna--;
				break;
			}

				if (!(destinocaja.columna<0 || destinocaja.columna>NUM_COLUMNAS - 1 || destinocaja.fila<0 || destinocaja.fila>NUM_FILAS - 1)) 
				{
					if (juego.tablero[destinocaja.fila][destinocaja.columna].estado == VACIA) 
					{
						juego.tablero[juego.listaJugadores[juego.turnoActual].posActual.fila][juego.listaJugadores[juego.turnoActual].posActual.columna].estado = VACIA;
						juego.tablero[destinocaja.fila][destinocaja.columna].estado = CAJA;
						juego.tablero[destino.fila][destino.columna].estado = TORTUGA;
						juego.tablero[destino.fila][destino.columna].tortuga.direccion = juego.tablero[juego.listaJugadores[juego.turnoActual].posActual.fila][juego.listaJugadores[juego.turnoActual].posActual.columna].tortuga.direccion;
						juego.tablero[destino.fila][destino.columna].tortuga.numero = juego.tablero[juego.listaJugadores[juego.turnoActual].posActual.fila][juego.listaJugadores[juego.turnoActual].posActual.columna].tortuga.numero;
						juego.listaJugadores[juego.turnoActual].posActual = destino;
					}
				}
			
			mostrarJuego(juego);
		}

		else if (juego.tablero[destino.fila][destino.columna].estado == JOYA) 
		{
			juego.tablero[juego.listaJugadores[juego.turnoActual].posActual.fila][juego.listaJugadores[juego.turnoActual].posActual.columna].estado = VACIA;
			juego.tablero[destino.fila][destino.columna].tortuga = juego.tablero[juego.listaJugadores[juego.turnoActual].posActual.fila][juego.listaJugadores[juego.turnoActual].posActual.columna].tortuga;
			juego.listaJugadores[juego.turnoActual].posActual = destino;
			juego.tablero[destino.fila][destino.columna].estado = TORTUGA;
			mostrarJuego(juego);
			joya = true;
		}
	}
	return joya;
}

void dispararLaser(tJuego & juego) 
{
	bool buscarObstaculo = true;
	tCoordenada destinolaser;
	destinolaser.columna = juego.listaJugadores[juego.turnoActual].posActual.columna;
	destinolaser.fila = juego.listaJugadores[juego.turnoActual].posActual.fila;

	while (buscarObstaculo) 
	{
		switch (juego.tablero[juego.listaJugadores[juego.turnoActual].posActual.fila][juego.listaJugadores[juego.turnoActual].posActual.columna].tortuga.direccion) 
		{
		case NORTE:
			destinolaser.fila--;
			break;
		case SUR:
			destinolaser.fila++;
			break;
		case ESTE:
			destinolaser.columna++;
			break;
		case OESTE:
			destinolaser.columna--;
			break;
		}
		if (destinolaser.columna<0 || destinolaser.columna>NUM_COLUMNAS - 1 || destinolaser.fila<0 || destinolaser.fila>NUM_FILAS - 1) 
		{
			buscarObstaculo = false;
		}
		else if (juego.tablero[destinolaser.fila][destinolaser.columna].estado != HIELO) 
		{
			cout << "El laser no es eficaz contra objetos que no sean muros de hielo..." << endl;
			buscarObstaculo = false;
		}
		else if (juego.tablero[destinolaser.fila][destinolaser.columna].estado == HIELO) 
		{
			buscarObstaculo = false;
			juego.tablero[destinolaser.fila][destinolaser.columna].estado = VACIA;
		}
		mostrarJuego(juego);
	}
}