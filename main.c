#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "color.h"
#include "parser.h"

/**************************\
 * Version: 1.1.0 Beta    *
 * Author: Evan Shimoniak *
\**************************/

bool isCode(char* chars);

int main() {
	char line[256];

	do {
		printf("~ ");

		//Get input
		if (fgets(line, sizeof(line), stdin)) {
			if (isCode(line)) {
				exec(line);
			} else {
				//
			}
		}
	} while (true);


	return 0;
}

bool isCode(char* chars) {
	int i = 0;

	for (i; i <= sizeof(chars); i++) {
		if (chars[i] == '+' || chars[i] == '-' || chars[i] == '>' || chars[i] == '<' || chars[i] == '[' || chars[i] == ']' || chars[i] == ',' || chars[i] == '.') {
			return true;
		}
	}

	return false;
}
