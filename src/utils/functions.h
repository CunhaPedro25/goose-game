#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <errno.h>

#ifdef _WIN32
    #include <windows.h>
#elif __linux__
    #include <sys/stat.h>
#elif __APPLE__
    #include <sys/stat.h>
#endif


#include "ui.h"
#include "../questions/questions.h"

void getPlatformFilePath(char* platformPath);
int createFolder(const char* folderPath);
void installGame();

void showSpecificInvalidOption(char *text);

size_t strlen_utf8(const char *string);

bool isInt(char *text);
bool isEmpty(char *text);

bool getString(char *string, int maxInputSize);
bool getNumber(int *number, int maxInputSize);
bool getNumberFromRange(int *answer, int min, int max);

void waitInput(char *message);

#endif /* FUNCTIONS_H */
