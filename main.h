#pragma once

#include<math.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>

extern "C" {
#include"SDL2-2.0.10/include/SDL.h"
#include"SDL2-2.0.10/include/SDL_main.h"
}

#ifdef __cplusplus
extern "C"
#endif

#define SCREEN_WIDTH	520
#define SCREEN_HEIGHT	630

#define FINISH_LINE 940

#define RIVER SCREEN_HEIGHT * 10 / 2
#define ROAD SCREEN_HEIGHT * 10 - 400

#define DOCK_1_LEFT 200 
#define DOCK_1_RIGHT 600

#define DOCK_2_LEFT 1300
#define DOCK_2_RIGHT 1700

#define DOCK_3_LEFT 2400 
#define DOCK_3_RIGHT 2800

#define DOCK_4_LEFT 3500
#define DOCK_4_RIGHT 3900

#define DOCK_5_LEFT 4600 
#define DOCK_5_RIGHT 5000

#define LOG_ROW_3 1370
#define TURTLE_ROW_2 1800
#define LOG_ROW_2 2230
#define LOG_ROW_1 2660
#define TURTLE_ROW_1 3090

#define CAR_ROW_5 3950
#define CAR_ROW_4 4380
#define CAR_ROW_3 4810
#define CAR_ROW_2 5240
#define CAR_ROW_1 5670

#define FROG_START_POSITION_X (rand() % 13) * 400 + 200
#define FROG_START_POSITION_Y SCREEN_HEIGHT * 10 - 200

#define LOG_1_SPAWN_RATE 350
#define LOG_2_SPAWN_RATE 400
#define LOG_3_SPAWN_RATE 500
#define TURTLE_1_SPAWN_RATE 400
#define TURTLE_2_SPAWN_RATE 360

#define CAR_1_SPAWN_RATE 400
#define CAR_2_SPAWN_RATE 470
#define CAR_3_SPAWN_RATE 530
#define CAR_4_SPAWN_RATE 600
#define CAR_5_SPAWN_RATE 500

#define TURTLE_TYPE 2
#define LOG_TYPE 1
#define CAR_TYPE_RIGHT 3
#define CAR_TYPE_LEFT 1
#define TRUCK_TYPE 4
#define CAR_TYPE 1

#define LIFES_NUMBER 5

#define LONG_LOG_NUMBER 4
#define SHORT_LOG_NUMBER 6
#define SHORT_TURTLE_NUMBER 4
#define LONG_TURTLE_NUMBER 3
#define CAR_NUMBER 5
#define TRUCK_NUMBER 4

struct logType {
	int positionX;		
	int speed1 = 1600;
	int speed2 = 1000;
	int speed3 = 1300;
	logType()
	{
		positionX = 0;
	}
};

struct turtleType2 {
	int positionX;
	int turtleType = 1;
	int speed = 850;
	turtleType2()
	{
		positionX = SCREEN_WIDTH * 10 + 1200;
	}
};

struct turtleType1 {
	int positionX;
	int turtleType = 2;
	int speed = 800;
	turtleType1()
	{
		positionX = SCREEN_WIDTH * 10 + 1600;
	}
};

struct carType1 {
	int positionX;
	int speed1 = 1200;
	int speed2 = 1500;
	carType1()
	{
		positionX = SCREEN_WIDTH * 10 + 400;
	}
};

struct carType2 {
	int positionX;
	int speed1 = 1300;  //zrobie define
	int speed2 = 1100;
	carType2()
	{
		positionX = 0;
	}
};

struct truckType {
	int positionX;;
	int speed = 1000;
	truckType()
	{
		positionX = SCREEN_WIDTH * 10 + 800;
	}
};

struct frogType {
	int positionX;
	int positionY;
	int logCollision;
	int carCollision;
	frogType()
	{
		positionX = FROG_START_POSITION_X;
		positionY = FROG_START_POSITION_Y;
		logCollision = 0;
		carCollision = 0;
	}
};

struct gameType {
	int logCounter1 = 0;
	int dFromLastLog1 = 0;
	int screenPositionL1 = 0;

	int logCounter2 = 0;
	int dFromLastLog2 = 0;
	int screenPositionL2 = 0;

	int logCounter3 = 0;
	int dFromLastLog3 = 0;
	int screenPositionL3 = 0;

	int turtleCounter1 = 0;
	int dFromLastTurtle1 = 0;
	int screenPositionT1 = 0;

	int turtleCounter2 = 0;
	int dFromLastTurtle2 = 0;
	int screenPositionT2 = 0;

	int carCounter1 = 0;
	int dFromLastCar1 = 0;
	int screenPositionC1 = 0; 

	int carCounter2 = 0;
	int dFromLastCar2 = 0;
	int screenPositionC2 = 0;

	int carCounter3 = 0;
	int dFromLastCar3 = 0;
	int screenPositionC3 = 0;

	int carCounter4 = 0;
	int dFromLastCar4 = 0;
	int screenPositionC4 = 0;

	int carCounter5 = 0;
	int dFromLastCar5 = 0;
	int screenPositionC5 = 0;

	int mainScreen = 0;
};

struct gameInfoType {
	int win = 0;
	int quit = 0;
	int pause = 0;
	int eog = 0; //end of game
	int menu = 1;
	int gameCounter = 0;
	int lifes = LIFES_NUMBER;
	int docksLeft = 5;
	double gameTime = 0;
	int score = 0;
};

struct screenType {
	int logscreen1 = 0;
	int logscreen2 = 0;
	int logscreen3 = 0;
	int turtleScreen1 = 0;
	int turtleScreen2 = 0;
	int carScreen1 = 0;
	int carScreen2 = 0;
	int carScreen3 = 0;
	int carScreen4 = 0;
	int carScreen5 = 0;
};

void resetCollisions(frogType* frogger);

void checkDistance(int& distance, int type);

int ifWin(frogType& frogger, int& win);

int ifInWater(frogType& frogger, int& menu);

int ifHitByCar(frogType& frogger, int& menu);

void checkCarCollisionRight(frogType* frogger, int counter, carType1* car, int row);

void checkCarCollisionLeft(frogType* frogger, int counter, carType2* car, int row);

void checkTruckCollision(frogType* frogger, int counter, truckType* truck);

void checkLog1Collision(frogType* frogger, int counter, logType* row);

void checkLog2Collision(frogType* frogger, int counter, logType* row);

void checkLog3Collision(frogType* frogger, int counter, logType* row);

void checkTurtleCollision1(frogType* frogger, int counter, turtleType1* row);

void checkTurtleCollision2(frogType* frogger, int counter, turtleType2* row);

void addLog(int& dFromLast, int& counter,  int speed, double delta, int row);

void addTurtle(int& dFromLast, int& counter, int speed, double delta, int row);

void addCar(int& dFromLast, int& counter, int speed, double delta, int row);

void moveFrog(frogType* frogger, int speed, double delta);

void fpsThing(double& timer, double& fps, int& frames);

int checkScreen(int& screen, int counter, int speed, double delta, int type);

int checkTime(double time);

int checkLifes(int lifes);

int checkDock(frogType* frogger, int* frogArray, int& score, int& docksLeft, int gameTime);

void DrawString(SDL_Surface* screen, int x, int y, const char* text,
	SDL_Surface* charset);

void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y);

void DrawMoving(SDL_Surface* screen, SDL_Surface* sprite, int x, int y);

void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color);

void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color);

void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k,
	Uint32 outlineColor, Uint32 fillColor);