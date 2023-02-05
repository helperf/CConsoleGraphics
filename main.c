#include <stdio.h>
#include <windows.h>
#include <math.h>

#define SCREENW 80
#define SCREENH 25

char buffer[SCREENH][SCREENW];

void gotoxy(int x, int y) { 
    COORD pos = {x, y};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

void setpixel(int x, int y) {
	buffer[y][x] = '@';
}

void setpixelch(int x, int y, char ch) {
	buffer[y][x] = ch;
}

void fill(char ch, short isSet) {
	for (int i = 0; i < SCREENH; i++) {
		for (int j = 0; j < SCREENW; j++) {
			putchar(ch);
			if (isSet == 1)
				setpixelch(j, i, ch);
		}
	}
	gotoxy(0, 0);
}

void drawSquare(int x, int y, int h, int w) {
	for (int i = x; i <= h+1; i++) {
		for (int j = y; j <= w+1; j++) {
			setpixel(j, i);
		}
	}
}

void drawBuffer() {
	for (int i = 0; i < SCREENH; i++) {
		for (int j = 0; j < SCREENW; j++) {
			putchar(buffer[i][j]);
		}
	}
}

void drawSphere(int x, int y, int r) {
	x -= 2;
	y -= 2;
	int nx = x-2;
	int ny = r-2;
	int delta = 1-2*r;
	int error = 0;
	int x1 = r+x;
	int y1 = r+y;
	while (ny >= nx) {
		setpixel(x1+nx, y1+ny);
		setpixel(x1+nx, y1-ny);
		setpixel(x1-nx, y1+ny);
		setpixel(x1-nx, y1-ny);
		setpixel(x1+ny, y1+nx);
		setpixel(x1+ny, y1-nx);
		setpixel(x1-ny, y1+nx);
		setpixel(x1-ny, y1-nx);
		error = 2 * (delta+ny) - 1;
		if ((delta < 0) && (error <= 0)) {
			delta += 2 * (++nx) + 1;
			continue;
		}
		if ((delta > 0) && (error > 0)) {
			delta -= 2 * (--ny) + 1;
			continue;
		}
		delta += 2 * ((++nx) - (--ny));
	}
}

void drawLine(int x0, int y0, int x1, int y1) {
	int deltax = abs(x1 - x0);
	int deltay = abs(y1 - y0);
	int error = 0;
	int deltaerr = (deltay + 1);
	int y = y0;
	int diry = y1-y0;
	if (diry > 0) {
		diry = 1;
	}
	if (diry < 0) {
		diry = -1;
	}
	for (int x = x0; x < x1; x++) {
		setpixel(x, y);
		error = error + deltaerr;
		if (error >= (deltax+1)) {
			y = y + diry;
			error = error - (deltax+1);
		}
	}
}

void main(void) {
	system("cls");
	fill('a', 1);
	for (;;) {
		drawSphere(0, 0, 10);
		drawLine(10, 10, 25, 25);
		drawBuffer();
		gotoxy(0, 0);
	}
	return;
}
