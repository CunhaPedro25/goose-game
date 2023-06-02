#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef struct question{
  char question[500];
  char answer[100];
  char wrongAnswers[3][100];
}Questions;

typedef struct questionNode{
    Questions data;
    struct questionNode* next;
}QuestionNode;


void insertAtHead(QuestionNode* head, Questions *data);
void freeQuestionList(QuestionNode* head);

int getNumberQuestions(char *filepath);
bool createQuestionFile(char *filePath);
bool editQuestionFile(char *filePath, Questions question, int line);
bool deleteQuestionFromFile(char *filePath, int line);
bool addToQuestionFile(char *filePath, Questions question);
Questions* getQuestion(char *filePath, int line);

bool storeRandomizedQuestions(char *filepath, QuestionNode* head);
Questions* getQuestionFromList(QuestionNode* head);


/* Questions with True or False answers */
int getNumberBoolQuestions();
bool editBoolQuestion(int line, Questions newQuestion);
bool deleteBoolQuestion(int line);
bool addNewBoolQuestion(Questions newQuestion);
Questions* getBoolQuestion(int line);

// Game functions for bool questions
bool verifyBoolQuestion(char *correctAnswer, int userAnswer);
bool storeRandomizedBoolQuestions(QuestionNode* head);
/*----------------*/


/* Questions with Multiple choice answers (4 options) */
int getNumberMultipleChoiceQuestions();
bool editMultipleChoiceQuestion(int line, Questions newQuestion);
bool deleteMultipleChoiceQuestion(int line);
bool addNewMultipleChoiceQuestion(Questions newQuestion);
Questions* getMultipleChoiceQuestion(int line);

// Game functions for multiple choice questions
int getCorrectAnswerIndex(char correctAnswer[100], char wrongAnswers[3][100]);
bool storeRandomizedMultipleChoiceQuestions(QuestionNode* head);
/*----------------*/


/* Questions with Written answers */
int getNumberWrittenQuestions();
bool editWrittenQuestion(int line, Questions newQuestion);
bool deleteWrittenQuestion(int line);
bool addNewWrittenQuestion(Questions newQuestion);
Questions* getWrittenQuestion(int line);

// Game functions for bool questions
bool verifyWrittenQuestion(char correctAnswer[100], char userAnswer[100]);
bool storeRandomizedWrittenQuestions(QuestionNode* head);
/*----------------*/

#endif
