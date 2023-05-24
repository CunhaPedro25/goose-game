#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


/* Questions with true or false answers */
typedef struct boolQuestion{
  char question[500];
  bool answer;
}BoolQuestion;

typedef struct boolNode{
    BoolQuestion data;
    struct boolNode* next;
}BoolNode;

int getNumberBoolQuestions();
bool addNewBoolQuestion(char question[500], bool answer);

bool storeRandomizeBoolQuestions();
void freeBoolQuestionList();
BoolQuestion* getBoolQuestion();



/* Questions with Multiple choice answers (4 options) */
typedef struct multipleChoiceQuestion{
  char question[500];
  char correctAnswer[100];
  char wrongAnswers[3][100];
}MultipleChoiceQuestion;

typedef struct multipleChoiceNode{
    MultipleChoiceQuestion data;
    struct multipleChoiceNode* next;
}MultipleChoiceNode;




/* Questions with a direct/written answer */
typedef struct writtenQuestion{
  char question[500];
  char answer[100];
}WrittenQuestion;

typedef struct writtenNode{
    WrittenQuestion data;
    struct writtenNode* next;
}WrittenNode;


#endif
