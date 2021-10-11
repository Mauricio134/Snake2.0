#include <iostream>
#include <conio.h>

using namespace std;

bool gameOver = false, loose, menu = true, run = true;
const int width{20}, height{20};
int x, y, fruitx, fruity, bx, by, score, vidas;
int tailX[100], tailY[100];
int nTail;
enum eDirection {LEFT, RIGHT, UP, DOWN};
eDirection dir;
char obstaculo[width][height];
char bloques = 219;
int seleccionador;


void Clear();

void Status();

void Presentation();

void Pantalla();

void Loser();

void Keyword();

void Keyword_Gameover();

void Keyword_Menu();

void Direccion();

int main(){
	Status();
	while(run == true){
		while(menu == true){
			Presentation();
			Keyword_Menu();
		}
		while(gameOver == true){
			Pantalla();
			Keyword();
			Direccion();
		}
		while (loose == true){
			Loser();
			Keyword_Gameover();
		}
	}
	return 0;
}

void Status(){
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

void Pantalla(){
	char pantalla[width][height];
	char a;
	char jugador = 'O';
	
	Clear();
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			if (score != 0 && score%20 == 0){
				if (bx == 0){
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
			
			if (i == 0 && j == 0){
				cout << "\033[0;1;37m";
				a = 201;
			}
			else if (i == height - 1 && j == 0){
				cout << "\033[0;1;37m";
				a = 200;
			}
			else if (i == 0 && j == width-1){
				cout << "\033[0;1;37m";
				a = 187;
			}
			else if (i == height-1 && j == width-1){
				cout << "\033[0;1;37m";
				a = 188;
			}
			else if (j == 0 || j == width-1){
				cout << "\033[0;1;37m";
				a = 186;
			}
			else if (i == 0 || i == height-1){
				cout << "\033[0;1;37m";
				a = 205;
			}
			else if (i == y && j == x){
				cout << "\033[0;40;32m";
				a = jugador;
			}
			else if (i == fruity && j == fruitx){
				cout << "\033[0;1;31m";
				a = 162;
			}
			else{
				a = ' ';
			}
			
			for (int k = 0; k < nTail; k++){
				if (tailX[k] == j && tailY[k] == i){
					cout << "\033[0;40;32m";
					a = 'o';
				}
			}
			for (int m = 0; m < height; m++){
				for (int n = 0; n < width; n++){
					if (obstaculo[m][n] == bloques && i == m && j == n){
						cout << "\033[5;1;34m";
						a = bloques;
					}
				}
			}
			pantalla[i][j] = a;
			cout << pantalla[i][j];
		}
		cout << "\n";
	}
	cout << "\033[0;1;37m";
	cout << "VIDAS" << " = " << vidas << endl;
	cout << "\033[0;1;37m";
	cout << "PUNTAJE" << " = " << score;
}


void Keyword(){
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

void Direccion(){
	
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
	
	if (x == fruitx && y == fruity){
		score += 10;
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
	
	if (obstaculo[y][x] == bloques){
		gameOver = false;
		loose = true;
	}
	
	if (x == 0 || x == width-1 || y == 0 || y == height-1){
		vidas--;
		x = width/2;
		y = height/2;
		if (vidas == 0){
			gameOver = false;
			loose = true;
		}
	}
	
	for (int j = 0; j < nTail; j++){
		if (tailX[j] == x && tailY[j] == y){
			gameOver = false;
			loose = true;
		}
	}
}

void Loser(){
	Clear();
	cout << "\033[1;1;31m";
	cout << "\n\n\n\n";
	cout << "================ " << "GAME OVER" << " ==================" << endl;
	cout << "                 " "PUNTAJE: " << score << endl;
	cout << "\n\n";
	cout << "     " << "Presionar [x] para terminar de jugar" << endl;
}

void Keyword_Gameover(){
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

void Presentation(){
	Clear();
	cout << "\033[0;40;32m";
	cout << "\n\n\n\n";
	cout << "================ " << "SNAKE 2.0" << " ==================" << endl;
	cout << "\n\n";
	cout << "     " << "Presionar [p] para empezar a jugar" << endl;
}

void Keyword_Menu(){
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

void Clear(){
	system("cls");
	//cout << "\033[H\033[2J\033[3J";
}