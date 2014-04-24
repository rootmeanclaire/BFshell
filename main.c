#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "color.h"
#include "parser.h"

/**************************\
 * Version: 1.3.0 Beta    *
 * Author: Evan Shimoniak *
\**************************/

bool isCode(char* chars);
//char** splitStrBySpaces(char* str);
void processCommand(char* line);

int main() {
	//Create a character array to store user input
	char line[256];

	do {
		//Print input prompt
		printf("~ ");

		//Read user input upon entering a newline
		if (fgets(line, sizeof(line), stdin)) {
			//If line contains a syntax character([]+-,.<>), then parse as syntax and execute
			if (isCode(line)) {
				exec(line);
			} else {
				//If line contains no syntax characters, then attempt processing as an interpreter command
				processCommand(line);
//				char** splitStr = splitStrBySpaces(line);
//				int i = 0;
//
//				for (i; i < sizeof(splitStr); i++) {
//					printf("%s\n", splitStr[i]);
//				}
			}
		}
	} while (true);


	return 0;
}

bool isCode(char* chars) {
	int i = 0;

	for (i; i < strlen(chars); i++) {
		if (chars[i] == '+' || chars[i] == '-' || chars[i] == '>' || chars[i] == '<' || chars[i] == '[' || chars[i] == ']' || chars[i] == ',' || chars[i] == '.') {
			return true;
		}
	}

	return false;
}

void processCommand(char* line) {
	if (strcmp(line, "help\n") == 0) {
		printf("COMMANDS\n\t\"version\" Print the current version of the interpreter\n\t\"reset\"   Reset program memory\n");
	} else if (strcmp(line, "version\n") == 0) {
		printf("Beta 1.3.0\n");
	} else if (strcmp(line, "reset\n") == 0) {
		reset();
		setColor(BLACK, DEFAULT);
		printf("Memory reset\n");
		setColor(DEFAULT, BLACK);
	} else {
		printf("Unrecognized command\n");
	}
}

//Unused
char** splitStrBySpaces(char* str) {
	unsigned int i = 0;
	unsigned int letter = 0;
	unsigned int word = 0;
	char** words;

	for (i; i < strlen(str); i++) {
		//If current char is space
		if (str[i] == ' ') {
			//If char isn't first char and previous char isn't a space
			if (i != 0 && str[i - 1] != ' ') {
				word++;
				letter = 0;
			}
		} else {
			words[word][letter] = str[i];
			letter++;
		}
	}

	return words;
}
