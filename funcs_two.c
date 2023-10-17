#include "main.h"

/**
 * print_string - prints string after converting single chars into their value
 * @s: string
 * @b: buffer to place string to be printed
 * @i: pointer to index
 * Return: number of printed chars
*/

int print_string(char *s, char *b, int *i)
{
	int printed = 0;
	unsigned int symbol = 0;

	while (*s)
	{
		if (*s > 31 && *s < 127)
			printed += add_char(b, *s, i);
		else
		{
			printed += add_char(b, '\\', i);
			symbol = *s;
			printed += add_char(b, 'x', i);
			if (symbol < 16)
				printed += add_char(b, '0', i);
			printed += change_base(b, i, symbol, 16, 0);
		}
		s++;
	}
	return (printed);
}

/**
 * print_address - save address into buffer to be printed
 * @b: buffer
 * @i: pointer to index of buffer
 * @num: address
 * Return: number of printed chars
*/

int print_address(char *b, int *i, unsigned long num)
{
	int length = get_length(num, 16);
	char t[65];

	if (!num)
		return (add_string(b, "(nil)", i, "(nil)"));
	t[length--] = '\0';
	do {
		if (num % 16 == 10)
			t[length] = 'a';
		else if (num % 16 == 11)
			t[length] = 'b';
		else if (num % 16 == 12)
			t[length] = 'c';
		else if (num % 16 == 13)
			t[length] = 'd';
		else if (num % 16 == 14)
			t[length] = 'e';
		else if (num % 16 == 15)
			t[length] = 'f';
		else
			t[length] = '0' + num % 16;
		length--, num /= 16;
	} while (num);
	return (add_string(b, "0x", i, "0") + add_string(b, t, i, "0"));
}

/**
 * rev_str - reverse string place it into buffer
 * @b: buffer
 * @i: pointer to index of buffer
 * @s: string
 * Return: printed chars
*/

int rev_str(char *b, int *i, char *s)
{
	int j = 0, c = 0;

	if (!s)
		s = "(null)";
	while (s[j])
		j++;
	while (j--)
		c += add_char(b, s[j], i);
	return (c);
}

/**
 * shift_R - shift the content of s by 13
 * @b: buffer to save result
 * @i: index of buffer
 * @s: string
 * Return: num of printed chars
*/

int shift_R(char *b, int *i, char *s)
{
	int c, j = 0, k = 0;
	char *a = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *r = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM";

	if (!s)
		s = "(null)";
	while (s[j])
	{
		for (c = 0; a[c]; c++)
			if (s[j] == a[c])
			{
				k += add_char(b, r[c], i);
				c = -1;
				break;
			}
		if (c != -1)
			k += add_char(b, s[j], i);
		j++;
	}

	return (k);
}

/**
 * call_funcs - handle the calling
 * @format: string
 * @i: index of that string
 * @buffer: the buffer
 * @ind: index of buffer
 * @ap: arguments
 * Return: number of printed chars
*/

int call_funcs(const char *format, int *i, char *buffer, int *ind, va_list ap)
{
	if (format[*i + 1] == '\0')
		return (-1);
	else if (format[*i + 1] == 'c')
		return (add_char(buffer, va_arg(ap, int), ind));
	else if (format[*i + 1] == 's')
		return (add_string(buffer, va_arg(ap, char*), ind, "(null)"));
	else if (format[*i + 1] == '%')
		return (add_char(buffer, '%', ind));
	else if (format[*i + 1] == 'i' || format[*i + 1] == 'd')
		return (print_int(buffer, ind, va_arg(ap, int)));
	else if (format[*i + 1] == 'b')
		return (change_base(buffer, ind, va_arg(ap, unsigned int), 2, 0));
	else if (format[*i + 1] == 'u')
		return (change_base(buffer, ind, va_arg(ap, unsigned int), 10, 0));
	else if (format[*i + 1] == 'o')
		return (change_base(buffer, ind, va_arg(ap, unsigned int), 8, 0));
	else if (format[*i + 1] == 'x' || format[*i + 1] == 'X')
		return (change_base(buffer, ind, va_arg(ap, unsigned int), 16,
					format[*i + 1] == 'X' ? 0 : 32));
	else if (format[*i + 1] == 'S')
		return (print_string(va_arg(ap, char*), buffer, ind));
	else if (format[*i + 1] == 'p')
		return (print_address(buffer, ind, va_arg(ap, unsigned long)));
	else if (format[*i + 1] == 'r')
		return (rev_str(buffer, ind, va_arg(ap, char*)));
	else if (format[*i + 1] == 'R')
		return (shift_R(buffer, ind, va_arg(ap, char*)));
	return (add_char(buffer, '%', ind) +
		add_char(buffer, format[*i + 1], ind));
}
