#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// only works for non-negative INTEGER exponent values
int main(int argc, char *argv[]) {
  char *endptr;
  int term;
  char *endptr2;
  double x = 0;
  double y = 1;
  if (argc != 3) {
    printf("Usage: ./polynomial (Number of terms) (number to evaluate the "
           "function at)");
    return 1;
  }
  long temp = strtol(argv[1], &endptr, 10);
  if (endptr == argv[1] || *endptr != '\0') {
    printf("The number of terms must be a number");
    return 2;
  }
  term = temp;
  if (term < 1) {
    printf("The number of terms must be greater than 0");
    return 3;
  }
  double temp2 = strtod(argv[2], &endptr2);
  if (endptr2 == argv[2] || *endptr2 != '\0') {
    printf("The number to evaluate at must be a real number");
    return 4;
  }
  double num = temp2;

  struct poly {
    double c;
    int expo;
  };
  struct poly terms[term];

  for (int i = 0; i < term; i++) {
    printf("Exponent for term %i: ", i + 1);
    if (scanf("%i", &terms[i].expo) != 1) {
      printf("Invalid Exponent");
      return 5;
    }
    if (terms[i].expo < 0) {
      printf("Exponent must be a non-negative integer value");
      return 6;
    }
    printf("Coefficient for term %i: ", i + 1);
    if (scanf("%lf", &terms[i].c) != 1) {
      printf("Invalid Coefficient");
      return 7;
    }
  }
  // for each term, we have to take terms[i].c * argv[2]^terms[i].expo
  for (int z = 0; z < term; z++) {
    y = 1;
    for (int j = 0; j < terms[z].expo; j++) {
      y *= num;
    }
    x += terms[z].c * y;
  }
  printf("The value of your expression when x = %lf is %lf\n", num, x);
  return 0;
  // yes i know that i shouldve swapped x and num, but as the saying goes:
  // If it ain't broken, it don't need fixing
}
