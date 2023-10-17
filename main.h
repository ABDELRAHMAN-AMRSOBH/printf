#ifndef PRINTF_LIBRARY
#define PRINTF_LIBRARY

#define BUFF_SIZE 1024

#include <stdarg.h>
#include <unistd.h>

int add_char(char *buffer, char c, int *index);
int add_string(char *buffer, char *t, int *index, char *de_fault);
int get_length(unsigned long number, int base);
int change_base(char *buffer, int *index, unsigned int num, int base, int fla);
int print_int(char *buffer, int *index, int num);
int _printf(const char *format, ...);
int print_string(char *s, char *b, int *i);
int print_address(char *b, int *i, unsigned long num);
int rev_str(char *b, int *i, char *s);
int shift_R(char *b, int *i, char *s);
int call_funcs(const char *format, int *i, char *buffer, int *ind, va_list ap);

#endif
