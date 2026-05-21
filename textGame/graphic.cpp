#include <iostream>
#include <Windows.h>

using namespace std;

void moveCursor(int x, int y) {
    COORD pos;
    pos.X = x;
    pos.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void clearArea(int startX , int startY , int width , int height) {
	for (int y = startY; y < startY + height; y++) {
		moveCursor(startX , y);
		for (int x = 0; x < width; x++) {
			wcout << " ";
		}
	}
}