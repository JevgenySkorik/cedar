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
	dest[i] = '\n';
	dest[i+1] = '\0';
}

void append_buffer(char* file, char* line) {
	while (1) {
		read_line(line);
		if (str_len(line) == 1 && line[0] == '.') {
			break;
		}
		str_concat(file, line);
	}
}

void print_buffer(char* buffer) {
	if (buffer == NULL || str_len(buffer) == 0)
		return;
	for (int i = 0; buffer[i] != '\0'; ++i)
		printf("%c", buffer[i]);
}

void print_line(char* buffer, unsigned int line_number) {
	if (buffer == NULL || str_len(buffer) == 0)
		return;
	unsigned int current_line = 1;
	for (int i = 0; buffer[i] != '\0'; ++i) {
		if (current_line == line_number)
			printf("%c", buffer[i]);
		if (current_line > line_number)
			return;
		if (buffer[i] == '\n')
			current_line++;
	}
}

void write_file(char* file_name, char* file) {
	FILE *fp = fopen(file_name, "w");
	if (fp == NULL) {
		printf("Could not read file");
		exit(0);
	}
	fprintf(fp, "%s", file);
	fclose(fp);
}

unsigned int read_file(char* file_name, char* file) {
	unsigned int last_line = 0;
	FILE *fp = fopen(file_name, "r");
	if (fp == NULL) {
		printf("Could not read file");
		exit(0);
	}
	int c, i = 0;
	while ((c = fgetc(fp)) != EOF) {
		if (c == '\n')
			last_line++;
		file[i++] = c;
	}
	fclose(fp);
	return last_line;
}

int main(int argc, char* argv[]) {
	char* line = malloc(BUF_SIZE);
	char* file = malloc(BUF_SIZE);
	char* file_name = NULL;
	unsigned int current_line = 1;

	if (argc > 2) {
		printf("Multiple arguments passed, please only enter one file name...");
		exit(1);
	}
	if (argc == 2) {
		file_name = malloc(64);
		file_name = argv[1];
		current_line = read_file(file_name, file);
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
					append_buffer(file, line);
					break;
				case 'w':
					write_file(file_name, file);
					break;
				case 'p':
					print_line(file, current_line);
					break;
				case 'P':
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
	free(file_name);
	return 0;
}
