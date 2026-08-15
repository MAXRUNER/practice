#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
double f(double x, int equation);
double df(double x, int equation);

int main(int argc, char *argv[]) {
  int iter;
  char *endptr;
  double guess;
  char *endptr2;
  double x;
  clock_t start;
  clock_t end;
  if (argc != 3) {
    printf("Usage: ./finding_root (iterations) (first guess)\n");
    return 1;
  }
  long temp = strtol(argv[1], &endptr, 10);
  if (endptr == argv[1] || *endptr != '\0') {
    printf("Iterations must be an integer");
    return 2;
  }
  guess = strtod(argv[2], &endptr2);
  if (endptr2 == argv[2] || *endptr2 != '\0') {
    printf("The first guess must be a number");
    return 3;
  }
  int equa_son;
  int algo;
  printf("Pick one of the options\n1. x^2 - 2\n2. x^3 - x - 2\n3. cos(x) - "
         "x\n4. e^x - 3x\n");
  if (scanf("%d", &equa_son) != 1) {
    printf("Invalid input\n");
    return 4;
  }
  if (equa_son < 1 || equa_son > 4) {
    printf("Invalid input, please choose an interger between 1 and 4\n");
    return 5;
  }
  printf("Which algorithm would you like to utilize?\n1. Newton-Raphson "
         "Method\n2. Secant Method\n");
  if (scanf("%d", &algo) != 1) {
    printf("Invalid input\n");
    return 6;
  }
  if (algo < 1 || algo > 2) {
    printf("Invalid input, please choose an interger between 1 and 2\n");
    return 7;
  }
  /* algo = chosen algorithm
   * guess = initial guess, hopefully through the intermediate value theorem
   * equa_son = chosen equation
   * iter = iterations, aight bet
   * x is the updating value
   */

  /* Take the derivatives of each of the equations
  1. x^2 - 2      -> 2x
  2. x^3 - x - 2  -> 3x^2 - 1
  3. cos(x) - x   -> -sin(x) - 1
  4. e^x - 3x     -> e^x - 3
  */
  iter = temp;
  printf("---------------------------------------------------------------------"
         "\n");
  printf("%-10s %-15s %-15s\n", "Iter", "Guess", "f(x)");
  printf("---------------------------------------------------------------------"
         "\n");
  if (algo == 1) {
    start = clock();
    x = guess;
    for (int i = 0; i < iter + 1; i++) {
      printf("%-10d %-15.8f %-15.8f\n", i, x, f(x, equa_son));
      if (fabs(df(x, equa_son)) < 1e-12) {
        printf("Derivative too close to zero.\n");
        break;
      }
      x = x - (f(x, equa_son) / df(x, equa_son));
    }
    end = clock();
  }
  if (algo == 2) {
    start = clock();
    double x_prev = 1.0;
    double x_curr = guess;
    for (int i = 0; i < iter + 1; i++) {
      double f_prev = f(x_prev, equa_son);
      double f_curr = f(x_curr, equa_son);
      printf("%-10d %-15.8f %-15.8f\n", i, x_curr, f_curr);
      double denominator = f_curr - f_prev;
      if (fabs(denominator) < 1e-12) {
        printf("Secant denominator too close to zero.\n");
        break;
      }
      double x_next = x_curr - f_curr * (x_curr - x_prev) / denominator;
      end = clock();
      x_prev = x_curr;
      x_curr = x_next;
      x = x_curr;
    }
    end = clock();
  }
  printf("After %s iterations, x = %lf\n", argv[1], x);
  if (algo == 2) {
    printf("For the Secant method, we needed two guesses which was too hard to "
           "consider, hence we took your second guess to be defaulted to 1.");
  }
  double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
  printf("Time taken: %f\n", elapsed_time);
}

double f(double x, int equation) {
  switch (equation) {
  case 1:
    return x * x - 2;

  case 2:
    return x * x * x - x - 2;

  case 3:
    return cos(x) - x;

  case 4:
    return exp(x) - 3 * x;
  }
  return NAN;
}

double df(double x, int equation) {
  switch (equation) {
  case 1:
    return 2 * x;

  case 2:
    return 3 * x * x - 1;

  case 3:
    return -sin(x) - 1;

  case 4:
    return exp(x) - 3;
  }
  return NAN;
}
