#ifndef Graphics
#define Graphics
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <string.h>
void setconsolesize(int x, int y);
void hidecursor();
void clrscr();
void gotoxy(int column, int row);
#endif