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

void str_concat(char* dest, char* source) {
	int i;
	for (i = 0; dest[i] != '\0'; i++);
	for (int j = 0; source[j] != '\0'; j++, i++) {
		dest[i] = source[j];
	}
	dest[i] = '\0';
}

void append_file(char* file, char* line) {
	while (1) {
		read_line(line);
		if (str_len(line) == 1 && line[0] == '.')
			break;
		str_concat(file, line);
	}
}

void print_buffer(char* buffer) {
	if (buffer == NULL || str_len(buffer) == 0)
		return;
	for (int i = 0; buffer[i] != '\0'; ++i)
		printf("%c", buffer[i]);
	printf("\n");
}

int main(int argc, char* argv[]) {
	char* line = malloc(BUF_SIZE);
	char* file = malloc(BUF_SIZE);

	if (argc > 2) {
		printf("Multiple arguments passed, please only enter one file name...");
		exit(1);
	}
	if (argc == 2) {
		// TODO: This should be a separate function
		// Read existing file
		FILE *fp = fopen(argv[1], "r");
		if (fp == NULL) {
			printf("Could not read file");
			return 0;
		}
		int c, i = 0;
		while ((c = fgetc(fp)) != EOF) {
			file[i++] = c;
		}
		fclose(fp);
	}

	if (line == NULL || file == NULL) {
		printf("Could not allocate buffer.\n");
		exit(0);
	}

	while(1) {
		printf(">");
		read_line(line);

		// Check if input is a command
		if (str_len(line) == 1 && line[0] != ' ') {
			switch (line[0]) {
				case 'q':
					exit(0);
				case 'a':
					append_file(file, line);
					break;
				case 'p':
					print_buffer(file);
					break;
				default:
					printf("Unknown command\n");
					break;
			}
		}
		else
			printf("Unknown command\n");
	}

	free(line);
	free(file);
	return 0;
}
