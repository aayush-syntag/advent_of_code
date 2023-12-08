#include <stdio.h>
#include <stdlib.h>

#define FILE_ENDED 0
#define FILE_NOT_ENDED 1

int get_digit(char c) {
	char num = -1;
	num = c - '0';
	if (num < 0 || num > 9) return -1;
	return num;
}

int get_state(char c) {
	return ((c == 'b') << 2 | (c == 'g') << 1 | (c == 'r')) >> 1;
}

int process_game(FILE *fptr) {
	/* 12 red, 13 green, 14 blue */ 
	int starting_balls[3] = {0};
	char c;
	int got_digit = 0, curr_digit = 0;
	int digit = 0;
	int index = 0;
	int i;

	while ((c = getc(fptr)) != '\n') {
		if (c == ' ') continue;
		else if (!got_digit) {
			digit = get_digit(c);
			if (digit >= 0) { curr_digit = curr_digit * 10 + digit; }
			else if (curr_digit > 0) {
				got_digit = 1;
				index = get_state(c);
				if (starting_balls[index] < curr_digit) starting_balls[index] = curr_digit;
			}
		}
		else if (c == ',' || c == ';') {
			got_digit = 0;
			curr_digit = 0;
		}
	}
	return starting_balls[0] * starting_balls[1] * starting_balls[2];
}

int process_line(FILE *fptr, int *ret_game) {
	char c;
	int return_status = FILE_ENDED;
	int got_game = 0;
	int game = 0;
	int digit = -1;

	while (!got_game) {
		c = getc(fptr);
		digit = get_digit(c);
		if (digit >= 0) game = game * 10 + digit;
		else if (c == ':') {
			got_game = 1;
		}
	}

	*ret_game = process_game(fptr);
	if (getc(fptr) != EOF) { return_status = FILE_NOT_ENDED; fptr--; }
	return return_status;
}

int main() {
	FILE *fptr = stdin;
	int sum = 0;
	int game;
	while (process_line(fptr, &game) != FILE_ENDED) {
		sum += game;
	}
	sum += game;
	
	printf("%d\n", sum);
	return 0;
}
