#include "questions.h"

int getNumberWrittenQuestions(){
  return getNumberQuestions("writtenQuestions.dat");
}

bool editWrittenQuestion(int line, Questions newQuestion){
  return editQuestionFile("writtenQuestions.dat", newQuestion, line);
}

bool deleteWrittenQuestion(int line){
  return deleteQuestionFromFile("writtenQuestions.dat", line);
}

bool addNewWrittenQuestion(Questions newQuestion){
  return addToQuestionFile("writtenQuestions.dat", newQuestion);
}

bool getWrittenQuestion(Questions* question, int line){
  return getQuestion("writtenQuestions.dat", question, line);
}

/* Functions used for Game */
bool storeRandomizedWrittenQuestions(QuestionNode** head){
  return storeRandomizedQuestions("writtenQuestions.dat", head);
}
