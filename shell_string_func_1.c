#include "shell.h"

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	unsigned int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);

	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));

	if (!ret)
		return (NULL);

	for (length++; length--;)
		ret[length] = *--str;

	return (ret);
}

/**
 * _puts - prints input string
 * @str: the string to be printed
 */
void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - writes the char c to stdout
 * @c: The char to print
 * Return: On success 1.
 * On error -1 and errno is set
 */
int _putchar(char c)
{
	static int i;
	static char buffr[WRITE_FULL_BUFFER_SIZE];

	if (c == NEGATIVE_ONE || i >= WRITE_FULL_BUFFER_SIZE)
	{
		write(1, buffr, i);
		i = 0;
	}

	if (c != NEGATIVE_ONE)
		buffr[i++] = c;

	return (1);
}
