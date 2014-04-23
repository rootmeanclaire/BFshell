#include "color.h"
#include <stdio.h>

void setColor(unsigned char foreground, unsigned char background) {
	printf("\x1B[%i; %i; %im", 1, foreground + 30, background + 40);
}
