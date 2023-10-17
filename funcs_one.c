#include "main.h"

/**
 * add_char - add a letter to buffer
 * Description: if buffer is full after addition print buffer
 * @buffer: the buffer
 * @c: the letter
 * @index: a pointer to index or size of buffer so we can edit
 * Return: If we print we return BUFF_SIZE MACRO else 0
*/

int add_char(char *buffer, char c, int *index)
{
	if (*index == BUFF_SIZE - 1)
	{
		buffer[*index] = c;
		write(1, buffer, BUFF_SIZE);
		*index = 0;
		return (BUFF_SIZE);
	}
	buffer[*index] = c;
	*index = *index + 1;
	return (0);
}

/**
 * add_string - add a string to buffer
 * @buffer: the buffer
 * @t: the string
 * @index: pointer to index
 * @de_fault: in case t is invalid add de_fault instead
 * Return: number or printed charaters
*/

int add_string(char *buffer, char *t, int *index, char *de_fault)
{
	int printed = 0;

	if (!t)
		t = de_fault;
	while (*t)
		printed += add_char(buffer, *t++, index);
	return (printed);
}

/**
 * get_length - calculate length of number in given base
 * @number: number
 * @base: base
 * Return: New length
*/

int get_length(unsigned long number, int base)
{
	int length = 0;

	do {
		length++;
		number /= base;
	} while (number);

	return (length);
}

/**
 * change_base - change the base of a number to a given base
 * @buffer: place the result inside the buffer
 * @index: pointer to index
 * @num: must be of size unsigned int
 * @base: given base can't be higher than 16
 * @fla: flag to set captial letters or small
 * Return: number of printed charaters if any
*/

int change_base(char *buffer, int *index, unsigned int num, int base, int fla)
{
	int length = get_length(num, base);
	int case_sensitive = 0, position = length - 1;
	char t[65];

	t[length] = '\0';
	if (fla)
		case_sensitive = 32;
	do {
		if (num % base == 10)
			t[position] = 'A' + case_sensitive;
		else if (num % base == 11)
			t[position] = 'B' + case_sensitive;
		else if (num % base == 12)
			t[position] = 'C' + case_sensitive;
		else if (num % base == 13)
			t[position] = 'D' + case_sensitive;
		else if (num % base == 14)
			t[position] = 'E' + case_sensitive;
		else if (num % base == 15)
			t[position] = 'F' + case_sensitive;
		else
			t[position] = '0' + num % base;
		position--, num /= base;
	} while (num);
	return (add_string(buffer, t, index, "0"));
}

/**
 * print_int - convert int into string save it into buffer
 * @buffer: the buffer
 * @index: pointer to index of buffer
 * @num: number of type int
 * Return: number of written charaters
*/

int print_int(char *buffer, int *index, int num)
{
	int count = 0;
	char number[32];
	int num_ind = 32;

	if (num < 0)
	{
		count += add_char(buffer, '-', index);
		do {
			num_ind--;
			number[num_ind] = '0' - num % 10;
			num /= 10;
		} while (num);
		while (num_ind < 32)
		{
			count += add_char(buffer, number[num_ind], index);
			num_ind++;
		}
		return (count);
	}
	do {
	num_ind--;
	number[num_ind] = '0' + num % 10;
	num /= 10;
	} while (num);
	while (num_ind < 32)
	{
		count += add_char(buffer, number[num_ind], index);
		num_ind++;
	}
	return (count);
}
