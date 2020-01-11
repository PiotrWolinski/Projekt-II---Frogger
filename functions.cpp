#include "main.h"
#define _USE_MATH_DEFINES
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

//resetuje kolizje dla froggera
void resetCollisions(frogType* frogger)
{
	frogger->carCollision = 0;
	frogger->logCollision = 0;
}

//sprawdza czy dana wspolrzedna x-owa nie wyszla poza szerokosc dwoch ekranow
void checkDistance(int& distance, int type)
{
	switch (type)
	{
	case (1):
	{
		if (distance >= SCREEN_WIDTH * 10 * 2)
		{
			distance = 0;
		}
		break;
	}
	case (2):
	{
		if (distance <= 0)
		{
			distance = SCREEN_WIDTH * 10 * 2 + 1600;
		}
		break;
	}
	case (3):
	{
		if (distance <= 0)
		{
			distance = SCREEN_WIDTH * 10 * 2 + 400;
		}
		break;
	}
	case (4):
	{
		if (distance <= 0)
		{
			distance = SCREEN_WIDTH * 10 * 2 + 800;
		}
		break;
	}
	}
}

//sprawdza czy gracz zmiescil sie w dockach
int ifWin(frogType& frogger, int& win)
{
	if (frogger.positionY == FINISH_LINE)
	{
		if (frogger.positionX > DOCK_1_LEFT&& frogger.positionX < DOCK_1_RIGHT ||
			frogger.positionX > DOCK_2_LEFT&& frogger.positionX < DOCK_2_RIGHT ||
			frogger.positionX > DOCK_3_LEFT&& frogger.positionX < DOCK_3_RIGHT ||
			frogger.positionX > DOCK_4_LEFT&& frogger.positionX < DOCK_4_RIGHT ||
			frogger.positionX > DOCK_5_LEFT&& frogger.positionX < DOCK_5_RIGHT
			)
		{
			win = 1;
			return 1;
		}
	}
	return 0;
}

//sprawdza czy gracz wpadl do wody
int ifInWater(frogType& frogger)
{
	if (frogger.logCollision == 0 && frogger.positionY < RIVER &&
		frogger.positionY >= FINISH_LINE ||
		frogger.positionX > SCREEN_WIDTH * 10 ||
		frogger.positionX < 0
		)
	{
		return 1;
	}
	return 0;
}

//sprawadza czy gracz zostal przejechany
int ifHitByCar(frogType& frogger)
{
	if (frogger.carCollision == 1 && frogger.positionY > RIVER&&
		frogger.positionY < FROG_START_POSITION_Y)
	{
		return 1;
	}
	return 0;
}

//sprawdza kolizje dla samochodow jadacych z prawej
void checkCarCollisionRight(frogType* frogger, int counter, carType1* car, int row)
{
	for (int i = 0; i < counter; i++)
	{
		if (frogger->positionX + 200 >= car[i].positionX - 300 &&
			frogger->positionX - 200 <= car[i].positionX - 50 &&
			frogger->positionY == row)
		{
			frogger->carCollision = 1;
			break;
		}
	}
}

//sprawdza kolizje dla samochodow jadacych z lewej
void checkCarCollisionLeft(frogType* frogger, int counter, carType2* car, int row)
{
	for (int i = 0; i < counter; i++)
	{
		if (frogger->positionX + 200 >= car[i].positionX - 300 &&
			frogger->positionX - 200 <= car[i].positionX - 50 &&
			frogger->positionY == row)
		{
			frogger->carCollision = 1;
			break;
		}
	}
}

//sprawdza kolizje dla ciezarowki
void checkTruckCollision(frogType* frogger, int counter, truckType* truck)
{
	for (int i = 0; i < counter; i++)
	{
		if (frogger->positionX + 200 >= truck[i].positionX - 700 &&
			frogger->positionX - 200 <= truck[i].positionX - 50 &&
			frogger->positionY == CAR_ROW_5)
		{
			frogger->carCollision = 1;
			break;
		}
	}
}

//sprawdza kolizje dla pni
void checkLogCollision(frogType* frogger, int counter, logType* row, int rowNumber)
{
	int length = 1200;
	if (rowNumber == LOG_ROW_2)
	{
		length = 1600;
	}
	for (int x = 0; x < counter; x++)
	{
		if (frogger->positionX < row[x].positionX &&
			frogger->positionX > row[x].positionX - length &&
			frogger->positionY == rowNumber)
		{
			frogger->logCollision = 1;
			break;
		}
	}
}

//sprawdza kolizje dla zolwi
void checkTurtleCollision(frogType* frogger, int counter, turtleType* row, int rowNumber)
{
	int length = (rowNumber == TURTLE_ROW_1) ? 1600 : 1200;
	if (rowNumber == TURTLE_ROW_1)
	{
		for (int x = 0; x < counter; x++)
		{
			if (frogger->positionX < row[x].positionX1 &&
				frogger->positionX > row[x].positionX1 - length &&
				frogger->positionY == rowNumber)
			{
				frogger->logCollision = 1;
				break;
			}
		}
	}
	else
	{
		for (int x = 0; x < counter; x++)
		{
			if (frogger->positionX < row[x].positionX2 &&
				frogger->positionX > row[x].positionX2 - length &&
				frogger->positionY == rowNumber)
			{
				frogger->logCollision = 1;
				break;
			}
		}
	}
	
}

//dodaje kolejny pien do tablicy, jesli jest to mozliwe
void addLog(int& dFromLast, int& counter,  int speed, double delta, int row)
{
	int distance = 0;
	int limit = 0;
	switch (row)
	{
	case (LOG_ROW_1):
	{
		distance = -1200;
		limit = 5;
		break;
	}
	case (LOG_ROW_2):
	{
		distance = -1600;
		limit = 4;
		break;
	}
	case (LOG_ROW_3):
	{
		distance = -1200;
		limit = 5;
		break;
	}
	}

	if ((dFromLast > 950 && counter < limit) || !counter)
	{
			//w tym miejscu dodaje nowe logi do danego rzedu 
			counter++;
			dFromLast = distance;
	}
	dFromLast += speed * delta;
}

//dodaje kolejnego zolwia do tablicy, jesli jest to mozliwe
void addTurtle(int& dFromLast, int& counter,  int speed, double delta, int row)
{
	int limit = (row == TURTLE_ROW_1)? LONG_TURTLE_NUMBER : SHORT_TURTLE_NUMBER;
	int space = (row == TURTLE_ROW_1) ? 1330 : 880;
	
	if ((dFromLast > space && counter < limit) || !counter)
	{
		++counter;
		dFromLast = 0;
	}
	dFromLast += speed * delta;
}

//dodaje kolejny samochod do tablicy, jesli jest to mozliwe
void addCar(int& dFromLast, int& counter, int speed, double delta, int row)
{
	int space = 1120;
	int distance = (row == CAR_ROW_5) ? -800 : -400;
	int limit = (row == CAR_ROW_5) ? TRUCK_NUMBER : CAR_NUMBER;
	if (row == CAR_ROW_5)
	{
		space = 1820;
	}
	if (row == CAR_ROW_2 || row == CAR_ROW_4)
	{
		space = 1820;
	}

	if ((dFromLast > space && counter < limit) || !counter)
	{
		counter++;
		dFromLast = distance;
	}
	dFromLast += speed * delta;
}

//porusza zabe razem z pniem/zolwiem
void moveFrog(frogType* frogger, int speed, double delta)
{
	if (frogger->logCollision)
	{
		frogger->positionX += speed * delta;
	}
}

//kontroluje fpsy
void fpsThing(double& timer, double& fps, int& frames)
{
	if (timer > 0.5) {
		fps = frames * 2;
		frames = 0;
		timer -= 0.5;
	}
}

//sprawdza czas gry
int checkTime(gameInfoType* info, frogType* frogger)
{
	if ((int)info->gameTime >= 53)
	{
		info->gameTime = 0;
		info->lifes--;
		return 1;
	}
	return 0;
}

//sprawdza zycia gracza
int checkLifes(int lifes)
{
	if (lifes == 0)
	{
		return 0;
	}
	return 1;
}

//zwraca prawde, jesli dock jest wolny i zaba w nim wyladowala
//jesli dock jest zajety, to zwraca 0
int checkDock(frogType* frogger, int* frogArray, gameInfoType* info) 
{
	if (frogger->positionX >= DOCK_1_LEFT && frogger->positionX <= DOCK_1_RIGHT)
	{
		if (frogArray[0] == 0) //podziele na mniejsze funkcje
		{
			info->docksLeft--;
			frogArray[0] = (DOCK_1_LEFT + DOCK_1_RIGHT) / 2 / 10;
			info->score += 50 + (53 - info->gameTime)*10;
			return 1;
		}
		return 0;
	}
	else if (frogger->positionX >= DOCK_2_LEFT && frogger->positionX <= DOCK_2_RIGHT)
	{
		if (frogArray[1] == 0)
		{
			info->docksLeft--;
			frogArray[1] = (DOCK_2_LEFT + DOCK_2_RIGHT) / 2 / 10;
			info->score += 50 + (53 - info->gameTime) * 10;
			return 1;
		}
		return 0;
	}
	else if (frogger->positionX >= DOCK_3_LEFT && frogger->positionX <= DOCK_3_RIGHT)
	{
		if (frogArray[2] == 0)
		{
			info->docksLeft--;
			frogArray[2] = (DOCK_3_LEFT + DOCK_3_RIGHT) / 2 / 10;
			info->score += 50 + (53 - info->gameTime) * 10;
			return 1;
		}
		return 0;
	}
	else if (frogger->positionX >= DOCK_4_LEFT && frogger->positionX <= DOCK_4_RIGHT)
	{
		if (frogArray[3] == 0)
		{
			info->docksLeft--;
			frogArray[3] = (DOCK_4_LEFT + DOCK_4_RIGHT) / 2 / 10;
			info->score += 50 + (53 - info->gameTime) * 10;
			return 1;
		}
		return 0;
	}
	else if (frogger->positionX >= DOCK_5_LEFT && frogger->positionX <= DOCK_5_RIGHT)
	{
		if (frogArray[4] == 0)
		{
			info->docksLeft--;
			frogArray[4] = (DOCK_5_LEFT + DOCK_5_RIGHT) / 2 / 10;
			info->score += 50 + (53 - info->gameTime) * 10;
			return 1;
		}
		return 0;
	}
}

// narysowanie napisu txt na powierzchni screen, zaczynajπc od punktu (x, y)
// charset to bitmapa 128x128 zawierajπca znaki
void DrawString(SDL_Surface* screen, int x, int y, const char* text,
	SDL_Surface* charset) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
	};
};

// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt úrodka obrazka sprite na ekranie
void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
};

//drawSurface, tylko zamieniony, zeby wspolrzedne x, y to srodek prawej krawedzi obrazka
void DrawMoving(SDL_Surface* screen, SDL_Surface* sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x - sprite->w;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
};

// rysowanie pojedynczego pixela
void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
};

// rysowanie linii o d≥ugoúci l w pionie (gdy dx = 0, dy = 1) 
// bπdü poziomie (gdy dx = 1, dy = 0)
void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for (int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};

// rysowanie prostokπta o d≥ugoúci bokÛw l i k
void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k,
	Uint32 outlineColor, Uint32 fillColor) {
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};
