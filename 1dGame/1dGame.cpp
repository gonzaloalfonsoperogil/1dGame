// 1dGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <list>

struct Enemy
{
	int x			= -1;
	int count		= 0;
	int randomEnemy	= 0;
	int sideEnemy;
};

struct Bullet
{
	int x;
};

struct Mushroom
{
	int x;
	int count	= 0;
	int random	= 0;
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
int			score			= 0;
int			lives			= 3;

std::list<Enemy>		enemyList;
std::list<Bullet>		bulletList;
std::list<Mushroom>		mushroomList;

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
	
	while (!end) {
		/*printf("%s", "'");
		printf("\r");
		Sleep(50);
		printf("%s", ":");
		printf("\r");
		Sleep(50);
		printf("%s", ".");
		printf("\r");
		Sleep(50);*/
		printf("\n\n\n\n\n\n\n\n");

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
		system("cls");
	}
	return 0;
}

void UpdateDraw() {
	printf("Lives:%i ", lives);
	
	for (int i = 0; i < screenWith; i++) {
		bool q = false;
		if (i == posPlayer) {
			printf("8");
			q = true;
		}

		for (auto it = mushroomList.begin(); it != mushroomList.end(); ++it) {
			if (i == (*it).x) {
				printf("$");
				q = true;
			}
		}

		for (auto it = bulletList.begin(); it != bulletList.end(); ++it) {
			if (i == (*it).x && posPlayer > (*it).x) {
				printf("<");
				q = true;
			}
			else if (i == (*it).x && posPlayer < (*it).x) {
				printf(">");
				q = true;
			}
		}

		for (auto it = enemyList.begin(); it != enemyList.end(); ++it) {
			if (i == (*it).x) {
				printf("@");
				q = true;
			}
		}
		if (!q) {
			printf("_");
		}
		
	}

	printf(" Score:%i", score);
}

void UpdateBullet() {
	for (auto it = bulletList.begin(); it != bulletList.end();) {
		if ((*it).x < posPlayer) {
			(*it).x--;
		}
		else if ((*it).x > posPlayer) {
			(*it).x++;
		}

		for (auto itE = enemyList.begin(); itE != enemyList.end(); ++itE) {
			if ((*itE).x == (*it).x) {
				(*itE).x = -1;
				(*it).x = -1;
			}
		}

		if ((*it).x < 0 || (*it).x > screenWith) {
			it = bulletList.erase(it);
		}
		else {
			it++;
		}
	}
}

void UpdateEnemy() {
	for (auto it = enemyList.begin(); it != enemyList.end(); ++it) {
		if (((*it).x<0 || (*it).x>screenWith)) {
			(*it).randomEnemy = rand() % 41;
			if ((*it).count>(*it).randomEnemy) {
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

			for (auto itB = bulletList.begin(); itB != bulletList.end(); ++itB) {
				if ((*itB).x == (*it).x) {
					(*itB).x = -1;
					(*it).x = -1;
				}
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
	if ((rand() % 50) == 0) {
		Mushroom m;
		m.random=rand() % 21;
		m.count = 0;
		mushroomList.push_back(m);
	}

	for (auto it = mushroomList.begin(); it != mushroomList.end();) {
		(*it).count++;if ((*it).count == (*it).random) {
			(*it).x = rand() % screenWith + 1;
			it++;
		}
		
		else if ((*it).count >(*it).random) {
			if ((*it).count >= (*it).random + 80) {
				it=mushroomList.erase(it);
				
			}
			else if ((*it).x == posPlayer) {
				it=mushroomList.erase(it);
				score += 10;
			}
			else {
				it++;
			}
		}
		
	}
}

void Input() {
	if (_kbhit()) {
		int key = _getch();
		switch (key) {
		case ESC:									end = true;					break;
		case KEY_A: if (posPlayer > 0)				posPlayer--;				break;
		case KEY_D: if (posPlayer < screenWith)		posPlayer++;				break;
		case KEY_K:
													{Bullet b;
													b.x = posPlayer - 1;
													bulletList.push_back(b);}	break;
		case KEY_L:
													{Bullet c;
													c.x = posPlayer + 1;
													bulletList.push_back(c); }	break;
		}
	}
}
