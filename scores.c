#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *file_ptr;
  char *endptr;
  // Better variable names for once. Idt ill do it consistently though.
  if (argc != 2) {
    printf("./scores (number of students)\n");
    return 1;
  }
  int line = strtol(argv[1], &endptr, 10);
  if (endptr == argv[1] || *endptr != '\0' || line <= 0) {
    printf("Usage: ./scores (positive number of students)\n");
    return 1;
  }

  file_ptr = fopen("example.txt", "w");
  if (file_ptr == NULL) {
    printf("Error: Could not open the file.\n");
    return 1;
  }

  typedef struct {
    int id;
    char name[50];
    float marks;
  } Student;
  Student *students = malloc(line * sizeof(Student));
  if (students == NULL) {
    printf("Memory allocation failed\n");
    fclose(file_ptr);
    return 1;
  }

  for (int i = 0; i < line; i++) {
    students[i].id = i;
    printf("Student %d Name: ", i + 1);
    if (scanf("%49s", students[i].name) != 1) {
      printf("Could not save student name");
      free(students);
      fclose(file_ptr);
      return 1;
    }
    printf("Student %d Marks: ", i + 1);
    if (scanf("%f", &students[i].marks) != 1) {
      printf("Could not save student marks");
      free(students);
      fclose(file_ptr);
      return 1;
    }
    fprintf(file_ptr, "%d %s %.2f\n", students[i].id, students[i].name,
            students[i].marks);
  }
  for (int i = 0; i < line; i++) {
    printf("%d | %s | %.2f\n", students[i].id, students[i].name,
           students[i].marks);
  }
  fclose(file_ptr);
  free(students);
  return 0;
}
