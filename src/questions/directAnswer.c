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

Questions* getWrittenQuestion(int line){
  return getQuestion("writtenQuestions.dat", line);
}

/* Functions used for Game */
bool verifyWrittenQuestion(char correctAnswer[100], char userAnswer[100]){
  return strcasecmp(correctAnswer, userAnswer);
}

bool storeRandomizedWrittenQuestions(QuestionNode* head){
  return storeRandomizedQuestions("writtenQuestions.dat", head);
}
