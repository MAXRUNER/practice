#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int id;
  char name[50];
  int age;
  float grade;
} Student;

typedef struct {
  Student *students;
  int size;
  int capacity;
} Database;

void load_database(Database *db) {
  FILE *file = fopen("database.dat", "rb");

  if (file == NULL) {
    return;
  }

  Student student;

  while (fread(&student, sizeof(Student), 1, file) == 1) {
    if (db->size == db->capacity) {
      db->capacity *= 2;

      Student *temp = realloc(db->students, db->capacity * sizeof(Student));

      if (temp == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        exit(1);
      }

      db->students = temp;
    }

    db->students[db->size] = student;
    db->size++;
  }

  fclose(file);
}

void save_database(Database *db) {
  FILE *file = fopen("database.dat", "wb");

  if (file == NULL) {
    printf("Could not save database.\n");
    return;
  }

  fwrite(db->students, sizeof(Student), db->size, file);

  fclose(file);
}

void print_student(Student *student) {
  printf("%d | %s | %d | %.2f\n", student->id, student->name, student->age,
         student->grade);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: ./database <command>\n");
    return 1;
  }

  Database db;

  db.size = 0;
  db.capacity = 10;

  db.students = malloc(db.capacity * sizeof(Student));

  if (db.students == NULL) {
    printf("Memory allocation failed.\n");
    return 1;
  }

  load_database(&db);

  char *endptr;

  // adding stuff
  if (strcmp(argv[1], "add") == 0) {
    if (argc != 2) {
      printf("Usage: ./database add\n");
      free(db.students);
      return 1;
    }

    if (db.size == db.capacity) {
      db.capacity *= 2;

      Student *temp = realloc(db.students, db.capacity * sizeof(Student));

      if (temp == NULL) {
        printf("Memory allocation failed.\n");
        free(db.students);
        return 1;
      }

      db.students = temp;
    }

    Student *student = &db.students[db.size];

    printf("Student ID: ");
    if (scanf("%d", &student->id) != 1) {
      printf("Invalid ID.\n");
      free(db.students);
      return 1;
    }

    // check for duplicate ids
    for (int i = 0; i < db.size; i++) {
      if (db.students[i].id == student->id) {
        printf("A student with that ID already exists.\n");
        free(db.students);
        return 1;
      }
    }

    printf("Student Name: ");
    if (scanf("%49s", student->name) != 1) {
      printf("Invalid name.\n");
      free(db.students);
      return 1;
    }

    printf("Student Age: ");
    if (scanf("%d", &student->age) != 1) {
      printf("Invalid age.\n");
      free(db.students);
      return 1;
    }

    printf("Student Grade: ");
    if (scanf("%f", &student->grade) != 1) {
      printf("Invalid grade.\n");
      free(db.students);
      return 1;
    }

    db.size++;

    save_database(&db);

    printf("Student added.\n");
  }

  // DELETE
  else if (strcmp(argv[1], "delete") == 0) {
    if (argc != 3) {
      printf("Usage: ./database delete <id>\n");
      free(db.students);
      return 1;
    }

    long id = strtol(argv[2], &endptr, 10);

    if (endptr == argv[2] || *endptr != '\0') {
      printf("Invalid ID.\n");
      free(db.students);
      return 1;
    }

    int found = 0;

    for (int i = 0; i < db.size; i++) {
      if (db.students[i].id == id) {
        found = 1;

        for (int j = i; j < db.size - 1; j++) {
          db.students[j] = db.students[j + 1];
        }

        db.size--;
        break;
      }
    }

    if (found) {
      save_database(&db);
      printf("Student deleted.\n");
    } else {
      printf("Student not found.\n");
    }
  }
  // search for shi
  else if (strcmp(argv[1], "search") == 0) {
    if (argc != 4) {
      printf("Usage: ./database search <field> <value>\n");
      free(db.students);
      return 1;
    }

    int found = 0;

    // SEARCH ID
    if (strcmp(argv[2], "id") == 0) {
      long id = strtol(argv[3], &endptr, 10);

      if (endptr == argv[3] || *endptr != '\0') {
        printf("Invalid ID.\n");
        free(db.students);
        return 1;
      }

      for (int i = 0; i < db.size; i++) {
        if (db.students[i].id == id) {
          print_student(&db.students[i]);
          found = 1;
        }
      }
    }

    // search for a name
    else if (strcmp(argv[2], "name") == 0) {
      for (int i = 0; i < db.size; i++) {
        if (strcmp(db.students[i].name, argv[3]) == 0) {
          print_student(&db.students[i]);
          found = 1;
        }
      }
    }

    // search for an age
    else if (strcmp(argv[2], "age") == 0) {
      long age = strtol(argv[3], &endptr, 10);

      if (endptr == argv[3] || *endptr != '\0') {
        printf("Invalid age.\n");
        free(db.students);
        return 1;
      }
      for (int i = 0; i < db.size; i++) {
        if (db.students[i].age == age) {
          print_student(&db.students[i]);
          found = 1;
        }
      }
    }
    // search for a grade
    else if (strcmp(argv[2], "grade") == 0) {
      float grade = strtof(argv[3], &endptr);

      if (endptr == argv[3] || *endptr != '\0') {
        printf("Invalid grade.\n");
        free(db.students);
        return 1;
      }
      for (int i = 0; i < db.size; i++) {
        if (db.students[i].grade == grade) {
          print_student(&db.students[i]);
          found = 1;
        }
      }
    } else {
      printf("Unknown search field.\n");
      free(db.students);
      return 1;
    }

    if (!found) {
      printf("No matching student found.\n");
    }
  }
  // find func
  else if (strcmp(argv[1], "find") == 0) {
    if (argc != 3) {
      printf("Usage: ./database find <partial-name>\n");
      free(db.students);
      return 1;
    }

    int found = 0;

    for (int i = 0; i < db.size; i++) {
      if (strstr(db.students[i].name, argv[2]) != NULL) {
        print_student(&db.students[i]);
        found = 1;
      }
    }

    if (!found) {
      printf("No matching student found.\n");
    }
  }

  // list func
  else if (strcmp(argv[1], "list") == 0) {
    if (argc != 2) {
      printf("Usage: ./database list\n");
      free(db.students);
      return 1;
    }
    if (db.size == 0) {
      printf("Database is empty.\n");
    }
    for (int i = 0; i < db.size; i++) {
      print_student(&db.students[i]);
    }
  } else {
    printf("Unknown command: %s\n", argv[1]);
    free(db.students);
    return 1;
  }
  free(db.students);
  return 0;
}
