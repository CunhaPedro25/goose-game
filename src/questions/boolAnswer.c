#include "questions.h"

int getNumberBoolQuestions(){
  return getNumberQuestions("boolQuestions.dat");
}

bool editBoolQuestion(int line, Questions newQuestion){
  return editQuestionFile("boolQuestions.dat", newQuestion, line);
}

// This is stupid. Too bad!
bool deleteBoolQuestion(int line){
  return deleteQuestionFromFile("boolQuestions.dat", line);
}

bool addNewBoolQuestion(Questions newQuestion){
  return addToQuestionFile("boolQuestions.dat", newQuestion);
}

// This is also stupid. Too bad!
Questions* getBoolQuestion(int line){
  return getQuestion("boolQuestions.dat", line);
}

/* Functions used for Game */
bool verifyBoolQuestion(char *correctAnswer, int userAnswer){
  return userAnswer && strcmp(correctAnswer, "True") == 0 ? true : userAnswer != 1 && strcmp(correctAnswer, "False") == 0 ? true : false;
}

bool storeRandomizedBoolQuestions(QuestionNode* head){
  return storeRandomizedQuestions("boolQuestions.dat", head);
}
