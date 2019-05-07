#include"TeclasEspeciales.h"
#include"checkML.h"

tTecla leerTecla()
{
int tecla;
tTecla tipotecla=NADA;

cin.sync();
tecla = _getch();

if (tecla == 0xe0) 
{
	tecla = _getch();
	switch (tecla) 
	{
	case 72:
		tipotecla = CARTAAVANZA;
		break;
	case 77:
		tipotecla = CARTADERECHA;
		break;
	case 75:
		tipotecla = CARTAIZQUIERDA;
		break;
	default:
		tipotecla = NADA;
		break;
	}
}

else if (tecla == 32) 
{
	tipotecla = CARTALASER;
	}
else if (tecla == 13) 
{
	tipotecla = SALIR;
	}

else 
{
	cout << "Ejecutaste una tecla incorrecta, debes usar las teclas de direccion y el espacio" << endl;
	tipotecla = NADA;
}


return tipotecla;
}

void mostrarTecla(tTecla tecla) 
{
	switch (tecla) 
	{
	case CARTAAVANZA:
		cout << "^";
		break;
	case CARTAIZQUIERDA:
		cout << "<";
		break;
	case CARTADERECHA:
		cout << ">";
		break;
	case CARTALASER:
		cout << "~";
		break;
	case SALIR:
		cout << " ";
		break;
	case NADA:
		cout << " ";
		break;
	}
}