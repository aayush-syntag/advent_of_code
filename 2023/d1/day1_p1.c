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

int get_line(FILE *fptr, int *ret) {
	char c = 0;
	int digit;
	int num1 = -1, num2 = -1, rval = FILE_DONE;

	while ((c = getc(fptr)) != EOF) {
		if (c == '\n') { rval = FILE_NOT_DONE; break; }
		digit = get_num(c);
		if (num1 < 0) {
			num1 = digit;
			num2 = digit;
		}
		else if (digit >= 0) num2 = digit;
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
	printf("%d\n",sum);
	return 0;
}
