#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

void change_line(char* line, int current_line, char* file) {
	char* temp = malloc(BUF_SIZE);
	int l = 1;
	int t = 0;
	bool line_changed = 0;
	for (int i = 0; file[i] != '\0'; ++i) {
		if (l == current_line && !line_changed) {
			int j, n; 
			for (j = 0; line[j] != '\0'; ++j)
				temp[t+j] = line[j];
			for (n = i; file[n+1] != '\n'; ++n);
			i = n;
			t += j;
			line_changed = 1;
			continue;
		}
		temp[t++] = file[i];
		if (file[i] == '\n' && file[i+1] != '\0')
			l++;
	}
	strcpy(file, temp);
	free(temp);
}

void print_buffer(char* buffer, bool print_line_numbers) {
	if (buffer == NULL || str_len(buffer) == 0)
		return;
	if (print_line_numbers) {
		int l = 1;
		printf("%d ", l++);
		for (int i = 0; buffer[i] != '\0'; ++i) {
			if (buffer[i] == '\n' && buffer[i+1] != '\0')
				printf("\n%d ", l++);
			else
				printf("%c", buffer[i]);
		}
	}
	else
		for (int i = 0; buffer[i] != '\0'; ++i)
			printf("%c", buffer[i]);
}

void print_line(char* buffer, unsigned int line_number, bool print_line_numbers) {
	if (buffer == NULL || str_len(buffer) == 0)
		return;
	unsigned int current_line = 1;
	for (int i = 0; buffer[i] != '\0'; ++i) {
		if (current_line == line_number)
			printf("%c", buffer[i]);
		if (current_line > line_number)
			return;
		if (buffer[i] == '\n') {
			current_line++;
			if (current_line == line_number && print_line_numbers)
				printf("%d ", line_number);
		}
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

bool char_is_number(char c) {
	if (c > 47 && c < 58)
		return true;
	return false; 
}

unsigned int line_count(char* buffer) {
	unsigned int l = 1;
	for (int i = 0; buffer[i] != '\0'; i++)
		if (buffer[i] == '\n')
			l++;
	return l;
}

bool line_is_number(char* line) {
	if (line[0] == '\0')
		return false;
	for (int n = 0; line[n] != '\0'; n++) {
		if (!char_is_number(line[n]))
			return false;
	}
	return true;
}

bool line_is_change_current_line(char* line) {
	// check for +/- line
	for (int n = 0; line[n] != '\0'; n++) {
		if (line[0] == '+' || line[0] == '-') {
			for (int i = 1; line[i] != '\0'; i++) {
				if (!char_is_number(line[i]))
					return false;
			}
			return true;
		}
	}
	return false;
}

void change_current_line(char* line, unsigned int* current_line) {
	if (line[0] == '+') {

	}
}

void delete_line(char* file, unsigned int* current_line) {
	char* temp = malloc(BUF_SIZE);
	int l = 1;
	int t = 0;
	bool line_deleted = 0;
	for (int i = 0; file[i] != '\0'; ++i) {
		if (l == *current_line && !line_deleted) {
			if (file[i] == '\n' || file[i] == '\0') {
				line_deleted = true;
				l++;
			}
			continue;
		}
		temp[t++] = file[i];
		if (file[i] == '\n' && file[i+1] != '\0')
			l++;
	}
	strcpy(file, temp);
	free(temp);

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
		printf("current: %d, real: %d\n", current_line, line_count(file));
		if (current_line > line_count(file))
			current_line = line_count(file);
		printf(">");
		read_line(line);

		// Check if input is a command
		if (str_len(line) == 1 && line[0] != ' ' && !char_is_number(line[0])) {
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
					print_line(file, current_line, false);
					break;
				case 'P':
					print_buffer(file, false);
					break;
				case 'n':
					print_line(file, current_line, true);
					break;
				case 'N':
					print_buffer(file, true);
					break;
				case 'c':
					read_line(line);
					change_line(line, current_line, file);
					break;
				case 'd':
					delete_line(file, &current_line);
					break;
				default:
					printf("Unknown command\n");
					break;
			}
		}
		else if (line_is_number(line)) {
			unsigned int user_entered_line = atoi(line);
			if (user_entered_line > 0 && user_entered_line < line_count(file))
				current_line = user_entered_line;
			else
				printf("Unknown command\n");
		}
		//else if (line_is_change_current_line(line)) {
			//printf("old current_line: %d\n", current_line);
			//change_current_line(line, &current_line);
			//printf("new current_line: %d\n", current_line);
		//}
		else
			printf("Unknown command\n");
	}

	free(line);
	free(file);
	free(file_name);
	return 0;
}
