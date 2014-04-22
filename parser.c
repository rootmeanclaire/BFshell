#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "color.h"

char memory[30/*000*/];
char *ptr = memory;

int getMatchingBraceIndex(unsigned int braceIndex, char* str) {
	int i, level;
	int returnLvl = -1;

	if (str[braceIndex] == '[') {

		for (i; i < strlen(str); i++) {
			if (str[i] == '[') {
				if (i == braceIndex) {
					returnLvl = level;
					level++;
				}
				level++;
			} else if (str[i] == ']') {
				if (level == returnLvl) {
					return i;
				} else {
					level--;
				}
			}
		}
	} else if (str[braceIndex] == ']') {
		int i = sizeof(str);

		for (i; i > strlen(str); i--) {
			if (str[i] == ']') {
				if (i == braceIndex) {
					returnLvl = level;
				}
				level++;
			} else if (str[i] == '[') {
				if (level == returnLvl) {
					return i;
				} else {
					level--;
				}
			}
		}
	} else {
		//Error
		return -1;
	}

	return -1;
}

void reset() {
	memset(memory, 0, sizeof(memory));
}

void exec(char* code) {
	//Check for syntax errors
	{
		int openbrs = 0;
		int closebrs = 0;
		int i = 0;

		for (i; i < strlen(code); i++) {
			if (code[i] == '[') {
				openbrs++;
			} else if (code[i] == ']') {
				closebrs++;
			}
		}

		if (openbrs != closebrs) {
			setColor(RED, BLACK);
			if (openbrs > closebrs) {
				printf("Syntax error: missing ']'\n");
			} else {
				printf("Syntax error: missing '['\n");
			}
			setColor(DEFAULT, BLACK);

			return;
		}
	}

	//Run Code
	int i = 0;
	bool output = false;

	for (i; i < strlen(code); i++) {
		switch (code[i]) {
			case '+':
				++*ptr;
				break;
			case '-':
				--*ptr;
				break;
			case '>':
				++ptr;
				break;
			case '<':
				--ptr;
				break;
			case '.':
				putchar(*ptr);
//				printf("(%d)", (int) *ptr);
				output = true;
				break;
			case ',':
				*ptr = getchar();
				break;
			case '[':
				if (*ptr == 0) {
					i = getMatchingBraceIndex(i, code);
				}
				break;
			case ']':
				if (*ptr != 0) {
					i = getMatchingBraceIndex(i, code);
				}
				break;
		}
	}
	if (output) {
		putchar('\n');
	}
}
