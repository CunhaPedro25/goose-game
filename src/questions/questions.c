#include "questions.h"

void insertAtHead(QuestionNode* head, Questions *data){
  QuestionNode* newNode = (QuestionNode*)malloc(sizeof(QuestionNode));
  newNode->data = *data;
  newNode->next = head;
  head = newNode;
}

void freeQuestionList(QuestionNode* head){
  while (head != NULL) {
    QuestionNode* next = head->next;
    free(head);
    head = next;
  }
}

int getNumberQuestions(char *filepath){
  FILE *file = NULL;
  file = fopen(filepath, "rb");
  if(file == NULL){
    return -1;
  }

  int numQuestions = 0;
  fread(&numQuestions, sizeof(int), 1, file);

  fclose(file);
  return numQuestions;
}

bool createQuestionFile(char *filePath){
  FILE *file = NULL;

  file = fopen(filePath, "wb");
  if(file == NULL){
    return false;
  }

  int numQuestions = 0;
  fwrite(&numQuestions, sizeof(int), 1, file);

  fclose(file);

  return true;
}

bool editQuestionFile(char *filePath, Questions question, int line){
  FILE *file = fopen(filePath, "rb+");
  if(file == NULL){
    return false;
  }

  // Calculate the position of the desired line
  long int position = sizeof(int) + (line-1) * sizeof(Questions);

  // Move the file pointer to the calculated position
  fseek(file, position, SEEK_SET);
  fwrite(&question, sizeof(Questions), 1, file);

  fclose(file);

  return true;
}

bool deleteQuestionFromFile(char *filePath, int line){
  FILE *file = NULL;

  file = fopen(filePath, "rb");
  if(file == NULL){
    printf("Cant open the question file");
    return false;
  }


  int numQuestions;
  fread(&numQuestions, sizeof(int), 1, file);

  Questions* questionArray = (Questions*)malloc(numQuestions * sizeof(Questions));
  fread(questionArray, sizeof(Questions), numQuestions, file);

  file = fopen("boolQuestions.dat", "wb");

  fseek(file, 0, SEEK_SET);
  numQuestions--;
  fwrite(&numQuestions, sizeof(int), 1, file);

  for(int i = 0; i <= numQuestions; i++){
    if(i != line-1){
      fwrite(&questionArray[i], sizeof(Questions), 1, file);
    }
  }

  fclose(file);

  return true;
}

bool addToQuestionFile(char *filePath, Questions question){
  FILE *file = fopen(filePath, "rb+");
  if(file == NULL){
    // File doesn't exist, create it and initialize the number of questions to 0
    createQuestionFile(filePath);

    // Open the file again in rb+ mode to append new questions
    file = fopen(filePath, "rb+");
    if(file == NULL){
      return false;
    }
  }

  int numQuestions;
  fread(&numQuestions, sizeof(int), 1, file);

  fseek(file, 0, SEEK_END);
  fwrite(&question, sizeof(Questions), 1, file);

  numQuestions++;
  fseek(file, 0, SEEK_SET);
  fwrite(&numQuestions, sizeof(int), 1, file);

  fclose(file);

  return true;
}

Questions* getQuestion(char *filePath, int line){
  FILE *file = fopen(filePath, "rb");
  if(file == NULL){
    printf("Cant open the question file");
    return NULL;
  }

  // Calculate the position of the desired line
  long int position = sizeof(int) + (line-1) * sizeof(Questions);

  // Move the file pointer to the calculated position
  fseek(file, position, SEEK_SET);

  Questions* question = (Questions*)malloc(sizeof(Questions));
  fread(question, sizeof(Questions), 1, file);

  return question;
}

// Game function
bool storeRandomizedQuestions(char *filepath, QuestionNode* head){
  int numQuestions = getNumberQuestions(filepath);
  if(numQuestions == -1){
    return false;
  }

  int *indices = (int*)calloc(numQuestions, sizeof(int));
  // Generate random permutation of array indices
  for(int i = 0; i < numQuestions; i++){
      indices[i] = i+1;
  }

  srand(time(NULL));
  for(int i = numQuestions - 1; i > 0; i--){
      int j = (rand() % i + 1) + 1;
      int temp = indices[i];
      indices[i] = indices[j];
      indices[j] = temp;
  }

  // Traverse array using random permutation and insert into linked list
  for(int i = 0; i < numQuestions; i++){
      insertAtHead(head, getQuestion(filepath, indices[i]));
  }

  free(indices);

  return true;
}

Questions* getQuestionFromList(QuestionNode* head){
    if(head == NULL){
        printf("No more questions\n");
        return NULL;
    }

    // Store the first question in the list into a new variavel
    Questions* question = (Questions*)malloc(sizeof(Questions));
    memcpy(question, &head->data, sizeof(Questions));

    // Remove the first element of the list
    QuestionNode* temp = head;
    head = head->next;
    free(temp);

    // Return the question
    return question;
}
