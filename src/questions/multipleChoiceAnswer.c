#include "questions.h"

int getNumberMultipleChoiceQuestions(){
  return getNumberQuestions("multipleChoiceQuestions.dat");
}

bool editMultipleChoiceQuestion(int line, Questions newQuestion){
  return editQuestionFile("multipleChoiceQuestions.dat", newQuestion, line);
}

bool deleteMultipleChoiceQuestion(int line){
  return deleteQuestionFromFile("multipleChoiceQuestions.dat", line);
}

bool addNewMultipleChoiceQuestion(Questions newQuestion){
  return addToQuestionFile("multipleChoiceQuestions.dat", newQuestion);
}

bool getMultipleChoiceQuestion(Questions* question, int line){
  return getQuestion("multipleChoiceQuestions.dat", question, line);
}


/* Functions used for Game */
int getCorrectAnswerIndex(char correctAnswer[100], char wrongAnswers[3][100]){
  // Generate a random seed
  srand(time(NULL));

  // Create a new array to hold all the answers
  const char* answers[4];

  // Set the correct answer
  answers[0] = correctAnswer;

  // Set the wrong answers
  answers[1] = wrongAnswers[0];
  answers[2] = wrongAnswers[1];
  answers[3] = wrongAnswers[2];

  // Shuffle the answers using Fisher-Yates algorithm
  for (int i = 3; i > 0; --i) {
      int j = rand() % (i + 1);
      const char* temp = answers[i];
      answers[i] = answers[j];
      answers[j] = temp;
  }

  // Find the index of the correct answer
  int correctIndex = -1;
  for (int i = 0; i < 4; ++i) {
      printf("%d - %s\n", i + 1, answers[i]);
      if (strcmp(answers[i], correctAnswer) == 0) {
          correctIndex = i + 1;
      }
  }

  return correctIndex;
}

bool storeRandomizedMultipleChoiceQuestions(QuestionNode** head){
  return storeRandomizedQuestions("MultipleChoiceQuestions.dat", head);
}
