#include <stdio.h>
#include <stdlib.h>

#define FILE_DONE -1
#define FILE_NOT_DONE 0

int get_num(char c) {
	int diff = '0';
	diff = c - diff;
	if (diff > 0 & diff < 10) return diff;
	return -1;
}

int update_table(char c, const char **word_arr, int *statuses) {
	int i, ret=-1;
	for (i = 0; i < 9; i++) {
		if ((*word_arr)[*statuses] == c) {
			if ((*word_arr)[*statuses + 1] == '\0') { 
				ret = i+1; 
				*statuses = 0;
			}
			else {
				(*statuses)++;
			}
		}
		else {
			*statuses = 0;
			if ((*word_arr)[*statuses] == c) (*statuses)++;
		}
		statuses++;
		word_arr++;
	}

	return ret;
}

int get_line(FILE *fptr, int *ret) {
	char c = 0;
	const char *words[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	int word_status[9] = {0};

	int digit;
	int num1 = -1, num2 = -1, rval = FILE_DONE;

	while ((c = getc(fptr)) != EOF) {
		if (c == '\n') { rval = FILE_NOT_DONE; break; }
		digit = update_table(c, &words[0], &word_status[0]);
		if (digit < 0) digit = get_num(c);
	
		if (digit >= 0) {
			if (num1 < 0) num1 = digit;
			num2 = digit;
		}
	}
	*ret = num1*10 + num2;
	return rval;
}

int main() {
	FILE *fptr = stdin;
	int sum = 0, new_code = 0;
	while (get_line(fptr, &new_code) == FILE_NOT_DONE) {
		sum += new_code;
		new_code = 0;
	}
	printf("%d\n", new_code);
	printf("%d\n",sum);
	return 0;
}
