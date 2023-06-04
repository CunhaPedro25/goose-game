#include "questions.h"

#define FILE_PATH_LENGTH 256
#define EXTRA_PATH_LENGTH 512

#ifdef _WIN32
    #define PLATFORM_PATH_ENV "LOCALAPPDATA"
    #define PLATFORM_FOLDER "gooseGame\\questions\\"
#elif __linux__
    #define PLATFORM_PATH_ENV "HOME"
    #define PLATFORM_FOLDER "gooseGame/questions/"
#elif __APPLE__
    #define PLATFORM_PATH_ENV "HOME"
    #define PLATFORM_FOLDER "Applications/gooseGame/questions/"
#endif

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

int getNumberQuestions(char *filePath){
  char platformPath[FILE_PATH_LENGTH];
  getPlatformFilePath(platformPath);

  char fullPath[FILE_PATH_LENGTH];
  sprintf(fullPath, "%s%s", platformPath, filePath);

  FILE *file = NULL;
  file = fopen(fullPath, "rb");
  if(file == NULL){
    return -1;
  }

  int numQuestions = 0;
  fread(&numQuestions, sizeof(int), 1, file);

  fclose(file);
  return numQuestions;
}

bool editQuestionFile(char *filePath, Questions question, int line){
  char platformPath[FILE_PATH_LENGTH];
  getPlatformFilePath(platformPath);

  char fullPath[FILE_PATH_LENGTH];
  sprintf(fullPath, "%s%s", platformPath, filePath);

  FILE *file = fopen(fullPath, "rb+");
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
  char platformPath[FILE_PATH_LENGTH];
  getPlatformFilePath(platformPath);

  char fullPath[FILE_PATH_LENGTH];
  sprintf(fullPath, "%s%s", platformPath, filePath);

  char tempFullPath[FILE_PATH_LENGTH];
  sprintf(fullPath, "%s%s", platformPath, filePath);

  FILE *file, *tempFile;

  file = fopen(fullPath, "rb");
  tempFile = fopen(tempFullPath, "wb");
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

  remove(fullPath);
  rename(tempFullPath, fullPath);

  return true;
}

bool addToQuestionFile(char *filePath, Questions question){
  char platformPath[FILE_PATH_LENGTH];
  getPlatformFilePath(platformPath);

  char fullPath[FILE_PATH_LENGTH];
  sprintf(fullPath, "%s%s", platformPath, filePath);

  FILE *file = fopen(fullPath, "rb+");
  if(file == NULL){
    return false;
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
  char platformPath[FILE_PATH_LENGTH];
  getPlatformFilePath(platformPath);

  char fullPath[FILE_PATH_LENGTH];
  sprintf(fullPath, "%s%s", platformPath, filePath);

  FILE *file = fopen(fullPath, "rb");
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
bool storeRandomizedQuestions(char *filePath, QuestionNode** head){
  int numQuestions = getNumberQuestions(filePath);
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
    getQuestion(filePath, &question, indices[i]);
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
  char platformPath[FILE_PATH_LENGTH], fullPath[EXTRA_PATH_LENGTH];
  getPlatformFilePath(platformPath);

  if (!createFolder(platformPath)) {
    printf("Error creating folder: %s\n", platformPath);
  }

  FILE *boolQuestions, *multipleChoiceQuestions, *writtenQuestions;

  snprintf(fullPath, EXTRA_PATH_LENGTH, "%s%s", platformPath, "/boolQuestions.dat");
  boolQuestions = fopen(fullPath, "rb");
  if (boolQuestions == NULL) {
      boolQuestions = fopen(fullPath, "wb");
      if (boolQuestions == NULL) {
          printf("Error creating boolQuestions.dat file.\n");
          return;
      }

      int numQuestions = 0;
      fseek(boolQuestions, 0, SEEK_SET);
      fwrite(&numQuestions, sizeof(int), 1, boolQuestions);
      fclose(boolQuestions);

      Questions boolQuestions[] = {
        { "Is the Earth round?", "True"},
        { "Is the sky green?", "False"},
        { "Does 1 + 1 equal 3?", "False"},
        { "Is water wet?", "True"},
        { "Are dogs mammals?", "True"},
        { "Is the capital of France Paris?", "True"},
        { "Is the sun a planet?", "False"},
        { "Is the moon made of cheese?", "False"},
        { "Is fire a living organism?", "False"},
        { "Is the speed of light faster than sound?", "True"},
        { "Is a tomato a fruit?", "True"},
        { "Is the Atlantic Ocean the largest ocean?", "False"},
        { "Is the human brain pink?", "False"},
        { "Is a square a type of rectangle?", "True"},
        { "Is the Statue of Liberty located in London?", "False"},
        { "Is the Great Wall of China visible from space?", "False"},
        { "Is chocolate a vegetable?", "False"},
        { "Is gravity a force?", "True"},
        { "Is the Earth the third planet from the sun?", "True"},
        { "Is the Sahara Desert the largest desert in the world?", "False"},
        { "Is the Statue of Liberty green?", "True"},
        { "Is the Pacific Ocean the deepest ocean?", "True"},
        { "Is an ostrich able to fly?", "False"},
        { "Is the Amazon River the longest river in the world?", "True"},
        { "Is the Eiffel Tower located in Italy?", "False"},
        { "Is the human body made up of cells?", "True"},
        { "Is a lemon a citrus fruit?", "True"},
        { "Is the Nile River located in Africa?", "True"},
        { "Is the speed of sound faster than light?", "False"},
        { "Is a triangle a polygon?", "True"},
        { "Are elephants smaller than ants?", "False"},
        { "Is the Earth the largest planet in the solar system?", "False"},
        { "Is the North Pole located in Antarctica?", "False"},
        { "Are all birds capable of flight?", "False"},
        { "Is the human skeleton made of rubber?", "False"},
        { "Is the planet Mars closer to the Sun than Earth?", "False"},
        { "Are all snakes venomous?", "False"},
        { "Is the human heart located in the chest?", "True"},
        { "Is the number zero an even number?", "True"},
        { "Are all metals magnetic?", "False"},
        { "Is the Amazon Rainforest the largest rainforest in the world?", "True"},
        { "Is the Mona Lisa a famous painting by Leonardo da Vinci?", "True"},
        { "Is the Statue of Liberty taller than the Eiffel Tower?", "False"},
        { "Are all insects capable of flying?", "False"},
        { "Is the planet Saturn known for its prominent rings?", "True"},
        { "Is the Great Barrier Reef located in South America?", "False"},
        { "Is the human liver the largest internal organ?", "True"},
        { "Is the number pi equal to 3.14?", "True"},
        { "Are all mammals warm-blooded?", "True"},
        { "Is the Sahara Desert the coldest place on Earth?", "False"},
        { "Is the planet Neptune the farthest from the Sun?", "True"},
        { "Is the color purple a primary color?", "False"},
        { "Is the planet Venus larger than the planet Earth?", "False"},
        { "Are all planets in our solar system named after gods?", "False"},
        { "Is the human skin the largest organ?", "True"},
        { "Is the number one considered an odd number?", "True"},
        { "Are all flowers capable of photosynthesis?", "False"},
        { "Is the Great Wall of China the longest man-made structure?", "True"},
        { "Is the planet Mercury the hottest planet in our solar system?", "True"},
        { "Is the color black considered a shade?", "True"},
        { "Are all spiders venomous?", "False"},
        { "Is the human eye responsible for vision?", "True"},
        { "Is the number ten a prime number?", "False"},
        { "Are all deserts extremely hot?", "False"},
        { "Is the planet Jupiter composed mostly of gas?", "True"},
        { "Is the color orange a secondary color?", "True"},
        { "Are all fruits sweet?", "False"},
        { "Is the Great Barrier Reef the largest coral reef in the world?", "True"},
        { "Is the planet Uranus the smallest planet in our solar system?", "False"},
        { "Is the color white the absence of color?", "True"},
        { "Are all fish capable of swimming?", "True"},
        { "Is the human nose responsible for smelling?", "True"},
        { "Is the number two considered a prime number?", "True"},
        { "Are all rocks made of the same minerals?", "False"},
        { "Is the planet Pluto considered a dwarf planet?", "True"},
        { "Is the color green a primary color?", "True"},
        { "Are all birds warm-blooded?", "True"},
        { "Is the Sahara Desert the driest place on Earth?", "True"},
        { "Is the planet Mars known for its red color?", "True"},
        { "Is the color pink a shade of red?", "True"},
        { "Are all vegetables considered fruits?", "False"},
        { "Is the Grand Canyon located in Canada?", "False"},
        { "Is the planet Earth the only known planet with life?", "True"},
        { "Is the color blue a primary color?", "True"},
        { "Are all mammals capable of laying eggs?", "False"},
        { "Is the Sahara Desert the largest hot desert in the world?", "True"},
        { "Is the planet Venus known as the morning star?", "True"},
        { "Is the color yellow a secondary color?", "True"},
        { "Are all birds capable of singing?", "False"},
        { "Is the Amazon River the longest river in South America?", "True"},
        { "Is the number five considered a prime number?", "True"},
        { "Are all clouds made of the same type of gas?", "False"},
        { "Is the planet Saturn known for its many moons?", "True"},
        { "Is the color red a primary color?", "True"},
        { "Are all mammals capable of flying?", "False"},
        { "Is the Sahara Desert the largest desert in Africa?", "True"},
        { "Is the planet Neptune known for its blue color?", "True"},
        { "Is the color brown considered a shade?", "True"},
        { "Are all reptiles cold-blooded?", "True"},
        { "Is the Nile River the longest river in Africa?", "True"},
        { "Is the number seven considered a prime number?", "True"},
        { "Are all trees capable of producing fruits?", "False"},
        { "Is the planet Jupiter known for its giant storm called the Great Red Spot?", "True"},
        { "Is the color purple a secondary color?", "True"},
        { "Are all insects considered pests?", "False"},
        { "Is the Amazon Rainforest the largest rainforest in South America?", "True"},
        { "Is the number three considered a prime number?", "True"},
        { "Are all metals conductive?", "False"},
        { "Is the planet Uranus known for its rings?", "True"},
        { "Is the color black the absence of color?", "True"},
        { "Are all snakes venomous?", "False"},
        { "Is the human brain responsible for thinking?", "True"},
        { "Is the number zero considered a positive number?", "False"},
        { "Are all flowers capable of reproducing?", "True"},
        { "Is the Great Wall of China the longest man-made structure on Earth?", "True"},
        { "Is the planet Mercury known for its extreme temperatures?", "True"},
        { "Is the color orange a primary color?", "True"},
        { "Are all fruits considered healthy?", "False"},
        { "Is the Great Barrier Reef the largest coral reef in Australia?", "True"},
        { "Is the planet Uranus the largest planet in our solar system?", "False"},
        { "Is the color white considered a shade?", "True"},
        { "Are all fish capable of breathing underwater?", "True"},
        { "Is the human heart responsible for pumping blood?", "True"},
        { "Is the number one considered a natural number?", "True"},
        { "Are all rocks made of the same type of rock?", "False"},
        { "Is the planet Pluto no longer considered a planet?", "True"},
        { "Is the color green a secondary color?", "True"},
        { "Are all birds capable of flying?", "False"},
        { "Is the Sahara Desert the driest desert on Earth?", "True"},
        { "Is the planet Mars known for its reddish appearance?", "True"},
        { "Is the color pink a shade of purple?", "False"},
        { "Are all vegetables considered healthy?", "False"},
        { "Is the Grand Canyon located in the United States?", "True"},
        { "Is the planet Earth the only known planet with intelligent life?", "Unknown"},
        { "Is the color blue a primary color?", "True"},
        { "Are all mammals capable of swimming?", "False"},
        { "Is the Sahara Desert the largest desert in the world?", "True"},
        { "Is the planet Venus known as the evening star?", "True"},
        { "Is the color yellow a secondary color?", "True"},
        { "Are all birds capable of flying?", "False"},
        { "Is the Amazon River the longest river in South America?", "True"},
        { "Is the number five considered a natural number?", "True"},
        { "Are all clouds made of the same type of cloud?", "False"},
        { "Is the planet Saturn known for its beautiful rings?", "True"},
        { "Is the color red a primary color?", "True"},
        { "Are all mammals capable of hibernating?", "False"},
        { "Is the Sahara Desert the largest desert in Africa?", "True"},
        { "Is the planet Neptune known for its blue appearance?", "True"},
        { "Is the color brown considered a shade of black?", "False"},
        { "Are all reptiles considered dangerous?", "False"},
        { "Is the Nile River the longest river in Africa?", "True"},
        { "Is the number seven considered a natural number?", "True"},
        { "Are all trees capable of growing fruits?", "False"},
        { "Is the planet Jupiter known for its massive size?", "True"},
        { "Is the color purple a secondary color?", "True"},
        { "Are all insects considered beneficial?", "False"},
        { "Is the Amazon Rainforest the largest rainforest in the world?", "True"},
        { "Is the number three considered a natural number?", "True"},
        { "Are all metals considered solid?", "False"},
        { "Is the planet Uranus known for its unique rotation?", "True"},
        { "Is the color black considered a shade of white?", "False"},
        { "Are all snakes considered venomous?", "False"},
        { "Is the human brain responsible for memory?", "True"},
        { "Is the number zero considered a whole number?", "True"},
        { "Are all flowers capable of attracting insects?", "True"},
        { "Is the Great Wall of China the longest wall in the world?", "True"},
        { "Is the planet Mercury known for its crater-filled surface?", "True"},
        { "Is the color orange a secondary color?", "True"},
        { "Are all fruits considered juicy?", "False"},
        { "Is the Great Barrier Reef the largest coral reef in the world?", "True"},
        { "Is the planet Uranus the smallest planet in our solar system?", "False"},
        { "Is the color white considered a shade of black?", "False"},
        { "Are all fish capable of living in saltwater?", "False"},
        { "Is the human heart responsible for pumping oxygen?", "True"},
        { "Is the number one considered a whole number?", "True"},
        { "Are all rocks made of the same type of material?", "False"},
        { "Is the planet Pluto considered a planet?", "False"},
        { "Is the color green a primary color?", "True"},
        { "Are all birds capable of swimming?", "False"},
        { "Is the Sahara Desert the hottest desert on Earth?", "True"},
        { "Is the planet Mars known for its two moons?", "True"},
        { "Is the color pink a shade of red?", "True"},
        { "Are all vegetables considered nutritious?", "True"},
        { "Is the Grand Canyon located in Arizona?", "True"},
        { "Is the planet Earth the only known planet with water?", "True"},
        { "Is the color blue a primary color?", "True"},
        { "Are all mammals considered nocturnal?", "False"},
        { "Is the Sahara Desert the largest hot desert in the world?", "True"},
        { "Is the planet Venus known for its extreme temperatures?", "True"},
        { "Is the color yellow a secondary color?", "True"},
        { "Are all birds capable of swimming?", "False"},
        { "Is the Amazon River the longest river in the world?", "True"},
        { "Is the number five considered a whole number?", "True"},
        { "Are all clouds made of the same type of gas?", "False"},
        { "Is the planet Saturn known for its distinct rings?", "True"},
        { "Is the color red a primary color?", "True"},
        { "Are all mammals considered herbivores?", "False"},
        { "Is the Sahara Desert the largest desert on Earth?", "True"},
        { "Is the planet Neptune known for its stormy weather?", "True"},
        { "Is the color brown considered a shade?", "True"},
        { "Are all reptiles considered venomous?", "False"},
        { "Is the Nile River the longest river in the world?", "True"},
        { "Is the number seven considered a whole number?", "True"},
        { "Are all trees considered evergreen?", "False"},
        { "Is the planet Jupiter known for its many moons?", "True"},
        { "Is the color purple considered a warm color?", "False"}
      };


      for (int i = 0; i < sizeof(boolQuestions) / sizeof(boolQuestions[0]); i++) {
        addNewBoolQuestion(boolQuestions[i]);
      }
  }

  snprintf(fullPath, EXTRA_PATH_LENGTH, "%s%s", platformPath, "/multipleChoiceQuestions.dat");
  multipleChoiceQuestions = fopen(fullPath, "rb");
  if (multipleChoiceQuestions == NULL) {
      multipleChoiceQuestions = fopen(fullPath, "wb");
      if (multipleChoiceQuestions == NULL) {
          printf("Error creating multipleChoiceQuestions.dat file.\n");
          return;
      }

      int numQuestions = 0;
      fwrite(&numQuestions, sizeof(int), 1, multipleChoiceQuestions);
      fclose(multipleChoiceQuestions);

      Questions multipleChoiceQuestions[] = {
        { "What is the largest country by land area?",
          "Russia",
          { "Canada", "China", "United States" }
        },
        { "Who is the author of 'The Lord of the Rings'?",
          "J.R.R. Tolkien",
          { "C.S. Lewis", "George R.R. Martin", "J.K. Rowling" }
        },
        { "Which country is known for the Statue of Liberty?",
          "United States",
          { "United Kingdom", "France", "Italy" }
        },
        { "What is the largest desert in the world?",
          "Sahara Desert",
          { "Gobi Desert", "Arabian Desert", "Atacama Desert" }
        },
        { "Who is the author of 'The Odyssey'?",
          "Homer",
          { "Virgil", "Sophocles", "Euripides" }
        },
        { "Which country is known for the Great Barrier Reef?",
          "Australia",
          { "Brazil", "Mexico", "India" }
        },
        { "Who discovered gravity?",
          "Isaac Newton",
          { "Albert Einstein", "Galileo Galilei", "Nikola Tesla" }
        },
        { "What is the chemical symbol for sodium?",
          "Na",
          { "K", "Mg", "Ca" }
        },
        { "Who wrote the novel 'Moby-Dick'?",
          "Herman Melville",
          { "Mark Twain", "Emily Dickinson", "Nathaniel Hawthorne" }
        },
        { "What is the closest planet to the Sun?",
          "Mercury",
          { "Venus", "Earth", "Mars" }
        },
        { "Which country is known for the Angkor Wat?",
          "Cambodia",
          { "Thailand", "Vietnam", "Indonesia" }
        },
        { "Who painted the 'Girl with a Pearl Earring'?",
          "Johannes Vermeer",
          { "Rembrandt", "Edvard Munch", "Claude Monet" }
        },
        { "What is the deepest ocean in the world?",
          "Pacific Ocean",
          { "Atlantic Ocean", "Indian Ocean", "Arctic Ocean" }
        },
        { "Who is the author of 'War and Peace'?",
          "Leo Tolstoy",
          { "Fyodor Dostoevsky", "Anton Chekhov", "Ivan Turgenev" }
        },
        { "Which country is known for the Parthenon?",
          "Greece",
          { "Egypt", "Italy", "Spain" }
        },
        { "Who discovered electricity?",
          "Benjamin Franklin",
          { "Thomas Edison", "Nikola Tesla", "James Watt" }
        },
        { "What is the chemical symbol for potassium?",
          "K",
          { "Na", "Mg", "Ca" }
        },
        { "Who wrote the play 'Othello'?",
          "William Shakespeare",
          { "George Bernard Shaw", "Samuel Beckett", "Tennessee Williams" }
        },
        { "What is the second-largest planet in our solar system?",
          "Saturn",
          { "Jupiter", "Uranus", "Neptune" }
        },
        { "Which country is known for the Taj Mahal?",
          "India",
          { "China", "Japan", "Thailand" }
        },
        { "Who painted the 'Starry Night'?",
          "Vincent van Gogh",
          { "Pablo Picasso", "Salvador Dalí", "Claude Monet" }
        },
        { "What is the highest mountain in the world?",
          "Mount Everest",
          { "K2", "Kangchenjunga", "Makalu" }
        },
        { "Who is the author of 'Pride and Prejudice'?",
          "Jane Austen",
          { "Charlotte Brontë", "Emily Brontë", "Virginia Woolf" }
        },
        { "Which country is known for the Colosseum?",
          "Italy",
          { "Greece", "France", "Spain" }
        },
        { "Who invented the telephone?",
          "Alexander Graham Bell",
          { "Thomas Edison", "Nikola Tesla", "Guglielmo Marconi" }
        },
        { "What is the chemical symbol for silver?",
          "Ag",
          { "Au", "Cu", "Pt" }
        },
        { "Who wrote the novel 'To Kill a Mockingbird'?",
          "Harper Lee",
          { "John Steinbeck", "F. Scott Fitzgerald", "Ernest Hemingway" }
        },
        { "What is the third planet from the Sun?",
          "Earth",
          { "Venus", "Mars", "Jupiter" }
        },
        { "Which country is known for the Pyramids of Giza?",
          "Egypt",
          { "Mexico", "Greece", "Turkey" }
        },
        { "Who painted the 'Mona Lisa'?",
          "Leonardo da Vinci",
          { "Michelangelo", "Raphael", "Donatello" }
        },
        { "What is the largest waterfall in the world?",
          "Angel Falls",
          { "Niagara Falls", "Victoria Falls", "Iguazu Falls" }
        },
        { "Who is the author of 'The Chronicles of Narnia'?",
          "C.S. Lewis",
          { "J.R.R. Tolkien", "George R.R. Martin", "J.K. Rowling" }
        },
        { "Which country is known for the Eiffel Tower?",
          "France",
          { "United Kingdom", "Germany", "Spain" }
        },
        { "Who painted the 'The Last Supper'?",
          "Leonardo da Vinci",
          { "Michelangelo", "Raphael", "Donatello" }
        },
        { "What is the chemical symbol for gold?",
          "Au",
          { "Ag", "Cu", "Pt" }
        },
        { "Who wrote the play 'Romeo and Juliet'?",
          "William Shakespeare",
          { "Arthur Miller", "Samuel Beckett", "Tennessee Williams" }
        },
        { "What is the fourth planet from the Sun?",
          "Mars",
          { "Venus", "Earth", "Jupiter" }
        },
        { "Which country is known for the Great Wall?",
          "China",
          { "Japan", "South Korea", "India" }
        },
        { "Who painted the 'The Persistence of Memory'?",
          "Salvador Dalí",
          { "Pablo Picasso", "Vincent van Gogh", "Claude Monet" }
        },
        { "What is the highest waterfall in the United States?",
          "Yosemite Falls",
          { "Niagara Falls", "Victoria Falls", "Angel Falls" }
        },
        { "Who is the author of '1984'?",
          "George Orwell",
          { "Aldous Huxley", "Ray Bradbury", "Kurt Vonnegut" }
        },
        { "What is the fifth planet from the Sun?",
          "Jupiter",
          { "Venus", "Earth", "Mars" }
        },
        { "Which country is known for the Machu Picchu?",
          "Peru",
          { "Brazil", "Chile", "Argentina" }
        },
        { "Who painted the 'The Scream'?",
          "Edvard Munch",
          { "Pablo Picasso", "Vincent van Gogh", "Claude Monet" }
        },
        { "What is the longest river in the world?",
          "Nile River",
          { "Amazon River", "Mississippi River", "Yangtze River" }
        },
        { "Who is the author of 'The Great Gatsby'?",
          "F. Scott Fitzgerald",
          { "Ernest Hemingway", "John Steinbeck", "Harper Lee" }
        },
        { "What is the sixth planet from the Sun?",
          "Saturn",
          { "Venus", "Mars", "Jupiter" }
        },
        { "Which country is known for the Petra?",
          "Jordan",
          { "Egypt", "Saudi Arabia", "Lebanon" }
        },
        { "Who painted the 'Water Lilies'?",
          "Claude Monet",
          { "Pablo Picasso", "Salvador Dalí", "Vincent van Gogh" }
        },
        { "What is the tallest mountain in North America?",
          "Denali",
          { "Mount Everest", "K2", "Kangchenjunga" }
        },
        { "Who is the author of 'The Catcher in the Rye'?",
          "J.D. Salinger",
          { "Mark Twain", "Harper Lee", "Emily Dickinson" }
        },
        { "What is the seventh planet from the Sun?",
          "Uranus",
          { "Venus", "Mars", "Jupiter" }
        },
        { "Which country is known for the Stonehenge?",
          "United Kingdom",
          { "France", "Germany", "Spain" }
        },
        { "Who painted the 'The Starry Night'?",
          "Vincent van Gogh",
          { "Pablo Picasso", "Salvador Dalí", "Claude Monet" }
        },
        { "What is the largest bay in the world?",
          "Hudson Bay",
          { "San Francisco Bay", "Chesapeake Bay", "Bay of Bengal" }
        },
        { "Who is the author of 'Moby-Dick'?",
          "Herman Melville",
          { "Mark Twain", "Emily Dickinson", "Nathaniel Hawthorne" }
        },
        { "What is the eighth planet from the Sun?",
          "Neptune",
          { "Venus", "Mars", "Jupiter" }
        },
        { "Which country is known for the Alhambra?",
          "Spain",
          { "Italy", "Greece", "Portugal" }
        },
        { "Who painted the 'The Birth of Venus'?",
          "Sandro Botticelli",
          { "Leonardo da Vinci", "Michelangelo", "Raphael" }
        },
        { "What is the largest lake in Africa?",
          "Lake Victoria",
          { "Lake Tanganyika", "Lake Malawi", "Lake Chad" }
        },
        { "Who is the author of 'The Hobbit'?",
          "J.R.R. Tolkien",
          { "C.S. Lewis", "George R.R. Martin", "J.K. Rowling" }
        },
        { "What is the ninth planet from the Sun?",
          "Pluto",
          { "Venus", "Mars", "Jupiter" }
        },
        { "Which country is known for the Acropolis?",
          "Greece",
          { "Egypt", "Italy", "Spain" }
        },
        { "Who painted the 'The Last Judgment'?",
          "Michelangelo",
          { "Leonardo da Vinci", "Raphael", "Donatello" }
        },
        { "What is the largest canyon in the world?",
          "Grand Canyon",
          { "Copper Canyon", "Fish River Canyon", "Yarlung Tsangpo Grand Canyon" }
        },
        { "Who is the author of 'The Grapes of Wrath'?",
          "John Steinbeck",
          { "Ernest Hemingway", "F. Scott Fitzgerald", "Harper Lee" }
        },
        { "What is the tenth planet from the Sun?",
          "No answer",
          { "Venus", "Mars", "Jupiter" }
        },
        { "What is the largest desert in the world?",
          "Sahara Desert",
          { "Gobi Desert", "Arabian Desert", "Atacama Desert" }
        },
        { "Who is the author of 'The Odyssey'?",
          "Homer",
          { "Virgil", "Sophocles", "Euripides" }
        },
        { "Which country is known for the Great Barrier Reef?",
          "Australia",
          { "Brazil", "Mexico", "India" }
        },
        { "Who discovered gravity?",
          "Isaac Newton",
          { "Albert Einstein", "Galileo Galilei", "Nikola Tesla" }
        },
        { "What is the chemical symbol for sodium?",
          "Na",
          { "K", "Mg", "Ca" }
        },
        { "Who wrote the novel 'Moby-Dick'?",
          "Herman Melville",
          { "Mark Twain", "Emily Dickinson", "Nathaniel Hawthorne" }
        },
        { "What is the closest planet to the Sun?",
          "Mercury",
          { "Venus", "Earth", "Mars" }
        },
        { "Which country is known for the Angkor Wat?",
          "Cambodia",
          { "Thailand", "Vietnam", "Indonesia" }
        },
        { "Who painted the 'Girl with a Pearl Earring'?",
          "Johannes Vermeer",
          { "Rembrandt", "Edvard Munch", "Claude Monet" }
        },
        { "What is the deepest ocean in the world?",
          "Pacific Ocean",
          { "Atlantic Ocean", "Indian Ocean", "Arctic Ocean" }
        },
        { "Who is the author of 'War and Peace'?",
          "Leo Tolstoy",
          { "Fyodor Dostoevsky", "Anton Chekhov", "Ivan Turgenev" }
        },
        { "Which country is known for the Parthenon?",
          "Greece",
          { "Egypt", "Italy", "Spain" }
        },
        { "Who discovered electricity?",
          "Benjamin Franklin",
          { "Thomas Edison", "Nikola Tesla", "James Watt" }
        },
        { "What is the chemical symbol for potassium?",
          "K",
          { "Na", "Mg", "Ca" }
        },
        { "Who wrote the play 'Othello'?",
          "William Shakespeare",
          { "George Bernard Shaw", "Samuel Beckett", "Tennessee Williams" }
        },
        { "What is the largest planet in the solar system?",
          "Jupiter",
          { "Saturn", "Uranus", "Neptune" }
        },
        { "Which country is known for the Pyramids of Giza?",
          "Egypt",
          { "Mexico", "China", "Greece" }
        },
        { "Who painted the 'Starry Night'?",
          "Vincent van Gogh",
          { "Pablo Picasso", "Leonardo da Vinci", "Michelangelo" }
        },
        { "What is the highest mountain in the world?",
          "Mount Everest",
          { "K2", "Kangchenjunga", "Makalu" }
        },
        { "Who is the author of 'Pride and Prejudice'?",
          "Jane Austen",
          { "Emily Brontë", "Charlotte Brontë", "Virginia Woolf" }
        },
        { "Which country is known for the Taj Mahal?",
          "India",
          { "Japan", "China", "South Korea" }
        },
        { "Who discovered the theory of relativity?",
          "Albert Einstein",
          { "Isaac Newton", "Max Planck", "Werner Heisenberg" }
        },
        { "What is the chemical symbol for iron?",
          "Fe",
          { "Au", "Ag", "Cu" }
        },
        { "Who wrote the novel 'To Kill a Mockingbird'?",
          "Harper Lee",
          { "John Steinbeck", "F. Scott Fitzgerald", "Ernest Hemingway" }
        },
        { "What is the largest ocean in the world?",
          "Pacific Ocean",
          { "Atlantic Ocean", "Indian Ocean", "Southern Ocean" }
        },
        { "Who is the author of '1984'?",
          "George Orwell",
          { "Aldous Huxley", "Ray Bradbury", "J.D. Salinger" }
        },
        { "Which country is known for the Colosseum?",
          "Italy",
          { "Spain", "France", "Greece" }
        }
      };

      for (int i = 0; i < sizeof(multipleChoiceQuestions) / sizeof(multipleChoiceQuestions[0]); i++) {
        addNewMultipleChoiceQuestion(multipleChoiceQuestions[i]);
      }
  }


  snprintf(fullPath, EXTRA_PATH_LENGTH, "%s%s", platformPath, "/writtenQuestions.dat");
  writtenQuestions = fopen(fullPath, "rb");
  if (writtenQuestions == NULL) {
    writtenQuestions = fopen(fullPath, "wb");
    if (writtenQuestions == NULL) {
        printf("Error creating writtenQuestions.dat file.\n");
        return;
    }

    int numQuestions = 0;
    fwrite(&numQuestions, sizeof(int), 1, writtenQuestions);
    fclose(writtenQuestions);

    Questions directAnswerQuestions[] = {
      { "What is the capital of France?", "Paris" },
      { "Who painted the Mona Lisa?", "Leonardo da Vinci" },
      { "What is the largest planet in our solar system?", "Jupiter" },
      { "Who wrote the play 'Hamlet'?", "William Shakespeare" },
      { "What is the chemical symbol for gold?", "Au" },
      { "Who is the author of the novel 'One Hundred Years of Solitude'?", "Gabriel Garcia Marquez" },
      { "What is the tallest mountain in the world?", "Mount Everest" },
      { "Who discovered penicillin?", "Alexander Fleming" },
      { "What is the capital of Australia?", "Canberra" },
      { "Who painted the 'Sistine Chapel Ceiling'?", "Michelangelo" },
      { "What is the currency of Japan?", "Japanese yen" },
      { "Who wrote the play 'Macbeth'?", "William Shakespeare" },
      { "What is the chemical symbol for iron?", "Fe" },
      { "Who was the first person to walk on the moon?", "Neil Armstrong" },
      { "What is the capital of Brazil?", "Brasilia" },
      { "Who painted the 'Guernica'?", "Pablo Picasso" },
      { "What is the largest continent in the world?", "Asia" },
      { "Who is the author of the novel '1984'?", "George Orwell" },
      { "What is the currency of Germany?", "Euro" },
      { "Who wrote the play 'The Crucible'?", "Arthur Miller" },
      { "What is the chemical symbol for silver?", "Ag" },
      { "Who composed the symphony 'Symphony No. 9 in D minor'?", "Ludwig van Beethoven" },
      { "What is the capital of South Africa?", "Pretoria" },
      { "Who painted the 'The Starry Night'?", "Vincent van Gogh" },
      { "What is the smallest country in the world?", "Vatican City" },
      { "Who is the author of the novel 'Pride and Prejudice'?", "Jane Austen" },
      { "What is the currency of Canada?", "Canadian dollar" },
      { "Who wrote the novel 'Crime and Punishment'?", "Fyodor Dostoevsky" },
      { "What is the capital of Italy?", "Rome" },
      { "Who painted the 'The Persistence of Memory'?", "Salvador Dalí" },
      { "What is the currency of Mexico?", "Mexican peso" },
      { "Who composed the symphony 'Symphony No. 5 in C minor'?", "Ludwig van Beethoven" },
      { "What is the capital of Spain?", "Madrid" },
      { "Who painted the 'The Last Supper'?", "Leonardo da Vinci" },
      { "What is the currency of India?", "Indian rupee" },
      { "Who wrote the novel 'The Great Gatsby'?", "F. Scott Fitzgerald" },
      { "What is the capital of China?", "Beijing" },
      { "Who painted the 'The Birth of Venus'?", "Sandro Botticelli" },
      { "What is the currency of France?", "Euro" },
      { "Who composed the symphony 'Symphony No. 6 in F major'?", "Ludwig van Beethoven" },
      { "What is the capital of Canada?", "Ottawa" },
      { "Who painted the 'Water Lilies'?", "Claude Monet" },
      { "What is the currency of United Kingdom?", "Pound sterling" },
      { "Who wrote the novel 'Moby-Dick'?", "Herman Melville" },
      { "What is the capital of Russia?", "Moscow" },
      { "Who painted the 'The Creation of Adam'?", "Michelangelo" },
      { "What is the currency of Brazil?", "Brazilian real" },
      { "Who is the author of the novel 'To Kill a Mockingbird'?", "Harper Lee" },
      { "What is the capital of Argentina?", "Buenos Aires" },
      { "Who painted the 'The Girl with a Pearl Earring'?", "Johannes Vermeer" },
      { "What is the currency of South Korea?", "South Korean won" },
      { "Who wrote the play 'Romeo and Juliet'?", "William Shakespeare" },
      { "What is the chemical symbol for sodium?", "Na" },
      { "Who composed the symphony 'Symphony No. 9 in E minor (From the New World)'?", "Antonín Dvořák" },
      { "What is the capital of Egypt?", "Cairo" },
      { "Who painted the 'The Thinker'?", "Auguste Rodin" },
      { "What is the currency of Saudi Arabia?", "Saudi riyal" },
      { "Who is the author of the novel 'The Catcher in the Rye'?", "J.D. Salinger" },
      { "What is the capital of Germany?", "Berlin" },
      { "Who painted the 'The Night Watch'?", "Rembrandt" },
      { "What is the currency of Australia?", "Australian dollar" },
      { "Who wrote the play 'A Midsummer Night's Dream'?", "William Shakespeare" },
      { "What is the chemical symbol for calcium?", "Ca" },
      { "Who composed the symphony 'Symphony No. 9 in D major (Choral)'?", "Ludwig van Beethoven" },
      { "What is the capital of Japan?", "Tokyo" },
      { "Who painted the 'American Gothic'?", "Grant Wood" },
      { "What is the currency of Spain?", "Euro" },
      { "Who is the author of the novel 'The Lord of the Rings'?", "J.R.R. Tolkien" },
      { "What is the capital of United States?", "Washington, D.C." },
      { "Who painted the 'The Creation of Adam'?", "Michelangelo" },
      { "What is the currency of Italy?", "Euro" },
      { "Who wrote the play 'Othello'?", "William Shakespeare" },
      { "What is the chemical symbol for potassium?", "K" },
      { "Who composed the symphony 'Symphony No. 3 in E-flat major (Eroica)'?", "Ludwig van Beethoven" },
      { "What is the capital of India?", "New Delhi" },
      { "Who painted the 'The Persistence of Memory'?", "Salvador Dalí" },
      { "What is the currency of Canada?", "Canadian dollar" },
      { "Who is the author of the novel 'The Hobbit'?", "J.R.R. Tolkien" },
      { "What is the capital of France?", "Paris" },
      { "Who painted the 'The Starry Night'?", "Vincent van Gogh" },
      { "What is the currency of Mexico?", "Mexican peso" },
      { "Who wrote the play 'King Lear'?", "William Shakespeare" },
      { "What is the chemical symbol for magnesium?", "Mg" },
      { "Who composed the symphony 'Symphony No. 5 in C-sharp minor (Adagietto)'?", "Gustav Mahler" },
      { "What is the capital of Brazil?", "Brasília" },
      { "Who painted the 'The Scream'?", "Edvard Munch" },
      { "What is the currency of United Kingdom?", "British pound" },
      { "Who is the author of the novel '1984'?", "George Orwell" },
      { "What is the capital of China?", "Beijing" },
      { "Who painted the 'The Last Supper'?", "Leonardo da Vinci" },
      { "What is the currency of Germany?", "Euro" },
      { "Who wrote the play 'Macbeth'?", "William Shakespeare" },
      { "What is the chemical symbol for iron?", "Fe" },
      { "Who composed the symphony 'Symphony No. 6 in F major (Pastoral)'?", "Ludwig van Beethoven" },
      { "What is the capital of Australia?", "Canberra" },
      { "Who painted the 'The Birth of Venus'?", "Sandro Botticelli" },
      { "What is the currency of India?", "Indian rupee" },
      { "Who is the author of the novel 'Pride and Prejudice'?", "Jane Austen" },
      { "What is the capital of South Africa?", "Pretoria" },
      { "What is the currency of Russia?", "Russian ruble" },
      { "Who wrote the play 'The Tempest'?", "William Shakespeare" },
      { "What is the chemical symbol for copper?", "Cu" },
      { "Who composed the symphony 'Symphony No. 7 in A major'?", "Ludwig van Beethoven" }
    };

    for (int i = 0; i < sizeof(directAnswerQuestions) / sizeof(directAnswerQuestions[0]); i++) {
        addNewWrittenQuestion(directAnswerQuestions[i]);
    }
  }

}
