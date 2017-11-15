// 1dGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <list>

struct Enemy
{
	int x = -1;
	int count = 0;
	int randomEnemy=0;
	int sideEnemy;
};

struct Bullet
{
	int x = -1;
};


#define ESC 27
#define KEY_A 97
#define KEY_D 100
#define KEY_L 108
#define KEY_K 107

void UpdateDraw();
void UpdateBullet();
void UpdateEnemy();
void UpdateMushroom();
void Input();

bool		end				= false;
int			screenWith		= 90;
const int	initPosPlayer	= 20;
int			posPlayer		= initPosPlayer;
int			posBullet		= -1;
int			posMushroom		= -1;
int			countMushroom	= 0;
int			randomMushroom;
int			posEnemy		= -1;
int			score			= 0;
int			lives			= 3;
std::list<Enemy> enemyList;
std::list<Bullet> bulletList;


void Init() {
	Enemy e1, e2, e3, e4;
	enemyList.push_back(e1);
	enemyList.push_back(e2);
	enemyList.push_back(e3);
	enemyList.push_back(e4);
}

int main()
{
	Init();
	printf("\n\n\n\n\n\n\n\n");
	while (!end) {

		// Draw loop
		UpdateDraw();

		//Bullet logic
		UpdateBullet();

		//Enemy logic
		UpdateEnemy();

		//Mushroom logic
		UpdateMushroom();

		//INPUT
		Input();

		Sleep(50);
	}
	return 0;
}

void UpdateDraw() {
	printf("Lives:%i ", lives);
	
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
		else if (i == posMushroom) {
			printf(":");
		}else {
			printf("_");
		}
		
		/*else if (i == posEnemy) {
			printf("@");
		}*/
		
		for (auto it = enemyList.begin(); it != enemyList.end(); ++it) {
			//printf("%i\n",e.count);
			if (i == (*it).x) {
				printf("@");
			}
		}
		/*unsigned int len = sizeof(enemiesX) / sizeof(enemiesX[0]);
		for(int pos=0; pos<len; pos++){
			if (i == enemiesX[pos]) {
				printf("@");
			}
		}*/

		
	}

	printf(" Score:%i", score);
	printf("\r");
}

void UpdateBullet() {
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
}

void UpdateEnemy() {
	for (auto it = enemyList.begin(); it != enemyList.end(); ++it) {
		if (((*it).x<0 || (*it).x>screenWith) || (*it).randomEnemy==0) {
			(*it).randomEnemy = rand() % 41;
			if ((*it).x<-1 || (*it).x>screenWith) {
				(*it).count = 0;
			}
			(*it).sideEnemy = rand() % 2;
		}
		if ((*it).count == (*it).randomEnemy) {
			if ((*it).sideEnemy == 0) {
				(*it).x = 0;
			}
			else {
				(*it).x = screenWith;
			}
		}
		else if ((*it).count >= (*it).randomEnemy) {
			if ((*it).sideEnemy == 0) {
				(*it).x++;
			}
			else {
				(*it).x--;
			}
			if ((*it).x == posBullet) {
				(*it).x = -1;
				posBullet = -1;
			}
			if ((*it).x == posPlayer) {
				posPlayer = initPosPlayer;
				lives--;
				if (lives < 0) {
					end = true;
				}
			}
		}
		(*it).count += 1;
	}
}

void UpdateMushroom() {
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
}

void Input() {
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
}
