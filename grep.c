#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: ./grep word filename\n");
    return 1;
  }
  FILE *file = fopen(argv[2], "r");
  if (file == NULL) {
    printf("Error opening file\n");
    return 2;
  }
  char buffer[100];
  size_t bytes_read = fread(buffer, 1, sizeof(buffer) - 1, file);
  buffer[bytes_read] = '\0';
  size_t word_len = strlen(argv[1]);
  int line_number = 1;
  int index = 0;
  while (buffer[index] != '\0') {
    if ((size_t)index + word_len > bytes_read)
      break;
    bool mismatch = false;
    if (buffer[index] == '\n')
      line_number++;
    for (size_t j = 0; j < word_len; j++) {
      if (argv[1][j] != buffer[index + j]) {
        mismatch = true;
        break;
      }
    }
    if (!mismatch) {
      int start = index;
      while (start > 0 && buffer[start - 1] != '\n')
        start--;
      int end = index;
      while (buffer[end] != '\n' && buffer[end] != '\0')
        end++;
      printf("%d: ", line_number);
      fwrite(&buffer[start], 1, end - start, stdout);
      putchar('\n');
      index = end;
      continue;
    }
    index++;
  }
  fclose(file);
  return 0;
}
