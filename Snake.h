#define MAX_X	40
#define MAX_Y	20
#define MAX		MAX_X*MAX_Y
#define left	1
#define right	2
#define up		3
#define down	4
#include "Apple.h"

class Snake{
private: 
	int snakeX[MAX], snakeY[MAX];
	int snakeXo[MAX], snakeYo[MAX];
	int lengthSnake;
	char displaySnake;
	int directionSnake;
public:
	friend class Apple;
	Snake(){
		snakeX[0]		= 5;
		snakeY[0]		= 5;
		lengthSnake		= 1;
		displaySnake	='*';
		directionSnake	= right;
	}
	void initSnake(){
		snakeX[0]		= 5;
		snakeY[0]		= 5;
		lengthSnake		= 1;
		displaySnake	='*';
		directionSnake	= right;
	}

	int *getSnakeX(){
		return this->snakeX;
	}

	int *getSnakeY(){
		return this->snakeY;
	}

	int *getSnakeXo(){
		return this->snakeXo;
	}

	int *getSnakeYo(){
		return this->snakeYo;
	}

	int getLengthSnake(){
		return this->lengthSnake;
	}

	void setDisplaySnake(char newDisplay){
		this->displaySnake = newDisplay;
	}

	char getDisplaySnake(){
		return this->displaySnake;
	}

	void setDirectionSnake(int newDirection){
		this->directionSnake = newDirection;
	}

	int getDirectionSnake(){
		return this->directionSnake;
	}

	bool checkDieSnake(int nextX, int nextY){
		for(int i = 0; i < this->lengthSnake - 2; i++)
			if(nextX == snakeX[i] && nextY == snakeY[i])
				return true;
		if(nextX == 0 || nextX == MAX_X-1 || nextY == 0 || nextY == MAX_Y-1)
			return true;
		if((nextX >= MAX_X/4 && nextX <= (MAX_X - MAX_X/4) && nextY == MAX_Y/4) || (nextY >= MAX_Y/4 && nextY <= (MAX_Y-MAX_Y/4) && nextX == MAX_X/2))
			return true;
		return false;
	}

	void changeDirection(int nextX, int nextY){
		snakeXo[0] = snakeX[0];
		snakeYo[0] = snakeY[0];
		for(int i = 0; i < lengthSnake - 1 ; i++){
			snakeX[i] = snakeX[i+1];
			snakeY[i] = snakeY[i+1];
		}
		snakeX[lengthSnake-1] = nextX;
		snakeY[lengthSnake-1] = nextY;
		if(nextX < 1 && directionSnake == left)
			snakeX[lengthSnake-1] = MAX_X-2;
		if(nextX > MAX_X-2 && directionSnake == right)
			snakeX[lengthSnake-1] = 1;
		if(nextY < 1 && directionSnake == up)
			snakeY[lengthSnake-1] = MAX_Y-2;
		if(nextY > MAX_Y-2 && directionSnake == down)
			snakeY[lengthSnake-1] = 1;
	}

	void upgradeSnake(int addX, int addY){
		snakeX[lengthSnake] = addX;
		snakeY[lengthSnake] = addY;
		lengthSnake++;
	}

	int moveSnake(Apple apple){
		int tempX = snakeX[lengthSnake-1];
		int tempY = snakeY[lengthSnake-1];
		switch(directionSnake){
		case left:
			tempX--;
			break;
		case right:
			tempX++;
			break;
		case up:
			tempY--;
			break;
		case down:
			tempY++;
			break;
		}
		if(checkDieSnake(tempX, tempY)){
			return -1;
		}
		else if(apple.checkEatApple(tempX, tempY)){
			upgradeSnake(tempX, tempY);
			return 0;
		}
		changeDirection(tempX, tempY);
		return 1;
	}
};