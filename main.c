#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 1024

void read_line(char* line) {
  char c;
  int i = 0;
  while(1) {
    c = getchar();
    if (c == 10) {
      line[i] = '\0';
      return;
    }
    line[i] = c;
    i += 1;
  }
}

int str_len(char* line) {
  int i;
  for (i = 0; line[i] != '\0'; i++);
  return i;
}

void append_file(char* file) {

}

void print_buffer(char* buffer) {
  for (int i = 0; buffer[i] != EOF; ++i)
    printf("%c", buffer[i]);
}

int main(int argc, char* argv[]) {
  char* line = malloc(BUF_SIZE);
  char* file = malloc(BUF_SIZE);

  if (argc > 2) {
    printf("Multiple arguments passed, please only enter one file name...");
    exit(1);
  }
  if (argc == 2) {
    // Read existing file
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
      printf("Could not read file");
      return 0;
    }
    for (int i = 0; !feof(fp); i++) {
      file[i] = fgetc(fp);
    }
    fclose(fp);
  }

  if (line == NULL || file == NULL) {
    printf("Could not allocate buffer.\n");
    exit(0);
  }

  while(1) {
    printf("?");
    read_line(line);

    // Check if input is a command
    if (str_len(line) == 1 && line[0] != ' ') {
      //printf("command is: %c\n", line[0]);
      switch (line[0]) {
        case 'q':
          exit(0);
        case 'a':
          //append_file(file);
          break;
        case 'p':
          print_buffer(file);
          break;

        default:
          printf("Unknown command\n");
          break;
      }
    }
    //printf("stored line: %s, line length: %d\n", line, str_len(line));
  }

  free(line);
  return 0;
}
