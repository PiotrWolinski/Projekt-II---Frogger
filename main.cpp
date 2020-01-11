#include "main.h"

extern "C" {
#include"SDL2-2.0.10/include/SDL.h"
#include"SDL2-2.0.10/include/SDL_main.h"
}

#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char** argv) {
	srand(time(NULL));
	int t1, t2, frames, rc, msDelta, msTime, secCounter;
	double delta, worldTime, fpsTimer, fps;
	SDL_Event event;
	SDL_Surface* screen, * charset;
	SDL_Surface* map;
	SDL_Surface* frog;
	SDL_Surface* log1, * log2;
	SDL_Surface* turtle1, * turtle2;
	SDL_Surface* car1, * car2, * car1r, * car2r, * truck;
	SDL_Texture* scrtex;
	SDL_Window* window;
	SDL_Renderer* renderer;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
	}

	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
		&window, &renderer);
	if (rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
	};

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "Frogger");

	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		SCREEN_WIDTH, SCREEN_HEIGHT);

	charset = SDL_LoadBMP("cs8x8.bmp");
	if (charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	}

	SDL_SetColorKey(charset, true, 0x000000);

	map = SDL_LoadBMP("board.bmp");
	if (map == NULL) {
		printf("SDL_LoadBMP(board.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	}

	frog = SDL_LoadBMP("frog.bmp");
	if (frog == NULL) {
		printf("SDL_LoadBMP(frog.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	}

	log1 = SDL_LoadBMP("log1.bmp");
	if (log1 == NULL) {
		printf("SDL_LoadBMP(log1.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	}

	log2 = SDL_LoadBMP("log2.bmp");
	if (log2 == NULL) {
		printf("SDL_LoadBMP(log2.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	}

	turtle1 = SDL_LoadBMP("turtle1.bmp");
	if (turtle1 == NULL) {
		printf("SDL_LoadBMP(turtle1.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	}

	turtle2 = SDL_LoadBMP("turtle2.bmp");
	if (turtle2 == NULL) {
		printf("SDL_LoadBMP(turtle2.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	}

	car1 = SDL_LoadBMP("car1.bmp");
	if (car1 == NULL) {
		printf("SDL_LoadBMP(car1.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	}

	car1r = SDL_LoadBMP("car1r.bmp");
	if (car1r == NULL) {
		printf("SDL_LoadBMP(car1r.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	}

	car2 = SDL_LoadBMP("car2.bmp");
	if (car2 == NULL) {
		printf("SDL_LoadBMP(car2.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	}

	car2r = SDL_LoadBMP("car2r.bmp");
	if (car2r == NULL) {
		printf("SDL_LoadBMP(car2r.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	}

	truck = SDL_LoadBMP("truck.bmp");
	if (truck == NULL) {
		printf("SDL_LoadBMP(truck.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	}

	char text[128];
	int czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int zielony = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	int czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	int niebieski = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);
	int bialy = SDL_MapRGB(screen->format, 255, 255, 255);

	t1 = SDL_GetTicks();  //GetTicks zwraca 32bitowom reprezentacle liczbowa czasu, ktory uplynal od zainicjowania biblioteki SDL

	frames = 0;
	fpsTimer = 0;
	fps = 0;
	worldTime = 0;
	msDelta = 0;
	msTime = 0;
	secCounter = 0;

	frogType* frogger = new frogType;

	logType* logRow1 = new logType[SHORT_LOG_NUMBER]; //12 zamienie na stala (define)
	logType* logRow2 = new logType[LONG_LOG_NUMBER];
	logType* logRow3 = new logType[SHORT_LOG_NUMBER];

	turtleType1* turtleRow1 = new turtleType1[LONG_TURTLE_NUMBER];
	turtleType2* turtleRow2 = new turtleType2[SHORT_TURTLE_NUMBER];

	carType1* carRow1 = new carType1[CAR_NUMBER];
	carType2* carRow2 = new carType2[CAR_NUMBER];
	carType1* carRow3 = new carType1[CAR_NUMBER];
	carType2* carRow4 = new carType2[CAR_NUMBER];
	truckType* carRow5 = new truckType[TRUCK_NUMBER]; //zamienie na define to wszystko

	gameType* game = new gameType;

	screenType* gameScreen = new screenType;

	int frogArray[5] = {};

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

	int maxY = SCREEN_HEIGHT;

	//tutaj zaczyna sie glowna petla rozgrywki
	while (!quit) {
		if (menu)
		{
			if (gameCounter > 0)
			{
				win = 0;
				frogger = new frogType;
			}

			char option1[128];
			char option2[128];

			SDL_RenderClear(renderer);

			SDL_FillRect(screen, NULL, czarny);
			DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, SCREEN_HEIGHT - 8, czarny, czarny);
			sprintf(text, "MENU");
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, SCREEN_HEIGHT / 2, text, charset);

			if (gameCounter > 0)
			{
				char option3[128];
				sprintf(option3, "Play again - press 1");
				DrawString(screen, screen->w / 2 - strlen(option3) * 8 / 2, SCREEN_HEIGHT / 2 + 12, option3, charset);
			}
			else
			{
				sprintf(option1, "Play Frogger - press 1");
				DrawString(screen, screen->w / 2 - strlen(option1) * 8 / 2, SCREEN_HEIGHT / 2 + 12, option1, charset);
			}

			sprintf(option2, "Exit - press 2");
			DrawString(screen, screen->w / 2 - strlen(option2) * 8 / 2, SCREEN_HEIGHT / 2 + 24, option2, charset);

			if (score)
			{
				sprintf(text, "Last score:  %d", score);
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, SCREEN_HEIGHT / 2 + 36, text, charset);
			}

			SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
			SDL_RenderCopy(renderer, scrtex, NULL, NULL);
			SDL_RenderPresent(renderer);

			t1 = SDL_GetTicks();

			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_2)
					{
						quit = 1;
					}
					else if (event.key.keysym.sym == SDLK_1)
					{
						for (int i = 0; i < 5; i++)
						{
							frogArray[i] = 0;
						}
						win = 0;
						gameTime = 0;
						docksLeft = 5;
						worldTime = 0;
						lifes = LIFES_NUMBER;
						maxY = SCREEN_HEIGHT;
						score = 0;
						menu = 0;
					}
					break;
				case SDL_QUIT:
					quit = 1;
					break;
				};
			};
		}
		else if (pause % 2 == 0 && eog == 0 && menu == 0)
		{
			gameCounter++;
			t2 = SDL_GetTicks();

			resetCollisions(frogger);
			// w tym momencie t2-t1 to czas w milisekundach,
			// jaki uplyna³ od ostatniego narysowania ekranu
			// delta to ten sam czas w sekundach
			delta = (t2 - t1) * 0.001;
			msDelta = t2 - t1;
			t1 = t2;
			msTime += msDelta;
			worldTime += delta;
			gameTime += delta;

			checkLog1Collision(frogger, game->logCounter1, logRow1); //pozmieniam te funkcje wspolne dla rzedow, zeby dzialaly

			checkLog2Collision(frogger, game->logCounter2, logRow2); //wystarczy dodac odpowiedniego define'a do parametrow 

			checkLog3Collision(frogger, game->logCounter3, logRow3);

			checkTurtleCollision1(frogger, game->turtleCounter1, turtleRow1);

			checkTurtleCollision2(frogger, game->turtleCounter2, turtleRow2);

			checkCarCollisionRight(frogger, game->carCounter1, carRow1, CAR_ROW_1); //zrobie z tego jedna duza funkcje, ktora bedzie sprawdzala
																				//kolizje dla wszystkich samochodow
			checkCarCollisionLeft(frogger, game->carCounter2, carRow2, CAR_ROW_2);

			checkCarCollisionRight(frogger, game->carCounter3, carRow3, CAR_ROW_3);

			checkCarCollisionLeft(frogger, game->carCounter4, carRow4, CAR_ROW_4);

			checkTruckCollision(frogger, game->carCounter5, carRow5);

			switch (frogger->positionY) //funkcje movefrog zmienie tak, zeby obslugiwala calego tego switcha
			{
			case (TURTLE_ROW_1):
			{
				moveFrog(frogger, (-1) * turtleRow1[0].speed, delta);
				break;
			}
			case (LOG_ROW_1):
			{
				moveFrog(frogger, logRow1[0].speed1, delta);
				break;
			}
			case (LOG_ROW_2):
			{
				moveFrog(frogger, logRow2[0].speed2, delta);
				break;
			}
			case (TURTLE_ROW_2):
			{
				moveFrog(frogger, (-1) * turtleRow2[0].speed, delta);
				break;
			}
			case (LOG_ROW_3):
			{
				moveFrog(frogger, logRow3[0].speed3, delta);
				break;
			}
			}

			gameScreen->carScreen1 = checkScreen(game->screenPositionC1, game->carCounter1, carRow1[0].speed1, delta, CAR_TYPE);
			gameScreen->carScreen2 = checkScreen(game->screenPositionC2, game->carCounter2, carRow2[0].speed1, delta, CAR_TYPE);
			gameScreen->carScreen3 = checkScreen(game->screenPositionC3, game->carCounter3, carRow3[0].speed2, delta, CAR_TYPE);
			gameScreen->carScreen4 = checkScreen(game->screenPositionC4, game->carCounter4, carRow4[0].speed2, delta, CAR_TYPE);
			gameScreen->carScreen5 = checkScreen(game->screenPositionC5, game->carCounter5, carRow5[0].speed, delta, CAR_TYPE);

			addLog(game->dFromLastLog1, game->logCounter1, logRow1[0].speed1, delta, LOG_ROW_1);

			addLog(game->dFromLastLog2, game->logCounter2, logRow2[0].speed2, delta, LOG_ROW_2);

			addLog(game->dFromLastLog3, game->logCounter3, logRow3[0].speed3, delta, LOG_ROW_3);

			addTurtle(game->dFromLastTurtle1, game->turtleCounter1, turtleRow1[0].speed, delta, TURTLE_ROW_1);

			addTurtle(game->dFromLastTurtle2, game->turtleCounter2, turtleRow2[0].speed, delta, TURTLE_ROW_2);

			addCar(game->dFromLastCar1, game->carCounter1, carRow1[0].speed1, delta, CAR_ROW_1);

			addCar(game->dFromLastCar2, game->carCounter2, carRow2[0].speed1, delta, CAR_ROW_2);

			addCar(game->dFromLastCar3, game->carCounter3, carRow3[0].speed2, delta, CAR_ROW_3);

			addCar(game->dFromLastCar4, game->carCounter4, carRow4[0].speed2, delta, CAR_ROW_4);

			addCar(game->dFromLastCar5, game->carCounter5, carRow5[0].speed, delta, CAR_ROW_5);

			DrawSurface(screen, map,
				SCREEN_WIDTH / 2,
				SCREEN_HEIGHT / 2 + 20);

			for (int y = 0; y < game->logCounter1; y++)
			{
				//tutaj bede podawal numer danego loga z tablicy i przekazywal jego wspolrzedne do funckji
				DrawMoving(screen, log1,
					logRow1[y].positionX / 10,
					LOG_ROW_1 / 10);

				logRow1[y].positionX += logRow1[0].speed1 * delta;
				checkDistance(logRow1[y].positionX, LOG_TYPE);
			}

			for (int y = 0; y < game->logCounter2; y++)
			{
				//tutaj bede podawal numer danego loga z tablicy i przekazywal jego wspolrzedne do funckji
				DrawMoving(screen, log2,
					logRow2[y].positionX / 10,
					LOG_ROW_2 / 10);

				logRow2[y].positionX += logRow2[0].speed2 * delta;
				checkDistance(logRow2[y].positionX, LOG_TYPE);
			}

			for (int y = 0; y < game->turtleCounter1; y++)
			{
				//tutaj bede podawal numer danego loga z tablicy i przekazywal jego wspolrzedne do funckji
				DrawMoving(screen, turtle2,
					turtleRow1[y].positionX / 10,
					TURTLE_ROW_1 / 10);

				turtleRow1[y].positionX -= turtleRow1[0].speed * delta;
				checkDistance(turtleRow1[y].positionX, TURTLE_TYPE);
			}

			for (int y = 0; y < game->turtleCounter2; y++)
			{
				//tutaj bede podawal numer danego loga z tablicy i przekazywal jego wspolrzedne do funckji
				DrawMoving(screen, turtle1,
					turtleRow2[y].positionX / 10,
					TURTLE_ROW_2 / 10);

				turtleRow2[y].positionX -= turtleRow2[0].speed * delta;
				checkDistance(turtleRow2[y].positionX, TURTLE_TYPE);
			}

			for (int y = 0; y < game->logCounter3; y++)
			{
				//tutaj bede podawal numer danego loga z tablicy i przekazywal jego wspolrzedne do funckji
				DrawMoving(screen, log1,
					logRow3[y].positionX / 10,
					LOG_ROW_3 / 10);

				logRow3[y].positionX += logRow3[0].speed3 * delta;
				checkDistance(logRow3[y].positionX, LOG_TYPE);
			}

			for (int y = 0; y < game->carCounter1; y++)
			{
				DrawMoving(screen, car1,
					carRow1[y].positionX / 10,
					CAR_ROW_1 / 10);

				carRow1[y].positionX -= carRow1[0].speed1 * delta;
				checkDistance(carRow1[y].positionX, CAR_TYPE_RIGHT);
			}

			for (int y = 0; y < game->carCounter2; y++)
			{
				//tutaj bede podawal numer danego loga z tablicy i przekazywal jego wspolrzedne do funckji
				DrawMoving(screen, car1r,
					carRow2[y].positionX / 10,
					CAR_ROW_2 / 10);

				carRow2[y].positionX += carRow2[0].speed1 * delta;
				checkDistance(carRow2[y].positionX, CAR_TYPE_LEFT);
			}

			for (int y = 0; y < game->carCounter3; y++)
			{
				//tutaj bede podawal numer danego loga z tablicy i przekazywal jego wspolrzedne do funckji
				DrawMoving(screen, car2,
					carRow3[y].positionX / 10,
					CAR_ROW_3 / 10);

				carRow3[y].positionX -= carRow3[0].speed2 * delta;
				checkDistance(carRow3[y].positionX, CAR_TYPE_RIGHT);
			}

			for (int y = 0; y < game->carCounter4; y++)
			{
				//tutaj bede podawal numer danego loga z tablicy i przekazywal jego wspolrzedne do funckji
				DrawMoving(screen, car2r,
					carRow4[y].positionX / 10,
					CAR_ROW_4 / 10);

				carRow4[y].positionX += carRow4[0].speed2 * delta;
				checkDistance(carRow4[y].positionX, CAR_TYPE_LEFT);
			}

			for (int y = 0; y < game->carCounter5; y++)
			{
				//tutaj bede podawal numer danego loga z tablicy i przekazywal jego wspolrzedne do funckji
				DrawMoving(screen, truck,
					carRow5[y].positionX / 10,
					CAR_ROW_5 / 10);

				carRow5[y].positionX -= carRow5[0].speed * delta;
				checkDistance(carRow5[y].positionX, TRUCK_TYPE);
			}

			for (int i = 0; i < 5; i++)
			{
				if (frogArray[i] != 0)
				{
					DrawSurface(screen, frog,
						frogArray[i],
						FINISH_LINE / 10);
				}
			}

			if ((int)gameTime < 3)
			{
				sprintf(text, "Start za : %d", 3 - (int)gameTime);
				DrawString(screen, screen->w / 2 - strlen(text) / 2 * 8, SCREEN_HEIGHT / 2 + 20, text, charset);
			}

			fpsTimer += delta;
			fpsThing(fpsTimer, fps, frames);

			DrawSurface(screen, frog,
				frogger->positionX / 10,
				frogger->positionY / 10);

			DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, czarny, czarny);

			if ((int)gameTime < 43 && (int)gameTime >= 3)
			{
				DrawRectangle(screen, 16, 16, 100 - 2 * ((int)gameTime - 3), 10, bialy, bialy);
			}
			else if ((int)gameTime < 53 && (int)gameTime >= 3)
			{
				DrawRectangle(screen, 16, 16, 100 - 2 * ((int)gameTime - 3), 10, czerwony, czerwony);
			}

			sprintf(text, "Lifes left: %d", lifes);
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 16, text, charset);

			sprintf(text, "Score: %d", score);
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2 + 100, 16, text, charset);

			SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
			SDL_RenderCopy(renderer, scrtex, NULL, NULL);
			SDL_RenderPresent(renderer);

			if (ifWin(*frogger, win) && docksLeft != 0)
			{
				win = 0;
				if (docksLeft != 0)
				{
					if (!checkDock(frogger, frogArray, score, docksLeft, gameTime))
					{
						lifes--;
					}
					gameTime = 0;
					frogger = new frogType;
					maxY = SCREEN_HEIGHT;
				}
			}

			if (docksLeft == 0)
			{
				win = 1;
				menu = 1;
				SDL_Delay(1000);

				SDL_RenderClear(renderer);

				SDL_FillRect(screen, NULL, czarny);
				DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, SCREEN_HEIGHT - 8, czarny, czarny);
				sprintf(text, "YOU WON!");
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, SCREEN_HEIGHT / 2, text, charset);

				SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
				SDL_RenderCopy(renderer, scrtex, NULL, NULL);
				SDL_RenderPresent(renderer);

				SDL_Delay(2000);
			}

			if (checkTime(gameTime))
			{
				gameTime = 0;
				lifes--;
				frogger = new frogType;
			}

			//sprawdza czy gracz powinien umrzec, jak wypadnie poza pole
			if (((ifInWater(*frogger, menu) || ifHitByCar(*frogger, menu)) && !win) && checkLifes(lifes))
			{
				gameTime = 0;
				menu = 0;
				lifes--;
				frogger = new frogType;
				maxY = SCREEN_HEIGHT;
			}

			if (!checkLifes(lifes))
			{
				menu = 1;
				SDL_Delay(1000);

				SDL_RenderClear(renderer);

				SDL_FillRect(screen, NULL, czarny);
				DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, SCREEN_HEIGHT - 8, czarny, czarny);
				sprintf(text, "GAME OVER");
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, SCREEN_HEIGHT / 2, text, charset);

				SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
				SDL_RenderCopy(renderer, scrtex, NULL, NULL);
				SDL_RenderPresent(renderer);

				SDL_Delay(2000);
			}
		}

		else if (pause % 2 == 1)
		{
			t1 = SDL_GetTicks();
			t2 = SDL_GetTicks();
		}
		else if (eog == 1)
		{
			t1 = SDL_GetTicks();

			sprintf(text, "Exit? Y/N");
			DrawRectangle(screen, SCREEN_WIDTH / 2 - strlen(text) * 8 / 2 - 10, SCREEN_HEIGHT / 2 - 20, strlen(text) * 8 + 20, 40, czarny, czarny);

			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, SCREEN_HEIGHT / 2, text, charset);

			SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
			SDL_RenderCopy(renderer, scrtex, NULL, NULL);
			SDL_RenderPresent(renderer);

			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_y)
					{
						eog = 0;
						menu = 1;
					}
					else if (event.key.keysym.sym == SDLK_n)
					{
						eog = 0;
					}
					break;
				case SDL_QUIT:
					quit = 1;
					break;
				};
			};
		}
		// obs³uga zdarzeñ
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
				else if (event.key.keysym.sym == SDLK_q && pause % 2 == 0)
				{
					eog = 1;
				}
				else if (event.key.keysym.sym == SDLK_p)
				{
					pause++;
				}
				else if (event.key.keysym.sym == SDLK_UP && pause % 2 == 0 && (int)gameTime >= 3)
				{
					if (frogger->positionY < 1100)
					{
						break;
					}
					frogger->positionY -= 430;
					if (frogger->positionY / 10 < maxY && frogger->positionY > FINISH_LINE)
					{
						score += 10;
						maxY = frogger->positionY / 10;
					}
				}
				else if (event.key.keysym.sym == SDLK_DOWN && pause % 2 == 0 && (int)gameTime >= 3)
				{
					if (frogger->positionY > SCREEN_HEIGHT * 10 - 300)
					{
						break;
					}
					frogger->positionY += 430;
				}
				else if (event.key.keysym.sym == SDLK_RIGHT && pause % 2 == 0 && (int)gameTime >= 3)
				{
					if (frogger->positionX > SCREEN_WIDTH * 10 - 300)
					{
						break;
					}
					frogger->positionX += 400;
				}
				else if (event.key.keysym.sym == SDLK_LEFT && pause % 2 == 0 && (int)gameTime >= 3)
				{
					if (frogger->positionX < 300)
					{
						break;
					}
					frogger->positionX -= 400;
				}
				break;

			case SDL_QUIT:
				quit = 1;
				break;
			};
		};
		frames++;
	};

	// zwolnienie powierzchni / freeing all surfaces
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
};
