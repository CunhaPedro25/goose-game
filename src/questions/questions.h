#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#ifdef _WIN32
    #include <windows.h>
#elif __linux__
    #include <sys/stat.h>
    #include<unistd.h>
#elif __APPLE__
    #include <sys/stat.h>
    #include<unistd.h>
#endif

#include "../utils/functions/functions.h"

typedef struct question{
  char question[500];
  char answer[100];
  char wrongAnswers[3][100];
}Questions;

typedef struct questionNode{
    Questions data;
    struct questionNode* next;
}QuestionNode;

void freeQuestionList(QuestionNode* head);
void installQuestionFiles();

int getNumberQuestions(char *filepath);
bool createQuestionFile(char *filePath);
bool editQuestionFile(char *filePath, Questions question, int line);
bool deleteQuestionFromFile(char *filePath, int line);
bool addToQuestionFile(char *filePath, Questions question);
bool getQuestion(char *filePath, Questions* question, int line);
int searchForQuestion(char *filePath, char *search);

bool storeRandomizedQuestions(char *filepath, QuestionNode** head);
bool getQuestionFromList(QuestionNode** head, Questions* question);


/* Questions with True or False answers */
int getNumberBoolQuestions();
bool editBoolQuestion(int line, Questions newQuestion);
bool deleteBoolQuestion(int line);
bool addNewBoolQuestion(Questions newQuestion);
bool getBoolQuestion(Questions* question, int line);
int searchForBoolQuestion(char *search);

// Game functions for bool questions
bool verifyBoolQuestion(char *correctAnswer, int userAnswer);
bool storeRandomizedBoolQuestions(QuestionNode** head);
/*----------------*/


/* Questions with Multiple choice answers (4 options) */
int getNumberMultipleChoiceQuestions();
bool editMultipleChoiceQuestion(int line, Questions newQuestion);
bool deleteMultipleChoiceQuestion(int line);
bool addNewMultipleChoiceQuestion(Questions newQuestion);
bool getMultipleChoiceQuestion(Questions* question, int line);
int searchForMultipleChoiceQuestion(char *search);

// Game functions for multiple choice questions
int getCorrectAnswerIndex(char correctAnswer[100], char wrongAnswers[3][100]);
bool storeRandomizedMultipleChoiceQuestions(QuestionNode** head);
/*----------------*/


/* Questions with Written answers */
int getNumberWrittenQuestions();
bool editWrittenQuestion(int line, Questions newQuestion);
bool deleteWrittenQuestion(int line);
bool addNewWrittenQuestion(Questions newQuestion);
bool getWrittenQuestion(Questions* question, int line);
int searchForWrittenQuestion(char *search);

// Game functions for bool questions
bool storeRandomizedWrittenQuestions(QuestionNode** head);
/*----------------*/

#endif
