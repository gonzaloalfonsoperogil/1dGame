// 1dGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <stdio.h>
#include <windows.h>


#define ESC 27
#define KEY_A 97
#define KEY_D 100
#define KEY_L 108
#define KEY_K 107

int main()
{
	bool end = false;
	int  screenWith = 50;
	const int  initPosPlayer = 20;
	int  posPlayer = initPosPlayer;
	int  posBullet = -1;
	int  posMushroom = -1;
	int  countMushroom = 0;
	int  randomMushroom;
	int  posEnemy = -1;
	int  countEnemy = 0;
	int  randomEnemy;
	int  sideEnemy;
	int  score = 0;
	int  lives = 3;

	printf("\n\n\n\n\n\n\n\n");
	while (!end) {

		// Draw loop
		for (int i = 0; i <= screenWith; i++) {
			if (i == posPlayer) {
				printf("8");
			}
			else if (i == posBullet && posPlayer > posBullet) {
				printf("<");
			}
			else if (i == posBullet && posPlayer < posBullet) {
				printf(">");
			}
			else if (i == posEnemy) {
				printf("@");
			}
			else if (i == posMushroom) {
				printf(":");
			}
			else {
				printf("_");
			}

		}
		printf("\tScore:%i\t Lives:%i", score, lives);
		printf("\r");

		//Bullet logic
		if (posBullet < posPlayer || posBullet == posPlayer) {
			posBullet--;
		}
		else if (posBullet > posPlayer) {
			posBullet++;
		}
		if (posEnemy == posBullet) {
			posEnemy = -1;
			posBullet = -1;
		}


		//Enemy logic
		if (posEnemy<0 || posEnemy>screenWith) {
			randomEnemy = rand() % 21;
			countEnemy = 0;
			sideEnemy = rand() % 2;
		}
		if (countEnemy == randomEnemy) {
			if (sideEnemy == 0) {
				posEnemy = 0;
			}
			else {
				posEnemy = screenWith;
			}
		}
		else if (countEnemy >= randomEnemy) {
			if (sideEnemy == 0) {
				posEnemy++;
			}
			else {
				posEnemy--;
			}
			if (posEnemy == posBullet) {
				posEnemy = -1;
				posBullet = -1;
			}
			if (posEnemy == posPlayer) {
				posPlayer = initPosPlayer;
				lives--;
				if (lives < 0) {
					end = true;
				}
			}
			
		}
		countEnemy++;

		//Mushroom logic
		if (posMushroom < 0 || posMushroom>screenWith) {
			randomMushroom = rand() % 21;
			countMushroom = 0;
		}
		if (countMushroom == randomMushroom) {
			posMushroom = rand() % screenWith + 1;
		}

		else if (countMushroom > randomMushroom) {
			if (countMushroom >= randomMushroom + 80) {
				posMushroom = -1;
			}
			else if (posMushroom == posPlayer) {
				posMushroom = -1;
				posBullet = -1;
				score += 10;
			}
		}
		countMushroom++;

		//INPUT
		if (_kbhit()) {
			int key = _getch();
			switch (key) {
			case ESC:
				end = true;
				break;

			case KEY_A:
				if (posPlayer > 0) {
					posPlayer--;
				}
				break;

			case KEY_D:
				if (posPlayer < screenWith) {
					posPlayer++;
				}
				break;

			case KEY_K:
				if (posBullet<0 || posBullet > screenWith) {
					posBullet = posPlayer - 1;
				}
				break;

			case KEY_L:
				if (posBullet<0 || posBullet > screenWith) {
					posBullet = posPlayer + 1;
				}
				break;
			}
		}
		Sleep(50);
	}

	return 0;
}
