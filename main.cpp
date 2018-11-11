#include<iostream>
#include<ctime>
#include<Windows.h>
#include"Snake.h"
//#include"Utility.h"
#include<conio.h>
using namespace std;
#define LEFT	VK_LEFT
#define RIGHT	VK_RIGHT
#define UP		VK_UP
#define	DOWN	VK_DOWN
#define ESC		VK_ESCAPE
Snake snake;
Apple apple;

void gotoxy(short x,short y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = { x,y};
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}

void drawMap(){
	for(int x = 0; x < MAX_X; x++){
		gotoxy(x, 0);
		cout<<"#";
		gotoxy(x, MAX_Y-1);
		cout<<"#";
	}
	for(int y = 0; y < MAX_Y; y++){
		gotoxy(0, y);
		cout<<"#";
		gotoxy(MAX_X-1, y);
		cout<<"#";
	}
	for(int x = MAX_X/4; x < (MAX_X - MAX_X/4); x++){
		gotoxy(x, MAX_Y/4);
		cout<<"#";
	}
	for(int y = MAX_Y/4; y < (MAX_Y - MAX_Y/4); y++){
		gotoxy(MAX_X/2, y);
		cout<<"#";
	}

}

void drawSnake(){
	for(int i = 0; i < snake.getLengthSnake(); i++){
		gotoxy(snake.getSnakeX()[i], snake.getSnakeY()[i]);
		cout<<snake.getDisplaySnake();
	}
	gotoxy(snake.getSnakeXo()[0], snake.getSnakeYo()[0]);
	cout<<" ";
}

void drawApple(){
	gotoxy(apple.getAppleX(), apple.getAppleY());
	cout<<apple.getDisplayApple();
}

bool checkKey(int key){
	return GetAsyncKeyState(key);
}

bool endGame = false;
void waitKey(){
	if(checkKey(LEFT) && snake.getDirectionSnake() != right)
		snake.setDirectionSnake(left);
	if(checkKey(RIGHT) && snake.getDirectionSnake() != left)
		snake.setDirectionSnake(right);
	if(checkKey(UP) && snake.getDirectionSnake() != down)
		snake.setDirectionSnake(up);
	if(checkKey(DOWN) && snake.getDirectionSnake() != up)
		snake.setDirectionSnake(down);
	if(checkKey(ESC))
		endGame = true;
}

int ranX;
int ranY;

bool conditionApple(int x, int y){
	if((x >= MAX_X/4 && x <= (MAX_X - MAX_X/4) && y == MAX_Y/4) || (y >= MAX_Y/4 && y <= (MAX_Y-MAX_Y/4) && x == MAX_X/2) || x == 0 || x == MAX_X-1 || y == 0 || y == MAX_Y-1)
		return true;
	for(int i = 0; i < snake.getLengthSnake(); i++)
		if(x == snake.getSnakeX()[i] && y == snake.getSnakeY()[i])
			return true;
	return false;
}

void randomApple(){
	while(1){
	srand(time(NULL));
	ranX = rand() % (MAX_X-3) + 1;
	ranY = rand() % (MAX_Y-3) + 1;
	if(!conditionApple(ranX, ranY))
		break;
	}
	apple.setAppleX(ranX);
	apple.setAppleY(ranY);
}

void menu(){
	system("cls");
	cout<<"<1>- Play game\n";
	cout<<"<2>- Exit\n";
}

void playgame(){
	int value;
	system("cls");
	endGame = false;
	snake.initSnake();
	apple.initApple();
	while(!endGame){
			drawMap();
			drawSnake();
			drawApple();
			value = snake.moveSnake(apple);
			waitKey();
			if(value == -1){
				endGame = true;
			}
			else if(value == 0){
				randomApple();
			}
			else if(value == 1){
			}
			Sleep(200);
		}
	getch();
}

void main(){
	int Op;
	while(1){
		menu();
		cout<<"Your choice: ";
		cin>>Op;
		switch(Op){
		case 1: 
			playgame();
			break;
		case 2:
			return;
		}
		
	}
}