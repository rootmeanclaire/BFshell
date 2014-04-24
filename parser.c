#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "color.h"
#include "settings.h"

char memory[30000];
char *ptr = memory;

//Matches an opening or closing bracket to a corresponding opening or closing bracket
int getMatchingBraceIndex(unsigned int braceIndex, char* str) {
	int i = 0;
	int level = 0;
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
		int i = strlen(str);

		for (i; i > 0; i--) {
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
		setColor(RED, BLACK);
		printf("Unable to match brace at index %i\n", braceIndex);
		setColor(DEFAULT, BLACK);
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
				if (printASCIIval) {
					printf("(%d)", (int) *ptr);
				}
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
