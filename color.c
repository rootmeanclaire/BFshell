#include <windows.h>
#include "color.h"

void setColor(unsigned char foreground, unsigned char background) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, foreground + (16 * background));
}
