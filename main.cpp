#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
COORD coord;

enum VerticalDirection {
	UP,
	DOWN
};

enum HorizontalDirection {
	LEFT,
	RIGHT
};

struct Point {
	int x;
	int y;
	VerticalDirection vDirection;
	HorizontalDirection hDirection;
};

void gotoXY(int, int);
void printPoint(Point, int);

void printBorders();

int main(int argc, char *argv[]) {

	srand(time(NULL));

	Point point = {rand() % 59 + 1, rand() % 19 + 1};
	Point prevPoint;

	point.hDirection = (HorizontalDirection)(rand() % 2);
	point.vDirection = (VerticalDirection)(rand() % 2);
	printBorders();
	SetConsoleTextAttribute(handle, 13);

	while (true) {

		if (point.x >= 59) {
			point.hDirection = LEFT;
		}

		if (point.x <= 1) {
			point.hDirection = RIGHT;
		}

		if (point.y >= 19) {
			point.vDirection = UP;
		}

		if (point.y <= 1) {
			point.vDirection = DOWN;
		}

		switch(point.hDirection) {
		case LEFT:
			prevPoint.x = point.x--;
			break;
		case RIGHT:
			prevPoint.x = point.x++;
			break;
		};

		switch (point.vDirection)
		{
		case UP:
			prevPoint.y = point.y--;
			break;
		case DOWN:
			prevPoint.y = point.y++;
			break;
		}
		printPoint(point, 254);
		printPoint(prevPoint, ' ');
		Sleep(125);
	}
	gotoXY(23,23);
	return EXIT_SUCCESS;
}

void printPoint(Point point, int symbol) {
	gotoXY(point.x, point.y);
	putchar(symbol);
}

void printBorders() {
	gotoXY(0, 0);
	for (int i = 0; i < 60; i++) {
		putchar(205);
	}
	for (int i = 0; i < 20; i++) {

		if (i == 0) {
			gotoXY(0, i);
			putchar(201);
		} else {
			gotoXY(0, i);
			putchar(186);
		}
	}

	for (int i = 0; i < 60; i++) {
		if (i == 0) {
			gotoXY(i, 20);
			putchar(200);
		} else {
			gotoXY(i, 20);
			putchar(205);
		}
		
	}

	for (int i = 0; i < 21; i++) {
		if (i == 0) {
			gotoXY(60, i);
			putchar(187);
		} else if (i == 20) {
			gotoXY(60, i);
			putchar(188);
		} else {
			gotoXY(60, i);
			putchar(186);
		}
	}
}

void gotoXY(int x, int y) {
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(handle, coord);
}