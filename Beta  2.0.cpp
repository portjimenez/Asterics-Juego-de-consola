#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string.h>
using namespace std;

void gotoxy(int x, int y);
void movimientoPrimer(int xA[], int yA[], int numero[]);
void movimientoSegundo(int xA[], int yA[], int numero[]);
void movimientoTercero(int xA[], int yA[], int numero[]);
void resultadosFinalesWin(int pasosAlmacenados, int puntosAlmacenados);
void bordes();
void PrimerNivel();
void SegundoNivel();
void TercerNivel();
int ImprimirResultados(int pasosAlmacen[]);
int Puntos(int puntosAlmacen[]);

char opcion;
char aster = '*';
char borrar = ' ';
int pasos = 0;
int pasosAlmacen[3] = {0,0,0};
int contadorPuntos = 0;
int puntosAlmacen[3] = {0,0,0};
string nivel1 = "NIVEL UNO";
string nivel2 = "NIVEL DOS";
string nivel3 = "NIVEL TRES";

int main(){
	const int altoMapa = 120;
	int largoMapa = 4;
	string bienvenida1, bienvenida2;
	char inicio;
	
	bienvenida1 = "BIENVENIDO A ASTER";
	bienvenida2 = "PRESIONA LA TECLA enter PARA EMPEZAR :)";
	
	system("color a");
	bordes();
	gotoxy((altoMapa - bienvenida1.length()) / 2, largoMapa);
	cout<<bienvenida1;
	gotoxy(15, 6);
	cout<<"Reglas para jugar: ";
	gotoxy(15, 8);
	cout<<"1. Debe de ir recolectando los numeros de menor a mayor."<<endl;
	gotoxy(15, 10);
	cout<<"2. Solo recolecte los numeros que se encuentra dentro o en los bordes,";
	gotoxy(18, 11);
	cout<<"mas haya no debera de recolectar.";
	gotoxy(15, 13);
	cout<<"3. Puede moverse con las teclas (WSAD) o bien con las flehas del teclado.";
	gotoxy(15, 15);
	cout<<"4. Busca la trayectoria mas rapida para llegar a cada numero.";
	gotoxy(15, 17);
	cout<<"5. Diviertete e intenta no romper tu teclado :)";
	gotoxy((altoMapa - bienvenida2.length()) / 2, 19);
	cout<<bienvenida2;
	inicio = getch();
	switch(inicio){
		case char(13):
			system("cls");
			PrimerNivel();
		break;
		default: 
			system("cls");
			gotoxy(42, 2);
			cout<<"Tecla no valida :( presione enter";
			main();
	}
	
	return 0;

}
void gotoxy(int x, int y){
	HANDLE hcon	= GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}

//FUNCIONES PARA NIVELES Y MOVIMIENTO
void PrimerNivel(){
	srand(time(NULL));
	
	gotoxy((120 - nivel1.length()) / 2, 2); cout<<nivel1;
	
	bordes();
	
	int xA[5];
	int yA[5];
	int numero[5];
	int contador[10] = {0};
	
	//CICLO PARA GENERAR LOS NUMEROS
	for (int i = 0; i < 5; i++){
		int num = rand() % 10;
		while (contador[num] >= 2) {
            num = rand() % 10;
        }
        contador[num]++;
        
        numero[i] = num;
	}
	
	int orden = sizeof(numero) / sizeof(numero[0]);
	sort(numero, numero + orden);
	
	//CICLO PARA REPARTIR LOS NUMEROS
	for(int ii = 0; ii < 5; ii++){
		xA[ii] = rand() % 110;
		yA[ii] = rand() % 23;
		
		//SPAUN DE NUMEROS DENTRO DEL MAPA (BORDES)
		if((xA[ii] > 10 && xA[ii] < 110) && (yA[ii] > 4 && yA[ii] < 23)){ 
			gotoxy(xA[ii], yA[ii]);cout<<numero[ii];
		}else{
			if(xA[ii] <= 10){
				xA[ii] = xA[ii] + 10;
				gotoxy(xA[ii], yA[ii]);cout<<numero[ii];
			}
			if(yA[ii] <= 4){
				yA[ii] = yA[ii] + 4;
				gotoxy(xA[ii], yA[ii]);cout<<numero[ii];
			}
			if(xA[ii] >= 110){
				xA[ii] = xA[ii] - 11;
				gotoxy(xA[ii], yA[ii]);cout<<numero[ii];
			}
			if(yA[ii] >= 23){
				yA[ii] = yA[ii] - 9;
				gotoxy(xA[ii], yA[ii]);cout<<numero[ii];
			}
		}
	}
	
	movimientoPrimer(xA, yA, numero);
}
void movimientoPrimer(int xA[], int yA[], int numero[]){
	int x=11, y=11;
	int numero_actual = numero[0];
	int siguiente_numero = 1;
	
	while(opcion!='n'){
		gotoxy(x,y); cout<<aster;
		opcion=getch();
		switch(opcion){
			//MOVIMIENTO CON LETRAS
			case 'w':cout<<"\b \b"; y--; pasos++; break;
			case 's':cout<<"\b \b"; y++; pasos++; break;
			case 'a':cout<<"\b \b"; x--; pasos++; break;
			case 'd':cout<<"\b \b"; x++; pasos++; break;
			//MOVIMIENTO CON FLECHAS
			case char(72):cout<<"\b \b"; y--; pasos++; break;
			case char(80):cout<<"\b \b"; y++; pasos++; break;
			case char(75):cout<<"\b \b"; x--; pasos++; break;
			case char(77):cout<<"\b \b"; x++; pasos++; break;
		}
		
		//CICLO PARA LOCALIZAR CADA COORDENADA LLENA
		for (int i = 0; i < 5; i++){
			if(x == xA[i] && y == yA[i]){
				gotoxy(x, y);
				if (numero[i] == numero_actual) {
					contadorPuntos++;
					numero_actual = numero[siguiente_numero];
					siguiente_numero++;
					numero[i] = -1;
				} else if (numero[i] != numero_actual && numero[i] != -1){
					string msm1, msm2, msm3, msm4;
					char continuar;
					
					msm1 = "Fin del Juego :(";
					msm2 = "Aster se comio un numero equivocado :(";
					msm3 = "Desea jugar nuevamente?...";
					msm4 = "presione ENTER para jugar nuevamente o cualquier otra tecla para finalizar :)";
					 
					system("cls");
					gotoxy((120 - msm1.length())/2, 30/2);
					cout<<msm1<<endl;;
					gotoxy((120 - msm2.length())/2, (30/2) + 1);
					cout<<msm2<<endl;
					gotoxy((120 - msm3.length()) / 2, (30/2) + 2);
					cout<<msm3<<endl;
					gotoxy((120 - msm4.length()) / 2, (30/2) + 3);
					cout<<msm4;
					continuar = getch();
					
					switch(continuar){
						case char(13):
							system("cls");
							main();
						break;
						default: exit(1);
					}
					
				}else if (numero[i] == -1){
					continue;
				}
			}
		}
		if(numero[4] == -1){
			pasosAlmacen[0] = pasos;
			puntosAlmacen[0] = contadorPuntos;
			ImprimirResultados(pasosAlmacen);
			Puntos(puntosAlmacen);
			SegundoNivel();
		}

	}	
}

void SegundoNivel(){
	system("cls");
	
	srand(time(NULL));
	
	gotoxy((120 - nivel2.length()) / 2, 2); cout<<nivel2;
	
	bordes();
	
	int xA[10];
	int yA[10];
	int numero[10];
	int contador[10] = {0};
	
	//CICLO PARA GENERAR LOS NUMEROS
	for (int i = 0; i < 10; i++){
		int num = rand() % 10;
		while (contador[num] >= 2) {
            num = rand() % 10;
        }
        contador[num]++;
        
        numero[i] = num;
	}
	
	int orden = sizeof(numero) / sizeof(numero[0]);
	sort(numero, numero + orden);
	

	//CICLO PARA REPARTIR LOS NUMEROS
	for(int ii = 0; ii < 10; ii++){
		xA[ii] = rand() % 110;
		yA[ii] = rand() % 23;
		
		//SPAUN DE NUMEROS DENTRO DEL MAPA (BORDES)
		if((xA[ii] > 10 && xA[ii] < 110) && (yA[ii] >= 4 && yA[ii] < 23)){ 
			gotoxy(xA[ii], yA[ii]);cout<<numero[ii];
		}else{
			if(xA[ii] <= 10){
				xA[ii] = xA[ii] + 10;
				gotoxy(xA[ii], yA[ii]);cout<<numero[ii];
			}
			if(yA[ii] <= 4){
				yA[ii] = yA[ii] + 4;
				gotoxy(xA[ii], yA[ii]);cout<<numero[ii];
			}
			if(xA[ii] >= 110){
				xA[ii] = xA[ii] - 11;
				gotoxy(xA[ii], yA[ii]);cout<<numero[ii];
			}
			if(yA[ii] >= 23){
				yA[ii] = yA[ii] - 9;
				gotoxy(xA[ii], yA[ii]);cout<<numero[ii];
			}
		}
	}
	
	movimientoSegundo(xA, yA, numero);
}
void movimientoSegundo(int xA[], int yA[], int numero[]){
	int x=11, y=11;
	int numero_actual = numero[0];
	int siguiente_numero = 1;
	
	while(opcion!='n'){
		gotoxy(x,y); cout<<aster;
		opcion=getch();
		switch(opcion){
			//MOVIMIENTO CON LETRAS
			case 'w':cout<<"\b \b"; y--; pasos++; break;
			case 's':cout<<"\b \b"; y++; pasos++; break;
			case 'a':cout<<"\b \b"; x--; pasos++; break;
			case 'd':cout<<"\b \b"; x++; pasos++; break;
			//MOVIMIENTO CON FLECHAS
			case char(72):cout<<"\b \b"; y--; pasos++; break;
			case char(80):cout<<"\b \b"; y++; pasos++;break;
			case char(75):cout<<"\b \b"; x--; pasos++; break;
			case char(77):cout<<"\b \b"; x++; pasos++; break;
		}
		
		//CICLO PARA LOCALIZAR CADA COORDENADA LLENA
		for (int i = 0; i < 10; i++){
			if(x == xA[i] && y == yA[i]){
				gotoxy(x, y);
				if (numero[i] == numero_actual) {
					contadorPuntos++;
					numero_actual = numero[siguiente_numero];
					siguiente_numero++;
					numero[i] = -1;
				} else if (numero[i] != numero_actual && numero[i] != -1){
					string msm1, msm2, msm3, msm4;
					char continuar;
					
					msm1 = "Fin del Juego :(";
					msm2 = "Aster se comio un numero equivocado :(";
					msm3 = "Desea jugar nuevamente?...";
					msm4 = "presione ENTER para jugar nuevamente o cualquier otra tecla para finalizar :)";
					 
					system("cls");
					gotoxy((120 - msm1.length())/2, 30/2);
					cout<<msm1<<endl;;
					gotoxy((120 - msm2.length())/2, (30/2) + 1);
					cout<<msm2<<endl;
					gotoxy((120 - msm3.length()) / 2, (30/2) + 2);
					cout<<msm3<<endl;
					gotoxy((120 - msm4.length()) / 2, (30/2) + 3);
					cout<<msm4;
					continuar = getch();
					
					switch(continuar){
						case char(13):
							system("cls");
							main();
						break;
						default: exit(1);
					}
				}else if (numero[i] == -1){
					continue;
				}
			}
		}
		if(numero[9] == -1){
			pasosAlmacen[1] = pasos;
			puntosAlmacen[1] = contadorPuntos;
			ImprimirResultados(pasosAlmacen);
			Puntos(puntosAlmacen);
			TercerNivel();
		}
	}	
}

void TercerNivel(){
	system("cls");
	srand(time(NULL));
	
	gotoxy((120 - nivel3.length()) / 2, 2); cout<<nivel3;
	
	bordes();
	
	int xA[15];
	int yA[15];
	int numero[15];
	int contador[10] = {0};
	
	//CICLO PARA GENERAR LOS NUMEROS
	for (int i = 0; i < 15; i++){
		int num = rand() % 10;
		while (contador[num] >= 2) {
            num = rand() % 10;
        }
        contador[num]++;
        
        numero[i] = num;
	}
	
	int orden = sizeof(numero) / sizeof(numero[0]);
	sort(numero, numero + orden);
	
	
	
	//CICLO PARA REPARTIR LOS NUMEROS
	for(int ii = 0; ii < 15; ii++){
		xA[ii] = rand() % 110;
		yA[ii] = rand() % 23;
		
		//SPAUN DE NUMEROS DENTRO DEL MAPA (BORDES)
		if((xA[ii] > 10 && xA[ii] < 110) && (yA[ii] > 4 && yA[ii] < 23)){ 
			gotoxy(xA[ii], yA[ii]);cout<<numero[ii];
		}else{
			if(xA[ii] <= 10){
				xA[ii] = xA[ii] + 10;
				gotoxy(xA[ii], yA[ii]);cout<<numero[ii];
			}
			if(yA[ii] <= 4){
				yA[ii] = yA[ii] + 4;
				gotoxy(xA[ii], yA[ii]);cout<<numero[ii];
			}
			if(xA[ii] >= 110){
				xA[ii] = xA[ii] - 11;
				gotoxy(xA[ii], yA[ii]);cout<<numero[ii];
			}
			if(yA[ii] >= 23){
				yA[ii] = yA[ii] - 9;
				gotoxy(xA[ii], yA[ii]);cout<<numero[ii];
			}
		}
	}
	movimientoTercero(xA, yA, numero);
}
void movimientoTercero(int xA[], int yA[], int numero[]){
	int x=11, y=11;
	int numero_actual = numero[0];
	int siguiente_numero = 1;
	
	
	while(opcion!='n'){
		gotoxy(x,y); cout<<aster;
		opcion=getch();
		switch(opcion){
			//MOVIMIENTO CON LETRAS
			case 'w':cout<<"\b \b"; y--; pasos++; break;
			case 's':cout<<"\b \b"; y++; pasos++; break;
			case 'a':cout<<"\b \b"; x--; pasos++; break;
			case 'd':cout<<"\b \b"; x++; pasos++; break;
			//MOVIMIENTO CON FLECHAS
			case char(72):cout<<"\b \b"; y--; pasos++; break;
			case char(80):cout<<"\b \b"; y++; pasos++; break;
			case char(75):cout<<"\b \b"; x--; pasos++; break;
			case char(77):cout<<"\b \b"; x++; pasos++; break;
		}
		
		//CICLO PARA LOCALIZAR CADA COORDENADA LLENA
		for (int i = 0; i < 15; i++){
			if(x == xA[i] && y == yA[i]){
				gotoxy(x, y);
				if (numero[i] == numero_actual) {
					contadorPuntos++;
					numero_actual = numero[siguiente_numero];
					siguiente_numero++;
					numero[i] = -1;
				} else if (numero[i] != numero_actual && numero[i] != -1){
					string msm1, msm2, msm3, msm4;
					char continuar;
					
					msm1 = "Fin del Juego :(";
					msm2 = "Aster se comio un numero equivocado :(";
					msm3 = "Desea jugar nuevamente?...";
					msm4 = "presione ENTER para jugar nuevamente o cualquier otra tecla para finalizar :)";
					 
					system("cls");
					gotoxy((120 - msm1.length())/2, 30/2);
					cout<<msm1<<endl;;
					gotoxy((120 - msm2.length())/2, (30/2) + 1);
					cout<<msm2<<endl;
					gotoxy((120 - msm3.length()) / 2, (30/2) + 2);
					cout<<msm3<<endl;
					gotoxy((120 - msm4.length()) / 2, (30/2) + 3);
					cout<<msm4;
					continuar = getch();
					
					switch(continuar){
						case char(13):
							system("cls");
							main();
						break;
						default: exit(1);
					}
				}else if (numero[i] == -1){
					continue;
				}
			}
		}
		if(numero[14] == -1){
			pasosAlmacen[2] = pasos;
			puntosAlmacen[2] = contadorPuntos;
			int suma = ImprimirResultados(pasosAlmacen);
			int sumaP = Puntos(puntosAlmacen);
			resultadosFinalesWin(suma, sumaP);
		}
	}	
}

//CONTEO DE PASOS
int ImprimirResultados(int pasosAlmacen[]){
	int pasosSuma = 0;
	int almacenaje[3] = {0,0,0};
	
	almacenaje[0] = pasosAlmacen[0];
	almacenaje[1] = pasosAlmacen[1];
	almacenaje[2] = pasosAlmacen[2];
	
	for (int p = 0; p < 3; p++){
		pasosSuma += almacenaje[p];
	}
	return pasosSuma;
}

//CONTEO DE PUNTOS
int Puntos(int puntosAlmacen[]){
	int puntosSuma = 0;
	int almacenajeP[3] = {0,0,0};
	
	almacenajeP[0] = puntosAlmacen[0];
	almacenajeP[1] = puntosAlmacen[1];
	almacenajeP[2] = puntosAlmacen[2];
	
	for (int p = 0; p < 3; p++){
		puntosSuma += almacenajeP[p];
	}
	return puntosSuma;
}

//RESULTADO DE LOS TRES NIVELES
void resultadosFinalesWin(int pasosAlmacenados, int puntosAlmacenados){
	system("cls");
	string msm1, msm2, msm3, msm4, msm5, msm6;
	
	msm1 = "Pasos que dio el jugador: ";
	msm2 = "Puntos del jugador: ";
	msm3 = "SU TRAYECTORIA FUE CORTA :)";
	msm4 = "SU TRAYECTORIA FUE ALGO LARGA :|";
	msm5 = "SU TRAYECTORIA FUE MUY LARGA :(";
	msm6 = "Desea juagar otra vez?...presione ENTER o ESC para cerrar";
	
	gotoxy((120 - msm1.length())/2, 30/2);
	cout<<msm1<<pasosAlmacenados<<endl;
	gotoxy((120 - msm2.length())/2, (30/2) + 1);
	cout<<msm2<<puntosAlmacenados<<endl;
	if(pasosAlmacenados < 1500){
		gotoxy((120 - msm3.length())/2, (30/2) + 2);
		cout<<msm3;
	}else if(pasosAlmacenados >= 1500 && pasosAlmacenados <= 2100){
		gotoxy((120 - msm4.length())/2, (30/2) + 3);
		cout<<msm4;
	}else if (pasosAlmacenados > 2100){
		gotoxy((120 - msm5.length())/2, (30/2) + 4);
		cout<<msm5;
	}
	gotoxy((120 - msm6.length())/2, (30/2) + 6);
	cout<<msm6;
	char reiniciar = getch();
	switch (reiniciar){
		case char(13):
			system("cls");
			main();
		break;
		case char(27):
			exit(1);
		break;
	}
	
}

//MAPA
void bordes(){
	for(int i = 10; i < 110; i++){
		gotoxy(i,3); printf("%c",45);//HORIZONTAL
		gotoxy(i,23); printf("%c",45);
	}
	for(int i = 4; i < 23; i++){
		gotoxy(10,i); printf("%c", 179);//VERTICAL
		gotoxy(109,i); printf("%c",179);
	}
	//ESQUINAS
	gotoxy(10,3); printf("%c",201);
	gotoxy(10,23); printf("%c",200);
	gotoxy(109,3); printf("%c",187);
	gotoxy(109,23); printf("%c",188);
}

