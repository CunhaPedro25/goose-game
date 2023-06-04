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

void getPlatformFilePath(char* platformPath, char* platformEnv, char* platformFolder) {
#ifdef _WIN32
    // Windows
    const char* appDataPath = getenv(platformEnv);
    sprintf(platformPath, "%s\\%s", appDataPath, platformFolder);
#elif __linux__ || __APPLE__
    // Linux and macOS
    const char* homePath = getenv(platformEnv);
    sprintf(platformPath, "%s/%s", homePath, platformFolder);
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
  getPlatformFilePath(platformPath, PLATFORM_PATH_ENV, PLATFORM_FOLDER);

  if (!createFolder(platformPath)) {
    printf("Error creating folder: %s\n", platformPath);
    return;
  }

  // Create the question folder inside the platform folder
  snprintf(fullPath, sizeof(fullPath), "%s%s", platformPath, "admin/");
  if (!createFolder(fullPath)) {
    printf("Error creating folder: %s\n", fullPath);
    return;
  }

  snprintf(fullPath, sizeof(fullPath), "%s%s", platformPath, "admin/admins.dat");

  FILE* file = fopen(fullPath, "rb");
  if(file == NULL){
    file = fopen(fullPath, "wb");
    if(file == NULL){
      printf("Error creating admin file: %s\n", fullPath);
      return;
    }

    Admins admin;
    memset(&admin, 0, sizeof(Admins));

    printf("For this game, a username and password are needed, which will be used for game settings.\n");
    printf("Username: ");
    getString(admin.username, 100);
    printf("Password: ");
    getString(admin.password, 100);

    int number = 1;
    fseek(file, 0, SEEK_SET);
    fwrite(&number, sizeof(int), 1, file);

    fseek(file, 0, SEEK_END);
    fwrite(&admin, sizeof(Admins), 1, file);
  }
  fclose(file);

  // Create the question folder inside the platform folder
  snprintf(fullPath, sizeof(fullPath), "%s%s", platformPath, "questions/");
  if (!createFolder(fullPath)) {
    printf("Error creating folder: %s\n", fullPath);
    return;
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

bool askConfirmation(char *question){
  char string[100];
  printf("%s (y/n)? ",question);
  do {
    getString(string, 100);
    if(strcmp(string, "y") != 0 && strcmp(string, "Y") != 0 && strcmp(string, "n") != 0 && strcmp(string, "N") != 0){
      showSpecificInvalidOption("[Invalid Option]");
    }
  } while (strcmp(string, "y") != 0 && strcmp(string, "Y") != 0 && strcmp(string, "n") != 0 && strcmp(string, "N") != 0);

  return strcmp(string, "y") == 0 || strcmp(string, "Y") == 0;
}


bool editAdmin(int id){
  char platformPath[FILE_PATH_LENGTH];
  getPlatformFilePath(platformPath, PLATFORM_PATH_ENV, PLATFORM_FOLDER);

  char fullPath[EXTRA_PATH_LENGTH];
  sprintf(fullPath, "%s%s", platformPath, "admin/admins.dat");

  FILE *file = fopen(fullPath, "rb+");
  if(file == NULL){
    return false;
  }

  Admins admin;
  memset(&admin, 0, sizeof(Admins));
  clearConsole();
  printf("Edit user %d\n", id);
  printf("Username: ");
  getString(admin.username, 100);
  printf("Password: ");
  getString(admin.password, 100);

  // Calculate the position of the desired line
  long int position = sizeof(int) + (id-1) * sizeof(Admins);

  // Move the file pointer to the calculated position
  fseek(file, position, SEEK_SET);
  fwrite(&admin, sizeof(Admins), 1, file);

  fclose(file);
  return true;
}

bool deleteAdmin(int id){
  char platformPath[FILE_PATH_LENGTH];
  getPlatformFilePath(platformPath, PLATFORM_PATH_ENV, PLATFORM_FOLDER);

  char fullPath[EXTRA_PATH_LENGTH];
  sprintf(fullPath, "%s%s", platformPath, "admin/admins.dat");

  char tempFullPath[EXTRA_PATH_LENGTH];
  sprintf(tempFullPath, "%s%s", platformPath, "admin/tempAdmins.dat");


  FILE *file, *tempFile;

  file = fopen(fullPath, "rb");
  tempFile = fopen(tempFullPath, "wb");
  if(file == NULL || tempFile == NULL)
    return false;

  int numberAdmins;
  fread(&numberAdmins, sizeof(int), 1, file);
  fseek(file, 0, SEEK_SET);
  numberAdmins--;
  fwrite(&numberAdmins, sizeof(int), 1, tempFile);

  Admins admin;

  for(int i = 0; i <= numberAdmins; i++){
    if(i != id-1){
      getAdmin(&admin, i+1);
      fwrite(&admin, sizeof(Admins), 1, tempFile);
    }
  }

  fclose(file);
  fclose(tempFile);

  remove(fullPath);
  rename(tempFullPath, fullPath);

  return true;
}

void addNewAdmin(){
  char platformPath[FILE_PATH_LENGTH], fullPath[EXTRA_PATH_LENGTH];
  getPlatformFilePath(platformPath, PLATFORM_PATH_ENV, PLATFORM_FOLDER);
  FILE* file = NULL;

  snprintf(fullPath, sizeof(fullPath), "%s%s", platformPath, "admin/admins.dat");
  file = fopen(fullPath, "rb+");
  if(file == NULL){
    return;
  }

  Admins admin;
  memset(&admin, 0, sizeof(Admins));
  clearConsole();
  printf("New User\n");
  printf("Username: ");
  getString(admin.username, 100);
  printf("Password: ");
  getString(admin.password, 100);

  int number;
  fread(&number, sizeof(int), 1, file);
  fseek(file, 0, SEEK_SET);
  number++;
  fwrite(&number, sizeof(int), 1, file);

  fseek(file, 0, SEEK_END);
  fwrite(&admin, sizeof(Admins), 1, file);

  fclose(file);
}


int getNumberAdmins(){
  char platformPath[FILE_PATH_LENGTH], fullPath[EXTRA_PATH_LENGTH];
  getPlatformFilePath(platformPath, PLATFORM_PATH_ENV, PLATFORM_FOLDER);
  FILE* file = NULL;

  snprintf(fullPath, sizeof(fullPath), "%s%s", platformPath, "admin/admins.dat");
  file = fopen(fullPath, "rb");
  if(file == NULL){
    return false;
  }

  int number;
  fseek(file, 0, SEEK_SET);
  fread(&number, sizeof(int), 1, file);

  fclose(file);
  return number;
}


bool getAdmin(Admins* admin, int id){
  char platformPath[FILE_PATH_LENGTH], fullPath[EXTRA_PATH_LENGTH];
  getPlatformFilePath(platformPath, PLATFORM_PATH_ENV, PLATFORM_FOLDER);
  FILE* file = NULL;

  snprintf(fullPath, sizeof(fullPath), "%s%s", platformPath, "admin/admins.dat");
  file = fopen(fullPath, "rb");
  if(file == NULL){
    return false;
  }

  fseek(file, sizeof(int) + (id-1) * sizeof(Admins), SEEK_SET);
  fread(admin, sizeof(Admins), 1, file);

  fclose(file);

  return true;
}


int loginAdmin(){
  char platformPath[FILE_PATH_LENGTH], fullPath[EXTRA_PATH_LENGTH];
  getPlatformFilePath(platformPath, PLATFORM_PATH_ENV, PLATFORM_FOLDER);
  FILE* file = NULL;

  snprintf(fullPath, sizeof(fullPath), "%s%s", platformPath, "admin/admins.dat");
  file = fopen(fullPath, "rb");
  if(file == NULL){
    return 0;
  }

  do{
    int counter = 0;
    char username[100], password[100];

    printf("Username: ");
    getString(username, 100);
    printf("Password: ");
    getString(password, 100);


    Admins admin;
    do{
      fseek(file, sizeof(int) + counter * sizeof(Admins), SEEK_SET);
      fread(&admin, sizeof(Admins), 1, file);
      if(strcmp(admin.username, username) == 0 && strcmp(admin.password, password) == 0){
        return counter+1;
      }
      counter++;
    }while(!feof(file));
  }while(askConfirmation("Wrong username or Password. Try Again"));

  fclose(file);
  return 0;
}
