#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define ALPHABET 26

struct amLetters {
	char letter;
	int amount;
};

void swap(struct amLetters* l1, struct amLetters* l2) {
	struct amLetters tmp = *l1;
	*l1 = *l2;
	*l2 = tmp;
}



int fetchAmount(char* line) {
	char* c = line;
	while (*c < '0' || *c > '9')
		c++;
	
	return atoi(c);
}



int checkKey(char* line, struct amLetters* letters, int amount) {
	char* c = line;

	while (*c++ != '[');
	
	int x = 0;
	while (*c != ']') {
		if (*c != letters[x].letter)
			return 0;

		c++;
		x++;
		if (x >= amount && *c != ']')
			return 0;
	}

	return 1;
}



struct amLetters* stripFirstPart(char* line, int* length) {

	struct amLetters letters[ALPHABET];
	for (int x = 0; x < ALPHABET; x++)
		letters[x].letter = 0;

	struct amLetters* ret;
	int i = 0;
	int l = 0;

	for (char* c = line; *c >= 'a' && *c <= 'z' || *c == '-'; c++) {
		if (*c != '-') {
			int x = 0;
			while (x < l) {
				if (letters[x].letter == *c) {
					letters[x].amount++;
					break;
				}
				x++;
			}

			if (x == l) {
				letters[x].letter = *c;
				letters[x].amount = 1;
				l++;
			}
			
			while(x > 0) {
				if ((letters[x].amount > letters[x - 1].amount) || (letters[x].letter < letters[x - 1].letter && letters[x].amount == letters[x - 1].amount)) {
					swap(&letters[x], &letters[x - 1]);
					x--;
				}
				else
					break;
			}

		}
	}

	ret = malloc(l * sizeof(struct amLetters));
	for (int x = 0; x < l; x++)
		ret[x] = letters[x];

	*length = l;
	return ret;
}

void shift(char* line, int amount) {
	char* c = line;
	while ((*c >= 'a' && *c <= 'z') || *c == '-') {
		if (*c == '-') {
			c++;
			continue;
		}

		*c = (((*c - 'a') + amount) % ALPHABET) + 'a';
		c++;
	}
}


int main() {


	FILE* f;
	f = fopen("input.txt", "r");

	if (f == NULL)
		return -1;

	char buffer[1000];
	struct amLetters* letters;
	int amount;

	int sum = 0;

	while (fgets(buffer, sizeof(buffer), f)) {

		shift(buffer, fetchAmount(buffer));
		printf("%s", buffer);
		if (strstr(buffer, "north") != NULL)
			printf("%s", buffer);
	}

	printf("Sum: %d", sum);

	return 0;
}
