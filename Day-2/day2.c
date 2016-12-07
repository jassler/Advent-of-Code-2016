#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

char numpad[7][7] = {
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', '1', ' ', ' ', ' ' },
	{ ' ', ' ', '2', '3', '4', ' ', ' ' },
	{ ' ', '5', '6', '7', '8', '9', ' ' },
	{ ' ', ' ', 'A', 'B', 'C', ' ', ' ' },
	{ ' ', ' ', ' ', 'D', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ' }
};

struct {
	int x, y;
} pos = { 1, 3 };


char getChar() {
	return numpad[pos.y][pos.x];
}

void move(char* input) {
	for (char* c = input; *c != '\0' && *c != '\n'; c++) {
		switch (*c) {
		case 'L': if(numpad[pos.y][pos.x - 1] != ' ') pos.x--; break;
		case 'R': if(numpad[pos.y][pos.x + 1] != ' ') pos.x++; break;
		case 'U': if(numpad[pos.y - 1][pos.x] != ' ') pos.y--; break;
		case 'D': if(numpad[pos.y + 1][pos.x] != ' ') pos.y++; break;
		default:
			printf("Unknown instruction: %c (= %d)\n", *c, *c);
		}
	}
}


int main() {
	FILE* f;
	f = fopen("input.txt", "r");

	if (f == NULL)
		return -1;

	char buffer[1000];
	while (fgets(buffer, sizeof(buffer), f)) {
		move(buffer);
		printf("Next input: %c\n", getChar());
	}
  
	return 0;
}
