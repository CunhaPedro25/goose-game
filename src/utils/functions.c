#include "functions.h"

#define FILE_PATH_LENGTH 256
#define EXTRA_PATH_LENGTH 512

#ifdef _WIN32
    #define PLATFORM_PATH_ENV "LOCALAPPDATA"
    #define PLATFORM_FOLDER "gooseGame\\"
#elif __linux__
    #define PLATFORM_PATH_ENV "HOME"
    #define PLATFORM_FOLDER ".gooseGame/"
#elif __APPLE__
    #define PLATFORM_PATH_ENV "HOME"
    #define PLATFORM_FOLDER "Applications/gooseGame/"
#endif

void getPlatformFilePath(char* platformPath) {
#ifdef _WIN32
    // Windows
    const char* appDataPath = getenv(PLATFORM_PATH_ENV);
    sprintf(platformPath, "%s\\%s", appDataPath, PLATFORM_FOLDER);
#elif __linux__ || __APPLE__
    // Linux and macOS
    const char* homePath = getenv(PLATFORM_PATH_ENV);
    sprintf(platformPath, "%s/%s", homePath, PLATFORM_FOLDER);
#endif
}

int mkdir_recursive(const char* folderPath, mode_t mode) {
    char* path = strdup(folderPath);
    char* p = path;
    int result = 0;

    while (*p != '\0') {
        if (*p == '/' && p != path) {
            *p = '\0';
            if (mkdir(path, mode) != 0 && errno != EEXIST) {
                result = -1;
                break;
            }
            *p = '/';
        }
        p++;
    }

    free(path);
    return result;
}

int createFolder(const char* folderPath) {
  #ifdef _WIN32
      if (CreateDirectory(folderPath, NULL) != 0 || GetLastError() == ERROR_ALREADY_EXISTS) {
          return 1;
      }
  #elif __linux__ || __APPLE__
      if (mkdir_recursive(folderPath, 0777) == 0 || errno == EEXIST) {
          return 1;
      }
  #endif

  return 0;
}

void installGame(){
  char platformPath[FILE_PATH_LENGTH], fullPath[EXTRA_PATH_LENGTH];
  getPlatformFilePath(platformPath);

  if (!createFolder(platformPath)) {
    printf("Error creating folder: %s\n", platformPath);
  }

  installQuestionFiles();
}


void showSpecificInvalidOption(char *text){
  setTextColor(RED, false);
  clearToLineEnd();
  printf("%s", text);    // Show error message
  restoreCursor();
  clearToLineEnd();
}


void removeNewline(char *string){
  string[strcspn(string, "\n")] = 0;
}

size_t strlen_utf8(const char *string) {
  size_t count = 0;
  while (*string) {
    count += (*string++ & 0xC0) != 0x80;
  }
  return count;
}

//Checks for int type in string by finding char that are not digits
bool isInt(char *text){
  for(int i = 0; i < strlen_utf8(text); i++){
    if(!isdigit(text[i])){
      return false;
    }
  }
  return true;
}

bool isEmpty(char *text){
  if(strcmp(text, "") == 0) return true;
  for (int i = 0; i < strlen_utf8(text); ++i) {
    if(text[i] != ' '){
      return false;
    }
  }

  return true;
}

//Custom read func for strings that requires a valid input to be met
bool getString(char *string, int maxInputSize){
  do {
    saveCursor();
    fgets(string, maxInputSize, stdin);
    removeNewline(string);

    if(isEmpty(string))
      showSpecificInvalidOption("[Invalid Option]");
  }while (isEmpty(string));
  clearToLineEnd();

  return true;
}

//Custom read func for ints that requires a valid input to be met
bool getNumber(int *number, int maxInputSize){
  char *tempString = NULL;
  tempString = (char *) malloc(maxInputSize * sizeof(char));
  char *trash;
  do {
    getString(tempString, maxInputSize);
    if (isInt(tempString) == false) {
      showSpecificInvalidOption("[Invalid Option]");
    }
  }while (isInt(tempString) == false);
  *number = strtol(tempString, &trash, 10);
  clearToLineEnd();

  free(tempString);

  return true;
}


bool getNumberFromRange(int *answer, int min, int max){
  do {
    getNumber(answer, 100);
    if(*answer < min || *answer > max) {
      showSpecificInvalidOption("[Invalid Option]");
    }
  }while(*answer < min || *answer > max);
  clearToLineEnd();

  return true;
}

void waitInput(char *message){
    clearToScreenEnd();
    printf("%s", message);
    getchar();
}
