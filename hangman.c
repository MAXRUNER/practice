#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 40
// If the user types in more than one letter as their guess, then the code will
// take each individual letter as a guess and check For example, if the user has
// - - - - as their current word, and they type easy when the word is actually
// hard The code will check e, then a, s and then y and remove 3 lives since e,
// s and y are not in the word
int main(void) {
  int lives = 5;
  char g;

  char dict[SIZE][37] = {
      "bad",         "easy",       "lol",        "Hurt",       "Goon",
      "code",        "hate",       "kill",       "ice",        "fire",
      "hangman",     "destroy",    "computer",   "book",       "dictionary",
      "technology",  "power",      "thunder",    "controller", "dexterity",
      "keyboard",    "thunderous", "blizzard",   "hazardous",  "algorithm",
      "destruction", "operation",  "assignment", "despicable", "tiger",
      "lion",        "elephant",   "zebra",      "horse",      "camel",
      "deer",        "crocodile",  "rabbit",     "cat"};

  srand(time(NULL));
  int x = rand() % SIZE;
  char word[37];
  char copy[37];
  strcpy(word, dict[x]);
  for (int i = 0; word[i] != '\0'; i++) {
    word[i] = tolower(word[i]);
  }
  for (int i = 0; i < strlen(word); i++) {
    copy[i] = '-';
  }
  copy[strlen(word)] = '\0';
  while (lives > 0) {
    printf("\nWord: %s\n", copy);
    printf("Lives: %d\n", lives);
    printf("What is your letter guess? ");
    if (scanf(" %c", &g) != 1) {
      printf("Invalid guess\n");
      return 1;
    }
    g = tolower(g);
    int found = 0;

    for (int check = 0; check < strlen(word); check++) {
      if (g == word[check]) {
        copy[check] = g;
        found = 1;
      }
    }
    if (found == 0) {
      printf("Wrong guess!\n");
      lives--;
    }
    if (strcmp(copy, word) == 0) {
      printf("\nWord: %s\n", copy);
      printf("You win!\n");
      return 0;
    }
  }
  printf("\nYou lost! The word was %s\n", word);
  return 0;
}
