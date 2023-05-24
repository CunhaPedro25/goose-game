#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "ui.h"

void showSpecificInvalidOption(char *text);

size_t strlen_utf8(const char *string);

bool isInt(char *text);
bool isEmpty(char *text);

bool getString(char *string, int maxInputSize);
bool getNumber(int *number, int maxInputSize);
bool getNumberFromRange(int *answer, int min, int max);

#endif /* FUNCTIONS_H */
