#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

typedef struct {int x; int y;} Point;

char* read_file(const char* path, const char** a_error) {
    FILE* file = fopen(path, "r");
    fseek(file, 0, SEEK_END);
    int file_length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* content = malloc(sizeof(*content) * file_length);
    fread(content, sizeof(*content), file_length, file);
    return content;
}


void write_file(const char* path, const char* contents, const char** a_error) {
	FILE* file = fopen(path, "w");
	if(file==NULL || ferror(file)){
		*a_error = strerror(errno);
		return;
	}
	int file_length = strlen(contents);
	fwrite(contents, sizeof(*contents), file_length, file);
	fclose(file);
	return;
}


void write_point(const char* path, Point p, const char** a_error) {
	FILE* file = fopen(path, "w");
	fwrite(&p, sizeof(Point), 1, file);
	fclose(file);
	return;
}


Point read_point(const char* path, const char** a_error) {
	Point p={.x=0,.y=0};
	FILE* file = fopen(path, "r");
	fread(&p, sizeof(Point), 1, file);
	fclose(file);
	return p;
}