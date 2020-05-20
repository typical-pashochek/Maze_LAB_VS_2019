#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include "graphics.h"

int Size;
int Delay;


struct Point {
	int x;
	int y;
	struct Point* next;
	struct Point* prev;
};

typedef struct Point Point;

void GenerateMaze(int*** mass) {
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			(*mass)[i][j] = 0;
		}
	}
	int x = rand() % Size;
	int y = rand() % Size;
	Point* head = (Point*)malloc(sizeof(Point));
	head->x = x;
	head->y = y;
	head->next = 0;
	head->prev = 0;
	int flag = 0;
	int step_count = 1;
	(*mass)[x][y] = 1;
	while (flag == 0) {
		int direction = rand() % 4;
		int count = 0;
		if (x == 0) {
			count++;
		}
		else if ((*mass)[x - 1][y] != 0) {
			count++;
		}
		if (y == 0) {
			count++;
		}
		else if ((*mass)[x][y - 1] != 0) {
			count++;
		}
		if (x == Size - 1) {
			count++;
		}
		else if ((*mass)[x + 1][y] != 0) {
			count++;
		}
		if (y == Size - 1) {
			count++;
		}
		else if ((*mass)[x][y + 1] != 0) {
			count++;
		}
		if (count == 4) {
			if (head->prev == 0 || step_count > Size* Size / (rand() % 4 + 3)) {
				break;
			}
			else {
				head = head->prev;
				free(head->next);
				x = head->x;
				y = head->y;
			}

		}
		switch (direction) {
		case 0:
			if (x != 0 && (*mass)[x - 1][y] == 0) {
				x--;
				head->next = (Point*)malloc(sizeof(Point));
				head->next->x = x;
				head->next->y = y;
				head->next->next = 0;
				head->next->prev = head;
				head = head->next;
				step_count++;
				(*mass)[x][y] = 1;
			}
			break;
		case 1:
			if (y != 0 && (*mass)[x][y - 1] == 0) {
				y--;
				head->next = (Point*)malloc(sizeof(Point));
				head->next->x = x;
				head->next->y = y;
				head->next->next = 0;
				head->next->prev = head;
				head = head->next;
				step_count++;
				(*mass)[x][y] = 1;
			}
			break;
		case 2:
			if (x != Size - 1 && (*mass)[x + 1][y] == 0) {
				x++;
				head->next = (Point*)malloc(sizeof(Point));
				head->next->x = x;
				head->next->y = y;
				head->next->next = 0;
				head->next->prev = head;
				head = head->next;
				step_count++;
				(*mass)[x][y] = 1;
			}
			break;
		case 3:
			if (y != Size - 1 && (*mass)[x][y + 1] == 0) {
				y++;
				head->next = (Point*)malloc(sizeof(Point));
				head->next->x = x;
				head->next->y = y;
				head->next->next = 0;
				head->next->prev = head;
				head = head->next;
				step_count++;
				(*mass)[x][y] = 1;
			}
			break;
		default:
			continue;
		}
	}
	while (head->prev != 0) {
		head = head->prev;
		free(head->next);
	}
	free(head);
}

void PrintMaze(int*** mass) {
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			if ((*mass)[i][j] == 0) {
				printf("#");
			}
			else {
				printf(" ");
			}
		}
		printf("|\n");
	}
	for (int i = 0; i < Size; i++) {
		printf("-");
	}
}




int main() {
	setconsolesize(60, 45);
	printf("Enter field Size(10-40) and Delay\n");
	scanf_s("%d %d", &Size, &Delay);
	if (Size > 40 || Size < 10) {
		printf("Wrong size!!!\n");
		exit(1);
	}
	srand((unsigned int)time(0));
	int** mass = (int**)malloc(Size * sizeof(int*));
	for (int i = 0; i < Size; i++) {
		mass[i] = (int*)malloc(Size * sizeof(int));
	}
	while (1 != 0) {
		
		GenerateMaze(&mass);
		clrscr();
		gotoxy(0, 0);
		PrintMaze(&mass);
		Sleep(Delay);
	}	
	for (int i = 0; i < Size; i++) {
		free(mass[i]);
	}
	free(mass);
	return 0;
}