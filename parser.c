#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "color.h"
#include "settings.h"

//Set up program memory
unsigned char memory[30000];
unsigned char *ptr = memory;

//Matches an opening or closing bracket to a corresponding opening or closing bracket
int getMatchingBraceIndex(unsigned int braceIndex, char* str) {
	//Current nesting level
	int level = 0;
	//Matching brace's nesting level
	//(Matching braces have to be at the same level)
	int returnLvl = -1;
	int stringLen = strlen(str);

	/*******************************************************************************\
	 * Note:                                                                       *
	 * If brace given is open brace, iterate through string from beginning to end  *
	 * If brace given is close brace, iterate through string from end to beginning *
	\*******************************************************************************/
	//If brace given is open brace
	if (str[braceIndex] == '[') {
		//Iterator
		int i = 0;

		//Iterate through given string
		for (i; i < stringLen; i++) {
			//If current character of string is open brace
			if (str[i] == '[') {
				//Increment nesting level
				level++;
				//If current character is given brace, assume that matching brace is on the same nesting level
				if (i == braceIndex) {
					returnLvl = level;
				}
			//If current character of string is close brace
			} else if (str[i] == ']') {
				//If currnet nesting level is nesting level of matching brace, return current index
				if (level == returnLvl) {
					return i;
				//Otherwise, decrement nesting level and keep going through the string
				} else {
					level--;
				}
			}
		}
	//If brace given is close brace
	} else if (str[braceIndex] == ']') {
		//Iterator
		int i = stringLen - 1;

		//Iterate through given string
		for (i; i >= 0; i--) {
			//If current character of string is close brace
			if (str[i] == ']') {
				//Increment nesting level
				level++;
				//If current character is given brace, assume that matching brace is on the same nesting level
				if (i == braceIndex) {
					returnLvl = level;
				}
			//If current character of string is open brace
			} else if (str[i] == '[') {
				//If nesting level is nesting level of matching brace, return current index
				if (level == returnLvl) {
					return i;
				//Otherwise, decrement nesting level and keep going through the string
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
	//(Check for proper brace matching)
	{
		int openbrs = 0;
		int closebrs = 0;
		int i = 0;
		bool foundOpen = false;
		bool lastBraceOpen = false;

		//Check number of openning and closing braces
		for (i; i < strlen(code); i++) {
			if (code[i] == '[') {
				foundOpen = true;
				lastBraceOpen = true;
				openbrs++;
			} else if (code[i] == ']') {
				if (!foundOpen) {
					setColor(RED, BLACK);
					printf("Syntax error: missing '['\n");
					setColor(DEFAULT, BLACK);
					return;
				}
				lastBraceOpen = false;
				closebrs++;
			}
		}
		if (lastBraceOpen) {
			setColor(RED, BLACK);
			printf("Syntax error: missing ']'\n");
			setColor(DEFAULT, BLACK);
			return;
		}

		//If number of open braces isn't equal to number of close braces, print error message and abort execution
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
	{
		int i = 0;
		//If program has output anything
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
		//Put a newline after the program has run if the program output anything
		//(Prevents the program's output from being on the same line as the shell's input prompt)
		if (output) {
			putchar('\n');
		}
	}
}
