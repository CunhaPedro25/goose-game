#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <stdbool.h>

typedef struct boolQuestion{
  char question[500];
  bool answer;
}BoolQuestion;

typedef struct writtenQuestion{
  char question[500];
  char answer[100];
}WrittenQuestion;

typedef struct multipleChoiceQuestion{
  char question[500];
  char correctAnswer[100];
  char wrongAnswers[3][100];
}MultipleChoiceQuestion;

#endif
