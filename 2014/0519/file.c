#include <stdio.h>

int getc(FILE *stream);
int fgetc(FILE *stream);
int putc(int c, FILE *stream);
int fputc(int c, FILE *stream);

char* gets(char *s);
char* fgets(char *s, int n, FILE* stream);
int puts(const char* s);
int fputs(const char* s, FILE* stream);

int printf(const char* format, ...);
int fprintf(FILE* stream, const char* format, ...);
int sprintf(char* s, const char* format, ...);

int scanf(const char format, ...);
int fscanf();
int sscanf();


