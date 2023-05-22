#include "questions.h"

BoolNode* head = NULL;

int getNumberBoolQuestions(){
  FILE *file = NULL;
  file = fopen("./boolQuestions.dat", "rb");
  if(file == NULL){
    return -1;
  }

  int numBoolQuestions = 0;
  fread(&numBoolQuestions, sizeof(int), 1, file);

  fclose(file);
  return numBoolQuestions;
}

bool createBoolQuestionsFile(){
  FILE *file = NULL;

  file = fopen("boolQuestions.dat", "wb");
  if(file == NULL){
    return false;
  }

  int numBoolQuestions = 0;
  fwrite(&numBoolQuestions, sizeof(int), 1, file);

  fclose(file);

  return true;
}

bool addNewBoolQuestion(char question[500], bool answer){
  FILE *file = NULL;

  file = fopen("boolQuestions.dat", "rb+");
  if(file == NULL){
    // File doesn't exist, create it and initialize the number of questions to 0
    createBoolQuestionsFile();

    // Open the file again in rb+ mode to append new questions
    file = fopen("boolQuestions.dat", "rb+");
    if(file == NULL){
      return false;
    }
  }

  BoolQuestion newQuestion;
  strncpy(newQuestion.question, question, sizeof(newQuestion.question));
  newQuestion.answer = answer;

  fseek(file, 0, SEEK_END);
  fwrite(&newQuestion, sizeof(BoolQuestion), 1, file);

  int numBoolQuestions = getNumberBoolQuestions();
  if(numBoolQuestions == -1){
    return false;
  }
  numBoolQuestions++;
  fseek(file, 0, SEEK_SET);
  fwrite(&numBoolQuestions, sizeof(int), 1, file);

  fclose(file);

  return true;
}

/* Function to insert in to the linked list */
void insertAtHead(BoolQuestion data){
    BoolNode* newNode = (BoolNode*)malloc(sizeof(BoolNode));
    newNode->data = data;
    newNode->next = head;
    head = newNode;
}

bool storeRandomizeBoolQuestions(){
    // Step 1: Read questions from binary file and store in array
    FILE* file = fopen("boolQuestions.dat", "rb");
    if(file == NULL){
        printf("Failed to open file\n");
        return false;
    }

    int numQuestions;
    fread(&numQuestions, sizeof(int), 1, file);

    BoolQuestion* questionArray = (BoolQuestion*)malloc(numQuestions * sizeof(BoolQuestion));
    fread(questionArray, sizeof(BoolQuestion), numQuestions, file);

    fclose(file);

    // Step 2: Generate random permutation of array indices
    int* indices = (int*)malloc(numQuestions * sizeof(int));
    for(int i = 0; i < numQuestions; i++){
        indices[i] = i;
    }

    srand(time(NULL));
    for(int i = numQuestions - 1; i > 0; i--){
        int j = rand() % (i + 1);
        int temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }

    // Step 3: Traverse array using random permutation and insert into linked list
    for(int i = 0; i < numQuestions; i++){
        insertAtHead(questionArray[indices[i]]);
    }

    free(indices);
    free(questionArray);

    return true;
}

void freeBoolQuestionList(){
  while (head != NULL) {
    BoolNode* next = head->next;
    free(head);
    head = next;
  }
}


BoolQuestion* getQuestion(){
    if(head == NULL){
        printf("No more questions\n");
        return NULL;
    }

    // Store the first question in the list into a new variavel
    BoolQuestion* question = (BoolQuestion*)malloc(sizeof(BoolQuestion));
    question->answer = head->data.answer;
    strcpy(question->question, head->data.question);

    // Remove the first element of the list
    BoolNode* temp = head;
    head = head->next;
    free(temp);

    // Return the question
    return question;
}
