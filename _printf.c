#include "main.h"

/**
 * _printf - print formated
 * @format: string which contains %
 * Return: number of printed letters
*/

int _printf(const char *format, ...)
{
	va_list ap;
	char buffer[BUFF_SIZE];
	int index = 0, index2 = 0, printed = 0, value = 0;

	if (!format)
		return (-1);
	va_start(ap, format);
	for (index2 = 0; format[index2] != '\0'; index2++)
		if (format[index2] == '%')
		{
			value = call_funcs(format, &index2, buffer, &index, ap);
			if (value != -1)
			{
				printed += value;
				index2++;
				continue;
			}
			write(1, buffer, index);
			return (value);
		}
		else
			printed += add_char(buffer, format[index2], &index);
	va_end(ap);
	return (printed + write(1, buffer, index));
}
