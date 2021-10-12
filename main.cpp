#include <iostream>
#include <conio.h>

using namespace std;

bool gameOver = false, loose, menu = true, run = true;  		//declaración e inicialización de variables booleanas para el bucle while del funcionamiento principal
const int width{20}, height{20}; 								//declaración e inicialización de variables para tamaño de recuadro
int x, y, fruitx, fruity, bx, by, score, vidas; 				// variables generales de funcionamiento
int tailX[100], tailY[100]; 									//arrays para cola (funcionameinto tipo coordenada)
int nTail; 														//variable tamaño de cola
enum eDirection {LEFT, RIGHT, UP, DOWN}; 						//declaración de variables para dirección 
eDirection dir; 												//especificación de enumerador
char obstaculo[width][height]; 									//declaración e inicialización de array obstaculo 
char bloques = 219;												//declaración e inicialización de variable para obstáculo
int delay = 15000; 												//declaración e inicialización de variable delay


void Clear();

void Status();

void Presentation();

void Pantalla();

void Loser();

void Keyword();

void Keyword_Gameover();

void Keyword_Menu();

void Direccion();

void del();

int main(){    
	Status();
	while(run == true){
		while(menu == true){
			Presentation();
			del();
			Keyword_Menu();
		}
		while(gameOver == true){
			Pantalla();
			if (delay != 0){
				del();
			}
			Keyword();
			Direccion();
		}
		while (loose == true){
			Loser();
			del();
			Keyword_Gameover();
		}
	}
	return 0;
}

void Status(){      // Función declaración de variables generales
	gameOver = true;
	x = width/2;
	y = height/2;
	fruitx = rand()%width;
	fruity = rand()%height;
	bx = rand()%(width-1);
	by = rand()%(height-1);
	vidas = 3;
	score = 0;
}

void Pantalla(){    //Función renderizado de bordes y obstaculos 
	char pantalla[width][height];
	char a;
	char jugador = 'O';
	
	Clear();
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			if (score != 0 && score%20 == 0){   // condicional creación de obstaculos cada 20 puntos en score
				if (bx == 0){					//condicional para evitar cruce con margen
					bx++;
				}
				if (by == 0){
					by++;
				}
				if (bx == width-1){
					bx--;
				}
				if (by == height-1){
					by--;
				}
				obstaculo[by][bx] = bloques;
			}
			
			if (i == 0 && j == 0){              //condicional caso esquina superior izquierda
				cout << "\033[0;1;37m";
				a = 201;
			}
			else if (i == height - 1 && j == 0){ //condicional caso esquina inferior izquierda
				cout << "\033[0;1;37m";
				a = 200;
			}
			else if (i == 0 && j == width-1){	//condicional caso esquina inferior derecha
				cout << "\033[0;1;37m";
				a = 187;
			}
			else if (i == height-1 && j == width-1){  //condicional caso esquina inferior derecha
				cout << "\033[0;1;37m";
				a = 188;
			}
			else if (j == 0 || j == width-1){  //condicional caso laterales
				cout << "\033[0;1;37m";
				a = 186;
			}
			else if (i == 0 || i == height-1){ //condicional caso margen superior e inferior
				cout << "\033[0;1;37m";
				a = 205;
			}
			else if (i == y && j == x){  //condicional cabeza serpiente
				cout << "\033[0;40;32m";
				a = jugador;
			}
			else if (i == fruity && j == fruitx){  //condicional fruta
				cout << "\033[0;1;31m";
				a = 162;
			}
			else{
				a = ' ';   	//condicional espacio de juego
			}
			
			for (int k = 0; k < nTail; k++){  	//condicional cola de serpiete
				if (tailX[k] == j && tailY[k] == i){
					cout << "\033[0;40;32m";
					a = 'o';
				}
			}
			for (int m = 0; m < height; m++){ 		//condicional caso de obstaculo (berifica si la posision es igual a bloque, valor otorgado en el primer condicional)
				for (int n = 0; n < width; n++){
					if (obstaculo[m][n] == bloques && i == m && j == n){
						cout << "\033[5;1;34m";
						a = bloques;
					}
				}
			}
			pantalla[i][j] = a;  			//se coloca valor de "a" (de acuerdo a condicionales ) a la posicion del array 
			cout << pantalla[i][j]; 
		}
		cout << "\n";
	}
	cout << "\033[0;1;37m";
	cout << "VIDAS" << " = " << vidas << endl;
	cout << "\033[0;1;37m";
	cout << "PUNTAJE" << " = " << score;
}


void Keyword(){							//Función de verificación de tecla pulsada
	if (_kbhit())
	{
		switch(_getch())
		{
			case 'a':
				dir = LEFT;
				break;
			case 'd':
				dir = RIGHT;
				break;
			case 's':
				dir = DOWN;
				break;
			case 'w':
				dir = UP;
				break;
			case 'x':
				gameOver = false;
				loose = false;
				run = false;
				break;
		}
	}
}

void Direccion(){ 						//Función de movimiento de cola y verificación de colisiones 
	
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	
	for (int i = 1; i < nTail; i++){
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	
	
	
	switch(dir)
	{
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case DOWN:
			y++;
			break;
		case UP:
			y--;
			break;
	}
	
	if (x == fruitx && y == fruity){    	//Condicional colision con comida
		score += 5;
		fruitx = rand()%width;
		fruity = rand()%height;
		
		bx = rand()%(width-1);
		by = rand()%(height-1);
		
		if (fruitx == 0){
			fruitx++;
		}
		if (fruity == 0){
			fruity++;
		}
		if (fruitx == width-1){
			fruitx--;
		}
		if (fruity == height-1){
			fruity--;
		}
		nTail++;
	}
	
	if (obstaculo[y][x] == bloques){		//Condicional colision con obstáculos
		gameOver = false;
		loose = true;
	}
	
	if (x == 0 || x == width-1 || y == 0 || y == height-1){		//Condicional colision con bordes
		vidas--;
		x = width/2;
		y = height/2;
		if (vidas == 0){
			gameOver = false;
			loose = true;
		}
	}
	
	for (int j = 0; j < nTail; j++){					//Condicional colision con cola
		if (tailX[j] == x && tailY[j] == y){
			gameOver = false;
			loose = true;
		}
	}
}

void Loser(){       //Función pantalla de perdida
	Clear();
	cout << "\033[1;1;31m";
	cout << "\n\n\n\n";
	cout << "================ " << "GAME OVER" << " ==================" << endl;
	cout << "                 " "PUNTAJE: " << score << endl;
	cout << "\n\n";
	cout << "     " << "Presionar [x] para terminar de jugar" << endl;
}

void Keyword_Gameover(){		//Función tecla fin de juego
	if (_kbhit())
	{
		switch(_getch())
		{
			case 'x':
				loose = false;
				run = false;
				break;
		}
	}
}

void Presentation(){			//Función pantalla de inicio
	Clear();
	cout << "\033[0;40;32m";
	cout << "\n\n\n\n";
	cout << "================ " << "SNAKE 2.0" << " ==================" << endl;
	cout << "\n\n";
	cout << "     " << "Presionar [p] para empezar a jugar" << endl;
}

void Keyword_Menu(){			//Función tecla inicio de juego
	if (_kbhit())
	{
		switch(_getch())
		{
			case 'p':
				menu = false;
				gameOver = true;
				break;
		}
	}
}

void Clear(){					//Función borrar pantalla de comando (OPCIONAL)
	system("cls");
	//cout << "\033[H\033[2J\033[3J";
}

void del(){
						//Función de delay de pantalla (simula sleep)
	for ( int c = 1 ; c <= delay ; c++ ){
       for ( int d = 1 ; d <= delay ; d++ ){
	   }
	}
	
	if (score%20 == 0){
		delay = delay - 100;
	}
}