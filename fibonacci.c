#include <stdio.h>
#include <stdlib.h>

double num1;
double num2;
int num3;
double temp;

void add(void);

int main(int argc, char *argv[]) {
  char *endptr;
  char *endptr2;
  if (argc != 3) {
    printf("Usage: ./fibonacci num1 num2\n");
    return 10;
  }
  num1 = strtod(argv[1], &endptr);
  if (endptr == argv[1]) {
    printf("num1 and num2 must be numbers");
    return 1;
  }
  num2 = strtod(argv[2], &endptr2);
  if (endptr2 == argv[2]) {
    printf("num1 and num2 must be numbers");
    return 1;
  }
  printf("Enter number of iterations (after first 2 numbers): \n");
  if (scanf("%d", &num3) != 1) {
    printf("Invalid iteration count!\n");
    return 3;
  } else if (num3 <= 0) {
    printf("Must be greater than 0\n");
    return 4;
  }
  printf("%.0lf, %.0lf, ", num1, num2);
  for (int i = 0; i < num3 - 1; i++) {
    add();
    printf(", ");
  }
  add();
  printf("\n");
}

void add(void) {
  temp = num1 + num2;
  num1 = num2;
  num2 = temp;
  printf("%.0lf", temp);
}
