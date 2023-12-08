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
	int starting_balls[3] = {12, 13, 14};
	char c;
	int return_status = 0;
	int got_digit = 0, curr_digit = 0;
	int digit = 0;
	int index = 0;
	int exit = 0;
	int i;

	while ((c = getc(fptr)) != '\n') {
		if (c == ';') {
			return_status |= 2;
			break;
		}
		if (c == ' ' || exit) continue;
		else if (!got_digit) {
			digit = get_digit(c);
			if (digit >= 0) { curr_digit = curr_digit * 10 + digit; }
			else if (curr_digit > 0) {
				got_digit = 1;

				index = get_state(c);
				starting_balls[index] -= curr_digit;
				if (starting_balls[index] < 0) { return_status |= 1; exit = 1; }
			}
		}
		else if (c == ',') {
			got_digit = 0;
			curr_digit = 0;
		}
	}
	return return_status;
}

int process_line(FILE *fptr, int *ret_game) {
	char c;
	int return_status = FILE_ENDED;
	int got_game = 0;
	int game = 0;
	int digit = -1;
	int game_status = 0;

	while (!got_game) {
		c = getc(fptr);
		digit = get_digit(c);
		if (digit >= 0) game = game * 10 + digit;
		else if (c == ':') {
			got_game = 1;
		}
	}
	*ret_game = game;

	while ((game_status |= process_game(fptr)) >= 2) game_status &= 1;
	if (game_status == 1) *ret_game = 0;
	if (getc(fptr) != EOF) { return_status = FILE_NOT_ENDED; fptr--; }
	return return_status;
}

int main() {
	FILE *fptr = stdin;
	int sum = 0;
	int game;
	while (process_line(fptr, &game) != FILE_ENDED) {
		sum += game;
		game = 0;
	}
	sum += game;
	
	printf("%d\n", sum);
	return 0;
}
