#include "questions.h"

void insertAtHead(QuestionNode** head, Questions* data){
  QuestionNode* newNode = (QuestionNode*)malloc(sizeof(QuestionNode));
  newNode->data = *data;
  newNode->next = *head;
  *head = newNode;
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
  FILE *file, *tempFile;

  file = fopen(filePath, "rb");
  tempFile = fopen("tempFile", "wb");
  if(file == NULL || tempFile == NULL)
    return false;

  int numQuestions;
  fread(&numQuestions, sizeof(int), 1, file);
  fseek(file, 0, SEEK_SET);
  numQuestions--;
  fwrite(&numQuestions, sizeof(int), 1, tempFile);

  Questions question;

  for(int i = 0; i < numQuestions; i++){
    if(i != line-1){
      getQuestion(filePath, &question, i+1);
      fwrite(&question, sizeof(Questions), 1, tempFile);
    }
  }

  fclose(file);
  fclose(tempFile);

  remove(filePath);
  rename("tempFile", filePath);

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

bool getQuestion(char *filePath, Questions* question, int line){
  FILE *file = fopen(filePath, "rb");
  if(file == NULL){
    printf("Cant open the question file");
    return false;
  }

  // Calculate the position of the desired line
  long int position = sizeof(int) + (line-1) * sizeof(Questions);

  // Move the file pointer to the calculated position
  fseek(file, position, SEEK_SET);

  fread(question, sizeof(Questions), 1, file);

  return true;
}

// Game function
bool storeRandomizedQuestions(char *filepath, QuestionNode** head){
  int numQuestions = getNumberQuestions(filepath);
  if(numQuestions == -1){
    return false;
  }

  // TODO: Not creating an array of indices
  int *indices;
  indices = (int*)calloc(numQuestions, sizeof(int));
  // Generate random permutation of array indices
  for(int i = 0; i < numQuestions; i++){
      indices[i] = i+1;
  }

  srand(time(NULL));
  for(int i = numQuestions - 1; i > 0; i--){
      int j = rand() % i + 1;
      int temp = indices[i];
      indices[i] = indices[j];
      indices[j] = temp;
  }

  // Traverse array using random permutation and insert into linked list
  Questions question;
  for(int i = 0; i < numQuestions; i++){
    getQuestion(filepath, &question, indices[i]);
    insertAtHead(head, &question);
  }

  free(indices);

  return true;
}

bool getQuestionFromList(QuestionNode** head, Questions* question){
    if(head == NULL || *head == NULL){
      return false;
    }

    memcpy(question, &(*head)->data, sizeof(Questions));

    // Remove the first element of the list
    QuestionNode* temp = *head;
    *head = (*head)->next;
    free(temp);

    // Return the question
    return true;
}


void installQuestionFiles(){
  FILE *boolQuestions, *multipleChoiceQuestions, *writtenQuestions;

  boolQuestions = fopen("boolQuestions.dat", "rb+");
  if(boolQuestions == NULL){
    Questions boolQuestions[5] = {
      { "Is the Earth round?", "True"},
      { "Is the sky green?", "False"},
      { "Does 1 + 1 equal 3?", "False"},
      { "Is water wet?", "True"},
      { "Are dogs mammals?", "True"},
    };

    for(int i = 0; i < 5; i++){
      addNewBoolQuestion(boolQuestions[i]);
    }
  }

  multipleChoiceQuestions = fopen("multipleChoiceQuestions.dat", "rb+");
  if(multipleChoiceQuestions == NULL){
    Questions multipleChoiceQuestions[5] = {
      { "What is the capital of Australia?",
        "Canberra",
        { "Sydney", "Melbourne", "Perth" }
      },
      { "Which planet is known as the 'Red Planet'?",
        "Mars",
        { "Venus", "Jupiter", "Mercury" }
      },
      { "Who is the author of the 'Harry Potter' book series?",
        "J.K. Rowling",
        { "Stephen King", "George R.R. Martin", "Dan Brown" }
      },
      { "Which element has the chemical symbol 'H'?",
        "Hydrogen",
        { "Helium", "Lithium", "Carbon" }
      },
      { "Which famous scientist developed the theory of relativity?",
        "Albert Einstein",
        { "Isaac Newton", "Galileo Galilei", "Marie Curie" }
      }
    };


    for(int i = 0; i < 5; i++){
        addNewMultipleChoiceQuestion(multipleChoiceQuestions[i]);
    }
  }

  writtenQuestions = fopen("writtenQuestions.dat", "rb+");
  if(writtenQuestions == NULL){
    Questions directAnswerQuestions[5] = {
      { "What is the capital of France?", "Paris" },
      { "Who painted the Mona Lisa?", "Leonardo da Vinci" },
      { "What is the largest planet in our solar system?", "Jupiter" },
      { "Who wrote the play 'Hamlet'?", "William Shakespeare" },
      { "What is the chemical symbol for gold?", "Au" },
    };

    for(int i = 0; i < 5; i++){
      addNewWrittenQuestion(directAnswerQuestions[i]);
    }
  }
}
