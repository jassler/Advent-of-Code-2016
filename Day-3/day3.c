#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int isTrianglePossible(int a, int b, int c) {
	return ((a + b) > c) && ((a + c) > b) && ((b + c) > a);
}

void readNumsFromLine(char* line, int* a, int* b, int* c) {
	int nums[3] = { 0, 0, 0 };
	int i = 0;
	
	for (char* c = line; c != '\n' && c != '\0'; c++) {
		if (*c != ' ') {
			while (*c >= '0' && *c <= '9') {
				nums[i] = nums[i] * 10 + (*c - '0');
				c++;
			}
			if (++i >= 3)
				break;
		}
	}

	*a = nums[0];
	*b = nums[1];
	*c = nums[2];
}


int main() {
	FILE* f;
	f = fopen("input.txt", "r");

	if (f == NULL)
		return -1;

	int counter = 0;
	int index = 0;
	char buffer[1000];
	int triangles[3][3];

	while (fgets(buffer, sizeof(buffer), f)) {
		readNumsFromLine(buffer, &triangles[0][index], &triangles[1][index], &triangles[2][index]);
		index = (index + 1) % 3;

		if (index == 0) {
			for (int x = 0; x < 3; x++)
				counter += isTrianglePossible(triangles[x][0], triangles[x][1], triangles[x][2]);
		}
	}

	printf("Amount of valid triangles: %d", counter);

	return 0;
}
