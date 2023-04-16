#include<iostream>
#include<conio.h>
#include<windows.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

void gotoxy(int x, int y);
void movimiento(int xA[], int yA[], int numero[]);
void bordes();
void PrimerNivel();

char opcion;
char aster = '*';

int main(){

	
	//llamado a la funcion de bordes
	bordes();
	
	//funcion primer nivel
	PrimerNivel();
	
	return 0;

}
void gotoxy(int x, int y){
	HANDLE hcon	= GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}

void PrimerNivel(){
	srand(time(NULL));
	int xA[5];
	int yA[5];
	int numero[5];
	
	//for para generar los numeros aleatorios
	for (int i = 0; i < 5; i++){
		numero[i] = rand() % 9;
	}
	
	int orden = sizeof(numero) / sizeof(numero[0]);
	sort(numero, numero + orden);
	
	//for con el array de numero ordenado
	for(int ii = 0; ii < 5; ii++){
		xA[ii] = rand() % 120;
		yA[ii] = rand() % 30;
		
		//para que los numeros esten dentro del cuadro
		if((xA[ii] > 10 && xA[ii] < 110) && (yA[ii] >= 4 && yA[ii] < 23)){ 
			gotoxy(xA[ii], yA[ii]);cout<<numero[ii];
		}else{
			if(xA[ii] <= 10){
				xA[ii] = xA[ii] + 10;
				gotoxy(xA[ii], yA[ii]);cout<<numero[ii];
			}
			if(yA[ii] < 4){
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
	//funcion de movimiento que absorve tres paramatros para localizacion
	movimiento(xA, yA, numero);
}

//funcion movimiento
void movimiento(int xA[], int yA[], int numero[]){
	int x=11, y=11;
	int numero_actual = numero[0];
	int siguiente_numero = 1;
	
	// Mostrar el primer número que se debe recolectar
	gotoxy(0, 0);
	cout << "Recolecta el numero: " << numero_actual << endl;
	
	while(opcion!='n'){
		gotoxy(x,y); cout<<aster;
		opcion=getch();
		switch(opcion){
			//se puede mover con las letras
			case 'w':cout<<"\b \b"; y--; break;
			case 's':cout<<"\b \b"; y++; break;
			case 'a':cout<<"\b \b"; x--; break;
			case 'd':cout<<"\b \b"; x++; break;
			//se puede mover con las flechas
			case char(72):cout<<"\b \b"; y--; break;
			case char(80):cout<<"\b \b"; y++; break;
			case char(75):cout<<"\b \b"; x--; break;
			case char(77):cout<<"\b \b"; x++; break;
		}
		
		// for para localizar la coordenada y numero que se almacena
		for (int i = 0; i < 5; i++){
			if(x == xA[i] && y == yA[i]){
				gotoxy(x, y);
				if (numero[i] == numero_actual ) {
					cout << "El numero es correcto";
					numero_actual = numero[siguiente_numero];
					siguiente_numero++;
					gotoxy(0, 0);
					cout << "Recolecta el numero: " << numero_actual << endl;
				} else {
					cout << "El numero no es correcto";
				}
			}
		}
	}	
}

//funcion que dibuja el mapa
void bordes(){
	for(int i = 10; i < 110; i++){
		gotoxy(i,3); printf("%c",45);//horizontal
		gotoxy(i,23); printf("%c",45);
	}
	for(int i = 4; i < 23; i++){
		gotoxy(10,i); printf("%c", 179);// vertical
		gotoxy(109,i); printf("%c",179);
	}
	//esquinas
	gotoxy(10,3); printf("%c",201);
	gotoxy(10,23); printf("%c",200);
	gotoxy(109,3); printf("%c",187);
	gotoxy(109,23); printf("%c",188);
}

